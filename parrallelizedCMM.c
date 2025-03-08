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
                        m[i][j]=cost; //Critical section
                    }
                }
            }
        }
    }

}
int main(){
     int p[N]={20,30,40,50,10};//dimensions
    int m[N][N]={0};
    int num_of_threads=8;
    omp_set_num_threads(num_of_threads);
    double stime=omp_get_wtime();
    chain_matrix(p,m);
    double etime=omp_get_wtime();
    printf("Parrallel Chain Matrix Multiplication Has Exe_time = %f seconds/n",etime-stime );
    return 0;

}