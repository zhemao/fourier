#include "fourier.h"
#include <stdio.h>
#include <math.h>

void filltdom(double complex * tdom, int n){
	int i; 

	for(i=0; i<n; i++){
		tdom[i] = cos(i) + cos(2*i);
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
	double complex tdom[n], fdom[n], tdom2[n], error[n];
	int i;

	filltdom(tdom, n);
	
	fft(fdom, tdom, n, 1);
	ifft(tdom2, fdom, n);

	ar_difference(error, tdom, tdom2, n);

	for(i=0; i<n; i++){
		printf("%f\t%f\t%f\n", cabs(tdom[i]), cabs(tdom2[i]), cabs(error[i]));
	}

	return 0;
}
