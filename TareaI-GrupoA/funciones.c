#include "funciones.h"

// Alumnos:
// 		Denylson Romero, 13-11270.
//		Jawil Ricauter, 13,11199.


////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////


// Definimos las estructuras a utilizar.

struct Proceso{
	long pid;
	Estado estado;
	float time;
	char comando[50];
};

struct ElementoLista{
	Proceso * proceso;
	struct ElementoLista * siguiente;
	
};

struct ListaIdentificar{
	Elemento * inicio;
	Elemento * fin;
	int longitud;
};

struct EstructuraDeListas{
	Lista * listas_prioridad[6];
};


////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////


// Creacion de funciones auxiliares.

// Esta funcion, dado los atributos de un proceso, te devuelve un proceso.
Proceso * crear_proceso(long id, Estado state, float tm, char command[50]){
	Proceso * p = (Proceso*)malloc(sizeof(Proceso));
	p->pid = id;
	p->estado = state;
	p->time = tm;
	strcpy(p->comando, command);

	return p;
}


// Inicializacion de una lista enlazada.
Lista * inicializacion(){
	Lista * lista = (Lista *)malloc(sizeof(Lista));
	lista->inicio = NULL;
	lista->fin = NULL;
	lista->longitud = 0;

	return lista;
}

// Insercion a la lista enlazada, en nuestro caso, como la lista debe funcionar como
// una cola, entonces los elementos solo se insertaran al final de la lista.
int insercion(Lista * lista, Proceso * p){
	Elemento * nuevo_elemento;
	if ((nuevo_elemento = (Elemento *)malloc(sizeof(Elemento))) == NULL) return -1;
	if ((nuevo_elemento->proceso = (Proceso*)malloc(50 * sizeof(Proceso))) == NULL) return -1;	
				// Estos condicionales son en dado caso que no se pueda almacenar memoria.

	nuevo_elemento->proceso = p;
	nuevo_elemento->siguiente = NULL;

	if(lista->longitud == 0){
		lista->inicio = nuevo_elemento;
	}
	else{
		(lista->fin)->siguiente = nuevo_elemento;
	}

	lista->fin = nuevo_elemento;
	lista->longitud++;
	return 0;
}

// Esta funcion elimina el primer nodo de la lista enlaza, para que la lista funcione como cola.
int eliminar_primero(Lista * lista){
	if (lista->longitud == 0) return -1;
	Elemento * temporal;

	temporal = lista->inicio;
	lista->inicio = lista->inicio->siguiente;

	if(lista->longitud == 1){
		lista->fin = NULL;
	}

	free(temporal->proceso);
	free(temporal);
	lista->longitud--;
	return 0;
}

// Funcion que permite extraer el primer nodo de la lista enlazada.
Proceso * extraccion_primero(Lista * lista){
	if (lista->longitud == 0) return NULL;
	Elemento * temporal;

	temporal = lista->inicio;
	lista->inicio = lista->inicio->siguiente;

	if(lista->longitud == 1){
		lista->fin = NULL;
	}

	lista->longitud--;
	return temporal->proceso;
}



// Funcion que elimina cualquier nodo de la lista dado un identificador.
// Se tienen dos casos, El primero es que si el elemento se encuentra en la primera
// posicion, entonces se "desencola", y el segundo es que si no se encuentra de primero
// entonces se busca por toda la lista y se elimina.
int eliminacion(Lista * lista, long identificador){


	if (lista->longitud < 1) return -1;	// Si la lista es vacia.

	Elemento * el_actual;
	Elemento * el_siguiente;

	el_actual = lista->inicio;				// Apuntador a un nodo actual.
	el_siguiente = el_actual->siguiente;	// Apuntador a un nodo siguiente.

	int auxiliar_long = lista->longitud;
	if (auxiliar_long == 1){
		// Si la lista solo tiene un elemento, tambien se "desencola" 
		if(lista->inicio->proceso->pid == identificador){
			eliminar_primero(lista);
		}
	}
	else{
		// Si no tiene solo un elemento entonces se procede a buscarlo
		while ((auxiliar_long > 0) && (el_siguiente != NULL)){

			Proceso * proceso_sig = el_siguiente->proceso;

			if(proceso_sig->pid == identificador){
				el_actual->siguiente = el_actual->siguiente->siguiente;
				lista->longitud--;
			}

			if(lista->inicio->proceso->pid == identificador){
				eliminar_primero(lista);
			}

			el_actual = el_actual->siguiente;
			el_siguiente = el_siguiente->siguiente;
			auxiliar_long--;
		}
	}
	


	return 0;
}

// Funcion que extrae el primer elemento listo de la lista.
// Funciona exactamente como eliminar, solo que esta devuelve un proceso.
Proceso * extraccion_listo(Lista * lista){

	if (lista->longitud < 1) return NULL;	// Si la lista es vacia.

	Elemento * el_actual;
	Elemento * el_siguiente;

	el_actual = lista->inicio;				// Apuntador a un nodo actual.
	el_siguiente = el_actual->siguiente;	// Apuntador a un nodo siguiente

	Proceso * x;


	int auxiliar_long = lista->longitud;
	if (auxiliar_long == 1){
		// Si la lista solo tiene un elemento, tambien se "desencola" 
		if(lista->inicio->proceso->estado == 'L'){
			x = extraccion_primero(lista);
		}
	}
	else{
		// Si no tiene solo un elemento entonces se procede a buscarlo
		while ((auxiliar_long > 0) && (el_siguiente != NULL)){

			Proceso * proceso_sig = el_siguiente->proceso;

			// Si el siguiente estado esta listo pero el anterior no, entonces se procede a eliminarlo
			// Esto se maneja asi para evitar cuando el primero esta listo y el siguiente tambien.
			if(proceso_sig->estado == 'L' && el_actual->proceso->estado != 'L'){
				x = proceso_sig;
				el_actual->siguiente = el_actual->siguiente->siguiente;
				lista->longitud--;
				break;
			}

			if(lista->inicio->proceso->estado == 'L'){
				x = extraccion_primero(lista);
				break;
			}

			el_actual = el_actual->siguiente;
			el_siguiente = el_siguiente->siguiente;
			auxiliar_long--;
		}
	}
	

	return x;
}


// Funcion que imprime los atributos de todos los procesos almacenados en una lista.
void visualizacion(Lista * lista){
	Elemento * el_actual;
	el_actual = lista->inicio;

	while (el_actual != NULL){
		Proceso * temporal = el_actual->proceso;
		printf("Identificador: %ld, Estado: %c, Tiempo: %.1f, Comando: %s\n", temporal->pid, temporal->estado, temporal->time, temporal->comando);
		el_actual = el_actual->siguiente;
	}
}

// Esta funcion permite buscar un proceso p en una lista determinada y cambiarle el estado.
void cambiar_estado_proceso(Lista * lista, Proceso * p, Estado nuevoEstado){
	Elemento * el_actual;
	el_actual = lista->inicio;
	while (el_actual != NULL){
		if (el_actual->proceso->pid == p->pid){
			el_actual->proceso->estado = nuevoEstado;
		}
		el_actual = el_actual->siguiente;
	}
}

// Funcion que extrae el primer elemento de una lista, se le cambia su estado a en ejecucion
// y luego se inserta al final de la lista.
Proceso * proceso_planificado(Lista * lista){
	Proceso * auxiliar = extraccion_listo(lista);
	auxiliar->estado = 'E';
	insercion(lista, auxiliar);
	return auxiliar;
}

// funcion que encuentra un proceso en ejecucion y devuelve su identificador.
long encontrar_proceso_en_ejecucion(Lista * lista){
	long id = -1;

	Elemento * el_actual;
	el_actual = lista->inicio;

	while (el_actual != NULL){
		if (el_actual->proceso->estado == 'E'){
			id = el_actual->proceso->pid;
		}
		el_actual = el_actual->siguiente;
	}

	return id;
}

// Funcion que escribe todos los procesos de todas las listas en un archivo dado por el usuario.
int escribir_procesos(EstrucSched * s, char * filename){

	FILE* miarchivo;
	miarchivo = fopen(filename, "w");
	if (miarchivo == NULL)return -1;

	int i;
	for(i = 0; i < 6; i++){
		if(s->listas_prioridad[i]->longitud > 0){
			Proceso * x = extraccion_primero(s->listas_prioridad[i]);
			fprintf(miarchivo, "%ld %c %d %.1f %s\n", x->pid, x->estado, i, x->time, x->comando);
		}
	}
	
	fclose(miarchivo);
	return 0;
}


////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////


// Ahora vendran las funciones obligatorias.


void InsertarProceso(EstrucSched * s, Proceso* p, short prioridad){
	insercion(s->listas_prioridad[prioridad], p);
}


void ElimProceso(EstrucSched *s, long pid, short prio){
	eliminacion(s->listas_prioridad[prio], pid);
}


void ElimProcesoE(EstrucSched *s){
	int i;

	for(i = 0; i < 6; i++){
		if(s->listas_prioridad[i]->longitud > 0){
			// Si la cola no es vacia entonces...
			long id_proceso = encontrar_proceso_en_ejecucion(s->listas_prioridad[i]);
			if (id_proceso != -1){
				// Si se encontro el proceso en ejecucion entonces se elimina.
				eliminacion(s->listas_prioridad[i], id_proceso);
			}
			else{
				// Si no, sale un mensaje de error.
				printf("Lo sentimos, no existe ningun proceso en ejecucion.\n");
			}
		}
	}

}

Proceso * ProxProceso(EstrucSched *s){
	int i;
	Proceso * auxiliar;

	for(i = 0; i < 6; i++){
		// Se busca en todas las listas del planificador.
		if(s->listas_prioridad[i]->longitud > 0){
			// Si la lista no es vacia entonces se extrae el proceso y se coloca al final.
			auxiliar = proceso_planificado(s->listas_prioridad[i]);
			break;
		}
		else{
			// Si la cola es vacia se ignora.
			continue;
		}
	}

	return auxiliar;

}

void CambiarEstado(EstrucSched *s, Proceso* p, Estado newestado){

	int i;
	for(i = 0; i < 6; i++){
		if(p->estado == 'E'){
			// Se busca si el estado esta en ejecucion entonces se pasa a listo.
			cambiar_estado_proceso(s->listas_prioridad[i], p, newestado);
		}
	}
	
}

EstrucSched *Construye(char *filename){
	FILE* miarchivo;
	char* nombrearchivo = filename;
	char lectura[80];

	miarchivo = fopen(nombrearchivo, "r");
	if(miarchivo == NULL) return NULL;

	EstrucSched * s = (EstrucSched*)malloc(sizeof(EstrucSched));

	int i;
	for (i = 0; i < 6; i++){
		s->listas_prioridad[i] = inicializacion();
	}

	while (fgets(lectura, sizeof(lectura), miarchivo) != NULL){

		long id;
		Estado est;
		int prioridad;
		float tiempo;
		char cmd[50];

   		sscanf(lectura, "%ld %c %d %f %s", &id, &est, &prioridad, &tiempo, cmd);
   		

   		Proceso * process = crear_proceso(id, est, tiempo, cmd);
   		
   		// Se insertan los procesos leidos en la estructura de listas.
		InsertarProceso(s, process, prioridad);

	}

	return s;
}

void Imprime(EstrucSched *s){
	int i;
	for(i = 0; i < 6; i++){
		printf("\nPara la cola numero %d estan los siguientes procesos:\n", i);
		visualizacion(s->listas_prioridad[i]);
		printf("\n");
	}
}


////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////