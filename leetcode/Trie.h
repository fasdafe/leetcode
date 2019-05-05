
#ifndef _TRIE_H_
#define _TRIE_H_

#include "utils.h"

struct TrieNode {
    //char letter;
    bool isWord;
    TrieNode* child[26];
    /*TrieNode() : isWord(false) {
		for(int i = 0; i < 26; i++){
			child[i] = NULL;
		}
	}*/
};

class Trie {
private:
    TrieNode *root;
public:
    /** Initialize your data structure here. */
    Trie() {
        root = new TrieNode();
    }
    
    /** Inserts a word into the trie. */
    void insert(std::string word);
    
	void remove(std::string word);

    /** Returns if the word is in the trie. */
    bool search(std::string word);
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(std::string prefix);
};

#endif // _TRIE_H_