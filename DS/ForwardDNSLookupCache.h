#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

namespace ForwardDNSLookupCache
{
	inline const int CHARS = 27;
	inline const int MAX = 100;

	inline int getIndex(const char c)
	{
		return (c == '.') ? 26 : (c - 'a');
	}

	inline char getCharFromIndex(int i)
	{
		return (i == 26) ? '.' : ('a' + i);
	}

	struct trieNode
	{
		bool isLeaf;
		char* ipAdd;
		struct trieNode** children;

		trieNode()
		{
			isLeaf = false;
			ipAdd = NULL;
			children = new trieNode* [CHARS];
			for (int i = 0; i < CHARS; i++)
			{
				children[i] = NULL;
			}
		}
	};

	class trie
	{
	private:
		struct trieNode* suffixes;
	public:
		trie()
		{
			suffixes = new trieNode();
		}
		void insert(char *url, char *ipAdd)
		{
			int len = strlen(url);
			struct trieNode* pCrawl = suffixes;

			for(int level  = 0; level <len; level++)
			{
				int index = getIndex(url[level]);
				if (!pCrawl->children[index])
					pCrawl->children[index] = new trieNode();
				pCrawl = pCrawl->children[index];
			}

			pCrawl->isLeaf = true;
			pCrawl->ipAdd = new char[strlen(ipAdd) + 1];
			strcpy(pCrawl->ipAdd, ipAdd);
		}
		char *searchDnsCache(char *url)
		{
			struct trieNode* pCrawl = suffixes;
			int len = strlen(url);
			for(int level = 0; level<len;level++)
			{
				int index = getIndex(url[level]);
				if (!pCrawl->children[index])
					return NULL;
				pCrawl = pCrawl->children[index];
			}

			if (pCrawl != NULL && pCrawl->isLeaf)
				return pCrawl->ipAdd;
			return NULL;
		}
			 
	};

	class trieTest
	{
	public:
		void Run()
		{
			char URL[3][50] = { "www.samsung.com", "www.samsung.net",
					  "www.google.in"
			};
			char ipAdd[3][MAX] = { "107.108.11.123", "107.109.123.255",
								  "74.125.200.106"
			};
			int n = sizeof(URL) / sizeof(URL[0]);
			trie* t = new trie();

			// Inserts all the domain name and their corresponding
			// ip address
			for (int i = 0; i < n; i++)
				t->insert(URL[i], ipAdd[i]);

			// If forward DNS look up succeeds print the url along
			// with the resolved ip address.
			char url[] = "www.google.in";
			char* res_ip = t->searchDnsCache(url);
			if (res_ip != NULL)
				printf("Forward DNS look up resolved in cache:\n%s --> %s",
					url, res_ip);
			else
				printf("Forward DNS look up not resolved in cache ");

			delete t;
		}
	};
	
}