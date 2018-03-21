#include <stdio.h>

struct contacto{
	int edad;
	long tel;
};

typedef struct contacto contacto_t;

int main(){
	
	/* Forma Estatica
	contacto_t contacto1;
	contacto1.edad = 3;
	printf("edad del contacto1: %d\n", contacto1.edad);
	*/

	contacto_t* contacto1 = malloc(sizeof(contacto_t));
	if(contacto1 == NULL)printf("Memoria llena!\n");
	//(*contacto1).edad = 3;
	// ES mas facil hacer:
	contacto1->edad = 3
	printf("Edad del contacto1 dinamico: %d\n", contacto1->edad);

	contacto_t* contacto3 = malloc(sizeof(contacto_t));
	if(contacto3 == NULL)printf("Memoria llena!\n");
	contacto3->tel = 443254;
	printf("El telefono del contacto 3 es: %d\n", contacto3->tel);

	free(contacto1);
	free(contacto3);

	return 0;
}