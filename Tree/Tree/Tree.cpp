#include <stdio.h>
#include <stdlib.h>
void eatline()
{
	char ch = getchar();
	while (ch != '\n')
		ch = getchar();
}
typedef struct tree{
	char data;
	struct tree * left;
	struct tree * right;
}* Tree;

//������
int CreateTree(Tree &T)
{
	char ch = getchar();
	// eatline();
	if (ch!=' ')
	{
		T = (Tree)malloc(sizeof(struct tree));
		T->data = ch;
		T->left = NULL;
		T->right = NULL;
		CreateTree(T->left);
		CreateTree(T->right);
		return 1;
	}
	else {
		T = NULL;
		return 0;
	}
}
//ǰ�����
int PreTraveTree(Tree T)
{
	if (T!=NULL)
	{
		printf_s("%c", T->data);
		PreTraveTree(T->left);
		PreTraveTree(T->right);
		return 1;
	}
	else return 0;
}
//�������
int InTraveTree(Tree T)
{
	if (T != NULL)
	{
		PreTraveTree(T->left);
		printf_s("%c", T->data);
		PreTraveTree(T->right);
		return 1;
	}
	else return 0;
}
//β�����
int PastTraveTree(Tree T)
{
	if (T != NULL)
	{
		PreTraveTree(T->left);
		PreTraveTree(T->right);
		printf_s("%c", T->data);
		return 1;
	}
	else return 0;
}
//�����������
int Deep(Tree T,int deep)
{
	if (T != NULL)
	{
		deep++;
		int d1 = Deep(T->left, deep);
		int d2 = Deep(T->right, deep);
		return d1 > d2 ? d1 : d2;
	}
	else return deep;
}
//�������õ�ĳ��Ԫ��,�������ĸ��ڵ�
Tree Find(Tree T, int data)
{
	if (T != NULL)
	{
		if ((T->left != NULL||T->right!=NULL)
			&&(T->left->data == data||T->right->data==data))
		{
			return T;
		}
		Find(T->left,data);
		Find(T->right, data);
	}
	else return NULL;
}
int main()
{
	Tree T = NULL;	CreateTree(T);
	printf_s("ǰ��");
	PreTraveTree(T);
	printf_s("\n����");
	InTraveTree(T);
	printf_s("\n����: ");
	PastTraveTree(T);
	int d = Deep(T, 0);
	printf_s("\n deep of this tree is %d", d);
	eatline();
	puts("find code father:");
	char data = getchar();
	Tree parents = Find(T,data);
	if(parents!=NULL)
		printf_s("\n%c's parents is %c",data, parents->data);
	else printf_s("\ncan't find anything");
	system("pause");
	return 0;
}