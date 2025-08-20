#include <stdio.h>

int fibonacciRecursivo(int n) {
    if (n == 0) return 0;   // Caso base
    if (n == 1) return 1;   // Caso base
    return fibonacciRecursivo(n - 1) + fibonacciRecursivo(n - 2);
}

void fibonacciIterativo(int n) {
    int a = 0, b = 1, siguiente, i;

    printf("Serie de Fibonacci (iterativo):\n");
    for (i = 0; i < n; i++) {
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

