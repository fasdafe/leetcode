// #493 Hard
#include "utils.h"

using namespace std;

int reversePairs(const vector<int> &nums) {
	multiset<int> mset;
	int count = 0;
	for (int num : nums) {
		count += distance(mset.upper_bound(2 * num), mset.end()); // cost of distance function is linear!
		mset.insert(num); // cost of insert is logarithmic
	}
	return count;
}

class SolutionBIT {
private:
	struct FenwickTree {
		vector<int> treeVec;
		int sz;
		FenwickTree(int n) : sz(n+1), treeVec(n+1, 0) {}
		int lowBit(int x) {
			return x&(-x);
		}
		int query(int n) {
			int sum = 0;
			while (n > 0 && n < sz) {
				sum += treeVec[n];
				n -= lowBit(n);
			}
			return sum;
		}
		void update(int n, int delta = 1) {
			if (n <= 0) return;
			while (n < sz) {
				treeVec[n] += delta;
				n += lowBit(n);
			}
		}
	};
	

public:
	int reversePairs(const vector<int> &nums) { // time complexity O(n*log(n))
		int count = 0;
		FenwickTree bit(nums.size());
		vector<int> copy = nums;
		sort(copy.begin(), copy.end());
		for (int i = 0; i < nums.size(); i++) {
			count += i - bit.query(upper_bound(copy.begin(), copy.end(), 2 * nums[i]) - copy.begin());
			bit.update(lower_bound(copy.begin(), copy.end(), nums[i]) - copy.begin() + 1);
		}
		return count;
	}
};

void testReversePairs() {
	srand(time(0));
	int n = 200;
	vector<int> nums(n);
	int repeat;
	cin >> repeat;
	SolutionBIT sol;
	int diff = 0, c1, c2;
	for (int r = 0; r < repeat; r++) {
		for (int i = 0; i < n; i++) nums[i] = rand() % 10;
		//int count = reversePairs(nums);
		//cout << nums << endl;
		c1 = reversePairs(nums);
		c2 = sol.reversePairs(nums);
		diff += abs(c1 - c2);
		//cout << c1 << ", " << c2 << ": " << abs(c1-c2) << endl;
	}
	cout << "Diff = " << diff << endl;
}