#include <iostream>
using namespace std;

typedef struct node
{
	int data;
	struct node *next;
}node, *linklist;

linklist create_list(int n)//头插法建立链表
{
	struct node *L;
	L = (struct node *)malloc(sizeof(struct node));
	L->next = NULL;

	int x;
	int i = 0;
	while (i < n)
	{
		cin >> x;
		struct node *p;
		p = (struct node *)malloc(sizeof(struct node));
		p->data = x;
		p->next = L->next;
		L->next = p;
		i++;
	}
	return L;
}

void reverse(struct node *head)//逆置
{
	struct node *p, *s, *t;
	p = head;
	s = p->next;
	while (s->next != NULL)
	{
		t = s->next;
		s->next = p;
		p = s;
		s = t;
	}
	s->next = p;
	head->next->next = NULL; 
	head->next = s;
}

void display(struct node *head)//输出三的倍数
{
	struct node *p;
	p = head->next;
	while (p != NULL)
	{
		if (p->data % 3 == 0)
			cout << p->data << " ";
		p = p->next;
	}
	cout << endl;
}

int main()
{
	int n;
	cin >> n;
	linklist list, start;
	list = create_list(n);
	for (start = list->next; start != NULL; start = start->next)
	{
		cout << start->data << " ";
	}
	cout << endl;
	reverse(list);
	display(list);
	return 0;
}