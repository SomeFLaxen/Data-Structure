#include<iostream>
using namespace std;

struct node
{
	int data;
	struct node *next;
} *head, *tail, *p, *q;

int main()
{

	/*建立循环链表*/
	int n, m, i, k;
	head = (struct node *)malloc(sizeof(struct node));
	head->data = 1;
	tail = head;	
	/*从第k个人开始，每m个人报数*/
	cin >> n >> k >> m;
	for (i = 2; i <= n; i++)
	{
		p = (struct node *)malloc(sizeof(struct node));
		p->next = NULL;
		p->data = i;
		tail->next = p;
		tail = p;
	}
	tail->next = head;
	q = tail;  // 指向head前边那个节点


	int num = 0;
	while (q->next != q)//当循环链表元素数量大于一
	{
		p = q->next;
		num++;
		if (num % m == 0)
		{
			q->next = p->next;
			//cout << (p->data + k - 1) % n << " ";

			if (p->data + k - 1 <= n)
				cout << p->data + k - 1 << " ";
			else
				cout << (p->data + k - 1) % n << "";
			free(p);
		}
		else
		{
			q = p;
		}
	}
	cout << (q->data + k - 1) % n << endl; // 输出的是q->data,因为之前是用q进行的游动
	return 0;
}