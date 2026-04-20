#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#include "aserciones.h"
#include "cadenas.h"
#include "../recursividad.h"

int main() {
    imprimir_titulo("TP Integrador - Ruta de Rescate en Mina");

    resolver_ruta_mina("archivos/prueba1_entrada.txt", "archivos/prueba1_salida.txt");
    assert(file_eq("archivos/prueba1_salida_esperada.txt", "archivos/prueba1_salida.txt"));

    resolver_ruta_mina("archivos/prueba2_entrada.txt", "archivos/prueba2_salida.txt");
    assert(file_eq("archivos/prueba2_salida_esperada.txt", "archivos/prueba2_salida.txt"));

    return 0;
}