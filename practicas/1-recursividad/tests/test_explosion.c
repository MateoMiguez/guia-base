#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include "aserciones.h"
#include "cadenas.h"
#include "../recursividad.h"

int main() {
    imprimir_titulo("Tests del Ejercicio de Explosión saraza");

    int size;
    int *resul;

    int esperado1[] = {3, 2, 1, 1, 3};
    int esperado2[] = {4, 3, 2, 2, 1, 1, 1, 1, 5};

    resul = explosion(10, 3 , &size); // => {3, 2, 1, 1, 3}
    assert(size == 5);
    for (int i = 0; i < size; i++) {
        assert(resul[i] == esperado1[i]);
    }

    resul = explosion(20, 5 , &size); // => {4, 3, 2, 2, 1, 1, 1, 1, 5}
    assert(size == 9);
    for (int i = 0; i < size; i++) {
        assert(resul[i] == esperado2[i]);
    }


    return 0;
}
