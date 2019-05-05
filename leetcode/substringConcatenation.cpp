// #30
#include "utils.h"
using namespace std;

class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        unordered_map<string, int> need, seen;
		vector<int> res;
		if(words.size() == 0 || s.size() == 0) return res;
		for(auto &word : words) need[word]++;
        int k = words[0].size(), nWords = words.size();
        for(int i = 0; i < k; i++) {
			int start = i, end = i, cnt = 0;
			seen.clear();
			string subs;
			while(start + k*nWords <= s.size()) {
				subs = s.substr(end, k);
				cnt++;
				if(need.count(subs)) {
					seen[subs]++;
					if(seen[subs] <= need[subs]) {
						if(cnt == nWords) {
							res.push_back(start);
							seen[s.substr(start, k)]--;
							cnt--;
							start += k;
						}
					}
					else {
						while(s.compare(start, k, subs) != 0) {
							seen[s.substr(start, k)]--;
							cnt--;
							start += k;
						}
						seen[s.substr(start, k)]--;
						cnt--;
						start += k;
					}
				}
				else {
					seen.clear();
					start += cnt*k;
					cnt = 0;
				}
				end += k;
			}
		}
        return res;
    }
};

void testSubstringConcatenation() {
	string s;
	cout << "string: ";
	cin >> s;
	vector<string> words;
	cout << "words: ";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cin >> words;
	Solution mysol;
	vector<int> res = mysol.findSubstring(s, words);
	cout << res << endl;
}