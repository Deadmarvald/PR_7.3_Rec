// Lab_07_3(Rec).cpp
// Вольвенко Іван
// Лабораторна робота № 7.3
// Опрацювання динамічних багатовимірних масивів ітераційними способами.
// Варіант 13

#include <iostream>
#include <iomanip>
#include <time.h>
#include <cmath>
#include <windows.h>

using namespace std;

void PrintRow(int** mas, const int rowNo, const int N, int colNo)
{
	cout << setw(4) << mas[rowNo][colNo];

	if (colNo < N - 1)
		PrintRow(mas, rowNo, N, colNo + 1);
	else
		cout << endl;
}
void PrintRows(int** mas, const int K, const int N, int rowNo)
{
	PrintRow(mas, rowNo, N, 0);

	if (rowNo < K - 1)
		PrintRows(mas, K, N, rowNo + 1);
	else
		cout << endl;
}

void CreateRow(int** mas, const int rowNo, const int N, const int Low, const int High, int colNo)
{
	mas[rowNo][colNo] = Low + rand() % (High - Low + 1);

	if (colNo < N - 1)
		CreateRow(mas, rowNo, N, Low, High, colNo + 1);
}

void CreateRows(int** mas, const int K, const int N, const int Low, const int High, int rowNo)
{
	CreateRow(mas, rowNo, N, Low, High, 0);

	if (rowNo < K - 1)
		CreateRows(mas, K, N, Low, High, rowNo + 1);
}

void MovingRight(int** mas, const int K, const int N, int x, int tmp, int p, int i, int j)
{
	if (x > N)
		x = (x % N);

	if (p < x)
	{
		if (i < K)
		{
			tmp = mas[i][N - 1];
			if (j > 0)
			{
				mas[i][j] = mas[i][j - 1];
				MovingRight(mas, K, N, x, tmp, p, i, j - 1);
			}
			else
				MovingRight(mas, K, N, x, tmp, p, i + 1, N - 1);
			mas[i][0] = tmp;
		}
		else
			MovingRight(mas, K, N, x, tmp, p + 1, 0, N - 1);
	}
}

void MovingDown(int** mas, const int K, const int N, int x, int tmp, int p, int i, int j)
{
	if (x > K)
		x = (x % K);

	if (p < x)
	{
		if (j < N)
		{
			tmp = mas[K - 1][j];
			if (i > 0)
			{
				mas[i][j] = mas[i - 1][j];
				MovingDown(mas, K, N, x, tmp, p, i-1, j);
			}
			else
				MovingDown(mas, K, N, x, tmp, p, K-1, j+1);
			mas[0][j] = tmp;
		}
		else
			MovingDown(mas, K, N, x, tmp, p + 1, K-1, 0);
	}
}

int FindRow(int** mas, const int K, const int N, int m, int q, int t, int i, int j)
{
	if (i < K)
	{
		if (j < N)
		{
			if (mas[i][j] == 0)
				m++;
			if (m > q)
			{
				q = m;
				t = i;
				FindRow(mas, K, N, m, q, t, i, j + 1);
			}
			else
				FindRow(mas, K, N, m, q, t, i, j + 1);
		}
		else
			FindRow(mas, K, N, 0, q, t, i + 1, 0);
	}
	else
		return t+1;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	srand((unsigned)time(NULL));

	int Low = 0;
	int	High = 1;

	int K, N, x;
	bool TrueFalse;
	
	cout << "K = "; cin >> K;
	cout << "N = "; cin >> N;
	cout << endl;

	int** a = new int* [N];
	for (int i = 0; i < N; i++)
		a[i] = new int[N];

	CreateRows(a, K, N, Low, High, 0);
	PrintRows(a, K, N, 0);

	cout << "Введіть 1, якщо бажаєте здійснити переміщення елементів вправо" << endl
		<< "Введіть 0, якщо бажаєте здійснити переміщення елементів вниз" << endl;
	cin >> TrueFalse;
	cout << "x = "; cin >> x;

	if (TrueFalse)
		MovingRight(a, K, N, x, 0, 0, 0, N - 1);
	else
		MovingDown(a, K, N, x, 0, 0, K-1, 0);

	PrintRows(a, K, N, 0);

	cout << "номер рядка = " << FindRow(a, K, N, 0, -1, 0, 0 ,0) << endl;

	delete[] a;

	return 0;
}