//
// Created by Semih on 10.09.2022.
//



#ifndef CLION_MATRIXCOMMONELEMENT_H
#define CLION_MATRIXCOMMONELEMENT_H

#endif //CLION_MATRIXCOMMONELEMENT_H

#include <unordered_map>
using namespace std;

class MatrixCommonElement
{
public:
    int findCommon(int N, int M,int mat[4][5])
    {
        unordered_map<int,int> cnt;
        int i,j;
        for(i = 0; i <M; i++)
        {
            cnt[mat[i][0]]++;
            for(j = 0; j<N;j++)
            {
                if(mat[i][j] != mat[i][j-1])
                    cnt[mat[i][j]]++;
            }
        }
        for(auto ele: cnt)
        {
            if(ele.second == M)
                return ele.first;
        }
        return -1;
    }

    int Run()
    {
        const int M = 4;
        const int N = 5;

        int mat[M][N] = {
                { 1, 2, 3, 4, 5 },
                { 2, 4, 5, 8, 10 },
                { 3, 5, 7, 9, 11 },
                { 1, 3, 5, 7, 9 },
        };
        int result = findCommon(N,M,mat);
        cout<<result<<endl;
        return result;
    }
};




