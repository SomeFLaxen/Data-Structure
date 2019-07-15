#include<iostream>
using namespace std;

class L
{
private:
	int LA[10000], LB[10000], LC[10000] = { 0 };
	int n = 0, m = 0;

public:
	void Input()
	{
		int temp1, temp2;
		for (int i = 0;; i++)
		{
			cin >> temp1;
			if (temp1 != 0)
			{
				LA[i] = temp1;
				n++;
			}
			else break;
		}

		for (int j = 0;; j++)
		{
			cin >> temp2;
			if (temp2 != 0)
			{
				LB[j] = temp2;
				m++;
			}
			else break;
		}
	}

	void SortList()
	{
		int temp;
		for (int i = 0; i < n - 1; i++)
		{
			for (int j = 0; j < n - 1 - i; j++)
			{
				if (LA[j] > LA[j + 1])
				{
					temp = LA[j];
					LA[j] = LA[j + 1];
					LA[j + 1] = temp;
				}
			}
		}

		for (int i = 0; i < m - 1; i++)
		{
			for (int j = 0; j < m - 1 - i; j++)
			{
				if (LB[j] > LB[j + 1])
				{
					temp = LB[j];
					LB[j] = LB[j + 1];
					LB[j + 1] = temp;
				}
			}
		}
	}

	void LinkList()
	{
		int i=0,j=0,k=0;
		while (i<n && j<m)
		{
			if (LA[i]<=LB[j])
				LC[k++]=LA[i++];
			else
				LC[k++]=LB[j++];
		}
		while (i<n) LC[k++]=LA[i++];
		while (j<m) LC[k++]=LB[j++];
	}

	void Output()
	{
		for (int i = 0; i<n+m; i++)
		{
			cout << LC[i] << " ";
		}
		cout << endl;
	}
} List;

int main()
{
	List.Input();
	List.SortList();
	List.LinkList();
	List.Output();
	return 0;
}