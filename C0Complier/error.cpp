#include <cstdio>
#include "error.h"
#include "lexical_analysis.h"

using namespace std;

bool noerror = true;

void error(int n)
{
    noerror = false;
    printf("%s:%d:%d: error: ", src_file_name.c_str(), lcnt, chcnt);
    switch (n) {
    case 1:
        printf("���Ϸ����ַ�����'%c'\n", ch);
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
        printf("�޷�ʶ��ķ���'%c'\n", ch);
        nextch();
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
        puts("����Ԫ�ظ���������0");
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
        puts("��Ӧ���ֵĳ�����ʶ��");
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
        puts("����ֵ�����뺯����һ��");
        break;
    case 26:
        puts("ȱ����С����");
        break;
    case 27:
        puts("��ϵ������������Ͳ�һ��");
        break;
    case 28:
        puts("���ʽ��ֵ��Ϊ����");
        break;
    case 29:
        puts("case���ĳ���������switch���ʽ��ֵ��һ��");
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
        puts("��ʶ�����Ͳ�Ϊ����");
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
        puts("����ṹ����");
        break;
    case 38:
        puts("û�кϷ���main����");
        break;
    case 39:
        puts("����ȱ�ٷ������");
        break;
    case 40:
        puts("case���ĳ��������ظ�");
        break;
    default:
        puts("��������");
        break;
    }
}