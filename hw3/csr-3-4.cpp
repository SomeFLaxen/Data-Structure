#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

#define _CRT_SECURE_NO_WARNINGS

#define ELEMTYPE_IS_INT		
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR -1
#define INFEASIBLE -1
#define LOVERFLOW -2

#define LIST_INIT_SIZE 10000      //��ʼ��СΪ10000
#define LISTINCREMENT 100        //�ռ��������

typedef int Status;
typedef int ElemType;


typedef struct LNode {
	ElemType data;
	struct LNode *next;
}LNode, *LinkList;

Status InitList(LinkList *L);
Status DestoryList(LinkList *L);
int LocateElem(LinkList L, ElemType e, Status(*compare)(ElemType e1, ElemType e2));
Status ListInsert(LinkList *L, int i, ElemType e);
Status ListDelete(LinkList *L, int i, ElemType *e);
Status ListTraverse(LinkList L, Status(*visit)(ElemType e));
int ListLength(LinkList L);
Status GetElem(LinkList L, int i, ElemType *e);
Status MergeList_L(LinkList &La, LinkList &Lb, LinkList &Lc);
Status SortList(LinkList &L);

/*��ʼ�����Ա�*/
Status InitList(LinkList *L)
{
	/*����ͷ���ռ�,��ֵ��ͷָ��*/
	*L = (LNode *)malloc(sizeof(LNode));
	if (*L == NULL)
		exit(OVERFLOW);
	(*L)->next = NULL;
	return OK;
}

/*ɾ�����Ա�*/
Status DestoryList(LinkList *L)
{
	LinkList q, p = *L;

	/*��ͷ��㿪ʼ�����ͷ�(��ͷ���)*/
	while (p)
	{
		q = p->next;
		free(p);
		p = q;
	}
	*L = NULL;  //ͷָ����NULL

	return OK;
}

/*���ҷ���ָ��������Ԫ��*/
int LocateElem(LinkList L, ElemType e, Status(*compare)(ElemType e1, ElemType e2))
{
	LinkList p = L->next;  //��Ԫ���
	int pos = 1;  //��ʼλ��

				  /*ѭ����������*/
	while (p && (*compare)(e, p->data) == FALSE)
	{
		p = p->next;
		pos++;
	}

	return p ? pos : -1;
}


/*main�����е�MyCompare����,��˳��ʵ����ȫһ��,����ʱ:LocateElem(L,e,MyCompare)����*/
Status MyCompare(ElemType e1, ElemType e2)
{
	if (e1 == e2)
		return TRUE;
	else
		return FALSE;
}

/*��ָ��λ��ǰ����һ����Ԫ��*/
Status ListInsert(LinkList *L, int i, ElemType e)
{
	LinkList s, p = *L;
	int pos = 0;

	/*Ѱ�ҵ�i-1�����*/
	while (p&&pos < i - 1)
	{
		p = p->next;
		pos++;
	}

	if (p == NULL || pos > i - 1)  //iֵ�Ƿ��򷵻�
		return ERROR;
	//ִ�е��˱�ʾ�ҵ���λ��,pָ���i-1�����

	s = (LinkList)malloc(sizeof(LNode));
	if (s == NULL)
		return OVERFLOW;
	s->data = e;  //�½��������ֵ
	s->next = p->next;
	p->next = s;

	return OK;
}

/*ɾ��ָ��λ�õ�Ԫ��,������ɾ��Ԫ�ص�ֵ����e�з���*/
Status ListDelete(LinkList *L, int i, ElemType *e)
{
	LinkList q, p = *L;  //pָ��ͷ���
	int pos = 0;

	/*Ѱ�ҵ�i�����(p->next�ǵ�i�����)*/
	while (p->next&&pos < i - 1)
	{
		p = p->next;
		pos++;
	}
	if (p->next == NULL || pos > i - 1)  //iֵ�Ƿ��򷵻�
		return ERROR;

	//ִ�е��˱�ʾ�ҵ��˵�i�����,��ʱpָ���i-1�����

	q = p->next;
	p->next = q->next;
	*e = q->data;  //ȡ��i������ֵ
	free(q);

	return OK;
}

/*�������Ա�*/
Status ListTraverse(LinkList L, Status(*visit)(ElemType e))
{
	LinkList p = L->next;  //ָ����Ԫ���

	while (p && (*visit)(p->data) == TRUE)
		p = p->next;

	if (p)
		return ERROR;

	printf("\n");  //����ӡһ������
	return OK;
}

/*main�����е�MyVisit����,��˳��ʵ����ȫһ��,����ʱ:ListTraverse(L,MyVisit)����*/
Status MyVisit(ElemType e)
{
	cout << e << ' ';
	return OK;
}

/*���ĳ���*/
int ListLength(LinkList L)
{
	LinkList p = L->next;  //ָ����Ԫ���
	int len = 0;

	/*ѭ����������,���м���*/
	while (p)
	{
		p = p->next;
		len++;
	}

	return len;
}

/*ȡ����Ԫ��*/
Status GetElem(LinkList L, int i, ElemType *e)
{
	LinkList p = L->next;  //pָ����Ԫ���
	int pos = 1;  //��ʼλ��Ϊ1

				  /*����ΪNULL,��δ����i��Ԫ��*/
	while (p != NULL && pos < i)
	{
		p = p->next;
		pos++;
	}

	if (!p || pos > i)
		return ERROR;

	*e = p->data;
	return *e;
}

/*�ϲ�����*/
Status MergeList_L(LinkList &La, LinkList &Lb, LinkList &Lc)
{
	LinkList pa = La->next, pb = Lb->next, pc;
	InitList(&Lc);
	Lc = pc = La;  //����La��ͷ�ڵ���Lc��ͷ�ڵ�
	while (pa&&pb)
	{
		if (pa->data <= pb->data)
		{
			pc->next = pa;  //��pa��ָ�ڵ�ֱ�ӽ���Lc�����
			pc = pa;
			pa = pa->next;
		}
		else
		{
			pc->next = pb;
			pc = pb;
			pb = pb->next;
		}
	}

	pc->next = pa ? pa : pb;
	free(Lb);

	return OK;
}

/*����������*/
Status SortList(LinkList &L)
{
	ElemType t;
	int count = ListLength(L);

	for (LinkList p=L->next; p; p = p->next)
	{
		for (LinkList q=p->next; q; q = q->next)
		{
			if (p->data >= q->data)
			{
				t = p->data;
				p->data = q->data;
				q->data = t;
			}
		}
	}

	return OK;
}

int main()
{
	LinkList La, Lb, Lc;
	ElemType list_a[LIST_INIT_SIZE], list_b[LIST_INIT_SIZE];

	InitList(&La);
	InitList(&Lb);  //��ʼ������

	int i;

	for (i = 0; i < LIST_INIT_SIZE; i++)
	{
		cin >> list_a[i];
		if (list_a[i] <= 10000)
		{
			if (list_a[i] == 0)
				break;
			else
				ListInsert(&La, i + 1, list_a[i]);
		}
	}
	SortList(La);

	for (i = 0; i < LIST_INIT_SIZE; i++)
	{
		cin >> list_b[i];
		if (list_b[i] <= 10000)
		{
			if (list_b[i] == 0)
				break;
			else
				ListInsert(&Lb, i + 1, list_b[i]);
		}
	}
	SortList(Lb);

	MergeList_L(La, Lb, Lc);

	ListTraverse(Lc, MyVisit);

	return 0;
}