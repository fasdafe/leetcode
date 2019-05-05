// LeetCode #931
#include "utils.h"

using namespace std;

int sqrtInt(int n){
	int i = 1;
	while(i*i < n) i <<= 1;
	if(i*i == n) return i;
	int left = (i>>1), right = i;
	int mid;
	while(left < right-1){
		mid = (left+right) / 2;
		if(mid*mid == n) return mid;
		else if(mid*mid < n) left = mid;
		else right = mid;
	}
	return left;
}

int numSquares1(int n){
	int cache[10] = {1,2,3,1,2,3,4,2,1,2};
	if(n <= 10) return cache[n-1];
	while(n%4 == 0) n /= 4;
	if(n%8 == 7) return 4;
	int sr = sqrtInt(n);
	if(sr*sr == n) return 1;
	int k = 4, t;
	for(int i = sr/2; i <= sr; i++){
		t = 1 + numSquares1(n-i*i);
		if(t == 2) return 2;
		if(t < k) k = t;
	}
	return k;
}

int numSquares2(int n) { 
	while (n % 4 == 0) n /= 4; 
	if (n % 8 == 7) return 4; 
	for (int a = 0; a * a <= n; ++a) { 
		int b = sqrt(n - a * a + 0.5); 
		if (a * a + b * b == n) { 
			return !!a + !!b; 
		} 
	} 
	return 3; 
}

int numSquares3(int n) {
	vector<int> dp(n + 1, INT_MAX);
	dp[0] = 0;
	for (int i = 0; i <= n; ++i) {
		for (int j = 1; i + j * j <= n; ++j) {
			dp[i + j * j] = min(dp[i + j * j], dp[i] + 1);
		}
	}
	return dp.back();
}

int numSquares4(int n) {
	static vector<int> dp(1, 0);
	while (dp.size() <= n) {
		int m = dp.size(), val = INT_MAX;
		for (int i = 1; i * i <= m; ++i) {
			val = min(val, dp[m - i * i] + 1);
		}
		dp.push_back(val);
	}
	return dp.back();
}

int numSquaresReal(int n) {
	while (n % 4 == 0)
		n /= 4;
	if (n % 8 == 7)
		return 4;
	int a = -1, b = sqrt(n);
	n -= b * b;
	b += b + 1;
	while (a <= b) {
		if (n < 0)
			n += b -= 2;
		else if (n > 0)
			n -= a += 2;
		else
			return a < 0 ? 1 : 2;
	}
	return 3;
}

int numSquares(int n){
	return numSquaresReal(n);
}

void testNumSquares(){
	srand(time(0));
	for(int i = 0; i < 10; i++)
	{
		int n = rand()%1000;
		cout << n << " -> " << numSquares(n) << endl;
	}
	cout << 15 << " -> " << numSquares(15) << endl;
	cout << 6665 << " -> " << numSquares(6665) << endl;
	cout << 66665 << " -> " << numSquares(66665) << endl;
}