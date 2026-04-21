#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "aserciones.h"
#include "cadenas.h"
#include "../recursividad.h"

int main() {
    imprimir_titulo("Tests para la mafia china");
    assert(strcmp(chinos(1), "(-.-)") == 0);
    assert(strcmp(chinos(2), "(-.(-.-).-)" ) == 0);

    char *r=  chinos(4);

    assert(strcmp(r, "(-.(-.(-.(-.-).-).-).-)" ) == 0);
    assert(strcmp(r, "(-.(-.(-.-).-).-)" ) != 0);

    free(r);

    return 0;
}
