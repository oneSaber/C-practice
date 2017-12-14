#pragma once
#ifndef _MAP_H
#include<stdio.h>
#include<stdlib.h>
#define MAXLEN 1000 // ��ʾͼ�Ķ�����
struct Vertex {
	int num;//�����ֱ�ʾ����
	int weight;
	struct Vertex *next;
};
typedef struct Vertex * Node;

void InsertNode(Node *G, int to, int weight, bool Derction)
{
	Node p = (*G)->next;
	Node q = *G;
	int insertfinsh = 0;
	while (p)
	{
		//�յ��Ѿ�����
		if (p->num == to)
		{
			if (Derction)
			{
				p->weight = weight;
			}
			insertfinsh = 1;
			break;
		}
		q = p;
		p = p->next;
	}
	if (!insertfinsh)
	{
		p = (Node)malloc(sizeof(struct Vertex));
		p->num = to;
		p->weight = weight;
		p->next = NULL;
		q->next = p;
	}
}
void InsertVoidNode(Node *G, int from, int to, int weight,bool Derction,bool isfrom)
{
	(*G) = (Node)malloc(sizeof(struct Vertex));
	(*G)->num = from;
	if (isfrom || !Derction)
	{
		Node p = (Node)malloc(sizeof(struct Vertex));
		p->num = to;
		p->weight = weight;
		p->next = NULL;
		(*G)->next = p;
	}
	else (*G)->next = NULL;
}
//����ͼ�Ķ�����,���ɵ�ͼ��Derction�����Ƿ�����
int CreatGraph(Node G[], bool Derction)
{
	int i = 0;
	int from, to, weight;
	G[i] = (Node)malloc(sizeof(struct Vertex));
	G[i]->num = -1;
	G[i]->weight = 0;
	G[i]->next = NULL;
	while (scanf_s("%d %d %d", &from, &to, &weight) == 3)
	{
		int findfrom = 0;
		int findto = 0;
		for (int j = 0; j <= i; j++)
		{
			//�����ڵ�ͼ���ҵ����
			if (G[j]->num == from)
			{
				findfrom = 1;
				InsertNode(&G[j], to, weight, Derction);
			}
			if (G[j]->num == to)
			{
				findto = 1;
				//����ͼ����Ҫ���뵽����
				if(!Derction)
					InsertNode(&G[j], from, weight*-1, (!Derction));
			}
		}
		if (!findfrom)
		{
			//��ǰͼ��û��from�ڵ㣬����from
			InsertVoidNode(&G[++i], from, to, weight,Derction,true);
		}
		if (!findto)
		{
			InsertVoidNode(&G[++i], to, from, weight*-1,Derction,false);
		}
	}
	//G[0]���涥����
	G[0]->num = i;
	return i;
}
void ShowGraph(Node G[])
{
	for (int i = 1; i <= G[0]->num; i++)
	{
		printf_s("%d :", G[i]->num);
		Node p = G[i]->next;
		while (p)
		{
			printf_s("(%d %d %d),", G[i]->num, p->num, p->weight);
			p = p->next;
		}
		printf_s("null\n");
	}
}
#endif // !_MAP_H
