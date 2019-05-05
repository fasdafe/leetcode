// #315

#include "utils.h"

using namespace std;

class Solution {
public:
    vector<int> countSmaller(vector<int>& nums) {
		int n = nums.size();
        vector<int> count(n), sorted;
		for(int i = n-1; i >= 0; i--){
			count[i] = insert(sorted, nums[i]);
		}
		return count;
    }

	int insert(vector<int>& sorted, int num){
		auto it = lower_bound(sorted.begin(), sorted.end(), num);
		int res = it-sorted.begin();
		sorted.insert(it, num);
		return res;
	}
};

// Binary Search Tree
class SolutionBST {
public:
    struct Node {
        int val, smaller;
        Node *left, *right;
        Node(int v, int s) : val(v), smaller(s), left(NULL), right(NULL) {}
    };
    int insert(Node *&root, int v) {
        if (!root) return (root = new Node(v, 0)), 0;
        if (root->val > v) return root->smaller++, insert(root->left, v);
        else return insert(root->right, v) + root->smaller + (root->val < v ? 1 : 0);
    }
    vector<int> countSmaller(vector<int>& nums) {
        vector<int> res(nums.size());
        Node *root = NULL;
        for (int i = nums.size() - 1; i >= 0; --i) {
            res[i] = insert(root, nums[i]);
        }
        return res;
    }
};

// When compared with a flat array of numbers, the Fenwick tree achieves 
// a much better balance between two operations: element update and prefix 
// sum calculation. In a flat array of n numbers, you  can either store
// the elements, or the prefix sums. In the first case, computing prefix
// sums requires linear time; in the second case, updating the array 
// elements requires linear time (in both cases, the other operation can 
// be performed in constant time).

// Fenwick trees allow both operations to be performed in O(log(n)) time. 
// This is achieved by representing the numbers as a tree, where the value 
// of each node is the sum of the numbers in that subtree. The tree 
// structure allows operations to be performed using only O(log(n)) node 
// accesses.

#define LSB(i) ((i) & -(i)) // zeroes all the bits except the least significant one
class FenwickTree{ // Binary Indexed Tree
private:
	int sz;
	vector<int> A;
public:
	
	FenwickTree(int N) : sz(N+1), A(vector<int>(N+1, 0)) {}

	int sum(int i) // Returns the sum from index 1 to i
	{
	    int sum = 0;
	    while (i > 0) 
	        sum += A[i], i -= LSB(i);
	    return sum;
	}
	 
	void add(int i, int k) // Adds k to element with index i
	{
	    while (i < sz) 
	        A[i] += k, i += LSB(i);
	}
};

class SolutionBIT {
public:
	vector<int> countSmaller(vector<int>& nums){
		int n = nums.size();
		vector<int> res(n);
		if(n == 0) return res;
		set<int> set(nums.begin(), nums.end());
		unordered_map<int, int> ranks;
		int rank = 0;
		for(auto item : set) ranks[item] = ++rank;
		FenwickTree fwTree(ranks.size());
		for(int i = n-1; i >= 0; i--){
			res[i] = fwTree.sum(ranks[nums[i]]-1);
			fwTree.add(ranks[nums[i]], 1);
		}
		return res;
	}
};


class SolutionMergeSort {
    typedef vector<pair<int, int>> Pii;
    typedef Pii::iterator Pit;
public:
    vector<int> countSmaller(vector<int>& nums) {
        int n = nums.size();
        vector<int> res(n);
        Pii nums_(n);
        for(int i = 0; i < n; ++i)
            nums_[i].first = nums[i], nums_[i].second = i;
        merge(nums_.begin(), nums_.end(), res);
        return res;
    }
    
    void merge(Pit begin, Pit end, vector<int>& res){
        if(end - begin <= 1)
            return;
        auto mid = begin + (end - begin) / 2;
        merge(begin, mid, res);
        merge(mid, end, res);
        for(auto i = begin, j = mid; i != mid; ++i){
            while(j != end && i->first > j->first)
                ++j;
            res[i->second] += j - mid;
        }
        inplace_merge(begin, mid, end);
    }
};