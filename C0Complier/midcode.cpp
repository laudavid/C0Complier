#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <string>
#include <vector>
#include "midcode.h"
#include "table.h"

using namespace std;

vector<midcodeitem> midcode;
int mx = -1;

void midcode_enter(optyp op, int v1, int v2, int v3)
{
    ++mx;
    midcodeitem item;
    item.op = op;
    item.v1 = v1;
    item.v2 = v2;
    item.v3 = v3;
    item.lev = b;
    midcode.push_back(item);
}


void print_midcode(FILE *out, int index)
{
    midcodeitem item = midcode[index]; 
    
    fprintf(out, "    ");
    switch (item.op) {
    case _const:
        if (item.v1 == ints) {
            fprintf(out, "const int %s = %d\n", tab[item.v2].name.c_str(), item.v3);
        }
        else {
            fprintf(out, "const char %s = '%c'\n", tab[item.v2].name.c_str(), item.v3);
        }
        break;
    case _var:
        if (item.v1 == ints) {
            fprintf(out, "var int %s\n", tab[item.v2].name.c_str());
        }
        else {
            fprintf(out, "var char %s\n", tab[item.v2].name.c_str());
        }
        break;

    case _array:
        if (item.v1 == ints) {
            fprintf(out, "array int %s %d\n", tab[item.v2].name.c_str(), item.v3);
        }
        else {
            fprintf(out, "array char %s %d\n", tab[item.v2].name.c_str(), item.v3);
        }
        break;
    case _func:
        fprintf(out, "\n\n");
        if (item.v1 == ints) {
            fprintf(out, "int %s()\n", tab[item.v2].name.c_str());
        }
        else if (item.v1 == chars) {
            fprintf(out, "char %s()\n", tab[item.v2].name.c_str());
        }
        else {
            fprintf(out, "void %s()\n", tab[item.v2].name.c_str());
        }
        break;
    case _para:
        if (item.v1 == ints) {
            fprintf(out, "para int %s\n", tab[item.v2].name.c_str());
        }
        else {
            fprintf(out, "para char %s\n", tab[item.v2].name.c_str());
        }
        break;
    case _push:
        fprintf(out, "push $t%d\n", item.v1);
        break;
    case _call:
        fprintf(out, "call %s\n", tab[item.v1].name.c_str());
        break;
    case _ret:
        if (item.v1 != -1) {
            fprintf(out, "ret $t%d\n", item.v1);
        }
        else {
            fprintf(out, "ret\n");
        }
        break;
    case _assign:
        if (item.v2 == RET) {
            fprintf(out, "$t%d = RET\n", item.v1);
        }
        else {
            fprintf(out, "%s = $t%d\n", tab[item.v1].name.c_str(), item.v2);
        }
        break;
    case _arrassign:
        fprintf(out, "%s[$t%d] = $t%d\n", tab[item.v1].name.c_str(), item.v2, item.v3);
        break;
    case _conload:
        if (item.v2 == ints) {
            fprintf(out, "$t%d = %d\n", item.v1, item.v3);
        }
        else if (item.v2 == chars) {
            fprintf(out, "$t%d = '%c'\n", item.v1, item.v3);
        }
        else {
            fprintf(out, "$t%d = \"%s\"\n", item.v1, stab[item.v3].c_str());
        }
        break;
    case _varload:
        fprintf(out, "$t%d = %s\n", item.v1, tab[item.v2].name.c_str());
        break;
    case _arrload:
        fprintf(out, "$t%d = %s[$t%d]\n", item.v1, tab[item.v2].name.c_str(), item.v3);
        break;
    case _label:
        fprintf(out, "label_%d:\n", item.v1);
        break;
    case _goto:
        fprintf(out, "GOTO label_%d\n", item.v1);
        break;
    case _bz:
        fprintf(out, "BZ label_%d\n", item.v1);
        break;
    case _neg:
        fprintf(out, "$t%d = -$t%d\n", item.v1, item.v2);
        break;
    case _plus:
        fprintf(out, "$t%d = $t%d + $t%d\n", item.v1, item.v2, item.v3);
        break;
    case _minus:
        fprintf(out, "$t%d = $t%d - $t%d\n", item.v1, item.v2, item.v3);
        break;
    case _times:
        fprintf(out, "$t%d = $t%d * $t%d\n", item.v1, item.v2, item.v3);
        break;
    case _idiv:
        fprintf(out, "$t%d = $t%d / $t%d\n", item.v1, item.v2, item.v3);
        break;
    case _eql:
        fprintf(out, "$t%d == $t%d\n", item.v2, item.v3);
        break;
    case _neq:
        fprintf(out, "$t%d != $t%d\n", item.v2, item.v3);
        break;
    case _gtr:
        fprintf(out, "$t%d > $t%d\n", item.v2, item.v3);
        break;
    case _geq:
        fprintf(out, "$t%d >= $t%d\n", item.v2, item.v3);
        break;
    case _lss:
        fprintf(out, "$t%d < $t%d\n", item.v2, item.v3);
        break;
    case _leq:
        fprintf(out, "$t%d <= $t%d\n", item.v2, item.v3);
        break;

    default:
        fprintf(out, "unknown midcode op: %d\n", item.op);
        printf("unknown midcode op: %d\n", item.op);
        break;
    }
}


void print_midcodes()
{
    FILE *out;

    out = fopen("..\\midcode.txt", "w");
    for (int i = 0; i <= mx; i++) {
        print_midcode(out, i);
    }
    fclose(out);
    printf("���ɵ��м�����������midcode.txt�ļ��С�\n");
}
