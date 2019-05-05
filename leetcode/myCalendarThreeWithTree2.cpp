// #732
#include "utils.h"
using namespace std;

class SegmentTree {
private:
	struct TreeNode {
	    int start, end;
	    TreeNode *left, *right;
	    /**
	     * How much number is added to this interval(node)
	     */
	    int booked;
	    /**
	     * The maximum number in this interval(node). 
	     */
	    int savedres;
		TreeNode(int s, int t) {
	        start = s;
	        end = t;
			left = NULL;
			right = NULL;
			booked = 0;
			savedres = 0;
	    }
		~TreeNode(){
			if(left) delete left;
			if(right) delete right;
		}
	    bool inside(TreeNode *b) {
	        if(b->start <= start && end <= b->end) {
	            return true;
	        }
	        return false;
	    }
	    bool intersect(TreeNode *b) {
	    	if(inside(b) || end <= b->start || b->end <= start) {
	            return false;
	        }
	        return true;
	    }
	};
    TreeNode *root;
	void add(TreeNode *root, TreeNode *event, int val) {
        if(root == NULL) {
            return ;
        }
        /**
         * If current node's range lies completely in update query range.
         */
        if(root->inside(event)) {
            root->booked += val;
            root->savedres += val;
        }
        /**
         * If current node's range overlaps with update range, follow the same approach as above simple update.
         */
        if(root->intersect(event)) {
        	// Recur for left and right children.
            int mid = (root->start + root->end) / 2;
            if(root->left == NULL) {
                root->left = new TreeNode(root->start, mid);
            }
            add(root->left, event, val);
            if(root->right == NULL) {
                root->right = new TreeNode(mid, root->end);
            }
            add(root->right, event, val);
            // Update current node using results of left and right calls.
            root->savedres = max(root->left->savedres, root->right->savedres) + root->booked;
        }
    }
public:
    SegmentTree(int left, int right) {
        root = new TreeNode(left, right);
    }
	~SegmentTree() {
		if(root) delete root;
	}
    void add(int start, int end, int val) {
        TreeNode *event = new TreeNode(start, end);
    	add(root, event, val);
    }
    int getMax() {
        return root->savedres;
    }
    /**
     * find maximum for nums[i] (start <= i <= end) is not required.
     * so i did not implement it. 
     */
    int get(int start, int right) {return 0;}

};

class MyCalendarThree {
private:
	SegmentTree *segmentTree;
public:
	MyCalendarThree() {
    	segmentTree = new SegmentTree(0, 1000000000);
    }
	~MyCalendarThree() {
		delete segmentTree;
	}
    int book(int start, int end) {
        segmentTree->add(start, end, 1);
        return segmentTree->getMax();
    }
};

void testMyCalendarThreeWithTree2() {
	MyCalendarThree cal;
	cout << cal.book(10, 20) << endl; // returns 1
	cout << cal.book(50, 60) << endl; // returns 1
	cout << cal.book(10, 40) << endl; // returns 2
	cout << cal.book(5, 15)  << endl; // returns 3
	cout << cal.book(5, 10)  << endl; // returns 3
	cout << cal.book(25, 55) << endl; // returns 3
}