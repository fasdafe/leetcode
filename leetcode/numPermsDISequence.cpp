// #903
#include "utils.h"
using namespace std;

class Solution {
public:
    int numPermsDISequence(string S) {
        int n = S.size();
        long long sum, psum, m = 1e9 + 7;
        vector<vector<long long>> dp(n, vector<long long>(n+1, 0));
        dp[0][0] = S[0] == 'D' ? 1 : 0;
        dp[0][1] = S[0] == 'I' ? 1 : 0;
        for(int i = 1; i < n; i++){
            sum = accumulate(dp[i-1].begin(), dp[i-1].begin()+i+1, 0LL);
            psum = 0;
            for(int j = 0; j <= i+1; j++){
                if(S[i] == 'D') dp[i][j] = (sum - psum) % m;
                else dp[i][j] = psum % m;
                psum += dp[i-1][j];
            }
        }
        return accumulate(dp[n-1].begin(), dp[n-1].end(), 0LL) % m;
    }
};

class SolutionDP1D {
public:
    int numPermsDISequence(string S) {
        int n = S.size();
        long long sum, psum, m = 1e9 + 7, temp;
        vector<long long> dp(n+1, 0);
        dp[0] = S[0] == 'D' ? 1 : 0;
        dp[1] = S[0] == 'I' ? 1 : 0;
        for(int i = 1; i < n; i++){
            sum = accumulate(dp.begin(), dp.begin()+i+1, 0LL);
            psum = 0;
            for(int j = 0; j <= i+1; j++){
                temp = dp[j];
                if(S[i] == 'D') dp[j] = (sum - psum) % m;
                else dp[j] = psum % m;
                psum += temp;
            }
        }
        return accumulate(dp.begin(), dp.end(), 0LL) % m;
    }
};

void testNumPermsDISequence(){
	string s;
	cin >> s;
	for(char si : s){
		if(si != 'D' && si != 'I') {
			cout << "invalid input sequence" << endl;
			return;
		}
	}
	SolutionDP1D mysol;
	int c = mysol.numPermsDISequence(s);
	cout << "number of valid permutations = " << c << endl;
}