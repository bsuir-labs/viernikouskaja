#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <conio.h>
#include <algorithm>
#include <sstream>

using namespace std;

const int MAXN = 20000;
vector<int> g[MAXN];
int num[MAXN][MAXN];
int kol[MAXN];
int result[20000];
bool used[MAXN];
int timer, arrB[MAXN], arrA[MAXN];
int n;
int pol = 0;

void read();
void dfs(int v, int p);
void find_bridges();
void res(int a, int b, int i);
void Sort(int left, int right);

int main()
{
	for (int u = 0; u < MAXN; u++)
		kol[u] = 0;
	read();
	find_bridges();
	Sort(1, pol);
	ofstream out("bridges.out");
	out << pol << endl;
	for (int y = 1; y <= pol; y++)
		out << result[y] << " ";
	out << endl << endl;
	out.close();
	return 0;
}

void read()
{
	int Dorogi;
	int t1, t2;
	ifstream fin("bridges.in");
	fin >> n;
	fin >> Dorogi;
	for (int i = 0; i < Dorogi; i++)
	{
		if (fin.eof())
			break;
		fin >> t1;
		fin >> t2;
		--t1;
		--t2;
		g[t1].push_back(t2);	//������ ���������
		g[t2].push_back(t1);
		num[t1][kol[t1]] = i + 1; kol[t1]++;
		num[t2][kol[t2]] = i + 1; kol[t2]++;
	}
	fin.close();
}

void find_bridges()
{
	timer = 0;
	for (int i = 0; i < n; ++i)
		used[i] = false;
	for (int i = 0; i < n; ++i)
		if (!used[i])
			dfs(i,-1); //� �������
}

//v - ������� �� ������� ���������� �����; p - ������� � ������� ������� �����.
void dfs(int v, int p = -1)
{
	used[v] = true;
	arrB[v] = arrA[v] = timer++;
	for (size_t i = 0; i < g[v].size(); ++i)
	{
		int to = g[v][i];	//to ��� ������ ������� � ������� ������� V

		if (to == p)  continue; // ���� to - ������� � ������� ������� �����
		if (used[to])
			arrA[v] = min(arrA[v], arrB[to]);
		else
		{
			dfs(to, v);
			arrA[v] = min(arrA[v], arrA[to]);
			if (arrA[to] > arrB[v])
				res(v, to, i);
		}
	}
}

void res(int a, int b, int i)
{
	pol++;
	result[pol] = num[a][i];
}

void Sort(int left, int right)
{
	int i = left, j = right;
	int t, x;
	x = result[(i + j) / 2];
	do {
		while (result[i] < x && i < right) i++;
		while (result[j] > x && j > left) j--;
		if (i <= j) {
			t = result[i];
			result[i] = result[j];
			result[j] = t;
			i++; j--;
		}
	} while (i <= j);
	if (left < j) Sort(left, j);
	if (i < right) Sort(i, right);
}