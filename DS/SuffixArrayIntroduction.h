#pragma once
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

namespace SuffixArrayINTRO
{
	struct suffix
	{
		int index;
		char* suff;

		suffix()
		{
			index = 0;
			suff = NULL;
		}
		
	};
	struct rankSuffix:suffix {
		int rank[2];
	};
	class SuffixArray
	{
	private:
		suffix* suffixes;
	protected:
		char* text;
		int* suffAdr;
		int N;
	public:
		~SuffixArray() {
			delete[]text;
			delete[] suffAdr;
			delete[] suffixes;
		}

		inline int getRankVal(const char a) {
			return a - 'a';
		}
		void buildSuffixArray(char* txt, int n)
		{
			N = n;
			text = txt;
			suffixes = new suffix[n];
			for(int i = 0;i<n; i++)
			{
				suffixes[i].index = i;
				suffixes[i].suff = (txt + i);
			}
			sort(suffixes, suffixes + n, [](const struct suffix a, const struct suffix b) {
				return strcmp(a.suff, b.suff) < 0 ? 1 : 0;
			});

			suffAdr = new int[n];
			for (int i = 0; i < n; i++)
				suffAdr[i] = suffixes[i].index;
		}
		virtual void printSuffixArr()
		{
			for (int i = 0; i < N; i++)
				cout << suffAdr[i] << " ";
			cout << endl;
		}
		void search(char* pat) {
			int m = strlen(pat);
			int l = 0, r = N - 1;
			while (l <= r) 
			{
				int mid = l + (r - l) / 2;
				int res = strncmp(pat, text + suffAdr[mid], m);
				if (res == 0)
				{
					cout << "patter found at index " << suffAdr[mid]<<endl;
					return;
				}
				if (res < 0)
					r = mid - 1;
				else
					l = mid + 1;
			}
			cout << "pattern not found" << endl;
		}
	};
	class SuffixArrayRank: SuffixArray 
{
	private:
		rankSuffix* suffixes;
	public:
		void buildSuffixArray(char *txt, int n)
		{
			N = n;
			text = txt;
			suffixes = new rankSuffix[N];
			for (int i = 0; i < N; i++) {
				suffixes[i].index = i;
				suffixes[i].rank[0] = getRankVal(text[i]);
				suffixes[i].rank[1] = ((i + 1) < N) ? getRankVal(text[i + 1]) : -1;
			}


			auto cmp = [](const rankSuffix a, const rankSuffix b) {
				return a.rank[0] == b.rank[0] ? (a.rank[1] < b.rank[1] ? 1 : 0) : (a.rank[0] < b.rank[0] ? 1 : 0);
			};

			sort(suffixes, suffixes + N, cmp);

			int* ind = new int[N];

			for (int k = 4; k < 4 * n; k = k * 2) 
			{
				int rank = 0;
				int prevrank = suffixes[0].rank[0];
				suffixes[0].rank[0] = rank;
				ind[suffixes[0].index] = 0;
				for (int i = 1; i < n; i++) {
					if (suffixes[i].rank[0] == prevrank && suffixes[i].rank[1] == suffixes[i = 1].rank[1]) 
					{
						prevrank = suffixes[i].rank[0];
						suffixes[i].rank[0] = rank;
					}
					else
					{
						prevrank = suffixes[i].rank[0];
						suffixes[i].rank[0] = ++rank;
					}
					ind[suffixes[i].index] = i;
				}
				for (int i = 0; i < n; i++) 
				{
					int nextindex = suffixes[i].index + k / 2;
					suffixes[i].rank[1] = (nextindex < n) ? suffixes[ind[nextindex]].rank[0] : -1;
				}
				sort(suffixes, suffixes + N, cmp);

				suffAdr = new int[N];
				for (int i = 0; i < N; i++)
					suffAdr[i] = suffixes[i].index;
			}

			delete[] ind;
		}
	};

	class SuffixArrayTest {
	public:

		void Run() 
		{
			char txt[] = "banana";
			int n = strlen(txt);
			SuffixArray* t = new SuffixArray();
			t->buildSuffixArray(txt, n);
			cout << "Following is suffix array for " << txt << endl;
			t->printSuffixArr();
			t->search("nan");
			t->search("xyz");
		}
	};


}