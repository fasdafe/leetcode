// #3
#include "utils.h"
using namespace std;

class Solution { // mine
public:
	int lengthOfLongestSubstring(string s) {
		vector<int> count(256, 0);
		int res = 0, c, left = 0, right = 0;
		for (; right < s.size(); ++right) {
			c = s[right];
			if (count[c]) {
				while (s[left] != c) {
					count[s[left]]--;
					left++;
				}
				left++;
				// cout << left << ", " << right << endl;
			}
			else count[c]++;
			res = max(res, right - left + 1);
		}
		return max(res, right - left);
	}
};

class Solution1 {
public:
	int lengthOfLongestSubstring(string s) {
		vector<int> m(256, -1);
		int ans = 0, last = -1;
		for (int i = 0; i < s.size(); i++) {
			last = max(last, m[s[i]]);
			ans = max(ans, i - last);
			m[s[i]] = i;
		}
		return ans;
	}
};