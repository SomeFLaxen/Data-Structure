#include <iostream>
#include <stdio.h>
#include <stdlib.h>		//malloc/realloc函数
#include <math.h>               //fabs函数
#include <string.h>		//strcpy/strcmp等函数
#define _CRT_SECURE_NO_WARNINGS
using namespace std;

/* P.10 的预定义常量和类型 */
#define TRUE		1
#define FALSE		0
#define OK		1
#define ERROR		0
#define INFEASIBLE	-1
//#define LOVERFLOW	-2		//因为<math.h>中已有 OVERFLOW 的定义，因此换一下

typedef int Status;
typedef int ElemType;
typedef struct LNode {
	ElemType    data;   //数据
	struct LNode *next; //后继的指针
}LNode, *LinkList;

Status MyCompare(ElemType e1, ElemType e2)
{

	if (e1 == e2)
		return TRUE;
	else
		return FALSE;
}

/* 用于访问某个元素的值的具体函数，与ListTraverse中的函数指针定义相同，调用时代入
Status ListTraverse(sqlist L, Status (*visit)(ElemType e)) */
Status MyVisit(ElemType e)
{
	cout << e << ' ';
	return OK;
}
/* 求表的长度 */
int ListLength(LinkList L)
{
	LinkList p = L->next;//指向首元结点
	int len = 0;

	/*循环计数*/
	while (p) {
		p = p->next;
		len++;
	}

	return len;
}
Status assign(ElemType *e, ElemType data)//将data赋值给指针e指向的值
{
	*e = data;
	return OK;
}
/* 初始化线性表 */
Status InitList(LinkList *L)//main中声明为 LinkList L 调用为InitList（&L）;
{
	//申请头结点空间，赋值给头指针
	*L = (LNode*)malloc(sizeof(LNode));   //&L是指针的指针 
	if (*L == NULL)
		exit(OVERFLOW);
	(*L)->next = NULL;
	return OK;
}
/* 在指定位置前插入一个新元素 */
Status ListInsert(LinkList *L, int i, ElemType e)
{
	LinkList s, p = *L;  //p指向头结点
	int  pos = 0;
	//寻找第i-1个结点
	while (p&&pos < i - 1) {
		p = p->next;
		pos++;
	}
	if (p == NULL || pos > i - 1) //i值非法返回
		return ERROR;
	//p指向第i-1个结点
	s = (LinkList)malloc(sizeof(LNode));
	if (s == NULL)
		return OVERFLOW;

	//新结点数据域赋值
	assign(&(s->data), e);

	s->next = p->next;
	p->next = s;
	return OK;
}

/* 删除指定位置的元素，并将被删除元素的值放入e中返回 */
Status ListDelete(LinkList *L, int i, ElemType *e)
{
	LinkList q, p = *L; //p >头结点
	int  pos = 0;
	//寻找第i个结点(p->next)
	while (p->next&&pos < i - 1) {
		p = p->next;
		pos++;
	}
	if (p->next == NULL || pos > i - 1) //i非法返回
		return ERROR;
	//p指向第i-1个结点
	q = p->next;  //q>i个结点
	p->next = q->next; //i-1->next   >   i+1
	assign(e, q->data);

	free(q);

	return OK;
}
/* 查找符合指定条件的元素 */
int LocateElem(LinkList L, ElemType e, Status(*compare)(ElemType e1, ElemType e2))
{
	LinkList p = L->next; //首元结点
	int pos = 1;          //初始位置

						  //循环整个链表
	while (p && (*compare)(e, p->data) == FALSE) {
		p = p->next;
		pos++;
	}

	return p ? pos : -1;
}
/* 遍历线性表 */
Status ListTraverse(LinkList L, Status(*visit)(ElemType e))
{
	LinkList p = L->next;  //指向首元
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
	
	//创建
	int n;
	cin >> n;
	InitList(&L);
	for (i = 1; i <= n; i++)
	{
		cin >> e1;
		ListInsert(&L, 1, e1);
	}
	ListTraverse(L, MyVisit);
	
	//插入
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