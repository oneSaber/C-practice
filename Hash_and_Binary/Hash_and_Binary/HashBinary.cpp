#include<stdio.h>
#include<stdlib.h>
#include<math.h>
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
		L.length = LIST_INIT_SIZE;
		L.listsize = LIST_INIT_SIZE;
		int i;
		for (i = 0; i < L.length; i++)
			L.elem[i] = INT_MIN;
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
int BinarySearch(int Array[], int left, int right,int searchKey)
{
	if (left > right)
		return -1;
	else {
		int middle = (left + right) / 2;
		if (Array[middle] == searchKey)
			return middle;
		else {
			if (Array[middle] < searchKey)
				return BinarySearch(Array, middle + 1, right, searchKey);
			else return BinarySearch(Array, left, middle - 1, searchKey);
		}
	}
}
//�ҵ���������µ��������
int findPrime(int Maxlen)
{
	int i ;
	for (i = Maxlen - 1; i > 2; i--)
	{
		int flag = 1;
		for (int j = 2; j < sqrt(i) + 1; j++)
		{
			if (i%j == 0)
			{
				flag = 0;
				break;
			}
		}
		if (flag)
			return i;
	}
}
//ÿһ��Ԫ�صĹ�ϣֵ
int Hash(int key,int prime)
{
	return key % prime;
}
void HashInsert(Sqlist la,int prime)
{
	int hash;
	int e;
	printf_s("����lb����ɢ��(q����):");
	while (scanf_s("%d", &e))
	{
		hash = Hash(e,prime);
		//��λ���Ѿ���ռ�ã�������hash
		while (la.elem[hash] != INT_MIN)
			hash = Hash(hash+1, prime);
		la.elem[hash] = e;
	}
	getchar();
}
void HashFind(Sqlist la,int searchKey,int prime)
{
	int hash = Hash(searchKey, prime);
	int findtime = 0;
	while (searchKey != la.elem[hash]&&findtime <= la.length)
	{
		findtime++;
		hash = Hash(hash + 1, prime);
	}
	if (findtime >= la.length)
		printf_s("can't find");
	else printf_s("%d��λ����%d\n", searchKey,hash);
}
int main()
{
	printf_s("1.���ֲ���\n");
	printf_s("2.ɢ��\n");
	printf_s("����ģʽ��");
	int mode;
	scanf_s("%d", &mode);
	getchar();
	switch (mode)
	{
	case 1: {
		Sqlist la;
		InitList(la);
		int i = 1;
		int e;
		i = 1;
		puts("���� La��q ��ʾ����):");
		while (scanf_s("%d", &e))
		{
			ListInsert(la, i, e);
			i++;
		}
		la.length = i-1;
		getchar();
		printf_s("���ֲ���,������ҵ�Ԫ�أ�");
		int searchKey;
		while (scanf_s("%d", &searchKey))
		{//���ص���searchkey��λ��
			int pos = BinarySearch(la.elem, 0, la.length - 1, searchKey) + 1;
			if (pos)
				printf_s("%d ��λ���� %d\n",searchKey, pos);
			else printf_s("can't find\n");
			getchar();
			printf_s("��������(q �˳�)��");
		}

	}break;
	case 2: {
		Sqlist lb;
		InitList(lb);
		int prime = findPrime(LIST_INIT_SIZE);
		HashInsert(lb, prime);
		int hashkey;
		printf_s("������Ҫ���ҵ�ֵ(q �˳�)��");
		while (scanf_s("%d", &hashkey))
		{
			HashFind(lb, hashkey, prime);
			getchar();
			printf_s("������һ����������q�˳�����");
		}
	}break;
	default:
		break;
	}
	system("pause");
	return 0;
}