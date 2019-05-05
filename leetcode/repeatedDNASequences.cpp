// LeetCode #187: Repeated DNA Sequences

#include "utils.h"

using namespace std;

vector<string> findRepeatedDnaSequences(string s) {
	set<string> st, setOut;
	for(int i = 0; i <= (int)s.length()-10; i++){
		string subs = s.substr(i, 10);
		if(!st.insert(subs).second)
			setOut.insert(subs);
	}
	return vector<string>(setOut.begin(), setOut.end());
}

void printResults(string s){
	cout << s << " -> " << endl;
	for(auto &item : findRepeatedDnaSequences(s))
		cout << item << endl;
}

void testRepeatedDNASequences(){
	printResults("AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT");
	printResults("");
	printResults("AAAAAAAAAAAA");
}