// LeetCode #32: Longest Valid Parentheses

#include "utils.h"

using namespace std;

int longestValidParenthesesStack(string s) {
	stack<int> st;
	int prev = 0, last = 0;
	for(int i = 0; i < s.length(); i++){
		if(st.empty()){
			if(s[i] == '('){
				st.push(i);
			}
			else{
				st.push(~i);
				prev = i;
			}
		}
		else{
			if(s[i] == '('){
				st.push(i);
			}
			else{
				if(st.top() >= 0) {
					st.pop();
					if(st.empty()) last = i+1;
					else if(st.top() >= 0) last = max(last, i-st.top());
					else last = max(last, i-(~st.top()));
				}
				else {
					prev = max(prev, i+st.top());
					last = 0;
					st.push(~i);
				}
			}
		}
	}
	return max(prev, last);
}

int longestValidParenthesesStackShort(string s) {
	stack<int> st;
	int prev = 0, last = 0;
	for(int i = 0; i < s.length(); i++){
		if(s[i] == '(') st.push(i);
		else if(st.empty()){
			st.push(~i);
			prev = i;
		}
		else if(st.top() < 0){
			prev = max(prev, i+st.top());
			last = 0;
			st.push(~i);
		}
		else{
			st.pop();
			if(st.empty()) last = i+1;
			else if(st.top() >= 0) last = max(last, i-st.top());
			else last = max(last, i-(~st.top()));
		}
	}
	return max(prev, last);
}

int longestValidParenthesesStackShorter(string s) {
	stack<int> st;
	int longest = 0, i, t;
	for(i = 0; i < s.length(); i++){
		if(s[i] == '(') st.push(i);
		else if(st.empty() || st.top() < 0) st.push(~i);
		else st.pop();
	}
	if(st.empty()) return i; // i = s.length()
	while(!st.empty()){
		t = st.top();
		t = t<0?~t:t;
		longest = max(longest, i-t);
		i = t;
		st.pop();
	}
	return max(longest-1, t);
}

int longestValidParenthesesStackShortest(string s) {
	vector<int> st;
	for(int i = 0; i < s.length(); i++){
		if(s[i] == '(') st.push_back(i);
		else if(st.empty() || st.back() < 0) st.push_back(~i);
		else st.pop_back();
	}
	st.push_back(s.length());
	for(int i = 0; i < st.size(); i++)
		if(st[i] < 0) st[i] = ~st[i];
	int longest = st[0];
	for(int i = 1; i < st.size(); i++) 
		longest = max(longest, st[i]-st[i-1]-1);
	return longest;
}

int longestValidParenthesesStackShortest2(string s) {
	stack<int> st;
	int res = 0, start = 0;
	for(int i = 0; i < s.length(); i++){
		if(s[i] == '(') st.push(i);
		else{
			if(st.empty()) start = i;
			else{
				st.pop();
				res = max(res, i - (st.empty() ? start : st.top()));
			}
		}
	}
	return res;
}

void testLongestValidParentheses(){
	string s;
	cout << "Type a string of parentheses: ";
	cin >> s;
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << "Length of longest valid substring is " << longestValidParenthesesStackShortest2(s) << endl;
}