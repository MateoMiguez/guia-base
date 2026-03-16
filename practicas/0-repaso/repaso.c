#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "repaso.h"

enum Referencia dondeEstaElPunto(int xc, int yc, int rc, int xp, int yp) {
 // XC, YC puntos del centro de la circunferencia (h, k)
 // RC radio de la circunferencia (r)
 // XP, YP coordenadas del punto a comprobar (x, y)

 // (XP-XC)^2 + (YP-YC)^2

 int circunferencia = ((xp*xp) - 2*xp*xc + (xc*xc)) + ((yp*yp) - 2*yp*yc + (yc*yc)); 
 int radio = rc * rc;   // se puede hacer directo: (xp - xc) * (xp - xc) + (yp - yc) * (yp - yc)

   if(circunferencia < radio){
    return INTERNO;
   } else if(circunferencia == radio){
    return EN_CIRCUNFERENCIA;
   } else {
    return EXTERNO;
   }
}

bool digitoEnNumero(long n, short d) {

    if (d>9 || d<0)
    {
        return false;
    }

    while(n > 0){

        if(n % 10 == d){
            return true;
        } else {
            n /= 10;
        }
    }

    return false;
}

enum Referencia dondeEstaElPuntoBis(struct Punto centroC, int rc, struct Punto p) {
    int circunferencia = (p.x - centroC.x) * (p.x - centroC.x) + (p.y - centroC.y) * (p.y - centroC.y);
    int radio = rc * rc;

    if(circunferencia < radio){
    return INTERNO;
   } else if(circunferencia == radio){
    return EN_CIRCUNFERENCIA;
   } else {
    return EXTERNO;
   }

}

// Función para ordenar jugadores por cantidad de partidos jugados
struct Jugador *jugadoresOrdenadosPorCantDePartidos(struct Jugador equipo[CANT_JUGADORES]) {
    
    struct Jugador temp; // para poder cambiar

    for (int i = 1; i < CANT_JUGADORES; i++)
    {
        for (int j = i + 1; j < CANT_JUGADORES; j++)
        {
            if (equipo[i].partidosJugados < equipo[j].partidosJugados)
            {
                temp = equipo[i];
                equipo[i] = equipo[j];
                equipo[j] = temp;
            }
        }
    }
    return equipo;
}

// Función para ordenar jugadores por edad
struct Jugador *jugadoresOrdenadosPorEdad(struct Jugador equipo[CANT_JUGADORES]) {
    static struct Jugador ordenados[CANT_JUGADORES];
    for (int i = 0; i < CANT_JUGADORES; i++) {
        ordenados[i] = equipo[i];
    }

    for (int i = 0; i < CANT_JUGADORES - 1; i++) {
        for (int j = i + 1; j < CANT_JUGADORES; j++) {
            if (ordenados[i].edad > ordenados[j].edad) {
                struct Jugador temp = ordenados[i];
                ordenados[i] = ordenados[j];
                ordenados[j] = temp;
            }
        }
    }

    return ordenados;
}

// Función para calcular el promedio de partidos jugados dada una edad
float promedioDePartidosJugados(struct Jugador equipo[CANT_JUGADORES], int edad) {
    int suma = 0, contador = 0;
    for (int i = 0; i < CANT_JUGADORES; i++) {
        if (equipo[i].edad == edad) {
            suma += equipo[i].partidosJugados;
            contador++;
        }
    }
    return (contador == 0) ? 0 : (float)suma / contador;
}

Vivienda viviendaConMasHabitantes(int edificio[CANT_PISOS][CANT_DEPARTAMENTOS]) {
    int maxHabitantes = -1;
    Vivienda v;

    for (int i = 0; i < CANT_PISOS; i++) {
        for (int j = 0; j < CANT_DEPARTAMENTOS; j++) {
            if (edificio[i][j] > maxHabitantes) {
                maxHabitantes = edificio[i][j];
                v.piso = i;
                v.depto = 'A' + j;
            }
        }
    }

    return v;
}

// Función que devuelve el piso con más habitantes
int pisoConMasHabitantes(int edificio[CANT_PISOS][CANT_DEPARTAMENTOS]) {
    int maxHabitantes = 0, pisoMax = 0;

    for (int i = 0; i < CANT_PISOS; i++) {
        int suma = 0;
        for (int j = 0; j < CANT_DEPARTAMENTOS; j++) {
            suma += edificio[i][j];
        }
        if (suma > maxHabitantes) {
            maxHabitantes = suma;
            pisoMax = i;
        }
    }

    return pisoMax;
}

// Función que devuelve el número de departamentos vacíos
int cantidadDeViviendasVacias(int edificio[CANT_PISOS][CANT_DEPARTAMENTOS]) {
    int contador = 0;
    for (int i = 0; i < CANT_PISOS; i++) {
        for (int j = 0; j < CANT_DEPARTAMENTOS; j++) {
            if (edificio[i][j] == 0) {
                contador++;
            }
        }
    }
    return contador;
}

// Función que devuelve el promedio de habitantes por departamento
float promedioHabitantesPorVivienda(int edificio[CANT_PISOS][CANT_DEPARTAMENTOS]) {
    int total = 0, contador = 0;
    for (int i = 0; i < CANT_PISOS; i++) {
        for (int j = 0; j < CANT_DEPARTAMENTOS; j++) {
            total += edificio[i][j];
            contador++;
        }
    }
    return (float)total / contador;
}

void cantidadDeViviendasVaciasPorPiso(int edificio[CANT_PISOS][CANT_DEPARTAMENTOS], int vaciasPorPiso[CANT_PISOS]) {
    for (int i = 0; i < CANT_PISOS; i++) {
        vaciasPorPiso[i] = 0;
        for (int j = 0; j < CANT_DEPARTAMENTOS; j++) {
            if (edificio[i][j] == 0) {
                vaciasPorPiso[i]++;
            }
        }
    }
}

void viviendasVacias(int edificio[CANT_PISOS][CANT_DEPARTAMENTOS],
     Vivienda viviendasVacias[CANT_PISOS * CANT_DEPARTAMENTOS]) {
    int paso = 0;
    for (int i = 0; i < CANT_PISOS; i++) {
        for (int j = 0; j < CANT_DEPARTAMENTOS; j++) {
            if (edificio[i][j] == 0) {
                    viviendasVacias[paso].piso = i;
                    viviendasVacias[paso].depto = 'A' + j; // corrección
                    paso++;
            }    
        }
    }

}

void procesarArchivo(const char *nombreArchivo) {
    FILE *f = fopen(nombreArchivo, "r");
    if (!f) {
        perror("No se pudo abrir el archivo");
        return;
    }

    int edificio[CANT_PISOS][CANT_DEPARTAMENTOS];

    for (int i = 0; i < CANT_PISOS; i++) {
        for (int j = 0; j < CANT_DEPARTAMENTOS; j++) {
            if (fscanf(f, "%d", &edificio[i][j]) != 1) {
                printf("Error al leer datos en la posición [%d][%d]\n", i, j);
                fclose(f);
                return;
            }
        }
    }

    fclose(f);
}
