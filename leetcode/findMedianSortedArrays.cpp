// #4

#include "utils.h"

using namespace std;

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size(), n = nums2.size(), left = (m + n + 1) / 2, right = (m + n + 2) / 2;
        return (findKth(nums1, 0, nums2, 0, left) + findKth(nums1, 0, nums2, 0, right)) / 2.0;
    }
    int findKth(vector<int>& nums1, int i, vector<int>& nums2, int j, int k) {
        if (i >= nums1.size()) return nums2[j + k - 1];
        if (j >= nums2.size()) return nums1[i + k - 1];
        if (k == 1) return min(nums1[i], nums2[j]);
        int midVal1 = (i + k / 2 - 1 < nums1.size()) ? nums1[i + k / 2 - 1] : INT_MAX;
        int midVal2 = (j + k / 2 - 1 < nums2.size()) ? nums2[j + k / 2 - 1] : INT_MAX;
        if (midVal1 < midVal2) {
            return findKth(nums1, i + k / 2, nums2, j, k - k / 2);
        } else {
            return findKth(nums1, i, nums2, j + k / 2, k - k / 2);
        }
    }
};

void testFindMedianSortedArrays(){
	int m, n;
	cout << "Provide length of two arrays:";
	cin >> m >> n;
	srand(time(0));
	vector<int> nums1, nums2;
	for(int i = 0; i < m; i++) nums1.push_back(rand()%20);
	for(int i = 0; i < n; i++) nums2.push_back(rand()%20);
	sort(nums1.begin(), nums1.end());
	sort(nums2.begin(), nums2.end());
	Solution mysol;
	double med = mysol.findMedianSortedArrays(nums1, nums2);
	cout << nums1 << endl << nums2 << endl;
	cout << "The median is " << med << endl;
}