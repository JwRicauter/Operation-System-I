#include<stdio.h>

int main(){
	
	char nombre[5];
	nombre[0] = 'H';
	nombre[1] = 'O';
	nombre[2] = 'L';
	nombre[3] = 'A';
	nombre[4] = '\0';
	printf("%s\n", nombre);

	char nombre2[] = "Jawil Marliott Ricauter Dodero";
	printf("%s\n", nombre2);

	return 0;
}