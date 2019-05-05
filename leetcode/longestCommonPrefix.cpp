// #14
#include "utils.h"
using namespace std;

class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        string prefix;
        if(strs.size() == 0) return prefix;
        prefix = strs[0];
        for(int i = 1; i < strs.size(); i++)
            helper(strs[i], prefix);
        return prefix;
    }
    
    void helper(const string& str, string& prefix) {
        int i = 0;
        while(i < str.size() && i < prefix.size()){
            if(str[i] == prefix[i]) i++;
			else break;
        }
        prefix.erase(prefix.begin()+i, prefix.end());
    }
};


void testLongestCommonPrefix() {
	vector<string> strs;
	cin >> strs;
	cout << strs << endl;
	Solution mysol;
	string s = mysol.longestCommonPrefix(strs);
	cout << s << endl;
}