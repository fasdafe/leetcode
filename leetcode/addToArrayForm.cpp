// 989
#include "utils.h"
using namespace std;

class Solution { // mine
public:
	vector<int> addToArrayForm(vector<int>& A, int K) {
		vector<int> res;
		while (K) {
			res.push_back(K % 10);
			K /= 10;
		}
		if (res.size() == 0) return A;
		reverse(A.begin(), A.end());
		int carry = 0, m = A.size(), n = res.size(), cur = 0;

		for (int i = 0; i < m - n; ++i) res.push_back(0);
		for (int i = 0; i < n - m; ++i) A.push_back(0);

		for (int i = 0; i < max(m, n); ++i) {
			cur = A[i] + res[i] + carry;
			res[i] = cur % 10;
			carry = cur / 10;
		}
		if (carry == 1) res.push_back(1);
		reverse(res.begin(), res.end());
		return res;
	}
};

class Solution1 { // lee215
public:
	vector<int> addToArrayForm(vector<int> A, int K) {
		for (int i = A.size() - 1; i >= 0 && K > 0; --i) {
			A[i] += K;
			K = A[i] / 10;
			A[i] %= 10;
		}
		while (K > 0) {
			A.insert(A.begin(), K % 10);
			K /= 10;
		}
		return A;
	}
};