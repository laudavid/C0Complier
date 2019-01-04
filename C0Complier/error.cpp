#include <cstdio>
#include <set>
#include "error.h"
#include "table.h"
#include "lexical_analysis.h"

using namespace std;


symbol s3[] = {
    constsy, intsy, charsy, voidsy
};
set<symbol> procbegsys(s3, s3 + sizeof(s3) / sizeof(s3[0]));

symbol s1[] = {
    ifsy, whilesy, switchsy, returnsy, semicolon, lbrace, ident
};
set<symbol> statbegsys(s1, s1 + sizeof(s1) / sizeof(s1[0]));

symbol s2[] = {
    eql, neq, gtr, geq, lss, leq
};
set<symbol> relationops(s2, s2 + sizeof(s2) / sizeof(s2[0]));

symbol s4[] = {
    ifsy, whilesy, switchsy, returnsy, semicolon, lbrace, rbrace, constsy, intsy, charsy, voidsy
};
set<symbol> statskipsys(s4, s4 + sizeof(s4) / sizeof(s4[0]));


void skip(set<symbol> s)
{
    if (!s.count(sy)) {
        while (!s.count(sy) && sy != eofsy) {
            insymbol();
        }
    }
}

void skip2(set<symbol> set1, set<symbol> set2)
{
    if (!set1.count(sy) && !set2.count(sy)) {
        while (!set1.count(sy) && !set2.count(sy) && sy != eofsy) {
            insymbol();
        }
    }
}



bool noerror = true;

void error(int n)
{
    noerror = false;
    //printf("%s:��%d��, ��%d��: ����: ", src_file_name.c_str(), lcnt, chcnt);
    printf("%s:��%d��: ����: ", src_file_name.c_str(), lcnt);
    switch (n) {
    case 1:
        printf("���Ϸ����ַ�����\'%c\'\n", ch);
        break;
    case 2:
        puts("ȱ�ٵ������ս��");
        break;
    case 3:
        puts("ȱ��˫�����ս��");
        break;
    case 4:
        puts("���Ϸ��ķ���'!'");
        break;
    case 5:
        printf("���Ϸ��ķ���'%c'\n", ch);
        break;

    case 6:
        puts("ȱ�ٱ�ʶ��");
        break;
    case 7:
        puts("ȱ�ٸ�ֵ����");
        break;
    case 8:
        puts("ȱ���������ַ�����");
        break;
    case 9:
        puts("ȱ�����ͱ�ʶ��int��char");
        break;
    case 10:
        puts("����Ԫ�ظ������Ϸ�");
        break;
    case 11:
        puts("û��ָ������Ԫ�ظ���");
        break;
    case 12:
        puts("ȱ����������");
        break;
    case 13:
        puts("ȱ�ٷֺ�");
        break;
    case 14:
        puts("ȱ����С����");
        break;
    case 15:
        puts("ȱ���������");
        break;
    case 16:
        puts("ȱ���Ҵ�����");
        break;
    case 17:
        puts("������ʶ��������Ϊ��俪ʼ����");
        break;
    case 18:
        puts("δ����ı�ʶ��");
        break;
    case 19:
        puts("��ʶ�������ض���");
        break;
    case 20:
        puts("���Ϸ������");
        break;
    case 21:
        puts("ȱ��ð��");
        break;
    case 22:
        puts("ȱ����������");
        break;
    case 23:
        puts("�����޷���ֵ");
        break;
    case 24:
        puts("���Ϸ��ı��ʽ�����ӣ�");
        break;
    case 25:
        puts("����ֵ�����뺯�����岻һ��");
        break;
    case 26:
        puts("ȱ����С����");
        break;
    //case 27:
    //    puts("��ϵ�����������ʽ���Ͳ�һ��");
    //    break;
    case 28:
        puts("�������ʽ�����Ͳ�Ϊ����");
        break;
    case 29:
        puts("case���ĳ���������switch���ʽ�����Ͳ�һ��");
        break;
    case 30:
        puts("ȱ��case���");
        break;
    case 31:
        puts("�����±�������Ϊ����");
        break;
    case 32:
        puts("��ֵ����������Ͳ�һ��");
        break;
    case 33:
        puts("scanf�����б�ʶ�����Ͳ�Ϊ����");
        break;
    case 34:
        puts("ʵ�θ�������");
        break;
    case 35:
        puts("ʵ�����β����Ͳ�һ��");
        break;
    case 36:
        puts("ʵ�θ�������");
        break;
    case 37:
        puts("main�������������﷨�ɷ�");
        break;
    case 38:
        puts("����ȱ��main����");
        break;
    case 39:
        puts("����ȱ�ٷ������");
        break;
    case 40:
        puts("case���ĳ��������ظ�");
        break;
    case 41:
        puts("�����±�Խ��");
        break;
    case 42:
        puts("����������ֵ�λ�ò���");
        break;
    case 43:
        puts("����������ֵ�λ�ò���");
        break;
    case 44:
        puts("void���ͺ����������");
        break;
    case 45:
        puts("�޷�ʶ��ĳ���ʼ����");
        break;
    case 46:
        puts("��ϵ����������ʽ���Ͳ�Ϊ����");
        break;
    case 47:
        puts("��ϵ������Ҳ���ʽ���Ͳ�Ϊ����");
        break;
    case 48:
        puts("main�������岻�淶");
        break;
    case 49:
        puts("ȱ�ٶ��ŷָ���");
        break;
    default:
        puts("��������");
        break;
    }
}
