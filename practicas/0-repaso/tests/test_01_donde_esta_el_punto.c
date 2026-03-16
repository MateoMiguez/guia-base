#include <stdio.h>
#include <assert.h>

#include "aserciones.h"
#include "../repaso.h"
#include "cadenas.h"


int main() {
    imprimir_titulo("Tests de Ejercicio 1");

    assert(dondeEstaElPunto(0, 0, 2, 1, 1 )== INTERNO); // INTERNO
    assert(dondeEstaElPunto(0, 0, 1, 1, 1 )== EXTERNO); // EXTERNO
    assert(dondeEstaElPunto(0, 0, 1, 1, 0 )== EN_CIRCUNFERENCIA); // EN_CIRCUNFERENCIA

    return 0;
}
