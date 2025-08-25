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
        sprintf(buffer, "%.2e anios", y);
    } else if (y >= 1000.0) {
        sprintf(buffer, "%.1fK anios", y / 1000.0);
    } else if (y >= 1.0) {
        sprintf(buffer, "%.0f anios", y);
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

// Variables globales ya no necesarias para conteo de operaciones
// long long operaciones_recursivo = 0;
// long long operaciones_iterativo = 0;
// long long operaciones_cota = 0;

// Funciones de cálculo real eliminadas para optimización
// (solo mantenemos cálculos teóricos)

double calcular_tiempo_teorico_recursivo(int n) {
    // Calcular número de operaciones usando la cota inferior 2^(n/2)
    double operaciones = pow(2.0, n / 2.0);
    // Convertir a tiempo asumiendo 1 nanosegundo por operación
    // 1 nanosegundo = 1e-6 milisegundos
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
    
    // Calcular el valor real de Fibonacci usando fórmula de Binet (rápido)
    double phi = (1.0 + sqrt(5.0)) / 2.0;
    double valor_fibonacci_double = (pow(phi, n) - pow(-phi, -n)) / sqrt(5.0);
    
    // Tiempo teórico para calcular la cota (complejidad logarítmica)
    double tiempo_cota = log2(n) * 1e-6; // log₂(n) operaciones × 1ns cada una, en milisegundos
    
    // Operaciones iterativas (igual a n + 1)
    double terminos_iterativo_double = (double)(n + 1);
    // Tiempo teórico iterativo ((n + 1) operaciones * 1ns cada una)
    double tiempo_iterativo = (n + 1) * 1e-6; // en milisegundos
    
    // Formatear los números grandes
    formatear_numero_grande(terminos_recursivo_double, buffer_cota);
    formatear_numero_grande(terminos_recursivo_double, buffer_fibonacci); // Mostrar cota inferior 2^(n/2)
    formatear_numero_grande(terminos_iterativo_double, buffer_ops_iter);
    
    // Formatear los tiempos en buffers
    formatear_tiempo(tiempo_recursivo, buffer_tiempo_rec);
    formatear_tiempo(tiempo_cota, buffer_tiempo_cota);
    formatear_tiempo(tiempo_iterativo, buffer_tiempo_iter);
    
    // Imprimir la fila con alineación fija
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
    
    // Generar k filas desde A, incrementando B en cada fila
    for (int i = 0; i < k; i++) {
        int n = A + (i * B);
        imprimir_fila(n);
    }
    
    /*while ((opt = getopt(argc,argv, "k:")) != -1) {
        switch (opt) {
            case 'k':
            k= atoi(optarg);
            break;
        default:
            fprint(stderr, "Uso: %s -k <numero>\n", argv[0]);
            return 1;
        }
    
    }*/
    printf("========================================================================================================================================\n");
    return 0;
}

