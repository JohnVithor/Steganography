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

void salvaChar(FILE *arqSaida, char caractere){
	// Escrevo o caractere no arquivo criado
	if (caractere != '\0'){
		fputc(caractere,arqSaida);
	}
}

void escondeChar(unsigned char caractere, pixel** pixelMap, int largura, int *i, int *j){
	// Inicio um laço que percorre 4 pixels
	for (int b = 0; b < 4; ++b){
		// Se o LSB do caractere atual for 1
		if (caractere & 1){
			// Se o LSB do Red no pixel indicado for 0
			if (!(pixelMap[*i][*j].R & 1)){
				// Troco seu valor para 1
				pixelMap[*i][*j].R ^= 1;
			}
		// Se o LSB do caractere atual for 0
		} else {
			// Se o LSB do Red no pixel indicado for 1
			if (pixelMap[*i][*j].R & 1){
				// Troco seu valor para 0
				pixelMap[*i][*j].R &= 254;
			}
		}
		// Movo os bits do caractere para a mudar o LSB
		caractere >>=1;
		// Se o LSB do caractere atual for 1
		if (caractere & 1){
			// Se o LSB do Green no pixel indicado for 0
			if (!(pixelMap[*i][*j].G & 1)){
				// Troco seu valor para 1
				pixelMap[*i][*j].G ^= 1;
			}
		// Se o LSB do caractere atual for 0
		} else {
			// Se o LSB do Green no pixel indicado for 1
			if (pixelMap[*i][*j].G & 1){
				// Troco seu valor para 0
				pixelMap[*i][*j].G &= 254;
			}
		}
		// Movo os bits do caractere para a mudar o LSB
		caractere >>=1;
		// Incremento o indice j para ir para o proximo pixel
		++(*j);
		// Se o indice j for igual a largura da imagem
		if (*j == largura){
			// incremento o indice i
			++(*i);
			// reinicio o indice j
			*j = 0;
		}
	}
	return;
}


unsigned char descobreChar(pixel** pixelMap, int largura, int *i, int *j){
	unsigned char caractere = 0;
	// Crio um laço que indica qual bit do caractere está sendo recuperado
	for (int b = 0; b < 8; b += 2){
		// Para cada campo de cor indicado pelos indices 'j' e 'i'
		// Recupero seu LSB e o desloco para a posição indicada pelo 'b' atual
		caractere += ((pixelMap[*i][*j].R & 1) << b);
		caractere += ((pixelMap[*i][*j].G & 1) << (b+1));
		// Incremento o indice j
		++(*j);
		// Se o indice j for igual a largura da imagem
		if (*j == largura){
			// incremento o indice i
			++(*i);
			// reinicio o indice j
			*j = 0;
		}
	}
	return caractere;
}