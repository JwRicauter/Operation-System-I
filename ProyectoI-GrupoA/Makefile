#Alumnos:
#	Denylson Romero, 13-11270
#	Jawil Ricauter, 13-11199

# Compilador
COMP = gcc

# Flags de depuración
DEBUG = -Wall -Wextra -ggdb

# Opción por defecto al hacer make
default: clean pscheduler libClean

# Seccion donde se ejecuta el main.c
pscheduler: funciones.o
	$(COMP) $(DEBUG) *.o main.c -o els

# Compilar archivos auxiliares del main.
funciones.o: funciones.c funciones.h
	$(COMP) $(DEBUG) -c funciones.c -o funciones.o

# Elimina los ejecutables.
libClean:
	$(RM) *.o

# Eliminar todo
clean:
	$(RM) pscheduler *.o