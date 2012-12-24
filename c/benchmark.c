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

void ar_difference(double complex *diff, 
		   double complex *ara, double complex *arb, int n)
{
	int i;
	for(i = 0; i < n; i++){
		diff[i] = ara[i] - arb[i];
	}
}

int main(int argc, char *argv[])
{
	int n;

	if (argc > 1)
		n = atoi(argv[1]);
	else
		n = 1024;

	double complex tdom[n], fdom[n];
	
	filltdom(tdom, n);
	
	fft(fdom, tdom, n);

	return 0;
}
