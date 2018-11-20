#ifndef _LEXICAL_ANALYSIS_H_
#define _LEXICAL_ANALYSIS_H_
#include <cstdio>
#include <string>
#include "tabs.h"

using namespace std;

extern string sourcefilename;
extern FILE *psin;
extern char ch;
extern int lcnt, chcnt; // ��¼��ǰ�ַ����ڵ�����������
extern string id; //��¼��ʶ�������ֻ��������
extern symbol sy; //��¼��ǰ���ʷ��ŵ�����
extern int inum; //��¼�����������ַ�������ֵ
extern int sleng; //��¼�ַ�������

void lexcial_init();
void nextch();
void insymbol();
void printsymbol();

#endif // !_LEXICAL_ANALYSIS_H_
