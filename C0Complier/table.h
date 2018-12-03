#ifndef _TABLE_H_
#define _TABLE_H_
#include <string>
#include <map>
#include <set>
#include <vector>

using namespace std;

typedef enum symbol {
    intcon, charcon, stringcon, //����  �ַ�  �ַ���
    _plus_, _minus_, times, idiv, //+  -  *  /
    eql, neq, gtr, geq, lss, leq, //==  !=  >  >=  <  <=
    lparent, rparent, lbracket, rbracket, lbrace, rbrace, //( ) [ ] { } 
    comma, semicolon, colon, becomes, //, ; : =  
    ident, //mainsy, scanfsy, printfsy,
    constsy, returnsy, intsy, charsy, voidsy,
    ifsy, switchsy, casesy, defaultsy, whilesy, eofsy
} symbol;

typedef enum objtyp {
    constant, variable, arrays, function
} objtyp;


typedef enum types {
    ints, chars, voids, strs
} types;

typedef struct tabitem {//���ű�Ԫ��
    string name;
    int link; //ָ��ͬһ��������һ����ʶ����tab���е�λ��
    objtyp obj; // ��ʶ�����ࣺ���������������������������
    types typ; // ��ʶ�����ͣ�int�͡�char�͡�void�͵�
    int lev; // ��ʶ�����ڵľ�̬��Σ�ȫ�ֳ�������������Ϊ0���ֲ���������������1��Ϊ��Ӧ������btab���ָ��
    int ref; //��������ָ������btab���е�ָ��ֵ  
    int arrcnt; //����Ԫ�ظ���
    int adr; // �������βΣ���ȫ�ֱ�����������ջs�е���Ե�ַ������������ӦĿ��������ڵ�ַ�����ͳ�������Ӧ��ֵ��
} tabitem;

typedef struct btabitem {
    int last, lastpar, psize, vsize;
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

extern set<symbol> statbegsys;
extern set<symbol> relationop;

void tabs_init();
void tab_enter(string name, objtyp obj, types typ, int adr);
void btab_enter();
int loc(string name);


#endif // !_TABLE_H_
