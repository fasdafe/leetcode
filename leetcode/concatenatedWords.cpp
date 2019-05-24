// #472
#include "utils.h"
using namespace std;

class Solution {
public:
	vector<string> findAllConcatenatedWordsInADict(vector<string>& words) {
		auto comp = [](const string & s1, const string & s2) -> bool {
			return s1.size() < s2.size(); // don't use "<=", will get runtime error!!!
		};
		sort(words.begin(), words.end(), comp);
		unordered_set<string> w(words.begin(), words.end());
		unordered_set<string> res;
		for (string& s : words) {
			for (int i = s.size() - 1; i > 0; --i) {
				if (w.count(s.substr(i))) {
					if (res.count(s.substr(0, i)) || isConcatenated(w, s.substr(0, i))) {
						res.insert(s);
						//cout << s << " = " << s.substr(0, i) << " + " << s.substr(i) << endl;
						break;
					}
				}
			}
		}
		return vector<string>(res.begin(), res.end());
	}

	bool isConcatenated(const unordered_set<string> & words, const string & s) {
		for (int i = s.size() - 1; i > 0; --i) {
			if (words.count(s.substr(i)) && isConcatenated(words, s.substr(0, i)))
				return true;
		}
		return words.count(s);
	}
};

void testConcatenatedWords() {
	vector<string> words;
	cin >> words;
	Solution sol;
	cout << sol.findAllConcatenatedWordsInADict(words) << endl;
}