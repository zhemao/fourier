CC=c99
OPTS=-Wall
LDFLAGS=-lm

ftest: ftest.c fourier.o
	$(CC) $(OPTS) fourier.o ftest.c $(LDFLAGS) -o ftest

fourier.o: fourier.h fourier.c
	$(CC) $(OPTS) -c fourier.c 

clean: 
	rm -f ftest *.o
