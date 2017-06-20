#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <ctype.h>
#include <unistd.h>
#include <getopt.h>

#include "funcoes.h"
#include "structs.h"

int main(int argc, char** argv){

	int e_flag = 0, d_flag = 0, s_flag = 0;
	char *arquivoTexto = NULL, *formato = NULL, *imagem = NULL;
	int c;
	opterr = 0;

	while ((c = getopt (argc, argv, "edi:f:o:s")) != -1){
	 	switch(c){
			case 'e':
				if (d_flag == 1){
					fprintf(stderr, "Erro: Não é permitido o uso de '-e' e '-d' no mesmo comando\n");
					return 1;
				} else {
					e_flag = 1;
				}
				break;
			case 'd':
				if (e_flag == 1){
					fprintf(stderr, "Erro: Não é permitido o uso de '-e' e '-d' no mesmo comando\n");
					return 1;
				} else {
					d_flag = 1;
				}
				break;
			case 'i':
				if (d_flag == 1){
					fprintf(stderr, "Erro: Não é permitido o uso de '-i' e '-d' no mesmo comando\n");
					return 1;
				} else {
					// arquivoTexto recebe o nome do arquivo onde está a mensagem
					arquivoTexto = optarg;
				}
				break;
			case 'o':
				if (e_flag == 1){
					fprintf(stderr, "Erro: Não é permitido o uso de '-o' e '-e' no mesmo comando\n");
					return 1;
				} else if (s_flag == 1){
					fprintf(stderr, "Erro: Não é permitido o uso de '-o' e '-s' no mesmo comando\n");
					return 1;
				} else {
					// arquivoTexto recebe o nome do arquivo onde está a mensagem
					arquivoTexto = optarg;
				}
				break;
			case 's':
				if (e_flag == 1){
					fprintf(stderr, "Erro: Não é permitido o uso de '-s' e '-e' no mesmo comando\n");
					return 1;
				} else {
					s_flag = 1;
				}
				break;
			case 'f':
					formato = optarg;
					break;
			case '?':
				if (optopt == 'i' || optopt == 'o' || optopt == 'f'){
					fprintf(stderr, "Erro: '-%c' necessita de um argumento.\n", optopt);
					return 1;
				} else if (isprint(optopt)){
					fprintf(stderr, "Erro: '-%c' inválido.\n", optopt);
					return 1;
				} else {
					fprintf(stderr, "Erro: '\\x%x' caractere inválido\n", optopt);
					return 1;
				}	
			default:
				abort();
		}
	}

	if (optind < argc){
		// imagem recebe o nome do arquivo de imagem
		imagem = argv[optind];
	}

	if (e_flag){// Caso a opção de 'Encode' seja selecionada
		printf("Codificando mensagem...\n");
		char *msgLida;
		unsigned long tamanhoDaMsg;
		// Leio o arquivo da mensagem e guardo seu conteudo na string msgLida
		msgLida = abreMsg(arquivoTexto, &tamanhoDaMsg);
		// Caso o formato seja ppm
		if (strcmp(formato, "ppm") == 0){
			imgPPM imagemLida;
			// Leio a imagem e a armazeno na struct 'imagemLida'
			abreImgPPM(imagem, &imagemLida);
			// Inicio o processo de esconder a mensagem
			if (escondeMsgPPM(msgLida, tamanhoDaMsg, &imagemLida)){
				fprintf(stderr, "Imagem muito pequena para esconder essa mensagem.\n");
				return 1;
			}
			salvaImgPPM("Saida.ppm", &imagemLida);
		}
		// Caso o formato seja bmp
		if (strcmp(formato, "bmp") == 0){
			imgBMP imagemLida;
			// Leio a imagem e a armazeno na struct 'imagemLida'
			abreImgBMP(imagem, &imagemLida);
			// Inicio o processo de esconder a mensagem
			if (escondeMsgBMP(msgLida, tamanhoDaMsg, &imagemLida)){
				fprintf(stderr, "Imagem muito pequena para esconder essa mensagem.\n");
				return 1;
			}
			salvaImgBMP("Saida.bmp", &imagemLida);
		}
		printf("Codificação concluída!\n");
		printf("Mensagem escondida na imagem: Saida.%s\n",formato);
	}

	if (d_flag){ // Caso a opção de 'Decode' seja selecionada
		printf("Decodificando mensagem...\n");
		char saida;
		if (s_flag){
			saida = 's';
		} else {
			saida = 'o';
		}
		// Caso o formato seja ppm
		if (strcmp(formato, "ppm") == 0){
			imgPPM imagemLida;
			// Leio a imagem e a armazeno na struct 'imagemLida'
			abreImgPPM(imagem, &imagemLida);
			// Inicio o processo de recuperar a mensagem escondida
			if (descobreMsgPPM(saida, &imagemLida, arquivoTexto)){
				fprintf(stderr, "Não foi encontrado um fim de mensagem.\n");
				return 1;
			}
		}
		// Caso o formato seja bmp
		if (strcmp(formato, "bmp") == 0){
			imgBMP imagemLida;
			// Leio a imagem e a armazeno na struct 'imagemLida'
			abreImgBMP(imagem, &imagemLida);
			// Inicio o processo de recuperar a mensagem escondida
			if (descobreMsgBMP(saida, &imagemLida, arquivoTexto)){
				fprintf(stderr, "Não foi encontrado um fim de mensagem.\n");
				return 1;
			}
		}
	}
	return 0;
}