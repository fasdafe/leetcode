// LeetCode #405: Convert Int to Hex String

#include "utils.h"

using namespace std;

string toHex(int num) {
	if(num == 0) return "0";
	int n = num>0 ? num : ~num;
	int k = 0;
	string res;
	while(k++ < 8){
		int i = n & 15;
		n >>= 4;
		if(num < 0) i = 15 - i;
		char c = i<10 ? i+'0' : i-10+'a';
		res = c + res;
		if(num > 0 && n == 0) break;
	}
	return res;
}

void testToHex(){
	const int N = 1;
	int test[N] = {-10};
	for(int i = 0; i < N; i++){
		cout << test[i] << " -> " << toHex(test[i]) << endl;
	}
}