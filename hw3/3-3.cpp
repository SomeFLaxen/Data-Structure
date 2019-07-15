#include<iostream>
using namespace std;

typedef struct node
{
	int data;
	struct node *next;
}node,*linklist;


/*尾插法建立链表*/

linklist create_list(int n)
{
	struct node *l;
	l = (struct node *)malloc(sizeof(struct node));
	l->next = NULL;
	struct node *r; r = l;
	int x, i = 0;
	while (i < n)
	{
		cin >> x;
		struct node *p;
		p = (struct node *)malloc(sizeof(struct node));
		p->data = x;
		r->next = p;
		r = p;
		i++;
	}
	r->next = NULL;
	return l;
}


/*去重*/
/*若有相同的data，则跳过该节点指向下一个节点*/
/*p->next=q->next*/

linklist RemoveDupNode(linklist L)//删除重复结点的算法
{
	linklist p, q, r;
	p = L->next;
	while (p)    // p用于遍历链表
	{
		q = p;
		while (q->next) // q遍历p后面的结点，并与p数值比较
		{
			if (q->next->data == p->data)
			{
				r = q->next; // r保存需要删掉的结点
				q->next = r->next;   // 需要删掉的结点的前后结点相接
				free(r);
			}
			else
				q = q->next;
		}
		p = p->next;
	}
	return L;
}


/*输出完整链表*/

void output(struct node *L)
{
	struct node *p;
	p = L->next;
	while (p != NULL)
	{
		cout << p->data << " ";
		p = p->next;
	}
	cout << endl;
}

int main()
{
	int n;
	cin >> n;
	struct node *head, *L;
	head = create_list(n);
	L = RemoveDupNode(head);
	output(L);
	return 0;
}