#include "fourier.h"
#include <stdlib.h>
#include <string.h>

void dft(double complex * fdom, double complex * tdom, int n){
	int memsize = n * sizeof(double complex);
	int i, j;

	memset(fdom, 0, memsize);

	for(i=0; i<n; i++){
		for(j=0; j < n; j++){
			fdom[i] += tdom[j] * cexp(EXPCONST * i * j / n);
		}
	}
}

static void fft_r(double complex * fdom, double complex * tdom, int n, int s){
	if(n == 1){
		fdom[0] = tdom[0];
	} else {
		int i, hn = n/2;
		double complex efdom[hn], ofdom[hn];

		fft_r(efdom, tdom, hn, 2 * s);
		fft_r(ofdom, tdom + s, hn, 2 * s);

		for(i=0; i<hn; i++){
			fdom[i] = efdom[i] + cexp(EXPCONST * i / n) * ofdom[i];
			fdom[i+hn] = efdom[i] - cexp(EXPCONST * i /n) * ofdom[i];
		}
	}
}

inline void fft(double complex * fdom, double complex * tdom, int n){
	fft_r(fdom, tdom, n, 1);
}

void ifft(double complex * tdom, double complex * fdom, int n){
	double complex fconj[n];
	int i;

	for(i=0; i<n; i++){
		fconj[i] = conj(fdom[i]);
	}

	fft(tdom, fconj, n);

	for(i=0; i<n; i++){
		tdom[i] = conj(tdom[i])/n;
	}
}

void convolve(double complex * r, double complex * a, 
              double complex *b, int n){
	
	double complex A[n], B[n], R[n];
	int i;

	fft(A, a, n);
	fft(B, b, n);
	
	for(i=0; i<n; i++){
		R[i] = A[i] * B[i];
	}

	ifft(r, R, n);
}
