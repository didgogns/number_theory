package practice;

import java.util.*;

public class Practice {
	static int MAX = 72;
	
	static int lcm(int a, int b) {
		for (int i = a; i <= a * b; i++) {
			if (i % a == 0 && i % b == 0) return i;
		}
		return -1;
	}
	static boolean[][] possible = new boolean[MAX + 1][MAX + 1];
	
	//@SuppressWarnings("resource")
	public static void main(String[] args) {
		for (int n = 1; n <= MAX; n++) {
			double max = 0.0;
			for (int i = 1; i <= n; i++) {
				for (int j = 1; j <= n; j++) {
					if (lcm(i, j) > n) possible[i][j] = true;
					else possible[i][j] = false;
				}
			}
			for (long i = 0; i < (1L << (n / 2 + 1)); i++) {
				List<Integer> mem = new ArrayList<Integer>();
				for (int j = 0; j < (n / 2 + 1); j++) {
					if (((i >> ((n / 2 + 1) - 1 - j)) & 1L) != 0) mem.add(j + 1);
				}
				boolean flag = true;
				int z = 0;
				for (int a : mem) {
					for (int b : mem) {
						if (a != b && !possible[a][b]) {
							flag = false;
							z = b;
							break;
						}
					}
					if (!flag) break;
				}
				if (!flag) {
					i += (1L << ((n / 2 + 1) - z)) - 1;
					continue;
				}
				for (int j = (n / 2 + 2); j <= n; j++)
				{
					flag = true;
					for (int a : mem) {
						if (j % a == 0) flag = false;
					}
					if (flag) mem.add(j);
				}
				double sum = 0.0;
				for (int a : mem) sum += 1.0 / a;
				if (max < sum) max = sum;
			}
			System.out.println("n: " + n + ", max: " + max);
		}
	}
}
