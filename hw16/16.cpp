#include<iostream>
#include <cstdlib>
using namespace std;
#define MAXSIZE 1000000
typedef int Keytype;
typedef struct {
	Keytype key;
	int inof;
}RecordType;//元素类型
typedef struct {
	RecordType r[MAXSIZE + 1];//0闲置
	int length;
}sqlist;//顺序表
void initial(sqlist&L)
{
	cin >> L.length;
	for (int i = 1; i<=L.length; i++)
	{
		cin >> L.r[i].key;
	}
}
//直接插入排序
void InsertSort(sqlist&L)
{
	int j, i;
	for (i = 2; i <= L.length; i++)
	{
		if (L.r[i].key <= L.r[i - 1].key)
		{
			L.r[0] = L.r[i];
			L.r[i] = L.r[i - 1];
			for (j = i - 2; L.r[0].key <= L.r[j].key; j--)
				L.r[j + 1] = L.r[j];
			    L.r[j + 1] = L.r[0];
		}
	}
}
//折半插入排序
void BinsertSort(sqlist&L)
{
	int m = 0;
	for (int i = 2; i <= L.length; i++)
	{
		L.r[0] = L.r[i];//仅仅只是暂时存储
		int low = 1;
	    int high = i - 1;
		while (low <= high)
		{
			m = (low + high) / 2;
			if (L.r[0].key <= L.r[m].key)

				high = m - 1;
			else
				low = m + 1;
		}
		for (int j = i - 1; j >= high + 1; j--)
			L.r[j + 1] = L.r[j];
		L.r[high + 1] = L.r[0];
	}
}
//希尔排序
void ShellInsert(sqlist &L, int gap)
{
	int j = 0;
	for (int i = gap + 1; i <= L.length; ++i)
	{
		{if (L.r[i].key < L.r[i - gap].key)
		{
			L.r[0] = L.r[i];
			for (j = i - gap; j > 0 && (L.r[0].key < L.r[j].key);
				j -= gap)
				L.r[j + gap] = L.r[j]; //记录后移
			L.r[j + gap] = L.r[0];
		}
		}
	}
}
void ShellSort(sqlist&L, int dlta[], int t)
{//做t趟希尔排序；t是数组的大小，数组放增量序列，保证最后一个是1
	for (int i = 0; i < t; ++i)
		ShellInsert(L, dlta[i]);
}
//冒泡排序
void BubbleSort(sqlist &L)
{
	int flag = 1;
	for (int i = L.length; flag&&i >= 2; i--)
	{
		flag = 0;
		for (int j = 1; j < i; j++)
			if (L.r[j + 1].key <= L.r[j].key)
			{
				int temp = L.r[j + 1].key;
				L.r[j + 1].key = L.r[j].key;
				L.r[j].key = temp;
				flag = 1;
			}
	}
}
//快速排序
int Partition(sqlist &L,int low,int high)
{
	L.r[0] = L.r[low];
	int pivotkey = L.r[low].key;//取出来，访问时快些
	while (low < high)
	{
		while (low < high&&L.r[high].key >= pivotkey)
			high--;
		L.r[low] = L.r[high];//while退出后执行
		while (low < high&&L.r[low].key <= pivotkey)
		{
			low++;
		}
		L.r[high] = L.r[low];
	}
	L.r[low] = L.r[0];//基准元素到位
	return low;//返回基准位置下标
}
void QSort(sqlist &L, int low, int high)
{
	if (low < high)
	{
		int pivotloc = Partition(L, low, high);
		QSort(L, low, pivotloc - 1);//左半区
		QSort(L,  pivotloc +1,high);//右半区
	}
}
void QuickSort(sqlist &L)
{
	QSort(L, 1, L.length);
}
//选择排序
void SelectSort(sqlist &L)
{
	for (int i = 1; i < L.length; ++i)
	{
		int k = i;
		for (int j = i + 1; j <= L.length; ++j)
			if (L.r[k].key > L.r[j].key) k = j;
		if (i != k) {
			RecordType temp = L.r[i];
			L.r[i] = L.r[k];
			L.r[k] = temp;
		}
	}
}
//归并排序
void Merge(RecordType SR[], RecordType TR[], int i,int m, int n)
{
	int k = 0,j=0;
	for ( j = m + 1, k = i; i <= m && j <= n; ++k) {
		if (SR[i].key<SR[j].key)
			 TR[k] = SR[i++];
		else TR[k] = SR[j++];
	}
	if (i<=m)
		for (int n1 = k, n2 = i; n1<= n &&n2 <= m; n1++, n2++)
			TR[n1] = SR[n2];
	if (j<=n)
		for (int n1 = k, n2 = j; n1 <= n &&n2 <= n; n1++, n2++)
			TR[n1] = SR[n2];
}
void MSort(RecordType SR[], RecordType TR1[], int s, int t) 
{
	RecordType TR2[MAXSIZE];
	if (s==t) TR1[s] = SR[s];
	else {
		int m = (s + t) / 2;
		MSort(SR, TR2, s, m);
		MSort(SR, TR2, m+1, t);
		Merge(TR2, TR1, s, m, t);
	}
}
void MergeSort(sqlist &L)
{
	MSort(L.r, L.r, 1, L.length);
}
//堆排序
void HeapAdjust(sqlist&H, int s, int m)
{
	RecordType T;
	T = H.r[s];
	for (int j = 2 * s; j <= m; j *= 2) {
		if (j < m&&H.r[j].key <= H.r[j + 1].key)
			j++;//如果右子树大，则选择右子树
		if (!(T.key<H.r[j].key))//s为插入位置
			break;
		H.r[s] = H.r[j];//根等于左右子树中大的（不是交换）
		s = j;//s成为子树的根
	}
	H.r[s] = T;
}
void HeapSort(sqlist &H)
{
	RecordType T;
	for (int i = H.length / 2; i > 0; i--)
	{
		HeapAdjust(H, i, H.length);
	}
	for (int i = H.length; i > 1; i--)
	{
		T = H.r[1];
		H.r[1] = H.r[i];
		H.r[i] = T;
		HeapAdjust(H, 1,i-1);//前i-1个调整为堆
	}
}
void print(sqlist&L)
{
	for (int i = 1; i <=L.length; i++)
	{
		cout << L.r[i].key << " ";
	}
}
int main()
{
	sqlist L;
	initial(L);
	int a[100];
	int k =0;
	for (int i=L.length / 2; i >=1; i=i/2)
	{
		a[k++] = i;
	}
	ShellSort(L, a, k);
	//QuickSort(L);
	//SelectSort(L);
	print(L);
	return 0;

}