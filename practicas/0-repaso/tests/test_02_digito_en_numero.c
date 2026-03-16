#include <stdio.h>
#include <assert.h>

#include "aserciones.h"
#include "../repaso.h"
#include "cadenas.h"


int main() {
    imprimir_titulo("Tests de Ejercicio 2");

    assert(digitoEnNumero(987, 11)== false);
    assert(digitoEnNumero(987, 7)== true); // True
    assert(digitoEnNumero(987, 6)== false); // False

    return 0;
}
