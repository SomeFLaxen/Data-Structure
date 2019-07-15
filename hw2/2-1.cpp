#include<iostream>
using namespace std;
#define LIST_INIT_SIZE 10000
#define LISTINCREMENT 10
#define ERROR -1
#define OK 0
typedef int ElemType;


class SqList {
public:
	SqList() {
		elem = new ElemType[LIST_INIT_SIZE];
		if (!elem)exit(1);
		length = 0;
		listsize = LIST_INIT_SIZE;
	}
	~SqList() {}
	int SqList_Length() {
		return length;
	}

	int *get_elem() { return elem; }
	int SqList_Create(int n);
	int ListInsert_Sq(int i, ElemType e);
	int ListDelete_Sq(int i, ElemType &e);
	int LocateElem_Sq(ElemType e);
	int Delete_Sq(ElemType x);
	int DeleteAll_Sq(ElemType x);
	void OutputList_Sq();
	void ClearList_Sq();
private:
	ElemType *elem;
	int length;
	int listsize;
};

/*建立顺序表*/
int SqList::SqList_Create(int n) {
	int i, *p;
	p = elem;
	for (i = 0; i<n; i++)cin >> *p++;
	length = n;
	return OK;
}//SqList_Create;

int SqList::ListInsert_Sq(int i, ElemType e) {
	//i的合法值为1≤i≤Length+1
	int *newbase, *p, *q;
	if (i<1 || i>length + 1) return ERROR;   //i值不合法
	if (length >= listsize) {
		newbase = new ElemType[LISTINCREMENT];
		if (!newbase)exit(1);
		elem = newbase;
		listsize += LISTINCREMENT;
	}
	q = &(elem[i - 1]);
	for (p = &(elem[length - 1]); p >= q; --p) *(p + 1) = *p;
	*q = e;
	++(length);
	return OK;   //成功插入元素，返回0
}//ListInsert_Sq;

int SqList::ListDelete_Sq(int i, ElemType &e) {
	//i的合法值为1≤i≤Length
	int *p, *q;
	if ((i<1) || (i>length)) return ERROR;   //i值不合法
	p = &(elem[i - 1]);
	e = *p;
	q = elem + length - 1;
	for (++p; p <= q; ++p) *(p - 1) = *p;
	--(length);
	return OK;
}//ListDelete_Sq;

int SqList::LocateElem_Sq(ElemType e) {
	//若找到，则返回其在L中的位序，否则返回ERROR
	int i = 1, *p;
	p = elem;
	while (i <= length&&*p++ != e) ++i;
	if (i <= length) return i;
	else return ERROR;
}//LocatElem_Sq;

void SqList::OutputList_Sq() {
	int i, *p;
	p = elem;
	if (length == 0) {
		system("pause");
	}
	else {
		for (i = 0; i < length; i++) {
			cout << *p++ << " ";
		}
		cout << endl;
	}
}//OutputList_Sq;

void SqList::ClearList_Sq() {
	length = 0;
	cout << "已清空" << endl;
}

int SqList::Delete_Sq(ElemType x) {
	int i, e;
	i = LocateElem_Sq(x);
	if (i == ERROR) return ERROR;
	if (ListDelete_Sq(i, e) == OK) return OK;
	return ERROR;
}

int SqList::DeleteAll_Sq(ElemType x) {
	int i, e, q, *p;
	p = elem;
	for (i = 1; i <= length; i++)
		if (*p++ == x) {
			q = ListDelete_Sq(i, e);
			--i;
			--p;
		}
	if (q == OK&&e == x) return OK;
	else
		return ERROR;
}

int main()
{
	int n, i, e;
	SqList L, *p = &L;

	cin >> n;
	p->SqList_Create(n);
	p->OutputList_Sq();

	cin >> i >> e;
	if (p->ListInsert_Sq(i, e) == OK)
	{
		p->OutputList_Sq();
	}
	else cout << -1 << endl;

	cin >> i;
	if (p->ListDelete_Sq(i, e) == OK)
	{
		p->OutputList_Sq();
	}
	else cout << -1 << endl;

	cin >> e;
	i = p->LocateElem_Sq(e);
	if (i == ERROR)
	{
		cout << -1 << endl;
	}
	else cout << i << endl;

	return 0;
}