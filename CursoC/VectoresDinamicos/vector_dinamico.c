#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "vector_dinamico.h"

struct vector{
	size_t tam;
	void** datos;

}; 


vector_t* vector_crear(size_t tam_inicial){

	// Pedimos memoria para la estructura
	vector_t* vector = malloc(sizeof(vector));
	if(vector == NULL)return NULL;

	// Guardamos el tamano
	vector->tam = tam_inicial;

	// Pedimos memoria para los datos
	vector->datos = malloc(sizeof(void*)*tam_inicial);
	if(vector->datos == NULL){
		free(vector);
		return NULL;
	}

	//limpiamos el vector

	for(int i = 0; i < tam_inicial; i++){
		vector->datos[i] = NULL;
	}

	return vector;	
}

bool vector_agregar(vector_t* vector, size_t indice, void* elemento){
	// Validamos el indice
	if(indice < 0 || indice >= vector->tam) return false;

	// Guardamos el elemento.
	vector->datos[indice] = elemento;

	return true;
}

void* vector_obtener(vector_t* vector, size_t indice){

	if(indice < 0 || indice >= vector->tam) return NULL;
	return vector->datos[indice];
}


size_t vector_obtener_tam(vector_t* vector){
	return vector->tam;
}

bool vector_redimensionar(vector_t* vector, size_t nuevotam){
	if(nuevotam < vector->tam) return false;
	void** datos_nuevos = realloc(vector->datos, nuevotam*sizeof(void*));
	if (datos_nuevos == NULL)return false;
	free(vector->datos);
	vector->datos = datos_nuevos;
	vector->tam = nuevotam;
	return true;
}

void vector_destruir(vector_t* vector){
	free(vector->datos);
	free(vector);
}

int main(){
	vector_t* v1 = vector_crear(3);
	int dato1 = 7;
	float dato2 = 3.1452;
	char* dato3 = "JawilRicauter";

	vector_agregar(v1, 0, &dato1);
	vector_agregar(v1, 1, &dato2);
	vector_agregar(v1, 2, dato3);

	int* elemento_en_0 = (int*)(vector_obtener(v1, 0));
	printf("V1 en pos: %d = %d\n",0, *elemento_en_0);

	float* elemento_en_1 = (float*)(vector_obtener(v1, 1));
	printf("V1 en pos: %d = %f\n",1, *elemento_en_1);


	char* elemento_en_2 = (char*)(vector_obtener(v1, 2));
	printf("V1 en pos: %d = %s\n",2, elemento_en_2);

	return 0;
}