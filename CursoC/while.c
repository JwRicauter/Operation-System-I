#include<stdio.h>

int main(){

	int valor1 = 0, valor2 = 10;

	while(valor1 < valor2){
		printf("Estoy dentro del ciclo %d\n", valor1);
		valor1++;
		if(valor1 < 5)printf("e\n");
	}

	printf("Ya estoy fuera del ciclo %d\n", valor1);
	


	return 0;
}