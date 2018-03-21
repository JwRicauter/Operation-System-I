#include <stdio.h>


// Nueva manera
typedef struct video{
	char titulo[41];
	int visitas;
	float tiempo;
}video_t;

// Vieja Manera
// typedef struct video video_t;

video_t crear_video(){
	video_t nuevo_video;

	printf("\nIngrese el nombre del video: ");
	__fpurge(stdin);
	gets(nuevo_video.titulo);

	printf("\nIngrese el numero de visitas: ");
	__fpurge(stdin);
	scanf("%d", &nuevo_video.visitas);

	printf("\nIngrese el tiempo del video: ");
	__fpurge(stdin);
	scanf("%f", &nuevo_video.tiempo);

	return nuevo_video;


}

void imprimir_video(video_t video){
	printf("%s, tiempo %g, visitas %d \n", video.titulo, video.tiempo, video.visitas);
}

int main(){

	video_t v1 = crear_video();
	video_t v2 = crear_video();

	imprimir_video(v2);
	

	return 0;
}