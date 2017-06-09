#include <stdio.h>
#include <stdlib.h>

#include "funcoes.h"
#include "structs.h"

void lerHeaderBMP(imgBMP *imagemLida, FILE* arqEntrada){
	fread(&imagemLida->header.fileType, sizeof(unsigned short int), 1, arqEntrada);
	fread(&imagemLida->header.fileSize, sizeof(unsigned int), 1, arqEntrada);
	fread(&imagemLida->header.fileReserved1, sizeof(unsigned short int), 1, arqEntrada);
	fread(&imagemLida->header.fileReserved2, sizeof(unsigned short int), 1, arqEntrada);
	fread(&imagemLida->header.fileOffBits, sizeof(unsigned int), 1, arqEntrada);
	return;
}

void lerInfoBMP(imgBMP *imagemLida, FILE* arqEntrada){
	fread(&imagemLida->info.header.biSize, sizeof(unsigned int), 1, arqEntrada);
	fread(&imagemLida->info.header.biWidth, sizeof(unsigned int), 1, arqEntrada);
	fread(&imagemLida->info.header.biHeight, sizeof(unsigned int), 1, arqEntrada);
	fread(&imagemLida->info.header.biPlanes, sizeof(unsigned short int), 1, arqEntrada);
	fread(&imagemLida->info.header.biBitCount, sizeof(unsigned short int), 1, arqEntrada);
	fread(&imagemLida->info.header.biCompression, sizeof(unsigned int), 1, arqEntrada);
	fread(&imagemLida->info.header.biSizeImage, sizeof(unsigned int), 1, arqEntrada);
	fread(&imagemLida->info.header.biXpelsPerMeter, sizeof(unsigned int), 1, arqEntrada);
	fread(&imagemLida->info.header.biYpelsPerMeter, sizeof(unsigned int), 1, arqEntrada);
	fread(&imagemLida->info.header.biClrUsed, sizeof(unsigned int), 1, arqEntrada);
	fread(&imagemLida->info.header.biClrImportant, sizeof(unsigned int), 1, arqEntrada);
	return;
}

void escreverHeaderBMP(imgBMP *imagemLida, FILE* arqSaida){
	fwrite(&imagemLida->header.fileType, sizeof(unsigned short int), 1, arqSaida);
	fwrite(&imagemLida->header.fileSize, sizeof(unsigned int), 1, arqSaida);
	fwrite(&imagemLida->header.fileReserved1, sizeof(unsigned short int), 1, arqSaida);
	fwrite(&imagemLida->header.fileReserved2, sizeof(unsigned short int), 1, arqSaida);
	fwrite(&imagemLida->header.fileOffBits, sizeof(unsigned int), 1, arqSaida);
	return;
}

void escreverInfoBMP(imgBMP *imagemLida, FILE* arqSaida){
	fwrite(&imagemLida->info.header.biSize, sizeof(unsigned int), 1, arqSaida);
	fwrite(&imagemLida->info.header.biWidth, sizeof(unsigned int), 1, arqSaida);
	fwrite(&imagemLida->info.header.biHeight, sizeof(unsigned int), 1, arqSaida);
	fwrite(&imagemLida->info.header.biPlanes, sizeof(unsigned short int), 1, arqSaida);
	fwrite(&imagemLida->info.header.biBitCount, sizeof(unsigned short int), 1, arqSaida);
	fwrite(&imagemLida->info.header.biCompression, sizeof(unsigned int), 1, arqSaida);
	fwrite(&imagemLida->info.header.biSizeImage, sizeof(unsigned int), 1, arqSaida);
	fwrite(&imagemLida->info.header.biXpelsPerMeter, sizeof(unsigned int), 1, arqSaida);
	fwrite(&imagemLida->info.header.biYpelsPerMeter, sizeof(unsigned int), 1, arqSaida);
	fwrite(&imagemLida->info.header.biClrUsed, sizeof(unsigned int), 1, arqSaida);
	fwrite(&imagemLida->info.header.biClrImportant, sizeof(unsigned int), 1, arqSaida);
	return;
}

void abreImgBMP(char *nomeImg, imgBMP *imagemLida){
	FILE* arqEntrada;

	if((arqEntrada = fopen(nomeImg, "rb")) == NULL){
		printf("Impossível de abrir o arquivo.\n");
		exit(1);
	}

	lerHeaderBMP(imagemLida, arqEntrada);
		
	lerInfoBMP(imagemLida, arqEntrada);
	
	imagemLida->pixelMap = (pixel **) malloc (imagemLida->info.header.biHeight * sizeof(pixel *));
	for (int i = 0; i < imagemLida->info.header.biHeight; i++ ){
		imagemLida->pixelMap[i] = (pixel *) malloc (imagemLida->info.header.biWidth * sizeof(pixel));
	}

	imagemLida->padRow = (pading *) malloc (imagemLida->info.header.biWidth * sizeof(pading));

	for (int i = 0; i < imagemLida->info.header.biHeight; ++i){
		for (int j = 0; j < imagemLida->info.header.biWidth; ++j){
			imagemLida->pixelMap[i][j].B = fgetc(arqEntrada);
			imagemLida->pixelMap[i][j].G = fgetc(arqEntrada);
			imagemLida->pixelMap[i][j].R = fgetc(arqEntrada);
		}
		imagemLida->padRow[i].P1 = fgetc(arqEntrada);
		imagemLida->padRow[i].P2 = fgetc(arqEntrada);
	}

	fclose(arqEntrada);
	return;
}

void salvaImgBMP(char *nomeImg, imgBMP *imagemLida){
	FILE *arqSaida;
	if((arqSaida = fopen(nomeImg, "wb")) == NULL){
		printf("Impossível de salvar o arquivo.\n");
		exit(1);
	}

	escreverHeaderBMP(imagemLida, arqSaida);
		
	escreverInfoBMP(imagemLida, arqSaida);

	for (int i = 0; i < imagemLida->info.header.biHeight; ++i){
		for (int j = 0; j < imagemLida->info.header.biWidth; ++j){
			putc(imagemLida->pixelMap[i][j].B, arqSaida);
			putc(imagemLida->pixelMap[i][j].G, arqSaida);
			putc(imagemLida->pixelMap[i][j].R, arqSaida);
		}
		putc(imagemLida->padRow[i].P1, arqSaida);
		putc(imagemLida->padRow[i].P2, arqSaida);
	}
	fclose(arqSaida);
	return;
}

int escondeMsgBMP(char *mensagem, int tamanhoDaMsg, imgBMP *imagemLida){
	int i = 0, j = 0;
	if (tamanhoDaMsg >= imagemLida->info.header.biHeight * imagemLida->info.header.biWidth * 4){
		return 1;
	}
	for (int c = 0; c < tamanhoDaMsg; ++c){
		escondeChar(mensagem[c], imagemLida->pixelMap, imagemLida->info.header.biWidth, &i, &j);
	}
	char fim = '\0';
	escondeChar(fim, imagemLida->pixelMap, imagemLida->info.header.biWidth, &i, &j);
	return 0;
}

int descobreMsgBMP(char *mensagem, imgBMP *imagemLida){
	int i = 0, j = 0, k = 0;
	char caractere;
	do{
		caractere = descobreChar(imagemLida->pixelMap, imagemLida->info.header.biWidth, i, j);
		j += 4;
		if (j >= imagemLida->info.header.biWidth){
		 	++i;
		 } 
		adicionaChar(mensagem,caractere);	
		if (i == imagemLida->info.header.biHeight - 1 && j == imagemLida->info.header.biWidth){
			return 1;
		}
		++k;
	}while(caractere != '\0');
	return 0;
}
