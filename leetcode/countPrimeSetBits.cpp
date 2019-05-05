// LeetCode #762: Prime Number of Set Bits in Binary Representation

#include "utils.h"

using namespace std;

int countPrimeSetBits(int L, int R) {
	string isPrime = "001101010001010001010001000001010";
	int count = 0, nset, k;
	if(L <= 0) L = 1;
	for(int i = L; i <= R; ++i){
		k = i;
		nset = 1;
		while(k = k & (k-1)){
			nset++;
		}
		if(isPrime[nset] == '1') count++;
	}
	return count;
}

void testCountPrimeSetBits(){
	const int N = 1;
	int L[N] = {842};
	int R[N] = {888};
	for(int i = 0; i < N; i++){
		cout << "L = " << L[i] << ", R = " << R[i] << " -> count = " << countPrimeSetBits(L[i], R[i]) << endl;
	}
}