#include <stdio.h>
#include <time.h>
#include <omp.h>

int main() 
{
    const long long N = 1'000'000'000; 
    long long int i = 0; 
    double sum = 0.0; 
    clock_t t0 = clock();
    float start_time = omp_get_wtime();
    
    #pragma omp parallel for private(i) reduction(+ : sum)
    for (i = N - 1; i >= 0; --i) 
    { 
        sum += 1.0 / (i + 1.0); 
    } 
    // Correct sum 21.3005
    
    clock_t t1 = clock(); 
    float end_time = omp_get_wtime();

    printf("s = %g\n", sum); 
    printf("T = %f\n", end_time - start_time);
    printf("t = %g\n", ((double)t1 - t0) / CLOCKS_PER_SEC); 
}