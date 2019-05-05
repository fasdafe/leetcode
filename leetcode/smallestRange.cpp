// #632 https://leetcode.com/problems/smallest-range/
// Example 1:
// Input:[[4,10,15,24,26], [0,9,12,20], [5,18,22,30]]
// Output: [20,24]
// Explanation: 
// List 1: [4, 10, 15, 24,26], 24 is in range [20,24].
// List 2: [0, 9, 12, 20], 20 is in range [20,24].
// List 3: [5, 18, 22, 30], 22 is in range [20,24].

#include "utils.h"
using namespace std;

class Solution {
public:
    vector<int> smallestRange(vector<vector<int>>& nums) {
        int k = nums.size();
        vector<int> next(k, 0);
        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;
        int kmax = INT_MIN;
        for(int i = 0; i < k; i++) {
			vector<int> temp(2);
			temp[0] = nums[i][0];
			temp[1] = i;
            pq.push(temp);
            kmax = max(kmax, nums[i][0]);
        }
        vector<int> res(2);
        res[0] = 0;
        res[1] = INT_MAX;
        
        while(1) {
            int i = pq.top()[1];
            if(kmax - pq.top()[0] < res[1] - res[0]) {
                res[0] = pq.top()[0];
                res[1] = kmax;
            }
            next[i]++;
            if(next[i] >= nums[i].size()) break;
            kmax = max(kmax, nums[i][next[i]]);
            pq.pop();
			vector<int> temp(2);
			temp[0] = nums[i][next[i]];
			temp[1] = i;
            pq.push(temp);
        }
        
        return res;
    }
};

class Solution1 { // much faster than Solution
    struct cmp {
        bool operator()(pair<int, int>& a, pair<int, int>& b) {
            return a.first > b.first;
        }
    };
public:
    vector<int> smallestRange(vector<vector<int>>& nums) {
        int k = nums.size();
        vector<int> next(k, 0);
        priority_queue<pair<int, int>, vector<pair<int, int>>, cmp> pq;
        int kmax = INT_MIN;
        for(int i = 0; i < k; i++) {
            pq.push(make_pair(nums[i][0], i));
            kmax = max(kmax, nums[i][0]);
        }
        vector<int> res(2);
        res[0] = 0;
        res[1] = INT_MAX;
        
        while(1) {
            int i = pq.top().second;
            if(kmax - pq.top().first < res[1] - res[0]) {
                res[0] = pq.top().first;
                res[1] = kmax;
            }
            next[i]++;
            if(next[i] >= nums[i].size()) break;
            kmax = max(kmax, nums[i][next[i]]);
            pq.pop();
            pq.push(make_pair(nums[i][next[i]], i));
        }
        
        return res;
    }
};

class Solution2 {
public:
	vector<int> smallestRange(vector<vector<int>>& nums) {
		int n=nums.size();
		vector<int> res(2);
		vector<pair<int,int>> arr;
		for(int i=0; i<n; i++){
			for(int j : nums[i]){
				arr.push_back(make_pair(j, i));
			}
		}
		sort(arr.begin(), arr.end());
		int start = 0, cnt = 0, diff = INT_MAX;
		vector<int> m(n, 0);
		for(int i=0; i<arr.size(); i++){
			if(m[arr[i].second]++ == 0) cnt++;
			while(cnt == n && start <= i){
				if(diff > (arr[i].first - arr[start].first)){
					diff = arr[i].first - arr[start].first;
					res[0] = arr[start].first;
					res[1] = arr[i].first;
				}
				if(--m[arr[start].second] == 0) cnt--;
				start++;
			}
		}
		return res;
	}
};

void testSmallestRange() {
	// [[4,10,15,24,26],[0,9,12,20],[5,18,22,30]]
	vector<vector<int>> nums;
	cin >> nums;
	Solution2 mysol;
	vector<int> range = mysol.smallestRange(nums);
	cout << range << endl;
}