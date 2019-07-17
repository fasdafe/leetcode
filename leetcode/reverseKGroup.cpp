// #25

#include "utils.h"
using namespace std;


//Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

ListNode* buildList(const vector<int>& v) {
	if (v.size() == 0) return NULL;
	ListNode* head = new ListNode(v[0]), * node = head;
	for (int i = 1; i < v.size(); ++i) {
		node->next = new ListNode(v[i]);
		node = node->next;
	}
	return head;
}

void printList(ListNode* head) {
	cout << "[";
	if (head) cout << head->val;
	while (head && head->next) {
		head = head->next;
		cout << ", " << head->val;
	}
	cout << "]" << endl;
}

class Solution {
public:
	ListNode* reverseKGroup(ListNode* head, int k) {
		ListNode* first = new ListNode(0), * left = first, * right, * temp, * prev;
		left->next = head;
		while (true) {
			right = left;
			for (int i = 0; i < k; ++i) {
				if (right->next) right = right->next;
				else return first->next;
			}
			temp = left->next;
			left->next = right;
			head = temp;
			prev = right->next;
			for (int i = 0; i < k; ++i) {
				left = temp;
				temp = left->next;
				left->next = prev;
				prev = left;
			}
			left = head;
		}
		return head;
	}
};

void testReverseKGroup() {
	vector<int> v;
	int k = 2;
	char c;
	cin >> v;
	cin >> k;
	ListNode* head = buildList(v);
	Solution sol;
	printList(sol.reverseKGroup(head, k));
}