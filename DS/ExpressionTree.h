 //
// Created by Semih on 10.09.2022.
//
#ifndef CLION_EXPRESSIONTREE_H
#define CLION_EXPRESSIONTREE_H
#include <cstddef>
#include <iostream>
using namespace std;

 class ExpressiobTreeSol{
 public:
     class node
     {
     public:
         char value;
         node* left;
         node* right;
         node* next = NULL;

         node(char c){
             value = c;
             left = right = NULL;
         }
         node()
         {
             left = right = NULL;
         }
         friend class Stack;
         friend class ExpressionTree;
     };
     class Stack{
         node* head = NULL;
     public:
         void push(node* x)
         {
             if(head == NULL){
                 head = x;
             }
             else {
                 x->next = head;
                 head = x;
             }

         }
         node* pop(){
             node* p = head;
             head = head->next;
             return p;
         }

         friend class ExpressionTree;
     };
     class ExpressionTree{
     public:
         void inOrder(node* x){
             if(x == NULL)
                 return;
             else
             {
                 inOrder(x->left);
                 cout<<x->value<< " ";
                 inOrder(x->right);
             }
         }
     };

     void Run(){
         string str = "ABC*+D/";
         Stack stack;
         ExpressionTree et;
         node *x,*y,*z;
         int l = str.length();

         for(int i = 0 ; i<l;i++)
         {
             z= new node(str[i]);
             if(str[i] == '+' ||
                     str[i] == '-' ||
                     str[i] == '*' ||
                     str[i] == '/' ||
                     str[i] == '^' )
             {

                    x= stack.pop();
                    y = stack.pop();
                    z->left = y;
                    z->right = x;
             }
             stack.push(z);
         }
         et.inOrder(z);
     }

 };
#endif //CLION_EXPRESSIONTREE_H
