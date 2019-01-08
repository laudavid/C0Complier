#ifndef _TABLE_H_
#define _TABLE_H_
#include <string>
#include <map>
#include <set>
#include <vector>
#include "optimization.h"

using namespace std;

typedef enum {
    intcon, charcon, stringcon, //����  �ַ�  �ַ���
    plus_sy, minus_sy, times_sy, idiv_sy, //+  -  *  /
    eql, neq, gtr, geq, lss, leq, //==  !=  >  >=  <  <=
    lparent, rparent, lbracket, rbracket, lbrace, rbrace, //( ) [ ] { } 
    comma, semicolon, colon, becomes, //, ; : =  
    ident, //mainsy, scanfsy, printfsy,
    constsy, returnsy, intsy, charsy, voidsy,
    ifsy, switchsy, casesy, defaultsy, whilesy, eofsy
} symbol;

typedef enum {
    constant, variable, arrays, function
} objtyp;


typedef enum {
    ints, chars, voids, strs
} datatyp;

typedef struct {//���ű�Ԫ��
    string name;
    int link; //ָ��ͬһ��������һ����ʶ����tab���е�λ��
    objtyp obj; // ��ʶ�����ࣺ���������������������������
    datatyp typ; // ��ʶ�����ͣ�int�͡�char�͡�void�͵�
    int lev; // ��ʶ�����ڵľ�̬��Σ�ȫ�ֳ�������������Ϊ0���ֲ���������������0��Ϊ��Ӧ������btab���ָ��
    int ref; //��������ָ������btab���е�ָ��ֵ  
    int arrcnt; //����Ԫ�ظ���
    int adr; // �������βΣ���ȫ�ֱ�����������ջs�е���Ե�ַ������������ӦĿ��������ڵ�ַ�����ͳ�������Ӧ��ֵ��
    int pos;
} tabitem;

typedef struct {
    int last, lastpar, psize, vsize;
    int start_blk, end_blk;
    int n_tmpvar, n_localvar;
    bool is_leaf;
    vector<vector<bool>> conflict_graph;
    vector<reg> regs;
    /*
      lastָ�������һ����ʶ����tab���е�λ�ã�
      lastparָ���������һ��������tab���е�λ�ã�
      psizeΪ������������Ϣ����ռ�Ĵ洢��Ԫ����
      vsize�ֲ�������������������Ϣ����ռ�Ĵ洢��Ԫ������
    */
} btabitem;

extern map<string, symbol> ksy; //�����ֱ�
extern map<char, symbol> sps; //�����ַ���

extern vector<tabitem> tab; //���ű�
extern int t;

extern vector<btabitem> btab; //�ֳ����
extern int b;

extern vector<string> stab; //�ַ���������
extern int sx; //�ַ�������������


void tabs_init();
void tab_enter(string name, objtyp obj, datatyp typ, int adr);
void btab_enter();
int loc(string name);


#endif // !_TABLE_H_
