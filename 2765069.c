/*
 * https://math.stackexchange.com/questions/2765069/what-proportion-of-the-natural-numbers-satisfies-the-following-inequality
 */

#include <stdio.h>
#include <math.h>
#define MAX 100000000

long long table[MAX];
int n[MAX];

int primes[5000];
int pi;
inline bool square( long long x );

FILE *f;

void init()
{
	f = fopen("file.txt", "w");
	if (f == NULL)
	{
	    printf("Error opening file!\n");
	    exit(1);
	}
	for (int i = 2; i < 32768; i++)
	{
		if (n[i]) continue;
		primes[pi++] = i;
		for (int j = 2; i * j < 32768; j++) n[i * j] = 1;
	}
	printf("init end\n");
}

int gcd(long long a, long long b)
{
	if (!b) return a;
	return gcd(b, a % b);
}

int main(void)
{
	init();
	for (int iter = 0; iter < 10; iter++)
	{
		for (int i = 0; i < MAX; i++) table[i] = 1;
		for (int i = 0; i < MAX; i++) n[i] = MAX * iter + i + 1;
		printf("initialization done\n");
		for (int i = 0; i < pi; i++)
		{
			int start = n[0];
			if (start % primes[i] != 0) start += primes[i] - start % primes[i];
			start -= n[0];
			for (int j = start; j < MAX; j += primes[i])
			{
				int c = 1;
				while (n[j] % primes[i] == 0)
				{
					c *= primes[i];
					c += 1;
					n[j] /= primes[i];
				}
				table[j] *= c;
			}
		}
		printf("pi iteration done\n");
		for (int i = 0; i < MAX; i++)
		{
			if (n[i] > 1) table[i] *= n[i] + 1;
			int m = MAX * iter + i + 1;
			double sqrtn = sqrt(m);
			int result = gcd(m, table[i]);
			if (result > sqrtn)
			{
				fprintf(f, "n: %d, c: %f\n", m, result / sqrtn);
			}
		}
		printf("loop done\n");
	}
	return 0;
}
