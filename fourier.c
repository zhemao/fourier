#include "fourier.h"
#include <stdlib.h>
#include <string.h>



void dft(double complex * fdom, double complex * tdom, int n){
	int memsize = n * sizeof(double complex);
	int i, j;

	memset(fdom, 0, memsize);

	for(i=0; i<n; i++){
		for(j=0; j<n; j++){
			fdom[i] += tdom[j] * cexp(EXPCONST * i * j / n);
		}
	}

}

void fft(double complex * fdom, double complex * tdom, int n){
	if(n < 5){
		dft(fdom, tdom, n);
	} else {

		int i;
		int hn = n/2;
		double complex ofdom[hn], otdom[hn], efdom[hn], etdom[hn];

		for(i=0; i<hn; i++){
			etdom[i] = tdom[2*i];
			otdom[i] = tdom[2*i+1];
		}

		fft(efdom, etdom, hn);
		fft(ofdom, otdom, hn);

		for(i=0; i<hn; i++)
			fdom[i] = efdom[i] + cexp(EXPCONST * i / n) * ofdom[i];
	
		for(i=hn; i<n; i++)
			fdom[i] = efdom[i-hn] - cexp(EXPCONST * (i-hn) / n) * ofdom[i-hn];
	}
}
