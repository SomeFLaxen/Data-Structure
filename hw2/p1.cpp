#include <iostream>
#include <stdio.h>
#include <stdlib.h>		//malloc/realloc����
#include <math.h>               //fabs����
#include <string.h>		//strcpy/strcmp�Ⱥ���
#define _CRT_SECURE_NO_WARNINGS
using namespace std;

/* P.10 ��Ԥ���峣�������� */
#define TRUE		1
#define FALSE		0
#define OK		1
#define ERROR		0
#define INFEASIBLE	-1
//#define LOVERFLOW	-2		//��Ϊ<math.h>������ OVERFLOW �Ķ��壬��˻�һ��

typedef int Status;
typedef int ElemType;
typedef struct LNode {
	ElemType    data;   //����
	struct LNode *next; //��̵�ָ��
}LNode, *LinkList;

Status MyCompare(ElemType e1, ElemType e2)
{

	if (e1 == e2)
		return TRUE;
	else
		return FALSE;
}

/* ���ڷ���ĳ��Ԫ�ص�ֵ�ľ��庯������ListTraverse�еĺ���ָ�붨����ͬ������ʱ����
Status ListTraverse(sqlist L, Status (*visit)(ElemType e)) */
Status MyVisit(ElemType e)
{
	cout << e << ' ';
	return OK;
}
/* ���ĳ��� */
int ListLength(LinkList L)
{
	LinkList p = L->next;//ָ����Ԫ���
	int len = 0;

	/*ѭ������*/
	while (p) {
		p = p->next;
		len++;
	}

	return len;
}
Status assign(ElemType *e, ElemType data)//��data��ֵ��ָ��eָ���ֵ
{
	*e = data;
	return OK;
}
/* ��ʼ�����Ա� */
Status InitList(LinkList *L)//main������Ϊ LinkList L ����ΪInitList��&L��;
{
	//����ͷ���ռ䣬��ֵ��ͷָ��
	*L = (LNode*)malloc(sizeof(LNode));   //&L��ָ���ָ�� 
	if (*L == NULL)
		exit(OVERFLOW);
	(*L)->next = NULL;
	return OK;
}
/* ��ָ��λ��ǰ����һ����Ԫ�� */
Status ListInsert(LinkList *L, int i, ElemType e)
{
	LinkList s, p = *L;  //pָ��ͷ���
	int  pos = 0;
	//Ѱ�ҵ�i-1�����
	while (p&&pos < i - 1) {
		p = p->next;
		pos++;
	}
	if (p == NULL || pos > i - 1) //iֵ�Ƿ�����
		return ERROR;
	//pָ���i-1�����
	s = (LinkList)malloc(sizeof(LNode));
	if (s == NULL)
		return OVERFLOW;

	//�½��������ֵ
	assign(&(s->data), e);

	s->next = p->next;
	p->next = s;
	return OK;
}

/* ɾ��ָ��λ�õ�Ԫ�أ�������ɾ��Ԫ�ص�ֵ����e�з��� */
Status ListDelete(LinkList *L, int i, ElemType *e)
{
	LinkList q, p = *L; //p >ͷ���
	int  pos = 0;
	//Ѱ�ҵ�i�����(p->next)
	while (p->next&&pos < i - 1) {
		p = p->next;
		pos++;
	}
	if (p->next == NULL || pos > i - 1) //i�Ƿ�����
		return ERROR;
	//pָ���i-1�����
	q = p->next;  //q>i�����
	p->next = q->next; //i-1->next   >   i+1
	assign(e, q->data);

	free(q);

	return OK;
}
/* ���ҷ���ָ��������Ԫ�� */
int LocateElem(LinkList L, ElemType e, Status(*compare)(ElemType e1, ElemType e2))
{
	LinkList p = L->next; //��Ԫ���
	int pos = 1;          //��ʼλ��

						  //ѭ����������
	while (p && (*compare)(e, p->data) == FALSE) {
		p = p->next;
		pos++;
	}

	return p ? pos : -1;
}
/* �������Ա� */
Status ListTraverse(LinkList L, Status(*visit)(ElemType e))
{
	LinkList p = L->next;  //ָ����Ԫ
	while (p && (*visit)(p->data) == TRUE)
		p = p->next;

	if (p)
		return ERROR;

	printf("\n");
	return OK;
}

int main()
{
	LinkList L;
	ElemType e1;
	int      i;
	
	//����
	int n;
	cin >> n;
	InitList(&L);
	for (i = 1; i <= n; i++)
	{
		cin >> e1;
		ListInsert(&L, 1, e1);
	}
	ListTraverse(L, MyVisit);
	
	//����
	cin >> i >> e1;
	int ppp=ListInsert(&L, i, e1);
	if (ppp)
		ListTraverse(L, MyVisit);
	else
		cout << -1 << endl;
	
	//delete
	cin >> i;
	int bbb=ListDelete(&L, i, &e1);
	if (bbb)
		ListTraverse(L, MyVisit);
	else
		cout << -1 << endl;
	
	//search
	cin >> e1;
	cout<<LocateElem(L, e1, MyCompare)<<endl;
	
	//count
	cout << ListLength(L);
	return 0;
}