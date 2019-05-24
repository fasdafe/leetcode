// 1044
#include "utils.h"
using namespace std;

class Solution {
public:
	string longestDupSubstring(string S) { // brute force with pruning
		int n = S.size();
		vector<vector<int>> pos(26);
		for (int i = 0; i < n; ++i) pos[S[i] - 'a'].push_back(i);
		int len = 0;
		string res = "";
		for (int k = 0; k < 26; ++k) {
			vector<int>& v = pos[k];
			for (int i = 0; i < v.size(); ++i) {
				for (int j = i + 1; j < v.size(); ++j) {
					if (v[i] > 0 && S[v[i] - 1] == S[v[j] - 1]) continue;
					int p = v[i], q = v[j];
					while (q < n && S[p] == S[q]) { p++; q++; }
					if (q - v[j] > len) {
						len = q - v[j];
						res = S.substr(v[j], len);
					}
				}
			}
		}
		return res;
	}
};

class Solution0 { // still slow
public:
	string longestDupSubstring(string S) {
		int n = S.size();
		int len = 0, end1 = 0, end2 = 0;
		for (int k = 1; k < n; ++k) {
			for (int i = 0, r = 0; i < n - k; ++i) {
				if (S[i] != S[i + k]) r = 0;
				else {
					r++;
					if (r > len) {
						end1 = i;
						end2 = i + k;
						len = r;
					}
				}
			}
		}
		return len > 0 ? S.substr(end1 - len + 1, len) : "";
	}
};

class Solution2 { //Rabin-Karp Algorithm: binary search + rolling hash
public:
	string longestDupSubstring(string& s) {
		// binary search on length of duplicate substring
		int n = s.size();
		int lo = 0, hi = n - 1, mid;
		int startIndex = -1, k = 0;
		while (lo <= hi) {
			mid = lo + (hi - lo) / 2;
			int index = check(s, mid);
			if (index != -1) {
				// record
				startIndex = index;
				k = mid;
				// update search range
				lo = mid + 1;
			}
			else {
				hi = mid - 1;
			}
		}

		if (k == 0) {
			return "";
		}
		return s.substr(startIndex, k);
	}
private:
	// check if there exists two same substring of length k
	// Rabin-Karp, rolling hash
	// time O(N), space O(N)
	int check(string& s, int k) {
		int n = s.size();
		// all prime of the form 6k + 1, 6k - 1
		int q = 6 * (1 << 20) + 1;
		// base
		int b = 31;
		// precompute power = b^(k-1)
		int power = 1;
		for (int i = 1; i < k; i++) {
			power = (power * b) % q;
		}
		// double check by using hash table (key=hash code, value={startIndex})
		unordered_map<int, vector<int>> seen;
		// initialize
		int hash = 0;
		for (int i = 0; i < k; i++) {
			hash = (hash * b % q + s[i]) % q;
		}
		seen[hash].push_back(0);

		// rolling hash, Rabin-Karp
		for (int i = k; i < n; i++) {
			// remove old value
			hash = (hash - power * s[i - k] % q + q) % q;
			// add new value
			hash = (hash * b % q + s[i]) % q;
			if (seen.count(hash)) {
				// double check
				for (int& index : seen[hash]) {
					if (s.substr(index, k) == s.substr(i - k + 1, k)) {
						return index;
					}
				}
			}
			// add to hash table
			seen[hash].push_back(i - k + 1);
		}

		// does not find
		return -1;
	}
};

void testLongestDupSubstring() {
	string s;
	cin >> s;
	Solution0 sol;
	cout << s.size() << ": " << endl << s << endl;
	string subs = sol.longestDupSubstring(s);
	cout << subs << endl;
}