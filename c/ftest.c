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
	int i;

	if (argc > 1)
		n = atoi(argv[1]);
	else
		n = 1024;

	double complex tdom[n], dfdom[n], ffdom[n]; 
	
	filltdom(tdom, n);
	
	dft(dfdom, tdom, n);
	fft(ffdom, tdom, n);

	for(i = 0; i < n; i++){
		printf("%f\t%f\n", cabs(dfdom[i]), cabs(ffdom[i]));
	}

	return 0;
}
