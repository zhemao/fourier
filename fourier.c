#include "fourier.h"
#include <stdlib.h>
#include <string.h>

void dft(double complex * fdom, double complex * tdom, int n, int s){
	int memsize = n * sizeof(double complex);
	int i, j;

	memset(fdom, 0, memsize);

	for(i=0; i<n; i++){
		for(j=0; j < n; j++){
			fdom[i] += tdom[j*s] * cexp(EXPCONST * i * j / n);
		}
	}

}

void fft(double complex * fdom, double complex * tdom, int n, int s){
	if(n <= 5){
		dft(fdom, tdom, n, s);
	} else {
		int i, hn = n/2;
		double complex efdom[hn], ofdom[hn];

		fft(efdom, tdom, hn, 2 * s);
		fft(ofdom, tdom + s, hn, 2 * s);

		for(i=0; i<hn; i++){
			fdom[i] = efdom[i] + cexp(EXPCONST * i / n) * ofdom[i];
			fdom[i+hn] = efdom[i] - cexp(EXPCONST * i /n) * ofdom[i];
		}

		if(2*hn < n) fdom[2*hn] = efdom[0] + ofdom[0];
	}
}
