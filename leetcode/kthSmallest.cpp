// 230
#include "utils.h"
using namespace std;

class Solution {
public:
    int kthSmallest(TreeNode* root, int k) {
        if(!root) return 0;
        stack<TreeNode*> st;
		TreeNode *cur = root;
		while(cur || !st.empty()){
			while(cur){
				st.push(cur);
				cur = cur->left;
			}
			cur = st.top();
			st.pop();
			if(--k == 0) return cur->val;
			cur = cur->right;
		}
		return 0;
    }
};

class SolutionDivideAndConquer {
public:
    int kthSmallest(TreeNode* root, int k) {
        int cnt = count(root->left);
        if (k <= cnt) {
            return kthSmallest(root->left, k);
        } else if (k > cnt + 1) {
            return kthSmallest(root->right, k - cnt - 1);
        }
        return root->val;
    }
    int count(TreeNode* node) {
        if (!node) return 0;
        return 1 + count(node->left) + count(node->right);
    }
};

/* Follow up:
What if the BST is modified (insert/delete operations) often and you 
need to find the kth smallest frequently? How would you optimize the 
kthSmallest routine?
*/

