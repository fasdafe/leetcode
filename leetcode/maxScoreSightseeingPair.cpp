// 1014

#include "utils.h"

using namespace std;

class Solution {
private:
	vector<int> v1, v2;
public:
	int maxScoreSightseeingPair(vector<int>& A) {
		v1 = A;
		v2 = A;
		for (int i = 0; i < A.size(); i++) {
			v1[i] += i;
			v2[i] -= i;
		}
		return helper(0, A.size());
	}

	int helper(int left, int right) {
		if (right - left == 1) return 0;
		int mid = (right + left) / 2;
		int k = max_element(v1.begin() + left, v1.begin() + mid) - v1.begin();
		int m = max_element(v2.begin() + mid, v2.begin() + right) - v2.begin();
		return max(helper(left, mid), max(helper(mid, right), v1[k] + v2[m]));
	}
};

// https://leetcode.com/problems/best-sightseeing-pair/discuss/260850/JavaC%2B%2BPython-One-Pass
class Solution2 {
public:
	int maxScoreSightseeingPair(vector<int>& A) {
		int res = 0, cur = 0;
		for (int a : A) {
			res = max(res, cur + a);
			cur = max(cur, a) - 1;
		}
		return res;
	}
};