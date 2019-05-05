// #212: word search II

#include "utils.h"

using namespace std;

#include "Trie.h"

class Solution {
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        
        Trie dict;
        for(string& word : words) dict.insert(word);
        unordered_set<string> res;
        int row = board.size();
        if(row == 0) return vector<string>();
        int col = board[0].size();
        if(col == 0) return vector<string>();
        int dirs[4][2] = {-1, 0, 1, 0, 0, -1, 0, 1};
        
        for(int i = 0; i < row; i++){
            for(int j = 0; j < col; j++){
                stack<pair<pair<int, int>, int>> st;
                vector<pair<int, int>> path;
                string word;
                //path.push_back(make_pair(i, j));
                word.push_back(board[i][j]);
				if(dict.search(word)) res.insert(word);
                st.push(make_pair(make_pair(i, j), 1));
                int k;
                pair<int, int> loc;
                while(!st.empty()){
                    k = st.top().second;
                    loc = st.top().first;
                    st.pop();
                    path.resize(k);
                    word.resize(k);
					path[k-1] = loc;
					word[k-1] = board[loc.first][loc.second];
                    for(int i = 0; i < 4; i++){
                        int nextr = loc.first+dirs[i][0], nextc = loc.second+dirs[i][1];
                        if(nextr >= 0 && nextr < row && nextc >= 0 && nextc < col && find(path.begin(), path.end(), make_pair(nextr, nextc)) == path.end()){
                            path.push_back(make_pair(nextr, nextc));
                            word.push_back(board[nextr][nextc]);
                            if(dict.startsWith(word)){
                                st.push(make_pair(make_pair(nextr, nextc), k+1));
                                if(dict.search(word)) res.insert(word);
                            }
                            path.pop_back();
                            word.pop_back();
                        }
                    }
                }
            }
        }
        
        return vector<string>(res.begin(), res.end());
        
    }
};

class Solution2 {
public:
    struct TrieNode {
        TrieNode *child[26];
        string str;
        TrieNode() : str("") {
            for (auto &a : child)
                a = NULL;
        }
    };

    struct Trie {
        TrieNode *root;
        Trie() : root(new TrieNode()) {}

        void insert(string s) {
            TrieNode *p = root;
            for (auto &a : s) {
                int i = a - 'a';
                if (!p->child[i])
                    p->child[i] = new TrieNode();
                p = p->child[i];
            }
            p->str = s;
        }
    };

    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        vector<string> res;
        if (words.empty() || board.empty() || board[0].empty())
            return res;

        int row = board.size();
        int col = board[0].size();
        vector<vector<bool>> visited(row, vector<bool>(col, false));
        Trie T;
        for (auto &a : words)
            T.insert(a);

        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                if (T.root->child[board[i][j] - 'a']) {
                    dfs(i, j, row, col, T.root->child[board[i][j] - 'a'], board, visited, res);
                }
            }
        }
        return res;
    }

    void dfs(int r, int c, const int row, const int col, TrieNode *p, const vector<vector<char>>& board,
             vector<vector<bool>>& visited, vector<string>& res) {
        if (!p->str.empty()) {
            res.push_back(p->str);
            p->str.clear();
        }
        visited[r][c] = true;
        int d[][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        for (auto &item : d) {
            int nr = item[0] + r;
            int nc = item[1] + c;
            if (nr >= 0 && nr < row && nc >= 0 && nc < col && (!visited[nr][nc]) && p->child[board[nr][nc] - 'a']) {
                dfs(nr, nc, row, col, p->child[board[nr][nc] - 'a'], board, visited, res);
            }
        }
        visited[r][c] = false;
    }
};

void testWordSearchII(){
	Solution2 mysol;
	vector<string> words;
	cout << "words: ";
	cin >> words;
	//cin.clear();
	//cin.ignore(numeric_limits<streamsize>::max(), '\n');
	vector<vector<char>> board;
	cout << "board: " << endl;
	cin >> board;
	printVectorNewline(board);
	
	vector<string> exists = mysol.findWords(board, words);
	cout << exists << endl;
}