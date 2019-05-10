// 1015

#include "utils.h"

using namespace std;

class Solution {
public:
	int smallestRepunitDivByK(int K) {
		if (K % 2 == 0 || K % 5 == 0) return -1;
		else if (K == 1) return 1;
		else {
			int l = 1, n = 1, sum = 1;
			while (sum % K) {
				n *= 10;
				n %= K;
				sum += n;
				l++;
			}
			return l;
		}
	}
};