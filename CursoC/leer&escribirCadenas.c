#include<stdio.h>


int main(){
	char cadena[40];
	char cadena2[40];

	// Primera forma
	printf("Ingrese una cadena: ");
	fflush(stdin);
	scanf("%[^\n]s", &cadena);
	printf("\nLa cadena es: %s\n", cadena);

	// Segunda forma

	printf("Ingrese una cadena: ");
	fflush(stdin);
	gets(cadena2);
	printf("\nLa cadena 2 es: %s\n", cadena2);

	return 0;
}