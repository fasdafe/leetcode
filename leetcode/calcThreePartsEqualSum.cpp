// 1013

#include "utils.h"

using namespace std;

class Solution {
public:
	bool canThreePartsEqualSum(vector<int>& A) {
		int n = A.size(), sum = accumulate(A.begin(), A.end(), 0.0);
		if (n < 3 || sum % 3) return false;
		int t = sum / 3, psum = 0, cnt = 0;
		for (int i = 0; i < n; i++) {
			psum += A[i];
			if (psum == t) {
				psum = 0;
				cnt++;
				if (cnt >= 3) return true;
			}
		}
		return false;
	}
};