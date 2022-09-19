//
// Created by Semih on 12.09.2022.
//



#ifndef CLION_ST_SUMOFGIVENRANGE_H
#define CLION_ST_SUMOFGIVENRANGE_H
#include <cstddef>
#include <iostream>
using namespace std;


class STSumofGivenRange{

    struct node {
        int val;
        struct node *left, *right;
        node(){}
        node(node *l,node *r, int v):left(l), right(r), val(v){}
    };


    int *arr;
    node** version;

    void build (node* n, int low, int high){

        if(low == high)
        {
            n->val =arr[low];
            return;
        }

        int mid = (low+high)/2;
        n->left = new node(NULL, NULL, 0);
        n->right = new node(NULL, NULL, 0);

        build (n->left, low, mid);
        build(n->right, mid+1, high);
        n->val = n->left->val + n->right->val;
    }

    void upgrade(node *prev, node *curr, int low, int high, int idx, int value){
        if(idx>high || idx<low || low>high)
            return;
        if(low == high){
            curr->val = value;
            return;
        }

        int mid = (low+high) / 2;
        if(idx<=mid){
            curr->right = prev->right;
            curr->left =  new node(NULL, NULL, 0);
            upgrade(prev->left, curr->left, low, mid, idx, value);
        }
        else{
            curr->left = prev->left;
            curr->right = new node(NULL, NULL, 0);
            upgrade(prev->right, curr->right,mid+1, high,idx,value);
        }
        curr->val =  curr->right->val +curr->left->val;
    }

    int query(node *n, int low, int high, int l, int r){
        if(l>high || r<low || low>high)
            return 0;
        if(l<=low  && high<=r)
            return n->val;

        int mid = (low+high)/2;
        int p1 = query(n->left, low, mid, l,r);
        int p2 = query(n->right, mid+1, high, l,r);
        return p1+p2;
    }
public:
    void Run(){
        int A[] = {1,2,3,4,5};
        int n = sizeof(A)/sizeof(int);

        arr = new int [n];
        version =  new node*[10];

        for (int i=0; i<n; i++)
            arr[i] = A[i];

        node* suffixes = new node(NULL, NULL, 0);
        build(suffixes, 0, n-1);

        version[0] = suffixes;

        version[1] = new node(NULL, NULL, 0);
        upgrade(version[0], version[1], 0, n-1, 4, 1);

        // upgrading to version-2
        version[2] = new node(NULL, NULL, 0);
        upgrade(version[1],version[2], 0, n-1, 2, 10);

        cout << "In version 1 , query(0,4) : ";
        cout << query(version[1], 0, n-1, 0, 4) << endl;

        cout << "In version 2 , query(3,4) : ";
        cout << query(version[2], 0, n-1, 3, 4) << endl;

        cout << "In version 0 , query(0,3) : ";
        cout << query(version[0], 0, n-1, 0, 3) << endl;



    }
};
#endif //CLION_ST_SUMOFGIVENRANGE_H