
#include <stdio.h>
#include <time.h>
#include <math.h>

long long operaciones_recursivo = 0;
long long operaciones_iterativo = 0;
long long operaciones_cota = 0;

int fibonacci_recursivo(int n) {
    operaciones_recursivo++;
    if (n == 0) return 0;
    if (n == 1) return 1;
    return fibonacci_recursivo(n - 1) + fibonacci_recursivo(n - 2);
}

void fibonacci_iterativo(int n) {
    operaciones_iterativo = 0;
    int a = 0, b = 1, siguiente, i;
    for (i = 0; i < n; i++) {
        operaciones_iterativo++;
        if (i <= 1)
            siguiente = i;
        else {
            siguiente = a + b;
            a = b;
            b = siguiente;
        }
        // No imprimir valores
    }
}

int fibonacci_cota_inferior(int n) {
    operaciones_cota = 1;
    double phi = (1.0 + sqrt(5.0)) / 2.0;
    return (int)((pow(phi, n) - pow(-phi, -n)) / sqrt(5.0) + 0.5);
}

double medir_tiempo_recursivo(int n) {
    clock_t inicio, fin;
    operaciones_recursivo = 0;
    inicio = clock();
    int resultado = fibonacci_recursivo(n);
    fin = clock();
    return ((double)(fin - inicio)) / CLOCKS_PER_SEC * 1000.0;
}

double medir_tiempo_iterativo(int n) {
    clock_t inicio, fin;
    operaciones_iterativo = 0;
    inicio = clock();
    fibonacci_iterativo(n);
    fin = clock();
    return ((double)(fin - inicio)) / CLOCKS_PER_SEC * 1000.0;
}

double medir_tiempo_cota(int n) {
    clock_t inicio, fin;
    operaciones_cota = 0;
    inicio = clock();
    int resultado = fibonacci_cota_inferior(n);
    fin = clock();
    return ((double)(fin - inicio)) / CLOCKS_PER_SEC * 1000.0;
}

void imprimir_encabezado() {
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

void imprimir_fila(int n) {
    double tiempo_recursivo, tiempo_cota, tiempo_iterativo;
    int resultado_recursivo, resultado_iterativo;
    operaciones_recursivo = 0;
    tiempo_recursivo = medir_tiempo_recursivo(n);
    long long terminos_recursivo = operaciones_recursivo;
    resultado_recursivo = fibonacci_recursivo(n);
    tiempo_cota = medir_tiempo_cota(n);
    long long terminos_cota = operaciones_cota;
    // ...existing code...
    tiempo_iterativo = medir_tiempo_iterativo(n);
    long long terminos_iterativo = operaciones_iterativo;
    resultado_iterativo = (n == 0) ? 0 : (n == 1) ? 1 : resultado_recursivo;
    printf("\n%-8d %-18lld %-18.6f %-18d %-18.6f %-18lld %-18.6f\n",
           n, terminos_recursivo, tiempo_recursivo, resultado_recursivo,
           tiempo_cota, terminos_iterativo, tiempo_iterativo);
}

int main() {
    imprimir_encabezado();
    int valores_prueba[] = {5, 10, 15, 20, 25, 30};
    int num_pruebas = sizeof(valores_prueba) / sizeof(valores_prueba[0]);
    for (int i = 0; i < num_pruebas; i++) {
        imprimir_fila(valores_prueba[i]);
    }
    printf("\n=================================================================================================================================================\n");
    return 0;
}

