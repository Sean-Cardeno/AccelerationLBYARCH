#include <stdio.h>
#include <stdlib.h>
#include <time.h>

extern void accel_ASM(int* results, int Y, double* matrix);

int main() {
    int Y;
    printf("Enter the number of cars (rows): ");
    scanf("%d", &Y);
    
    double* matrix = malloc(Y * 3 * sizeof(double));
    int* results = malloc(Y * sizeof(int));
    
    srand(time(NULL));
    
    clock_t start_time = clock();    

	for (int i = 0; i < Y; i++) {
        matrix[i * 3] = (double)(rand() % 201 - 100) / 10.0; // -10.0 to 10.0
        matrix[i * 3 + 1] = (double)(rand() % 1001) / 10.0;   // 0.0 to 100.0
        matrix[i * 3 + 2] = (double)(rand() % 101 + 1) / 10.0; // 0.1 to 10.0
        printf("Row %d (Randomized): Initial Velocity = %.2f, Final Velocity = %.2f, Time = %.2f\n", 
               i + 1, matrix[i * 3], matrix[i * 3 + 1], matrix[i * 3 + 2]);
    }

    accel_ASM(results, Y, matrix);
    
    for (int i = 0; i < Y; i++) {
    printf("Car %d: %d m/s^2\n", i + 1, results[i]);
	}
	free(matrix);
    free(results);
    
    clock_t end_time = clock();
    
    double execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("Execution Time: %.6f seconds\n", execution_time);
    
    free(matrix);
	free(results);
    return 0;
}
