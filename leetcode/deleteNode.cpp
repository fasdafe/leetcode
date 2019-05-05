// #450

#include "utils.h"
using namespace std;

class Solution {
public:
    TreeNode* deleteNode(TreeNode* root, int key) {
        if(!root) return NULL;
		else if(root->val > key) root->left = deleteNode(root->left, key);
		else if(root->val < key) root->right = deleteNode(root->right, key);
		else{
			if(!root->left) return root->right;
			if(!root->right) return root->left;
			TreeNode *node = root->left;
			if(!node->right){
				node->right = root->right;
				delete root;
				return node;
			}
			else{
				while(node->right->right) node = node->right;
				TreeNode *temp = node->right;
				node->right = temp->left;
				temp->left = root->left;
				temp->right = root->right;
				delete root;
				return temp;
			}
		}
		return root;
    }

};

class SolutionInterative {
public:
    TreeNode* deleteNode(TreeNode* root, int key) {
        //if(!root) return NULL;

		TreeNode *cur = root, *prev = NULL;
		while(cur && cur->val != key){
			prev = cur;
			if(cur->val > key) cur = cur->left;
			else cur = cur->right;
		}
		if(!cur) return root;
		//else if(root->val > key) root->left = deleteNode(root->left, key);
		//else if(root->val < key) root->right = deleteNode(root->right, key);
		else{
			if(!cur->left){
				if(!prev) return root->right; // cur = root
				else{
					if(prev->left == cur) prev->left = cur->right;
					else prev->right = cur->right;
					delete cur;
					return root;
				}
			}
			if(!cur->right){
				if(!prev) return root->left;
				else{
					if(prev->left == cur) prev->left = cur->left;
					else prev->right = cur->left;
					delete cur;
					return root;
				}
			}

			TreeNode *node = cur->left;
			if(!node->right){
				if(prev->left == cur) prev->left = node;
				else prev->right = node;
				node->right = cur->right;
				delete cur;
				return node;
			}
			else{
				while(node->right->right) node = node->right;
				TreeNode *temp = node->right;
				node->right = temp->left;
				temp->left = root->left;
				temp->right = root->right;
				delete root;
				return temp;
			}
		}
		return root;
    }

};