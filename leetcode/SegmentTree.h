#ifndef _intEGMENT_TREE_H_
#define _intEGMENT_TREE_H_

#include <queue>
#include <vector>

//template < class int >
class SegmentTree {
private:
	struct Node {
		int val;
		int start, end; // denote closed interval - [start, end]
		Node *left, *right;
		Node(int start, int end) : val(0), start(start), end(end), left(NULL), right(NULL) {}
	};
	Node *root;
	void build(Node* &root, int start, int end){
		root = new Node(start, end);
		if(start == end) return;
		int mid = start + (end - start) / 2;
		build(root->left, start, mid);
		build(root->right, mid+1, end);
	}
	int query(Node *node, int start, int end){
		if(start > node->end || end < node->start) return 0;
		else if(start <= node->start && end >= node->end) return node->val;
		else return query(node->left, start, end) + query(node->right, start, end);
	}
	int update(Node *node, int start, int end){
		if(node->start == node->end){
			if(start <= node->start && end >= node->end) node->val++;
		}
		else node->val = max(update(node->left, start, end), update(node->right, start, end));
		return node->val;
	}
public:
	SegmentTree() : root(NULL) {}
	SegmentTree(int start, int end) : root(NULL) {
		if(start < end) build(root, start, end);
	}
	int query(int start, int end){
		return query(root, start, end);
	}
	int update(int start, int end){
		return update(root, start, end);
	}
};

//typedef SegmentTree<int> IntSegTree;

#endif // _intEGMENT_TREE_H_