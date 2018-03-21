#include <stdio.h>
#include <stdlib.h>

typedef struct fecha{
	int dia;
	int mes;
	int anio;

}fecha_t;

fecha_t* crear_fecha(){
	fecha_t* nueva_fecha = malloc(sizeof(fecha_t));
	if(!nueva_fecha)printf("Error\n");

	printf("Ingrese el dia: ");
	scanf("%d", &nueva_fecha->dia);
	while(getchar() != '\n');

	printf("Ingrese el mes: ");
	scanf("%d", &nueva_fecha->mes);
	while(getchar() != '\n');

	printf("Ingrese el anio: ");
	scanf("%d", &nueva_fecha->anio);
	while(getchar() != '\n');

	return nueva_fecha;

}

void imprimir_fecha(fecha_t* fecha_a_imprimir){

	printf("\nDia: %d, Mes: %d, Anio: %d\n", fecha_a_imprimir->dia, fecha_a_imprimir->mes, fecha_a_imprimir->anio);

}


int main(){
	fecha_t* fecha1 = crear_fecha();
	imprimir_fecha(fecha1);


	return 0;
}