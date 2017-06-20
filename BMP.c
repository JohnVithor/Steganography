#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "funcoes.h"
#include "structs.h"

void lerHeaderBMP(imgBMP *imagemLida, FILE* arqEntrada){
	// Lê a primeira parte do cabeçalho
	fread(&imagemLida->header.fileType, sizeof(unsigned short int), 1, arqEntrada);
	fread(&imagemLida->header.fileSize, sizeof(unsigned int), 1, arqEntrada);
	fread(&imagemLida->header.fileReserved1, sizeof(unsigned short int), 1, arqEntrada);
	fread(&imagemLida->header.fileReserved2, sizeof(unsigned short int), 1, arqEntrada);
	fread(&imagemLida->header.fileOffBits, sizeof(unsigned int), 1, arqEntrada);
	return;
}

void lerInfoBMP(imgBMP *imagemLida, FILE* arqEntrada){
	// Lê a segunda parte do cabeçalho
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
	// Escreve a primeira parte do cabeçalho
	fwrite(&imagemLida->header.fileType, sizeof(unsigned short int), 1, arqSaida);
	fwrite(&imagemLida->header.fileSize, sizeof(unsigned int), 1, arqSaida);
	fwrite(&imagemLida->header.fileReserved1, sizeof(unsigned short int), 1, arqSaida);
	fwrite(&imagemLida->header.fileReserved2, sizeof(unsigned short int), 1, arqSaida);
	fwrite(&imagemLida->header.fileOffBits, sizeof(unsigned int), 1, arqSaida);
	return;
}

void escreverInfoBMP(imgBMP *imagemLida, FILE* arqSaida){
	// Escreve a segunda parte do cabeçalho
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
		fprintf(stderr, "Impossível de abrir o arquivo.\n");
		exit(1);
	}

	lerHeaderBMP(imagemLida, arqEntrada);
		
	lerInfoBMP(imagemLida, arqEntrada);
	
	// Aloca a matriz de pixel com base nas informações lidas no cabeçalho
	imagemLida->pixelMap = (pixel **) malloc (imagemLida->info.header.biHeight * sizeof(pixel *));
	for (int i = 0; i < imagemLida->info.header.biHeight; i++ ){
		imagemLida->pixelMap[i] = (pixel *) malloc (imagemLida->info.header.biWidth * sizeof(pixel));
	}
	// Aloca o 'pading' que informa o fim de linha no BMP
	imagemLida->padRow = (pading *) malloc (imagemLida->info.header.biWidth * sizeof(pading));

	// Inicia a leitura dos pixels
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
		fprintf(stderr, "Impossível de salvar o arquivo.\n");
		exit(1);
	}

	escreverHeaderBMP(imagemLida, arqSaida);
		
	escreverInfoBMP(imagemLida, arqSaida);

	// Escreve as informações de cada cor na matriz de pixels
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
	// Crio dois indices para percorrer a matriz de pixels
	int i = 0, j = 0;
	// Verifico se a imagem é grande o suficiente para comportar a mensagem
	if (tamanhoDaMsg >= imagemLida->info.header.biHeight * imagemLida->info.header.biWidth * 4){
		return 1;
	}
	// Para cada caractere da mensagem eu chamo a função escondeChar()
	for (int c = 0; c < tamanhoDaMsg; ++c){
		escondeChar((unsigned char) mensagem[c], imagemLida->pixelMap, imagemLida->info.header.biWidth, &i, &j);
	}
	// Escondo um caractere de fim de string para poder recuperar a mensagem depois
	escondeChar('\0', imagemLida->pixelMap, imagemLida->info.header.biWidth, &i, &j);
	return 0;
}

int descobreMsgBMP(char saida, imgBMP *imagemLida, char *arquivoTexto){
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
		caractere = descobreChar(imagemLida->pixelMap, imagemLida->info.header.biWidth, &i, &j);
		// Adiciono o caractere recuperado a uma string
		salvaChar(arqSaida, caractere);
		// Verifica se já foram percorridos todos os pixels da imagem
		if (i == imagemLida->info.header.biHeight - 1 && j >= imagemLida->info.header.biWidth){
			return 1;
		}
	// Continua o laço de repetição enquanto não for encontrado um '\0' na imagem
	} while (caractere != '\0');
	fclose(arqSaida);
	return 0;
}
