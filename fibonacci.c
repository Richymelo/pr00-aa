#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>



void imprimir_tiempo(double ms) {
    double ns = ms * 1e6;
    double us = ms * 1e3;
    double s = ms / 1000.0;
    double min = s / 60.0;
    double h = min / 60.0;
    double d = h / 24.0;
    double w = d / 7.0;
    double y = d / 365.25;
    if (y >= 1.0)
        printf("%.8f anios", y);
    else if (w >= 1.0)
        printf("%.6f sem", w);
    else if (d >= 1.0)
        printf("%.6f d", d);
    else if (h >= 1.0)
        printf("%.6f h", h);
    else if (min >= 1.0)
        printf("%.6f min", min);
    else if (s >= 1.0)
        printf("%.6f s", s);
    else if (ms >= 1.0)
        printf("%.3f ms", ms);
    else if (us >= 1.0)
        printf("%.3f us", us);
    else
        printf("%.0f ns", ns);
}

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
    printf("==============================================================================================================================================================================\n");
    printf("%-8s %-18s %-22s %-14s %-22s %-18s %-22s\n",
        "Valor n", "Térm. Rec.", "Tiempo Rec.", "Cota Inf.", "Tiempo Cota", "Térm. Iter.", "Tiempo Iter.");
    printf("==============================================================================================================================================================================\n");
}

void imprimir_fila(int n) {
    double tiempo_recursivo, tiempo_cota, tiempo_iterativo;
    int resultado_recursivo, resultado_iterativo;
    operaciones_recursivo = 0;
    tiempo_recursivo = medir_tiempo_recursivo(n);
    long long terminos_recursivo = operaciones_recursivo;
    resultado_recursivo = fibonacci_recursivo(n);
    int valor_cota = fibonacci_cota_inferior(n);
    tiempo_cota = medir_tiempo_cota(n);
    long long terminos_cota = operaciones_cota;
    // Guardar operaciones antes de medir tiempo iterativo
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
    }
    long long terminos_iterativo = operaciones_iterativo;
    tiempo_iterativo = medir_tiempo_iterativo(n);
    resultado_iterativo = (n == 0) ? 0 : (n == 1) ? 1 : resultado_recursivo;
    printf("%-8d %-18lld ", n, terminos_recursivo);
    imprimir_tiempo(tiempo_recursivo);
    printf(" %-14d ", valor_cota);
    imprimir_tiempo(tiempo_cota);
    printf(" %-18lld ", terminos_iterativo);
    imprimir_tiempo(tiempo_iterativo);
    printf("\n");
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

