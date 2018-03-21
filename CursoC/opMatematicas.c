#include<stdio.h>

int main(){
	int var1 = 2;
	int var2 = 11;

	int resultado =	var1 + var2;
	printf("%d + %d = %d\n", var1, var2, resultado);

	resultado =	var1 - var2;
	printf("%d - %d = %d\n", var1, var2, resultado);

	resultado =	var1 * var2;
	printf("%d * %d = %d\n", var1, var2, resultado);

	resultado =	var1 / var2;
	printf("%d / %d = %d\n", var1, var2, resultado);

	resultado =	var1 % var2;
	printf("Resto de %d / %d = %d\n", var1, var2, resultado);

	return 0;
}