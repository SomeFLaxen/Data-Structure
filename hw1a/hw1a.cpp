#include<iostream>
#include<string>
using namespace std;
typedef  int SElemType;
typedef int Status;
#define TRUE        1
#define FALSE        0
#define OK        1
#define ERROR        0
#define INFEASIBLE    -1
#define LOVERFLOW    -2
#define LISTINCREMENT    10


typedef struct
{
	SElemType *base;
	SElemType *top;
	int stacksize;
}SqStack;

Status InitStack(SqStack &S, int a)
{
	int STACK_INIT_SIZE = a;
	S.base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType));
	if (!S.base)
		exit(LOVERFLOW);
	S.top = S.base;
	S.stacksize = STACK_INIT_SIZE;
	return OK;
}

Status GetTop(SqStack S, SElemType &e)
{
	if (S.top == S.base)
		return ERROR;
	e = *(S.top - 1);
	return OK;
}
Status StackEmpty(SqStack S)
{
	if (S.top == S.base)
		return 1;
	else
		return 0;
}
Status StackFull(SqStack S)
{
	if (S.top - S.base >= S.stacksize)
		return 1;
	else
		return 0;
}
Status Push(SqStack &S, SElemType e)
{
	if (S.top - S.base >= S.stacksize)
		return 0;
	*S.top++ = e;
	return OK;
}
Status Push_jia(SqStack &S)
{
	if (S.top - S.base >= S.stacksize)
		return 0;
	return 1;
}
Status Pop(SqStack &S, SElemType &e)
{

	if (S.top == S.base)
		return ERROR;
	e = *--S.top;
	return OK;
}

void print_stack(SqStack S)
{
	if (S.top == S.base)
	{
		cout << 0 << endl;
		return;
	}
	while (S.top != S.base)
	{
		cout << *--S.top << " ";
	}
	cout << endl;
}
int main()
{
	SqStack S[10000];
	string a;
	int n, k, m, ki;
	cin >> n >> k;
	for (int i = 1; i <= n; i++)
	{
		cin >> m;
		InitStack(S[i], m);
	}
	for (int i = 0; i < k; i++)
	{
		cin >> ki;
		Push(S[1], ki);
	}
	cin >> a;
	int zhu1, zhu2, x1 = 0, x2 = 0, pd;
	int d1;
	while (1)
	{
		if (a == "MOVE")
		{
			cin >> zhu1 >> zhu2;
			GetTop(S[zhu1], x1);
			GetTop(S[zhu2], x2);
			if (StackEmpty(S[zhu1]))
				cout << zhu1 << " IS EMPTY" << endl;
			if (StackFull(S[zhu2]))
				cout << zhu2 << " IS FULL" << endl;
			if (x1 > x2 && !StackEmpty(S[zhu2]))
				cout << "ILLEGAL" << endl;
			if (!StackEmpty(S[zhu1]) && !StackFull(S[zhu2]) && (x1 <= x2 || StackEmpty(S[zhu2])))
			{
				Pop(S[zhu1], x1);
				cout << x1 << endl;
				Push(S[zhu2], x1);
			}
		}
		if (a == "DISPLAY")
		{
			cin >> d1;
			print_stack(S[d1]);
		}
		if (a == "QUIT")
		{
			for (int i = 1; i <= n; i++)
			{
				print_stack(S[i]);
			}
			break;
		}
		cin >> a;
	}
}

