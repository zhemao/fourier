#include <stdio.h>
#include <stdlib.h>
#include <fftw3.h>
#include <math.h>

int main(int argc, char *argv[]){
	if(argc < 2){
		printf("Must specify size of input array\n");
		exit(EXIT_FAILURE);
	}

	int n = atoi(argv[1]);
	int i = 0;
	double x;
	fftw_complex *in, *out;
	fftw_plan p;

	in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * n);
	out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * n);

	while(i<n && scanf("%lf", &x) > 0){
		in[i][0] = x;
		in[i][1] = 0;
		i++;
	}

	p = fftw_plan_dft_1d(n, in, out, FFTW_FORWARD, FFTW_ESTIMATE);

	fftw_execute(p);

	for(i=0; i<n; i++){
		x = sqrt(out[i][0] * out[i][0] + out[i][1] * out[i][1]);
		printf("%f\n", x);
	}

	fftw_destroy_plan(p);
	fftw_free(in);
	fftw_free(out);

	return 0;
}
