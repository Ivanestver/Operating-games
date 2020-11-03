#include "pch.h"
#include "Header.h"
#include <utility>
#include <limits.h>
#include <minwindef.h>

double **U;
unsigned int **R;
unsigned int **W;
unsigned int *V;
double **v;
double y;
double q = 0;
long direction, type;
long s = 1; // the step
long fs = 0;
long n = 0;
long m = 0;

double D;

// For receiving the information
void Constructor(unsigned int *Vl, 
				unsigned int k, 
				unsigned int i, 
				unsigned int **Rl,
				unsigned int **Wl) {
	V = Vl;
	direction = i;
	type = k;
	R = Rl;
	W = Wl;

	// Fill U
	U = new double *[direction];
	for (unsigned int j = 0; j < direction; j++) {
		U[j] = new double[type];
		for (unsigned int a = 0; a < type; a++) {
			U[j][a] = 0;
		}
	}

	for (unsigned int j = 0; j < type; j++) {
		U[0][j] = V[j];
	}

	// Fill R
	R = new unsigned int*[direction];
	for (unsigned int j = 0; j < direction; j++) {
		R[j] = new unsigned int[i];
		for (unsigned int a = 0; a < type; a++) {
			R[j][a] = 0;
		}
	}

	for (unsigned int j = 0; j < k; j++) {
		U[0][j] = V[j];
	}

	// Calculate D
	unsigned int _D = 1;
	for (unsigned int i = 0; i < k; i++) {
		_D += V[i] * V[i];
	}

	D = sqrt(_D);
}

// Sometimes I will add links to formulas from the presentation. So if you cannot realize what a formula it is, 
// you can look into the presentation 

void Do() {
	while (q > 0.01 || q != 0) {
		// Find G(u) on k direction. (2.10)
		unsigned long ks = 1, b = 0;
		// b is the sum of means we have on the direction i  
		for (unsigned long i = 0; i < direction; i++) {
			b -= U[i][0];
		}
		b += V[0];

		// Find the minimal G 
		unsigned long G = b;
		for (unsigned long k = 1; k < type; k++) {
			b = 0;
			for (unsigned long i = 0; i < direction; i++) {
				b -= U[i][k];
			}
			b += V[k];
			if (G > b) {
				G = b;
				ks = k;
			}
		}

		// The next couple of loops we are calculating v-vector (2.14)
		b = 0;
		// Here and the next loop we are calculating f(U(s))
		for (unsigned long k = 0; k < type; k++) {
			b += R[0][k] * U[0][k];
		}

		long f = b, is = 1;

		for (long i = 1; i < direction; i++) {
			b = 0;
			for (long k = 0; k < type; k++) {
				b += R[i][k] * U[i][k];
			}
			if (f > b) {
				f = b;
				is = i;
			}
		}

		long y = D / s; // The step of the method. D was calculated in the Constructor method before
		long vs = 0; // v-vector on the s step

		// Now we calculate the v-vector itself
		for (long i = 0; i < direction; i++) {
			for (long k = 0; k < type; k++) {
				if (G >= 0) {
					if (i != is) {
						W[i][k] = 0;
					}
					else {
						W[i][k] = R[i][k];
					}
				}
				else {
					if (k != ks) {
						W[i][k] = 0;
					}
					else {
						W[i][k] = -1;
					}
				}
				vs += W[i][k] * W[i][k];
			}
		}

		vs = sqrt(vs); // the normal of v-vector

		// So now we are going to calculate the U (2.11) using P-function 
		for (long i = 0; i < direction; i++) {
			for (long k = 0; k < type; k++) {
				double x = U[i][k] + y * W[i][k] / vs;

				if (x < 0) {
					U[i][k] = 0;
				}
				else {
					if (x > V[k]) {
						U[i][k] = V[k];
					}
					else {
						U[i][k] = x;
					}
				}
			}
		}

		s++;
		q = max((double)fs, (double)f) - (double)fs;
		fs = max(fs, f);
	}

	/*long c2 = 0;
	for (long k = 0; k < type; k++) {
		long c = 1;
		for (long i = 0; i < direction; i++) {
			c *= R[i][k];
		}

		c = pow(c, 1/n);
		c2 = c * V[k];
	}

	long c1 = 1;

	for (long k = 0; k < type; k++) {
		for (long i = 0; i < direction; i++) {
			c1 *= pow(R[i][k], 1 / (n * m));
		}
	}

	long c3 = 0;
	for (long i = 0; i < direction; i++) {
		long c = 1;
		for (long k = 0; k < type; k++) {
			c *= 1 /  pow(R[i][k], 1 / (m));
		}
		c3 += c;
	}

	long lambda = c2 / (c1 * c3);*/

	delete R;
	delete V;
	delete W;
	delete v;
}

double** GetU() {
	if (sizeof(U) / sizeof(U[0][0]) != 0) {
		return U;
	}
}