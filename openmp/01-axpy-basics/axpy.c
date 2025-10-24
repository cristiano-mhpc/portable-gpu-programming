#include <stdio.h>
#include "helper_functions.h"
#include <omp.h> 

// Array size
#ifndef N
#define N 102400
#endif

int main(void)
{
    printf("Using N = %d\n", N);

    double alpha, x[N], y[N];

    // Initialization
    alpha = 3.0;
    for (int i = 0; i < N; i++) {
        double frac = 1.0 / ((double) (N - 1));
        x[i] = i * frac;
        y[i] = i * frac * 100;
    }

    // Print input values
    printf("Input:\n");
    printf("a = %8.4f\n", alpha);
    print_array("x", x, N);
    print_array("y", y, N);

    // Calculate axpy
    // TODO: Use OpenMP directives for GPU execution
    double t_kernel_start = omp_get_wtime();
#   pragma omp target teams distribute parallel for map(to: x[0:N], alpha) map(tofrom: y[0:N])    
    for (int i = 0; i < N; i++) {
        y[i] += alpha * x[i];
    }
    double t_kernel = omp_get_wtime() - t_kernel_start;
    printf("  Kernel         : %.6f\n", t_kernel);
    // Print output values
    printf("Output:\n");
    print_array("y", y, N);
    return 0;
}
