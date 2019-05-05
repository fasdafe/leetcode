
// #85: maximal rectangle

#include "utils.h"

using namespace std;

int maximalRectangle(const vector<vector<int>>& matrix){
	int rows = matrix.size(), cols;
	if(rows == 0) return 0;
	else cols = matrix[0].size();
	if(cols == 0) return 0;

	vector<vector<vector<int>>> dp(rows+1, vector<vector<int>>(cols+1, vector<int>(rows+1, 0)));
	vector<vector<int>> res(rows+1, vector<int>(cols+1, 0));
	for(int i = 1; i <= rows; i++){
		for(int j = 1; j <= cols; j++){
			res[i][j] = max(res[i-1][j], res[i][j-1]);
			for(int t = 1; t <= i; t++){ // t is top row index
				if((t == i || dp[i-1][j][t]>=1) && matrix[i-1][j-1]==1) {
					dp[i][j][t] = dp[i][j-1][t]+1;
					res[i][j] = max(res[i][j], dp[i][j][t]*(i-t+1));
				}
				else dp[i][j][t] = 0;
			}
		}
	}
	printVectorNewline(res);
	return res[rows][cols];
}


void testMaximalRectangle(){
	vector<vector<int>> matrix;
	cin >> matrix;
	//char buffer[100];
	//cin.read(buffer, 100);
	//cout << buffer << endl;
	printVectorNewline(matrix);
	int res = maximalRectangle(matrix);
	cout << "Maximal rectangle = " << res << endl;
}