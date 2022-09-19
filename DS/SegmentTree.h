//
// Created by Semih on 10.09.2022.
//

#ifndef CLION_SEGMENTTREE_H
#define CLION_SEGMENTTREE_H
#include <iostream>
#include <cmath>
using namespace std;

class SegmetTreeSet1{

    int getMid(int s, int e )
    {
        return s + (e-s)/2;
    }
    /* A recursive function to get the sum of values in the given range
            of the array. The following are parameters for this function.

    st --> Pointer to segment tree
    si --> Index of current node in the segment tree. Initially
    0 is passed as root is always at index 0
    ss & se --> Starting and ending indexes of the segment represented
            by current node, i.e., st[si]
    qs & qe --> Starting and ending indexes of query range */
    int getSumUtil(int *st, int ss, int se, int qs, int qe, int si)
    {
        if(qs<=ss && qe>=se)
            return st[si];
        if(se<qs || ss>qe)
            return  0;
        int m = getMid(ss,se);

        return getSumUtil(st,ss,m,qs,qe,2*si+1)+ getSumUtil(st,m+1,se,qs,qe,2*si+2);
    }

    void updateValuesUtil(int *st, int ss, int se, int i, int diff, int si){
        if(i<ss || i>se)
            return;


        st[si] = st[si] + diff;

        if(se!= ss){
            int mid = getMid(ss,se);
            updateValuesUtil(st,ss,mid,i,diff,2*si+1);
            updateValuesUtil(st,mid+1,se,i,diff,2*si+2);
        }
    }

    void UpdateValue(int arr[], int *st, int n, int i, int nval){

        if(i<0  || i>=n )
        {
            cerr<< "invalid Input"<<endl;
            return;
        }

        int diff = nval - arr[i];

        arr[i] = nval;
        updateValuesUtil(st,0,n-1,i,diff,0);
    }

    int getSum(int *st, int n, int qs, int qe){
        if(qs<0 || qe>n-1 || qs>qe)
        {
            cerr<< "invalid Input"<<endl;
            return -1;
        }

        return getSumUtil(st,0,n-1,qs,qe,0);
    }

    int constructSTUtil(int arr[], int ss, int se, int *st, int si){

        if(ss==se)
        {
            st[si] = arr[ss];
            return arr[ss];
        }

        int mid = getMid(ss,se);

        st[si] = constructSTUtil(arr,ss,mid,st,si*2+1) +
                constructSTUtil(arr,mid+1,se,st,si*2+2);
        return st[si];
    }

    int *constructST(int arr[], int n)
    {
        int x = (int)(ceil(log2(n)));

        //Maximum size of segment tree
        int max_size = 2*(int)pow(2, x) - 1;

        // Allocate memory
        int *st = new int[max_size];

        // Fill the allocated memory st
        constructSTUtil(arr, 0, n-1, st, 0);
        // Return the constructed segment tree
        return st;
    }

public:
    int Run()
    {
        int arr[] = {1, 3, 5, 7, 9, 11, 123,23,123,5,5555555,5,67,234,4,534,534,12,1,4546,546,7675,867,845,6,46,456,456,456,345,345,34,5345,34,534,534,5,645,756,7,568,678,67,8,345,23,3,2,4587,849,36,7,3658,35,68,4358,47,8,789,53246,134,717,245,6,5,5,14,64,15,41,4,415,461,56,4165,};
        int n = sizeof(arr)/sizeof(arr[0]);

        // Build segment tree from given array
        int *st = constructST(arr, n);


        // Print sum of values in array from index 1 to 3
        cout<<"Sum of values in given range = "<<getSum(st, n, 20, 25)<<endl;

        // Update: set arr[1] = 10 and update corresponding
        // segment tree nodes
        UpdateValue(arr, st, n, 21, 1);

        // Find sum after the value is updated
        cout<<"Updated sum of values in given range = "
            <<getSum(st, n, 20, 25)<<endl;

        return 0;
    }
};
#endif //CLION_SEGMENTTREE_H
