//Paste your code here
//NOTE: If you use java, your Main class must be named solution
#include<iostream>
#include<cmath>
#include <stdio.h>
#include <stdlib.h>		//malloc/realloc函数
using namespace std;

#define LIST_INIT_SIZE	100	//初始大小定义为100（可按需修改）
#define LISTINCREMENT	10	//若空间不够，每次增长10（可按需修改）

typedef int ElemType;	//可根据需要修改元素的类型

typedef struct {
	ElemType *elem;	//存放动态申请空间的首地址（可以理解为表头元素a1的地址）
	int length;		//记录当前长度
	int listsize;	//当前分配的元素的个数
} sqlist;

#define TRUE		1
#define FALSE		0
#define OK		1
#define ERROR		0
#define INFEASIBLE	-1
#define OOVERFLOW	-2
/* 用于比较两个值是否相等的具体函数，与LocateElem中的函数指针定义相同，调用时代入
int LocateElem(sqlist L, ElemType e, int (*compare)(ElemType e1, ElemType e2)) */
int MyCompare(ElemType e1, ElemType e2)
{
	if (e1 == e2)
		return TRUE;
	else
		return FALSE;
}

int MyCompare2(ElemType e1, ElemType e2)
{
	if (e1 <e2)
		return TRUE;
	else
		return FALSE;
}

/* 用于访问某个元素的值的具体函数，与ListTraverse中的函数指针定义相同，调用时代入
int ListTraverse(sqlist L, int (*visit)(ElemType e)) */
int MyVisit(ElemType e)
{
	printf("%d", e);
	return OK;
}

//初始化线性表
int InitList(sqlist *L)//L为指针
{
	L->elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
	if (L->elem == NULL)
		exit(OOVERFLOW);

	L->length = 0;
	L->listsize = LIST_INIT_SIZE;
	return OK;
}
/* 在指定位置前插入一个新元素 */
int ListInsert(sqlist *L, int i, ElemType e)
{
	ElemType *p, *q; //如果是算法，一般可以省略，程序不能

	if (i<1 || i>L->length + 1)   //合理范围是 1..length+1
		return ERROR;

	// 空间已满则扩大空间
	if (L->length >= L->listsize) {
		ElemType *newbase;
		newbase = (ElemType *)realloc(L->elem, (L->listsize + LISTINCREMENT) * sizeof(ElemType));
		if (!newbase)
			return OOVERFLOW;

		L->elem = newbase;
		L->listsize += LISTINCREMENT;
		//L->length暂时不变
	}

	q = &(L->elem[i - 1]);  //第i个元素，即新的插入位置

							/* 从最后一个【length放在[length-1]中】开始到第i个元素依次后移一格 */
	for (p = &(L->elem[L->length - 1]); p >= q; --p)
		*(p + 1) = *p;

	/* 插入新元素，长度+1 */
	*q = e;
	L->length++;
	return OK;
}
/* 删除指定位置的元素，并将被删除元素的值放入e中返回 */
int ListDelete(sqlist *L, int i, ElemType *e)
{
	ElemType *p, *q; //如果是算法，一般可以省略，程序不能

	if (i<1 || i>L->length) //合理范围是 1..length
		return ERROR;

	p = &(L->elem[i - 1]); 		//指向第i个元素
	*e = *p; 				//取第i个元素的值放入e中
	q = &(L->elem[L->length - 1]);	//指向最后一个元素，也可以 q = L->elem+L->length-1

									/* 从第i+1到最后，依次前移一格 */
	for (++p; p <= q; ++p)
		*(p - 1) = *p;

	L->length--;	//长度-1
	return OK;
}
/* 查找符合指定条件的元素 */
int LocateElem(sqlist L, ElemType e)
{
	ElemType *p = L.elem;
	int       i = 1;

	while (i <= L.length )
	{
		if (compare(*p++, e) == TRUE)
			break;
		i++;
	}
	return (i <= L.length) ? i : -1;	//找到返回i，否则返回-1
}
//看元素是否大于e，大于则返回位置
int LocateElem2(sqlist L, ElemType e, int(*compare2)(ElemType e1, ElemType e2))
{
	ElemType *p = L.elem;
	int       i = 1;

	while (i <= L.length && (*compare2)(*p++, e) == TRUE)
		i++;

	return (i <= L.length) ? i : -1;	//找到返回i，否则返回-1
}
/* 遍历线性表 */
int ListTraverse(sqlist L, int(*visit)(ElemType e))
{
	ElemType *p = L.elem;
	int       i = 1;

	while (i <= L.length && (*visit)(*p++) == TRUE)
	{
		if (i != L.length)
			printf(" ");
		i++;
	}

	if (i <= L.length)
		return ERROR;

	return OK;
}
//升序排列
int ListSort(sqlist *L)
{

	for (int i = 0; i < L->length - 1; i++)
	{
		for (int j = 0; j < L->length - 1 - i; j++)// j开始等于0，
		{
			if (L->elem[j] > L->elem[j + 1])
			{
				int temp = L->elem[j];
				Llist->elem[j] = L->elem[j + 1];
				L->elem[j + 1] = temp;
			}
		}
	}
	return 0;
}
int main()
{
	sqlist   L;
	ElemType e;
	int      i = 1;

	InitList(&L);
	//创建
	while (1)
	{
		cin >> e;
		if (e == 0)
			break;
		ListInsert(&L, i, e);
		i++;
	}
	ListSort(&L);
	//插入
	int pos;
	//删除重复元素：每次调用locateelem删除值为elem的元素，从当前位置开始以保证不会删光
	//复杂度O(n)
	
	for (i=0;i<n-1;++i)
	{
		pos=LocateElem(L,i,e);
		ListDelete(L,pos,e);
	}
	ListTraverse(L,MyVisit);
	return 0;
}
