// #301

#include "utils.h"

using namespace std;

class Solution {
public:
    vector<string> removeInvalidParentheses(string s) {
        int invalidOpen = 0, invalidClose = 0, net = 0;
        for(char c : s){
            if(c == '(') net++;
            else if(c == ')') net--;
            if(net < 0){
				invalidClose++;
				net = 0;
			}
        }
        invalidOpen = net;
        unordered_set<string> res;
        dfs(s, 0, invalidOpen, invalidClose, "", 0, res);
        return vector<string>(res.begin(), res.end());
    }
    
    void dfs(const string& s, int start, int invalidOpen, int invalidClose, const string& prefix, int unmatchedOpen, unordered_set<string>& res){
        if(invalidOpen<0 || invalidClose<0 || unmatchedOpen<0) return;
        if(invalidOpen==0 && invalidClose==0){
            string cand(unmatchedOpen, '('), suffix = s.substr(start);
            cand += suffix;
            if(isValid(cand)) res.insert(prefix+suffix);
            return;
        }
        if(start == s.size()) return;
        if(s[start] == '('){
            dfs(s, start+1, invalidOpen-1, invalidClose, prefix, unmatchedOpen, res);
            dfs(s, start+1, invalidOpen, invalidClose, prefix+"(", unmatchedOpen+1, res);
        }
        else if(s[start] == ')'){
            dfs(s, start+1, invalidOpen, invalidClose-1, prefix, unmatchedOpen, res);
            dfs(s, start+1, invalidOpen, invalidClose, prefix+")", unmatchedOpen-1, res);
        }
        else
            dfs(s, start+1, invalidOpen, invalidClose, prefix+s[start], unmatchedOpen, res);
    }

    bool isValid(const string& s){
        int pair = 0;
        for(char c : s){
            if(c == '(') pair++;
            else if(c == ')') pair--;
            if(pair < 0) return false;
        }
        return pair == 0;
    }
};

class Solution2 {
private:
    bool isValid(string s) {
        int sum = 0;
        for(char &c : s) {
            if(c == '(') ++sum;
            else if(c == ')') --sum;
            if(sum < 0) return false;
        }
        return sum == 0;
    }
public:
    vector<string> removeInvalidParentheses(string s) {
        int num1 = 0, num2 = 0;
        for(char &c : s) {
            num1 += c == '(';
            if (num1 == 0) {
                num2 += c == ')';
            } else {
                num1 -= c == ')';
            }
        }
        vector<string> ret;
        dfs(s, 0, num1, num2, ret);
        return ret;
    }
    void dfs(string s, int beg, int num1, int num2, vector<string> &ret) {
        if(num1 == 0 && num2 == 0) {
            if(isValid(s))
                ret.push_back(s);
        } else {
            for(int i = beg; i < s.size(); ++i) {
                string tmp = s;
                if(num2 == 0 && num1 > 0 && tmp[i] == '(') {
                    if(i == beg || tmp[i] != tmp[i - 1]) {
                        tmp.erase(i, 1);
                        dfs(tmp, i, num1 - 1, num2, ret);
                    }
                }
                if(num2 > 0 && tmp[i] == ')') {
                    if(i == beg || tmp[i] != tmp[i - 1]) {
                        tmp.erase(i, 1);
                        dfs(tmp, i, num1, num2 - 1, ret);
                    }
                }
            }
        }
    }
};

void testRemoveInvalidParentheses(){
	Solution2 mysol;
	string s;
	cin >> s;
	vector<string> res = mysol.removeInvalidParentheses(s);
	cout << res << endl;
}