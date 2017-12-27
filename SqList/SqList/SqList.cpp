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
//ɾ�����еĵ�I��Ԫ��
bool ListDelete(Sqlist &L, int i, int &e)
{
	if (i<1 || i>L.length)
		return false;//�������Ϸ�
	int* p = &(L.elem[i - 1]);
	e = *p;
	int* q = L.elem + L.length - 1;
	for (++p; p <= q; ++p)
		*(p - 1) = *p;
	--L.length;
	return true;
}
//e�Ƿ������Ա�L�У��ڵĻ����ر��е�λ�ã����ڷ���false
int LocateElem(Sqlist L, int e)
{
	int find = false;
	for (int i = 0; i < L.length; i++)
	{
		if (L.elem[i] == e)
		{
			find = i+1;
			break;
		}
	}
	return find;
}
//���������Ա�ϲ�
void MergeList(Sqlist La, Sqlist Lb, Sqlist &Lc)
{
	Lc.length= La.length + Lb.length;
	Lc.listsize = LIST_INIT_SIZE;
	Lc.elem = (int *)malloc(sizeof(int)*Lc.listsize);
	int a = 0,b = 0;
	int i = 0;
	int insertNum;
	while (a < La.length&&b < Lb.length)
	{
		if (La.elem[a] > Lb.elem[b])
			insertNum = Lb.elem[b++];
		else insertNum = La.elem[a++];
		if (!LocateElem(Lc, insertNum))
			Lc.elem[i++] = insertNum;
	}
	while (a < La.length)
	{
		insertNum = La.elem[a++];
		if (!LocateElem(Lc, insertNum))
			Lc.elem[i++] = insertNum;
	}
	while (b < Lb.length)
	{
		insertNum = Lb.elem[b++];
		if (!LocateElem(Lc, insertNum))
			Lc.elem[i++] = insertNum;
	}
	Lc.length = i;
}
int main()
{
	Sqlist La;
	InitList(La);
	int i = 1;
	int e;
	puts("���� La��q ��ʾ����):");
	while (scanf_s("%d", &e))
	{
		ListInsert(La, i, e);
		i++;
	}
	getchar();
	char ch = 'A';
	while (ch!='Q')
	{
		printf_s("la:");
		for (int i = 0; i < La.length; i++)
			printf_s("%d ", La.elem[i]);
		int choose;
		printf_s("\n1.����ĳ��ֵ��λ��\n");
		printf_s("2.ɾ��ĳ��ֵ\n");
		printf_s("3.��ĳ��λ�ò���:\n");
		printf_s("4.��La��Lb�ϲ�:\n");
		printf_s("����ѡ��:");
		scanf_s("%d", &choose);
		getchar();
		switch (choose)
		{
		case 1: 
		{
			int searchVal;
			printf_s("������ҵ�ֵ��");
			scanf_s("%d", &searchVal);
			getchar();
			int pos = LocateElem(La, searchVal);
			if (pos)
				printf_s("%d �ڵ� %d λ��\n", searchVal, pos);
			else printf_s("can't find\n");
		}break;
		case 2:
		{
			int deletePos;
			printf_s("������Ҫɾ����i��Ԫ��:");
			scanf_s("%d", &deletePos);
			getchar();
			int e;
			if (ListDelete(La, deletePos,e))
				printf_s("%d ɾ���ɹ�\n",e);
			else printf_s("ɾ��ʧ��\n");
		}break;
		case 3: 
		{
			int insertPos;
			int insertVal;
			printf_s("��������λ�ú�ֵ:");
			scanf_s("%d %d", &insertPos,&insertVal);
			getchar();
			if (ListInsert(La, insertPos, insertVal))
				printf_s("����ɹ�\n");
			else printf_s("����ʧ��\n");
		}break;
		case 4:
		{
			Sqlist Lb, Lc;
			InitList(Lb);
			InitList(Lc);
			i = 1;
			puts("���� Lb��q ��ʾ����):");
			while (scanf_s("%d", &e))
			{
				ListInsert(Lb, i, e);
				i++;
			}
			getchar();
			MergeList(La, Lb, Lc);
			printf_s("lc:");
			for (int i = 0; i < Lc.length; i++)
				printf_s("%d ", Lc.elem[i]);
			puts("\n");
			getchar();
		}break;
		default:printf_s("�������\n");
			break;
		}
		choose = -1;
		printf_s("Q �˳�����:\n");
		ch = getchar();
	}
	system("pause");
	return 0;
}