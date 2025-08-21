#include <stdio.h>
#include <time.h>
#include <math.h>

// Global variables to count operations
long long recursive_operations = 0;
long long iterative_operations = 0;
long long lower_bound_operations = 0;

// Original recursive Fibonacci function
int fibonacciRecursivo(int n) {
    recursive_operations++;
    if (n == 0) return 0;   // Caso base
    if (n == 1) return 1;   // Caso base
    return fibonacciRecursivo(n - 1) + fibonacciRecursivo(n - 2);
}

// Original iterative Fibonacci function (prints series)
void fibonacciIterativo(int n) {
    iterative_operations = 0; // Reset counter
    int a = 0, b = 1, siguiente, i;

    printf("Serie de Fibonacci (iterativo):\n");
    for (i = 0; i < n; i++) {
        iterative_operations++;
        if (i <= 1)
            siguiente = i;
        else {
            siguiente = a + b;
            a = b;
            b = siguiente;
        }
        printf("%d ", siguiente);
    }
    printf("\n");
}

// Lower bound analysis - simplified constant time approximation
int fibonacciCotaInferior(int n) {
    lower_bound_operations = 1; // Constant time operation
    // Using Binet's formula approximation for demonstration
    // This represents the theoretical lower bound
    double phi = (1.0 + sqrt(5.0)) / 2.0;
    return (int)((pow(phi, n) - pow(-phi, -n)) / sqrt(5.0) + 0.5);
}

// Function to measure execution time for recursive algorithm
double measureTimeRecursive(int n) {
    clock_t start, end;
    recursive_operations = 0;
    
    start = clock();
    int result = fibonacciRecursivo(n);
    end = clock();
    
    return ((double)(end - start)) / CLOCKS_PER_SEC * 1000.0; // Return time in milliseconds
}

// Function to measure execution time for iterative algorithm  
double measureTimeIterative(int n) {
    clock_t start, end;
    iterative_operations = 0;
    
    start = clock();
    fibonacciIterativo(n);
    end = clock();
    
    return ((double)(end - start)) / CLOCKS_PER_SEC * 1000.0; // Return time in milliseconds
}

// Function to measure execution time for lower bound algorithm
double measureTimeLowerBound(int n) {
    clock_t start, end;
    lower_bound_operations = 0;
    
    start = clock();
    int result = fibonacciCotaInferior(n);
    end = clock();
    
    return ((double)(end - start)) / CLOCKS_PER_SEC * 1000.0; // Return time in milliseconds
}

// Function to print table header
void printTableHeader() {
    printf("\n");
    printf("=================================================================================================================================================\n");
    printf("%-8s %-18s %-18s %-18s %-18s %-18s %-18s\n", 
           "Valor n", "Términos Reales", "Tiempo Ejecución", "Fibonacci Rec.", "Cota Inferior", "Términos Reales", "Tiempo Ejecución");
    printf("%-8s %-18s %-18s %-18s %-18s %-18s %-18s\n", 
           "", "Algoritmo Rec.", "Algoritmo Rec.", "(Columna 3)", "Tiempo CI (ms)", "Algoritmo Iter.", "Algoritmo Iter.");
    printf("%-8s %-18s %-18s %-18s %-18s %-18s %-18s\n", 
           "", "", "(ms)", "", "(Columna 4)", "", "(ms)");
    printf("=================================================================================================================================================\n");
}

// Function to print a single row of the table
void printTableRow(int n) {
    double recursive_time, lower_bound_time, iterative_time;
    int fibonacci_recursive_result, fibonacci_iterative_result;
    
    // Measure recursive algorithm and get its result
    recursive_operations = 0;
    recursive_time = measureTimeRecursive(n);
    long long recursive_terms = recursive_operations;
    fibonacci_recursive_result = fibonacciRecursivo(n); // Get the return value for column 3
    
    // Measure lower bound algorithm
    lower_bound_time = measureTimeLowerBound(n);
    long long lower_bound_terms = lower_bound_operations;
    
    // Measure iterative algorithm (this prints the series)
    printf("\nPara n=%d:\n", n);
    iterative_time = measureTimeIterative(n);
    long long iterative_terms = iterative_operations;
    
    // Since iterative function prints series, we need to calculate what would be returned
    // The last number printed would be the nth Fibonacci number
    fibonacci_iterative_result = (n == 0) ? 0 : (n == 1) ? 1 : fibonacci_recursive_result; // For column 4, use recursive result
    
    printf("\n%-8d %-18lld %-18.6f %-18d %-18.6f %-18lld %-18.6f\n",
           n, recursive_terms, recursive_time, fibonacci_recursive_result, 
           lower_bound_time, iterative_terms, iterative_time);
}

int main() {
    printf("ANALISIS DE ALGORITMOS - FIBONACCI\n");
    printf("Comparación de algoritmos recursivo e iterativo\n");
    
    // Print table header
    printTableHeader();
    
    // Test with different values of n
    int test_values[] = {5, 10, 15, 20, 25, 30};
    int num_tests = sizeof(test_values) / sizeof(test_values[0]);
    
    for (int i = 0; i < num_tests; i++) {
        printTableRow(test_values[i]);
    }
    
    printf("\n=================================================================================================================================================\n");
    printf("\nNOTAS:\n");
    printf("- Columna 3: Valor retornado por fibonacciRecursivo(n)\n");
    printf("- Columna 4: Tiempo de ejecución de la cota inferior (algoritmo teórico optimizado)\n");
    printf("- Términos Reales: Número de operaciones/llamadas realizadas por cada algoritmo\n");
    printf("- Los tiempos están en milisegundos (ms)\n");
    
    return 0;
}

