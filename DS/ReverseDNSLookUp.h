#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

namespace ReverseDNSLookup {

	inline const int CHARS = 11;
	inline const  int MAX = 50;
	inline int getIndex(const char c) { return (c == '.') ? 10 : (c - '0'); }
	inline char getCharFromIndex(const int i) { return (i == 10) ? '.' : ('0' + i); }

	struct trieNode {
		bool isLeaf;
		char* url;
		struct trieNode **children;

		trieNode() {
			children = new trieNode*[CHARS];
			isLeaf = false;
			url = NULL;
			for (int i = 0; i < CHARS; i++) 
			{
				children[i] = NULL;
			}
				
		}
	};

	class Trie 
	{
		private:
			struct trieNode* suffixes;

		public:
		Trie()
		{
			suffixes = new trieNode();
		}

		void insert(const char *ipAdd, const char* url)
		{
			const int len = strlen(ipAdd);
			struct trieNode* crawl = suffixes;
			for(int level = 0; level<len;level++)
			{
				const int index = getIndex(ipAdd[level]);
				if (!crawl->children[index])
					crawl->children[index] = new trieNode();
				crawl = crawl->children[index];
			}
			crawl->isLeaf = true;
			crawl->url = new char[strlen(url) + 1];
			strcpy_s(crawl->url, strlen(url)+1, url);
		}

		char *searchDNSCache(char *ipAdd)
		{
			struct trieNode* pcrawl = suffixes;
			int len = strlen(ipAdd);

			for(int level = 0 ; level <len;level++)
			{
				int index = getIndex(ipAdd[level]);
				if (!pcrawl->children[index])
					return NULL;
				pcrawl = pcrawl->children[index];
			}

			if (pcrawl != NULL && pcrawl->isLeaf)
				return pcrawl->url;
			return NULL;
			
		}
	};

	class TrieTest
	{
	public:
		void Run()
		{
			char ipAdd[3][MAX] = { "107.108.11.123", "107.109.123.255",
						 "74.125.200.106" };
			char URL[3][50] = { "www.samsung.com", "www.samsung.net",
							  "www.google.in" };
			int n = sizeof(ipAdd) / sizeof(ipAdd[0]);
			Trie* t= new Trie();

			// Inserts all the ip address and their corresponding
			// domain name after ip address validation.
			for (int i = 0; i < n; i++)
				t->insert(ipAdd[i], URL[i]);

			// If reverse DNS look up succeeds print the domain
			// name along with DNS resolved.
			char ip[] = "107.108.11.123";
			char* res_url = t->searchDNSCache(ip);
			if (res_url != NULL)
				printf("Reverse DNS look up resolved in cache:\n%s --> %s",
					ip, res_url);
			else
				printf("Reverse DNS look up not resolved in cache ");
			delete t;
		}
	};
}