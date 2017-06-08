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
	salvaMsg("Saida.txt",msgLida);

if (strcmp(argv[5], "ppm") == 0){
	imgPPM imagemLida;
	abreImgPPM(argv[6], &imagemLida);
	salvaImgPPM("Saida.ppm", &imagemLida);
}
if (strcmp(argv[5], "bmp") == 0){
	imgBMP imagemLida;
	abreImgBMP(argv[6], &imagemLida);
	salvaImgBMP("Saida.bmp", &imagemLida);
}

	free(msgLida);
	return 0;
}