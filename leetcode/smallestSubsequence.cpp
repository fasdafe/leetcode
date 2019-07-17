// 5086: https://leetcode.com/contest/weekly-contest-140/problems/smallest-subsequence-of-distinct-characters/

#include "utils.h"
using namespace std;

class Solution {
public:
	string smallestSubsequence(string text) {
		string res = "";
		helper(text, 0, res);
		return res;
	}

	void helper(const string& text, int start, string& exclude) {
		// cout << text.substr(start) << endl;
		map<char, int> mp, first_id;
		for (int i = start; i < text.size(); ++i) {
			if (exclude.find(text[i]) == string::npos)
				mp[text[i]]++;
		}
		for (int i = start; i < text.size(); ++i) {
			if (exclude.find(text[i]) != string::npos) continue;
			if (first_id.find(text[i]) == first_id.end())
				first_id[text[i]] = i;
			if (--mp[text[i]] == 0) {
				auto p = *first_id.begin();
				exclude.push_back(p.first);
				// cout << text.substr(i) << ": " << exclude << endl;
				helper(text, p.second + 1, exclude);
				return;
			};
		}
	}
};

class Solution2 { // non-recursive, very efficient but hard to understand!!
public:
	string smallestSubsequence(string text) {
		string res = "";
		unordered_map<char, int> cnt;
		for (char c : text) cnt[c]++;
		for (char c : text) {
			if (res.find(c) != string::npos) {
				cnt[c]--;
				continue;
			}
			while (!res.empty() && c < res.back() && cnt[res.back()])
				res.pop_back();
			cnt[c]--;
			res.push_back(c);
		}
		return res;
	}
};