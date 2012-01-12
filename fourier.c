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
	if(n == 1){
		dft(fdom, tdom, n, s);
	} else {
		int i, hn = n/2, temp;

		fft(fdom, tdom, hn, 2 * s);
		fft(fdom + hn, tdom + s, hn, 2 * s);

		for(i=0; i<hn; i++){
			temp = fdom[i];
			fdom[i] = temp + cexp(EXPCONST * i / n) * fdom[i+hn];
			fdom[i+hn] = temp - cexp(EXPCONST * i /n) * fdom[i+hn];
		}
	}
}
