#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <map>
#include "lexical_analysis.h"
#include "syntax_analysis.h"
#include "table.h"
#include "error.h"
#include "midcode.h"
#include "mips.h"

using namespace std;

string src_file_name; //Դ�����ļ���
FILE *src_file; //Դ�����ļ�ָ��


int main(void)
{
    puts("������Դ�ļ����ƻ�·����ֱ�Ӱ��س���Ĭ����16061175_test.txtΪԴ�ļ���:");
    getline(cin, src_file_name);
    if (src_file_name.empty()) {
        //sourcefilename = "testcode.c";
        src_file_name = "16061175_test.txt";
    }
    src_file = fopen(src_file_name.c_str(), "r");
    tabs_init();
    lexcial_init();
    syntax_analysis();
    if (noerror) {
        print_midcode();
        gen_mips();
    }
    
    return 0;
}