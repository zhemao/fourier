#include "fourier.h"
#include <stdio.h>
#include <math.h>

void filltdom(double complex * tdom, int n){
	int i; 

	for(i=0; i<n; i++){
		tdom[i] = cos(i);
	}
}

void ar_difference(double complex * diff, 
					double complex * ara, double complex * arb, int n){
	int i;
	for(i=0; i<n; i++){
		diff[i] = ara[i] - arb[i];
	}
}

int main(void){
	int n = 1024;
	double complex tdom[n], dfdom[n], ffdom[n], error[n];
	int i;

	filltdom(tdom, n);
	
	dft(dfdom, tdom, n);
	fft(ffdom, tdom, n);

	ar_difference(error, dfdom, ffdom, n);

	for(i=0; i<n; i++){
		printf("%f\t%f\n", cabs(dfdom[i]), cabs(ffdom[i]));
	}

	return 0;
}
