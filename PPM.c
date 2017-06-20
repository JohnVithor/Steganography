#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "funcoes.h"
#include "structs.h"

void abreImgPPM(char *nomeImg, imgPPM *imagemLida){
	FILE* arqEntrada;

	if((arqEntrada = fopen(nomeImg, "rb")) == NULL){
		fprintf(stderr, "Impossível de abrir o arquivo.\n");
		exit(1);
	}

	// Lê as infomações do cabeçalho
	fscanf(arqEntrada, "%s\n", imagemLida->id);
	fscanf(arqEntrada, "%u %u\n", &imagemLida->largura, &imagemLida->altura);
	fscanf(arqEntrada, "%u\n", &imagemLida->max);

	// Aloca a matriz de pixel com base nas informações lidas no cabeçalho
	imagemLida->pixelMap = (pixel **) malloc (imagemLida->altura * sizeof(pixel *));
	for (int i = 0; i < imagemLida->altura; i++ ){
		imagemLida->pixelMap[i] = (pixel *) malloc (imagemLida->largura * sizeof(pixel));
	}

	// Inicia a leitura dos pixels
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
		fprintf(stderr, "Impossível de salvar o arquivo.\n");
		exit(1);
	}

	// Escreve as informações do cabeçalho
	fprintf(arqSaida, "%s\n", imagemLida->id);
	fprintf(arqSaida, "%u %u\n", imagemLida->largura, imagemLida->altura);
	fprintf(arqSaida, "%u\n", imagemLida->max);
	
	// Escreve as informações de cada cor na matriz de pixels
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
	// Crio dois indices para percorrer a matriz de pixels
	int i = 0, j = 0;
	// Verifico se a imagem é grande o suficiente para comportar a mensagem
	if (tamanhoDaMsg >= imagemLida->altura * imagemLida->largura * 4){
		return 1;
	}
	// Para cada caractere da mensagem eu chamo a função escondeChar()
	for (int c = 0; c < tamanhoDaMsg; ++c){
		escondeChar((unsigned char) mensagem[c], imagemLida->pixelMap, imagemLida->largura, &i, &j);
	}
	// Escondo um caractere de fim de string para poder recuperar a mensagem depois
	escondeChar('\0', imagemLida->pixelMap, imagemLida->largura, &i, &j);
	return 0;
}

int descobreMsgPPM(char saida, imgPPM *imagemLida, char *arquivoTexto){
	// Crio dois indices para percorrer a matriz de pixels
	int i = 0, j = 0;
	char caractere;
	FILE *arqSaida;
	if (saida == 'o'){
		// Crio o arquivo onde a mensagem será salva
		if((arqSaida = fopen(arquivoTexto, "w")) == NULL){
			fprintf(stderr, "Impossível de salvar o arquivo.\n");
			exit(1);
		}
		printf("Mensagem será salva no arquivo %s\n", arquivoTexto);
	} else {
		arqSaida = stdout;
		printf("Mensagem encontrada será impressa na tela\n");
	}
	do {
		// Um caractere previamente criado recebe o caractere recuperado da imagem
		caractere = descobreChar(imagemLida->pixelMap, imagemLida->largura, &i, &j);
		// Adiciono o caractere recuperado a uma string
		salvaChar(arqSaida, caractere);
		// Verifica se já foram percorridos todos os pixels da imagem
		if (i == imagemLida->altura - 1 && j == imagemLida->largura){
			return 1;
		}
	// Continua o laço de repetição enquanto não for encontrado um '\0' na imagem
	} while (caractere != '\0');
	fclose(arqSaida);
	return 0;
}
