// 1019

#include "utils.h"

using namespace std;

// Definition for singly-linked list.
struct ListNode {
	int val;
	ListNode* next;
	ListNode(int x) : val(x), next(NULL) {}
};
 
class Solution {
public:
	vector<int> nextLargerNodes(ListNode* head) {
		vector<int> res;
		head = reverseList(head);
		ListNode* node = head;
		stack<int> st;
		while (node) {
			while (!st.empty() && st.top() <= node->val) st.pop();
			if (st.empty()) res.push_back(0);
			else res.push_back(st.top());
			st.push(node->val);
			node = node->next;
		}
		reverse(res.begin(), res.end());
		head = reverseList(head);
		return res;
	}

	ListNode* reverseList(ListNode * head) {
		if (head == NULL) return NULL;
		ListNode * node = head->next, *prev = head, *cur;
		prev->next = NULL;
		while (node) {
			cur = node->next;
			node->next = prev;
			prev = node;
			node = cur;
		}
		return prev;
	}
};

class Solution1 {
public:
	vector<int> nextLargerNodes(ListNode* head) {
		vector<int> res, stack;
		for (ListNode* node = head; node; node = node->next) {
			while (stack.size() && res[stack.back()] < node->val) {
				res[stack.back()] = node->val;
				//cout << "pop " << stack.back() << endl;
				stack.pop_back();
			}
			stack.push_back(res.size());
			//cout << "push " << stack.back() << endl;
			res.push_back(node->val);
		}
		for (int i : stack) res[i] = 0;
		return res;
	}
};

void testNextLargerNode() {

}