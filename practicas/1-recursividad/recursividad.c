#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "recursividad.h"

bool esCapicua(int numero) {
}

bool esPalindromo(char *palabra) {
}

int productoRecursivo(int m, int n) {
}

int terminoSerieDeFibonacci(int n) {
}

bool esDivisiblePor7(int n) {
}

void explosionRecursiva(int n, int b, int *result, int *cant) {
    if(n <= b){
        result[(*cant)] = n;
        (*cant)++;
        return;
    }else{
        int n1 = n / 2;
        int n2 = n - n1;
        explosionRecursiva(n1, b, result, cant);
        explosionRecursiva(n2, b, result, cant);
    }

}

int *explosion(int n, int b, int *size) {
    int *result = malloc(1000 * sizeof(int));
    explosionRecursiva(n, b, result, size);
    return result;
}

char *chinos(unsigned int nivel) {
    if(nivel==1){
        char *result= malloc(sizeof(char)* 6);
        strcpy(result,"(-.-)");
        return result;
    }
    char *nivelAnterior= chinos(nivel - 1);
    char *result = malloc(sizeof(char) * (6 + strlen(nivelAnterior) + 1));
    sprintf(result,"(-.%s.-)", nivelAnterior);
    free(nivelAnterior);
    return result;
}

char *agregarSeparadoresRecursivo(char *numero, int indice, int contador) {

}

char *agregarSeparadorMiles(char *numero) {

}
