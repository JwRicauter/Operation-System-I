#ifndef VECTOR_DINAMICO_H_INCLUDED
#define VECTOR_DINAMICO_H_INCLUDED

// void* arreglodepunteros[]; No permitido
// void** arreglodepunteros;

typedef struct vector vector_t;

// Firmas de Funciones

// Crea el vector 
vector_t* vector_crear(size_t tam_inicial);

// Me agrega el elemento y ademas me devuelve si hubo un error o no
bool vector_agregar(vector_t* vector, size_t indice, void* elemento);

// Devuelve el elemento del indice
void* vector_obtener(vector_t* vector, size_t indice);


size_t vector_obtener_tam(vector_t* vector);

// Redimensiona el vector y devuelve si hubo algun error o no.
bool vector_redimensionar(vector_t* vector, size_t nuevotam);

// Libera la memoria pedida.
void vector_destruir(vector_t* vector);


#endif 