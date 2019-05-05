// #37: Soduku solver

#include "utils.h"

using namespace std;

class Solution { // much slower than Solution1
public:
    void solveSudoku(vector<vector<char>>& board) {
        vector<int> rows, cols;
        for(int i = 0; i < 9; i++){
            for(int j = 0; j < 9; j++){
                if(board[i][j] == '.'){
                    rows.push_back(i);
                    cols.push_back(j);
                }
            }
        }
        dfs(board, rows, cols, 0);
    }
    
    bool dfs(vector<vector<char>>& board, const vector<int>& rows, const vector<int>& cols, int pos){
        if(pos == rows.size()) return true;
        for(char c = '1'; c <= '9'; c++){
            if(check(board, rows[pos], cols[pos], c)){
                board[rows[pos]][cols[pos]] = c;
                if(dfs(board, rows, cols, pos+1)) return true;
                board[rows[pos]][cols[pos]] = '.';
            }
        }
        return false;
    }
    
    bool check(const vector<vector<char>>& board, int row, int col, char c) {
        for(int i = 0; i < 9; i++){
            if(board[row][i] == c || board[i][col] == c || board[(row/3)*3+i/3][(col/3)*3+i%3] == c) return false;
        }
        return true;
    }
};

class Solution1 {
public:
    void solveSudoku(vector<vector<char>>& board) {
        dfs(board, 0);
    }
    
    bool dfs(vector<vector<char>>& board, int pos){
        while(pos<81 && board[pos/9][pos%9] != '.') pos++;
        if(pos == 81) return true;
        int row = pos/9, col = pos%9;
        for(char c = '1'; c <= '9'; c++){
            if(check(board, row, col, c)){
                board[row][col] = c;
                if(dfs(board, pos+1)) return true;
                board[row][col] = '.';
            }
        }
        return false;
    }
    
    bool check(const vector<vector<char>>& board, int row, int col, char c) {
        for(int i = 0; i < 9; i++){
            if(board[row][i] == c || board[i][col] == c || board[(row/3)*3+i/3][(col/3)*3+i%3] == c) return false;
        }
        return true;
    }
};

class Solution2 {
public:
	bool solveSudoku(vector<vector<char>>& board) {
		int i,j,row=9,col=9;
		for(i=0;i<9;++i){
			for(j=0;j<9;++j){
				if(board[i][j]=='.'){
					row=i;
					col=j;
				}
			}
		}
		if(row==9&&col==9) return true;
		else{
			bool conflict;
			int val;
			for(val=1;val<10;++val){
				conflict=false;
				for(i=0;i<9;++i){
					if(board[row][i]==val+'0' || board[i][col]==val+'0' || board[(row/3)*3+i/3][(col/3)*3+i%3]==val+'0') conflict=true;
				}
				if(!conflict){
					board[row][col]=val+'0';
					if(solveSudoku(board)) return true;
					else board[row][col]='.';
				}
			}
			return false;
		}
	}
};

void testSodukuSolver(){
	//[[5, 3, ., ., 7, ., ., ., .], [6, ., ., 1, 9, 5, ., ., .], [., 9, 8, ., ., ., ., 6, .], [8, ., ., ., 6, ., ., ., 3], [4, ., ., 8, ., 3, ., ., 1], [7, ., ., ., 2, ., ., ., 6], [., 6, ., ., ., ., 2, 8, .], [., ., ., 4, 1, 9, ., ., 5], [., ., ., ., 8, ., ., 7, 9]]
	vector<vector<char>> board;
	cin >> board; 
	if(board.size() != 9 || board[0].size() != 9){
		cout << "input is invalid!" << endl;
		return;
	}
	printVectorNewline(board);
	Solution1 mysol;
	mysol.solveSudoku(board);
	printVectorNewline(board);
}