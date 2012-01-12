#include "fourier.h"
#include <stdio.h>
#include <math.h>

void filltdom(double complex * tdom, int n){
	int i; 
	double t;

	for(i=0; i<n; i++){
		t = 20.0 / n - 10.0;
		if(t == 0) tdom[i] = 1;
		else tdom[i] = sin(t)/t;
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
	int n = 1000;
	double complex tdom[n], dfdom[n], ffdom[n], error[n];
	int i;

	filltdom(tdom, n);
	
	dft(dfdom, tdom, n, 1);
	fft(ffdom, tdom, n, 1);

	ar_difference(error, dfdom, ffdom, n);

	for(i=0; i<n; i++){
		printf("%f\t%f\t%f\n", cabs(tdom[i]), cabs(dfdom[i]), cabs(ffdom[i]));
	}

	return 0;
}
