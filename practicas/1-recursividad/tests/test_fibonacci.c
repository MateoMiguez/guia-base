#include <assert.h>
#include <stdio.h>

#include "aserciones.h"
#include "cadenas.h"
#include "../recursividad.h"


int main() {
    imprimir_titulo("Tests para término de Fibonacci");

    assert(terminoSerieDeFibonacci(0)== 0);
    assert(terminoSerieDeFibonacci(1)== 1);
    assert(terminoSerieDeFibonacci(6)== 8);

    return 0;
}
