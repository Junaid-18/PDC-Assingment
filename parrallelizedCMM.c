#include <stdio.h>
#include <limits.h>
#include <omp.h>
#define N 300
 
void chain_matrix(int p[],int m[N][N]){
    int length,cost;
    #pragma omp parrallel for shared(m,p) private(length,cost) collapse(2)
    for(length=2;length<N;length++){
        for(int i =1;i<N - length+1;i++){
            int j=i + length-1;
            m[i][j]=INT_MAX;
            for(int k=i;k<j;k++){
                cost=m[i][k] + m[k+1][j]+p[i-1]*p[k]*p[j];
                #pragma omp critical
                {
                    if(cost<m[i][j]){
                        m[i][j]=cost;
                    }
                }
            }
        }
    }

}