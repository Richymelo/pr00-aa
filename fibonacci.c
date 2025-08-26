#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <unistd.h>



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
        printf("%.8f años", y);
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

void formatear_tiempo(double ms, char* buffer) {
    double ns = ms * 1e6;
    double us = ms * 1e3;
    double s = ms / 1000.0;
    double min = s / 60.0;
    double h = min / 60.0;
    double d = h / 24.0;
    double w = d / 7.0;
    double y = d / 365.25;
    
    // Para valores extremadamente grandes, usar notación científica
    if (y >= 1e6) {
        sprintf(buffer, "%.2e años", y);
    } else if (y >= 1000.0) {
        sprintf(buffer, "%.1fK años", y / 1000.0);
    } else if (y >= 1.0) {
        sprintf(buffer, "%.0f años", y);
    } else if (w >= 1.0) {
        sprintf(buffer, "%.0f sem", w);
    } else if (d >= 1.0) {
        sprintf(buffer, "%.0f d", d);
    } else if (h >= 1.0) {
        sprintf(buffer, "%.2f h", h);
    } else if (min >= 1.0) {
        sprintf(buffer, "%.2f min", min);
    } else if (s >= 1.0) {
        sprintf(buffer, "%.3f s", s);
    } else if (ms >= 1.0) {
        sprintf(buffer, "%.3f ms", ms);
    } else if (us >= 1.0) {
        sprintf(buffer, "%.3f us", us);
    } else
        sprintf(buffer, "%.0f ns", ns);
}

void formatear_numero_grande(double numero, char* buffer) {
    // Si el número es muy grande, usar notación científica
    if (numero >= 1e12) {
        sprintf(buffer, "%.2e", numero);
    } else if (numero >= 1e9) {
        sprintf(buffer, "%.1fB", numero / 1e9);
    } else if (numero >= 1e6) {
        sprintf(buffer, "%.1fM", numero / 1e6);
    } else if (numero >= 1e3) {
        sprintf(buffer, "%.1fK", numero / 1e3);
    } else {
        sprintf(buffer, "%.0f", numero);
    }
}

double calcular_tiempo_teorico_recursivo(int n) {
    double operaciones = pow(2.0, n / 2.0);
    return operaciones * 1e-6; // tiempo en milisegundos
}

void imprimir_encabezado() {
    printf("\n");
    printf("========================================================================================================================================\n");
    printf("%-8s %-12s %-15s %-12s %-15s %-12s %-15s\n",
        "N", "Term.Rec.", "Tiempo Rec.", "Cota Inf.", "Tiempo Cota", "Term.Iter.", "Tiempo Iter.");
    printf("========================================================================================================================================\n");
}

void imprimir_fila(int n) {
    char buffer_tiempo_rec[30], buffer_tiempo_cota[30], buffer_tiempo_iter[30];
    char buffer_cota[20], buffer_fibonacci[20], buffer_ops_iter[20];
    
    // Calcular tiempo teórico basado en la cota inferior (solo cálculos matemáticos)
    double tiempo_recursivo = calcular_tiempo_teorico_recursivo(n);
    double terminos_recursivo_double = pow(2.0, n / 2.0);
    

    double tiempo_cota = log2(n) * 1e-6; // log₂(n) operaciones × 1ns cada una, en milisegundos
    
    double terminos_iterativo_double = (double)(n + 1);
    double tiempo_iterativo = (n + 1) * 1e-6;
    
    formatear_numero_grande(terminos_recursivo_double, buffer_cota);
    formatear_numero_grande(terminos_recursivo_double, buffer_fibonacci); 
    formatear_numero_grande(terminos_iterativo_double, buffer_ops_iter);
    
    formatear_tiempo(tiempo_recursivo, buffer_tiempo_rec);
    formatear_tiempo(tiempo_cota, buffer_tiempo_cota);
    formatear_tiempo(tiempo_iterativo, buffer_tiempo_iter);
    
    printf("%-8d %-12s %-15s %-12s %-15s %-12s %-15s\n",
           n, buffer_cota, buffer_tiempo_rec, 
           buffer_fibonacci, buffer_tiempo_cota, 
           buffer_ops_iter, buffer_tiempo_iter);
}

int main(int argc, char *argv[]) {
    int opt;
    // Parámetros fijos por defecto
    int k = 20;  // número de filas
    int A = 10;  // valor inicial de n
    int B = 10;  // incremento
    
     while ((opt = getopt(argc, argv, "k:A:B:")) != -1) {
        switch (opt) {
            case 'k':
                k = atoi(optarg);
                break;
            case 'A':
                A = atoi(optarg);
                break;
            case 'B':
                B = atoi(optarg);
                break;
            default:
                fprintf(stderr, "Uso: %s [-k <filas>] [-A <inicio>] [-B <incremento>]\n", argv[0]);
                return 1;
        }
    }
    
    printf("=== Análisis de Complejidad del Algoritmo de Fibonacci ===\n");
    printf("Parámetros: k=%d filas, desde n=%d, incremento=%d\n", k, A, B);
    printf("\nDescripción de columnas:\n");
    printf("- Term.Rec.: Número de términos calculados por el algoritmo recursivo (2^n/2)\n");
    printf("- Tiempo Rec.: Tiempo teórico si cada término toma 1 nanosegundo\n");
    printf("- Cota Inf.: Cota inferior de complejidad (2^n/2)\n");
    printf("- Tiempo Cota: Tiempo teórico para calcular la cota (log₂(n) × 1ns)\n");
    printf("- Term.Iter.: Términos calculados por el algoritmo iterativo (n+1)\n");
    printf("- Tiempo Iter.: Tiempo teórico del algoritmo iterativo\n");
    printf("Valores a analizar: ");
    for (int i = 0; i < k && i < 10; i++) {
        printf("%d", A + (i * B));
        if (i < k-1 && i < 9) printf(", ");
    }
    if (k > 10) printf("...");
    printf("\n");
    
    imprimir_encabezado();
    
    for (int i = 0; i < k; i++) {
        int n = A + (i * B);
        imprimir_fila(n);
    }

    printf("========================================================================================================================================\n");
    return 0;
}

