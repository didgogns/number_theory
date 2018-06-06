/*
 * https://math.stackexchange.com/questions/2798850/assigning-tennis-players-to-clubs
 */

#include <stdio.h>

//Lookup table. Will explain about it later
int table[0x1FF];
//Sum of bits of each number.
int bitSum[0xFFFF];

void init()
{
	int idx = 0;
	/*
	 * Each value of i represents every possible parity of $A_i$s. For instance, if i = 0, then every bit of i is 0 so every $A_i$ has even value.
	 * If i = 8193 = 0001 0000 0000 0001 (base 2), then $A_{0, 0, 0, 0}$ and $A_{1, 1, 0, 0}$ is odd and others are even.
	 * It is always beneficial to assign $A_{0, 0, 0, 0}$, $A_{1, 0, 0, 0}$, $A_{0, 1, 0, 0}$, $A_{1, 1, 0, 0}$ to set 0 and
	 * $A_{0, 0, 1, 0}$, $A_{0, 0, 0, 1}$, $A_{0, 0, 1, 1}$ to set 1.
	 * This observation only leaves $2^9 = 512$ possible assignment for each members.
	 */
	for (int i = 0; i < 0x10000; i++)
	{
		bitSum[i] = bitSum[i >> 1] + (i & 0x1);
		// printf("bitsum[%d] = %d\n", i, bitSum[i]);
		if (i & 0x1111) continue;
		if (~i & 0xE) continue;
		table[idx++] = i;
	}
}

int main(void)
{
	init();
	int A = 0xFF00;
	int B = 0xF0F0;
	int C = 0xCCCC;
	int D = 0xAAAA;

	for (int i = 0; i < 0x10000; i++)
	{
		/*
		 * Check if the sum of wanted students for coach A, B, C, D is even.
		 */
		// printf("i: %d\n", i);
		if (bitSum[i & A] % 2) continue;
		if (bitSum[i & B] % 2) continue;
		if (bitSum[i & C] % 2) continue;
		if (bitSum[i & D] % 2) continue;
		// printf("i: %d is valid \"wishlist\"\n", i);

		int check = 0;
		/*
		 * For each assignment, we check if it meets each coach's requirement.
		 */
		for (int j = 0; j < 512; j++)
		{
			int clubAB = i & ~table[j];
			int clubCD = i & table[j];

			if (bitSum[clubAB & A] < bitSum[clubCD & A]) continue;
			if (bitSum[clubAB & B] < bitSum[clubCD & B]) continue;
			if (bitSum[clubAB & C] > bitSum[clubCD & C]) continue;
			if (bitSum[clubAB & D] > bitSum[clubCD & D]) continue;
			check = 1;
			// printf("ok!\n");
		}
		/*
		 * Print i if it fails.
		 */
		if (!check)
		{
			printf("Conjecture is false for i = %d\n", i);
		}
	}

	return 0;
}
