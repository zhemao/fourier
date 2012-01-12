#include <complex.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define EXPCONST -2 * M_PI * I

void dft(double complex * fdom, double complex * tdom, int n);
void fft(double complex * fdom, double complex * tdom, int n);
