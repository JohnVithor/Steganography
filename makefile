PROG = steg
CC = gcc
CFLAGS = -Wall -ansi -pedantic -std=c11
OBJS = steg.o PPM.o BMP.o mensagem.o

$(PROG): $(OBJS)
	$(CC) -o $(PROG) $(OBJS) -lm

steg.o: steg.c funcoes.h structs.h
	$(CC) $(CFLAGS) -c steg.c

PPM.o: PPM.c
	$(CC) $(CFLAGS) -c PPM.c

BMP.o: BMP.c
	$(CC) $(CFLAGS) -c BMP.c

mensagem.o: mensagem.c
	$(CC) $(CFLAGS) -c mensagem.c

clean:
	rm -f core $(PROG) $(OBJS) Saida.ppm Saida.bmp Saida.txt

runPPM:
	./steg -e -i segredo.txt -f ppm imd.ppm

runBMP:
	./steg -e -i segredo.txt -f bmp imd.bmp