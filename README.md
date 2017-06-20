# Esteganografia

O que foi feito:

	Criadas structs para armazenar os dados (cabeçalho e matriz de pixels) de cada tipo de imagem suportada (PPM e BMP);
	Ler as imagens e armazenar seus dados nas devidas structs;
	Salvar os dados de uma struct em um arquivo de imagem;
	Ler um arquivo de texto qualquer e armazenar seu conteúdo numa string;
	Codificar uma mensagem em uma imagem utilizando a técnica do LSB;
	Recuperar uma mensagem de uma imagem onde foi utilizada a técnica do LSB;
	Utilização da função getopt() para o processamento das opções do programa;
	Criação do Makefile para facilitar a compilação do projeto;
	
O que não foi feito:

	Suporte para outros formatos de imagem;
	Utilização de outras técnicas de esteganografia;

O que seria feito diferente:

	Tentaria utilizar uma única função para codificar a mensagem em diferentes formatos;
	Assim como uma única função para decodificar a mensagem escondida;
	
Como compilar o projeto:

	Utilização do comando 'make' no terminal do Linux;
