#include "funcoes.h"
#include "structs.h"
////////////////////////////////////////////////////////////////////////////////////////////////////
//						Esconder/Descobrir Mensagens
////////////////////////////////////////////////////////////////////////////////////////////////////

void escondeMsg(char *mensagem, int tamanhoDaMsg, imgPPM *imagemLida){
	char fim = '\0';
	char bits[8] = {1,2,4,8,16,32,64,128};
	int i = 0, j = 0;
	for (int c = 0; c < tamanhoDaMsg; ++i){
		if (mensagem[c] & bits[0]){
			if (imagemLida->pixelMap[i][j].R | bits[0]){
				imagemLida->pixelMap[i][j].R |= bits[0];
			}
		if (mensagem[c] & bits[1]){
			if (imagemLida->pixelMap[i][j].G | bits[0]){
				imagemLida->pixelMap[i][j].G |= bits[0];
			}	
		}
		if (mensagem[c] & bits[2]){
			if (imagemLida->pixelMap[i][j].B | bits[0]){
				imagemLida->pixelMap[i][j].B |= bits[0];
			}	
		}
		if (mensagem[c] & bits[3]){
			if (imagemLida->pixelMap[i][j].R | bits[0]){
				imagemLida->pixelMap[i][j].R |= bits[0];
			}	
		}
		if (mensagem[c] & bits[4]){
			if (imagemLida->pixelMap[i][j].G | bits[0]){
				imagemLida->pixelMap[i][j].G |= bits[0];
			}	
		}
		if (mensagem[c] & bits[5]){
			if (imagemLida->pixelMap[i][j].B | bits[0]){
				imagemLida->pixelMap[i][j].B |= bits[0];
			}	
		}
		if (mensagem[c] & bits[6]){
			if (imagemLida->pixelMap[i][j].R | bits[0]){
				imagemLida->pixelMap[i][j].R |= bits[0];
			}	
		}
		if (mensagem[c] & bits[7]){
			if (imagemLida->pixelMap[i][j].G | bits[0]){
				imagemLida->pixelMap[i][j].G |= bits[0];
			}	
		}
	}
	
	return;
}

char* descobreMsg(imgPPM *imagemLida){
	char *mensagem;

	return mensagem;
}