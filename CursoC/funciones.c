#include <stdio.h>

int ardilla(){
	int algo = 3;
	return algo;
}

void funcion_que_no_devuelve(){
	printf("ESTA FUNCION NO DEVUELVE NADA");

}

int cuadrado(int numero){
	int cuad = numero * numero;
	return cuad;
}

int main(){
	int x;
	printf("Hola \n"); // Llama a printf y le pasa "hola como parametro"
	x = ardilla();
	printf("%d\n", x);
	funcion_que_no_devuelve();
	int n = 5, resultado;

	resultado = cuadrado(n);
	printf("\n%d\n", resultado);

	return 0;
}