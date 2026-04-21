#include <assert.h>
#include <stdio.h>

#include "aserciones.h"
#include "cadenas.h"
#include "../recursividad.h"

int main() {
    imprimir_titulo("Tests para Capicua");

    assert(esCapicua(1)== true);
    assert(esCapicua(-1)== true);

    assert(esCapicua(161)== true);

    assert(esCapicua(2992)== true);
    assert(esCapicua(-2992)== true);

    assert(esCapicua(2993)== false);
    assert(esCapicua(-2993)== false);


    return 0;
}
