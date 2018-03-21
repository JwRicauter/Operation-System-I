#include <stdio.h>

int main(){
	printf("\n Bienvenidos al Escritor\n");
	FILE* miarchivo = NULL;
	char* nombrearchivo = "Data.txt";

	miarchivo = fopen(nombrearchivo, "w");
	if (miarchivo == NULL)return -1;

	fprintf(miarchivo, "Hola soy un archivo \n");
	fclose(miarchivo);

	return 0;
}