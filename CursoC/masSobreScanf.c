#include<stdio.h>

int main(){
	int a;
	float b;
	char c;

	printf("Ingtrese a,b y c separados por coma");
	scanf("%d, %f, %c\n", &a, &b, &c);


	printf("a: %d\n", a);
	printf("b: %g\n", b);
	printf("c: %c\n", c);


	return 0;
}