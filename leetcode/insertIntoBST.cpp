// #701

#include "utils.h"

using namespace std;

class Solution {
public:
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        if(!root) {
			root = new TreeNode(val);
			return root;
		}
		TreeNode *prev = NULL, *cur = root;
		stack<TreeNode*> st;
		while(cur || !st.empty()) {
			while(cur) {
				st.push(cur);
				cur = cur->left;
			}
			cur = st.top();
			st.pop();
			// visit cur
			if(!prev && cur->val > val){
				cur->left = new TreeNode(val);
				break;
			}
			else if(prev && prev->val < val && cur->val > val){
				if(!prev->right) prev->right = new TreeNode(val);
				else if(!cur->left) cur->left = new TreeNode(val);
				break;
			}
			prev = cur;
			cur = cur->right;
		}
		if(!cur && st.empty() && prev->val < val) 
            prev->right = new TreeNode(val);
		return root;
    }
};

class SolutionRecursive {
public:
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        if(!root) root = new TreeNode(val);
		else if(root->val > val) root->left = insertIntoBST(root->left, val);
		else root->right = insertIntoBST(root->right, val);
		return root;
    }
};

class SolutionIteration2 {
public:
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        if (!root) return new TreeNode(val);
        TreeNode *cur = root;
        while (true) {
            if (cur->val > val) {
                if (!cur->left) {cur->left = new TreeNode(val); break;}
                cur = cur->left;
            } else {
                if (!cur->right) {cur->right = new TreeNode(val); break;}
                cur = cur->right;
            }
        }
        return root;
    }
};