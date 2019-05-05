// 501

#include "utils.h"

using namespace std;

class Solution {
public:
    vector<int> findMode(TreeNode* root) {
        vector<int> res;
        int repeat = 0, maxRepeat = 0;
        if(!root) return res;
        stack<TreeNode*> st;
		TreeNode *cur = root, *prev = NULL;
		while(cur || !st.empty()){
			while(cur){
				st.push(cur);
				cur = cur->left;
			}
			cur = st.top();
			st.pop();

			if(!prev){
				maxRepeat = repeat = 1;
				res.push_back(cur->val);
			}
			else if(prev->val == cur->val){
				repeat++;
				if(repeat == maxRepeat) res.push_back(cur->val);
				else if(repeat > maxRepeat){
					if(res.size() > 1 || res.back() != cur->val){
						res.clear();
						res.push_back(cur->val);
					}
					maxRepeat = repeat;
				}
			}
			else {
				repeat = 1;
				if(maxRepeat == 1) res.push_back(cur->val);
			}

			prev = cur;
			cur = cur->right;
		}
		return res;
    }
};