#include "funcoes.h"
#include "structs.h"
////////////////////////////////////////////////////////////////////////////////////////////////////
//						Esconder/Descobrir Mensagens
////////////////////////////////////////////////////////////////////////////////////////////////////

int escondeMsg(char *mensagem, int tamanhoDaMsg, imgPPM *imagemLida){
	int i = 0, j = 0;
	if (tamanhoDaMsg*8 > imagemLida->altura * imagemLida->largura * 3){
		return 1;
	}
	for (int c = 0; c < tamanhoDaMsg-1; ++c){
		for (int b = 0; b < 8; ++b){
			if ((mensagem[c] % 2)){
				if (!(imagemLida->pixelMap[i][j].R % 2)){
					imagemLida->pixelMap[i][j].R ^= 1;
				}
			} else {
				if ((imagemLida->pixelMap[i][j].R % 2)){
					imagemLida->pixelMap[i][j].R ^= 0;
				}
			}
			mensagem[c] /= 2;
			if ((mensagem[c] % 2)){
				if (!(imagemLida->pixelMap[i][j].G % 2)){
					imagemLida->pixelMap[i][j].G ^= 1;
				}
			} else {
				if ((imagemLida->pixelMap[i][j].G % 2)){
					imagemLida->pixelMap[i][j].G ^= 0;
				}
			}
			mensagem[c] /= 2;
			++j;
			if (j == imagemLida->largura){
				i++;
				j = 0;
			}
		}
	}
	return 0;
}
