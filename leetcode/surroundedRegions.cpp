// #130: Surrounded Regions
#include "utils.h"

using namespace std;

class Solution {
private:
    vector<int> parents;
    vector<int> ranks;
    int find(int x) {
        if(x != parents[x]) parents[x] = find(parents[x]);
        return parents[x];
    }
    
    bool union_helper(int x, int y) {
        int px = find(x), py = find(y);
        if(px == py) return false;
        if(ranks[px] < ranks[py]) parents[px] = py;
        else {
            parents[py] = px;
            if(ranks[px] == ranks[py]) ranks[px]++;
        }
        return true;
    }
public:
    void solve(vector<vector<char>>& board) {
        if(board.size() == 0 || board[0].size() == 0) return;
        int rows = board.size(), cols = board[0].size(), N = rows * cols;
        parents.resize(N);
        ranks = vector<int>(N, 0);
        for(int i = 0; i < rows; i++)
            for(int j = 0; j < cols; j++)
                parents[i*cols+j] = i*cols+j;
        
        for(int i = 0; i < N; i++) {
            if(board[i/cols][i%cols] == 'O') {
                if(i >= cols && board[i/cols-1][i%cols] == 'O') union_helper(i, i-cols);
                if(i < N-cols && board[i/cols+1][i%cols] == 'O') union_helper(i, i+cols);
                if(i%cols > 0 && board[i/cols][i%cols-1] == 'O') union_helper(i, i-1);
                if(i%cols < cols-1 && board[i/cols][i%cols+1] == 'O') union_helper(i, i+1);
            }
        }
        unordered_set<int> boundary;
        for(int i = 0; i < cols; i++) {
            if(board[0][i] == 'O') boundary.insert(find(i));
            if(board[rows-1][i] == 'O') boundary.insert(find(N-cols+i));
        }
        for(int i = 1; i < rows-1; i++) {
            if(board[i][0] == 'O') boundary.insert(find(i*cols));
            if(board[i][cols-1] == 'O') boundary.insert(find(i*cols+cols-1));
        }
        for(int i = 0; i < N; i++) {
            if(board[i/cols][i%cols] == 'O' && boundary.count(find(i)) == 0)
                board[i/cols][i%cols] = 'X';
        }
    }
};

void testSurroundedRegions() {
	Solution sol;
	vector<vector<char>> board;
	cin >> board;
	printVectorNewline(board);
	sol.solve(board);
	printVectorNewline(board);
}