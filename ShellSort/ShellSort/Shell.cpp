#include<stdio.h>
#include<stdlib.h>
#define LIST_INIT_SIZE 100 //���Ա����ռ�ĳ�ʼ����
#define LISTINCREMENT 10   //���Ա����ռ������

typedef struct {
	int *elem;
	int length;
	int listsize;
}Sqlist;
bool InitList(Sqlist &L)
{
	L.elem = (int *)malloc(sizeof(int)*LIST_INIT_SIZE);
	if (L.elem)
	{
		L.length = 0;
		L.listsize = LIST_INIT_SIZE;
		return true;
	}
	else return false;
}
int Len(Sqlist L)
{
	return L.length;
}
//��e�嵽���Ա��i��λ����
bool ListInsert(Sqlist &L, int i, int e)
{
	if (i<1 || i>Len(L) + 1)
		return false;
	if (L.length >= L.listsize)
	{
		int *newbase = (int *)realloc(L.elem, (L.listsize + LISTINCREMENT) * sizeof(int));
		if (!newbase)
			return false;
		L.elem = newbase;
		L.listsize += LISTINCREMENT;
	}
	int *q = &(L.elem[i - 1]);
	for (int *p = &(L.elem[L.length - 1]); p >= q; --p)
		*(p + 1) = *p;
	*q = e;
	++L.length;
	return true;
}
void swap(int &a, int &b)
{
	int temp = a;
	a = b;
	b = temp;
}

void Shell(int a[], int length)
{
	int i, j, grp;
	for (grp = length / 2; grp > 0; grp = grp / 2)
	{//���������
		for (i = 0; i < grp; i++)
		{//��ÿһ����������
			for (j = i + grp; j < length; j += grp)
			{
				if (a[j] < a[j - grp])
				{
					int temp = a[j];
					int k = j - grp;
					while (k >= 0 && a[k] > temp)
					{
						a[k + grp] = a[k];
						k -= grp;
					}
					a[k+grp] = temp;
				}
			}
		}
	}

}
//ֱ�Ӳ�������
void InsertSort(int Array[],int length)
{
	int compare_time = 0;
	int change_time = 0;
	int i, j, k;
	for (i = 1; i < length; i++)
	{
		for (j = i - 1; j >= 0; j--)
		{
			compare_time++;
			if (Array[j] < Array[i])
				break;
		}
		if (j != i - 1)
		{
			int temp = Array[i];
			for (k = i - 1; k > j; k--)
			{
				change_time++;
				Array[k + 1] = Array[k];
			}
			Array[k + 1] = temp;
		}
	}
	//printf_s("��β���������Ҫ�Ƚ�%d�Σ��Լ�����%d��", compare_time, change_time);
}
int main()
{
	Sqlist La;
	int i = 1;
	int e;
	InitList(La);
	puts("���� La��q ��ʾ����):");
	while (scanf_s("%d", &e))
	{
		ListInsert(La, i, e);
		i++;
	}
	getchar();
	printf_s("La: ϣ��������:");
	Shell(La.elem, La.length);
	for (int i = 0; i < La.length; i++)
		printf_s("%d ", La.elem[i]);
	Sqlist Lb;
	InitList(Lb);
	int j = 1;
	int f;
	puts("\n���� Lb��q ��ʾ����):");
	while (scanf_s("%d", &f))
	{
		ListInsert(Lb, j, f);
		j++;
	}
	printf_s("lb,ֱ�Ӳ���������:");
	InsertSort(Lb.elem, Lb.length);
	for (int i = 0; i < Lb.length; i++)
		printf_s("%d ", Lb.elem[i]);
	system("pause");
	return 0;
}