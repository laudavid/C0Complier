#include <cstdio>
#include <string>
#include <map>
#include <vector>
#include "lexical_analysis.h"
#include "error.h"
#include "tabs.h"

using namespace std;

char ch; //��¼��Դ�����ж�ȡ����һ���ַ�
string id; //��¼��ʶ�������ֻ��������
symbol sy; //��¼��ǰ���ʷ��ŵ�����
int inum; //��¼�����������ַ�������ֵ
int sleng; //��¼�ַ�������

int sycnt; //ͳ���ѷ����ĵ��ʸ���
int lcnt, chcnt; // ��¼��ǰ�ַ����ڵ�����������
bool errflag; //����Ƿ�������


const char *symstr[] = { //����������Ӧ�����Ƿ���˳��Ӧ����symbol��Ա�����˳��һ��
    "intcon", "charcon", "stringcon",
    "plus", "minus", "times", "idiv",
    "eql", "neq", "gtr", "geq", "lss", "leq",
    "lparent", "rparent", "lbracket", "rbracket", "lbrace", "rbrace",
    "comma", "semicolon", "colon", "becomes",
    "ident", //"mainsy", "scanfsy", "printfsy",
    "constsy", "returnsy", "intsy", "charsy", "voidsy",
    "ifsy", "switchsy", "casesy", "defaultsy", "whilesy","eofsy"
};

void lexcial_init()
{
    ch = ' ';
    sycnt = 0;
    lcnt = 1;
    chcnt = 0;
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

    ch = (char)fgetc(src_file);
    chcnt++;
    if (ch == EOF) {
        eofflag = true;
    }
    else if (ch == '\n') {
        eolnflag = true;
    }
}



void print_symbol()
{
    switch (sy) {
    case intcon:
        printf("%-4d %-10s %d\n", ++sycnt, symstr[sy], inum);
        break;
    case charcon:
        printf("%-4d %-10s \'%c\'\n", ++sycnt, symstr[sy], inum);
        break;
    case stringcon:
        printf("%-4d %-10s \"%s\"\n", ++sycnt, symstr[sy], stab[inum].c_str());
        break;
    default:
        printf("%-4d %-10s %s\n", ++sycnt, symstr[sy], id.c_str());
        break;
    }
}

void insymbol()
{
    int k = 0;
    id.clear();
    errflag = false;

    while (ch == ' ' || ch == '\t' || ch == '\n') {
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
        inum = 0;
        sy = intcon;
        if (ch == '0') {
            nextch();
        }
        else {
            do {
                inum = inum * 10 + ch - '0';
                nextch();
            } while (isdigit(ch));
        }
    }
    else if (ch == '\'') { //�ַ�����
        nextch();
        if (isalnum(ch) || ch == '_' || ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            inum = (int)ch;
            sy = charcon;
        }
        else {
            error(1);  //���Ϸ����ַ�����
        }
        nextch();
        if (ch == '\'') {
            nextch();
        }
        else {
            error(2); //�ַ��������޵�����
        }
    }
    else if (ch == '\"') { //�ַ���������
        k = 0;
        nextch();
        while (ch != '\"') {
            if (ch >= 32 && ch <= 126) {
                id += ch;
                if (ch == '\\') {
                    id += ch;
                }
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
            error(3); //�ַ�������˫���Ž���
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
            error(4); //���Ϸ����������'!'
        }
    }
    else if (sps.count(ch)) { //�����Ϸ����������
        id += ch;
        sy = sps[ch];
        nextch();
    }
    else if (ch == EOF) {
        sy = eofsy;
    }
    else {
        error(5); //���Ϸ����������
    }
    //print_symbol();
}