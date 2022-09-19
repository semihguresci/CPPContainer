#pragma once
#include <iostream>
using namespace std;
namespace BITRangeUpdate
{
	class BITRU
	{
	public:
		int N = 0;
		int* BIT;

		void UpdateBIT(int n, int index, int val)
		{
			index = index + 1;
			while(index<N)
			{
				BIT[index] += val;
				index += index & (-index);
			}
		}
		void ConstuctBITree(int arr[], int n)
		{
			N = n;
			BIT = new int[n + 1];
			for (int i = 0; i < 1+n; i++)
				BIT[i] = 0;

			for (int i = 0; i < n; i++)
				UpdateBIT(n, i, arr[i]);
			
		}
		
		int getSum(int index)
		{
			int sum = 0;
			index = index + 1;
			while(index>0)
			{
				sum += BIT[index];
				index -= index & (-index);
			}
			return sum;
		}
		void Update(int l, int r , int n, int val)
		{
			UpdateBIT(n, l, val);
			UpdateBIT(n, r, -val);
		}


		~BITRU()
		{
			delete[] BIT;
		}
	};

	class BITRS
	{
	public:

		int sum(BITRU* bitru1, BITRU* bitru2, int x)
		{
			return bitru1->getSum(x)  + bitru2->getSum(x);
		}
		int rangeSum(BITRU* bitru1, BITRU* bitru2, int l, int r)
		{
			return sum(bitru1, bitru2, r) - sum(bitru1, bitru2, l - 1);
		}
	};

	class BITRUTest
	{
	public:
		void Run()
		{
			int arr[] = { 0, 0, 0, 0, 0 };
			int n = sizeof(arr) / sizeof(arr[0]);
			BITRU* bitru = new BITRU();
			bitru->ConstuctBITree(arr, n);

			// Add 2 to all the element from [2,4]
			int l = 2, r = 4, val = 2;
			bitru->Update(l, r, n, val);

			// Find the element at Index 4
			int index = 4;
			cout << "Element at index " << index << " is " << bitru->getSum(index) << "\n";

			// Add 2 to all the element from [0,3]
			l = 0, r = 3, val = 4;
			bitru->Update(l, r, n, val);

			// Find the element at Index 3
			index = 3;
			cout << "Element at index " << index << " is " << bitru->getSum(index) << "\n";

			BITRU* bitru2 = new BITRU();
			bitru2->ConstuctBITree(arr, n);

			l = 0;
			r = 4;
			val = 5;
			bitru2->Update(l, r, n, val);
			l = 2, r = 4, val = 10;
			bitru2->Update(l, r, n, val);
			BITRS* bitrs = new BITRS();

			l = 1, r = 4;
			cout << "Sum of elements from [" << l
				<< "," << r << "] is "<< bitrs->rangeSum(bitru, bitru2, l, r)<<endl;
			delete bitrs;
			delete bitru;
			delete bitru2;
		}
	};
}