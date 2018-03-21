#include<stdio.h>

int main(){
	
	int x = 1, y = 13, z;
	
	if (x > y){
		printf("x > y\n");
	}
	else if(x < y){
		printf("x < y\n");
	}
	else if(x == y){
		printf("x == y\n");
	}

	printf("Estoy debajo de los if/else\n");


	return 0;
}