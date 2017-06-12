#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "funcoes.h"
#include "structs.h"

char* abreMsg(char *nomeMsg, unsigned long *tamanhoMsg){
	FILE* arqEntrada;
	if((arqEntrada = fopen(nomeMsg, "r")) == NULL){
		fprintf(stderr, "Impossível de abrir o arquivo.\n");
		exit(1);
	}

	// Verifico qual o tamanho da mensagem a ser lida
	fseek(arqEntrada, 0, SEEK_END);
	*tamanhoMsg = (unsigned long)ftell(arqEntrada);
	fseek(arqEntrada, SEEK_SET, 0);

	// Aloco o tamanho necessario 
	char *mensagem;
	if((mensagem = (char*) malloc(sizeof(char) * (*tamanhoMsg))) == NULL){
		fprintf(stderr, "Erro durante a alocação da memória.\n");
		exit(1);
	}
	// Leio a mensagem
	fread (mensagem , sizeof(char), *tamanhoMsg , arqEntrada);
	fclose(arqEntrada);
	return mensagem;
}

void salvaMsg(char *nomeMsg, char *mensagem){
	FILE *arqSaida;
	// Crio o arquivo onde a mensagem será salva
	if((arqSaida = fopen(nomeMsg, "w")) == NULL){
		fprintf(stderr, "Impossível de salvar o arquivo.\n");
		exit(1);
	}
	// Escrevo a mensagem no arquivo criado
	fwrite (mensagem , sizeof(char), strlen(mensagem) ,arqSaida);
	fclose(arqSaida);
}

void escondeChar(unsigned char caractere, pixel** pixelMap, int largura, int *i, int *j){
	for (int b = 0; b < 4; ++b){
		if ((caractere % 2) == 1){
			if ((pixelMap[*i][*j].R % 2) == 0){
				pixelMap[*i][*j].R ^= 1;
			}
		} else {
			if ((pixelMap[*i][*j].R % 2) == 1){
				pixelMap[*i][*j].R &= 254;
			}
		}
		caractere /= 2;
		if ((caractere % 2)){
			if ((pixelMap[*i][*j].G % 2) == 0){
				pixelMap[*i][*j].G ^= 1;
			}
		} else {
			if ((pixelMap[*i][*j].G % 2) == 1){
				pixelMap[*i][*j].G &= 254;
			}
		}
		caractere /= 2;
		++(*j);
		if (*j == largura){
			++(*i);
			*j = 0;
		}
	}
	return;
}

unsigned char descobreChar(pixel** pixelMap, int largura, int *i, int *j){
	// Crio um caractere 
	unsigned char caractere = 0;
	for (int b = 0; b < 8; b += 2){
		// Recupero o LSB do pixel indicado e o multiplico pela devida potencia de 2
		// Somo o resultado no caractere previamente criado
		caractere += (pixelMap[*i][*j].R % 2) * pow(2,b);
		caractere += (pixelMap[*i][*j].G % 2) * pow(2,b+1);
		// Incremento o indice
		++(*j);
		if (*j == largura){
			++(*i);
			*j = 0;
		}
	}
	return caractere;
}

void adicionaChar(char *mensagem,int tamanhoMsg ,unsigned char c){
	// Crio um vetor com um único elemento
	// Armazeno o char a ser adicionado na mensagem
	// Realoco o tamanho necessario para poder concatenar o caractere com a mensagem
	// Utilizo a função strcat()
	char aux[1];
	aux[0] = c;
	mensagem = realloc(mensagem,(tamanhoMsg+1)*sizeof(char));
	strcat(mensagem,aux);
	return;
}
