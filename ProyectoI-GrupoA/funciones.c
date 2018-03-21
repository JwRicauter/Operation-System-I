#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <signal.h>


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////  Proyecto I  ///////////////////////////////////////////////////////////////
////////////////////////////////   Comunicación entre Procesos y Manejo de Archivos   //////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//		Integrantes:
//			Denylson Romero, 13-11270.
//			Jawil Ricauter, 13-11199.



/* La estructura Elementos contendrá, la cantidad de carpetas y el tamaño de las carpetas */
struct Elementos {
    int cantidad;
    int tamanio;
};


/* Esta funcion cuenta cuantas carpetas hay en un directorio, además del tamaño */
struct Elementos Contador(char *path){

	int cont = 0;			// Contador de las carpetas.
	char * nuevo_dir;
	int tamanio = 0; 		// Contador de archivos
	
	struct stat st;
	struct stat statbuf_aux;
	DIR *dirp_aux;
	dirp_aux = opendir(path);
	struct dirent *direntp_aux;
	

	while ((direntp_aux = readdir(dirp_aux)) != NULL) {
		
        if (stat(path, &statbuf_aux) == -1)
        	continue;

		if((direntp_aux->d_type == DT_DIR) && (strcmp(direntp_aux->d_name,".")!=0 ) && (strcmp(direntp_aux->d_name,"..")!=0))
			cont++;

		if((direntp_aux->d_type == DT_REG) && (strcmp(direntp_aux->d_name,".")!=0 ) && (strcmp(direntp_aux->d_name,"..")!=0)){	
			cont++;			
			nuevo_dir = malloc((1 + strlen("/") + strlen(direntp_aux->d_name) + strlen(path))*sizeof(char));
			
			strcpy(nuevo_dir, path);
			strcat(nuevo_dir, "/");
			strcat(nuevo_dir, direntp_aux->d_name);

			stat(nuevo_dir, &st);
	
			tamanio = tamanio + st.st_size;

			free(nuevo_dir);
		}
	}


	closedir(dirp_aux);
	struct Elementos total = {cont, tamanio};
	return total;
}

/* Manejador de Señales */
void sigintHandler(){
	// Evita que el programa sea interrumpido usado CTRL-C
    signal(SIGINT, sigintHandler);
    printf("\n El programa no puede terminar usando Ctrl+C \n");
    fflush(stdout);
}


/* Funcion que devuelve la linea de reporte cuando se encuentra con un archivo core */
char * reporte_core(struct stat statbuf, char * direccion){

	char * linea = malloc(150 * sizeof(linea)*sizeof(char));

	// La direccion de donde fue encontrado el archivo core
	linea = strcpy(linea, "Se encontro un archivo core (que sera borrado) en: ");
	linea = strcat(linea, direccion);
	linea = strcat(linea, "  ");

	// Se añade la fecha de modificacion.
	char date1[10];
	strftime(date1, 20, "%y-%m-%d", localtime(&(statbuf.st_ctime)));

	linea = strcat(linea, " con fecha de modificacion: ");
	linea = strcat(linea, date1);
	struct stat st;
  	stat(direccion, &st);

  	// Se añade tambien el tamaño del archivo core

  	linea = strcat(linea, " y tamanio: ");

	char temp1[15]  = "";
   	sprintf(temp1, "%ld", st.st_size);
	linea = strcat(linea, "");
  	linea = strcat(linea, temp1);
	linea = strcat(linea, "\n");

	return linea;

}


/* Funcion que crea una cadena de caracteres para el reporte del proceso */
char * reporte_proceso(struct stat statbuf, char * direccion){
	struct passwd *pwd;
	struct group *grp;

	// Se crea el string a devolver y se le coloca la ruta de donde se encuentra el proceso.
	char * linea = malloc(100 * sizeof(linea));
	linea = strcpy(linea, direccion);
	linea = strcat(linea, "  ");


	// Se le concatenan los permisos.
	linea = strcat(linea, ((statbuf.st_mode & S_IRUSR) ? "r" : "-"));
	linea = strcat(linea, ((statbuf.st_mode & S_IWUSR) ? "w" : "-"));
	linea = strcat(linea, ((statbuf.st_mode & S_IXUSR) ? "x" : "-"));
	linea = strcat(linea, ((statbuf.st_mode & S_IRGRP) ? "r" : "-"));
	linea = strcat(linea, ((statbuf.st_mode & S_IWGRP) ? "w" : "-"));
	linea = strcat(linea, ((statbuf.st_mode & S_IXGRP) ? "x" : "-"));
	linea = strcat(linea, ((statbuf.st_mode & S_IROTH) ? "r" : "-"));
	linea = strcat(linea, ((statbuf.st_mode & S_IWOTH) ? "w" : "-"));
	linea = strcat(linea, ((statbuf.st_mode & S_IXOTH) ? "x" : "-"));

	// Se colocan los nombres de usuario y de grupo.
	if ((pwd = getpwuid(statbuf.st_uid)) != NULL)
		linea = strcat(linea, "  ");
		linea = strcat(linea, pwd->pw_name);
		linea = strcat(linea, "  "); 


	if ((grp = getgrgid(statbuf.st_gid)) != NULL)
		linea = strcat(linea, grp->gr_name);

	// Concatenamos la fecha de ultima modificacion y de ultimo acceso.
	char date1[10];
	char date2[10];
	strftime(date1, 20, "%y-%m-%d", localtime(&(statbuf.st_ctime)));
	strftime(date2, 20, "%y-%m-%d", localtime(&(statbuf.st_atime)));

	linea = strcat(linea, "  ");
	linea = strcat(linea, date1);
	linea = strcat(linea, "  ");
	linea = strcat(linea, date2);

	// Por ultimo, se concatena el numero de archivos y la cantidad de archivos en bytes que tiene el directorio.
	struct Elementos totalPath = Contador(direccion);

	char temp1[15]  = "";
	char temp2[15]  = "";
    sprintf(temp1, "%d", totalPath.cantidad);
    sprintf(temp2, "%d", totalPath.tamanio);

	linea = strcat(linea, "  ");
    linea = strcat(linea, temp1);
    linea = strcat(linea, "  ");
    linea = strcat(linea, temp2);
    linea = strcat(linea, "  ");
	linea = strcat(linea, "\n");

	return linea;

}


/* Esta funcion existe especificamente para que, entren los datos que se obtendrán con los pipes y se haga el reporte 
   global sobre los subdirectorios de la primera capa  */
char * reporte_global_subdirectorios(struct stat statbuf, char * direccion, int archivos, int size){


	struct passwd *pwd;
	struct group *grp;

	// Se crea el string a devolver y se le coloca la ruta de donde se encuentra el proceso.
	char * linea = malloc(100 * sizeof(linea));
	linea = strcpy(linea, direccion);
	linea = strcat(linea, "  ");


	// Se le concatenan los permisos.
	linea = strcat(linea, ((statbuf.st_mode & S_IRUSR) ? "r" : "-"));
	linea = strcat(linea, ((statbuf.st_mode & S_IWUSR) ? "w" : "-"));
	linea = strcat(linea, ((statbuf.st_mode & S_IXUSR) ? "x" : "-"));
	linea = strcat(linea, ((statbuf.st_mode & S_IRGRP) ? "r" : "-"));
	linea = strcat(linea, ((statbuf.st_mode & S_IWGRP) ? "w" : "-"));
	linea = strcat(linea, ((statbuf.st_mode & S_IXGRP) ? "x" : "-"));
	linea = strcat(linea, ((statbuf.st_mode & S_IROTH) ? "r" : "-"));
	linea = strcat(linea, ((statbuf.st_mode & S_IWOTH) ? "w" : "-"));
	linea = strcat(linea, ((statbuf.st_mode & S_IXOTH) ? "x" : "-"));

	// Se colocan los nombres de usuario y de grupo.
	if ((pwd = getpwuid(statbuf.st_uid)) != NULL)
		linea = strcat(linea, "  ");
		linea = strcat(linea, pwd->pw_name);
		linea = strcat(linea, "  "); 


	if ((grp = getgrgid(statbuf.st_gid)) != NULL)
		linea = strcat(linea, grp->gr_name);


	// Concatenamos la fecha de ultima modificacion y de ultimo acceso.
	char date1[10];
	char date2[10];
	strftime(date1, 20, "%y-%m-%d", localtime(&(statbuf.st_ctime)));
	strftime(date2, 20, "%y-%m-%d", localtime(&(statbuf.st_atime)));

	linea = strcat(linea, "  ");
	linea = strcat(linea, date1);
	linea = strcat(linea, "  ");
	linea = strcat(linea, date2);

	// Ahora simplemente se le añaden los datos obtenidos gracias a los procesos hijos, por medio de los pipes
	char temp1[15]  = "";
	char temp2[15]  = "";
    sprintf(temp1, "%d", archivos);
    sprintf(temp2, "%d", size);

	linea = strcat(linea, "  ");
    linea = strcat(linea, temp1);
    linea = strcat(linea, "  ");
    linea = strcat(linea, temp2);
    linea = strcat(linea, "  ");
	linea = strcat(linea, "\n");


	return linea;
}


/* Funcion que realiza la recursion, en ella el proceso se va adentrando en las subcarpetas. */
struct Elementos recursion(char * path, char nombre[], char * filename){


	int cont = 0; // Contador de archivos
	int size = 0; // Contador de tamanio total de los archivos
	struct stat st;
	char * dir_archivo;
	char * nuevo_dir;	// Variable de iteracion.
	char * dirhijo;

	nuevo_dir = malloc((1 + strlen("/") + strlen(nombre) + strlen(path))*sizeof(char));

	strcpy(nuevo_dir, path);
	strcat(nuevo_dir, "/");
	strcat(nuevo_dir, nombre);


	DIR *dirp_aux;
	dirp_aux = opendir(nuevo_dir);
	
	if (dirp_aux == NULL){
		printf("Error: No se puede abrir el directorio\n");
		exit(2);
	}

	struct dirent *direntp_aux;
	struct stat statbuf_aux;


	


	while ((direntp_aux = readdir(dirp_aux)) != NULL) {
		
        if (stat(nuevo_dir, &statbuf_aux) == -1)
        	continue;


		// Excluye a los que no son directorios y a los directorios . y ..
		if((direntp_aux->d_type == DT_DIR) && (strcmp(direntp_aux->d_name,".")!=0 ) && (strcmp(direntp_aux->d_name,"..")!=0)){

			FILE *f = fopen(filename, "a");
			if (f == NULL){
			    printf("Error opening file!\n");
			    exit(1);
			}

			cont++;

			// Directorio hijo, donde se va a obtener la informacion para el reporte
			dirhijo = malloc((1 + strlen("/") + strlen(direntp_aux->d_name) + strlen(nuevo_dir))*sizeof(char));
			strcpy(dirhijo, nuevo_dir);
			strcat(dirhijo, "/");
			strcat(dirhijo, direntp_aux->d_name);

			// Llamada de reporte
			char * reporte_aux;
			reporte_aux = reporte_proceso(statbuf_aux, dirhijo);

			// Recursion
			struct Elementos totalrecursion = recursion(nuevo_dir, direntp_aux->d_name, filename);

			cont = cont + totalrecursion.cantidad;
			size = size + totalrecursion.tamanio;
			free(dirhijo);

        	fprintf(f, "%s" ,reporte_aux);
        	fclose(f);
		}

		// Archivo regular
		if((direntp_aux->d_type == DT_REG) && (strcmp(direntp_aux->d_name,".")!=0 ) && (strcmp(direntp_aux->d_name,"..")!=0) && (strcmp(direntp_aux->d_name,"core")!= 0)){	
			cont++;
			dir_archivo = malloc((1 + strlen("/") + strlen(direntp_aux->d_name) + strlen(nuevo_dir))*sizeof(char));
			
			strcpy(dir_archivo, nuevo_dir);
			strcat(dir_archivo, "/");
			strcat(dir_archivo, direntp_aux->d_name);

			stat(dir_archivo, &st);
	
			size = size + st.st_size;

			free(dir_archivo);
		}

		// Archivo core
		if((direntp_aux->d_type == DT_REG) && (strcmp(direntp_aux->d_name,".")!=0 ) && (strcmp(direntp_aux->d_name,"..")!=0) && (strcmp(direntp_aux->d_name,"core") == 0)){
			
			FILE *f = fopen(filename, "a");
			if (f == NULL){
			    printf("Error opening file!\n");
			    exit(1);
			}

			dir_archivo = malloc((1 + strlen("/") + strlen(direntp_aux->d_name) + strlen(nuevo_dir))*sizeof(char));
			
			strcpy(dir_archivo, nuevo_dir);
			strcat(dir_archivo, "/");
			strcat(dir_archivo, direntp_aux->d_name);
			char * reporte_aux;

			reporte_aux = reporte_core(statbuf_aux, dir_archivo);
		    fprintf(f, "%s", reporte_aux);
        	fclose(f);
			int comprobarR;
			if ((comprobarR = remove(dir_archivo)) != 0)
				printf("Error al intentar remover archivo\n");
		
			free(dir_archivo);

		}	

	}
	struct Elementos total = {cont, size}; // Archivos y byte total de los archivos para informar al padre
	return total;
}

/* Funcion que hace el primer recorrido y crea los procesos */
void els(char * path, char *file){


	char * filename = malloc(sizeof(strlen(file)) + (10 * sizeof(char)));
	filename = strcpy(filename, "/tmp/");
	filename = strcat(filename, file);

	/* Chequeo si se puede escribir en el archivo tmp */
	int chequeo;
	chequeo = access ("/tmp/", W_OK);
	if (chequeo == EACCES || chequeo == EROFS){
		printf("El directorio no permite escritura\n");
		exit(2);
	}

	DIR *dirp;
	struct dirent *direntp;

    /* Abrimos el directorio */
	dirp = opendir(path);
	if (dirp == NULL){
		printf("Error: No se puede abrir el directorio\n");
		exit(2);
	}

	struct stat statbuf;
	int status, nprocesos;
	nprocesos = 0;
	pid_t childpid;

	int fd[2];

	// Abro un archivo para escribir el reporte global.
	FILE *f_padre = fopen(filename, "w");
	if (f_padre == NULL){
		printf("Error opening file!\n");
		exit(1);
	}

	// Este contador auxiliar nos servira para escribir el reporte del padre
	int contador = 0;


	while ((direntp = readdir(dirp)) != NULL) {


		// Se crea el pipe.
		pipe(fd);

		if (stat(direntp->d_name, &statbuf) == -1)
			continue;

		if (contador == 0){
			char * reporte_principal;
			reporte_principal = reporte_proceso(statbuf, path);
			fprintf(f_padre, "%s", reporte_principal);
			fclose(f_padre);
 			contador++;
 		}

 		// Se excluye si es un archivo regular. Se dejan solo los directorios diferentes a . y ..
 		// Ademas tambien se excluyen a los archivos ocultos.
		if((direntp->d_type == DT_DIR) && (direntp->d_name[0] != '.') &&(strcmp(direntp->d_name,".")!=0 ) && (strcmp(direntp->d_name,"..")!=0)){
 			nprocesos++;
		
    		
			if ((childpid = fork()) < 0) {
				perror("fork:");
				exit(1);
			} 


			if (childpid == 0) {
				// Procesos hijos.

				// Nombre archivo nuevo contendra el nombre del reporte para los procesos.
				char * nombre_archivo_nuevo = malloc((strlen(direntp->d_name) + 1 + strlen("-") + strlen(filename))*sizeof(char));
				nombre_archivo_nuevo = strcpy(nombre_archivo_nuevo, filename);
				nombre_archivo_nuevo = strcat(nombre_archivo_nuevo, "-");
				nombre_archivo_nuevo = strcat(nombre_archivo_nuevo, direntp->d_name);

				// Nuevo path contendra la ruta hacia el subdirectorio encontrado
				char * nuevo_path = malloc((1 + strlen("/") + strlen(direntp->d_name) + strlen(path))*sizeof(char));
				nuevo_path = strcpy(nuevo_path, path);
				nuevo_path = strcat(nuevo_path, "/");
				nuevo_path = strcat(nuevo_path, direntp->d_name);


				// Se abre un archivo con el nombre del reporte para los procesos hijos.
				FILE *f = fopen(nombre_archivo_nuevo, "w");
				if (f == NULL){
				    printf("Error opening file!\n");
				    exit(1);
				}

				// Se extrae una linea que va a parar al reporte del proceso hijo.
				char * reporte_subdirectorios = reporte_proceso(statbuf, nuevo_path);
				fprintf(f, "%s", reporte_subdirectorios);
				fclose(f);


				// Se llama a la recursion y devuelve el numero total de archivos encontrados, asi como tambien
				// el tamaño en bytes de todos los archivos encontrados.	
	    		struct Elementos miTotal = recursion(path, direntp->d_name, nombre_archivo_nuevo);


				int cantidadElementos = miTotal.cantidad;
				int cantidadBytes = miTotal.tamanio;

				// Cierro lectura
				close(fd[0]);
				// Paso por el pipe la informacion obtenida gracias a la recursion.
				write(fd[1], &cantidadElementos, sizeof(cantidadElementos));
				write(fd[1], &cantidadBytes, sizeof(cantidadBytes));
	    		exit(0);
			}	
			else if(childpid > 0){
				signal(SIGINT, sigintHandler); // El padre no puede ser terminado con CTRL+C
				wait(&status);
				int nroEle, tamEle; //nro y tamanio total de elementos de cada hijo
				
				// String que contendra la ruta al subdirectorio de primera capa encontrado.
				char *dir_hijo;
				dir_hijo = malloc((1 + strlen("/") + strlen(direntp->d_name) + strlen(path))*sizeof(char));
				strcpy(dir_hijo, path);
				strcat(dir_hijo, "/");
				strcat(dir_hijo, direntp->d_name);
				
				// Se cierra el pipe para escritura.
				close(fd[1]);

				// Se lee lo recibido por el pipe de los hijos.
				read(fd[0], &nroEle, sizeof(nroEle));
				read(fd[0], &tamEle, sizeof(tamEle));

				// Se abre de nuevo el archivo del reporte global.
				FILE *f_hijos = fopen(filename, "a");
				if (f_hijos == NULL){
				    printf("Error opening file!\n");
				    exit(1);
				}

				// Obtenemos el string que contiene el reporte global de los subdirectorios de la primera capa.
				char * escritura_subd = reporte_global_subdirectorios(statbuf, dir_hijo, nroEle, tamEle);

				free(dir_hijo);
				fprintf(f_hijos, "%s",escritura_subd);

				fclose(f_hijos);

			}
		} 

       	// Si es un core
		if((direntp->d_type == DT_REG) && (strcmp(direntp->d_name,".")!=0 ) && (strcmp(direntp->d_name,"..")!=0) && (strcmp(direntp->d_name,"core")==0) ){
			
			FILE *f = fopen(filename, "a");
			if (f == NULL){
			    printf("Error opening file!\n");
			    exit(1);
			}
			char *dir_core;
			dir_core = malloc((1 + strlen("/") + strlen(direntp->d_name) + strlen(path))*sizeof(char));

			strcpy(dir_core, path);
			strcat(dir_core, "/");
			strcat(dir_core, direntp->d_name);
			char * reporte_aux;
			reporte_aux = reporte_core(statbuf, dir_core);

		    fprintf(f, "%s", reporte_aux);
        	fclose(f);
			int comprobarR;
			if ((comprobarR = remove(dir_core)) != 0)
				printf("Error al intentar remover archivo\n");
		
			free(dir_core);				
			}
	}

	

	for (int i = 0; i < nprocesos; ++i){
		wait(&status);
	} 
	 
	/* Cerramos el directorio */
	closedir(dirp);
}

/* Funcion que devuelve la ruta desde donde se ejecuta el programa */
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
