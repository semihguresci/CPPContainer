#pragma once

#include <iostream>
using namespace std;

namespace TwoDimansionalBITFenwickTree
{

	struct Query
	{
		int x1, y1, x2, y2;
	};


	class Fenwick2D
	{
	public:
		int N;
		int** BIT;

		virtual ~Fenwick2D()
		{
			for(int i = 0 ;i<=N; i++)
			{
				delete[] BIT[i];
			}
			delete[] BIT;
		}

		void updateBit(int x, int y, int val)
		{
			for(;x<=N; x+=(x&-x))
			{
				for (int yy = y; yy <= N; yy += (yy & -yy))
					BIT[x][yy] += val;
			}
		}
		int getSum(int x,int y)
		{
			int sum = 0;
			for(;x>0; x-= x&-x)
			{
				for (int yy = y; yy > 0; yy -= yy & -yy)
					sum += BIT[x][yy];
			}
			return sum;
		}

		void constructAux(int **mat, int **aux)
		{
			for (int j = 1; j <= N; j++) 
			{
				for (int i = 1; i <= N; i++)
				{
					aux[i][j] = mat[N - j][i - 1];
				}
			}
		}

		void construct2dBit(int **mat, int n)
		{
			N = n;

			int** aux;
			aux = new int*[N + 1];
			BIT  = new int*[N + 1];

			for(int i = 0; i<N+1; i++)
			{
				aux[i] = new int[N + 1];
				BIT[i] = new int[N + 1];
				for(int j = 0; j<N+1;j++)
				{
					aux[i][j] = 0;
					BIT[i][j] = 0;
				}
			}

			constructAux(mat, aux);

			/*
			for (int j = 1; j <= N; j++)
			{
				for (int i = 1; i <= N; i++)
				{
					cout << aux[i][j] << "\t"<<mat[i-1][j-1] << endl;
				}
			}
			*/

			for (int j = 1; j < N; j++)
			{
				for (int i = 1; i <= N; i++)
				{
					int v1 = getSum(i, j);
					int v2 = getSum(i, j-1);
					int v3 = getSum(i-1, j - 1);
					int v4 = getSum(i - 1, j );

					updateBit( i, j, aux[i][j] - (v1 - v2 - v4 + v3));
				}
			}

			for (int i = 0; i <= N; i++)
			{
				delete[] aux[i];
			}
			delete[] aux;

		}

		void Search(Query q[], int m)
		{
			for(int i = 0;i<m;i++)
			{
				int x1 = q[i].x1 + 1;
				int y1 = q[i].y1 + 1;
				int x2 = q[i].x2 + 1;
				int y2 = q[i].y2 + 1;

				int ans = getSum(x2, y2) - getSum(x2, y1 - 1) -
					getSum(x1 - 1, y2) + getSum(x1 - 1, y1 - 1);

				printf("Query(%d, %d, %d, %d) = %d\n",
					q[i].x1, q[i].y1, q[i].x2, q[i].y2, ans);
			}
		}

	};

	class Fenwick2DTest
	{
	public:
		void Run() {
			int mat[4][4] = { {1, 2, 3, 4},
					   {5, 3, 8, 1},
					   {4, 6, 7, 5},
					   {2, 4, 8, 9} };

			int* tmap[4];
			for (int i = 0; i < 4; i++)
				tmap[i] = mat[i];

			auto matp = tmap;
	
			Fenwick2D* f2d = new Fenwick2D();
			f2d->construct2dBit(matp, 4);
			Query q[] = { {1, 1, 3, 2}, {2, 2, 3, 3}, {1, 1, 1, 1} };
			int m = sizeof(q) / sizeof(q[0]);
			f2d->Search(q, m);
			delete f2d;
			 

		}

	};
}