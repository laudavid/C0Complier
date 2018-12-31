#ifndef _OPTIMIZATION_H_
#define _OPTIMIZATION_H_
#include <iostream>
#include <cstdio>
#include <string>

using namespace std;


typedef struct {
    //int id;
    int start, end; //������Ŀ�ʼ������λ��
    vector<int> pres, follows;//ǰ�����������顢��̻���������
    int n_pre, n_follow; //ǰ�������顢��̻����������
} block_item;



void code_opt();

#endif // !_OPTIMIZATION_H_