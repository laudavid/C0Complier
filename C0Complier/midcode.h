#ifndef _MIDCODE_H_
#define _MIDCODE_H_

#include <vector>

using namespace std;

#define RET -5
#define SCANF 1
#define PRINTF 2

typedef enum {
    _condef, _vardef, _arrdef, _funcdef, _paradef, //������Ԫʽ����_funcdef�ⲻ������Ӧ��Ŀ����룬���ÿ����Ż�
    _conload, _varload, _arrload, //ȡֵ��Ԫʽ���ɿ����������м����ʱ�Ż�
    _assign, _arrassign, //��ֵ��Ԫʽ���ɿ����������м����ʱ�Ż�
    _neg, _plus, _minus, _times, _idiv, //������Ԫʽ���ɿ����������м����ʱ���г����滻�ͳ����ϲ���ɾ���������
    _eql, _neq, _gtr, _geq, _lss, _leq, //��ϵ�Ƚ���Ԫʽ
    _label, _goto, _bz, //_bz�ɽ�ϱȽ������ѡ����ŵ�ָ��
    _ret, _push, _push_scanf, _call, _std_call
} optyp;

typedef enum {
    _intcon, _charcon, _strcon,  _tmpvar, _localvar, _globalvar, _arrvar, _retval, _reterr
} operandtyp;

typedef struct {
    optyp op;
    int v1, v2, v3;
    int t1, t2, t3; 
    int lev;
} midcodeitem;

extern vector<midcodeitem> midcode;
extern int mx;

void midcode_enter(optyp op, int v1, int v2, int v3);
void midcode_enter2(optyp op, int v1, int v2, int v3, int t1, int t2, int t3);
void print_midcode(FILE *out, int index);
void print_midcodes();
void print_midcodes_opt();
#endif
