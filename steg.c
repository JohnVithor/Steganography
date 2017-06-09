#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "funcoes.h"
#include "structs.h"

int main(int argc, char** argv){
	if(argc != 7){
		printf("./steg -e -i <input-file> -f <format> <image>\n");
		printf("./steg -d -o <output-file> -f <format> <image>\n");
		return 1;
	}

	char *msgLida;
	unsigned long tamanhoDaMsg;
	
	msgLida = abreMsg(argv[3], &tamanhoDaMsg);

if (strcmp(argv[5], "ppm") == 0){
	imgPPM imagemLida;
	abreImgPPM(argv[6], &imagemLida);
	if (escondeMsgPPM(msgLida, tamanhoDaMsg, &imagemLida)){
		printf("Imagem muito pequena para esconder essa mensagem.\n");
	}

	salvaImgPPM("Saida.ppm", &imagemLida);
	char *msgDesc;
	msgDesc = calloc(0 , sizeof(char));

	if (descobreMsgPPM(msgDesc, &imagemLida)){
		printf("Não foi encontrado um fim de mensagem, muito provavel que não exista mensagem escondida nesta imagem\n");
	}
	salvaMsg("Saida.txt",msgDesc);
}
if (strcmp(argv[5], "bmp") == 0){
	imgBMP imagemLida;
	abreImgBMP(argv[6], &imagemLida);
	if (escondeMsgBMP(msgLida, tamanhoDaMsg, &imagemLida)){
		printf("Imagem muito pequena para esconder essa mensagem.\n");
	}

	salvaImgBMP("Saida.bmp", &imagemLida);
	char msgDesc[] = "";

	if (descobreMsgBMP(msgDesc, &imagemLida)){
		printf("Não foi encontrado um fim de mensagem, muito provavel que não exista mensagem escondida nesta imagem\n");
	}
	salvaMsg("Saida.txt",msgDesc);
}
	free(msgLida);
	return 0;
}