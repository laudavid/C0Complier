#include <string>
#include <map>
#include <vector>
#include <set>
#include "table.h"
#include "error.h"

using namespace std;

map<string, symbol> ksy; //�����ֱ�
map<char, symbol> sps; //�����ַ���

vector<tabitem> tab; //���ű�
int t;
vector<btabitem> btab; //�ֳ����
int b;
vector<string> stab; //�ַ���������
int sx; //�ַ�������������


void tabs_init()
{
    t = -1;
    b = -1;
    sx = -1;

    ++t;
    tabitem item;
    item.name = "";
    item.link = 0;
    item.obj = function;
    item.typ = voids;
    item.adr = 0;
    item.ref = 0;
    item.lev = 0;
    item.arrcnt = 0;
    tab.push_back(item);

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
    //ksy["main"] = mainsy;
    //ksy["scanf"] = scanfsy;
    //ksy["printf"] = printfsy;

    sps['+'] = plus_sy;
    sps['-'] = minus_sy;
    sps['*'] = times_sy;
    sps['/'] = idiv_sy;
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

int loc(string name)
{
    int i;

    tab[0].name = name;
    i = btab[b].last;
    while (tab[i].name != name) {
        i = tab[i].link;
    }
    if (i != 0) {
        return i;
    }
    i = btab[0].last;
    while (tab[i].name != name) {
        i = tab[i].link;
    }
    return i;
}


void tab_enter(string name, objtyp obj, datatyp typ, int adr)
{
    int i, prb;

    prb = (obj == function) ? 0 : b;
    tab[0].name = name;
    i = btab[prb].last;
    while (tab[i].name != name) {
        i = tab[i].link;
    }

    if (i == 0) {
        ++t;
        tabitem item;
        item.name = name;
        item.obj = obj;
        item.typ = typ;
        item.adr = adr;
        item.ref = 0;
        item.arrcnt = 0;
        item.lev = prb;
        item.link = btab[prb].last;
        btab[prb].last = t;
        tab.push_back(item);
    }
    else {
        error(19); //��ʶ�������ض���
    }
}

void btab_enter()
{
    ++b;
    btabitem item;
    item.last = 0;
    item.lastpar = 0;
    item.psize = 0;
    item.vsize = 0;
    btab.push_back(item);
}
