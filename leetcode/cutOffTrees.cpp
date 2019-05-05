// #675: Cut Off Trees for Golf Event

#include "utils.h"

using namespace std;

class Solution {
private:
	vector<vector<int>> dirs;//{{-1,0},{1,0},{0,-1},{0,1}};
public:
	Solution(){
		int d[4][2] = {-1, 0, 1, 0, 0, -1, 0, 1};
		for(int i = 0; i < 4; i++)
			dirs.push_back(vector<int>(d[i], d[i]+2));
	}

    int cutOffTree(vector<vector<int>>& forest) {
        int row = forest.size();
        if(row == 0) return -1;
        int col = forest[0].size();
        if(col == 0) return -1;
        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq; // int[0] = height, int[1] = row, int[2] = column
        for(int i = 0; i < row; i++){
            for(int j = 0; j < col; j++){
                if(forest[i][j] != 0 && forest[i][j] != 1) pq.push(create(forest[i][j], i, j));
            }
        }
        
        int curR = 0, curC = 0, steps = 0, stepsTotal = 0;
        while(!pq.empty()){
            vector<int> tree = pq.top();
            pq.pop();
            steps = minPath(curR, curC, tree[1], tree[2], forest);
			cout << curR << ", " << curC << ", " << tree[1] << ", " << tree[2] << ": " << steps << endl;
            if(steps < 0) return -1;
            stepsTotal += steps;
			curR = tree[1];
			curC = tree[2];
        }
        return stepsTotal;
    }
    
    int minPath(int startR, int startC, int nextR, int nextC, const vector<vector<int>>& mat){
        int row = mat.size(), col = mat[0].size();
        vector<vector<bool>> visit(row, vector<bool>(col, false));
        
        queue<pair<int, int>> q;
        q.push(make_pair(startR, startC));
        visit[startR][startC] = true;
        int dist = 0;
        while(!q.empty()){
            int count = q.size(), r, c;
            for(int i = 0; i < count; i++){
                r = q.front().first;
                c = q.front().second;
                q.pop();
                
                if(r == nextR && c == nextC) return dist;
                
                for(auto &d : dirs){
                    if(r+d[0] >= 0 && r+d[0] < row && c+d[1] >= 0 && c+d[1] < col && !visit[r+d[0]][c+d[1]] && mat[r+d[0]][c+d[1]] > 0){
                        visit[r+d[0]][c+d[1]] = true;
                        q.push(make_pair(r+d[0], c+d[1]));
                    }
                }
            }
            dist++;
        }
        return -1;
    }
    
    vector<int> create(int height, int row, int col){
        vector<int> tp(3);
        tp[0] = height;
        tp[1] = row;
        tp[2] = col;
        return tp;
    }
};

void testCutOffTrees(){

	Solution mysol;
	vector<vector<int>> forest;
	cin >> forest; // [[1, 2, 3], [0, 0, 4], [7, 6, 5]]
	printVectorNewline(forest);
	int n = mysol.cutOffTree(forest);
	cout << n << endl;

}