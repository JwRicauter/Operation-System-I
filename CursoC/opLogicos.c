#include<stdio.h>

int main(){
	
	int a = 3, b = 5, c = 5, resultado;

	resultado = (a < b) && (b < c);
	printf("resultado1: %d\n", resultado);

	resultado = (a < b) || (b < c);
	printf("resultado2: %d\n", resultado);

	resultado = !(a != c);
	printf("resultado3: %d\n", resultado);


	return 0;
}