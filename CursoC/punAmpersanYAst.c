#include <stdio.h>

int main(){
	
	int a = 10;
	printf("El valor de a: %d\n", a);
	printf("La direccion de a: %d\n", &a);

	int *p1, *p2;
	p1 = &a;
	p2 = p1;	

	printf("El valor de p1: %d\n", p1);
	printf("La direccion de p1: %d\n", &p1);
	printf("Lo que apunta p1: %d\n", *p1);

	printf("El valor de p2: %d\n", p2);
	printf("La direccion de p2: %d\n", &p2);
	printf("Lo que apunta p2: %d\n", *p2);

	return 0;
}