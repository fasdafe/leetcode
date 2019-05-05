// LeetCode #401: Binary Watch

#include "utils.h"

using namespace std;

vector<int> getNumWithNBits(int nBits, int max){
	vector<int> v;
	for(int k = 0; k < max; k++){
		int n = 0, i = k;
		while(i){
			if(i&1) n++;
			i >>= 1;
		}
		if(n == nBits) v.push_back(k);
	}
	return v;
}


vector<string> readBinaryWatch(int num) {
	vector<string> res;
	vector<int> hours, minutes;
	for(int i = 0; i <= num; i++){
		hours = getNumWithNBits(i, 12);
		minutes = getNumWithNBits(num-i, 60);
		for(int j = 0; j < hours.size(); j++){
			for(int k = 0; k < minutes.size(); k++){
				string m = to_string(minutes[k]);
				if(minutes[k] < 10) m = "0"+m;
				res.push_back(to_string(hours[j]) + ":" + m);
			}
		}
	}
	return res;
}

void testBinaryWatch(){

	int n[] = {0, 1, 3, 5};
	for(int i = 0; i < sizeof(n)/sizeof(int); i++){
		vector<string> v = readBinaryWatch(n[i]);
		for(auto s : v){
			cout << s << " ";
		}
		cout << endl;
	}
}