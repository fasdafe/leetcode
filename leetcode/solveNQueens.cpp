// #51

#include "utils.h"

using namespace std;

class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> res;
        vector<vector<bool>> mask(n, vector<bool>(n, false));
        vector<int> found;
        dfs(found, mask, res);
        return res;
    }
    
	void dfs(vector<int>& found, const vector<vector<bool>>& mask, vector<vector<string>>& res){
		int n = mask.size(), r = found.size();
		if(r == n){
			vector<string> single(n, string(n, '.'));
			for(auto pos : found){
				single[pos/n][pos%n] = 'Q';
			}
			if(find(res.begin(), res.end(), single) == res.end())
				res.push_back(single);
			return;
		}
		for(int j = 0; j < n; j++){
			if(mask[r][j]) continue;
			vector<vector<bool>> tmp = mask;
			found.push_back(r*n+j);
			for(int k = 0; k < n; k++) tmp[r][k] = tmp[k][j] = true;
			for(int k = max(r+j-n+1, 0); k <= min(r+j, n-1); k++) tmp[k][r+j-k] = true;
			for(int k = max(j-r, 0); k <= min(n-1-r+j, n-1) ; k++) tmp[k+r-j][k] = true;
			dfs(found, tmp, res);
			found.pop_back();
		}
	}
};

void testNQueens(){
	int n;
	cin >> n;
	Solution mysol;
	vector<vector<string>> res = mysol.solveNQueens(n);
	cout << res.size() << " solutions found!" << endl;
	//for(auto &board : res)
	//	printVectorNewline(board);
}