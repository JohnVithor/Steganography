	Esteganografia		Projeto ITP/PTP		3ª Unidade

Aluno: João Vítor Venceslau Coelho	
Professor: Silvio Costa Sampaio
Link no Github: https://github.com/JohnVithor/Steganography
20/06/2017

Objetivo: Aplicar os conhecimentos ministrados em sala de aula para o desenvolvimento de um programa capaz de esconder mensagens em imagens através da estaganografia, e capaz de recuperar as mensagens escondidas pelo próprio programa.

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

	
Como compilar o programa:
	Utilização do comando 'make' no terminal do Linux;

Como executar o programa:
	Para codificar uma mensagem em uma imagem:
		./steg -e -i <imput-file> -f <format> <image>

	-e indica que o programa deve rodar em modo de codificador (encoder);
	-i <input-file> indica o arquivo de entrada (input) a ser codificado na imagem;
	-f <format> indica o formato da imagem a ser usada como hospedeira para a mensagem. Os valores possíveis para <format> são: bmp ou ppm;
	<image> imagem a ser usada como hospedeira para a mensagem;

	Para decodificar uma mensagem em uma imagem:
		./steg -d -o <output-file> -f <format> <image>
		./steg -d -s -f <format> <image>

	-d indica que o programa deve rodar em modo de decodificador (decoder);
	-o <output-file> indica o arquivo de saída (output) para onde será gravada a mensagem decodificada;
	-s indica que a mensagem decodificada deve ser mostrada na saída padrão (stdout). O uso desta opção invalida o uso da opção -o <output-file>;
	-f <format> indica o formato da imagem a ser usada como hospedeira para a mensagem. Os valores possíveis para <format> são: bmp ou ppm;
	<image> imagem hospedeira da mensagem (.ppm, .bmp);

Referências:
http://www.cplusplus.com/reference/
https://en.wikipedia.org/wiki/BMP_file_format
http://disciplinas.ist.utl.pt/~leic-cg.daemon/textos/livro/Formatos%20de%20Imagem.pdf
https://www.gnu.org/software/libc/manual/html_node/Getopt.html
