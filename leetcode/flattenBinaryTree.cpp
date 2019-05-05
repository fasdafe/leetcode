// #114
#include "utils.h"
using namespace std;

class SolutionStack {
public:
    void flatten(TreeNode* root) {
        if(!root) return;
        stack<TreeNode*> st;
        st.push(root);
        TreeNode *cur = NULL, *prev = NULL;
        while(!st.empty()){
            cur = st.top();
            st.pop();
            if(cur->right) st.push(cur->right);
            if(cur->left) st.push(cur->left);
            if(prev) {
                prev->right = cur;
                prev->left = NULL;
            }
            prev = cur;
        }
    }
};

class SolutionNoStack {
public:
    void flatten(TreeNode* root) {
        if(!root) return;
        TreeNode *cur = root, *iter;
        while(cur){
            if(cur->left) {
                iter = cur->left;
                while(iter->right) iter = iter->right;
                iter->right = cur->right;
                cur->right = cur->left;
                cur->left = NULL;
            }
            cur = cur->right;
        }
    }
};

class SolutionGenius {
public:
    void flatten(TreeNode* root) {
        TreeNode* prev = NULL;
        flatten(root, prev);
    }
private:
    void flatten(TreeNode* root, TreeNode*& prev) {
        if (!root) {
            return;
        }
        flatten(root -> right, prev);
        flatten(root -> left, prev);
        root -> right = prev;
        root -> left = NULL;
        prev = root;
    }
};