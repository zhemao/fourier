#include "fourier.h"
#include <stdlib.h>

#ifdef FFT_PTHREAD
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

struct fft_data {
	double complex *fdom;
	double complex *tdom;
	int n;
	int s;
	int nthreads;
};

#endif

void dft(double complex *fdom, double complex *tdom, int n)
{
	int i, j;

	for (i = 0; i < n; i++) {
		fdom[i] = 0;

		for (j=0; j < n; j++) {
			fdom[i] += tdom[j] * cexp(EXPCONST * i * j / n);
		}
	}
}

static void fft_r(double complex *fdom, double complex *tdom, int n, int s)
{
	if (n == 1) {
		fdom[0] = tdom[0];
	} else {
		int i, hn = n/2;

		fft_r(fdom, tdom, hn, 2 * s);
		fft_r(fdom+hn, tdom + s, hn, 2 * s);

		for (i = 0; i < hn; i++) {
			double complex odd = fdom[i+hn];
			fdom[i+hn] = fdom[i] - cexp(EXPCONST * i /n) * odd;
			fdom[i] = fdom[i] + cexp(EXPCONST * i / n) * odd;
		}
	}
}

#ifdef FFT_PTHREAD

static void* fft_par(void *data);

static int fft_create_thread(pthread_t *thread, struct fft_data *data)
{
	pthread_attr_t attr;
	int rc;

	rc = pthread_attr_init(&attr);

	if (rc < 0)
		return -1;
	
	rc = pthread_create(thread, &attr, fft_par, (void*) data);

	pthread_attr_destroy(&attr);

	if (rc < 0)
		return -1;

	return 0;
}

static void* fft_par(void *data)
{
	struct fft_data *olddata;
	struct fft_data newdata;
	int i, n, hn, s, nthreads, retval;
	double complex *fdom;
	pthread_t thread;

	olddata = (struct fft_data *) data;
	
	nthreads = olddata->nthreads;
	n = olddata->n;
	hn = olddata->n / 2;
	s = olddata->s;
	fdom = olddata->fdom;

	if (n == 1) {
		fdom[0] = olddata->tdom[0];
		return NULL;
	}

	if (nthreads == 1) {
		fft_r(olddata->fdom, olddata->tdom, n, s);
		return NULL;
	}

	
	newdata.fdom = olddata->fdom + hn;
	newdata.tdom = olddata->tdom + s;
	newdata.n = hn;
	newdata.s = 2 * s;
	newdata.nthreads = nthreads / 2;

	olddata->n = hn;
	olddata->s = 2 * s;
	olddata->nthreads = nthreads / 2;

	retval = fft_create_thread(&thread, &newdata);

	fft_par((void*) olddata);

	if (retval == 0)
		retval = pthread_join(thread, NULL);
	
	if (retval != 0)
		/* if pthread_create or pthread_join exited unsuccessfully,
		 * just do the second half sequentially */
		fft_par((void*) &newdata);
	
	for (i = 0; i < hn; i++) {
		double complex odd = fdom[i+hn];
		fdom[i+hn] = fdom[i] - cexp(EXPCONST * i / n) * odd;
		fdom[i] = fdom[i] + cexp(EXPCONST * i / n) * odd;
	}

	return NULL;
}

inline void fft(double complex *fdom, double complex *tdom, int n)
{
	struct fft_data data;
	
	data.fdom = fdom;
	data.tdom = tdom;
	data.n = n;
	data.s = 1;
	data.nthreads = sysconf(_SC_NPROCESSORS_ONLN);
	
	fft_par((void*) &data);
}

#else

inline void fft(double complex *fdom, double complex *tdom, int n)
{
	fft_r(fdom, tdom, n, 1);
}

#endif

void ifft(double complex *tdom, double complex *fdom, int n)
{
	double complex fconj[n];
	int i;

	for (i = 0; i < n; i++) {
		fconj[i] = conj(fdom[i]);
	}

	fft(tdom, fconj, n);

	for (i = 0; i < n; i++) {
		tdom[i] = conj(tdom[i])/n;
	}
}

void convolve(double complex *r, double complex *a, 
              double complex *b, int n){
	
	double complex A[n], B[n], R[n];
	int i;

	fft(A, a, n);
	fft(B, b, n);
	
	for (i = 0; i < n; i++) {
		R[i] = A[i] * B[i];
	}

	ifft(r, R, n);
}
