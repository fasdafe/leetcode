// LeetCode #321: Form Max Number From Two Arrays
#include "utils.h"

using namespace std;

vector<int>& maxVector_backward(vector<int>& v1, vector<int>& v2){
	for(int i = v1.size()-1; i >= 0; i--){
		if(v1[i] > v2[i]) return v1;
		else if(v1[i] < v2[i]) return v2;
	}
	return v1;
}

vector<int>& maxVector(vector<int>& v1, vector<int>& v2){
	for(int i = 0; i < v1.size(); i++){
		if(v1[i] > v2[i]) return v1;
		else if(v1[i] < v2[i]) return v2;
	}
	return v1;
}

vector<vector<int>> maxIndex(vector<int>& nums){
	int n = nums.size();
	vector<vector<int>> m(n, vector<int>(n));
	for(int i = 0; i < n; i++){
		m[i][i] = i;
		for(int j = i+1; j < n; j++){
			if(nums[m[i][j-1]] >= nums[j]) m[i][j] = m[i][j-1];
			else m[i][j] = j;
		}
	}
	return m;
}

vector<int> maxNumberDP(vector<int>& nums1, vector<int>& nums2, int k) {
	int m = nums1.size(), n = nums2.size();
	vector<vector<int>> max1 = maxIndex(nums1), max2 = maxIndex(nums2);
	vector<vector<vector<int>>> dp(m+1, vector<vector<int>>(n+1));
	for(int l = 1; l <= k; l++){
		cout << "l = " << l << endl;
		for(int i = 0; i <= m; i++){
			for(int j = 0; j <= min(n, m+n-i-l); j++){
				int p = min(m+n-j-l, m-1), q = min(m+n-i-l, n-1), m1 = i<m ? max1[i][p] : m-1, m2 = j<n ? max2[j][q] : n-1;
				vector<int> v1 = dp[m1+1][j], v2 = dp[i][m2+1];
				v1.push_back(i==m ? -1 : nums1[m1]);
				v2.push_back(j==n ? -1 : nums2[m2]);
				//dp[i][j] = maxVector_backward(v1, v2);
				if(j==n) dp[i][j] = v1;
				else {
					fill_n(dp[i].begin()+j, m2-j+1, maxVector_backward(v1, v2));
					j = m2;
				}

				cout << l << ", " << i+1 << ", " << j+1 << ": ";
				printVector(dp[i][j]);
			}
		}
	}
	vector<int> res = dp[0][0];
	reverse(res.begin(), res.end());
	return res;
}

void maxNumber(const vector<int>& nums, int start, int k, const vector<vector<int>>& mIdx, vector<int>& out){
	int n = nums.size();
	if(k == 0 || n-start < k) return;
	if(n-start == k) out.insert(out.end(), nums.begin()+start, nums.end());
	else {
		int next = mIdx[start][n-k];
		out.push_back(nums[next]);
		maxNumber(nums, next+1, k-1, mIdx, out);
	}
}

void helper2(const vector<int>& nums1, const vector<int>& nums2, int start1, int start2, int k, const vector<vector<int>>& mIdx1, const vector<vector<int>>& mIdx2, vector<int>& out){
	int n1 = nums1.size(), n2 = nums2.size();
	if(k == 0 || n1+n2-start1-start2 < k) return;
	if(start1 == n1) maxNumber(nums2, start2, k, mIdx2, out);
	else if(start2 == n2) maxNumber(nums1, start1, k, mIdx1, out);
	else {

	}

}

//vector<int> maxNumber2(vector<int>& nums1, vector<int>& nums2, int k) {
//	int m = nums1.size(), n = nums2.size();
//	vector<vector<int>> max1 = maxIndex(nums1), max2 = maxIndex(nums2);
//
//}

bool vectorLess(const vector<int>& v1, const vector<int>& v2, int start1, int start2){
	int n1 = v1.size(), n2 = v2.size();
	while(start1 < n1 && start2 < n2 && v1[start1]==v2[start2]) {start1++; start2++;}
	if(start1 >= n1) return true;
	else if(start2 >= n2) return false;
	else return v1[start1] < v2[start2];
}

vector<int> maxMerge(const vector<int>& v1, const vector<int>& v2){
	int n1 = v1.size(), n2 = v2.size();
	vector<int> res(n1+n2);
	for(int i = 0, j = 0, k = 0; k < n1+n2; ){
		if(j==n2) res[k++] = v1[i++];
		else if(i==n1) res[k++] = v2[j++];
		else if(v1[i]>v2[j]) res[k++] = v1[i++];
		else if(v1[i]<v2[j]) res[k++] = v2[j++];
		else{
			int p = i, q = j;
			while(p<n1 && q<n2 && v1[p]==v1[i] && v2[q]==v2[j]){
				res[k++] = v1[p];
				p++; q++;
			}
			if(vectorLess(v1, v2, p, q)) j = q;
			else i = p;
		}
	}
	//printVector(res);
	return res;
}

vector<int> maxMergeShort(const vector<int>& v1, const vector<int>& v2){
	int n1 = v1.size(), n2 = v2.size();
	vector<int> res(n1+n2);
	for(int i = 0, j = 0, k = 0; k < n1+n2; ){
		if(vectorLess(v1, v2, i, j)) res[k++] = v2[j++];
		else res[k++] = v1[i++];
		//if(j==n2) res[k++] = v1[i++];
		//else if(i==n1) res[k++] = v2[j++];
		//else if(v1[i]>v2[j]) res[k++] = v1[i++];
		//else if(v1[i]<v2[j]) res[k++] = v2[j++];
		//else{
		//	int p = i, q = j;
		//	while(p<n1 && q<n2 && v1[p]==v1[i] && v2[q]==v2[j]){
		//		res[k++] = v1[p];
		//		p++; q++;
		//	}
		//	if(vectorLess(v1, v2, p, q)) j = q;
		//	else i = p;
		//}
	}
	//printVector(res);
	return res;
}

//vector<int> maxNumber(const vector<int>& nums, int k){
//
//}

vector<int> maxNumber3(vector<int>& nums1, vector<int>& nums2, int k) {
	int m = nums1.size(), n = nums2.size();
	vector<vector<int>> max1 = maxIndex(nums1), max2 = maxIndex(nums2);
	vector<int> v1, v2, res(k, -1);
	for(int i = max(k-n, 0); i <= min(k, m); i++){
		v1.clear();
		v2.clear();
		maxNumber(nums1, 0, i, max1, v1);
		maxNumber(nums2, 0, k-i, max2, v2);
		//cout << "=====================>>>>" << endl;
		//printVector(v1);
		//printVector(v2);
		res = maxVector(res, maxMerge(v1, v2));
		//printVector(res);
	}
	return res;
}

vector<vector<int>> maxNumberSingleDP(const vector<int>& nums, int k){
	int n = nums.size();
	vector<vector<int>> dp(k+1); //dp[j] is the max number formed by j digits from nums[0~n-1]
	for(int j = k; j > 0; j--) dp[j] = vector<int>(j, -1);
	for(int i = n-1; i >= 0; i--){
		for(int j = min(k, n-i); j > 0; j--){
			if((i+j == n) || (dp[j][0] < nums[i]) || (dp[j][0] == nums[i] && vectorLess(dp[j], dp[j-1], 1, 0))){
				dp[j][0] = nums[i];
				copy(dp[j-1].begin(), dp[j-1].end(), dp[j].begin()+1);
			}
		}
	}
	return dp;
}

vector<int> maxNumberSingle(const vector<int>& nums, int k){
    int n = nums.size();
    vector<int> ans(k);
	//int old_j = 0;
    for (int i = 0, j = 0; i < n; ++i) {
        while (n - i + j > k && j > 0 && ans[j - 1] < nums[i]) j--;
        if (j < k) ans[j++] = nums[i];
		//cout << "i = " << i << ", j = " << j << ": ";
		//printVector(ans, old_j = max(old_j, j));
    }
    return ans;
}

vector<int> maxNumberSingle2(const vector<int>& nums, int k){
	// [4, 5, 3, 2, 1, 6, 0, 8]
	vector<int> res = nums;
	int inc = 0;
    while(res.size() > k){
		printVector(res);
	    while(inc < res.size()-1 && res[inc] >= res[inc+1]) inc++;
        res.erase(res.begin()+inc);
        if(inc) inc--;
    }
	printVector(res);
    return res;
}

vector<int> maxNumberSingle3(const vector<int>& nums, int k){
	list<int> res(nums.begin(), nums.end());
	int inc = 0, drop = nums.size()-k;
	auto it = res.begin();
	while(drop-- > 0){
		auto next = it;
		next++;
		printVector(vector<int>(res.begin(), res.end()));
		while(next != res.end() && *it >= *next) {it++; next++;}
		it = res.erase(it);
		if(it != res.begin()) it--;
	}
	printVector(vector<int>(res.begin(), res.end()));
	return vector<int>(res.begin(), res.end());
}

vector<int> maxNumber4(vector<int>& nums1, vector<int>& nums2, int k) {
	int m = nums1.size(), n = nums2.size();
	vector<vector<int>> max1 = maxNumberSingleDP(nums1, min(k, m)), max2 = maxNumberSingleDP(nums2, min(k, n));
	vector<int> cur(k), res(k, -1);
	for(int i = max(k-n, 0); i <= min(k, m); i++){
		cur = maxMerge(max1[i], max2[k-i]);
		if(!vectorLess(cur, res, 0, 0)) res = cur;
	}
	return res;
}

vector<int> maxNumber5(vector<int>& nums1, vector<int>& nums2, int k) {
	int m = nums1.size(), n = nums2.size();
	//vector<vector<int>> max1 = maxNumberSingleDP(nums1, min(k, m)), max2 = maxNumberSingleDP(nums2, min(k, n));
	vector<int> cur(k), res(k, -1);
	for(int i = max(k-n, 0); i <= min(k, m); i++){
		cur = maxMerge(maxNumberSingle(nums1, i), maxNumberSingle(nums2, k-i));
		if(!vectorLess(cur, res, 0, 0)) res = cur;
	}
	return res;
}

class Solution1{
public:
	vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {
	    int n1 = nums1.size(), n2 = nums2.size();
	    vector<int> best;
	    for (int k1=max(k-n2, 0); k1<=min(k, n1); ++k1)
	        best = max(best, maxNumber(maxNumber(nums1, k1),
	                                   maxNumber(nums2, k-k1)));
	    return best;
	}
	
	vector<int> maxNumber(vector<int> nums, int k) {
	    int drop = nums.size() - k;
	    vector<int> out;
	    for (int num : nums) {
	        while (drop && out.size() && out.back() < num) {
	            out.pop_back();
	            drop--;
	        }
	        out.push_back(num);
	    }
	    out.resize(k);
	    return out;
	}
	
	vector<int> maxNumber(vector<int> nums1, vector<int> nums2) {
	    vector<int> out;
	    while (nums1.size() + nums2.size()) {
	        vector<int>& now = nums1 > nums2 ? nums1 : nums2;
	        out.push_back(now[0]);
	        now.erase(now.begin());
	    }
	    return out;
	}
};

void testMaxNumber(){
	
	//int v1[] = {3,4,6,5}, v2[] = {9,1,2,5,8,3};
	int v1[] = {8,9,7,3,5,9,1,0,8,5,3,0,9,2,7,4,8,9,8,1,0,2,0,2,7,2,3,5,4,7,4,1,4,0,1,4,2,1,3,1,5,3,9,3,9,0,1,7,0,6,1,8,5,6,6,5,0,4,7,2,9,2,2,7,6,2,9,2,3,5,7,4,7,0,1,8,3,6,6,3,0,8,5,3,0,3,7,3,0,9,8,5,1,9,5,0,7,9,6,8,5,1,9,6,5,8,2,3,7,1,0,1,4,3,4,4,2,4,0,8,4,6,5,5,7,6,9,0,8,4,6,1,6,7,2,0,1,1,8,2,6,4,0,5,5,2,6,1,6,4,7,1,7,2,2,9,8,9,1,0,5,5,9,7,7,8,8,3,3,8,9,3,7,5,3,6,1,0,1,0,9,3,7,8,4,0,3,5,8,1,0,5,7,2,8,4,9,5,6,8,1,1,8,7,3,2,3,4,8,7,9,9,7,8,5,2,2,7,1,9,1,5,5,1,3,5,9,0,5,2,9,4,2,8,7,3,9,4,7,4,8,7,5,0,9,9,7,9,3,8,0,9,5,3,0,0,3,0,4,9,0,9,1,6,0,2,0,5,2,2,6,0,0,9,6,3,4,1,2,0,8,3,6,6,9,0,2,1,6,9,2,4,9,0,8,3,9,0,5,4,5,4,6,1,2,5,2,2,1,7,3,8,1,1,6,8,8,1,8,5,6,1,3,0,1,3,5,6,5,0,6,4,2,8,6,0,3,7,9,5,5,9,8,0,4,8,6,0,8,6,6,1,6,2,7,1,0,2,2,4,0,0,0,4,6,5,5,4,0,1,5,8,3,2,0,9,7,6,2,6,9,9,9,7,1,4,6,2,8,2,5,3,4,5,2,4,4,4,7,2,2,5,3,2,8,2,2,4,9,8,0,9,8,7,6,2,6,7,5,4,7,5,1,0,5,7,8,7,7,8,9,7,0,3,7,7,4,7,2,0,4,1,1,9,1,7,5,0,5,6,6,1,0,6,9,4,2,8,0,5,1,9,8,4,0,3,1,2,4,2,1,8,9,5,9,6,5,3,1,8,9,0,9,8,3,0,9,4,1,1,6,0,5,9,0,8,3,7,8,5};
	int v2[] = {7,8,4,1,9,4,2,6,5,2,1,2,8,9,3,9,9,5,4,4,2,9,2,0,5,9,4,2,1,7,2,5,1,2,0,0,5,3,1,1,7,2,3,3,2,8,2,0,1,4,5,1,0,0,7,7,9,6,3,8,0,1,5,8,3,2,3,6,4,2,6,3,6,7,6,6,9,5,4,3,2,7,6,3,1,8,7,5,7,8,1,6,0,7,3,0,4,4,4,9,6,3,1,0,3,7,3,6,1,0,0,2,5,7,2,9,6,6,2,6,8,1,9,7,8,8,9,5,1,1,4,2,0,1,3,6,7,8,7,0,5,6,0,1,7,9,6,4,8,6,7,0,2,3,2,7,6,0,5,0,9,0,3,3,8,5,0,9,3,8,0,1,3,1,8,1,8,1,1,7,5,7,4,1,0,0,0,8,9,5,7,8,9,2,8,3,0,3,4,9,8,1,7,2,3,8,3,5,3,1,4,7,7,5,4,9,2,6,2,6,4,0,0,2,8,3,3,0,9,1,6,8,3,1,7,0,7,1,5,8,3,2,5,1,1,0,3,1,4,6,3,6,2,8,6,7,2,9,5,9,1,6,0,5,4,8,6,6,9,4,0,5,8,7,0,8,9,7,3,9,0,1,0,6,2,7,3,3,2,3,3,6,3,0,8,0,0,5,2,1,0,7,5,0,3,2,6,0,5,4,9,6,7,1,0,4,0,9,6,8,3,1,2,5,0,1,0,6,8,6,6,8,8,2,4,5,0,0,8,0,5,6,2,2,5,6,3,7,7,8,4,8,4,8,9,1,6,8,9,9,0,4,0,5,5,4,9,6,7,7,9,0,5,0,9,2,5,2,9,8,9,7,6,8,6,9,2,9,1,6,0,2,7,4,4,5,3,4,5,5,5,0,8,1,3,8,3,0,8,5,7,6,8,7,8,9,7,0,8,4,0,7,0,9,5,8,2,0,8,7,0,3,1,8,1,7,1,6,9,7,9,7,2,6,3,0,5,3,6,0,5,9,3,9,1,1,0,0,8,1,4,3,0,4,3,7,7,7,4,6,4,0,0,5,7,3,2,8,5,1,4,5,8,5,6,7,5,7,3,3,9,6,8,1,5,1,1,1,0,3};
	//int v1[] = {6,7}, v2[] = {6,0,4};
	//int v1[] = {3,4,8,9,3,0}, v2[] = {6,1,9,1,1,2};
	//int v1[] = {3,4,6,5}, v2[] = {9,1,2,5,8,3};
	//int v1[] = {3,3,3,2,3,7,3,8,6,0,5,0,7,8,9,2,9,6,6,9,9,7,9,7,6,1,7,2,7,5,5,1}, v2[] = {5,6,4,9,6,9,2,2,7,5,4,3,0,0,1,7,1,8,1,5,2,5,7,0,4,3,8,7,3,8,5,3,8,3,4,0,2,3,8,2,7,1,2,3,8,7,6,7,1,1,3,9,0,5,2,8,2,8,7,5,0,8,0,7,2,8,5,6,5,9,5,1,5,2,6,2,4,9,9,7,6,5,7,9,2,8,8,3,5,9,5,1,8,8,4,6,6,3,8,4,6,6,1,3,4,1,6,7,0,8,0,3,3,1,8,2,2,4,5,7,3,7,7,4,3,7,3,0,7,3,0,9,7,6,0,3,0,3,1,5,1,4,5,2,7,6,2,4,2,9,5,5,9,8,4,2,3,6,1,9};
	//int v1[] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
	//int v2[] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
	vector<int> nums1(v1, v1+sizeof(v1)/sizeof(int)), nums2(v2, v2+sizeof(v2)/sizeof(int));
	//printVector(nums1);
	//printVector(nums2);
	int k = 500;//160;//5;//6;//100;//5;
	printVector(maxNumber5(nums1, nums2, k));
	//maxNumberSingle3(nums1, 0);
	//string s;
	while(true){
		cout << "test comparison of vectors (use format [a,b,c,...] to input vector items; enter two empty vectors to exit):" << endl;
		cout << "nums1 = ";
		cin >> nums1;
		cout << "nums1 = " << nums1 << endl;
		cout << "nums2 = ";
		cin >> nums2;
		cout << "nums2 = " << nums2 << endl;
		if(nums1.size() == 0 && nums2.size() == 0) break;
		cout << "[nums1 > nums2]  =  " << (nums1>nums2) << endl;
	}
	//cout << "[5,6,7] > [5,6]  ->  " << vector<
}