# pr00-aa

Este programa en C es una herramienta de línea de comandos para analizar y comparar las complejidades algorítmicas de los enfoques recursivo e iterativo para calcular la secuencia de Fibonacci.

Uso
Parámetros de la línea de comandos
Puedes usar los siguientes argumentos opcionales:

 -k <filas>: Especifica el número de filas de la tabla a generar.

 -A <inicio>: Define el valor inicial de n.

 -B <incremento>: Establece el incremento de n para cada fila.


Análisis de complejidad
El programa analiza y compara el rendimiento teórico de tres enfoques para calcular los números de Fibonacci:

Algoritmo Recursivo (Ingenuo): Se modela su complejidad de tiempo, que crece exponencialmente, a través de la cota inferior Ω(2^(n/2)). Esto demuestra por qué este enfoque es inviable para valores grandes de n.

Algoritmo Iterativo: Su complejidad de tiempo es lineal, O(n). Este método es muy eficiente y escalable, ya que el número de operaciones crece de forma directamente proporcional a n.

La salida del programa formatea los valores y tiempos de manera legible, usando unidades como ms (milisegundos), s (segundos), min (minutos), h (horas), d (días) y anios (años) para ilustrar la rapidez con la que el tiempo de ejecución de un algoritmo exponencial se vuelve astronómico.
