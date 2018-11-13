#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <string>
#include <map>
#include <vector>
#include "lexical_analysis.h"
using namespace std;

FILE *psin; //Դ�����ļ�ָ��

char ch; //��¼��Դ�����ж�ȡ����һ���ַ�
string id; //��¼��ʶ�������ֻ��������
symbol sy; //��¼��ǰ���ʷ��ŵ�����
int inum; //��¼�����������ַ�������ֵ
int sleng; //��¼�ַ�������

map<string, symbol> ksy; //�����ֱ�
map<char, symbol> sps; //�����ַ���
vector<string> stab; //�ַ���������
int sx; //�ַ�������������
int sycnt; //ͳ���ѷ����ĵ��ʸ���
int lcnt, chcnt; // ��¼��ǰ�ַ����ڵ�����������
bool errflag;

const char *symstr[] = { //����������Ӧ�����Ƿ���˳��Ӧ����symbol��Ա�����˳��һ��
    "intcon", "charcon", "stringcon",
    "plus", "minus", "times", "idiv",
    "eql", "neq", "gtr", "geq", "lss", "leq",
    "lparent", "rparent", "lbracket", "rbracket", "lbrace", "rbrace",
    "comma", "semicolon", "colon", "becomes",
    "ident", "mainsy", "scanfsy", "printfsy",
    "constsy", "returnsy", "intsy", "charsy", "voidsy",
    "ifsy", "switchsy", "casesy", "defaultsy", "whilesy"
};

void setup(FILE *in)
{
    psin = in;
    sx = -1;
    ch = ' ';
    sycnt = 0;
    lcnt = 1;
    chcnt = 0;

    ksy["const"] = constsy;
    ksy["if"] = ifsy;
    ksy["switch"] = switchsy;
    ksy["case"] = casesy;
    ksy["default"] = defaultsy;
    ksy["while"] = whilesy;
    ksy["return"] = returnsy;
    ksy["int"] = intsy;
    ksy["char"] = charsy;
    ksy["void"] = voidsy;
    ksy["main"] = mainsy;
    ksy["scanf"] = scanfsy;
    ksy["printf"] = printfsy;

    sps['+'] = _plus;
    sps['-'] = _minus;
    sps['*'] = times;
    sps['/'] = idiv;
    sps['('] = lparent;
    sps[')'] = rparent;
    sps['['] = lbracket;
    sps[']'] = rbracket;
    sps['{'] = lbrace;
    sps['}'] = rbrace;
    sps[','] = comma;
    sps[';'] = semicolon;
    sps[':'] = colon;
}


void nextch()
{
    static bool eofflag = false, eolnflag = false;

    if (eofflag) {
        exit(0);
    }
    else if (eolnflag) {
        lcnt++;
        chcnt = 0;
        eolnflag = false;
    }

    ch = fgetc(psin);
    chcnt++;
    if (ch == EOF) {
        eofflag = true;
    }
    else if (ch == '\n') {
        eolnflag = true;
    }
}

void error(int n)
{
    errflag = true;
    printf("%s:%d:%d: error: ", sourcefile.c_str(), lcnt, chcnt);
    switch (n) {
    case 0:
        puts("illegal integer constant with a leading '0'");
        break;
    case 1:
        printf("illegal character constant '%c'\n", ch);
        nextch();
        break;
    case 2:
        puts("missing terminating ' character");
        nextch();
        break;
    case 3:
        puts("missing terminating \" character");
        nextch();
        break;
    case 4:
        puts("illegal symbol '!' in program");
        break;
    case 5:
        printf("illegal symbol '%c' in program\n", ch);
        nextch();
        break;
    default:
        break;
    }
}

void printsymbol()
{
    switch (sy) {
    case intcon:
        printf("%-3d %-10s %d\n", ++sycnt, symstr[sy], inum);
        break;
    case charcon:
        printf("%-3d %-10s \'%c\'(%d)\n", ++sycnt, symstr[sy], inum, inum);
        break;
    case stringcon:
        printf("%-3d %-10s \"%s\"(length: %d)\n", ++sycnt, symstr[sy], stab[inum].c_str(), sleng);
        break;
    default:
        printf("%-3d %-10s %s\n", ++sycnt, symstr[sy], id.c_str());
        break;
    }
}

void insymbol()
{
    int k = 0;
    id.clear();
    errflag = false;

    while (ch == ' ' || ch == '\t' || ch == '\n' || ch == EOF) {
        nextch();
    }

    if (isalpha(ch) || ch == '_') { //��ʶ��������
        do {
            id += ch;
            nextch();
        } while (isalnum(ch) || ch == '_');

        if (ksy.count(id)) {
            sy = ksy[id];
        }
        else {
            sy = ident;
        }
    }
    else if (isdigit(ch)) { //�޷�����������
        if (ch != '0') {
            inum = 0;
            sy = intcon;
            do {
                inum = inum * 10 + ch - '0';
                nextch();
            } while (isdigit(ch));
        }
        else {
            nextch();
            if (isdigit(ch)) {
                error(0); //����ǰ�������
            }
            else {
                inum = 0;
                sy = intcon;
            }
        }
    }
    else if (ch == '\'') { //�ַ�����
        nextch();
        if (isalnum(ch) || ch == '_' || ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            inum = (int)ch;
            nextch();
            if (ch == '\'') {
                sy = charcon;
                nextch();
            }
            else {
                error(2); //�ַ��������޵�����
            }
        }
        else {
            error(1);  //���Ϸ����ַ���������
        }
    }
    else if (ch == '\"') { //�ַ���������
        k = 0;
        nextch();
        while (ch != '\"') {
            if (ch >= 32 && ch <= 126) {
                id += ch;
                k++;
                nextch();
            }
            else {
                errflag = true;
                break;
            }
        }
        if (!errflag) {
            sy = stringcon;
            stab.push_back(id);
            inum = ++sx;
            sleng = k;
            nextch();
        }
        else {
            error(3); //�ַ����к��зǷ��ַ�
        }
    }
    else if (ch == '>') { //���ںţ����ڵ��ں�
        id += ch;
        nextch();
        if (ch == '=') {
            id += ch;
            sy = geq;
            nextch();
        }
        else {
            sy = gtr;
        }
    }
    else if (ch == '<') { //С�ںţ�С�ڵ��ں�
        id += ch;
        nextch();
        if (ch == '=') {
            id += ch;
            sy = leq;
            nextch();
        }
        else {
            sy = lss;
        }
    }
    else if (ch == '=') { //��ֵ���ţ����ں�
        id += ch;
        nextch();
        if (ch == '=') {
            id += ch;
            sy = eql;
            nextch();
        }
        else {
            sy = becomes;
        }
    }
    else if (ch == '!') { //���Ⱥ�
        id += ch;
        nextch();
        if (ch == '=') {
            id += ch;
            sy = neq;
            nextch();
        }
        else {
            error(4); //���Ϸ����������
        }
    }
    else if (sps.count(ch)) { //�����Ϸ����������
        id += ch;
        sy = sps[ch];
        nextch();
    }
    else {
        error(5); //���Ϸ����������
    }

    if (!errflag) {
        //printsymbol();
    }
}