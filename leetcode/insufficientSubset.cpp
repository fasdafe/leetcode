// 5084: https://leetcode.com/contest/weekly-contest-140/problems/insufficient-nodes-in-root-to-leaf-paths/

#include "utils.h"
using namespace std;

class Solution {
public:
	TreeNode* sufficientSubset(TreeNode* root, int limit) {
		if (!root) return nullptr;
		// cout << root->val << endl;
		if (!root->left && !root->right)
			return root->val < limit ? nullptr : root;
		root->left = sufficientSubset(root->left, limit - root->val);
		root->right = sufficientSubset(root->right, limit - root->val);
		return (!root->left && !root->right) ? nullptr : root;
	}
};