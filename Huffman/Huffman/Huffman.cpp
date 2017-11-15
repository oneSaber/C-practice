#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLEN 1000
typedef struct  {
	int weight;//Ȩֵ
	int parent;//���ڵ�
	int lchild;//���ӽڵ�
	int rchild;//���ӽڵ�
	char value;//ֵ
}HuffmanNode;
typedef struct {
	int Bit[MAXLEN];
	int start;
}Code;

int HuffmanTree(HuffmanNode Huffman[MAXLEN], int n)
{
	//��ʼ������Ҷ��
	for (int i = 0; i < 2*n; i++)
	{
		Huffman[i].parent = -1;
		Huffman[i].lchild = -1;
		Huffman[i].rchild = -1;
	}
	//�õ�Ҷ�ӵ�Ȩֵ����ĸ
	for (int i = 0; i < n; i++)
	{
		scanf_s("%c", &Huffman[i].value);
		scanf_s("%d", &Huffman[i].weight);
		getchar();
	}
	int m1, m2;
	int x1, x2;
	int i;
	for (i = 0; i < n-1; i++)
	{
		m1 = m2 = INT_MAX;
		x1 = x2 = 0;
		//�ҵ���ǰȨֵ��С�������ڵ�
		for (int j = 0; j < n + i; j++)
		{
			if (Huffman[j].parent==-1&&Huffman[j].weight<m1)
			{
				m2 = m1;
				x2 = x1;
				m1 = Huffman[j].weight;
				x1 = j;
			}
			else if (Huffman[j].parent == -1 && Huffman[j].weight < m2)
			{
				m2 = Huffman[j].weight;
				x2 = j;
			}
		}
		Huffman[n + i].weight = Huffman[x1].weight + Huffman[x2].weight;
		Huffman[x1].parent = n + i;
		Huffman[x2].parent = n + i;
		Huffman[n + i].lchild = x1;
		Huffman[n + i].rchild = x2;
		Huffman[n + i].parent = -1;
		Huffman[n + i].value = -1;
		//printf("x1.weight and x2.weight in round %d: %d, %d\n", i + 1, Huffman[x1].weight, Huffman[x2].weight);
	}
	return n + i;
}
void ShowHaffmanTree(HuffmanNode Huffman[MAXLEN],int pos)
{
	if (pos < 0) return;
	if (Huffman[pos].rchild == -1 && Huffman[pos].lchild == -1)
		printf_s("%c", Huffman[pos].value);
	else
	{
		if (Huffman[pos].lchild != -1)
			ShowHaffmanTree(Huffman, Huffman[pos].lchild);
		if (Huffman[pos].rchild != -1)
			ShowHaffmanTree(Huffman, Huffman[pos].rchild);
	}
}
//���ر��뿪ʼ��λ��
int decode(char string[], HuffmanNode Huffman[], int bits[], int n)
{
	int start = 0;
	int TopOfTree = 0;
	while (Huffman[TopOfTree].parent != -1)
		TopOfTree = Huffman[TopOfTree].parent;
	for (int i = 0; string[i] != '\0'; i++)
	{
		int pos = -1;
		for (int j = 0; j < n; j++)
		{
			if (Huffman[j].value == string[i])
			{
				pos = j;
				break;
			}
		}
		while (pos != TopOfTree)
		{
			int parents = Huffman[pos].parent;
			if (Huffman[parents].lchild == pos)
				bits[start] = 0;//��ڵ�Ϊ0
			else bits[start] = 1;//�ҽڵ�Ϊ1
			pos = parents;
			start++;
		}
	}
	return start-1;
}
//start ȷ�������￪ʼ���룬lengthȷ���ӹ���������ͷ�ڵ�
int encode(char string[], HuffmanNode Huffman[], int bits[], int start,int length)
{
	if (start != 0 && Huffman[length - 1].rchild != -1 && Huffman[length - 1].lchild != -1)
	{
		int count = 0;
		int pos = length - 1;
		for (int i = start; i >= -1;)
		{
			if (Huffman[pos].lchild == -1 && Huffman[pos].rchild == -1)
			{
				//��һ���ڵ㣬���ڵ��ֵ�������
				string[count] = Huffman[pos].value;
				pos = length - 1;
				count++;
			}
			else
			{
				if (bits[i])
					pos = Huffman[pos].rchild;
				else pos = Huffman[pos].lchild;
				i--;
			}
		}
		string[count] = '\0';
		return 1;
	}
	else {
		printf_s("Nothing can encode");
		return 0;
	}
}
void turnString(char string[])
{
	int end;
	for (end = 0; string[end] != '\0'; end++);
	int i = 0, j = end-1;
	while (i < j)
	{
		char t = string[i];
		string[i] = string[j];
		string[j] = t;
		i++; j--;
	}
}
void Showcode(HuffmanNode Huffman[MAXLEN],int n)
{
	for (int i = 0; i < n; i++)
	{
		int tempcode[10];
		char basechar[2];
		basechar[0] = Huffman[i].value;
		basechar[1] = '\0';
		int start = decode(basechar, Huffman, tempcode, 8);
		printf_s("%c :", basechar[0]);
		for (int j = start; j >= 0; j--)
			printf_s("%d", tempcode[j]);
		printf_s("\n");
	}
}
int main()
{
	HuffmanNode Huffman[MAXLEN];
	//���ɹ����������������
	int length = HuffmanTree(Huffman, 8);
	Showcode(Huffman, 8);
	//����
	char decode_string[64];
	gets_s(decode_string, 64 * sizeof(char));
	int bits[MAXLEN];
	int start = decode(decode_string, Huffman, bits, 8);
	//����
	char encode_string[64];
	int staude = encode(encode_string, Huffman, bits, start, length);
	//���������������
	start = decode(encode_string, Huffman, bits, length);
	for (int i = start; i >= 0; i--)
		printf_s("%d",bits[i]);
	//������������
	turnString(encode_string);
	//���������
	puts(encode_string);
	system("pause");
	return 0;
}