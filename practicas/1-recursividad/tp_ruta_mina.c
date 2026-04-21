#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

/*
 Implementar un programa que resuelva un mapa en grilla, 
 encontrando recursivamente un camino desde un punto de inicio hasta una salida.
 El programa debe leer un mapa desde un archivo de entrada,
 calcular la mejor ruta posible y escribir el resultado en un archivo de salida.
 La búsqueda debe hacerse de forma recursiva, 
 explorando alternativas hasta encontrar la mejor solución según las reglas del enunciado.

 En el mapa hay:

        Un inicio, representado por I
        Una salida, representada por S
        Celdas bloqueadas, representadas por #
        Celdas libres, representadas por .
        Celdas con tesoro, representadas por dígitos 0 a 9 (su valor suma puntaje)

Se puede mover en 4 direcciones:

        Arriba
        Derecha
        Abajo
        Izquierda
        Restricciones:

        No se puede salir de la grilla
        No se puede pasar por celdas bloqueadas
        No se puede visitar dos veces la misma celda dentro de un mismo camino

Entre todas las rutas válidas de I a S, se elige:

        La de mayor puntaje total recolectado.
        hay empate, la de menor cantidad de pasos.
        Si persiste el empate, la de menor secuencia de movimientos en orden lexicográfico.

Para que el resultado sea determinístico y fácil de testear, usar este orden lexicográfico de movimientos:

        A = Arriba
        B = Abajo
        D = Derecha
        I = Izquierda

    Formato de salida
        Si existe al menos un camino válido:

            RESULTADO: ENCONTRADO
            PUNTAJE: <puntaje_total>
            PASOS: <cantidad_de_pasos>
            MOVIMIENTOS: <secuencia>
            CAMINO: (f1,c1) -> (f2,c2) -> ... -> (fk,ck)
        
            Si no existe camino:

            RESULTADO: SIN_CAMINO

Archivos de prueba
    Se recomienda incluir al menos estos casos:

        Caso base con una ruta clara
        Caso sin camino posible
        Caso con múltiples rutas que empaten en puntaje y requieran desempate por pasos
        Caso con empate en puntaje y pasos que requiera desempate lexicográfico

Ejemplo de entrada: laberinto 6x7

6 7
I2..#..
.#3.#S.
..#..#.
1..4...
.##..5.
...#...
*/

// Separar en funciones: 1) lectura, 2) resolución recursiva, 3) escritura y 4) liberación de memoria.

/// Estructuras para representar el mapa, la posición y la solución
struct Posicion {
    unsigned int fila;
    unsigned int columna;
};

struct Mapa {
    char **celdas;
    int filas;
    int columnas;
    struct Posicion inicio;
    struct Posicion salida;
};

struct Solucion {
    bool encontrada;
    int puntaje;
    int pasos;
    char *movimientos;
    struct Posicion *camino;
    int largo_camino;
};

// 1) función para leer el mapa desde un archivo y guardarlo en el struct Mapa
void leer_mapa(const char *nombre_archivo, struct Mapa *mapa){
    FILE *entrada;
    char linea[100]; //buffer para ir guardando cada línea que leamos
    entrada = fopen(nombre_archivo, "r");
    if (entrada == NULL) {
        printf("no se pudo abrir el archivo\n");
        exit(1);
    } 
    else {
        printf("Archivo abierto con exito\n"); // BORRAR printf de prueba
        printf("--------------------------------------------------\n");

        // 2) leer el mapa linea por linea usando fgets() y guardarlo en el struct Mapa
        fgets(linea, sizeof(linea), entrada); // leer la primera línea con las dimensiones
        
        sscanf(linea, "%d %d", &mapa->filas, &mapa->columnas); // extraer filas y columnas

        // 3) reservar memoria para las celdas del mapa
        mapa->celdas = (char **)malloc(mapa->filas * sizeof(char *));
        for (int i=0; i < mapa->filas; i++) {
            mapa->celdas[i] = (char *)malloc(mapa->columnas * sizeof(char));
        }
        // 4) leer cada linea del mapa y guardar en el struct Mapa, identificando la posición de inicio y salida
        for (int i=0; i < mapa->filas; i++) {
            fgets(linea, sizeof(linea), entrada); // leer una linea del mapa
            
            for (int j=0; j < mapa->columnas; j++) {
                mapa->celdas[i][j] = linea[j]; // guardar el caracter en la estructura

                // identificar la posición de inicio (I) y salida (S)
                if (linea[j] == 'I') {
                    mapa->inicio.fila = i;
                    mapa->inicio.columna = j;
                } else if (linea[j] == 'S') {
                    mapa->salida.fila = i;
                    mapa->salida.columna = j;
                }
            }
        }
        // 5) cerramos el archivo para liberar memoria
        fclose(entrada);
    }
}

// 2) función para resolver el problema de forma recursiva
void resolver_ruta(){

}

// 3) función para crear el archivo de salida con el resultado
void escribir_resultado(const char *nombre_archivo, struct Solucion *solucion){
    FILE *salida;
    salida = fopen(nombre_archivo, "w");
    if(salida == NULL) {
        printf("error al crear el archivo de salida\n");
        exit(1);
    }
        
    if (solucion->encontrada) {
        fprintf(salida, "RESULTADO: ENCONTRADO\n");
        fprintf(salida, "PUNTAJE: %d\n", solucion->puntaje);
        fprintf(salida, "PASOS: %d\n", solucion->pasos);
        fprintf(salida, "MOVIMIENTOS: %s\n", solucion->movimientos);
        fprintf(salida, "CAMINO: ");
        for (int i=0; i < solucion->largo_camino; i++) {
            fprintf(salida, "(%d,%d)", solucion->camino[i].fila +1, solucion->camino[i].columna +1);
            if (i < solucion->largo_camino - 1) {
                fprintf(salida, " -> ");
            }
        }
        fprintf(salida, "\n");
    } else {
        fprintf(salida, "RESULTADO: SIN_CAMINO\n");
    }

    fclose(salida); 
}

// 4) función para liberar la memoria asignada al mapa y a la solución
void liberar_memoria(struct Mapa *mapa, struct Solucion *solucion){
    for (int i=0; i < mapa->filas; i++) {
        free(mapa->celdas[i]);
    }
    free(mapa->celdas);
    
    if (solucion->movimientos) {
        free(solucion->movimientos);
    }
    if (solucion->camino) {
        free(solucion->camino);
    }
}




















/* void recorrido_recursivo(struct Mapa *mapa, struct Solucion *mejor_solucion, struct Posicion actual, int puntaje_actual, int pasos_actuales, char *movimientos_actuales, bool **visitados){
        if(actual.fila == mapa->salida.fila && actual.columna == mapa->salida.columna){
            // Caso base: llegamos a la salida
            // Actualizamos mejor_solucion si es necesario
            if (!mejor_solucion->encontrada || puntaje_actual > mejor_solucion->puntaje) {
                mejor_solucion->encontrada = true;
                mejor_solucion->puntaje = puntaje_actual;
                mejor_solucion->pasos = pasos_actuales;
                mejor_solucion->movimientos = strdup(movimientos_actuales);
                // Copiar el camino actual a mejor_solucion->camino
            } else if (puntaje_actual == mejor_solucion->puntaje) {
                if (pasos_actuales < mejor_solucion->pasos) {
                    mejor_solucion->pasos = pasos_actuales;
                    mejor_solucion->movimientos = strdup(movimientos_actuales);
                    // Copiar el camino actual a mejor_solucion->camino
                } 
                else if (pasos_actuales == mejor_solucion->pasos) {
                    
                    if (strcmp(movimientos_actuales, mejor_solucion->movimientos) < 0) {
                        mejor_solucion->movimientos = strdup(movimientos_actuales);
                        // Copiar el camino actual a mejor_solucion->camino
                    }
                }
            }
        }
    }
*/   

    // Separar en funciones: lectura, resolución recursiva, escritura y liberación de memoria.



/*
 1) Abrir el archivo de entrada usando fopen() y validar entrada.
 2) Leer el mapa línea por línea usando fgets() y almacenarlo en una estructura adecuada
 3) Implementar la función recursiva para resolver el problema
    - En la función recursiva hay que:
         definir el caso base (si posición actual == S llegué a la salida)
         verificar la posición actual
         ir guardando el puntaje que llevo
         ir guardando las celdas que ya visité ()
         ir guardando la secuencia de movimientos de la solucuión actual
         ir explorando las 4 direcciones posibles (A, B, D, I)

4) Comparar la solución encontrada con la mejor solución global y actualizarla si es necesario
5) Al finalizar la búsqueda, escribir el resultado en el archivo de salida siguiendo el formato especificado


*/