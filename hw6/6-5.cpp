#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>     //malloc/realloc函数
#include <string>
#include <iostream>
using namespace std;

#define TRUE        1
#define FALSE       0
#define OK      1
#define ERROR       0
#define INFEASIBLE  -1
#define LOVERFLOW   -2  //避免与<math.h>中的定义冲突

typedef int Status;

/* P.46 结构体定义 */
#define STACK_INIT_SIZE 100 //初始大小定义为100（可按需修改）
#define STACKINCREMENT  10  //若空间不够，每次增长10（可按需修改）

typedef int SElemType;  //可根据需要修改元素的类型

typedef struct {
    SElemType *base;    //存放动态申请空间的首地址
    SElemType *top;     //栈顶指针
    int stacksize;  //当前分配的元素的个数
} SqStack;

/* P.46-47的抽象数据类型定义转换为实际的C语言 */
Status  InitStack(SqStack *S);
Status  DestroyStack(SqStack *S);
Status  ClearStack(SqStack *S);
Status  StackEmpty(SqStack S);
int StackLength(SqStack S);
Status  GetTop(SqStack S, SElemType *e);
Status  Push(SqStack *S, SElemType e);
Status  Pop(SqStack *S, SElemType *e);
Status  StackTraverse(SqStack S, Status(*visit)(SElemType e));

/* 初始化栈 */
Status InitStack(SqStack *S)
{
    S->base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType));
    if (S->base == NULL)
        exit(LOVERFLOW);
    S->top = S->base;  //栈顶指针指向栈底，表示栈空
    S->stacksize = STACK_INIT_SIZE;
    return OK;
}

/* 删除栈 */
Status DestroyStack(SqStack *S)
{
    /* 若未执行 InitStack，直接执行本函数，则可能出错，因为指针初始值未定 */
    if (S->base)
        free(S->base);  //要考虑空栈删除的情况，因此要判断
    S->top = NULL;
    S->stacksize = 0;

    return OK;
}

/* 清空栈（已初始化，不释放空间，只清除内容） */
Status ClearStack(SqStack *S)
{
    /* 如果栈曾经扩展过，恢复初始的大小 */
    if (S->stacksize > STACK_INIT_SIZE) {
        S->base = (SElemType *)realloc(S->base, STACK_INIT_SIZE * sizeof(SElemType));
        if (S->base == NULL)
            exit(LOVERFLOW);
        S->stacksize = STACK_INIT_SIZE;
    }

    S->top = S->base; //栈顶指针指向栈顶，表示栈空
    return OK;
}

/* 判断是否为空栈 */
Status StackEmpty(SqStack S)
{
    if (S.top == S.base)
        return TRUE;
    else
        return FALSE;
}

/* 求栈的长度 */
int StackLength(SqStack S)
{
    return S.top - S.base;//指针相减，值为相差的元素个数
}

/* 取栈顶元素 */
Status GetTop(SqStack S, SElemType *e)
{
    if (S.top == S.base)
        return ERROR;

    *e = *(S.top - 1);  //下标从0开始，top是实际栈顶+1
    return OK;
}

/* 元素入栈 */
Status Push(SqStack *S, SElemType e)
{
    /* 如果栈已满，则扩充空间 */
    if (S->top - S->base >= S->stacksize) {
        S->base = (SElemType *)realloc(S->base, (S->stacksize + STACKINCREMENT) * sizeof(SElemType));
        if (S->base == NULL)
            return LOVERFLOW;
        S->top = S->base + S->stacksize; //因为S->base可能会变，因此要修正S->top的值
        S->stacksize += STACKINCREMENT;
    }
    *S->top++ = e;  //先*(S->top)，再S->top++
    return OK;
}

/* 元素出栈 */
Status Pop(SqStack *S, SElemType *e)
{
    int length;

    if (S->top == S->base)
        return ERROR;
    *e = *--S->top;

    /* 如果栈缩小，则缩小动态申请空间的大小 */
    length = S->top - S->base;
    if (S->stacksize > STACK_INIT_SIZE && S->stacksize - length >= STACKINCREMENT) {
        S->base = (SElemType *)realloc(S->base, (S->stacksize - STACKINCREMENT) * sizeof(SElemType));
        if (S->base == NULL)
            return LOVERFLOW;
        S->top = S->base + length; //若S->base变化，则修正S->top的值
        S->stacksize -= STACKINCREMENT;
    }

    return OK;
}

/* 遍历栈 */
Status StackTraverse(SqStack S, Status(*visit)(SElemType e))
{
    int line_count; //在main中定义的打印换行计数器（与算法无关）
    SElemType *t = S.base;

    line_count = 0;     //计数器恢复初始值（与算法无关）
    while (t < S.top && (*visit)(*t) == TRUE)
        t++;

    if (t < S.top)
        return ERROR;

    printf("\n");//最后打印一个换行，只是为了好看，与算法无关
    return OK;
}

int station(string out, string in)
{
    SqStack sta;  //车站和入口
    SElemType elem;
    InitStack(&sta);
    int i, j;
    i = 0, j = 0;
    while (out[i] != 0)
    {
        if (GetTop(sta,&elem) && elem == out[i])
        {
            Pop(&sta, &elem);
        }
        else {//车站栈顶不等于//从入口循环读
            while (1) 
            {
                if (in[j] == 0) {//in 读到底
                    cout << "no" << endl;
                    return ERROR;
                }
                if (in[j] != out[i]) {
                    Push(&sta, in[j]);
                    j++;
                    continue;
                }
                if (in[j] == out[i]) {
                    j++;
                    break;
                }
            }//while end
        }//ifelse end
        i++;
    }//while end
    cout << "yes" << endl;

    return OK;
}

int main()
{
    string in, out;
    getline(cin, in);
    while (getline(cin, out))
    {
        station(out, in);
    }
    return 0;
}