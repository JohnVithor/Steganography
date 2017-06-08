#include <stdio.h>
#include <stdlib.h>

#include "funcoes.h"
#include "structs.h"
////////////////////////////////////////////////////////////////////////////////////////////////////
//						Abrir/Salvar Imagens PPM
////////////////////////////////////////////////////////////////////////////////////////////////////

void abreImgPPM(char *nomeImg, imgPPM *imagemLida){
	FILE* arqEntrada;

	if((arqEntrada = fopen(nomeImg, "rb")) == NULL){
		printf("Impossível de abrir o arquivo.\n");
		exit(1);
	}

	fscanf(arqEntrada, "%s\n", imagemLida->id);
	fscanf(arqEntrada, "%u %u\n", &imagemLida->largura, &imagemLida->altura);
	fscanf(arqEntrada, "%u\n", &imagemLida->max);

	imagemLida->pixelMap = (pixel **) malloc (imagemLida->altura * sizeof(pixel *));
	for (int i = 0; i < imagemLida->altura; i++ ){
		imagemLida->pixelMap[i] = (pixel *) malloc (imagemLida->largura * sizeof(pixel));
	}

	for (int i = 0; i < imagemLida->altura; ++i){
		for (int j = 0; j < imagemLida->largura; ++j){
			imagemLida->pixelMap[i][j].R = fgetc(arqEntrada);
			imagemLida->pixelMap[i][j].G = fgetc(arqEntrada);
			imagemLida->pixelMap[i][j].B = fgetc(arqEntrada);
		}
	}

	fclose(arqEntrada);
	return;
}

void salvaImgPPM(char *nomeImg, imgPPM *imagemLida){
	FILE *arqSaida;
	if((arqSaida = fopen(nomeImg, "wb")) == NULL){
		printf("Impossível de salvar o arquivo.\n");
		exit(1);
	}	
	fprintf(arqSaida, "%s\n", imagemLida->id);
	fprintf(arqSaida, "%u %u\n", imagemLida->largura, imagemLida->altura);
	fprintf(arqSaida, "%u\n", imagemLida->max);
	
	for (int i = 0; i < imagemLida->altura; ++i){
		for (int j = 0; j < imagemLida->largura; ++j){
			putc(imagemLida->pixelMap[i][j].R, arqSaida);
			putc(imagemLida->pixelMap[i][j].G, arqSaida);
			putc(imagemLida->pixelMap[i][j].B, arqSaida);
		}
	}
	fclose(arqSaida);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
//						Abrir/Salvar Imagens BMP
////////////////////////////////////////////////////////////////////////////////////////////////////

void lerHeaderBMP(imgBMP *imagemLida, FILE* arqEntrada){
	fread(&imagemLida->header.fileType, sizeof(unsigned short int), 1, arqEntrada);
	fread(&imagemLida->header.fileSize, sizeof(unsigned int), 1, arqEntrada);
	fread(&imagemLida->header.fileReserved1, sizeof(unsigned short int), 1, arqEntrada);
	fread(&imagemLida->header.fileReserved2, sizeof(unsigned short int), 1, arqEntrada);
	fread(&imagemLida->header.fileOffBits, sizeof(unsigned int), 1, arqEntrada);
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
}

void escreverHeaderBMP(imgBMP *imagemLida, FILE* arqSaida){
	fwrite(&imagemLida->header.fileType, sizeof(unsigned short int), 1, arqSaida);
	fwrite(&imagemLida->header.fileSize, sizeof(unsigned int), 1, arqSaida);
	fwrite(&imagemLida->header.fileReserved1, sizeof(unsigned short int), 1, arqSaida);
	fwrite(&imagemLida->header.fileReserved2, sizeof(unsigned short int), 1, arqSaida);
	fwrite(&imagemLida->header.fileOffBits, sizeof(unsigned int), 1, arqSaida);
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
}

void abreImgBMP(char *nomeImg, imgBMP *imagemLida){
	FILE* arqEntrada;

	if((arqEntrada = fopen(nomeImg, "rb")) == NULL){
		printf("Impossível de abrir o arquivo.\n");
		exit(1);
	}

	lerHeaderBMP(imagemLida, arqEntrada);
		
	lerInfoBMP(imagemLida, arqEntrada);
	
	imagemLida->pixelMap = (RGBSquad **) malloc (imagemLida->info.header.biHeight * sizeof(RGBSquad *));
	for (int i = 0; i < imagemLida->info.header.biHeight; i++ ){
		imagemLida->pixelMap[i] = (RGBSquad *) malloc (imagemLida->info.header.biWidth * sizeof(RGBSquad));
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
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//						Abrir/Salvar Mensagens TXT
////////////////////////////////////////////////////////////////////////////////////////////////////

char* abreMsg(char *nomeMsg, unsigned long *tamanhoMsg){
	FILE* arqEntrada;
	if((arqEntrada = fopen(nomeMsg, "r")) == NULL){
		printf("Impossível de abrir o arquivo.\n");
		exit(1);
	}

	fseek(arqEntrada, 0, SEEK_END);
	*tamanhoMsg = (unsigned long)ftell(arqEntrada);
	fseek(arqEntrada, SEEK_SET, 0);

	char *mensagem;
	if((mensagem = (char*) malloc(sizeof(char) * (*tamanhoMsg)+1)) == NULL){
		printf("Erro durante a alocação da memória.\n");
		exit(1);
	}
	
	fgets (mensagem , *tamanhoMsg , arqEntrada);
	fclose(arqEntrada);
	return mensagem;
}

void salvaMsg(char *nomeMsg, char *mensagem){
	FILE *arqSaida;
	if((arqSaida = fopen(nomeMsg, "w")) == NULL){
		printf("Impossível de salvar o arquivo.\n");
		exit(1);
	}
	fputs (mensagem , arqSaida);
	fclose(arqSaida);
}