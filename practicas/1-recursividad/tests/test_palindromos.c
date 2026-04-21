#include <assert.h>
#include <stdio.h>

#include "aserciones.h"
#include "cadenas.h"
#include "../recursividad.h"

int main() {
    imprimir_titulo("Tests para palíndromos");

    assert(esPalindromo("neuquen")==true);
    assert(esPalindromo("palindromo")== false);

    return 0;
}
