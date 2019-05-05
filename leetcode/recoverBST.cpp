// #99

#include "utils.h"

using namespace std;

class Solution {
public:
    void recoverTree(TreeNode* root) {
        TreeNode *left = NULL, *right = NULL, *max1 = NULL, *max2 = NULL;
        findMisplace(root, left, right, max1, max2);
		if(max2 == NULL) max2 = max1;
		//while (max2->left != NULL) max2 = max2->left;
		//max2 = findNext(max2);
		if(root) max2 = findNext(root, max2);
		//cout << endl;
        if(max1) cout << max1->val << ", ";
        if(max2) cout << max2->val << endl;
		swap(max1->val, max2->val);
    }
    
	TreeNode* findNext(TreeNode *root, TreeNode *node){
		TreeNode *next = NULL;
		inOrder(root, node, next);
		return next;
	}

	void inOrder(TreeNode *node, TreeNode *target, TreeNode* &next){
		if(node->left != NULL) inOrder(node->left, target, next);
		if(next != NULL) {
			next = node; 
			return;
		}
		if(node == target) next = target;
		if(node->right != NULL) inOrder(node->right, target, next);
	}

    void findMisplace(TreeNode* root, TreeNode* &left, TreeNode* &right, TreeNode* &max1, TreeNode* &max2) {
        if(root == NULL || (root->left == NULL && root->right == NULL)) {
            left = root;
            right = root;
            return;
        }
        if(root->left == NULL){
            left = root;
            TreeNode *node;
            findMisplace(root->right, node, right, max1, max2);
            if(left->val > node->val){
                if(max1) max2 = max1;
                max1 = left;
            }
        }
        else if(root->right == NULL){
            right = root;
            TreeNode *node;
            findMisplace(root->left, left, node, max1, max2);
            if(node->val > right->val){
                if(max1) max2 = node;
                else max1 = node;
            }
        }
        else{
            TreeNode *node1;
            findMisplace(root->left, left, node1, max1, max2);
            if(max1 != NULL && max2 != NULL) return;
            else if(max1 != NULL && node1->val > root->val){
                max2 = node1;
                findMisplace(root->right, node1, right, max1, max2);
                // right = ?
                return;
            }
            else{
                TreeNode *node2 = NULL, *node3 = NULL;
                findMisplace(root->right, node2, right, node3, max2);
				if(node1->val > root->val) max1 = node1;
				if(root->val > node2->val) {
					if(max1) max2 = root;
					else max1 = root;
				}
                if(max1 == NULL) max1 = node3;
                else if(node3) max2 = node3;
            }
        }
    }
};


class Solution1 {
public:
    void recoverTree(TreeNode* root) {
        
        stack<TreeNode*> st;
        TreeNode *prev, *saved1 = NULL, *saved2 = NULL, *cur = root;
        while(cur != NULL){
            st.push(cur);
            cur = cur->left;
        }
        prev = st.top();
        while(!st.empty()){
            cur = st.top();
            st.pop();
            // visit cur
            if(prev->val > cur->val){
                if(saved1 == NULL) saved1 = prev;
                saved2 = cur;
            }
            prev = cur;
            cur = cur->right;
            while(cur != NULL){
                st.push(cur);
                cur = cur->left;
            }
        }
        swap(saved1->val, saved2->val);
    }
};


class SolutionMorris {
public:
    void recoverTree(TreeNode* root) {
        TreeNode *next = NULL, *prev = NULL, *saved1 = NULL, *saved2 = NULL, *cur = root;
        while(cur != NULL) {
            if(cur->left) {
                next = cur;
                cur = cur->left;
                while(cur->right && cur->right != next) cur = cur->right;
                if(cur->right == NULL) {
                    cur->right = next;
                    cur = next->left;
                }
                else {
                    cur->right = NULL;
                    // visit next here
                    if(prev->val > next->val){
                        if(saved1 == NULL) saved1 = prev;
                        saved2 = next;
                    }
                    prev = next;
                    cur = next->right;
                }
            }
            else {
                // visit cur here
                if(prev && prev->val > cur->val) {
                    if(saved1 == NULL) saved1 = prev;
                    saved2 = cur;
                }
                prev = cur;
                cur = cur->right;
            }
        }
        swap(saved1->val, saved2->val);
    }
};


void testRecoverBST(){
	vector<string> treeStr;
	cin >> treeStr;
	TreeNode *root = buildBinaryTree<int>(treeStr);
	SolutionMorris mysol;
	mysol.recoverTree(root);
	printBinaryTree(root, false);
}

