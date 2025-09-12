#include "../inc/suma.h"
#include <stdio.h>

int main(void) {
    int suma = 0;

    suma += 5;
    acumular(&suma, 3);
    printf("Suma: %d\n", suma);

    return 0;
}