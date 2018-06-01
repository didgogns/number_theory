/*
 * https://math.stackexchange.com/questions/2799106/iterations-of-the-radical-of-an-integer
 */

#include <stdio.h>
#include <math.h>
#define MAX 100000001

int radical[MAX];
int n[MAX];
int isPrime[MAX];

int primes[5000];
int pi;
inline bool square( long long x );

void init()
{
	for (int i = 2; i < 10000; i++)
	{
		if (radical[i]) continue;
		primes[pi++] = i;
		isPrime[i] = 1;
		for (int j = 2; i * j < 10000; j++) radical[i * j] = 1;
	}
	printf("init end\n");
}

int main(void)
{
	init();
	for (int i = 1; i < MAX; i++)
	{
		radical[i] = 1;
		n[i] = i;
	}
	printf("initialization done\n");
	for (int i = 0; i < pi; i++)
	{
		for (int j = primes[i]; j < MAX; j += primes[i])
		{
			radical[j] *= primes[i];
			while (n[j] % primes[i] == 0) n[j] /= primes[i];
		}
	}
	printf("pi iteration done\n");
	for (int i = 0; i < MAX; i++)
	{
		if (n[i] > 1)
		{
			if (n[i] == i) isPrime[i] = 1;
			radical[i] *= n[i];
		}
	}
	long long sum = 0;
	for (int i = 0; i < MAX; i++)
	{
		n[i] = 1;
		int k = i;
		while (k > 1 && !isPrime[k])
		{
			k = radical[k] + 1;
			n[i]++;
		}
		sum += n[i];
	}
	printf("loop done, result: %lld\n", sum);
	return 0;
}
