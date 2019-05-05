// #79: word search

#include "utils.h"

using namespace std;

class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        stack<pair<pair<int, int>, int>> st;
		vector<pair<int, int>> path;
        vector<pair<int, int>> start;
        int row = board.size(); 
        if(row == 0) return false;
        int col = board[0].size();
        if(col == 0) return false;
        if(word.size() == 0) return true;
        char cur = word[0];
        for(int i = 0; i < row; i++){
            for(int j = 0; j < col; j++){
                if(board[i][j] == cur){
                    start.push_back(make_pair(i, j));
                }
            }
        }
        int dirs[4][2] = {-1, 0, 1, 0, 0, -1, 0, 1};
        int len = word.size();
        for(auto p : start){
            st = stack<pair<pair<int, int>, int>>();
			path.clear();
            st.push(make_pair(p, 0));
            pair<int, int> pos, newpos;
            int r, c, newr, newc, k;
            while(!st.empty()){
                pos = st.top().first;
                k = st.top().second;
				path.resize(k);
				path.push_back(pos);
				printVectorNewline(path);
                if(k+1 == len) return true;
                k++;
                st.pop();
                r = pos.first;
                c = pos.second;
                for(int i = 0; i < 4; i++){
                    newr = r+dirs[i][0];
                    newc = c+dirs[i][1];
                    newpos = make_pair(newr, newc);
                    if(newr >= 0 && newr < row && newc >= 0 && newc < col && find(path.begin(), path.end(), newpos) == path.end() && board[newr][newc] == word[k]){
                        st.push(make_pair(newpos, k));
                    }
                }
            }
        }
        return false;
    }
};

void testWordSearch(){
	Solution mysol;
	string word;
	cout << "word: ";
	cin >> word;
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	vector<vector<char>> board;
	cout << "board: " << endl;
	cin >> board;
	printVectorNewline(board);
	bool exists = false;
	exists = mysol.exist(board, word);
	cout << (exists ? "the word exists in the board!" : "the word doesn't exist in the board!") << endl;
}