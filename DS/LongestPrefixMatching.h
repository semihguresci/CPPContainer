//
// Created by Semih on 12.09.2022.
//

#ifndef CLION_LONGESTPREFIXMATCHING_H
#define CLION_LONGESTPREFIXMATCHING_H
#include <iostream>
#include <map>
#include <string>

namespace LongestPrefixMatching
{
    class TrieNode{
    private:
        char value;
        std::map<char, TrieNode*> chilren;
        bool bleaf;
    public:
        std::map<char, TrieNode*>* getChildren(){ return &chilren; }
        char getValue(){return value;}
        void setLeaf(bool val){ bleaf = val;}
        bool isLeaf(){return bleaf;}

        TrieNode(char ch):value(ch),bleaf(false){}
    };

    class  Trie{
    private:
        TrieNode *suffixes;
    public:
        Trie()
        {
            suffixes = new TrieNode((char)0);
        }
        void insert(std::string word){
            int length = word.length();
            TrieNode* crawl =suffixes;
            for(int l = 0 ; l<length;l++)
            {
                char ch = word[l];
                if(!crawl->getChildren()->empty() && crawl->getChildren()->find(ch) != crawl->getChildren()->end())
                {
                    crawl =crawl->getChildren()->at(ch);
                }
                else{
                    TrieNode *t = new TrieNode(ch);
                    crawl->getChildren()->insert(std::make_pair(ch,t));
                    crawl = std::move(t);
                }
            }
            crawl->setLeaf(true);
        }

        std::string getMatchingPrefix(std::string input){
            std::string result;
            int l = input.length();
            TrieNode* crawl = suffixes;

            int level = 0, prevMatch = 0;

            for(level=0;level<l;level++){
                char ch = input[level];
                if(!crawl->getChildren()->empty() && crawl->getChildren()->find(ch) != crawl->getChildren()->end())
                {
                    result +=ch;
                    crawl=crawl->getChildren()->at(ch);

                    if(crawl->isLeaf())
                        prevMatch = level+1;
                }
                else
                    break;
            }

            if(!crawl->isLeaf())
                return result.substr(0,prevMatch);
            else
                return result;
        }

    };

    class TrieTest{
    public:
        void Run(){
           Trie *t = new Trie();
           t->insert("are");
           t->insert("area");
           t->insert("base");
           t->insert("cat");
           t->insert("cater");
           t->insert("basement");

           std::string input = "caterer";
           std::cout<<t->getMatchingPrefix(input)<< std::endl;
           input = "basement";
           std::cout<<t->getMatchingPrefix(input)<< std::endl;
            input = "catmmd";
           std::cout<<t->getMatchingPrefix(input)<< std::endl;
            input = "xyz";
           std::cout<<t->getMatchingPrefix(input)<< std::endl;

           delete t;

        }
    };

};
#endif //CLION_LONGESTPREFIXMATCHING_H
