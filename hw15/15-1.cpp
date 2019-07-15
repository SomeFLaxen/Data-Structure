#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cmath>

using namespace std;

#define MAX_SIZE 200
int key_sum, mod, HT_size;
typedef char *Elemtype;
typedef struct
{
	Elemtype *elem;
}HashTable;

int letter[MAX_SIZE];
int _count[MAX_SIZE];

void CreateHashTable(HashTable &HT, Elemtype key, int r)
{
	int l;
	int k = 0;
	l = 37 % mod;

	for (int j = 0; j<strlen(key); j++)
	{
		key[j] = (key[j] >= 'a' && key[j] <= 'z') ? (key[j] - 'a' + 1) : (key[j] - 'A' + 1);
		k = k + (((int)key[j])* pow(l, strlen(key) - j - 1));
	}
	k = k % mod;
	int q = 1;
	while (1)
	{
		if (strlen(HT.elem[k]) == 0)
		{
			strcpy(HT.elem[k], key);
			letter[r] = k;
			_count[r] = q;
			break;
		}
		else
		{
			k++; q++;
			k = k%mod;
		}
	}
}

int main()
{
	HashTable HT;
	cin >> key_sum >> mod >> HT_size;
	Elemtype key;
	key = new char[MAX_SIZE];
	int i = 0;
	HT.elem = new char*[MAX_SIZE];
	for (i = 0; i<MAX_SIZE; i++)
	{
		HT.elem[i] = new char[MAX_SIZE];
		memset(HT.elem[i], '\0', sizeof(HT.elem[i]));
	}
	i = 1;
	while (i <= key_sum)
	{
		cin >> key;
		CreateHashTable(HT, key, i);
		i++;
	}
	for (int j = 1; j <= key_sum; j++)
	{
		cout << letter[j] << " ";
	}
	cout << endl;
	for (int j = 1; j <= key_sum; j++)
	{
		cout << _count[j] << " ";
	}
	return 0;
}