// 990
#include "utils.h"
using namespace std;

class Solution {
private:
	vector<int> A, ranks;

	int find(int i) {
		if (A[i] != i) A[i] = find(A[i]);
		return A[i];
	}

	bool union_help(int i, int j) {
		int pi = find(i), pj = find(j);
		if (pi == pj) return false;
		if (ranks[pi] < ranks[pj]) A[pi] = pj;
		else if (ranks[pi] > ranks[pj]) A[pj] = pi;
		else {
			A[pj] = pi;
			ranks[pi]++;
		}
		return true;
	}
public:
	bool equationsPossible(vector<string> & equations) {
		for (int i = 0; i < 26; ++i) A.push_back(i);
		ranks = vector<int>(26, 0);
		for (auto& eq : equations) {
			if (eq[1] == '=') union_help(eq[0] - 'a', eq[3] - 'a');
		}
		for (auto& eq : equations) {
			if (eq[1] == '!' && find(eq[0] - 'a') == find(eq[3] - 'a')) return false;
		}
		return true;
	}
};