#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>
#include "aserciones.h"
#include "cadenas.h"
#include "../recursividad.h"
#include "../tp_ruta_mina.c"

bool file_eq(const char *archivo_esperado, const char *archivo_generado) {
    FILE *esperado = fopen(archivo_esperado, "r");
    FILE *generado = fopen(archivo_generado, "r");

    if (!esperado || !generado) {
        if (esperado) fclose(esperado);
        if (generado) fclose(generado);
        return false;
    }

    char linea_esperada[256];
    char linea_generada[256];
    bool son_iguales = true;

    while (fgets(linea_esperada, sizeof(linea_esperada), esperado) != NULL) {
        if (fgets(linea_generada, sizeof(linea_generada), generado) == NULL) {
            son_iguales = false;
            break;
        }

        if (strcmp(linea_esperada, linea_generada) != 0) {
            son_iguales = false;
            break;
        }
    }

    if (fgets(linea_generada, sizeof(linea_generada), generado) != NULL) {
        son_iguales = false;
    }

    fclose(esperado);
    fclose(generado);
    return son_iguales;
}

int main() {
    imprimir_titulo("TP Integrador - Ruta de Rescate en Mina");
    
    resolver_ruta_mina("../../../practicas/1-recursividad/prueba1_entrada.txt", "prueba1_salida.txt");
    
    assert(file_eq("prueba1_salida.txt", "../../../practicas/1-recursividad/prueba1_salidaesperada.txt"));
    
    printf("Test 1 pasado: prueba1_salida coincide con prueba1_salidaesperada\n");

    resolver_ruta_mina("../../../practicas/1-recursividad/prueba2_entrada.txt", "prueba2_salida.txt");
    
    assert(file_eq("prueba2_salida.txt", "../../../practicas/1-recursividad/prueba2_salidaesperada.txt"));
    
    printf("Test 2 pasado: prueba2_salida coincide con prueba2_salidaesperada\n");
    return 0;
}