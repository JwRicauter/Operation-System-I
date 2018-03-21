#include "funciones.h"



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  																												//
//   Creación de un pthread ls como Proyecto número 2 para Sistemas Operativos I.									//
//   Universidad Simón Bolívar.																						//
//   Valle de Sartenejas, Miranda.																					//
//																													//
//   Elaborado por:																									//
//			  		    Denylson Romero, 13-11270																	//
//						Jawil Ricauter,  13-11199																	//
//																													//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



pthread_mutex_t mutex1;



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// Definimos las Estructuras de Datos ///////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



struct Nodop{
    char * direccion;			// Contendrá la dirección pendiente por revisar.
    NodoPila * siguiente;
};

struct Pila{
	NodoPila * cabeza;
	int longitud;
};

struct Nodoc{
	char * direccion;			// Contendrá la dirección de donde se guardará la información.
	int numeroBytes;			// Tendrá la cantidad de bytes en el directorio.
	int numeroArchivos;			// Contendrá el número de archivos de la ruta.
	pthread_t idHilo;			// Guardará el identificador del hilo que revisará la ruta.
	Pila * dirEncontrados;		// Pila de directorios encontrados en el directorio.
	NodoCola * siguiente;
};

struct Cola{
	NodoCola * inicio;
	NodoCola * fin;
	int longitud;
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////// Operaciones de la Pila ////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



/* Función que inicializa una pila. 	  */
/*		Parámetros: void.				  */
/*		Devuelve: Una Pila inicializada.  */
Pila * inicializacionPila(){

	Pila * pila = (Pila*)malloc(sizeof(Pila));
	pila->cabeza = NULL;
	pila->longitud = 0;

	return pila;
}



/* Funcion que añade un elemento a la pila. 					  */
/*		Parámetros: pila, una Pila. 							  */
/*					dirección, un string que va a ser empilado.   */
/*		Devuelve:   entero que indica si se termino con exito.    */
int empilar(Pila * pila, char * direccion){

    NodoPila* temporal;
    if ((temporal = (NodoPila *)malloc(sizeof(NodoPila))) == NULL) return -1;
	if ((temporal->direccion = (char*)malloc(500 * sizeof(char))) == NULL) return -1;	


    temporal->direccion = direccion;
    temporal->siguiente = pila->cabeza;
    pila->cabeza = temporal;
    pila->longitud++;

    return 0;
}



/* Funcion que elimina un elemento de la pila.				  */
/*		Parámetros: pila, una Pila. 						  */
/*		Devuelve:   el string que fue desempilado.			  */
char * desempilar(Pila * pila){

	if(pila->longitud == 0) return NULL;
    NodoPila* temporal = pila->cabeza;

    pila->cabeza = pila->cabeza->siguiente;
    pila->longitud--;

    return temporal->direccion;
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////// Operaciones de la Cola ////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



/* Funcion que inicializa una cola.							 */
/*		Parámetros: void. 					  				 */
/*		Devuelve:   Un apuntador a la cola inicializada.	 */
Cola * inicializacionCola(){

	Cola * cola = (Cola*)malloc(sizeof(Cola));
	cola->inicio = NULL;
	cola->fin = NULL;
	cola->longitud = 0;

	return cola;

}



/* Funcion que inserta un nodo nuevo en una cola.			  		  */
/*		Parámetros: cola, una cola.							  		  */
/*					nuevoNodo, un nodo a ser insertado.        		  */
/*		Devuelve:   un entero que indica si la insercion fue exitosa. */
int insercion(Cola * cola, NodoCola * nuevoNodo){
	
	nuevoNodo->siguiente = NULL;

	if(cola->longitud == 0){
		cola->inicio = nuevoNodo;
	}
	else{
		(cola->fin)->siguiente = nuevoNodo;
	}

	cola->fin = nuevoNodo;
	cola->longitud++;
	return 0;

}



/* Funcion que elimina un nodo de la cola. 				 	  */
/*		Parámetros: cola, una cola.						  	  */
/*		Devuelve:   el nodo eliminado de la cola.			  */
NodoCola * eliminar(Cola * cola){
	if(cola->longitud == 0) return NULL;
	NodoCola * temporal;

	temporal = cola->inicio;
	cola->inicio = cola->inicio->siguiente;

	if (cola->longitud == 1){
		cola->fin = NULL;
	}

	cola->longitud--;
	return temporal;
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////// Funciones para realizar el thread ls ///////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



/* Funcion que devuelve la ruta desde donde se ejecuta el programa. 				*/
/*		Parámetros: void.						  	  								*/
/*		Devuelve:   un string que indica la ruta donde se encuentra este archivo 	*/
Argumentos * inicializarArgumentos(){

	Argumentos * arg = (Argumentos*)malloc(sizeof(Argumentos));
	if (arg == NULL) return NULL;

	arg->directoriosListos = inicializacionCola();
	arg->directoriosPendientes = inicializacionPila();

	return arg;
}



/* Funcion que devuelve la ruta desde donde se ejecuta el programa. 				*/
/*		Parámetros: void.						  	  								*/
/*		Devuelve:   un string que indica la ruta donde se encuentra este archivo 	*/
char * ruta_actual(){

	long tamanio;
	char *buf;
	char *path;
	tamanio = pathconf(".", _PC_PATH_MAX);


	// size_t guarda tamanio maximo de un objeto de cualquier tipo.
	if ((buf = (char *)malloc((size_t)tamanio)) != NULL){
		// Condicional que verifa si hay memoria suficiente
		// para guardar el path. 
    	path = getcwd(buf, (size_t)tamanio);
    	// La funcion getcwd guarda el path absoluto del directorio actual 
    	// de trabajo en el arreglo apuntado por buf.
	}

    return path;

}



/* Funcion que genera un mensaje de ayuda que contiene la sintaxis, descripción de parámetros, etc con  */ 
/* el objetivo de hacer entender al usuario el funcionamiento del programa 					     		*/
/*		Parámetros: void.						  	  													*/
/*		Devuelve:   void 																				*/
void generar_mensaje_ayuda(){

	printf("A continuación se mostrará un mensaje que contendrá, entre otras cosas, la sintaxis de la entrada\n");
	printf("la descripción de parámetros, entre otras cosas.\n\n");   
	printf("\t\tSintaxis\n\n");
	printf("tls[-h] | [-n i] [-d directorio] [ salida ]\n\n");
	printf("-h c            \t\t Muestra por pantalla un mensaje de ayuda (sintaxis, descripción de parámetros, etc.)\n");
	printf("              \t\t y termina.\n");
	printf("-n i          \t\t Nivel de concurrencia solicitado. Por defecto crea un solo hilo trabajador\n");
	printf("-d directorio \t\t Especifica un directorio desde donde revisa el espacio utilizado.\n");
	printf("              \t\t Por defecto hace el cálculo desde el directorio actual\n");
	printf("salida        \t\t Archivo que contendrá la lista de directorios y el espacio en bytes ocupado por\n");
	printf("              \t\t los archivos regulares. Valor por defecto es la salida estándar\n");
	printf("\nDonde: \n\n");
	printf("[ ]           \t\t Indica que lo que esté entre esos símbolos es opcional. Se debe especificar\n");
	printf("              \t\t un valor por defecto.\n");
	printf("A|B           \t\t Indica que se espera que el comando se puede ejecutar ya sea con A o con B, pero no\n");
	printf("              \t\t los dos al mismo tiempo. A y B puede ser una opción o secuencia de opciones como en tls.\n");
	printf("-n i          \t\t Indica que cuando se vea en la lista de parámetros -n el siguiente debe ser interpretado\n");
	printf("              \t\t como i. Esto se usa para no fijar el orden en que se pasan los parámetros al programa.\n");

	exit(0);
}



/* Funcion que realizará el hilo Padre y consiste en que, dado un directorio, va a recopilar todos los  */
/* datos en cuanto a número de archivos regulares, número de bytes y directorios encontrados. 			*/ 					     		
/*		Parámetros: char * ruta, la dirección de un directorio.	  	  									*/
/*		Devuelve:   Una apuntador a una cola que contendrá la información requerida. 					*/
Cola * explorarDirectorio(char * ruta){

	Cola * cola = inicializacionCola();

	NodoCola * nuevoNodo;
	if ((nuevoNodo = (NodoCola *)malloc(sizeof(NodoCola))) == NULL) return NULL;

	nuevoNodo->dirEncontrados = inicializacionPila();
	DIR *dirp;
	struct dirent *direntp;
	struct stat statbuf;
	int permisoLeer;
	int permisoEjecutar;
	char * nuevaRuta;

    nuevoNodo->direccion = ruta;			/* Asignamos la ruta al nodo */
	nuevoNodo->idHilo = pthread_self(); 	/* Asignamos el identificador del hilo que esta ejecutando la función */


	dirp = opendir(ruta);				/* Abrimos el directorio */
	if (dirp == NULL){
		printf("Error: No se puede abrir el directorio\n");
		exit(2);
	}



	while ((direntp = readdir(dirp)) != NULL){
		if (stat(ruta, &statbuf) == -1)
			continue;

		if((direntp->d_type == DT_DIR)){

			// Nuevo path contendra la ruta hacia el subdirectorio encontrado
			nuevaRuta = malloc((1 + strlen("/") + strlen(direntp->d_name) + strlen(ruta))*sizeof(char));
			if(nuevaRuta == NULL) return NULL;
			
			nuevaRuta = strcpy(nuevaRuta, ruta);
			nuevaRuta = strcat(nuevaRuta, "/");
			nuevaRuta = strcat(nuevaRuta, direntp->d_name);

			/* Determina si el directorio encontrado tiene permiso para leer y ejecutar */
			permisoLeer = access(nuevaRuta, R_OK);
			permisoEjecutar = access(nuevaRuta, X_OK);

			/* Además, se restringe a que no aparezcan los arhivos ocultos*/
			if((permisoLeer == 0) && (permisoEjecutar == 0) && (direntp->d_name[0] != '.')){
				empilar(nuevoNodo->dirEncontrados, nuevaRuta);
			}

		}
		if((direntp->d_type == DT_REG) && (direntp->d_name[0] != '.')){	
			nuevaRuta = malloc((1 + strlen("/") + strlen(direntp->d_name) + strlen(ruta))*sizeof(char));
			if(nuevaRuta == NULL) return NULL;
			nuevaRuta = strcpy(nuevaRuta, ruta);
			nuevaRuta = strcat(nuevaRuta, "/");
			nuevaRuta = strcat(nuevaRuta, direntp->d_name);
			stat(nuevaRuta, &statbuf);
			nuevoNodo->numeroBytes = nuevoNodo->numeroBytes + statbuf.st_size; // Se suman los números de bytes.	
			nuevoNodo->numeroArchivos++;					// Se suman los números de archivos regulares.
		}

	}

	insercion(cola, nuevoNodo);			// Insertamos el nodo en la cola.

	return cola;

}



/* Función que creará y manejará a los hijos trabajadores para evitar que haya una mala condición de carrera */
/*		Parámetros: Argumentos * arg, una estructura que contendrá los argumentos para pasárselos a la 		 */
/*					función de hilos. 																		 */
/*					NodoCola * nodo, un nodo de una cola. 													 */
/*					int nroHilos, un entero que representa la cantidad de hilos a crear  					 */
/*		Devuelve:   Una apuntador a una cola que contendrá la información requerida. 						 */
Cola * asignacionHilos(Argumentos * arg, NodoCola * nodo, int nroHilos){

	int i = 0; // Contador de hilos creados
	int j; 
	pthread_t * id_deHilos;		// Arreglo que contendrá los hilos.
	id_deHilos = (pthread_t *)malloc(sizeof(long unsigned) * nroHilos);
	if(id_deHilos == NULL) return NULL;

	arg = inicializarArgumentos(i + 2);
	arg->directoriosPendientes = nodo->dirEncontrados;
	insercion(arg->directoriosListos, nodo);


	//Inicializacion del mutex, que asegurará la exclusión mutua.
	pthread_mutex_init(&mutex1, NULL);


	while(1){

		if (arg->directoriosPendientes->longitud == 0){
		// Mientras no existan directorios pendientes, el esperará a que los hilos terminen.

			for (j = 0; j < i; j++)// 1 = nrodeHILOS
				pthread_join(id_deHilos[j], NULL);
			i = 0; // Cerraron todos los hilos, reiniciamos el contador

			// Si luego de esperar los hilos, la pila sigue vacia, se hace break
			if (arg->directoriosPendientes->longitud == 0)
				break;
		}


		pthread_create(&id_deHilos[i], 0, (void *)funcionHilos, (void *)arg);
		i++;

		// Si la cantidad de hilos creados esta al maximo Esperamos a que terminen
		if (i == nroHilos){	
			for (j = 0; j < nroHilos; j++) 
				pthread_join(id_deHilos[j], NULL);
			i = 0; // Cierran todos los hilos
		}
	}

	//Destruccion del mutex
	pthread_mutex_destroy(&mutex1);
	return arg->directoriosListos;

}



/* Función que será la que realizarán los hilos. 				 										 */
/*		Parámetros: void * arg, una estructura que contendrá los argumentos para pasárselos a la 		 */
/*		Devuelve:   void. 																				 */
int funcionHilos(void* arg){

	pthread_mutex_lock(&mutex1);
	Argumentos * argu = (Argumentos *)arg;
	Pila * pila = argu->directoriosPendientes;
	Cola * cola = argu->directoriosListos;
	char *ruta = desempilar(pila);
	pthread_mutex_unlock(&mutex1);

	// Si el hilo se creo con una ruta NULL, se sale
	if(ruta == NULL)
		pthread_exit(NULL);

	DIR *dirp;
	struct dirent *direntp;
	struct stat statbuf;
	int permisoLeer;
	int permisoEjecutar;
	char * nuevaRuta;
	NodoCola * nuevoNodo;
	if ((nuevoNodo = (NodoCola *)malloc(sizeof(NodoCola))) == NULL) exit(-1);

	nuevoNodo->direccion = ruta;
	nuevoNodo->idHilo = pthread_self();

    // Abrimos el directorio 
	dirp = opendir(ruta);
	if (dirp == NULL){
		printf("Error: No se puede abrir el directorio\n");
		exit(2);
	}


	while ((direntp = readdir(dirp)) != NULL){

		if (stat(ruta, &statbuf) == -1)
			continue;

		if(direntp->d_type == DT_DIR){

			// Nuevo path contendra la ruta hacia el subdirectorio encontrado
			nuevaRuta = malloc((1 + strlen("/") + strlen(direntp->d_name) + strlen(ruta))*sizeof(char));
			if(nuevaRuta == NULL) return -1;
			nuevaRuta = strcpy(nuevaRuta, ruta);
			nuevaRuta = strcat(nuevaRuta, "/");
			nuevaRuta = strcat(nuevaRuta, direntp->d_name);
			permisoLeer = access(nuevaRuta, R_OK);
			permisoEjecutar = access(nuevaRuta, X_OK);


			if((permisoLeer == 0) && (permisoEjecutar == 0) && (direntp->d_name[0] != '.')){

				// REGION CRITICA
				pthread_mutex_lock(&mutex1);
				empilar(pila, nuevaRuta);
				pthread_mutex_unlock(&mutex1);
			}

		}

		if((direntp->d_type == DT_REG) && (direntp->d_name[0] != '.')){	
			nuevaRuta = malloc((1 + strlen("/") + strlen(direntp->d_name) + strlen(ruta))*sizeof(char));
			if(nuevaRuta == NULL) return -1;
			nuevaRuta = strcpy(nuevaRuta, ruta);
			nuevaRuta = strcat(nuevaRuta, "/");
			nuevaRuta = strcat(nuevaRuta, direntp->d_name);
			stat(nuevaRuta, &statbuf);
			nuevoNodo->numeroBytes = nuevoNodo->numeroBytes + statbuf.st_size;
			nuevoNodo->numeroArchivos++;
		}

	}
	

	// REGION CRITICA
	pthread_mutex_lock(&mutex1);
	insercion(cola, nuevoNodo);
	pthread_mutex_unlock(&mutex1);
	return 0;

}

/* Función que imprimirá los datos de la cola de salida */
/*			Parámetros: Cola * cola, la cola que contendrá la información a imprimir. */
/*						char * salida, que contendrá el nombre del archivo donde 	  */
/*							           se vaciará los datos de la cola. 			  */
/*						int flag, variable que indicará si se cambió o no la salida   */
/*								  de la usual a la indicada por el usuario. 		  */ 
int imprimirCola(Cola * cola, char * salida, int flag){
	if (flag == 1){

		char * ruta;
		ruta = (char*)malloc((5 + strlen(salida)) * sizeof(char));
		if(ruta == NULL) return -1;
		ruta = strcpy(ruta, "/tmp/");
		ruta = strcat(ruta, salida);



		int chequeo;
		chequeo = access ("/tmp/", W_OK);
		if (chequeo == EACCES || chequeo == EROFS){
			printf("El directorio no permite escritura\n");
			exit(2);
		}

		FILE *f = fopen(ruta, "w");
		if (f == NULL){
			printf("Error opening file!\n");
			exit(1);
		}
		
		while(cola->longitud > 0){
			NodoCola * nodo = eliminar(cola);
			fprintf(f, "%lu  %s  %i  %i\n", nodo->idHilo, nodo->direccion, nodo->numeroArchivos, nodo->numeroBytes);
		}	

		fclose(f);
		
	}
	else{
		while(cola->longitud > 0){
			NodoCola * nodo = eliminar(cola);
			printf("%lu %s %i %i\n", nodo->idHilo, nodo->direccion, nodo->numeroArchivos, nodo->numeroBytes);
		}	
	}

	return 0;
}