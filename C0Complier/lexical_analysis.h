#ifndef _LEXICAL_ANALYSIS_H_
#define _LEXICAL_ANALYSIS_H_
#include <cstdio>
#include <string>
#include <set>
#include "table.h"

using namespace std;

extern string src_file_name;
extern FILE *src_file;
extern int ch;
extern int lcnt, chcnt; // ��¼��ǰ�ַ����ڵ�����������
extern string id; //��¼��ʶ�������ֻ��������
extern symbol sy; //��¼��ǰ���ʷ��ŵ�����
extern int inum; //��¼�����������ַ�������ֵ
extern int sleng; //��¼�ַ�������

void lexcial_init();
void nextch();
void insymbol();
void print_symbol();

#endif // !_LEXICAL_ANALYSIS_H_
