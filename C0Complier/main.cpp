#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <map>
#include "lexical_analysis.h"
#include "syntax_analysis.h"
#include "tabs.h"

using namespace std;


string sourcefilename; //Դ�����ļ���
FILE *psin; //Դ�����ļ�ָ��

map<string, symbol> ksy; //�����ֱ�
map<char, symbol> sps; //�����ַ���
vector<tabitem> tab; //���ű�
int t;
vector<btabitem> btab; //�ֳ����
int b;
vector<string> stab; //�ַ���������
int sx; //�ַ�������������

void setup()
{
    t = -1;
    b = -1;
    sx = -1;

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



int main(int argc, char *argv[])
{
    puts("Please input the source file name:");
    getline(cin, sourcefilename);
    if (sourcefilename.empty()) {
        sourcefilename = "16061175_test.txt";
    }
    psin = fopen(sourcefilename.c_str(), "r");
    setup();
    lexcial_init();
    syntax_analysis();
    

    return 0;
}