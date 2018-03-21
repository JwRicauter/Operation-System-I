#include <stdio.h>
#include <stdlib.h>

// realloc sirve para asignar el tamaño del bloque asignado anteriormente

int main(){
	
	void * vector_din = NULL;
	int * vector_convertido = NULL;
	int * vector_din_6lug = NULL;
	vector_din = malloc(4 * sizeof(int));

	if(vector_din == NULL)printf("No se puso asignar en memoria\n");
	// Convertir el vector din

	vector_convertido = (int*)vector_din;
	vector_convertido[0] = 1;
	vector_convertido[1] = 2;
	vector_convertido[2] = 3;
	vector_convertido[3] = 4;

	// Ahora quiero 6 lugares

	vector_din_6lug = realloc(vector_din, 6 * sizeof(int));
	if(vector_din_6lug == NULL)printf("No se puso asignar en memoria\n");
	vector_convertido = (int*)vector_din_6lug;

	printf("El nuevo vector en el [3]: %d\n", vector_convertido[3]);

	return 0;
}