#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "aserciones.h"
#include "cadenas.h"
#include "../recursividad.h"

int main() {
    imprimir_titulo("Tests para la mafia china");

    char *r=  chinos(4);

    assert(strcmp(r, "(-.(-.(-.(-.-).-).-).-)" ) == 0);
    assert(strcmp(r, "(-.(-.(-.-).-).-)" ) != 0);

    free(r);

    return 0;
}
