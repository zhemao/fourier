#include "fourier.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	if (argc < 2) {
		printf("Must specify size of input array\n");
		exit(EXIT_FAILURE);
	}

	int n = atoi(argv[1]);
	int i = 0;
	double x;
	double complex tdom[n], fdom[n];

	while (i<n && scanf("%lf", &x) > 0) {
		tdom[i] = x;
		i++;
	}

	dft(fdom, tdom, n);

	for (i=0; i<n; i++) {
		printf("%f\n", cabs(fdom[i]));
	}

	return 0;
}
