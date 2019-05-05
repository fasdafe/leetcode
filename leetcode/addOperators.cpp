// #282
#include "utils.h"
using namespace std;

class Solution {
public:
    vector<string> addOperators(string num, int target) {
        vector<string> res;
		if(num.size() == 0) return res;
        helper(num, 1, target, "", res);
        return res;
    }
    
    void helper(string num, long long mult, long long target, string suffix, vector<string>& out) {
        int sz = num.size();
        for(int i = sz-1; i >= max(1, sz-10); i--) {
            string s1 = num.substr(0, i), s2 = num.substr(i);
            if(i < sz-1 && s2[0] == '0') continue;
			long long n = stoll(s2);
            if(n * mult > (long long)INT_MAX) continue;
            helper(s1, 1, target-n*mult, "+"+s2+suffix, out); 
            helper(s1, 1, target+n*mult, "-"+s2+suffix, out);
            helper(s1, n*mult, target, "*"+s2+suffix, out);
        }
        if(sz <= 10) {
			if(sz > 1 && num[0] == '0') return;
            if(mult * stoll(num) == target) out.push_back(num+suffix);
        }
    }
};

void testAddOperators() {
	string s;
	cout << "string: ";
	cin >> s;
	int target;
	cout << "target: ";
	cin >> target;
	Solution mysol;
	vector<string> res = mysol.addOperators(s, target);
	cout << res << endl;
	cout << "there are " << res.size() << " solutions!" << endl;
}