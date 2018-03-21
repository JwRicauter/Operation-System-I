#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <signal.h>

#ifndef FUNCIONESH
#define FUNCIONESH


struct Elementos;

struct Elementos Contador(char *path);

void sigintHandler(int sig_num);

char * reporte_core(struct stat statbuf, char * direccion);

char * reporte_proceso(struct stat statbuf, char * direccion);

char * reporte_global_subdirectorios(struct stat statbuf, char * direccion, int archivos, int size); 

struct Elementos recursion(char * path, char nombre[], int comp, char * filename);

void els(char * path, char *file);

char * ruta_actual();

#endif

