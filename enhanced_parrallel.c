#include <stdio.h>
#include <limits.h>
#include <omp.h>

#define N 300  
#define RUNS 10  // Number of times to execute

void chain_matrix(int p[], int n, int m[N][N]) { 
    int i, j, k, cost;  

    #pragma omp parallel for private(i, j, k, cost) shared(m, p)
    for (int length = 2; length < n; length++) {  
        for (i = 1; i < n - length + 1; i++) {  
            j = i + length - 1;
            int min_cost = INT_MAX;//Int max will compute that  computed cost is smaller than the initial cost and store it in  min cost variable
            

            for (k = i; k < j; k++) {
                cost = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];

                if (cost < min_cost) {
                    min_cost = cost;
                }
            }
            m[i][j] = min_cost;  // Update outside the parallel region
        }
    }
}
int main(){
    int p[]={40,20,30,10,50};
    int n =sizeof(p)/sizeof(p[0]);
    int m[N][N]={0};
    int num_of_threads=8;
    omp_set_num_threads(num_of_threads);
    double total_time=0.0;
    printf("Running with %d threads \n",num_of_threads);
    for(int i=0;i<RUNS;i++){
        double stime=omp_get_wtime();
        chain_matrix(p,n,m);
        double etime=omp_get_wtime();

        double exe_time=etime-stime;
        total_time +=exe_time;
        printf("%d iteration has exe time = %f seconds\n",i+1,exe_time);
    }
    double average_time=total_time/RUNS;
    printf("Average execution time for %d iterations is %.9f seconds \n",RUNS,average_time);
    return 0;

}
