#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <string>
#include "lexical_analysis.h"
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

int main(int argc, char *argv[])
{
    puts("Please input the source file name:");
    getline(cin, sourcefilename);
    if (sourcefilename.empty()) {
        sourcefilename = "16061175_test.txt";
    }
    psin = fopen(sourcefilename.c_str(), "r");
    setup();
    while (true) {
        insymbol();
    }
    return 0;
}