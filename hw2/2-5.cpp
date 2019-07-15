#include<iostream>
using namespace std;

class L
{
private:
	int n;
	int a[10000] = { 0 }, b[10000] = { 0 };
	int q = 0;

public:
	void input()
	{
		cin >> n;
		for (int i = 0; i < n; i++)
		{
			cin >> a[i];
		}
	}

	void RemoveSame()
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = i + 1; j < n; j++)
			{
				if (a[i] == a[j])
				{
					a[j] = 0;
				}
			}
		}

		for (int k = 0; k < n; k++)
		{
			if (a[k] != 0)
			{
				b[q] = a[k]; q++;
			}
		}
	}

	void output()
	{
		for (int i = 0; i < q; i++)
		{
			cout << b[i] << " ";
		}
		cout << endl;
	}
}List;

int main()
{
	List.input();
	List.RemoveSame();
	List.output();
	return 0;
}