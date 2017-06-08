#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "funcoes.h"
#include "structs.h"

void printHeaderPPM(imgPPM *imagemLida){
	printf("id %s\n", imagemLida->id);
	printf("largura %u\n", imagemLida->largura);
	printf("altura %u\n", imagemLida->altura);
	printf("max %u\n", imagemLida->max);
}

void printHeaderBMP(imgBMP *imagemLida){
	printf("fileType %u\n", imagemLida->header.fileType);
	printf("fileSize %u\n", imagemLida->header.fileSize);
	printf("fileReserved1 %u\n", imagemLida->header.fileReserved1);
	printf("fileReserved2 %u\n", imagemLida->header.fileReserved2);
	printf("fileOffBits %u\n", imagemLida->header.fileOffBits);

	printf("biSize %u\n", imagemLida->info.header.biSize);
	printf("biWidth %u\n", imagemLida->info.header.biWidth);
	printf("biHeight %u\n", imagemLida->info.header.biHeight);
	printf("biPlanes %u\n", imagemLida->info.header.biPlanes);
	printf("biBitCount %u\n", imagemLida->info.header.biBitCount);
	printf("biCompression %u\n", imagemLida->info.header.biCompression);
	printf("biSizeImage %u\n", imagemLida->info.header.biSizeImage);
	printf("biXpelsPerMeter %u\n", imagemLida->info.header.biXpelsPerMeter);
	printf("biYpelsPerMeter %u\n", imagemLida->info.header.biYpelsPerMeter);
	printf("biClrUsed %u\n", imagemLida->info.header.biClrUsed);
	printf("biClrImportant %u\n", imagemLida->info.header.biClrImportant);
}

int main(int argc, char** argv){
	if(argc != 7){
		printf("./steg -e -i <input-file> -f <format> <image>\n");
		printf("./steg -d -o <output-file> -f <format> <image>\n");
		return 1;
	}

	char *msgLida;
	unsigned long tamanhoDaMsg;
	
	msgLida = abreMsg(argv[3], &tamanhoDaMsg);
	salvaMsg("Saida.txt",msgLida);

if (strcmp(argv[5], "ppm") == 0){
	imgPPM imagemLida;
	abreImgPPM(argv[6], &imagemLida);
	if (escondeMsg(msgLida,tamanhoDaMsg,&imagemLida)){
		printf("erro\n");
	}
	
	//imagemLida.pixelMap[1][1].R ^= 1;


	printHeaderPPM(&imagemLida);
	printf("R %c\n", imagemLida.pixelMap[1][1].R);
	printf("G %c\n", imagemLida.pixelMap[1][1].G);
	printf("B %c\n", imagemLida.pixelMap[1][1].B);



	salvaImgPPM("Saida.ppm", &imagemLida);
	//printHeaderPPM(&imagemLida);
}
if (strcmp(argv[5], "bmp") == 0){
	imgBMP imagemLida;
	abreImgBMP(argv[6], &imagemLida);
	salvaImgBMP("Saida.bmp", &imagemLida);
	printHeaderBMP(&imagemLida);
}

	free(msgLida);
	return 0;
}