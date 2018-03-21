#include<stdio.h>
#include<string.h>

int main(){
	char nombre1[] = "Mi nombre es Jawil";
	char nombre2[] = "Mi nombre es Marliott";
	printf("%s\n", nombre1);
	printf("%s\n", nombre2);

	// String copy

	printf("Copio lo que tiene nombre1 arriba de nombre2\n");
	strcpy(nombre2, nombre1);
	printf("%s\n", nombre2);

	// String length

	int largo;
	largo = strlen(nombre1);
	printf("Longitud de nombre1: %d\n", largo);

	// String compare

	int i = strcmp(nombre1, nombre2);
	printf("i: %d\n", i);

	// To upper, to lower y ascii

	char mayus;
	mayus = toupper(nombre1[7]);
	printf("El caracter 7 en mayus: %c\n", mayus);


	return 0;
}