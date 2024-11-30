/*
MP2 (XX22)
Manila Gang
John Rovere Iral
Daniella Limbag
Ma. Julianna Reyes
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

extern void x64CompAcceleration(long long int rows, float* matrix, int* results);

void x64CompAcceleration(int rows, float* matrix, int* results){
     //Constants for conversions
     const float kmtoM = 1000.0f;
     const float hoursToSec = 3600.0f;
     for(int i = 0; i < rows; i++){
             float V0 = matrix[i*3]; //Initial Velocity
             float V1 = matrix[i*3 + 1] //Final Velocity
             float T = matrix[i*3 + 2] //Time
             
             float acceleration = (V1 - V0) * kmtoM / (T * hoursToSec);
             
             results[i] = (int)acceleration;        
     }
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
    int* results = (int*)malloc(rows * sizeof(int));
    printf("Enter car data (Initial Velocity, Final Velocity, Time):\n");
    for (int i = 0; i < rows; i++) {
        printf("Car %d: ", i + 1);
        scanf("%f, %f, %f",
               &matrix[i * 3],
               &matrix[i * 3 + 1],
               &matrix[i * 3 + 2]);
    }
    
    // Measuring time
    start = clock();

	//Run 30 times
    for (loopFlag = 0; loopFlag < 30; loopFlag++) {
        x64CompAcceleration(rows, matrix, results);
    }
    
    end = clock();
    
    time_used = (double)(end - start) / CLOCKS_PER_SEC * 1000;
    average_time = time_used / 30;

    // Print results and everage execution time
    printf("\nAcceleration results (m/s^2):\n");
    for (int i = 0; i < rows; i++) {
        printf("%d\n", results[i]);
    }
    printf("\nAverage Execution Time (30 runs): %.6lf ms\n", average_time);

    // Free allocated memory
    free(matrix);
    free(results);
	return 0;
}
