#include <stdio.h>

int main(){
	
	int matriz1[2][3];

	// Pongo los de la fila 1

	matriz1[0][0] = 1;
	matriz1[0][1] = 2;
	matriz1[0][2] = 3;

	// Pongo los de la fila 2

	matriz1[1][0] = -1;
	matriz1[1][1] = -2;
	matriz1[1][2] = -5;

	printf("matriz[0][0]: %d\n", matriz1[0][0]);

	// Puedo tener matrices de muchas dimensiones.

	return 0;
}