#include<iostream>
using namespace std;

class L
{
private:
	int n, x;
	int ai[1000000], bi[1000000];
public:
	void input()
	{
		cin >> n;
		for (int i = 0; i < n; i++)
		{
			cin >> ai[i];
		}
		cin >> x;
	}

	void del()
	{

		int count = 0; int j = 0;
		for (int i = 0; i < n; i++)
		{
			if (ai[i] == x)
			{
				count++;
			}
			if (ai[i] != x)
			{
				bi[j] = ai[i]; j++;
			}
		}
		if (count == 0) cout << -1 << endl;
		else
		{
			for (int k = 0; k < n - count; k++)
			{
				cout << bi[k] << " ";
			}
			cout << endl;
		}
	}

}List;

int main()
{
	List.input();
	List.del();
	return 0;
}
