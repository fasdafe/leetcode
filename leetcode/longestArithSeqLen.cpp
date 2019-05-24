// 1027
#include "utils.h"
using namespace std;

class Solution {
public:
	int longestArithSeqLength(vector<int>& A) {
		int n = A.size(), res = 2;
		vector<unordered_map<int, int>> mp(n);
		for (int i = 1; i < n; ++i) {
			for (int j = 0; j < i; ++j) {
				auto it = mp[j].find(A[i] - A[j]);
				int k = it == mp[j].end() ? 2 : it->second + 1;
				mp[i][A[i] - A[j]] = k;
				res = max(res, k);
			}
			//cout << "mp[" << i << "]: " << "A[i] = " << A[i] << endl;
			//for (auto it = mp[i].begin(); it != mp[i].end(); ++it) {
			//	cout << "{ " << it->first << ", " << it->second << " }" << endl;
			//}
		}
		return res;
	}
};

void testLongestArithSeqLen() {
	vector<int> A;
	cin >> A;
	Solution sol;
	cout << sol.longestArithSeqLength(A) << endl;
}