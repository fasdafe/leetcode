// #783

#include "utils.h"

using namespace std;

class Solution {
public:
    int minDiffInBST(TreeNode* root) {
        if(!root) return -1;
        TreeNode *left, *right;
        return inOrder(root, left, right);
    }
    
    int inOrder(TreeNode* root, TreeNode* &left, TreeNode* &right){
        int minDiffL, minDiffR, minDiff;
        TreeNode *ll = NULL, *lr = NULL, *rl = NULL, *rr = NULL;
        if(root->left) {
            minDiffL = inOrder(root->left, ll, lr);
            left = ll;
        }
        else {
            minDiffL = INT_MAX;
            left = root;
        }
        if(root->right) {
            minDiffR = inOrder(root->right, rl, rr);
            right = rr;
        }
        else {
            minDiffR = INT_MAX;
            right = root;
        }
        minDiff = min(minDiffL, minDiffR);
        if(root->left && root->val - lr->val < minDiff)
            minDiff = root->val - lr->val;
        if(root->right && rl->val - root->val < minDiff)
            minDiff = rl->val - root->val;
        return minDiff;
    }
};

class SolutionRecursive {
  private:
    int res, pre;

  public:
	SolutionRecursive() : res(INT_MAX), pre(-1) {}

    int minDiffInBST(TreeNode* root) {
        if (root->left != NULL) minDiffInBST(root->left);
        if (pre >= 0) res = min(res, root->val - pre);
        pre = root->val;
        if (root->right != NULL) minDiffInBST(root->right);
        return res;
    }
};