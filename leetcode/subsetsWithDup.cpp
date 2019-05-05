// LeetCode #90: Subsets with Duplicates

#include "utils.h"

using namespace std;

vector<vector<int>> subsetsWithDup(vector<int>& nums) { // my solution
	unordered_map<int, int> m;
	for(auto &num : nums)
		m[num]++;
	int n = m.size();
	vector<int> sz(n+1);
	auto p = m.begin();
	sz[0] = 1;
	for(int i = 1; i <= n; i++, p++){
		sz[i] = sz[i-1]*(1+p->second);
	}
	vector<vector<int>> res(sz[n]);
	p = m.begin();
	for(int i = 1; i <= n; i++, p++){
		for(int j = 0; j < sz[n]; j += sz[i]){
			for(int l = sz[i-1]; l<sz[i]; l+=sz[i-1]){
				for(int k = l; k < sz[i]; k++){
					res[k+j].push_back(p->first);
				}
			}
		}
	}
	return res;
}

vector<vector<int>> subsetsWithDup1(vector<int> &S) {
	vector<vector<int>> totalset(1);
	sort(S.begin(),S.end());
	for(int i=0; i<S.size();){
		int count = 0; // num of elements are the same
		while(count + i<S.size() && S[count+i]==S[i])  count++;
		int previousN = totalset.size();
		for(int k=0; k<previousN; k++){
			vector<int> instance = totalset[k];
			for(int j=0; j<count; j++){
				instance.push_back(S[i]);
				totalset.push_back(instance);
			}
		}
		i += count;
	}
	return totalset;
}

vector<vector<int>> subsetsWithDup2(vector<int>& nums) {
	vector<vector<int>> ret;
	ret.push_back(vector<int>());
	sort(nums.begin(), nums.end());
	vector<vector<int>> sub;
	for (int i = 0; i < nums.size(); ++i) {
		if (i == 0 || nums[i] != nums[i-1]) sub = ret;
		for (auto& j:sub) j.push_back(nums[i]);
		ret.insert(ret.end(), sub.begin(), sub.end());
	}
	return ret;
}

void testSubsetsWithDup(){
	int nums1[] = {1, 2, 2};
	vector<int> nums(nums1, nums1+3);
	cout << "subsets of ";
	printVector(nums);
	for(auto &v : subsetsWithDup2(nums))
		printVector(v);

	
	int nums2[] = {5, 3, 1, 1, 5, 5};
	nums = vector<int>(nums2, nums2+6);
	cout << "subsets of ";
	printVector(nums);
	for(auto &v : subsetsWithDup2(nums))
		printVector(v);

}