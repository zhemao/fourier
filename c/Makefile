CC=gcc
CFLAGS=-Wall -g -DFFT_PTHREAD -pthread
ALL=fftstream dftstream ftest iftest fftwstream benchmark

all: $(ALL)

benchmark: benchmark.c fourier.o
	$(CC) $(CFLAGS) $(LDFLAGS) fourier.o benchmark.c -lm -o benchmark

fftwstream: fftwstream.c
	$(CC) $(CFLAGS) $(LDFLAGS) fftwstream.c -lm -lfftw3 -o fftwstream

fftstream: fftstream.c fourier.o
	$(CC) $(CFLAGS) $(LDFLAGS) fourier.o fftstream.c -lm -o fftstream

dftstream: dftstream.c fourier.o
	$(CC) $(CFLAGS) $(LDFLAGS) fourier.o dftstream.c -lm -o dftstream

ftest: ftest.c fourier.o
	$(CC) $(CFLAGS) $(LDFLAGS) fourier.o ftest.c -lm -o ftest

iftest: iftest.c fourier.o
	$(CC) $(CFLAGS) $(LDFLAGS) fourier.o iftest.c -lm -o iftest

fourier.o: fourier.h fourier.c
	$(CC) $(CFLAGS) -c fourier.c 

clean: 
	rm -f $(ALL) *.o
