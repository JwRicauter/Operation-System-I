#include<stdio.h>

int main(){

	int vector[3];
	float vector_float[100];

	vector_float[56] = 3.1459785462;

	vector[0] = 1;
	vector[1] = 2;
	vector[2] = 3;
	vector[3] = 4;

	printf("Vector en la posicion 0: %d\n", vector[0]);
	printf("Vector en la posicion 1: %d\n", vector[1]);
	printf("Vector en la posicion 2: %d\n", vector[2]);
	printf("Vector en la posicion 3: %d\n", vector[3]);

	printf("Vector float en la posicion 56: %f\n", vector_float[56]);

	return 0;
}