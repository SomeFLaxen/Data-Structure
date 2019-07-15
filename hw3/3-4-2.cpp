#include <iostream>
using namespace std;
#define OK 1
#define ERROR -1
typedef int ElemType;
struct LNode
{
    int data;
    LNode *next;
};

struct DuLNode
{
    int data;
	DuLNode *prior;
	DuLNode *next;
};

class LinkList
{
private:
    LNode *head;
	LNode *tail;
	int len;
public:
    //单链表具体操作
LinkList(){head=new LNode;head->next=NULL;tail=head;len=0;}//构造函数

~LinkList(){if(len)ClearList_L();head=tail=NULL;}//析构函数

int ClearList_L(){
	LNode *p,*q;
	p=head;
	if(!(p->next))return ERROR;
	p=p->next;
	while(!p){
		q=p;
	    p=q->next;
		free(q);
	}
	tail=head;
	len=0;
	return OK;
}

int ListEmpty(){
	if(len==0) return NULL;
	else return OK;
}

void Create2_L(int n){
	LNode *p,*q;
	q=head;
	for(int i=0;i<n;i++){
		p=new LNode;
		cin>>p->data;
		q->next=p;
		q=p;
	}
	q->next=NULL;
	tail=q;
	len=n;
}//尾插法建立长度为n的单链表

void MergeList_L(LinkList &La,LinkList &Lb){
	LNode *pa=La.head->next;
	LNode *pb=Lb.head->next;
	LNode *pc,*p;
	pc=head;
	while(pa&&pb){
		if(pa->data <= pb->data){
			p=new LNode;
			p->data=pa->data;
			pc->next=p;
			pc=p;
			pa=pa->next;
		}
		else{
			p=new LNode;
			p->data=pb->data;
			pc->next=p;
			pc=p;
			pb=pb->next;
		}
	}
	while(pa){
		p=new LNode;
		p->data=pa->data;
		pc->next=p;
		pc=p;
		pa=pa->next;
	}
	while(pb){
		p=new LNode;
		p->data=pb->data;
		pc->next=p;
		pc=p;
		pb=pb->next;
	}
	tail=pc;
	len=La.len+Lb.len;
	La.ClearList_L();
	Lb.ClearList_L();
}

void Print(){
	if(len==0){
		cout<<"当前链表为空"<<endl;
	}
	else{
		cout<<"当前链表为：";
	    LNode *p=head;
	    for(int i=0;i<len;i++){
		    p=p->next;
		    cout<<p->data<<" ";
	    }
	    cout<<endl;
	}
}

int main()
{
	LinkList L,*p,L1,L2,L3;
	int i,e;
	p=&L;
	L3.ClearList_L();
	int n1,n2;
    cin>>n1;
    L1.Create2_L(n1);
	cin>>n2;
	L2.Create2_L(n2);
	L3.MergeList_L(L1,L2);
	L3.Print();

	return 0;
}