/*
MP2 (XX22)
John Rovere Iral
Daniella Limbag
Ma. Julianna Reyes
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <sys/time.h>

extern void x64CompAcceleration(long long int rows, float* matrix, int* results);

void x64CompAcceleration_C(long long int rows, float* matrix, int* results) {
    //Constants for conversions
    const float kmtoM = 1000.0f;
    const float hoursToSec = 3600.0f;
    
    for (int i = 0; i < rows; i++) {
        float V0 = matrix[i * 3]; // Initial Velocity
        float V1 = matrix[i * 3 + 1]; // Final Velocity
        float T = matrix[i * 3 + 2]; // Time
        
        float acceleration = (V1 - V0) * kmtoM / (T * hoursToSec);
        
        results[i] = (int)round(acceleration);
    }
}

double get_time() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + tv.tv_usec * 1e-6;
}

int main() {
	int rows;
    clock_t start, end;
    double time_used, average_time;
    int loopFlag;

    // Input values
    printf("Enter number of cars: ");
    scanf("%d", &rows);
    float* matrix = (float*)malloc(rows * 3 * sizeof(float));
    int* results_c = (int*)malloc(rows * sizeof(int));
    int* results_x64 = (int*)malloc(rows * sizeof(int));
    
    printf("Enter car data (Initial Velocity, Final Velocity, Time):\n");
    for (int i = 0; i < rows; i++) {
        printf("Car %d: ", i + 1);
        scanf("%f, %f, %f",
               &matrix[i * 3],
               &matrix[i * 3 + 1],
               &matrix[i * 3 + 2]);
    }
    
    // Performance testing for C implementation
    start = clock();
    for (loopFlag = 0; loopFlag < 30; loopFlag++) {
        x64CompAcceleration_C(rows, matrix, results_c);
    }
    end = clock();
    
    time_used = (double)(end - start) / CLOCKS_PER_SEC * 1000;
    average_time = time_used / 30;
    
    printf("\nC Implementation Acceleration results (m/s^2):\n");
    for (int i = 0; i < rows; i++) {
        printf("%d\n", results_c[i]);
    }
    printf("\nC Implementation Average Execution Time (30 runs): %.6lf ms\n", average_time);
    
	// Performance testing for C implementation
    start = clock();
    for (loopFlag = 0; loopFlag < 30; loopFlag++) {
        x64CompAcceleration(rows, matrix, results_x64);
    }
    end = clock();
    
    time_used = (double)(end - start) / CLOCKS_PER_SEC * 1000;
    average_time = time_used / 30;
    
    printf("\nx64 Assembly Acceleration results (m/s^2):\n");
    for (int i = 0; i < rows; i++) {
        printf("%d\n", results_x64[i]);
    }
    printf("\nx64 Assembly Average Execution Time (30 runs): %.6lf ms\n", average_time);
    
    // Performance Testing with Scalability
    printf("\n----------------- Performance Testing -----------------\n");
    
    int test_rows[] = {10, 100, 1000, 10000};
    int num_tests = sizeof(test_rows) / sizeof(test_rows[0]);
    int iterations;
    
	for (int j = 0; j < num_tests; j++) {
	    long long int rows = test_rows[j];
	    printf("\nInput row size = %lld \n", rows);
	    iterations = 30;
	    printf("Iterations per test: %d\n", iterations);
	
	    float* matrix = malloc(rows * 3 * sizeof(float));
	    int* results_c = malloc(rows * sizeof(int));
	    int* results_x64 = malloc(rows * sizeof(int));
	    
	    // Random values for the matrix
	    srand(time(NULL) + j);
	    for (int i = 0; i < rows; i++) {
	        matrix[i * 3] = ((float)rand() / RAND_MAX) * 100.0f; // Initial Velocity
	        matrix[i * 3 + 1] = ((float)rand() / RAND_MAX) * 100.0f; // Final Velocity
	        matrix[i * 3 + 2] = 0.5f + ((float)rand() / RAND_MAX) * 19.5f; // Time
	    }
		    // Performance testing for C implementation
	    double total_time_c = 0.0;
	    double start, end;
	
	    for (int i = 0; i < iterations; i++) {
	        start = get_time();
	        x64CompAcceleration_C(rows, matrix, results_c);
	        end = get_time();
	
	        total_time_c += (end - start) * 1000;
	    }
	    double average_time_c = total_time_c / iterations;
	
	    printf("C Implementation - Average Time (ms): %lf\n", average_time_c);
	    printf("C Implementation Results (first 5):\n");
	    for (int i = 0; i < (rows < 5 ? rows : 5); i++) {
	        printf("Row %d: %d\n", i + 1, results_c[i]);
	    }
	
	    // Performance testing for x64 implementation
	    double total_time_x64 = 0.0;
	
	    for (int i = 0; i < iterations; i++) {
	        start = get_time();
	        x64CompAcceleration(rows, matrix, results_x64);
	        end = get_time();
	
	        total_time_x64 += (end - start) * 1000;
	    }
	    double average_time_x64 = total_time_x64 / iterations;
	
	    printf("x64 Implementation - Average Time (ms): %lf\n", average_time_x64);
	    printf("x86-64 Implementation Results (first 5):\n");
	    for (int i = 0; i < (rows < 5 ? rows : 5); i++) {
	        printf("Row %d: %d\n", i + 1, results_x64[i]);
	    }
	
	    // Free memory for this test
	    free(matrix);
	    free(results_c);
	    free(results_x64);
		}  
    return 0;
}
