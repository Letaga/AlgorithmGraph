/*Кураева А.В. 22ПМ
Лабораторная 4, Алгоритмы на графах*/

#include <iostream>
#include <vector>

using namespace std;

void PrimKrus();
void AlgPrKr(vector<vector<int>> Graph);

int EntrEdge(int x, int l, int r) //Checking the validity of values
{
	cin >> x;
	while (x < l || x > r)
	{
		cout << "Введите другое число\n";
		cin >> x;
	}
	return x;
}

int main()
{
	setlocale(LC_ALL, "Ru");

	PrimKrus();
}

void PrimKrus()
{
	int size = 0;
	cout << "Алгоритм Прима-Краскала\n\nВведите колличество вершин графа\n";
	size = EntrEdge(size, 2, INT_MAX);

	vector<vector<int>> Graph(size, vector<int>(size));
	int* Colour = new int[size];

	for (int i = 0; i < size; i++)
	{
		Colour[i] = i + 1;
		for (int j = 0; j < size; j++)
			Graph[i][j] = 0;
	}

	cout << "Ведите расстояния мажду вершинами\nЕсли дороги нет - введите '-1'\n";
	for (int i = 0; i < size; i++)
	{
		if (i != size - 1)
			cout << "-- Из " << i + 1 << "-й вершины --\n";
		for (int j = i; j < size; j++)
		{
			if (i == j) Graph[i][j] = INT_MAX;
			else
			{
				cout << "В " << j + 1 << "-ю\n";
				while (Graph[i][j] == 0)
				{
					Graph[i][j] = EntrEdge(Graph[i][j], -1, INT_MAX / 2);
					if (Graph[i][j] == -1)
						Graph[i][j] = INT_MAX;
					Graph[j][i] = Graph[i][j];
				}
			}
		}

	}


	AlgPrKr(Graph);

	cout << "\n\nGraph\n";
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (Graph[i][j] == INT_MAX)
				cout << "-\t";
			else
				cout << Graph[i][j] << "\t";
		}
		cout << endl << endl;
	}
}

void AlgPrKr(vector<vector<int>> Graph)
{
	int size = Graph.size();
	int sum = 0;
	int* Colour = new int[size-1];
	vector<vector<int>> OstTree(3, vector<int>(size));
	
	for (int i = 0; i < size; i++)
	{
		Colour[i] = i + 1;
	}

	for (int k = 0; k < size-1; k++)
	{
		int iMin = 0, jMin = 1, c = 0;
		while (c == 0)
		{
			for (int i = 0; i < size; i++)
			{
				for (int j = i; j < size; j++)
				{
					if (Graph[i][j] < Graph[iMin][jMin])
					{
						iMin = i;
						jMin = j;
					}
				}
			}

			if (Colour[iMin] != Colour[jMin])
			{
				Colour[iMin] = Colour[jMin];
				OstTree[0][k] = Graph[iMin][jMin];
				OstTree[1][k] = iMin;
				OstTree[2][k] = jMin;

				Graph[iMin][jMin] = INT_MAX;
				c++;
			}
			
		}
	}
	cout << "\n Остовное дерево\n";
	for (int i = 0; i < size - 1; i++)
	{
		cout << OstTree[1][i] + 1 << " -> " << OstTree[2][i] + 1 << " size: " << OstTree[0][i];
		cout << endl;
		sum += OstTree[0][i];
	}
	cout << "Сумма рёбер остовного дерева: \n" << sum;
}
