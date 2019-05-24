// #992

#include "utils.h"
using namespace std;

class Solution {
public:
	int subarraysWithKDistinct(vector<int>& A, int K) {
		unordered_map<int, int> mp1, mp2;
		int res = 0, left = 0, mid = 0, right = 0;
		for (int right = 0; right < A.size(); ++right) {
			mp1[A[right]]++;
			// cout << mp1.size() << ", ";
			if (mp1.size() > K) {
				while (mp1[A[left]] > 1) mp1[A[left++]]--;
				mp1.erase(A[left++]);
			}
			mp2[A[right]]++;
			// cout << mp2.size() << endl;
			if (mp2.size() >= K) {
				while (mp2[A[mid]] > 1) mp2[A[mid++]]--;
				mp2.erase(A[mid++]);
			}
			if (mp1.size() == K) res += (mid - left);
			// cout << mp1.size() << ", " << mp2.size() << " # " << left << ", " << mid << endl;
		}
		return res;
	}
};

class Solution1 { // lee215
public:
	int subarraysWithKDistinct(vector<int>& A, int K) {
		return atMostK(A, K) - atMostK(A, K - 1);
	}
	int atMostK(vector<int> & A, int K) {
		int i = 0, res = 0;
		unordered_map<int, int> count;
		for (int j = 0; j < A.size(); ++j) {
			if (!count[A[j]]++) K--;
			while (K < 0) {
				if (!--count[A[i]]) K++;
				i++;
			}
			res += j - i + 1;
		}
		return res;
	}
};