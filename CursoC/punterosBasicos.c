#include <stdio.h>


int main(){
	int b = 5;
	int * puntero1;
	puntero1 = &b;

	int resultado = 10 + *puntero1;
	printf("resultado: %d\n", resultado);

	b = 3;

	printf("b: %d\n", b);
	printf("puntero1: %d\n", puntero1);
	printf("*puntero1: %d\n", *puntero1);

	return 0;
}