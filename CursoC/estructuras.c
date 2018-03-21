#include <stdio.h>
#include <string.h>

struct alumno{
	int nota;
	char nombre[40];
	int edad;
};

int main(){
	int x;
	struct alumno a1;
	a1.nota = 4;
	a1.edad = 19;
	char nombre_aux[] = "Jawil Marliott";
	strcpy(a1.nombre, nombre_aux);
	printf("El alumno %s, edad %d tiene nota %d\n", a1.nombre, a1.edad, a1.nota);



	return 0;
}