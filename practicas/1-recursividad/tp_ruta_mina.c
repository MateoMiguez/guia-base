#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "recursividad.h"

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

// declaramos todas las funciones
void leer_mapa(const char *nombre_archivo, struct Mapa *mapa);

void resolver_ruta(struct Mapa *mapa, struct Solucion *solucion);

void resolver_ruta_rec(struct Mapa *mapa, struct Solucion *mejor_solucion, 
                       struct Posicion actual, int puntaje_actual, int pasos_actuales, 
                       char *movimientos_actuales, struct Posicion *camino_actual, 
                       int largo_camino_actual, bool **visitados);

void escribir_resultado(const char *nombre_archivo, struct Solucion *solucion);

void liberar_memoria(struct Mapa *mapa, struct Solucion *solucion);

// implementación de las funciones

void leer_mapa(const char *nombre_archivo, struct Mapa *mapa){
    FILE *entrada;
    char linea[100];
    entrada = fopen(nombre_archivo, "r");
    if (entrada == NULL) {
        printf("no se pudo abrir el archivo\n");
        return;
    } 
    else {
        printf("Archivo abierto con exito\n"); // BORRAR printf de prueba
        printf("--------------------------------------------------\n");

        fgets(linea, sizeof(linea), entrada); // leer la primera línea con las dimensiones
        sscanf(linea, "%d %d", &mapa->filas, &mapa->columnas);

        // reservar memoria para las celdas del mapa
        mapa->celdas = (char **)malloc(mapa->filas * sizeof(char *));
        for (int i=0; i < mapa->filas; i++) {
            mapa->celdas[i] = (char *)malloc(mapa->columnas * sizeof(char));
        }

        for (int i=0; i < mapa->filas; i++) {
            fgets(linea, sizeof(linea), entrada);
            
            for (int j=0; j < mapa->columnas; j++) {
                mapa->celdas[i][j] = linea[j]; // guardar el caracter en la struct

                if (linea[j] == 'I') {
                    mapa->inicio.fila = i;
                    mapa->inicio.columna = j;
                } else if (linea[j] == 'S') {
                    mapa->salida.fila = i;
                    mapa->salida.columna = j;
                }
            }
        }
        fclose(entrada);
    }
}

void resolver_ruta_rec(struct Mapa *mapa, struct Solucion *mejor_solucion, 
                       struct Posicion actual, int puntaje_actual, int pasos_actuales, 
                       char *movimientos_actuales, struct Posicion *camino_actual, 
                       int largo_camino_actual, bool **visitados) {
    
    // caso base: se encontró la salida
    if (actual.fila == mapa->salida.fila && actual.columna == mapa->salida.columna) {
        // guardar la posicion de salida en el camino
        camino_actual[largo_camino_actual] = actual;
        largo_camino_actual++;
        
        // verificar si esta es la mejor solucion
        if (!mejor_solucion->encontrada || puntaje_actual > mejor_solucion->puntaje || (puntaje_actual == mejor_solucion->puntaje && pasos_actuales < mejor_solucion->pasos) ||
            (puntaje_actual == mejor_solucion->puntaje && pasos_actuales == mejor_solucion->pasos && 
             strcmp(movimientos_actuales, mejor_solucion->movimientos) < 0)) {
            
            mejor_solucion->encontrada = true;
            mejor_solucion->puntaje = puntaje_actual;
            mejor_solucion->pasos = pasos_actuales;
            
            free(mejor_solucion->movimientos);
            mejor_solucion->movimientos = malloc(strlen(movimientos_actuales) + 1);
            strcpy(mejor_solucion->movimientos, movimientos_actuales);
            
            free(mejor_solucion->camino);
            mejor_solucion->camino = malloc(largo_camino_actual * sizeof(struct Posicion));
            for (int i = 0; i < largo_camino_actual; i++) {
                mejor_solucion->camino[i] = camino_actual[i];
            }
            mejor_solucion->largo_camino = largo_camino_actual;
        }
        return;
    }
    
    // marcar posicion actual como visitada
    visitados[actual.fila][actual.columna] = true;
    
    // vector de direcciones en orden lexicografico: A(Arriba), B(Abajo), D(Derecha), I(Izquierda)
    int direcciones[4][2] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
    char movimientos_dir[4] = {'A', 'B', 'D', 'I'};
    
    // avanzar en las 4 direcciones en orden
    for (int dir = 0; dir < 4; dir++) {
        struct Posicion siguiente;
        siguiente.fila = actual.fila + direcciones[dir][0];
        siguiente.columna = actual.columna + direcciones[dir][1];
        
        // verificar limites del la mina
        if (siguiente.fila < 0 || siguiente.fila >= mapa->filas || 
            siguiente.columna < 0 || siguiente.columna >= mapa->columnas) {
            continue;
        }
        
        // verificar si no esta visitado y no es una celda bloqueada
        if (visitados[siguiente.fila][siguiente.columna] || 
            mapa->celdas[siguiente.fila][siguiente.columna] == '#') {
            continue;
        }
        
        // calcular puntos de la siguiente celda
        int puntos_siguiente = 0;
        char celda = mapa->celdas[siguiente.fila][siguiente.columna];
        if (celda >= '0' && celda <= '9') {
            puntos_siguiente = celda - '0';
        }
        
        // crear el nuevo string de movimientos
        int len_movimientos = strlen(movimientos_actuales);
        char *nuevos_movimientos = malloc(len_movimientos + 2);
        strcpy(nuevos_movimientos, movimientos_actuales);
        nuevos_movimientos[len_movimientos] = movimientos_dir[dir];
        nuevos_movimientos[len_movimientos + 1] = '\0';
        
        // guardar posición en el camino
        camino_actual[largo_camino_actual] = actual;
        
        // llamada recursiva
        resolver_ruta_rec(mapa, mejor_solucion, siguiente, 
                         puntaje_actual + puntos_siguiente, 
                         pasos_actuales + 1, 
                         nuevos_movimientos, camino_actual, 
                         largo_camino_actual + 1, visitados);
        
        free(nuevos_movimientos);
    }
    
    // Backtracking: desmarcar como visitado
    visitados[actual.fila][actual.columna] = false;
    return;
}

void resolver_ruta(struct Mapa *mapa, struct Solucion *solucion){
    // Inicializar solución
    solucion->encontrada = false;
    solucion->puntaje = 0;
    solucion->pasos = 0;
    solucion->movimientos = malloc(1);
    strcpy(solucion->movimientos, "");
    solucion->camino = malloc(mapa->filas * mapa->columnas * sizeof(struct Posicion));
    solucion->largo_camino = 0;
    
    // Crear matriz de visitados
    bool **visitados = malloc(mapa->filas * sizeof(bool *));
    for (int i = 0; i < mapa->filas; i++) {
        visitados[i] = malloc(mapa->columnas * sizeof(bool));
        for (int j = 0; j < mapa->columnas; j++) {
            visitados[i][j] = false;
        }
    }
    
    // Buffer para guardar el camino durante la búsqueda
    struct Posicion *camino_buffer = malloc(mapa->filas * mapa->columnas * sizeof(struct Posicion));
    
    // Iniciar búsqueda desde la posición inicial
    char *mov_inicial = malloc(1);
    strcpy(mov_inicial, "");
    
    resolver_ruta_rec(mapa, solucion, mapa->inicio, 0, 0, mov_inicial, camino_buffer, 0, visitados);
    
    // Liberar memoria temporal
    free(mov_inicial);
    free(camino_buffer);
    for (int i = 0; i < mapa->filas; i++) {
        free(visitados[i]);
    }
    free(visitados);
}

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

void liberar_memoria(struct Mapa *mapa, struct Solucion *solucion){
    for (int i=0; i < mapa->filas; i++) {
        free(mapa->celdas[i]);
    }
    free(mapa->celdas);
    free(solucion->movimientos);
    free(solucion->camino);
}

void resolver_ruta_mina(const char *nombre_archivo_entrada, const char *nombre_archivo_salida) {
    struct Mapa mapa;
    struct Solucion solucion;
    
    leer_mapa(nombre_archivo_entrada, &mapa);
    resolver_ruta(&mapa, &solucion);
    escribir_resultado(nombre_archivo_salida, &solucion);
    liberar_memoria(&mapa, &solucion);

}

