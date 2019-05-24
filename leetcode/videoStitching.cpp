// #1024

#include "utils.h"

using namespace std;

class Solution { // too slow!!
public:
	int videoStitching(vector<vector<int>>& clips, int T) {
		vector<vector<int>> covers(T + 1);
		for (int i = 0; i < clips.size(); ++i) {
			for (int j = clips[i][0]; j <= clips[i][1] && j <= T; ++j)
				covers[j].push_back(i);
		}
		for (int i = 0; i <= T; ++i) {
			sort(covers[i].begin(), covers[i].end(), [&clips](int k1, int k2)->bool {return clips[k1][1] > clips[k2][1]; });
		}
		vector<bool> visited(clips.size(), false);
		int res = dfs(clips, covers, visited, 0, T);
		return res > 100 ? -1 : res;
	}

	int dfs(const vector<vector<int>> & clips, const vector<vector<int>> & covers, vector<bool> & visited, int start, int end) {
		int minN = 1000;
		for (int i : covers[start]) {
			if (!visited[i]) {
				visited[i] = true;
				if (clips[i][1] >= end) {
					visited[i] = false;
					return 1;
				}
				else minN = min(minN, 1 + dfs(clips, covers, visited, clips[i][1], end));
				visited[i] = false;
			}
		}
		return minN;
	}
};

class Solution1 { // fast O(n) solution!
public:
	int videoStitching(vector<vector<int>>& clips, int T) {
		sort(clips.begin(), clips.end());
		int n = clips.size(), res = 0, right = 0, pos = 0, tmp = 0;
		while (right < T) {
			res++;
			while (pos < n && clips[pos][0] <= right) {
				tmp = max(tmp, clips[pos][1]);
				pos++;
			}
			if (right == tmp) return -1;
			right = tmp;
		}
		return res;
	}
};

void testVideoStitching() {
	vector<vector<int>> clips;
	int T;
	/*
Test case:
clips, T = 
[[0, 5], [1, 6], [2, 7], [3, 8], [4, 9], [5, 10], [6, 11], [7, 12], [8, 13], [9, 14], [10, 15], [11, 16], [12, 17], [13, 18], [14, 19], [15, 20], [16, 21], [17, 22], [18, 23], [19, 24], [20, 25], [21, 26], [22, 27], [23, 28], [24, 29], [25, 30], [26, 31], [27, 32], [28, 33], [29, 34], [30, 35], [31, 36], [32, 37], [33, 38], [34, 39], [35, 40], [36, 41], [37, 42], [38, 43], [39, 44], [40, 45], [41, 46], [42, 47], [43, 48], [44, 49], [45, 50], [46, 51], [47, 52], [48, 53], [49, 54]]
50
	*/
	cin >> clips >> T;
	Solution1 sol;
	printVectorNewline(clips);
	cout << sol.videoStitching(clips, T) << endl;
}