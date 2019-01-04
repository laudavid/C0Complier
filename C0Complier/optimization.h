#ifndef _OPTIMIZATION_H_
#define _OPTIMIZATION_H_
#include <iostream>
#include <cstdio>
#include <string>

using namespace std;


typedef struct {
    //int id;
    int start, end; //������Ŀ�ʼ���������м����λ��
    vector<int> pres, follows;//ǰ�����������顢��̻���������
    int n_pre, n_follow; //ǰ�������顢��̻����������
    vector<bool> def1, use1, in1, out1;
    vector<bool> def2, use2, in2, out2;
} block_item;

typedef struct {
    int index;
    int kind;
    int num;
} reg;

extern vector<block_item> block_tab;
extern int block_index;

void code_opt();

#endif // !_OPTIMIZATION_H_