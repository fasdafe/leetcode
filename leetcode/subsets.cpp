// LeetCode #78: Subsets

#include "utils.h"

using namespace std;

vector<vector<int>> subsets(vector<int>& nums) {
	int n = nums.size(), power2 = 1<<n;
	vector<vector<int>> res(power2);
	for(int j = 0; j < n; j++){
		for(int i = 0, k = (1<<j); i < power2; i++){
			if(k&i) res[i].push_back(nums[j]);
		}
	}
	return res;
}

void testSubsets(){

	vector<int> nums;
	vector<vector<int>> res;
	int n[] = {4,5,6};
	for(int i = 0; i < sizeof(n)/sizeof(int); i++){
		nums.clear();
		for(int j = 0; j < n[i]; j++){
			nums.push_back(j+1);
		}
		res = subsets(nums);
		cout << "--------------------------------------" << endl << "subsets of ";
		printVector(nums);
		for(auto &item : res)
			printVector(item);
	}

}