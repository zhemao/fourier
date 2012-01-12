#include "fourier.h"
#include <stdio.h>
#include <math.h>

void filltdom(double complex * tdom, int n){
	int i;

	for(i=0; i<n; i++)
		tdom[i] = cos(i);
}

int main(void){
	int n = 100;
	double complex tdom[n], dfdom[n], ffdom[n];
	int i;

	filltdom(tdom, n);
	
	dft(dfdom, tdom, n);
	fft(ffdom, tdom, n);

	for(i=0; i<n; i++){
		printf("%f\t%f\t%f\n", cabs(tdom[i]), cabs(dfdom[i]) , cabs(ffdom[i]));
	}

	return 0;
}
