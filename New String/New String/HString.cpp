#include <stdio.h>
#include <stdlib.h>
#include "String.h"
int main()
{
	int count[1000] = { 0 };
	int line_num = 0;//����
	HString text;
	int word_num = 0;//������
	HString word;
	printf_s("Input the word for count:\n");
	StrInit(text);
	StrInit(word);
	GetString(word);
	GetString(text);
	while (text.Length != 0)
	{
		line_num++;
		int pos = 1;
		int last_num = word_num;//����֮ǰ�ĵ�����
		while (pos <= text.Length)
		{//��һ��û�б����ҹ�
			int index = Index_KMP(text, word, pos);//����KMP�㷨�ҵ�word��λ��
			if (index != 0)
			{
				word_num++;
				pos = index + 1;//��һ��������ʼ��
			}
			else break;
		}
		count[line_num] = word_num - last_num;
		GetString(text);
	}
	printf_s("�� %d �� �ı����� %d ����\n", line_num, word_num);
	for (int i = 1; i <= line_num; i++)
		printf_s("�� %d ���� %d ����\n", i, count[i]);
	ShowString(word);
	system("pause");
	return 0;
}