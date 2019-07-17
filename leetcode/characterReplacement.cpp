// #424
#include "utils.h"

using namespace std;

class Solution {
public:
	int characterReplacement(string s, int k) { // generic template for two pointer algorithms
		int i = 0, j = 0, cnt[91] = {};
		while (j < s.size()) {
			cnt[s[j++]]++;
			if (j - i - *max_element(cnt + 65, cnt + 91) > k)
				cnt[s[i++]]--;
		}
		return j - i;
	}
};

void testCharacterReplacement() {
	string s = "AABABBAA";
	int k = 1;
	Solution sol;
	cout << sol.characterReplacement(s, k) << endl;
}