// 1016

#include "utils.h"

using namespace std;

class Solution {
public:
	bool queryString(string S, int N) {
		unordered_set<int> set;
		for (int i = 0; i < S.size(); i++) {
			if (S[i] == '0') continue;
			int n = 1;
			set.insert(n);
			for (int j = i + 1; j < min((int)S.size(), i + 31); j++) {
				n <<= 1;
				n += S[j] - '0';
				if (n <= N) set.insert(n);
				else break;
			}
		}
		return N == set.size();
	}
};