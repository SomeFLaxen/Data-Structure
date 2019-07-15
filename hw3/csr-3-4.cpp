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

#define LIST_INIT_SIZE 10000      //初始大小为10000
#define LISTINCREMENT 100        //空间分配增量

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

/*初始化线性表*/
Status InitList(LinkList *L)
{
	/*申请头结点空间,赋值给头指针*/
	*L = (LNode *)malloc(sizeof(LNode));
	if (*L == NULL)
		exit(OVERFLOW);
	(*L)->next = NULL;
	return OK;
}

/*删除线性表*/
Status DestoryList(LinkList *L)
{
	LinkList q, p = *L;

	/*从头结点开始依次释放(含头结点)*/
	while (p)
	{
		q = p->next;
		free(p);
		p = q;
	}
	*L = NULL;  //头指针置NULL

	return OK;
}

/*查找符合指定条件的元素*/
int LocateElem(LinkList L, ElemType e, Status(*compare)(ElemType e1, ElemType e2))
{
	LinkList p = L->next;  //首元结点
	int pos = 1;  //初始位置

				  /*循环整个链表*/
	while (p && (*compare)(e, p->data) == FALSE)
	{
		p = p->next;
		pos++;
	}

	return p ? pos : -1;
}


/*main函数中的MyCompare函数,与顺序实现完全一致,调用时:LocateElem(L,e,MyCompare)即可*/
Status MyCompare(ElemType e1, ElemType e2)
{
	if (e1 == e2)
		return TRUE;
	else
		return FALSE;
}

/*在指定位置前插入一个新元素*/
Status ListInsert(LinkList *L, int i, ElemType e)
{
	LinkList s, p = *L;
	int pos = 0;

	/*寻找第i-1个结点*/
	while (p&&pos < i - 1)
	{
		p = p->next;
		pos++;
	}

	if (p == NULL || pos > i - 1)  //i值非法则返回
		return ERROR;
	//执行到此表示找到该位置,p指向第i-1个结点

	s = (LinkList)malloc(sizeof(LNode));
	if (s == NULL)
		return OVERFLOW;
	s->data = e;  //新结点数据域赋值
	s->next = p->next;
	p->next = s;

	return OK;
}

/*删除指定位置的元素,并将被删除元素的值放入e中返回*/
Status ListDelete(LinkList *L, int i, ElemType *e)
{
	LinkList q, p = *L;  //p指向头结点
	int pos = 0;

	/*寻找第i个结点(p->next是第i个结点)*/
	while (p->next&&pos < i - 1)
	{
		p = p->next;
		pos++;
	}
	if (p->next == NULL || pos > i - 1)  //i值非法则返回
		return ERROR;

	//执行到此表示找到了第i个结点,此时p指向第i-1个结点

	q = p->next;
	p->next = q->next;
	*e = q->data;  //取第i个结点的值
	free(q);

	return OK;
}

/*遍历线性表*/
Status ListTraverse(LinkList L, Status(*visit)(ElemType e))
{
	LinkList p = L->next;  //指向首元结点

	while (p && (*visit)(p->data) == TRUE)
		p = p->next;

	if (p)
		return ERROR;

	printf("\n");  //最后打印一个换行
	return OK;
}

/*main函数中的MyVisit函数,与顺序实现完全一致,调用时:ListTraverse(L,MyVisit)即可*/
Status MyVisit(ElemType e)
{
	cout << e << ' ';
	return OK;
}

/*求表的长度*/
int ListLength(LinkList L)
{
	LinkList p = L->next;  //指向首元结点
	int len = 0;

	/*循环整个链表,进行计数*/
	while (p)
	{
		p = p->next;
		len++;
	}

	return len;
}

/*取表中元素*/
Status GetElem(LinkList L, int i, ElemType *e)
{
	LinkList p = L->next;  //p指向首元结点
	int pos = 1;  //初始位置为1

				  /*链表不为NULL,且未到第i个元素*/
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

/*合并链表*/
Status MergeList_L(LinkList &La, LinkList &Lb, LinkList &Lc)
{
	LinkList pa = La->next, pb = Lb->next, pc;
	InitList(&Lc);
	Lc = pc = La;  //借用La的头节点做Lc的头节点
	while (pa&&pb)
	{
		if (pa->data <= pb->data)
		{
			pc->next = pa;  //将pa所指节点直接接在Lc的最后
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

/*对链表排序*/
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
	InitList(&Lb);  //初始化链表

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