#include<stdio.h>

int main(void){
	
	int i = 7;
	int size, direc;
	size = sizeof(int);
	direc = &i;


	printf("i: %d\n", i);
	printf("size: %d bytes\n", size);
	printf("direccion: %d\n", direc);


	return 0;
}