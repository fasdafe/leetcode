//1065 Index Pairs of a String
//Given a text string and words (a list of strings), return all index pairs[i, j] so that the 
//substring text[i]…text[j] is in the list of words.
//Example 1:
//Input: text = "thestoryofleetcodeandme", words = ["story", "fleet", "leetcode"]
//	Output : [[3, 7], [9, 13], [10, 17]]
//	Example 2 :
//	Input : text = "ababa", words = ["aba", "ab"]
//	Output : [[0, 1], [0, 2], [2, 3], [2, 4]]
//	Explanation :
//	Notice that matches can overlap, see "aba" is found in[0, 2] and [2, 4].
//	-------------------- -
//	https ://blog.csdn.net/u013700358/article/details/90744257 

#include "utils.h"
#include "Trie.h"
using namespace std;

class Solution {
public:
	vector<vector<int>> indexPairs(string text, vector<string>& words) {
		Trie trie;
		for (auto& word : words) trie.insert(word);
		vector<vector<int>> res;
		for (int i = 0; i < text.size(); ++i) {
			string s = string(1, text[i]);
			int j = i;
			while (j < text.size() && trie.startsWith(s)) {
				if (trie.search(s)) res.push_back({ i, j });
				s += text[++j];
			}
		}
		return res;
	}
};

void testIndexPairs() {
	string text = "thestoryofleetcodeandme";
	vector<string> words = { "story", "fleet", "leetcode" };
	Solution sol;
	cout << sol.indexPairs(text, words) << endl;
}