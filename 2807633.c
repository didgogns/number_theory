/*
 * https://math.stackexchange.com/questions/2807633/has-sigma-left-sigma-0n4-right-n-infinitely-many-solutions
 */

#include <stdio.h>
#include <math.h>

int prime[25] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};
double logp[25];
//log(search limit), will work up to ~80
double limit = 80;
/*
 * To easily compute sigma_0(sigma(m^4)) where m < 122880, I pre-computed possible sigma_0(sigma(p^4k)) of prime p which can appear in factorization of m (that is, p <= 43 and p^k <= 120880)
 * Also note that sigma_0(sigma(m^4)) <= products over i (sigma_0(sigma(p_i^4k_i))).
 */
int sigma_zero[20][20] = {
	{1, 2, 4, 2, 2, 12, 8, 8, 16, 4, 4, 64, 4, 8, 16, 2, 8},
	{1, 3, 4, 2, 4, 8, 12, 8, 16, 4, 8},
	{1, 4, 8, 2, 4, 16, 64, 8},
	{1, 2, 24, 2, 4, 32, 8},
	{1, 4, 8, 4, 2},
	{1, 2, 12, 8, 8},
	{1, 2, 8, 4, 8},
	{1, 4, 24, 8},
	{1, 2, 16, 4},
	{1, 2, 16, 8},
	{1, 8, 24, 8},
	{1, 8, 96, 2},
	{1, 4, 8, 8},
	{1, 2, 96, 2}
};

void init()
{
	for (int i = 0; i < 25; i++) logp[i] = log(prime[i]);
}

void bruteforce1()
{
	int max = 0;
	for (int i = 0; i < 100000000; i++)
	{
		int pow3 = i / 10000000;
		int pow5 = (i % 10000000) / 1000000;
		int pow7 = (i % 1000000) / 100000;
		int pow11 = (i % 100000) / 10000;
		int pow13 = (i % 10000) / 1000;
		int pow17 = (i % 1000) / 100;
		int pow19 = (i % 100) / 10;
		int pow23 = i % 10;
		if (pow3 < pow5) continue;
		if (pow5 < pow7) continue;
		if (pow7 < pow11) continue;
		if (pow11 < pow13) continue;
		if (pow13 < pow17) continue;
		if (pow17 < pow19) continue;
		if (pow19 < pow23) continue;
		if (!pow23) continue;
		double curLog = 0;
		int curDivisor = 1;
		curLog += pow3 * logp[1];
		curLog += pow5 * logp[2];
		curLog += pow7 * logp[3];
		curLog += pow11 * logp[4];
		curLog += pow13 * logp[5];
		curLog += pow17 * logp[6];
		curLog += pow19 * logp[7];
		curLog += pow23 * logp[8];
		if (curLog > limit) continue;
		curDivisor *= pow3 + 1;
		curDivisor *= pow5 + 1;
		curDivisor *= pow7 + 1;
		curDivisor *= pow11 + 1;
		curDivisor *= pow13 + 1;
		curDivisor *= pow17 + 1;
		curDivisor *= pow19 + 1;
		curDivisor *= pow23 + 1;
		if (max < curDivisor)
		{
			max = curDivisor;
			printf("%d %d %d %d %d %d %d %d", pow3, pow5, pow7, pow11, pow13, pow17, pow19, pow23);
			for (int i = 9; i < 25; i++) printf(" 0");
			printf(", curDivisor: %d\n", curDivisor);
		}
		for (int i = 9; i < 25; i++)
		{
			curLog += logp[i];
			if (curLog > limit) break;
			curDivisor *= 2;
			if (max < curDivisor)
			{
				max = curDivisor;
				printf("%d %d %d %d %d %d %d %d", pow3, pow5, pow7, pow11, pow13, pow17, pow19, pow23);
				for (int j = 9; j <= i; j++) printf(" 1");
				for (int j = i + 1; j < 25; j++) printf(" 0");
				printf(", curDivisor: %d\n", curDivisor);
			}
		}
	}
}

void bruteforce2()
{
	for (int i = 1; i <= 122880; i++)
	{
		int curI = i;
		int divider = 1;
		for (int j = 0; j < 14; j++)
		{
			int cnt = 0;
			while (curI % prime[j] == 0)
			{
				curI /= prime[j];
				cnt++;
			}
			divider *= sigma_zero[j][cnt];
		}
		if (curI != 1) continue;
		if (divider >= i || divider == 0) printf("%d\n", i);
	}
}

int main(void)
{
	init();
	bruteforce1();
	bruteforce2();
}
