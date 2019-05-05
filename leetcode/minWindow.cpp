// #76: Minimum window substring
// https://leetcode.com/problems/minimum-window-substring/

#include "utils.h"
using namespace std;

class Solution {
public:
    string minWindow(string s, string t) {
        int first = 0, last = 0;
        string res;
        unordered_map<char, int> need, seen;
        for(char c : t) need[c]++;
        int t_need = t.size(), t_seen = 0;
        while(t_seen < t_need && last < s.size()) {
            char c = s[last++];
            if(need.find(c) != need.end()) {
                seen[c]++;
                if(seen[c] <= need[c]) t_seen++;
            }
        }
        if(t_seen == t_need) {
            int min_len = INT_MAX, res_first, res_last;
            while(t_seen == t_need || last < s.size()) {
                if(t_seen == t_need) {
                    if(last - first < min_len) {
						min_len = last - first;
                        res_first = first;
                        res_last = last;
                    }
                    char c = s[first++];
                    if(need.find(c) != need.end()) {
                        seen[c]--;
                        if(seen[c] < need[c]) t_seen--;
                    }
                }
                else {
                    char c = s[last++];
                    if(need.find(c) != need.end()) {
                        seen[c]++;
                        if(seen[c] <= need[c]) t_seen++;
                    }
                }
            }
            res = s.substr(res_first, res_last-res_first);
        }
        return res;
    }
};

class Solution2 {
public:
    string minWindow(string s, string t) {
        vector<int> need(128, 0), seen(128, 0);
        for(char c : t) need[c]++;
        int t_need = t.size(), t_seen = 0;
        int min_len = INT_MAX, first = 0, last = 0, res_first = 0, res_last = 0;
        while(t_seen == t_need || last < s.size()) {
            if(t_seen == t_need) {
                if(last - first < min_len) {
                    min_len = last - first;
                    res_first = first;
                    res_last = last;
                }
                char c = s[first++];
                if(--seen[c] < need[c]) t_seen--;
            }
            else {
                char c = s[last++];
                if(++seen[c] <= need[c]) t_seen++;
            }
        }
        return s.substr(res_first, res_last-res_first);
    }
};

class Solution3 { // optimized version
public:
    string minWindow(string s, string t) {
        string res = "";
        vector<int> letterCnt(128, 0);
        int left = 0, cnt = 0, minLen = INT_MAX;
        for (char c : t) ++letterCnt[c];
        for (int i = 0; i < s.size(); ++i) {
            if (--letterCnt[s[i]] >= 0) ++cnt;
            while (cnt == t.size()) {
                if (minLen > i - left + 1) {
                    minLen = i - left + 1;
                    res = s.substr(left, minLen);
                }
                if (++letterCnt[s[left]] > 0) --cnt;
                ++left;
            }
        }
        return res;
    }
};

void testMinWindow() {
	string s, t, res;
	cin >> s >> t;
	Solution2 mysol;
	res = mysol.minWindow(s, t);
	cout << res << endl;
}