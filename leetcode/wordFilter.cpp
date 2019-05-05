// # 745

#include "utils.h"

using namespace std;

struct TrieNode {
    int weight;
    TrieNode* child[27];
    TrieNode() : weight(-1) {
        for(int i = 0; i < 27; i++)
            child[i] = NULL;
    }
};

class Trie {
private:
    TrieNode *root;
public:
    Trie() : root(new TrieNode()) {}
    
    void insert(const string& word, int weight){
        TrieNode *node;
        string modified = word;
        int idx;
        for(int i = word.size(); i >= 0; i--){
            if(i == word.size()) modified.insert(modified.begin(), '#');
            else modified.insert(modified.begin(), word[i]);
            node = root;
            for(char c: modified){
                idx = (c == '#' ? 26 : c-'a');
                if(node->child[idx] == NULL)
                    node->child[idx] = new TrieNode();
                node = node->child[idx];
                node->weight = weight;
            }
        }
    }
    
    int search(const string& word){
        TrieNode *node = root;
        int idx;
        for(char c : word){
            idx = (c=='#'?26:c-'a');
            if(node->child[idx] == NULL) return -1;
            else node = node->child[idx];
        }
        return node->weight;
    }
};

class WordFilter {
private:
    Trie t;
public:
    WordFilter(vector<string> words) {
        for(int i = 0; i < words.size(); i++) t.insert(words[i], i);
    }
    
    int f(string prefix, string suffix) {
		return t.search(suffix+"#"+prefix);
    }
};


void testWordFilter(){
	vector<string> words;
	cin >> words;
	WordFilter obj(words);
	int j = obj.f("", "op");
	cout << j << endl;
}
/**
 * Your WordFilter object will be instantiated and called as such:
 * WordFilter obj = new WordFilter(words);
 * int param_1 = obj.f(prefix,suffix);
 */