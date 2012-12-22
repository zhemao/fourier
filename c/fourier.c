#include "fourier.h"
#include <stdlib.h>

#ifdef FFT_PTHREAD
#include <pthread.h>
#include <unistd.h>

struct fft_thread {
	pthread_t thread;
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

static void* fft_par(void *data)
{
	struct fft_thread *oldthread;
	struct fft_thread newthread;
	int i, n, hn, s, nthreads;
	double complex *fdom;

	oldthread = (struct fft_thread *) data;
	
	nthreads = oldthread->nthreads;
	n = oldthread->n;
	hn = oldthread->n / 2;
	s = oldthread->s;
	fdom = oldthread->fdom;

	if (n == 1) {
		fdom[0] = oldthread->tdom[0];
		return NULL;
	}

	if (nthreads == 1) {
		fft_r(oldthread->fdom, oldthread->tdom, n, s);
		return NULL;
	}

	
	newthread.fdom = oldthread->fdom + hn;
	newthread.tdom = oldthread->tdom + s;
	newthread.n = hn;
	newthread.s = 2 * s;
	newthread.nthreads = nthreads / 2;

	oldthread->n = hn;
	oldthread->s = 2 * s;
	oldthread->nthreads = nthreads / 2;

	pthread_create(&newthread.thread, NULL, fft_par, (void*) &newthread);
	fft_par((void*) oldthread);
	
	pthread_join(newthread.thread, NULL);

	for (i = 0; i < hn; i++) {
		double complex odd = fdom[i+hn];
		fdom[i+hn] = fdom[i] - cexp(EXPCONST * i / n) * odd;
		fdom[i] = fdom[i] + cexp(EXPCONST * i / n) * odd;
	}

	return NULL;
}

inline void fft(double complex *fdom, double complex *tdom, int n)
{
	struct fft_thread thread;
	
	thread.fdom = fdom;
	thread.tdom = tdom;
	thread.n = n;
	thread.s = 1;
	thread.nthreads = sysconf(_SC_NPROCESSORS_ONLN);

	fft_par((void*) &thread);
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
