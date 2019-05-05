// #327 Hard

#include "utils.h"

using namespace std;

class Solution { // time complexity O(n*log^2(n))
public:
    int countRangeSum(vector<int>& nums, int lower, int upper) {
		if(nums.size() == 0) return 0;
		vector<int> leftSum, rightSum;
        return mergeAndCount(nums, 0, nums.size()-1, leftSum, rightSum, lower, upper);
    }

	int mergeAndCount(const vector<int>& nums, int left, int right, vector<int>& leftSum, 
		vector<int>& rightSum, int lower, int upper)
	{
		if(left == right){
			leftSum.clear();
			leftSum.push_back(nums[left]);
			rightSum.clear();
			rightSum.push_back(nums[left]);
			if(nums[left] >= lower && nums[left] <= upper) return 1;
			else return 0;
		}
		int mid = left + (right-left)/2;
		vector<int> llSum, lrSum, rlSum, rrSum;
		int c1 = mergeAndCount(nums, left, mid, llSum, lrSum, lower, upper);
		int c2 = mergeAndCount(nums, mid+1, right, rlSum, rrSum, lower, upper);
		leftSum.resize(right-left+1);
		copy(llSum.begin(), llSum.end(), leftSum.begin());
		for(int i = mid-left+1; i < right-left+1; i++){
			leftSum[i] = llSum.back() + rlSum[i-mid+left-1];
		}
		rightSum.resize(right-left+1);
		copy(rrSum.begin(), rrSum.end(), rightSum.begin()+mid-left+1);
		for(int i = 0; i < mid-left+1; i++){
			rightSum[i] = lrSum[i] + rrSum.front();
		}
		return c1 + c2 + count(lrSum, rlSum, lower, upper);
	}

	int count(vector<int>& numsL, vector<int>& numsR, int lower, int upper){
		sort(numsL.begin(), numsL.end());
		sort(numsR.begin(), numsR.end());
		int c = 0;
		for(auto k : numsL){
			c += upper_bound(numsR.begin(), numsR.end(), upper-k) - lower_bound(numsR.begin(), numsR.end(), lower-k);
		}
		return c;
	}
};

class SolutionMultiSet { // time and space complexity O(n*log(n))
public:
    int countRangeSum(vector<int>& nums, int lower, int upper) {
        int res = 0;
        long sum = 0;
        multiset<long> sums;
        sums.insert(0);
        for (int i = 0; i < nums.size(); ++i) {
            sum += nums[i];
            res += distance(sums.lower_bound(sum - upper), sums.upper_bound(sum - lower));
            sums.insert(sum);
        }
        return res;
    }        
};

class SolutionMergeSort { // time and space complexity O(n*log(n))
public:
    int countRangeSum(vector<int>& nums, int lower, int upper) {
        vector<long> sums(nums.size() + 1, 0);
        for (int i = 0; i < nums.size(); ++i) {
            sums[i + 1] = sums[i] + nums[i];
        }
        return countAndMergeSort(sums, 0, sums.size(), lower, upper);
    }
    int countAndMergeSort(vector<long> &sums, int start, int end, int lower, int upper) {
        if (end - start <= 1) return 0;
        int mid = start + (end - start) / 2;
        int cnt = countAndMergeSort(sums, start, mid, lower, upper) + countAndMergeSort(sums, mid, end, lower, upper);
        int j = mid, k = mid, t = mid;
        vector<int> cache(end - start, 0);
        for (int i = start, r = 0; i < mid; ++i, ++r) {
            while (k < end && sums[k] - sums[i] < lower) ++k;
            while (j < end && sums[j] - sums[i] <= upper) ++j;
            while (t < end && sums[t] < sums[i]) cache[r++] = sums[t++];
            cache[r] = sums[i];
            cnt += j - k;
        }
        copy(cache.begin(), cache.begin() + t - start, sums.begin() + start);
        return cnt;
    }
};