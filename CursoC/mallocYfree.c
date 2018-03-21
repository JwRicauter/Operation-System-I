#include <stdio.h>
#include <stdlib.h>

int main(){
	
	void * p1 = malloc(sizeof(char));

	// si esta llena la memoria dinamica, malloc devuelve null


	if(p1 == NULL){
		printf("Error: La memoria esta llena\n");
	}
	else{
		printf("Se asigno correctamente p1\n");
	}

	// Liberto el espacio pedido que seria lo que apunta p1

	free(p1);

	return 0;
}