// 654
#include "utils.h"

using namespace std;

class Solution {
public:
	TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
		int n = nums.size();
		TreeNode* root = NULL, * node;
		stack<TreeNode*> st;
		for (int i = 0; i < n; ++i) {
			node = new TreeNode(nums[i]);
			if (root == NULL) root = node;
			else {
				while (!st.empty() && st.top()->val < nums[i]) st.pop();
				if (st.empty()) {
					node->left = root;
					root = node;
				}
				else {
					node->left = st.top()->right;
					st.top()->right = node;
				}
			}
			st.push(node);
		}
		return root;
	}
};