#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MaxLen 100
#define LinkLen 10

//���ù�ϣ�洢��Ϣ��������ϢС��100

struct data {
	char PhoneNumber[81];
	char Name[81];
	char Address[81];
};
typedef struct data Person;
struct HashNode {
	Person info;
	struct HashNode *next;
};

struct InfoNode {
	Person info;
	int store;
	//1Ϊ�Ծ��洢��0Ϊδ�洢
};
typedef struct HashNode *Node;
typedef struct InfoNode Personal;

//��ͻʱ�����µ�hash
int newHash(int oldhash)
{
	return (oldhash + 1) % MaxLen;
}
//�����õ绰�������ɵ�hashֵ��-1Ϊ�������
int Hash(char Key[])
{
	if (Key[0] == '\0')
		return -1;
	int sum = 0;
	int i = 0;
	while (Key[i] != '\0')
		sum += Key[i++];
	return sum % MaxLen;
}
//��ʼ��People���飬�����и�����Ϊδ����
void InitPeople(Personal People[])
{
	for (int i = 0; i < MaxLen; i++)
	{
		People[i].store = 0;
	}
}
//���յ绰����洢��Ϣ
void StoreByPhone(Personal People[])
{
	int i = 0;
	char tempPhone[81];
	while (i<MaxLen)
	{
		gets_s(tempPhone);
		int hash = Hash(tempPhone);
		//�������
		if (hash == -1)
			return;
		if (hash > -1 && People[hash].store != 1)
		{
			strcpy_s(People[hash].info.PhoneNumber, tempPhone);
			gets_s(People[hash].info.Name);
			gets_s(People[hash].info.Address);
			i++;
		}
		else
		{
			while (hash < MaxLen-1)
			{
				hash = newHash(hash);
				if (People[hash].store != 1)
				{
					strcpy_s(People[hash].info.PhoneNumber, tempPhone);
					gets_s(People[hash].info.Name);
					gets_s(People[hash].info.Address);
					i++;
				}
			}
		}
	}
}
//���յ绰�����ѯ
void SearchByPhone(Personal People[])
{
	printf_s("������ҵĵ绰:");
	char Phone[81];
	gets_s(Phone);
	int oldHash = Hash(Phone);
	//ֱ�Ӳ��ҵ�������ͻ
	if (strcmp(Phone, People[oldHash].info.PhoneNumber) == 0)
	{
		printf_s("Number :%s\nName:%s\nAddress:%s",
			People[oldHash].info.PhoneNumber,
			People[oldHash].info.Name,
			People[oldHash].info.Address);

	}//��ͻ,��������
	else {
		int hash = oldHash;
		hash = newHash(hash);
		while(hash!=oldHash)
		{ 
			if (People[hash].store)
			{	//ֱ�Ӳ��ҵ�������ͻ
				if (strcmp(Phone, People[oldHash].info.Name) == 0)
				{
					printf_s("Number :%s\nName:%s\nAddress:%s",
						People[oldHash].info.PhoneNumber,
						People[oldHash].info.Name,
						People[oldHash].info.Address);
					break;
				}
			}
			hash = newHash(hash);
		}
		//�������ݲ�����
		hash = newHash(hash);
		//�ҵ���һ������ͻ��λ��
		while (!People[hash].store)
		{
			strcpy_s(People[hash].info.PhoneNumber, Phone);
			printf_s("û�в��ҵ��������ֺ͵�ַ��������");
			gets_s(People[hash].info.Name);
			gets_s(People[hash].info.Address);
			break;
		}
	}
}


//��name��hashֵ
int HashName(char Key[])
{
	if (Key[0] == '\0')
		return -1;
	int sum = 0;
	int i = 0;
	while (Key[i] != '\0')
		sum += Key[i++];
	return sum % LinkLen;
}
void Init(Node People[])
{
	for (int i = 0; i < LinkLen; i++)
	{
		People[i] = (Node)malloc(sizeof(struct HashNode));
		People[i]->next = NULL;
	}
}
void TravePeople(Node People[])
{
	for (int i = 0; i < LinkLen; i++)
	{
		printf_s("%d:", i);
		Node P = People[i]->next;
		while (P != NULL)
		{
			printf_s("(%s, %s, %s)->", P->info.Name, P->info.PhoneNumber, P->info.Address);
			P = P->next;
		}
		printf_s("Null\n");
	}
}
//�����ִ���
void StoreByName(Node Head[])
{
	char tempname[81];
	gets_s(tempname);
	int hash = HashName(tempname);
	while (hash != -1)
	{
		Node P = Head[hash];
		while (P->next!=NULL)
		{
			P = P->next;
		}
		Node Q = (Node)malloc(sizeof(struct HashNode));
		strcpy_s(Q->info.Name, tempname);
		gets_s(Q->info.PhoneNumber);
		gets_s(Q->info.Address);
		P->next = Q;
		Q->next = NULL;

		gets_s(tempname);
		hash = HashName(tempname);
	}
}

//�����ֲ���
void SearchByName(Node Head[])
{
	char searchname[81];
	printf_s("������ҵ�����:");
	gets_s(searchname);
	int hash = HashName(searchname);
	Node head = Head[hash];
	while (head->next != NULL)
	{
		//ͷ���ŵ�������ֵ
		head = head->next;
		if (strcmp(head->info.Name, searchname) == 0)
		{
			printf_s("(%s, %s, %s)->", head->info.Name, head->info.PhoneNumber, head->info.Address);
			return;
		}
	}
	Node Q = (Node)malloc(sizeof(struct HashNode));
	printf_s("δ���ҵ�");
	head->next = Q;
	Q->next = NULL;
	strcpy_s(Q->info.Name, searchname);
	gets_s(Q->info.PhoneNumber);
	gets_s(Q->info.Address);

}
int main()
{
	//���绰����洢
	/*Personal People[MaxLen];
	InitPeople(People);
	StoreByPhone(People);
	SearchByPhone(People);*/
	//�����ִ���
	Node People[LinkLen];
	Init(People);
	StoreByName(People);
	//TravePeople(People);
	SearchByName(People);
	system("pause");
	return 0;
}