// #982
#include "utils.h"
using namespace std;

class Solution {
public:
	int countTriplets(vector<int>& A) {
		int nbits = 0;

		int maximum = *max_element(A.begin(), A.end());
		while (maximum) {
			maximum >>= 1;
			++nbits;
		}

		int limit = 1 << nbits;
		//cout << "limit = " << limit << ":" << endl;
		vector<int> counts(limit, 0);

		for (auto a : A) for (auto b : A)
			++counts[a & b];
		//cout << counts << endl;

		int answer = 0;
		for (auto i : A) {
			//cout << "i = " << i << ":" << endl;
			for (int j = 0, k = 0; j < limit; k = i & j) {
				//cout << "j = " << j << ", i & j = " << k;
				if (k == 0) {
					//cout << ", counts[j] = " << counts[j];
					answer += counts[j++];
				}
				else
					j += k; // why this works ?!
				//cout << endl;
			}
		}

		return answer;
	}
};

class Solution1 {
public:
	int countTriplets(vector<int>& A) {

		int n = A.size();

		vector<int> cnt(1 << 16, 0);
		for (int i = 0; i < n; ++i) cnt[A[i]]++; //inital counts of supermasks of (i)

		//counting all the submasks for a given supermask (i) by removing one bit at a time
		int mx = 1 << 16;
		for (int bit = 0; bit < 16; ++bit) {
			int bit_to_remove = 1 << bit;
			for (int i = bit_to_remove; i < mx; i++) {
				if ((i >> bit) & 1) // if (i) has this bit set to 1
					cnt[i] += cnt[i ^ bit_to_remove]; // try removing this set bit and adding the number of ALREADY CALCULATED submasks to the current supermask (i)
			}
		}

		//just collecting up the answer after deciding on the first two elements (i, j) from their calculated complementary mask.
		int res = 0;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				int mask = A[i] & A[j];
				// int req_msk = (~mask) & ((1 << 16) - 1);  //or use this
				int req_msk = mask ^ ((1 << 16) - 1);
				res += cnt[req_msk];
			}
		}

		return res; // result ^_^
	}
};

void testCountTriplets() {
	vector<int> A;
	cin >> A;
	Solution1 sol;
	cout << sol.countTriplets(A) << endl;
}