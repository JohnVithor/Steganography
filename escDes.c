#include <string.h>
#include <math.h>
#include "funcoes.h"
#include "structs.h"
////////////////////////////////////////////////////////////////////////////////////////////////////
//						Esconder/Descobrir Mensagens
////////////////////////////////////////////////////////////////////////////////////////////////////
void escondeChar(char caractere, pixel** pixelMap, int largura, int *i, int *j){
	for (int b = 0; b < 4; ++b){
		if ((caractere % 2) == 1){
			if ((pixelMap[*i][*j].R % 2) == 0){
				pixelMap[*i][*j].R ^= 1;
				//printf("escondi '1' em R %d %d\n",*i,*j);
			} else {
				//printf("temos um '1' em R %d %d\n",*i,*j);
			}
		} else {
			if ((pixelMap[*i][*j].R % 2) == 1){
				pixelMap[*i][*j].R &= 0;
				//printf("escondi '0' em R %d %d\n",*i,*j);
			} else {
				//printf("temos um '0' em R %d %d\n",*i,*j);
			}
		}
		caractere /= 2;
		if ((caractere % 2)){
			if ((pixelMap[*i][*j].G % 2) == 0){
				pixelMap[*i][*j].G ^= 1;
				//printf("escondi '1' em G %d %d\n",*i,*j);
			} else {
				//printf("temos um '1' em G %d %d\n",*i,*j);
			}
		} else {
			if ((pixelMap[*i][*j].G % 2) == 1){
				pixelMap[*i][*j].G &= 0;
				//printf("escondi '0' em G %d %d\n",*i,*j);
			} else {
				//printf("temos um '0' em G %d %d\n",*i,*j);
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
	//printf(" 'i'  for inicial %d\n", i);
	for (int b = 0; b < 8; b += 2){
		caractere += (pixelMap[i][j].R % 2) * pow(2,b);
		//printf("char %d\t\t", caractere);
		//printf("R %d, %d %d\t", (pixelMap[i][j].R % 2),i,j);
		//printf("pow %.2lf\n", pow(2,b));
		caractere += (pixelMap[i][j].G % 2) * pow(2,b+1);
		//printf("char %d\t\t", caractere);
		//printf("G %d, %d %d\t", (pixelMap[i][j].G % 2),i,j);
		//printf("pow %.2lf\n", pow(2,b+1));
		++j;
		
		if (j == largura){
			++i;
			j = 0;
		}
		
		//printf(" 'i'  for atual %d\n", i);
	}
	//printf("caractere %c = %d\n",caractere,caractere );
	//printf(" 'i' atual %d\n", i);
	return caractere;
}

int escondeMsgPPM(char *mensagem, int tamanhoDaMsg, imgPPM *imagemLida){
	int i = 0, j = 0;
	if (tamanhoDaMsg * 8 > imagemLida->altura * imagemLida->largura * 3){
		return 1;
	}
	for (int c = 0; c < tamanhoDaMsg; ++c){
		escondeChar(mensagem[c], imagemLida->pixelMap, imagemLida->largura, &i, &j);
		//printf("%c escondido - ultimo i: %d j: %d\n", mensagem[c], i, j);
	}

	char fim = '\0';
	escondeChar(fim, imagemLida->pixelMap, imagemLida->largura, &i, &j);

	return 0;
}

int descobreMsgPPM(char *mensagem, imgPPM *imagemLida){
	int i = 0, j = 0, k = 0;
	char caractere[] = "";
	//printf(" 'i' fora %d\n", i);
	do{
		caractere[k] = descobreChar(imagemLida->pixelMap, imagemLida->largura, i, j);
		j += 4;
		if (j >= imagemLida->largura){
		 	++i;
		 } 
		strcat(mensagem, caractere);
		//printf(" 'i' fora %d\n", i);
		
		if (i == imagemLida->altura-1 && j == imagemLida->largura){
			return 1;
		}

		++k;
		//printf("k atual = %d\n",k);
	}while(caractere[k-1] != '\0');
	return 0;
}
