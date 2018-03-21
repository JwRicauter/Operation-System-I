#include<stdio.h>

int main(){
	printf("\n Bienvenido a la Fabrica de Vectores! \n");
	size_t largo;

	printf("Ingrese el largo de su vector: ");
	fflush(stdin);
	scanf(" %d", &largo);
	printf("El largo ingresado es: %d\n", largo);

	int vector1[largo];
	int i;
	for (i = 0; i < largo; i++){
		printf("Ingrese el valor para la posicion %d: ",i);
		fflush(stdin);
		scanf("%d", &vector1[i]);
	}

	printf("Ok, ahora vamos a imprimir su vector\n");

	// Ahora imprimo el vector
	for (i = 0; i < largo; i++){
		printf("Vector[%d]: %d\n", i, vector1[i]);

	}

	return 0;
}