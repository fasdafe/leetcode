// LeetCode #368: Largest Divisible Subset

#include "utils.h"

using namespace std;


vector<int> largestDivisibleSubset(vector<int>& nums) {
	size_t n = nums.size();
	if(n < 2) return nums;
	sort(nums.begin(), nums.end());
	vector<int> a(n); //a[i] = length of longest divisible subset that ends with nums[i]
	a[0] = 1;
	vector<int> m(n);
	m[0] = -1;
	int prevMax, maxIndex = 0;
	for(size_t i = 1; i < n; i++){
		prevMax = 0;
		m[i] = -1;
		for(size_t j = 0; j < i; j++){
			if(nums[i]%nums[j] == 0 && a[j] > prevMax){
				prevMax = a[j];
				m[i] = j;
			}
		}
		a[i] = prevMax + 1;
		if(a[i] > a[maxIndex]) maxIndex = i;
	}
	vector<int> res(a[maxIndex]);
	for(int i = maxIndex, j = a[maxIndex]-1; i >= 0 && j >= 0; i = m[i], j--){
		res[j] = nums[i];
	}
	return res;
}

void testLargestDivSubset(){
	int a[] = {1,2,3};
	vector<int> v(a, a+3);
	cout << "-------------------" << endl;
	printVector(v);
	cout << "largest divisible subset is:" << endl;
	printVector(largestDivisibleSubset(v));
	
	int b[] = {1,2,3,4,5,6,7,8,9,27,54};
	v = vector<int>(b, b+11);
	cout << "-------------------" << endl;
	printVector(v);
	cout << "largest divisible subset is:" << endl;
	printVector(largestDivisibleSubset(v));
}