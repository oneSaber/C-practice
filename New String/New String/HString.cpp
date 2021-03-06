#include <stdio.h>
#include <stdlib.h>
#include "String.h"

bool ischar(char ch)
{
	bool result = (ch >= 'a'&&ch <= 'z') || (ch >= 'A'&&ch <= 'Z');
	printf_s("%c is %d ", ch, result);
	return result;
}
bool IsWord(char head,char tail)
{
	int result = !ischar(head) && !ischar(tail);
	printf_s("\n");
	return result;
}

int main()
{
	int count[1000] = { 0 };
	int line_num = 0;//行数
	HString text;
	int word_num = 0;//单词数
	HString word;
	printf_s("Input the word for count:\n");
	StrInit(text);
	StrInit(word);
	GetString(word);
	printf_s("input the text:\n");
	GetString(text);
	while (text.Length != 0)
	{
		line_num++;
		int pos = 1;
		int last_num = word_num;//该行之前的单词数
		while (pos <= text.Length)
		{//这一行没有被查找过
			int index = Index_KMP(text, word, pos);//利用KMP算法找到word的位置
			if (index != 0 && IsWord(text.Elem[index - 1], text.Elem[index + word.Length]))
			{
				word_num++;
				pos = index + 1;//下一个查找起始点
			}
			else pos = pos + 1;
		}
		count[line_num] = word_num - last_num;
		GetString(text);
	}
	printf_s("在 %d 行 文本中有 %d 单词\n", line_num, word_num);
	for (int i = 1; i <= line_num; i++)
		printf_s("第 %d 行有 %d 单词\n", i, count[i]);
	//ShowString(word);
	system("pause");
	return 0;
}