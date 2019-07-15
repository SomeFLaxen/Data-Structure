#include<iostream>
using namespace std;

typedef struct Node
{
	int data;
	struct Node *next;//单链表的指针域
}Node,*linklist;

linklist initial_list(linklist L)//初始化
{
	L = (Node *)malloc(sizeof(Node));//申请节点空间
	if (L == NULL)
		exit(OVERFLOW);
	L->next = NULL;
	return L;
}

linklist create_list(int n)//头插法
{
	Node *L;
	L = (Node *)malloc(sizeof(Node));
	L->next = NULL;

	int x;
	int i = 0;
	while (i < n)
	{
		cin >> x;
		Node *p;
		p = (Node *)malloc(sizeof(Node));
		p->data = x;
		p->next = L->next;
		L->next = p;
		i++;
	}
	return L;
}

/*在第i个位置插入x*/
int insert_elem(linklist L, int i, int x)
{
	Node  *p, *q;
	p = L;
	int pos = 0;

	/*查找第i-个节点*/
	while (p && pos < i - 1)
	{
		p = p -> next;
		pos++;
	}

	if (p == NULL || pos > i - 1)
		return -1;

	q = (struct Node *)malloc(sizeof(struct Node));
	if (q == NULL)
		return 0;
	q->data = x;
	q->next = p->next;
	p->next = q;

	return 1;
}

/*删除第j个元素*/
/*若位置不合法输出-1，否则全部输出*/
int delete_elem(linklist L, int j, int n)
{
	int pos = 0;
	Node  *q, *p;
	p = L;

	/*查找第j个节点*/
	while (p->next && pos < j - 1)
	{
		p = p->next;
		pos++;
	}
	if (p->next == NULL || pos > j - 1)
		return -1;

	/*此时p指向第i-1个节点*/
	q = p->next;
	p->next = q->next;
	free(p);

	return 1;
}

/*查找整数y*/
linklist find_elem(linklist L, int y)
{
	Node *p;
	p = L;
	int pos = 1;
	for (pos = 1;; pos++)
	{
		if (p != NULL)
		{
			if (p->data == y)
			{
				cout << pos << endl;
				break;
			}
		}
		else
			break;
	}
}


int main()
{
	int n;
	cin >> n;

	linklist list, start;
	int i, x, j, y;
	list = create_list(n);
	for (start = list->next; start != NULL; start = start->next)
	{
		cout << start->data << " ";
	}
	cout << endl;

	cin >> i >> x;
	insert_elem(list, i, x);
	for (start = list->next; start != NULL; start = start->next)
		cout << start->data << " ";
	cout << endl;

	cin >> j;
	delete_elem(list, j, n);
	for (start = list->next; start != NULL; start = start->next)
		cout << start->data << " ";
	cout << endl;

	cin >> y;
	find_elem(list, y);

	return 0;
}