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

int dx, prt, prmx;
bool retflag;
int labelx;

void constdef()
{
    int line = lcnt;
    int sign = 1;
    insymbol();
    if (sy == intsy) {
        do {
            insymbol();
            if (sy == ident) {
                tab_enter(id, constant, ints, 0);
                insymbol();
                if (sy == becomes) {
                    insymbol();
                }
                else {
                    error(7);
                }
                if (sy == _plus_ || sy == _minus_) {
                    sign = (sy == _minus_) ? -1 : 1;
                    insymbol();
                }
                if (sy == intcon) {
                    tab[t].adr = sign * inum;
                    midcode_enter(_const, ints, t, sign * inum);
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
                tab_enter(id, constant, chars, 0);
                insymbol();
                if (sy == becomes) {
                    insymbol();
                }
                else {
                    error(7);
                }
                if (sy == charcon) {
                    tab[t].adr = inum;
                    midcode_enter(_const, chars, t, inum);
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
                tab_enter(name, arrays, typ, dx);
                tab[t].arrcnt = inum;
                midcode_enter(_array, typ, t, inum);
                //dx += (typ == ints) ? (inum * 4) : inum;
                dx += inum * 4;
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
        tab_enter(name, variable, typ, dx);
        midcode_enter(_var, typ, t, -1);
        //dx += (typ == ints) ? 4 : 1;
        dx += 4;
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
                        tab_enter(name, arrays, typ, dx);
                        tab[t].arrcnt = inum;
                        midcode_enter(_array, typ, t, inum);
                        //dx += (typ == ints) ? (inum * 4) : inum;
                        dx += inum * 4;
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
                tab_enter(name, variable, typ, dx);
                midcode_enter(_var, typ, t, -1);
                //dx += (typ == ints) ? 4 : 1;
                dx += 4;
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


int factor(types *ptyp, int tmp)
{
    types typ = ints, typ1;
    int sign = 1, ret = tmp;
    int i;

    switch (sy) {
    case charcon:
        typ = chars;
        midcode_enter(_conload, tmp, chars, inum);
        ret = tmp;
        insymbol();
        break;
    case _plus_:
    case _minus_:
        sign = (sy == _plus_) ? 1 : -1;
        insymbol();
        if (sy == intcon) {
            typ = ints;
            midcode_enter(_conload, tmp, ints, inum * sign);
            ret = tmp;
            insymbol();
        }
        else {
            error(8);
        }
        break;
    case intcon:
        typ = ints;
        midcode_enter(_conload, tmp, ints, inum);
        ret = tmp;
        insymbol();
        break;
    case lparent:
        insymbol();
        ret = expression(&typ, tmp);
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
            case variable:
                typ = tab[i].typ;
                midcode_enter(_varload, tmp, i, -1);
                ret = tmp;
                insymbol();
                break;
            case arrays:
                typ = tab[i].typ;
                insymbol();
                if (sy == lbracket) {
                    insymbol();
                }
                else {
                    error(22);
                }
                ret = expression(&typ1, tmp);
                if (typ1 != ints) {
                    error(31);
                }
                midcode_enter(_arrload, ret, i, ret);
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
                    ret = funccall(i, tmp);
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
    *ptyp = typ;
    printf("line %d: ����һ������\n", lcnt);
    return ret;
}


int term(types *ptyp, int tmp)
{
    types typ, typ1;
    int ret, ret1;
    optyp op;

    ret = factor(&typ, tmp);
    while (sy == times || sy == idiv) {
        typ = ints;
        op = (sy == times) ? _times : _idiv;
        insymbol();
        ret1 = factor(&typ1, ret + 1);
        midcode_enter(op, ret, ret, ret1);
    }
    *ptyp = typ;
    printf("line %d: ����һ����\n", lcnt);
    return ret;
}


int expression(types *ptyp, int tmp)
{
    int sign = 1;
    types typ = chars, typ1;
    int ret, ret1;
    optyp op;

    if (sy == _plus_ || sy == _minus_) {
        sign = (sy == _plus_) ? 1 : -1;
        insymbol();
        typ = ints;
    }
    ret = term(&typ1, tmp);
    typ = (typ1 == ints) ? ints : typ;
    if (sign == -1) {
        midcode_enter(_neg, ret, ret, -1);
        //ret++;
    }
    
    while (sy == _plus_ || sy == _minus_) {
        typ = ints;
        op = (sy == _plus_) ? _plus : _minus;
        insymbol();
        ret1 = term(&typ1, ret + 1);
        midcode_enter(op, ret, ret, ret1);
    }
    printf("line %d: ����һ�����ʽ\n", lcnt);
    *ptyp = typ;
    return ret;
}


void ifstatement()
{
    int ret1, ret2;
    types typ1, typ2;
    optyp op;
    int prlabelx = ++labelx;

    insymbol();
    if (sy == lparent) {
        insymbol();
    }
    else {
        error(26);
    }
    ret1 = expression(&typ1, 0);
    if (relationop.count(sy)) {
        op = (optyp)(sy - eql + _eql);
        insymbol();
        ret2 = expression(&typ2, ret1+1);
        if (typ2 != typ1) {
            error(27); //��ϵ������������Ͳ�һ��
        }
        midcode_enter(op, ret1, ret1, ret2);
    }
    else {
        if (typ1 != ints) {
            error(28); //���ʽ��ֵ��Ϊ����
        }
    }
    printf("line %d: ����һ������\n", lcnt);
    if (sy == rparent) {
        insymbol();
    }
    else {
        error(14);
    }

    midcode_enter(_bz, prlabelx, ret1, -1);
    statement();
    midcode_enter(_label, prlabelx, -1, -1);
    printf("line %d: ����һ���������\n", lcnt - 1);
}


void whilestatement()
{
    int ret1, ret2;
    types typ1 = ints, typ2 = ints;
    int prlabelx1 = ++labelx;
    int prlabelx2 = ++labelx;
    optyp op;

    midcode_enter(_label, prlabelx1, -1, -1);
    insymbol();
    if (sy == lparent) {
        insymbol();
    }
    else {
        error(26);
    }
    ret1 = expression(&typ1, 0);
    if (relationop.count(sy)) {
        op = (optyp)(sy - eql + _eql);
        insymbol();
        ret2 = expression(&typ2, ret1 + 1);
        if (typ2 != typ1) {
            error(27);
        }
        midcode_enter(op, ret1, ret1, ret2);
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

    midcode_enter(_bz, prlabelx2, ret1, -1);
    statement();
    midcode_enter(_goto, prlabelx1, -1, -1);
    midcode_enter(_label, prlabelx2, -1, -1);
    printf("line %d: ����һ��ѭ�����\n", lcnt - 1);
}


void onecase(types typ, int tmp, int labelxend)
{
    int sign = 1; 
    int labelx1 = ++labelx;
    
    insymbol();
    if (sy == charcon) {
        midcode_enter(_conload, tmp + 1, chars, inum);
        insymbol();
        if (typ != chars) {
            error(29);
        }
    }
    else {
        if (sy == _plus_ || sy == _minus_) {
            sign = (sy == _plus_) ? 1 : -1;
            insymbol();
        }
        if (sy == intcon) {
            midcode_enter(_conload, tmp + 1, ints, sign * inum);
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
    midcode_enter(_eql, tmp+1, tmp, tmp + 1);
    midcode_enter(_bz, labelx1, tmp+1, -1);
    statement();
    midcode_enter(_goto, labelxend, -1, -1);
    midcode_enter(_label, labelx1, -1, -1);
    printf("line %d: ����һ����������\n", lcnt - 1);
}


void switchstatement()
{
    int ret;
    types typ;
    int labelxend = ++labelx;

    insymbol();
    if (sy == lparent) {
        insymbol();
    }
    else {
        error(26);
    }
    ret = expression(&typ, 0);
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
            onecase(typ, ret, labelxend);
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
    midcode_enter(_label, labelxend, -1, -1);
    printf("line %d: ����һ��������\n", lcnt - 1);
}


void returnstatement()
{
    types typ = ints;
    int ret;
    retflag = true;
    insymbol();
    if (sy == lparent) {
        insymbol();
        ret = expression(&typ, 0);
        if (typ != tab[prt].typ) {
            error(25); //����ֵ���Ͳ�һ��
        }
        midcode_enter(_ret, ret, -1, -1);
        if (sy == rparent) {
            insymbol();
        }
        else {
            error(14);
        }
    }
    else {
        midcode_enter(_ret, -1, -1, -1);
    }
    printf("line %d: ����һ���������\n", lcnt);
}


void assignment(int i)
{
    types typ1, typ2;
    int ret1, ret2;

    insymbol();
    if (tab[i].obj == arrays) {
        if (sy == lbracket) {
            insymbol();
        }
        else {
            error(22);
        }
        ret1 = expression(&typ1, 0);
        if (typ1 != ints) {
            error(31);  //�����±�ֻ��Ϊ����
        }
        //else if(ptyp<0 || ptyp>tab[i].arrcnt-1) {
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
    if (tab[i].obj == arrays) {
        ret2 = expression(&typ2, ret1 + 1);
        if (typ2 != tab[i].typ) {
            error(32); //��ֵ�����������Ͳ�һ��
        }
        midcode_enter(_arrassign, i, ret1, ret2);
    }
    else {
        ret2 = expression(&typ2, 0);
        if (typ2 != tab[i].typ) {
            error(32); //��ֵ�����������Ͳ�һ��
        }
        midcode_enter(_assign, i, ret2, -1);
    }
    printf("line %d: ����һ����ֵ���\n", lcnt);
}


void stdfunccall()
{
    int ret;
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
                    midcode_enter(_push, i, SCANF, -1);
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
        midcode_enter(_call, loc("scanf"), -1, -1);
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
            midcode_enter(_conload, 0, strs, inum);
            midcode_enter(_push, 0, PRINTF, strs);
            insymbol();
            if (sy == comma) {
                insymbol();
                ret = expression(&typ, 0);
                midcode_enter(_push, ret, PRINTF, typ);
            }
        }
        else {
            ret = expression(&typ, 0);
            midcode_enter(_push, ret, PRINTF, typ);
        }
        midcode_enter(_call, loc("printf"), -1, -1);
        printf("line %d: ����һ��д���\n", lcnt);
    }

    if (sy == rparent) {
        insymbol();
    }
    else {
        error(14);
    }
}


int funccall(int i, int tmp)
{
    int lastp = btab[tab[i].ref].lastpar;
    int cpos = i;
    int ret;
    types typ;

    insymbol();
    if (sy == lparent) {
        insymbol();
    }
    else {
        error(26);
    }

    if (sy != rparent) {
        cpos++;
        ret = expression(&typ, tmp);
        if (cpos > lastp) {
            error(34); //ʵ�ι���
        }
        else {
            if (typ != tab[cpos].typ) {
                error(35); //ʵ�����β����Ͳ�һ��
            }
            midcode_enter(_push, ret, -1, -1);
        }

        while (sy == comma) {
            insymbol();
            cpos++;
            ret = expression(&typ, tmp);
            if (cpos > lastp) {
                error(34); //ʵ�ι���
            }
            else {
                if (typ != tab[cpos].typ) {
                    error(35); //ʵ�����β����Ͳ�һ��
                }
                midcode_enter(_push, ret, -1, -1);
            }
            
        }
    }
    printf("line %d: ����һ��ֵ������\n", lcnt);
    
    if (cpos < lastp) {
        error(36); //ʵ�ι���
    }
    if (sy == rparent) {
        insymbol();
    }
    else {
        error(14);
    }
    midcode_enter(_call, i, -1, -1);
    if (tab[i].typ == voids) {
        printf("line %d: ����һ���޷���ֵ�ĺ����������\n", lcnt);
    }
    else {
        midcode_enter(_assign, tmp, RET, -1);
        printf("line %d: ����һ���з���ֵ�ĺ����������\n", lcnt);
    }
    return tmp;
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
                    stdfunccall();
                }
                else {
                    funccall(i, 0);
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
    btab[b].vsize = dx;

    while (statbegsys.count(sy)) {
        statement();//��䴦���������ֺŶ���һ���ַ�
    }
    printf("line %d: ����һ�������\n", lcnt - 1);
    printf("line %d: ����һ���������\n", lcnt - 1);
}


int paralist()
{
    int paracnt = 0;
    types typ;

    insymbol();

    if (sy != rparent) {
        if (sy == intsy || sy == charsy) {
            typ = (sy == intsy) ? ints : chars;
            insymbol();
            if (sy == ident) {
                tab_enter(id, variable, typ, dx);
                midcode_enter(_para, typ, t, -1);
                //dx += (typ == ints) ? 4 : 1;
                dx += 4;
                paracnt++;
                insymbol();
            }
            else {
                error(6); //ȱ�ٲ�������ʶ��
            }
        }
        else{
            error(9); //ȱ�ٲ������ͱ�ʶ��
        }

        while (sy == comma) {
            insymbol();
            if (sy == intsy || sy == charsy) {
                typ = (sy == intsy) ? ints : chars;
                insymbol();
                if (sy == ident) {
                    tab_enter(id, variable, typ, dx);
                    midcode_enter(_para, typ, t, -1);
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
        }

    }

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
    int paracnt;
    
    btab_enter();
    tab_enter(name, function, typ, 0);
    midcode_enter(_func, typ, t, 0);
    prmx = mx;
    tab[t].ref = b;
    prt = t;

    dx = 0;
    paracnt = paralist();
    midcode[prmx].v3 = paracnt;
    btab[b].lastpar = t;
    btab[b].psize = dx;
    
    retflag = false;
    if (sy == lbrace) {
        insymbol();
        compoundstatement();
    }
    else {
        error(15);//ȱ���������������
    }

    if (typ != voids && !retflag) {
        error(39);//ȱ�������
    }

    if (sy == rbrace) {
        insymbol();
    }
    else {
        error(16);//ȱ���������Ҵ�����
    }

    midcode_enter(_ret, -1, -1, -1);
    if (name == "main" && typ == voids && paracnt == 0) {
        printf("line %d: ����һ���������Ķ���\n", lcnt);
        return true;
    }
    else if (typ == voids) {
        printf("line %d: ����һ���޷���ֵ�����Ķ���\n", lcnt - 1);
    }
    else {
        printf("line %d: ����һ���з���ֵ�����Ķ���\n", lcnt - 1);
    }
    return false;
}


void syntax_analysis()
{
    bool funcflag = false;
    bool mainflag = false;
    string name;
    types typ = ints;
    labelx = -1;

    btab_enter();
    tab_enter("scanf", function, voids, 1);
    tab_enter("printf", function, voids, 2);

    dx = 0;
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
                    if (!funcflag) {
                        btab[0].vsize = dx;
                    }
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
                    if (!funcflag) {
                        btab[0].vsize = dx;
                    }
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
    }

    if (!mainflag) {
        error(38);
    }
    if (sy != eofsy) {
        error(37);
    }
}
