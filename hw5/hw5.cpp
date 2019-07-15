#include <iostream>
#include <stdio.h>
#include <string>
using namespace std;

class SListNode {
public:
	string data;
	int cur;
};

class SList {
private:
	SListNode *s;
	int ListLen;
public:
	SList();
	~SList();
	void CreateList();//建立链表
	void ShowList();//输出数组中所有元素
	void PrintList();//打印链表
	void ListInsert();//插入元素
	void DeleteElem();//删除元素
	void LocateElem();//定位元素
	void AddElem();//在尾部追加元素
};

SList::SList()
{
	int m;
	cin >> m;
	s = new SListNode[m];
	ListLen = m;
	s[0].cur = -1;
	s[1].cur = 2;
	for (int i = 2; i < m - 1; i++)
	{
		s[i].cur = i + 1;
	}
	s[m - 1].cur = -1;
}

SList::~SList()
{
	delete[] s;
}

void SList::CreateList()
{
	int n;
	string str;
	cin >> n;
	if (n > ListLen - 2)n = ListLen - 2;
	for (int i = 0; i < n; i++)
	{
		cin >> str;
		int k = 0;
		while (s[k].cur != -1)
		{
			k = s[k].cur;
		}
		s[k].cur = s[1].cur;
		s[1].cur = s[s[1].cur].cur;
		s[s[k].cur].data = str;
		s[s[k].cur].cur = -1;
	}
	cin.clear();
	cin.ignore(1024,'\n');
	
}

void SList::ShowList()
{
	int k = 0, count = 0;
	while (k < ListLen)
	{
		cout << k << " : ";
		if (s[k].data == "") cout << "N/A";
		else cout << s[k].data;
		cout << " : " << s[k].cur << "\t\t";
		k++;
		if (k % 3 == 0)cout << endl;
	}
	if (k % 3 != 0)cout << endl;
}

void SList::ListInsert()
{
	int pos, i, k = 0;
	string x;
	cin >> pos >> x;
	
	if (s[1].cur == -1)
	{
		cout << "FULL" << endl;
		return;
	}
	for (i = 0; i < pos - 1; i++)
	{
		k = s[k].cur;
		if (k == -1)
		{
			cout << -1 << endl;
			return;
		}
	}
	int tmp = s[k].cur;
	s[k].cur = s[1].cur;
	s[1].cur = s[s[1].cur].cur;
	s[s[k].cur].data = x;
	s[s[k].cur].cur = tmp;

	PrintList();
}

void SList::PrintList()
{
	int k = s[0].cur;
	while (k != -1)
	{
		cout << s[k].data << " ";
		k = s[k].cur;
	}
	cout << endl;
}

void SList::DeleteElem()
{
	int pos=-1, k = 0, i;
	cin >> pos;
	if (s[0].cur == -1)
	{
		cout << "EMPTY" << endl;
		return;
	}
	for (i = 0; i < pos - 1; i++)
	{
		k = s[k].cur;
		if (s[k].cur == -1)
		{
			cout << -1 << endl;
			return;
		}
	}
	cout << s[s[k].cur].data << endl;
	int tmp = s[s[k].cur].cur;
	s[s[k].cur].cur = s[1].cur;
	s[1].cur = s[k].cur;

	s[k].cur = tmp;

	//PrintList();
}

void SList::LocateElem()
{
	string x;
	cin >> x;
	int k = s[0].cur, i = 0;
	while (k != -1)
	{
		i++;
		if (s[k].data == x)
		{
			cout << i << endl;
			return;
		}
		k = s[k].cur;
	}
	cout << -1 << endl;
}

void SList::AddElem()
{
	string str;
	cin >> str;
	if (s[1].cur == -1)
	{
		cout << "FULL" << endl;
		return;
	}
	int k = 0;
	while (s[k].cur != -1)
	{
		k = s[k].cur;
	}
	s[k].cur = s[1].cur;
	s[1].cur = s[s[1].cur].cur;
	s[s[k].cur].data = str;
	s[s[k].cur].cur = -1;
	PrintList();
}

int main()
{
	SList s;

	s.CreateList();
	s.ShowList();
	s.ListInsert();
	s.DeleteElem();
	s.LocateElem();
	s.AddElem();
	s.ShowList();

	return 0;
}