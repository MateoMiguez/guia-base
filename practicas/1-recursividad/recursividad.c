#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "recursividad.h"

bool esCapicua(int numero) {
    numero = abs(numero);

    if(numero<10) return true; 

    char digito[16];
    sprintf(digito, "%d", numero);

    int longitud = strlen(digito);

    if(digito[0] == digito[longitud - 1]){
        char SubDigito[16];
        for(int i = 0; i < longitud - 2; i++){
            SubDigito [i] = digito [i + 1];
        }
        SubDigito [longitud - 2] = '\0';

        int NuevoNumero;
        sscanf(SubDigito, "%d", &NuevoNumero);

        return esCapicua(NuevoNumero);
    } else {
        return false;
    }
}

bool esPalindromo(char *palabra) {
    int longitud = strlen(palabra);

    if(longitud <= 1) return true;

    if(palabra[0] != palabra[longitud - 1]) return false;

    char SubPalabra[longitud];
    for(int i = 0; i < longitud - 2; i++){
        SubPalabra [i] = palabra[i + 1];
    }
    SubPalabra [longitud - 2] = '\0';

    return esPalindromo(SubPalabra);
}

int productoRecursivo(int m, int n) {

    if(n==0) return 0;
    if(n==1) return m;

    if(n<0){
        m=-m;
        n=-n; 
    }

    return m + productoRecursivo(m, n - 1);
}

int terminoSerieDeFibonacci(int n) {
/*
F0 = 0
F1 = 1
F2 = 1
Fn = Fn-1 + Fn-2
*/

if (n == 0) return 0;
if (n == 1) return 1;

return terminoSerieDeFibonacci(n - 1) + terminoSerieDeFibonacci(n + 2);
}

bool esDivisiblePor7(int n) {

    if(n < 70 && n %7 == 0) return true;

    return esDivisiblePor7((n / 10) - ((n % 10)*2));
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

int *explosion(int n, int b, int *cantidad) {

    if(n <= b){
        int *result = malloc(sizeof(int));
        result[0] = n;
        *cantidad = 1;
        return result;
    }

    int n1 = n / b;
    int n2 = n - n1;

    int cantidad2 = 0;
    int *expN2 = explosion(n2, b, &cantidad2);

    int *result = malloc((1 + cantidad2) * sizeof(int));

    result[0] = n1;

    for (int i = 0; i < cantidad2; i++) {
        result[i + 1] = expN2[i];
    }

    *cantidad = 1 + cantidad2;

    free(expN2);

    return result;
}

char *chinos(unsigned int nivel) {

    if(nivel == 1){
        char *resultado = malloc(6);
        strcpy(resultado, "(-.-)");
        return resultado; 
    }

    char *anterior = chinos(nivel - 1);

    int nuevoTam = strlen(anterior) + 6;
    char *resultado = malloc(nuevoTam);

    sprintf(resultado, "(-.%s.-)", anterior);

    free(anterior);

    return resultado;
}

char *agregarSeparadoresRecursivo(char *numero, int indice, int contador) {

}

char *agregarSeparadorMiles(char *numero) {
 int len = strlen(numero);

    if (len <= 3) {
        char *res = malloc(len + 1);
        strcpy(res, numero);
        return res;
    }

    int primeros = len % 3;
    if (primeros == 0) primeros = 3;

    char inicio[20];
    for (int i = 0; i < primeros; i++) {
        inicio[i] = numero[i];
    }
    inicio[primeros] = '\0';


    //numero es un char * (un puntero al inicio del string). entonces (numero + primeros) es un puntero que apunta más adelante en el string
    char *resto = agregarSeparadorMiles(numero + primeros);

    char *res = malloc(strlen(inicio) + strlen(resto) + 2);
    sprintf(res, "%s.%s", inicio, resto);

    free(resto);

    return res;
}
