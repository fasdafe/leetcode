// LeetCode #211: Word Dictionary

#include "utils.h"

using namespace std;

class WordDictionary {
public:
	struct TrieNode{
		char c;
		bool end;
		TrieNode *child, *next;
		TrieNode() : c(0), end(false), child(NULL), next(NULL) {}
		TrieNode(char c) : c(c), end(false), child(NULL), next(NULL) {}
	};

	TrieNode *root;

	/** Initialize your data structure here. */
	WordDictionary() {
		root = new TrieNode();
	}

	/** Adds a word into the data structure. */
	void addWord(string word) {
		TrieNode *node, *parent = root;
		for(char c : word){
			node = parent->child;
			TrieNode *left = node, *prev = NULL;
			if(left != NULL){
				while(node != NULL && node->c < c){
					prev = node;
					node = node->next;
				}
				if(prev == NULL && node->c > c){ // insert on the left
					prev = new TrieNode(c);
					prev->next = left;
					parent->child = prev;
					parent = prev;
				}
				else if(node == NULL || node->c > c){
					prev->next = new TrieNode(c);
					prev->next->next = node;
					parent = prev->next;
				}
				else{ // no insertion
					parent = node;
				}
			}
			else{
				left = new TrieNode(c);
				parent->child = left;
				parent = left;
			}
		}
		parent->end = true;
	}

	/** Returns if the word is in the data structure. A word could contain the dot character '.' to represent any one letter. */
	bool search(string word) {
		if(root == NULL) return false;
		queue<TrieNode*> q;
		q.push(root);
		TrieNode *node;
		for(char c : word){
			if(q.empty()) return false;
			int sz = q.size();
			for(int i = 0; i < sz; ++i){
				node = q.front()->child;
				q.pop();
				while(node != NULL){
					if(c == '.' || node->c == c)
						q.push(node);
					if(node->c == c) break;
					node = node->next;
				}
			}
		}
		while(!q.empty()){
			if(q.front()->end) return true;
			q.pop();
		}
		return false;
	}
};

/**
* Your WordDictionary object will be instantiated and called as such:
* WordDictionary obj = new WordDictionary();
* obj.addWord(word);
* bool param_2 = obj.search(word);
*/

void testWordDict(){
	WordDictionary obj;
	obj.addWord("a");
	obj.addWord("ab");
	string s[8] = {"a","a.","ab",".a",".b","ab.",".",".."};
	for(int i = 0; i < 8; i++){
		cout << "search " << s[i] << ": " << obj.search(s[i]) << endl;
	}
}