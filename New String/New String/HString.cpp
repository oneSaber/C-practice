#include <stdio.h>
#include <stdlib.h>
#define MAXLEN 1000
typedef struct 
{
	char *Elem;
	int Length;
}HString;

//���һ��
void Eatline()
{
	char ch = getchar();
	while (ch != '\n')
		ch = getchar();
}
//��ʼ����
int StrInit(HString &S)
{
	S.Elem = (char *)malloc(sizeof(char)*MAXLEN);
	S.Length = 0; 
	if (S.Elem != NULL)
		return 1;
	else return 0;
}
//���봮���س���������
int GetString(HString &S)
{
	if (S.Elem == NULL)
		StrInit(S);
	int i = 1;
	char ch = getchar();
	while (ch!='\n')
	{
		S.Elem[i] = ch;
		ch = getchar();
		i++;
	}
	S.Length = i - 1;
	return 1;
}
//���ĳ���
int Len(HString S)
{
	return S.Length;
}
//�����
int ShowString(HString S)
{
	for (int i = 1; i <= S.Length; i++)
		printf_s("%c", S.Elem[i]);
	printf_s("\n");
	return 1;

}
//��S2��ֵ����S1
int StrAssign(HString &s1, HString s2)
{
	for (int i = 0; i < s1.Length; i++)
		s1.Elem[i+1] = 0;
	s1.Length = s2.Length;
	for (int i = 0; i < s2.Length; i++)
		s1.Elem[i + 1] = s2.Elem[i + 1];
	return 1;
}
//��S2ƴ����S1����
int StrConcat(HString &s1, HString s2)
{
	int start = s1.Length + 1;
	s1.Length += s2.Length;
	for (int i = start; i <= s1.Length;i++)
		s1.Elem[i] = s2.Elem[i - start + 1];
	return 1;
}
//���شӵ�i���ַ���ʼ����ΪLen���Ӵ�
int SubStr(HString S,HString &t ,int i, int len)
{
	if (i > S.Length)
		return 0;
	else {
		if (i + len - 1 < S.Length)
		{
			for (int k = i; k < i + len; k++)
				t.Elem[k - i + 1] = S.Elem[k];
			t.Length = len;
			return 1;
		}
		else {
			for (int k = i; k <= S.Length; k++)
				t.Elem[k - i + 1] = S.Elem[k];
			t.Length = S.Length - i + 1;
			return 2;
		}
	}
}
//�Ƚ��������Ƿ����
int StrCmp(HString S1, HString S2)
{
	if (S1.Length != S2.Length)
		return 0;
	else {
		int flag = 1;
		for (int i = 1; i <= S1.Length; i++)
		{
			if (S1.Elem[i] != S2.Elem[i])
			{
				flag = 0;
				break;
			}
		}
		return flag;
	}
}
//����T���뵽��S��i֮��
int StrInsert(HString &s, int i, HString t)
{
	if (s.Length + t.Length < MAXLEN)
	{
		for (int k = s.Length; k > i; k--)
		{
			s.Elem[k + t.Length] = s.Elem[k];
		}
		for (int k = i + 1; k <= t.Length+i; k++)
		{
			s.Elem[k] = t.Elem[k - i];
		}
		s.Length += t.Length;
		return 1;
	}
	else return 0;
}
//ɾ����
int StrDelete(HString &S, int i, int len)
{
	if (i + len-1 < S.Length)
	{
		S.Length -= len;
		for (int k = i; k < S.Length; k++)
			S.Elem[k] = S.Elem[k+len];
		return 1;
	}
	else {	
		for (int k = i; k <= S.Length; k++)
			S.Elem[k] = 0;
		S.Length -= (S.Length - i) + 1;
		return 2;
	}
}
//�õ�������t��ͬ���Ӵ��ĵ�һ��λ��

int main()
{
	printf_s("hello world!\n");
	HString S,T;
	StrInit(S);
	StrInit(T);
	GetString(S);
	//GetString(T);
	StrDelete(S, 5, 6);
	ShowString(S);
	system("pause");
	return 0;
}