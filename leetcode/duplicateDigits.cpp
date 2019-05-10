// #1012: Numbers With Repeated Digits

#include "utils.h"

using namespace std;

class Solution {
private:
	int helper(const vector<int>& digits, int nSlots) {
		int n = digits.size() - nSlots;
		unordered_set<int> s(digits.begin(), digits.begin() + n - 1);
		if (s.size() < n - 1) return 0;
		int num = digits[n - 1];
		for (auto& d : s)
			if (d < digits[n - 1]) num--;
		if (n == 1) num--;
		for (int i = 0; i < nSlots; i++) 
			num *= (10 - n - i);
		if (n == 1) {
			for (int i = 0, k = 1; i < nSlots; i++) {
				num += 9 * k;
				k *= (9 - i);
			}
			num++;
		}
		return num;
	}
public:
	int numDupDigitsAtMostN(int N) {
		vector<int> v;
		int res = N + 1, k = N + 1;
		do {
			v.push_back(k % 10);
		} while (k /= 10);
		reverse(v.begin(), v.end());
		for (int i = 0; i < v.size(); i++) 
			res -= helper(v, i);
		return res;
	}
};

void testDuplicateDigits() {
	int N;
	cin >> N;
	Solution sol;
	cout << sol.numDupDigitsAtMostN(N) << endl;
}