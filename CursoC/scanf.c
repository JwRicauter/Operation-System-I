#include<stdio.h>

int main(){
	
	int numero, resultado;

	printf("Ingrese un numero entero..\n");
	scanf("%d", &numero);

	printf("el numero ahora vale: %d\n", numero);

	resultado = numero * numero;
	printf("el resultado es: %d\n", resultado);

	return 0;
}