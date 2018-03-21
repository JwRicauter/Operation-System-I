#include<stdio.h>

int main(){
	int i, j;
	for (i = 0, j = 0; i < 10 & j <100; i++, j+=10){
		printf("I: %d\n", i);
		printf("J: %d\n", j);
	}

	printf("i: %d\n", i);
	printf("J: %d\n", j);



	return 0;
}