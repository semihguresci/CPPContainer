//
// Created by Semih on 10.09.2022.
//

#ifndef CLION_XORLINKLISTSET1_H
#define CLION_XORLINKLISTSET1_H
#include <iostream>
#include <cinttypes>
using namespace std;

class XORLINKEDLISTSET1{
    class Node {
    public:
        int data;
        Node* xnode;
    };

    Node* Xor(Node *x, Node *y)
    {
        return reinterpret_cast<Node*>(reinterpret_cast<uintptr_t>(x) ^ reinterpret_cast<uintptr_t>(y));
    }

    void insert(Node** head_ref, int data){
        Node* node = new Node();
        node->data = data;

        node->xnode = *head_ref;

        if(*head_ref)
        {
            (*head_ref) ->xnode = Xor(node,(*head_ref)->xnode);
        }
        *head_ref = node;
    }

    void printList(Node* head){
        Node* curr =head;
        Node* prev = NULL;
        Node* next;
        while(curr){
            cout<<curr->data<<" ";
            next = Xor(prev, curr->xnode);
            prev = curr;
            curr=next;
        }

    }

public:
    int Run()
    {
        Node* head = NULL;
        insert(&head, 10);
        insert(&head, 100);
        insert(&head, 1000);
        insert(&head, 10000);

        // Printing the created list
        printList(head);

        return (0);
    }

};

#endif //CLION_XORLINKLISTSET1_H
