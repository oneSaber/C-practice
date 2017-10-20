#pragma once
#ifndef Stack_H

#include<stdio.h>
#include<stdlib.h>
#define IN 'A'
#define OUT 'D'
#define END 'E'

void eatline()
{
	char ch = getchar();
	while (ch != '\n')
		ch = getchar();
}

struct car {
	char Info;
	int card_id;
	int stay_time;
	struct car *next;
};
typedef car Car;
typedef Car *Position;
typedef Car *Stack;
//�ж��Ƿ��ǿ�ջ
int IsEmpty(Stack S)
{
	return S->next == NULL;
}
//�ж��Ƿ���ջ��
int IsLast(Position p)
{
	return  p->next == NULL;
}
//����һ����ջ
Stack CreateStack(Stack S)
{
	if (!IsEmpty(S))
	{
		S = (Stack)malloc(sizeof(Car));
		S->next = NULL;
	}
	return S;
}
//����ջ��Ԫ��
Position Pop(Stack s)
{
	if (!IsEmpty(s))
	{
		Position p = s->next;
		s->next = p->next;
		return p;
	}
	else {
		printf_s("��ջ��");
		return NULL;
	}
}
//��ջ
void Push(Stack s, int card_id, int stay_time, char Info)
{
	Position p = (Position)malloc(sizeof(Car));
	p->card_id = card_id;
	p->Info = Info;
	p->stay_time = stay_time;
	p->next = s->next;
	s->next = p;
}
//����ջ��Ԫ�ص����ݣ�������ջ
Position Top(Stack S)
{
	return S->next;
}
//����������ջ
void All_inStack(Stack S)
{
	int car_id;
	int stay_time;
	char Info = getchar();
	eatline();
	while (scanf_s("%d%d", &car_id, &stay_time) == 2)
	{
		eatline();
		Push(S, car_id, stay_time, Info);
		Info = getchar();
		eatline();
	}
	eatline();
	printf_s("Stack OVER!\n");
}
//���ջ������
void ShowStack(Stack S)
{
	Position p;
	while (!IsEmpty(S))
	{
		p = Pop(S);
		printf_s("%c,%d,%d\n", p->Info, p->card_id, p->stay_time);
	}
}
#endif // !Stack_H
