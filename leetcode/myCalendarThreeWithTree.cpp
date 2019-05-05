// #732
#include "utils.h"
//#include "SegmentTree.h"
using namespace std;

class SegmentTree {
private:
	struct Node {
		int val;
		int start, end; // denote closed interval - [start, end)
		Node *left, *right;
		Node(int start, int end, int val = 0) : val(val), start(start), end(end), left(NULL), right(NULL) {}
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
		return 0;
	}
	void update(Node* &node, int start, int end, int val = 0){
		if(start >= end) return;
		if(!node && start < end) {
			node = new Node(start, end, 0);
			return;
		}
		if(start >= node->end || end <= node->start) return;
		if(start == node->start && end == node->end) return; //node->val++;
		update(node->left, node->start, start);
		update(node->right, start, node->end);

/*
		if(node->left){
			update(node->left, start, node->left->end);
			update(node->right, node->right->start, end);
		}
		else {
			if(node->start < start) {
				node->left = new Node(node->start, start);
				node->left->val = node->val;
				node->right = new Node(start, node->end);
				node->right->val = node->val;
				update(node->right, start, end);
			}
			else{
				node->left = new Node(start, end);
				node->left->val = node->val+1;
				node->right = new Node(end, node->end);
				node->right->val = node->val;
			}
		}*/
		//if(start > node->start)
	}
	void clear(Node *node){
		if(!node) return;
		clear(node->left);
		clear(node->right);
		delete node;
	}
public:
	SegmentTree() : root(NULL) {}
	SegmentTree(int start, int end) : root(NULL) {
		if(start <= end) root = new Node(start, end);
	}
	~SegmentTree() { clear(root); }
	int query(int start, int end){
		return 0;
	}
	int update(int start, int end){
		update(root, start, end);
		return 0;
	}
};

class MyCalendarThreeWithTree {
private:
	SegmentTree *events;
public:
	MyCalendarThreeWithTree() : events(new SegmentTree(0, 1e9)) {}
	~MyCalendarThreeWithTree() {
		delete events;
	}
	int book(int start, int end) {
		return events->update(start, end);
	}
};

void testMyCalendarThreeWithTree() {
	//MyCalendarThreeWithTree cal;
	//cout << cal.book(10, 20) << endl; // returns 1
	//cout << cal.book(50, 60) << endl; // returns 1
	//cout << cal.book(10, 40) << endl; // returns 2
	//cout << cal.book(5, 15)  << endl; // returns 3
	//cout << cal.book(5, 10)  << endl; // returns 3
	//cout << cal.book(25, 55) << endl; // returns 3
}