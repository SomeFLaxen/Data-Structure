#include<iostream>
using namespace std;

typedef struct node
{
	int data;
	struct node *next;
}node, *linklist;


void create_list(node *l)//尾插法
{
	struct node *p1, *p2;
	p1 = l;
	int flag = 1, x;
	while (flag)
	{
		cin >> x;
		if (x != 0)
		{
			p2 = (struct node *)malloc(sizeof(struct node));
			p2->data = x;
			p1->next = p2;
			p1 = p2;
		}
		else
		{
			flag = 0;
			p1->next = NULL;
		}
	}
}


void merge_list(node *la, node *lb)
{
	struct node *head;
	head = (struct node*)malloc(sizeof(struct node));
	head->next = NULL;

	/*生命两个指针分别指向两个链表的头指针*/
	struct node *p1 = la->next;
	struct node *p2 = lb->next;

	/*声明一个指针指向最后一个节点，开始时指向head*/
	node *last = head;

	while (p1 != NULL && p2 != NULL)
	{
		/*p1数据小，则将p1节点放入新链表，
		last和p1分别后移，p2不变*/
		if (p1->data < p2->data)
		{
			last->next = p1;
			p1 = p1->next;
			last = p1;
		}

		else
		{
			last->next = p2;
			p2 = p2->next;
			last = p2;
		}
	}

	/*有一个链表未结束时，
	将last直接指向未结束的链表的头指针*/
	last->next = p1 ? p1 : p2;
	
	struct node *p = head;
	p = (struct node *)malloc(sizeof(struct node));
	while (p)
	{
		cout << p->data << " ";
		p = p->next;
	}
}



int main()
{
	linklist l1, l2;
	l1 = (struct node *)malloc(sizeof(struct node));
	l1->next = NULL;
	l2 = (struct node *)malloc(sizeof(struct node));
	l2->next = NULL;
	create_list(l1);
	create_list(l2);
	merge_list(l1, l2);

	return 0;
}