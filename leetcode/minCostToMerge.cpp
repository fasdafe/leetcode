// 1000

#include "utils.h"

using namespace std;

class Solution {// recursive, too slow
public:
	int mergeStones(vector<int>& stones, int K) {
		int n = stones.size();
		if (K > 2 && n % (K - 1) != 1) return -1;
		if (n == 1) return 0;
		int res = INT_MAX;
		for (int i = 0; i <= n - K; ++i) {
			int s = accumulate(stones.begin() + i, stones.begin() + i + K, 0);
			vector<int> v(n - K + 1, 0);
			copy(stones.begin(), stones.begin() + i, v.begin());
			v[i] = s;
			copy(stones.begin() + i + K, stones.end(), v.begin() + i + 1);
			res = min(res, s + mergeStones(v, K));
		}
		return res;
	}
};

class Solution1 { // DP by lee215
public:
	int mergeStones(vector<int>& stones, int K) {
		int n = stones.size();
		if ((n - 1) % (K - 1)) return -1;

		vector<int> prefix(n + 1);
		for (int i = 0; i < n; i++)
			prefix[i + 1] = prefix[i] + stones[i];

		vector<vector<int> > dp(n, vector<int>(n));
		for (int m = K; m <= n; ++m)
			for (int i = 0; i + m <= n; ++i) {
				int j = i + m - 1;
				dp[i][j] = INT_MAX;
				for (int mid = i; mid < j; mid += K - 1)
					dp[i][j] = min(dp[i][j], dp[i][mid] + dp[mid + 1][j]);
				if ((j - i) % (K - 1) == 0)
					dp[i][j] += prefix[j + 1] - prefix[i];
			}
		return dp[0][n - 1];
	}
};

class Solution2 {
public:
	int mergeStones(vector<int>& stones, int K) {
		// Reference: huahua
		// Time: O(nˆ3 / K) Space: O(nˆ2)
		const int n = stones.size();
		if ((n - 1) % (K - 1)) return -1;

		vector<int> sums(n + 1);
		for (int i = 0; i < stones.size(); i++)
			sums[i + 1] = sums[i] + stones[i];

		const int kInf = 1e9;
		vector<vector<int>> cache(n, vector<int>(n, kInf));

		std::function<int(int, int)>dp;
		dp = [&stones, &sums, &cache, &dp, K, kInf](int i, int j) {
			const int l = j - i + 1;
			if (l < K) return 0;
			if (cache[i][j] != kInf) return cache[i][j];
			int ans = kInf;
			for (int m = i; m < j; m += K - 1)
				ans = min(ans, dp(i, m) + dp(m + 1, j));
			if ((l - 1) % (K - 1) == 0)
				ans += sums[j + 1] - sums[i];
			return cache[i][j] = ans;
		};
		return dp(0, n - 1);
	}
};