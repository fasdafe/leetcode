// #1011

#include "utils.h"

using namespace std;

class Solution {
public:
	int shipWithinDays(vector<int>& weights, int D) {
		int low = 1, high = accumulate(weights.begin(), weights.end(), 0), mid;
		if (daysNeeded(weights, low) <= D) return low;
		while (low < high - 1) {
			mid = (low + high) / 2;
			int k = daysNeeded(weights, mid);
			if (k <= D) high = mid;
			else low = mid;
		}
		return high;
	}

	int daysNeeded(const vector<int> & w, int cap) {
		int days = 1, total = 0;
		for (int i = 0; i < w.size(); i++) {
			if (w[i] > cap) return INT_MAX;
			if (total + w[i] <= cap) total += w[i];
			else {
				days++;
				total = w[i];
			}
		}
		return days;
	}
};

void testShipWithinDays() {
	vector<int> weights;
	int D;
	cin >> weights >> D;
	Solution sol;
	cout << sol.shipWithinDays(weights, D) << endl;
}