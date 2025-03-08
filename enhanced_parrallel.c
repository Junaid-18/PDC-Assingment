#include <stdio.h>
#include <limits.h>
#include <omp.h>
#include <string.h>

#define N 300  

void chain_matrix(int p[], int n, int m[N][N]) {
    int length, i, j, k, cost;

    for (length = 2; length < n; length++) {  
        #pragma omp parallel for private(i, j, k, cost) schedule(dynamic)  
        for (i = 1; i < (n - length + 1); i++) {  
            j = i + length - 1;
            m[i][j] = INT_MAX;

            for (k = i; k < j; k++) {
                cost = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];

                if (cost < m[i][j]) {
                    m[i][j] = cost;
                }
            }
        }
    }
}

// Function to print the matrix
void print_matrix(int m[N][N], int n) {
    printf("\n Matrix:\n");
    for (int i = 1; i < n; i++) { //this will traverse rows in matrix
        for (int j = 1; j < n; j++) {  // this will traverse column in mmatrix
            if (i > j) {
                printf(" ---- ");  
            } else {
                printf("%5d ", m[i][j]); //for actual values displaying 
            }
        }
        printf("\n");
    }
}

int main() {
    int p[] = {20, 30, 40, 50, 10};  
    int n = sizeof(p) / sizeof(p[0]);  
    int m[N][N];  
    memset(m, 0, sizeof(m));//it will set a block of memory for a value and initial m with 0(diagonal entries)

    int num_of_threads = 8;
    omp_set_num_threads(num_of_threads);
    
    printf("Running with %d threads\n", num_of_threads);

    double stime = omp_get_wtime();
    chain_matrix(p, n, m);
    double etime = omp_get_wtime();
    
    printf("\nParallel Chain Matrix Multiplication Execution Time: %f seconds\n", etime - stime);

    print_matrix(m, n);  // Print the matrix after execution

    return 0;
}
