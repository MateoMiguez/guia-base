#include <assert.h>
#include <stdio.h>

#include "aserciones.h"
#include "cadenas.h"
#include "../recursividad.h"

int main() {
    imprimir_titulo("Tests para producto");

    assert(productoRecursivo(3, 2)== 6);
    assert(productoRecursivo(5, -2)== -10);
    assert(productoRecursivo(-5, 2)== -10);
    assert(productoRecursivo(-5, -2)== 10);

    return 0;
}
