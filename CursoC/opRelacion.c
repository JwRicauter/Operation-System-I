#include<stdio.h>

int main(){
	int a = 3, b = 5, c = 3, resultado;

	resultado = (a < b);
	printf("a < b resultado: %d\n", resultado);

	resultado = (a > b);
	printf("a > b resultado: %d\n", resultado);

	resultado = (a == b);
	printf("a == b resultado: %d\n", resultado);

	resultado = (a == c);
	printf("a == c resultado: %d\n", resultado);


	return 0;
}