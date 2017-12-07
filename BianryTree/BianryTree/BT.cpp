#include<stdio.h>
#include<stdlib.h>

struct Node {
	int key;
	int data;
	struct Node*left, *right;
};

typedef struct Node NODE;
typedef struct Node* Tree;

//key�Ƕ����������ı�׼
int initTree(Tree &t)
{
	scanf_s("%d%d", &t->key, &t->data);
	t->left = NULL;
	t->right = NULL;
	return 1;
}

//ͨ��dataѰ��key��
int Find_by_data(int search_data, Tree T)
{
	if (T == NULL)
		return 0;
	if (T->key == search_data)
		return T->data;
	else {
		return Find_by_data(search_data, T->left);
		return Find_by_data(search_data, T->right);
	}
}

int InsertNode(Tree &T, int key)
{
	if(T == NULL)
		T = (Tree)malloc(sizeof(NODE));
	T->key = key;
	T->left = NULL;
	T->right = NULL;
	printf_s("input data");
	return scanf_s("%d", &T->data);
}
//ͨ��key����data,û�в��ҵ��Ļ�����ýڵ�
int Find_by_key(int search_key, Tree &T)
{
	if (T == NULL)
		return 0;
	if (T->key == search_key)
		return T->data;
	else
	{
		if (T->key > search_key)
		{
			if (T->left != NULL)
				return Find_by_key(search_key, T->left);
			else
			{
				if(InsertNode(T->left, search_key))
					return 2;//��ʾû���ҵ������ɹ�����
				else return -1;//��ʾδ�ɹ�������û�гɹ�����
			}
		}
		else {
			if (T->right != NULL)
				return Find_by_key(search_key, T->right);
			else
			{
				if(InsertNode(T->right, search_key))
					return 2;
				else return -1;
			}
		}
	}
}
//����һ����
int CreateTree(Tree &T)
{
	//�����ĸ���ʼ��
	initTree(T);
	int key,data;
	while (scanf_s("%d", &key))
	{
		switch (Find_by_key(key,T))
		{
		case 2:continue;
		case -1:printf_s("����ʧ��");
		default:
			printf_s("�Դ���");
		}
	}
	return 1;
}
void showTree(Tree T)
{
	if (T == NULL)
		return;
	else {
		
		showTree(T->left);
		printf_s("%d : %d \n", T->key, T->data);
		showTree(T->right);
	}
}
int main()
{
	Tree T = NULL;
	T = (Tree)malloc(sizeof(NODE));
	CreateTree(T);
	showTree(T);
	int search_key;
	system("pause");
	return 0;
}