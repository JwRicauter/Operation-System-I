#include <stdio.h>
#include <string.h>


typedef struct fecha{
	int dia;
	int mes;
	int anio;	
} fecha_t;

typedef struct contacto{
	char nombre[80];
	long tel;
	// fecha_nacimiento tambien es un struct;
	fecha_t fecha_nacimiento;
	
} contacto_t;

fecha_t crear_fecha(){
	fecha_t nueva_fecha;

	printf("\nIngrese el dia: ");
	scanf("%d", &nueva_fecha.dia);
	while(getchar() != '\n');

	printf("\nIngrese el mes: ");
	scanf("%d", &nueva_fecha.mes);
	while(getchar() != '\n');

	printf("\nIngrese el anio: ");
	scanf("%d", &nueva_fecha.anio);
	while(getchar() != '\n');

	return nueva_fecha;

}

contacto_t crear_contacto(){
	contacto_t nuevo_contacto;

	printf("Ingrese el nombre: ");
	gets(nuevo_contacto.nombre);
	while(getchar() != '\n');

	printf("\nIngrese el telefono");
	scanf("%d", &nuevo_contacto.tel);
	while(getchar() != '\n');

	nuevo_contacto.fecha_nacimiento = crear_fecha();

	return nuevo_contacto;
}

int main(){

	contacto_t c1 = crear_contacto();


	return 0;
}