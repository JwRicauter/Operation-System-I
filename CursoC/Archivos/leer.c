#include <stdio.h>

int main(){
	printf("\n Bienvenidos al lector \n");

	FILE* miarchivo;
	char* nombrearchivo = "texto.txt";
	char lectura[80];

	miarchivo = fopen(nombrearchivo, "r");
	if(miarchivo == NULL)return -1;

	fscanf(miarchivo," %[^\n]", &lectura);
	printf("Lectura: %s\n", lectura);
	fscanf(miarchivo," %[^\n]", &lectura);
	printf("Lectura: %s\n", lectura);
	fscanf(miarchivo," %[^\n]", &lectura);
	printf("Lectura: %s\n", lectura);

	return 0;
}