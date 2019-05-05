// LeetCode #693: Binary number with alternating bits

#include "utils.h"

using namespace std;

bool hasAlternatingBits(int n) {
	while((n&3) == 1 || (n&3) == 2){
		n >>= 1;
	}
	return n == 0;
}

void testHasAlternatingBits(){
	int n[] = {5,7,9,10};
	for(int i = 0; i < sizeof(n)/sizeof(int); i++){
		cout << n[i] << " -> " << (hasAlternatingBits(n[i]) ? "true" : "false") << endl;
	}
}