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
    
	return 0;
}