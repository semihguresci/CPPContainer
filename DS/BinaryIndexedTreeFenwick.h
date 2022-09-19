#pragma once
#include <iostream>
using namespace std;

namespace BinartIndexTreeStructure
{
	class BinaryIndexedTree
	{
	public:
		int getSum(int BITree[], int index)
		{
			int sum = 0;
			index += 1;
			while(index>0)
			{
				sum += BITree[index];
				index -= index & (-index);
			}
			return sum;
		}

		void updateBIT(int BITree[], int n, int index, int val)
		{
			index = index + 1;
			while(index<=n)
			{
				BITree[index] += val;
				index += index & (-index);
			}
		}

		int *constructBITree(int arr[], int n)
		{
			int* BITree = new int[n + 1];
			memset(BITree, 0, sizeof(int) * (n + 1));
			for (int i = 0; i < n; i++)
				updateBIT(BITree, n, i, arr[i]);
			return BITree;
		}

	};

	class BinaryIndexedTreeTest
	{
	public:
		void Run()
		{


			int freq[] = { 2, 1, 1, 3, 2, 3, 4, 5, 6, 7, 8, 9 };
			int n = sizeof(freq) / sizeof(freq[0]);
			BinaryIndexedTree* bit = new BinaryIndexedTree();

			int* BITree = bit->constructBITree(freq, n);

			cout << "\nSum of elements in arr[0..5] is "
				<< bit-> getSum(BITree, 5);

			// Let use test the update operation
			freq[3] += 6;
			bit->updateBIT(BITree, n, 3, 6); //Update BIT for above change in arr[]

			cout << "\nSum of elements in arr[0..5] after update is "
				<< bit->getSum(BITree, 5);
			delete[] BITree;
		}
	};

}