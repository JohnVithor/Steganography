PROG = steg
CC = gcc
CFLAGS = -Wall -ansi -pedantic -std=c11 -g
OBJS = abrirSalvar.o steg.o escDes.o

$(PROG): $(OBJS)
	$(CC) -o $(PROG) $(OBJS) -lm

abrirSalvar.o: abrirSalvar.c
	$(CC) $(CFLAGS) -c abrirSalvar.c
escDes.o: escDes.c
	$(CC) $(CFLAGS) -c escDes.c
steg.o: steg.c funcoes.h structs.h
	$(CC) $(CFLAGS) -c steg.c
	
clean:
	rm -f core $(PROG) $(OBJS)
