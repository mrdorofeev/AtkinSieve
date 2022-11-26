//#include "stdafx.h"
#include <iostream>
#include <math.h>
#include <chrono>
#include <random>
#include <time.h>
#include <fstream>
using namespace std;

std::chrono::duration<double>elapsed_seconds;

void atkin(bool massiv[], long long N)
{
	auto start = std::chrono::steady_clock::now();
	int sqr_lim;
	int x, y; // квадраты i и j
	int i, j;
	int k;

	sqr_lim = (long long)sqrt((long double)N);
	for (i = 0; i < N; ++i)
	{
		massiv[i] = false;
	}
	//massiv[2] = true;
	//massiv[3] = true;
	x = 0;
	for (i = 1; i < sqr_lim; ++i) {
		x += 2 * i - 1;
		y = 0;
		for (j = 1; j < sqr_lim; ++j) {
			y += 2 * j - 1;
			k = 4 * x + y;
			if ((k <= N) && (k % 12 == 1 || k % 12 == 5))
			{
				massiv[k] = !massiv[k];
			}
			// n = 3 * x2 + y2;
			k -= x;
			if ((k <= N) && (k % 12 == 7))
			{
				massiv[k] = !massiv[k];
			}
			// n = 3 * x2 - y2;
			k -= 2 * y;
			if ((i > j) && (k <= N) && (k % 12 == 11))
			{
				massiv[k] = !massiv[k];
			}
		}
	}
	for (i = 5; i < sqr_lim; ++i) {
		if (massiv[i]) {
			k = i * i;
			for (j = k; j < N; j += k)
			{
				massiv[j] = false;
			}
		}
	}


	auto end = std::chrono::steady_clock::now();
	elapsed_seconds = end - start;

	//cout << "2 3 5";
	//for (i = 6; i < N; ++i) {
	//	if ((massiv[i]) && (i % 3 != 0) && (i % 5 != 0))
	//	{
	//		cout << " " << i;
	//	}
	//}
}


void main()
{
	fstream fs;
	fs.open("C:\\Users\\srdor\\Desktop\\table4.txt");
	if (fs.is_open())
	{
		for (long long n = 2; n < 100000003; )
		{			
			bool* massiv = new bool[n];
			atkin(massiv, n);
		

			fs << n << " ";

			auto sec1 = elapsed_seconds.count();

			bool* massiv2 = new bool[2*n];
			atkin(massiv2, 2*n);
			auto sec2 = elapsed_seconds.count();
			cout << n << " " << std::fixed << sec1 << " " << std::fixed << sec2 << "\n";
			fs << std::fixed << sec1 << " " << std::fixed << sec2 << "\n";

			if (n < 10000)
				n += 10;
			else if (n < 100000)
				n += 2000;
			else if (n < 1000000)
				n += 10000;
			else if (n < 10000000)
				n += 100000;
			else
				n += 1000000;

			delete[] massiv;
			delete[] massiv2;
		}

		/*long long n = 100000002;

		bool* massiv = new bool[n];
		atkin(massiv, n);

		auto sec = elapsed_seconds.count();

		cout << n << " " << setprecision(5) << sec << "\n";
		fs << n << " " << sec << "\n";

		delete[] massiv;*/

	}

	/*setlocale(LC_ALL, "ru");
	int n;
	cout << "Введите размерность массива: ";
	cin >> n;
	bool* massiv = new bool[n];
	Atkin(massiv, n);
	delete[] massiv;
	cout << elapsed_seconds.count();
	cout << endl;*/

	fs.close();
}