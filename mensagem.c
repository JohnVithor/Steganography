#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "funcoes.h"
#include "structs.h"

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


void escondeChar(char caractere, pixel** pixelMap, int largura, int *i, int *j){
	for (int b = 0; b < 4; ++b){
		if ((caractere % 2) == 1){
			if ((pixelMap[*i][*j].R % 2) == 0){
				pixelMap[*i][*j].R ^= 1;
			}
		} else {
			if ((pixelMap[*i][*j].R % 2) == 1){
				pixelMap[*i][*j].R &= 0;
			}
		}
		caractere /= 2;
		if ((caractere % 2)){
			if ((pixelMap[*i][*j].G % 2) == 0){
				pixelMap[*i][*j].G ^= 1;
			}
		} else {
			if ((pixelMap[*i][*j].G % 2) == 1){
				pixelMap[*i][*j].G &= 0;
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

char descobreChar(pixel** pixelMap, int largura, int i, int j){
	int caractere = 0;
	for (int b = 0; b < 8; b += 2){
		caractere += (pixelMap[i][j].R % 2) * pow(2,b);
		caractere += (pixelMap[i][j].G % 2) * pow(2,b+1);
		++j;
		if (j == largura){
			++i;
			j = 0;
		}
	}
	return caractere;
}

void adicionaChar(char *mensagem, char c){
	char aux[1];
	aux[0] = c;
	realloc(mensagem, strlen(mensagem)+1);
	strcat(mensagem,aux);
	printf("%s\n", mensagem);
	return;
}
