#include <iostream>
#include <string>
using namespace std;
#define MAXSIZE 10000
class List {
public:
	List(); 				// 构造函数  
	List(int size); 			// 含参构造函数 - 创建最大长度为 size 的静态链表 
	int Size() const; 		// 返回链表的长度 
	bool IsFull() const; 		// 返回链表是否已满  
	bool IsEmpty() const; 	// 返回链表是否已空  
	void Clear(); 			// 清空链表 
	void Print();           // 输出链表
	void Print2();
	int Retrieve(int position, string &x); 		// 获取链表第 position 位置的元素到 x ，成功返回 0 ，否则返回 -1 
	int Replace(int position, const string &x); 	// 将链表第 position 位置的元素换为 x ，成功返回 0 ，否则返回 -1 
	int Remove(int position, string &x); 		// 获取并删除链表第 position 位置的元素，成功返回 0 ，否则返回 -1 
	int Insert(int position, const string &x); 	// 将元素 x 插入到链表第 position 位置，成功返回 0 ，否则返回 -1 
	int Append(const string &x); 			// 将元素 x 追加到链表尾部，成功返回 0 ，否则返回 -1
private:
	struct LNode {
		string data;
		int cur;
	};
	LNode *sls;
	int maxlen;
};

List::List() {
	int i;
	sls = new LNode[MAXSIZE + 2];
	sls[0].cur = sls[1].cur = -1;
	sls[0].data = "N/A";
	for (i = 1; i<MAXSIZE + 2; i++) {
		sls[i].cur = i + 1;
		sls[i].data = "N/A";
	}
	sls[MAXSIZE + 1].cur = -1;
	maxlen = MAXSIZE;
}

List::List(int size)
{
	int i;
	sls = new LNode[size + 2];
	sls[0].cur = sls[1].cur = -1;
	sls[0].data = "N/A";
	for (i = 1; i<size + 2; i++) {
		sls[i].cur = i + 1;
		sls[i].data = "N/A";
	}
	sls[size + 1].cur = -1;
	maxlen = size;
}

int List::Size()const {
	int i, j = 0;
	for (i = sls[0].cur; i<maxlen + 2 && sls[i].data != "N/A"; i = sls[i].cur) {
		++j;
	}
	return j;
}

bool List::IsFull()const {
	if (sls[1].cur == -1)return 1;
	else return 0;
}

bool List::IsEmpty()const {
	if (sls[0].cur == -1)return 1;
	else return 0;
}

void List::Clear() {
	sls[0].cur = sls[1].cur = -1;
	sls[0].data = "N/A";
	for (int i = 1; i<maxlen + 2; i++) {
		sls[i].cur = i + 1;
		sls[i].data = "N/A";
	}
	sls[maxlen + 1].cur = -1;
}

void List::Print() {
	int i, j = 0;
	for (i = 0; i<maxlen +2; i++) {
		cout << i << " : " << sls[i].data << " : " << sls[i].cur << '\t';
		++j;
		if (j % 3 == 0)cout << endl;
	}
}

void List::Print2()
{
	for (int i = 0; sls[i].cur != -1;)
	{
		i = sls[i].cur;
		cout << sls[i].data << ' ';
	}
	cout << endl;
}

int List::Retrieve(int position, string &x) {
	if (sls[position + 1].data == "N/A" || position>maxlen || position<1)return -1;
	x = sls[position + 1].data;
	return 0;
}

int List::Replace(int position, const string &x) {
	if (sls[position + 1].data == "N/A" || position>maxlen || position<1)return -1;
	else {
		sls[position + 1].data = x; return 0;
	}
}

int List::Remove(int position, string &x) {
	int i;
	if (IsEmpty() == 1)
	{
		cout << "EMPTY" << endl;
		return -1;
	}
	if (sls[position + 1].data == "N/A" || position>maxlen || position<1)return -1;
	else {
		for (i = 0; sls[i].cur != position + 1; i = sls[i].cur);
		sls[i].cur = sls[position + 1].cur;
		x = sls[position + 1].data;
		sls[position + 1].data = "N/A";
		for (i = 1; sls[i].cur != -1 && sls[i].cur<position + 1;)i = sls[i].cur;
		if (sls[i].cur == -1) {
			sls[i].cur = position + 1;
			sls[position + 1].cur = -1;
		}
		else {
			sls[position + 1].cur = sls[i].cur;
			sls[i].cur = position + 1;
		}
		return 0;
	}
}

int List::Insert(int position, const string &x) {
	int i, j;
	if (sls[position + 1].data == "N/A" || position>maxlen || position<1 || sls[1].cur == -1)return -1;
	else {
		i = sls[1].cur; sls[1].cur = sls[i].cur;
		sls[i].data = x;
		for (j = 0; sls[j].cur != position + 1; j = sls[j].cur);
		sls[i].cur = sls[j].cur;
		sls[j].cur = i;
		return 0;
	}
}

int List::Append(const string &x) {
	int i, j;
	if (IsFull() == 1)
	{
		cout << "FULL";
		return -1;
	}
	else {
		for (i = 0; sls[i].cur != -1; i = sls[i].cur);
		j = sls[1].cur; sls[1].cur = sls[j].cur;
		sls[j].data = x;
		sls[j].cur = -1;
		sls[i].cur = j;
	}
}

int main() 
{
	int m, n; cin >> m >> n;	
	List L(m - 2);
	string s;
	for (int k = 0; k < n; k++)
	{
		cin >> s;
		L.Append(s);
	}
	L.Print();

	int i1; string x1;
	cin >> i1 >> x1;
	L.Insert(i1, x1);
	L.Print2();
	
	int i2; cin >> i2;
	string x2;
	L.Remove(i2, x2);
	cout << x2 << endl;

	string y; cin >> y;
	int i3 = 0;
	string x;
	for (i3 = 1; i3 < m; i3++)
	{
		if (L.Retrieve(i3, x) == 0 && x == y)
			cout << i3 << endl;
	}

	string x4;
	cin >> x4;
	L.Append(x4);
	L.Print2();

	L.Print();
	
	return 0;
}