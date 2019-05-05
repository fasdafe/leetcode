// #98

#include "utils.h"

using namespace std;

class Solution {
public:
    bool isValidBST(TreeNode* root) {
        if(!root) return true;
        stack<TreeNode*> st;
        TreeNode *cur = root, *prev = NULL;
        while(cur) {
            st.push(cur);
            cur = cur->left;
        }
        while(!st.empty()) {
            cur = st.top();
            st.pop();
            if(prev && prev->val >= cur->val) return false;
            prev = cur;
            cur = cur->right;
            while(cur) {
                st.push(cur);
                cur = cur->left;
            }
        }
        return true;
    }
};

class Solution1 {
public:
    bool isValidBST(TreeNode* root) {
        if(!root) return true;
        stack<TreeNode*> st;
        TreeNode *cur = root, *prev = NULL;
        while(cur || !st.empty()) {
            while(cur) {
                st.push(cur);
                cur = cur->left;
            }
            cur = st.top();
            st.pop();
            if(prev && prev->val >= cur->val) return false;
            prev = cur;
            cur = cur->right;
        }
        return true;
    }
};

void testIsValidBST(){
	vector<string> treeStr;
	cin >> treeStr;
	TreeNode *root = buildBinaryTree<int>(treeStr);
	Solution1 mysol;
	cout << mysol.isValidBST(root) << endl;
	//printBinaryTree(root, false);
}