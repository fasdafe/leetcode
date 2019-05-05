//#837

#include "utils.h"

using namespace std;

double new21Game(int N, int K, int W) {
	if(K==0) return 1.0;
	else if(K-1+W<=N) return 1.0;
	else if(K>N) return 0.0;

	vector<double> prev(K, 1.0), cur = prev; // cur[j], prev[j] is reduced from A[i][j] = Prob(S_i <= j)
	double res = max(0.0, double(min(N,W)-K+1));
	for(int i = 1; i < K; i++){
		for(int j = 0; j < K; j++){
			if(j < i) cur[j] = 0.0;
			else {
				cur[j] = cur[j-1] + (prev[j-1]-(j<W+1 ? 0.0 : prev[j-W-1])) / W;
				res += (cur[j]-cur[j-1])*max(0.0, double(min(N,W+j)-K+1));
			}
		}
		swap(cur, prev);
	}
	return min(res/W, 1.0);
}

double new21Game2(int N, int K, int W) {
	if(K==0 || K<=N-W+1) return 1.0;
	else if(K>N) return 0.0;

	vector<double> dp(K, 1.0); // dp[i] = P(S_0=i)+...+P(S_i=i)
	double res = max(0.0, double(min(N,W)-K+1));
	for(int i = 1; i < K; i++){
		dp[i] = dp[i-1] + (dp[i-1] - (i<=W ? 0.0 : dp[i-W-1]))/W - double(i==1);
		res += max(0.0, double(min(N,W+i)-K+1)) * dp[i];
	}

	return min(res/W, 1.0);
}

void testNew21Game(){
	int N, K, W;
	cin >> N >> K >> W;
	double prob = new21Game(N, K, W);
	cout << "Probability = " << prob << endl;
}