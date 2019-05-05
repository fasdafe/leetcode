// #208: Implement Trie

#include "utils.h"
#include "Trie.h"

using namespace std;

/** Inserts a word into the trie. */
void Trie::insert(string word) {
	TrieNode *cur = root, *next;
	for(char letter : word){
		next = cur->child[letter-'a'];
		if(next == NULL){
			next = new TrieNode();
			cur->child[letter-'a'] = next;
		}
		cur = next;
	}
	cur->isWord = true;
}

void Trie::remove(string word){
	if(!search(word)) return;
	TrieNode *cur = root;
	vector<TrieNode*> path;
	path.push_back(cur);
	for(int i = 0; i < word.size(); i++){
		cur = cur->child[word[i] - 'a'];
		path.push_back(cur);
	}
	cur->isWord = false;
	for(int i = path.size()-1; i >= 1; i--){
		bool hasChild = false;
		cur = path[i];
		for(int j = 0; j < 26; j++){
			if(cur->child[j] != NULL){
				hasChild = true;
				break;
			}
		}
		if(hasChild){
			break;
		}
		else if(!hasChild && !cur->isWord){
			delete cur;
			path[i-1]->child[word[i-1]-'a'] = NULL;
		}
	}
}

/** Returns if the word is in the trie. */
bool Trie::search(string word) {
	TrieNode *cur = root;
	int i = 0, n = word.size();
	if(n == 0) return true;
	while(cur && i < n){
		cur = cur->child[word[i++]-'a'];
	}
	return i==n && cur!=NULL && cur->isWord;
}

/** Returns if there is any word in the trie that starts with the given prefix. */
bool Trie::startsWith(string prefix) {
	TrieNode *cur = root;
	int i = 0, n = prefix.size();
	if(n == 0) return true;
	while(cur && i < n){
		cur = cur->child[prefix[i++]-'a'];
	}
	return i==n && cur!=NULL;
}


void testTrie(){

	//Your Trie object will be instantiated and called as such:
	Trie obj;
	string word = "apple";
	obj.insert(word);
	cout << "insert " << word << endl;
	cout << "search " << word << ": " << obj.search(word) << endl;
	cout << "search app: " << obj.search("app") << endl;
	cout << "search prefix app: " << obj.startsWith("app") << endl;
	obj.insert("app");
	cout << "insert app" << endl;
	cout << "search app: " << obj.search("app") << endl;
	obj.remove(word);
	cout << "remove " << word << endl;
	cout << "search " << word << ": " << obj.search(word) << endl;
	cout << "search app: " << obj.search("app") << endl;

}