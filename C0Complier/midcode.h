#ifndef _MIDCODE_H_
#define _MIDCODE_H_

#include <vector>

using namespace std;

#define RET -5
#define SCANF 1
#define PRINTF 2

typedef enum {
    _const, _var, _array, _func, _para, //声明四元式，除_func外不生成相应的目标代码，不用考虑优化
    _conload, _varload, _arrload, //取值四元式，可考虑在生成中间代码时优化
    _assign, _arrassign, //赋值四元式，可考虑在生成中间代码时优化
    _neg, _plus, _minus, _times, _idiv, //运算四元式，可考虑在生成中间代码时进行常量替换和常数合并，删除冗余代码
    _eql, _neq, _gtr, _geq, _lss, _leq, //关系比较四元式
    _label, _goto, _bz, //_bz可结合比较运算符选择更优的指令
    _push, _call, _ret,
} optyp;


typedef struct {
    optyp op;
    int v1, v2, v3;
    int lev;
} midcodeitem;

extern vector<midcodeitem> midcode;
extern int mx;

void midcode_enter(optyp op, int v1, int v2, int v3);
void print_midcode(FILE *out, int index);
void print_midcodes();
#endif
