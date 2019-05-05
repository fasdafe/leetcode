// #124
#include "utils.h"
using namespace std;

class Solution {
public:
    int maxPathSum(TreeNode* root) {
		int l, r;
		return findMaxSum(root, l, r);
	}

	int findMaxSum(TreeNode *root, int &maxL, int &maxR) {
		maxL = maxR = INT_MIN;
		if (!root) return INT_MIN;
		int ll, lr, rl, rr;
		int m1 = findMaxSum(root->left, ll, lr);
		int m2 = findMaxSum(root->right, rl, rr);
		if(root->left) maxL = max(max(ll, lr), 0) + root->left->val;
		if(root->right) maxR = max(max(rl, rr), 0) + root->right->val;
		return max(max(m1, m2), max(maxL, 0) + max(maxR, 0) + root->val);
	}
};