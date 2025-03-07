#include <stdio.h>
#include <limits.h>
#include <omp.h>
#include <time.h>
#define N 300  //No of matirces
void chain_matrix(int p[],int n,int m[N][N]){
    for(int length=2;length<n;length++){
        for(int i=1;i<n- length+1;i++){
            int j=i+length-1; //for ending matrix
            m[i][j]=INT_MAX;
            for(int k=i;k<j;k++){
                int cost=m[i][k] + m[k+1][j]+p[i-1]*p[k]*p[j];//to find min cost within product chain
                if(cost<m[i][j]){//if cost is lesser then updation occurs
                    m[i][j]=cost;
                }
            }
        }
    }
}
int main(){
    int p[N]={20,30,40,50,10};//dimensions
    int m[N][N]={0};
    __clock_t start,end;
    double time_taken;
    start=clock();
    chain_matrix(p,N,m);
    end=clock();
    time_taken=((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Sequential Chain Matrix Multiplication has exe  time = %f seconds \n ",time_taken);
    return 0;
} 
