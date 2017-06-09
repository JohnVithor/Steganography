#include <stdio.h>
#include <stdlib.h>

#include "funcoes.h"
#include "structs.h"

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

int escondeMsgPPM(char *mensagem, int tamanhoDaMsg, imgPPM *imagemLida){
	int i = 0, j = 0;
	if (tamanhoDaMsg >= imagemLida->altura * imagemLida->largura * 4){
		return 1;
	}
	for (int c = 0; c < tamanhoDaMsg; ++c){
		escondeChar(mensagem[c], imagemLida->pixelMap, imagemLida->largura, &i, &j);
	}
	char fim = '\0';
	escondeChar(fim, imagemLida->pixelMap, imagemLida->largura, &i, &j);
	return 0;
}

int descobreMsgPPM(char *mensagem, imgPPM *imagemLida){
	int i = 0, j = 0, k = 0;
	char caractere;
	do{
		caractere = descobreChar(imagemLida->pixelMap, imagemLida->largura, i, j);
		j += 4;
		if (j >= imagemLida->largura){
		 	++i;
		 } 
		adicionaChar(mensagem,caractere);	
		if (i == imagemLida->altura - 1 && j == imagemLida->largura){
			return 1;
		}
		++k;
	}while(caractere != '\0');
	return 0;
}
