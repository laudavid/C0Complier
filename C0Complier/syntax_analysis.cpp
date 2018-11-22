#include <iostream>
#include <cstdio>
#include <string>
#include <map>
#include <vector>
#include <set>
#include "lexical_analysis.h"
#include "syntax_analysis.h"
#include "error.h"
#include "tabs.h"

using namespace std;

int dx, prt, prb, level;

void constdef()
{
    int line = lcnt;
    int sign = 1;
    insymbol();
    if (sy == intsy) {
        do {
            insymbol();
            if (sy == ident) {
                enter(id, constant, ints, 0);
                insymbol();
                if (sy == becomes) {
                    insymbol();
                }
                else {
                    error(7);
                }
                if (sy == _plus || sy == _minus) {
                    sign = (sy == _minus) ? -1 : 1;
                    insymbol();
                }
                if (sy == intcon) {
                    tab[t].adr = sign * inum;
                    insymbol();
                }
                else {
                    error(8);
                }
            }
            else {
                error(6);
            }
        } while (sy == comma);
    }
    else if (sy == charsy) {
        do {
            insymbol();
            if (sy == ident) {
                enter(id, constant, chars, 0);
                insymbol();
                if (sy == becomes) {
                    insymbol();
                }
                else {
                    error(7);
                }
                if (sy == charcon) {
                    tab[t].adr = inum;
                    insymbol();
                }
                else {
                    error(8);
                }
            }
            else {
                error(6);
            }
        } while (sy == comma);
    }
    else {
        error(9);
    }

    if (sy == semicolon) {
        insymbol();
    }
    else {
        error(13);
    }
    printf("line %d: ����һ����������\n", line);
}


void vardef(types typ, string name)
{
    int line = lcnt;
    if (sy == lbracket) {
        insymbol();
        if (sy == intcon) {
            if (inum > 0) {
                enter(name, arrays, typ, inum);
            }
            else {
                error(10);//����Ԫ�ظ���������0
            }
            insymbol();
        }
        else {
            error(8);//û��ָ������Ԫ��
        }
        if (sy == rbracket) {
            insymbol();
        }
        else {
            error(12);//ȱ����������
        }
    }
    else {
        enter(name, variable, typ, 0);
    }

    while (sy == comma) {
        insymbol();
        if (sy == ident) {
            name = id;
            insymbol();
            if (sy == lbracket) {
                insymbol();
                if (sy == intcon) {
                    if (inum > 0) {
                        enter(name, arrays, typ, inum);
                    }
                    else {
                        error(10);//����Ԫ�ظ���������0
                    }
                    insymbol();
                }
                else {
                    error(11);//û��ָ������Ԫ�ظ���
                }
                if (sy == rbracket) {
                    insymbol();
                }
                else {
                    error(12);//ȱ����������
                }
            }
            else {
                enter(name, variable, typ, 0);
            }
        }
        else {
            error(9); //�����ޱ�ʶ��
        }
    }

    if (sy == semicolon) {
        insymbol();
    }
    else {
        error(13);
    }
    printf("line %d: ����һ����������\n", line);
}


types factor(int *value)
{
    types typ = ints;
    int val, sign = 1;
    int i;
    switch (sy) {
    case charcon:
        *value = inum;
        typ = chars;
        insymbol();
        break;
    case _plus:
    case _minus:
        sign = (sy == _plus) ? 1 : -1;
        insymbol();
        if (sy == intcon) {
            *value = inum * sign;
            typ = ints;
            insymbol();
        }
        else {
            error(8);
        }
        break;
    case intcon:
        *value = inum;
        typ = ints;
        insymbol();
        break;
    case lparent:
        insymbol();
        typ = ints;
        expression(&val);
        *value = val;
        if (sy == rparent) {
            insymbol();
        }
        else {
            error(14);
        }
        break;
    case ident:
        i = loc(id);
        if (i != 0) {
            switch (tab[i].obj) {
            case constant:
                *value = tab[i].adr;
                typ = tab[i].typ;
                insymbol();
                break;
            case variable:
                *value = 1;
                typ = tab[i].typ;
                insymbol();
                break;
            case arrays:
                insymbol();
                if (sy == lbracket) {
                    insymbol();
                }
                else {
                    error(22);
                }
                typ = tab[i].typ;
                expression(value);
                if (sy == rbracket) {
                    insymbol();
                }
                else {
                    error(12);
                }
                break;
            case function:
                if (tab[i].typ != voids) {
                    typ = tab[i].typ;
                    *value = 1;
                    call(i);
                }
                else {
                    error(23);
                }
                break;
            default:
                break;
            }
        }
        else {
            error(18);//δ����ı�ʶ��

        }
        break;
    default:
        error(24);
        break;
    }
    printf("line %d: ����һ������\n", lcnt);
    return typ;
}

types term(int *value)
{
    int val, tmp;
    types typ = ints;
    typ = factor(&val);
    symbol op;
    while (sy == times || sy == idiv) {
        typ = ints;
        op = sy;
        insymbol();
        factor(&tmp);
        if (op == times) {
            val *= tmp;
        }
        else {
            val /= tmp;
        }
    }
    *value = val;
    printf("line %d: ����һ����\n", lcnt);
    return typ;
}

types expression(int *value)
{
    int sign = 1;
    int val, tmp;
    types typ = chars, typ1 = chars;
    if (sy == _plus || sy == _minus) {
        sign = (sy == _plus) ? 1 : -1;
        insymbol();
        typ = ints;
    }
    typ1 = term(&val);
    val *= sign;
    symbol op;
    while (sy == _plus || sy == _minus) {
        typ = ints;
        op = sy;
        insymbol();
        term(&tmp);
        if (op == _plus) {
            val += tmp;
        }
        else {
            val -= tmp;
        }
    }
    *value = val;
    printf("line %d: ����һ�����ʽ\n", lcnt);
    if (typ == ints || typ1 == ints) {
        return ints;
    }
    else {
        return chars;
    }
}

void ifstatement()
{
    insymbol();
    int value1, value2;
    types typ1 = ints, typ2 = ints;
    if (sy == lparent) {
        insymbol();
    }
    else {
        error(26);
    }
    typ1 = expression(&value1);
    if (relationop.count(sy)) {
        insymbol();
        typ2 = expression(&value2);
        if (typ2 != typ1) {
            error(27);
        }
    }
    else {
        if (typ1 != ints) {
            error(28);
        }
    }
    printf("line %d: ����һ������\n", lcnt);
    if (sy == rparent) {
        insymbol();
    }
    else {
        error(14);
    }
    statement();
    printf("line %d: ����һ���������\n", lcnt - 1);
}
void whilestatement()
{
    insymbol();
    int value1, value2;
    types typ1 = ints, typ2 = ints;
    if (sy == lparent) {
        insymbol();
    }
    else {
        error(26);
    }
    typ1 = expression(&value1);
    if (relationop.count(sy)) {
        insymbol();
        typ2 = expression(&value2);
        if (typ2 != typ1) {
            error(27);
        }
    }
    else {
        if (typ1 != ints) {
            error(28);
        }
    }
    printf("line %d: ����һ������\n", lcnt);
    if (sy == rparent) {
        insymbol();
    }
    else {
        error(14);
    }
    statement();
    printf("line %d: ����һ��ѭ�����\n", lcnt - 1);
}

void onecase(types typ)
{
    insymbol();
    int sign = 1, value;
    if (sy == charcon) {
        value = inum;
        insymbol();
        if (typ != chars) {
            error(29);
        }
    }
    else {
        if (sy == _plus || sy == _minus) {
            sign = (sy == _plus) ? 1 : -1;
            insymbol();
        }
        if (sy == intcon) {
            value = sign * inum;
            insymbol();
            if (typ != ints) {
                error(29);
            }
        }
        else {
            error(8);
        }
    }

    if (sy == colon) {
        insymbol();
    }
    else {
        error(21);
    }
    statement();
    printf("line %d: ����һ����������\n", lcnt - 1);
}

void switchstatement()
{
    insymbol();
    if (sy == lparent) {
        insymbol();
    }
    else {
        error(26);
    }
    int value;
    types typ = expression(&value);
    if (sy == rparent) {
        insymbol();
    }
    else {
        error(14);
    }

    if (sy == lbrace) {
        insymbol();
    }
    else {
        error(15);
    }

    if (sy == casesy) {
        do {
            onecase(typ);
        } while (sy == casesy);
    }
    else {
        error(30);// ��case���
    }
    if (sy == defaultsy) {
        insymbol();
        if (sy == colon) {
            insymbol();
        }
        else {
            error(21);
        }
        statement();
        printf("line %d: ����һ��ȱʡ\n", lcnt - 1);
    }
    if (sy == rbrace) {
        insymbol();
    }
    else {
        error(16);
    }
    printf("line %d: ����һ��������\n", lcnt - 1);
}


void returnstatement()
{
    types typ = ints;
    int value;
    insymbol();
    if (sy == lparent) {
        insymbol();
        typ = expression(&value);
        if (typ != tab[prt].typ) {
            error(25);//����ֵ���Ͳ�һ��
        }
        if (sy == rparent) {
            insymbol();
        }
        else {
            error(14);
        }
    }
    printf("line %d: ����һ���������\n", lcnt);
}


void assignment(int i)
{
    types typ1 = ints, typ2 = ints;
    int value1, value2;
    insymbol();
    if (tab[i].obj == arrays) {
        if (sy == lbracket) {
            insymbol();
        }
        else {
            error(22);
        }
        typ1 = expression(&value1);
        if (typ1 != ints) {
            error(31);
        }
        //else if(value<0 || value>tab[i].arrcnt-1) {
        //    error(0);//����Խ��
        //}
        if (sy == rbracket) {
            insymbol();
        }
        else {
            error(12);
        }
    }
    if (sy == becomes) {
        insymbol();
    }
    else {
        error(7);
    }
    typ2 = expression(&value2);
    if (typ2 != tab[i].typ) {
        error(32);
    }
    printf("line %d: ����һ����ֵ���\n", lcnt);
}

void standfunc()
{
    int value;
    types typ = ints;
    if (id == "scanf") {
        insymbol();
        if (sy == lparent) {
            do {
                insymbol();
                if (sy == ident) {
                    int i = loc(id);
                    if (i == 0) {
                        error(18);
                    }
                    else if (tab[i].obj != variable) {
                        error(33);
                    }
                    insymbol();
                }
                else {
                    error(6);
                }
            } while (sy == comma);
        }
        else {
            error(26);
        }
        printf("line %d: ����һ�������\n", lcnt);
    }
    else {
        insymbol();
        if (sy == lparent) {
            insymbol();
        }
        else {
            error(26);
        }
        if (sy == stringcon) {
            insymbol();
            if (sy == comma) {
                insymbol();
                typ = expression(&value);
            }
        }
        else {
            typ = expression(&value);
        }
        printf("line %d: ����һ��д���\n", lcnt);
    }

    if (sy == rparent) {
        insymbol();
    }
    else {
        error(14);
    }
}


void call(int i)
{

    int lastp = btab[tab[i].ref].lastpar;
    int cpos = i;
    int value;
    types typ = ints;

    insymbol();
    if (sy == lparent) {
        do {
            insymbol();
            if (sy != rparent) {
                cpos++;
                typ = expression(&value);
                if (cpos > lastp) {
                    error(34); //ʵ�ι���
                }
                else {
                    if (typ != tab[cpos].typ) {
                        error(35);
                    }
                }
            }
        } while (sy == comma);
        printf("line %d: ����һ��ֵ������\n", lcnt);
    }
    else {
        error(26);
    }

    if (sy == rparent) {
        insymbol();
    }
    else {
        error(14);
    }
    if (cpos < lastp) {
        error(36); //ʵ�ι���
    }
    if (tab[i].typ == voids) {
        printf("line %d: ����һ���޷���ֵ�ĺ����������\n", lcnt);
    }
    else {
        printf("line %d: ����һ���з���ֵ�ĺ����������\n", lcnt);
    }
}


void statement()
{
    int i;
    switch (sy) {
    case ifsy:
        ifstatement();
        break;
    case whilesy:
        whilestatement();
        break;
    case switchsy:
        switchstatement();
        break;
    case returnsy:
        returnstatement();
        if (sy == semicolon) {
            insymbol();
        }
        else {
            error(13);
        }
        break;
    case semicolon: insymbol(); printf("line %d: ����һ�������\n", lcnt); break;
    case lbrace: insymbol();
        while (statbegsys.count(sy)) {
            statement();//��䴦���������ֺŶ���һ���ַ�
        }
        if (sy == rbrace) {
            insymbol();
        }
        else {
            error(16);
        }
        break;
    case ident:
        i = loc(id);
        if (i != 0) {
            switch (tab[i].obj) {
            case constant: error(17); break;
            case variable:
            case arrays:
                assignment(i);
                if (sy == semicolon) {
                    insymbol();
                }
                else {
                    error(13);
                }
                break;
            case function:
                if (id == "scanf" || id == "printf") {
                    standfunc();
                }
                else {
                    call(i);
                }
                if (sy == semicolon) {
                    insymbol();
                }
                else {
                    error(13);
                }
                break;
            default:
                break;
            }
        }
        else {
            error(18);//δ����ı�ʶ��
        }
        break;
    default:
        error(20); //���Ϸ����
    }
}


void compoundstatement()
{
    string name;
    types typ = ints;

    while (sy == constsy) {
        constdef();
    }
    while (sy == intsy || sy == charsy) {
        typ = (sy == intsy) ? ints : chars;
        insymbol();
        if (sy == ident) {
            name = id;
            insymbol();
            vardef(typ, name);
        }
        else {
            error(6); //ȱ��������ʶ��
        }
    }

    while (statbegsys.count(sy)) {
        statement();//��䴦���������ֺŶ���һ���ַ�
    }
    printf("line %d: ����һ�������\n", lcnt - 1);
    printf("line %d: ����һ���������\n", lcnt - 1);
}


int paralist()
{
    int paracnt = 0;
    types typ = ints;
    do {
        insymbol();
        if (sy == intsy || sy == charsy) {
            typ = (sy == intsy) ? ints : chars;
            insymbol();
            if (sy == ident) {
                enter(id, variable, typ, 0);
                tab[t].adr = dx;
                //dx += (typ == ints) ? 4 : 1;
                dx += 4;
                paracnt++;
                insymbol();
            }
            else {
                error(6); //ȱ�ٲ�������ʶ��
            }
        }
        else if (sy != rparent) {
            error(9); //ȱ�ٲ������ͱ�ʶ��
        }
    } while (sy == comma);
    if (sy == rparent) {
        insymbol();
    }
    else {
        error(14);
    }
    printf("line %d: ����һ��������\n", lcnt - 1);
    return paracnt;
}


bool funcdef(types typ, string name)
{
    enter(name, function, typ, 0);
    dx = 0; //����
    prt = t;

    ++b;
    btabitem item;
    item.last = 0;
    item.lastpar = 0;
    item.psize = 0;
    item.vsize = 0;
    btab.push_back(item);

    prb = b;
    tab[prt].ref = prb;
    level = 1;
    int paracnt = paralist();
    btab[b].lastpar = t;
    btab[b].psize = dx;

    if (sy == lbrace) {
        insymbol();
        compoundstatement();
    }
    else {
        error(15);//ȱ���������������
    }
    if (sy == rbrace) {
        insymbol();
    }
    else {
        error(16);//ȱ���������Ҵ�����
    }

    if (name == "main" && typ == voids && paracnt == 0) {
        printf("line %d: ����һ���������Ķ���\n", lcnt);
        return true;
    }
    if (typ == voids) {
        printf("line %d: ����һ���޷���ֵ�����Ķ���\n", lcnt - 1);
    }
    else {
        printf("line %d: ����һ���з���ֵ�����Ķ���\n", lcnt - 1);
    }
    return false;
}

void syntax_init()
{
    tabinit("", variable, voids, 0); //ռλ
    tabinit("scanf", function, voids, 0);
    tabinit("printf", function, voids, 0);

    ++b;
    btabitem item;
    item.last = t;
    item.lastpar = 0;
    item.psize = 0;
    item.vsize = 0;
    btab.push_back(item);
    
    dx = 0; //����
    prt = t;
    prb = b;
    level = 0;
}


void program()
{
    bool funcflag = false;
    bool mainflag = false;
    string name;
    types typ = ints;

    insymbol();
    while (sy == constsy) {
        constdef();
    }

    while ((sy == intsy || sy == charsy || sy == voidsy) && !mainflag) {
        if (sy == intsy || sy == charsy) {
            typ = (sy == intsy) ? ints : chars;
            insymbol();
            if (sy == ident) {
                name = id;
                insymbol();
                if (sy == lparent) {
                    funcflag = true;
                    funcdef(typ, name);
                }
                else if (!funcflag) {
                    vardef(typ, name);
                }
                else {
                    error(37); //����ṹ����
                }
            }
            else {
                error(6);
            }
        }
        else { //sy == voidsy
            insymbol();
            if (sy == ident) {
                name = id;
                insymbol();
                if (sy == lparent) {
                    funcflag = true;
                    mainflag = funcdef(voids, name);
                }
                else {
                    error(37); //����ṹ����
                }
            }
            else {
                error(6);
            }
        }
        level = 0;
    }

    if (!mainflag) {
        error(38);
    }
    if (sy != eofsy) {
        error(37);
    }
}
