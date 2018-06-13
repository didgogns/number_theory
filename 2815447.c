/*
 * https://math.stackexchange.com/questions/2815447/conjecture-about-the-prime-number-function
 */

#include <stdio.h>
#include <math.h>

// use p_n > nlogn to compute lower bound of p_n,n
double min_pnn(int n)
{
	double b = log(n);
	for (int i = 0; i < n; i++) b += log(b);
	return b;
}

int main(void)
{
	for (int i = 1; i <= 100; i++)
	{
		double log_pnn = min_pnn(i);
		double log_nn = i * log(i);
		double log_n1n1 = (i + 1) * log(i + 1);

		if (log_pnn < log_nn) printf("p_%d_%d is too small, %f < %f\n", i, i, log_pnn, log_nn);
		if (log_pnn > log_n1n1) printf("p_%d_%d is too big, %f > %f\n", i, i, log_pnn, log_n1n1);
	}
}
