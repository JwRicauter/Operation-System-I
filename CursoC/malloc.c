#include <stdio.h>
#include <stdlib.h>

int main(){
	
	// En memoria Estatica
	// int a;
	// a = 3;
	// printf("a:%d", a);

	void * p1 = NULL;
	printf("un int ocupa: %d\n", sizeof(int));
	p1 = malloc(sizeof(int));		// Reserva el lugar para un entero.

	// Ahora tengo que convertir p1 en int * haciendo casting

	int * p1_convertido = (int *)p1;
	*p1_convertido = 3;

	printf("p1 convertido: %d\n", *p1_convertido);


	return 0;
}