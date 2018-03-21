#include <stdio.h>
#include <string.h>

struct contacto{
	char nombre [40];
	char direccion [80];
	int edad;
	long telefono;
};

// Cambiando el nombre del tipo strct contacto
typedef struct contacto contacto_t;

int main(){

	contacto_t c1;
	printf("Ingrese el nombre: \n");
	fflush(stdin);
	gets(c1.nombre);

	printf("Ingrese la direccion: \n");
	fflush(stdin);
	gets(c1.direccion);

	printf("Ingrese la edad: \n");
	fflush(stdin);
	scanf("%d", &c1.edad);

	printf("Ingrese el telefono: \n");
	fflush(stdin);
	scanf("%d", &c1.telefono);


	printf("Nombre: %s\n Direccion: %s\n Edad: %d\n Tel: %d\n", c1.nombre, c1.direccion, c1.edad, c1.telefono);

	return 0;
}

