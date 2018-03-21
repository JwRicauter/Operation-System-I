#include<stdio.h>

int main(void){
	int a;
	int b;

	printf("ingrese el valor de a: ");
	fflush(stdin); // Borramos el buffer de entrada
	scanf("%d", &a);
	fflush(stdin); 

	printf("ingrese el valor de b: ");
	scanf("%d", &b);
	fflush(stdin);

	printf("\n a = %d", a);
	printf("\n b = %d\n", b);


	return 0;
}