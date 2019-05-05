// #116
#include "utils.h"

using namespace std;

// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() {}

    Node(int _val, Node* _left, Node* _right, Node* _next) {
        val = _val;
        left = _left;
        right = _right;
        next = _next;
    }
};

class Solution {
public:
	Node* connect(Node *root) { // the tree is assumed to be perfectly balanced
		if (!root || !root->left) return root;
		connect(root->left);
		connect(root->right);
		Node *left = root->left, *right = root->right;
		while (left) {
			left->next = right;
			left = left->right;
			right = right->left;
		}
		return root;
	}
};

class Solution1 {
public:
	Node* connect(Node *root) { // the tree is assumed to be perfectly balanced
		if (!root || !root->left) return root;
		if(root->left) root->left->next = root->right;
		if(root->right && root->next) root->right->next = root->next->left;
		connect(root->left);
		connect(root->right);
		return root;
	}
};

class Solution2 {
public:
	Node* connect(Node *root) { // the tree is assumed to be perfectly balanced
		Node *ans = root, *next;
		while(root && root->left){
			next = root->left;
			while(root){
				root->left->next = root->right;
				if(root->next) root->right->next = root->next->left;
				root = root->next;
			}
			root = next;
		}
		return ans;
	}
};