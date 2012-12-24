#include "fourier.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void filltdom(double complex * tdom, int n)
{
	int i; 

	for (i = 0; i < n; i++) {
		tdom[i] = cos(i);
	}
}

int main(int argc, char *argv[])
{
	int i, size, times;

	if (argc > 1)
		size = atoi(argv[1]);
	else
		size = 1024;
	
	if (argc > 2)
		times = atoi(argv[2]);
	else
		times = 1;

	double complex tdom[size], fdom[size];
	
	filltdom(tdom, size);
	
	for (i = 0; i < times; i++)
		fft(fdom, tdom, size);

	return 0;
}
