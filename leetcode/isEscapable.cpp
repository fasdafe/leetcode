#include "utils.h"

using namespace std;

class Solution { 
// https://leetcode.com/problems/escape-a-large-maze/discuss/282860/C%2B%2B-Limited-BFS-28-ms
public:
	bool bfs(unordered_set<long long>& visited, vector<int>& s, vector<int>& t, int blocks) {
		vector<vector<int>> dirs = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
		vector<pair<int, int>> q = { {s[0], s[1]} };
		while (!q.empty() && q.size() <= blocks) {
			vector<pair<int, int>> q1;
			for (auto p : q) {
				for (auto d : dirs) {
					auto x = p.first + d[0], y = p.second + d[1];
					if (x < 0 || x > 999999 || y < 0 || y > 999999) continue;
					if (x == t[0] && y == t[1]) return true;
					if (visited.insert(((long long)x << 32) + y).second) q1.push_back({ x, y });
				}
			}
			swap(q, q1);
		}
		return !q.empty();
	}
	bool isEscapePossible(vector<vector<int>> & blocked, vector<int> & s, vector<int> & t) {
		unordered_set<long long> vis_s, vis_t;
		for (auto b : blocked) {
			if (abs(b[0] - s[0]) + abs(b[1] - s[1]) < 400) vis_s.insert(((long long)b[0] << 32) + b[1]);
			if (abs(b[0] - t[0]) + abs(b[1] - t[1]) < 400) vis_t.insert(((long long)b[0] << 32) + b[1]);
		}
		return bfs(vis_s, s, t, vis_s.size()) && bfs(vis_t, t, s, vis_t.size());
	}
};

class Solution2 {
public:
	bool isEscapePossible(vector<vector<int>>& blocked, vector<int>& source, vector<int>& target) {
		return bfs(blocked, source, target) && bfs(blocked, target, source);
	}

	bool bfs(vector<vector<int>>& blocked, vector<int>& source, vector<int>& target) {
		queue<pair<int, int>> que;
		que.push(make_pair(source[0], source[1]));
		int cnt = 1;
		unordered_set<long long> visited;
		for (auto& b : blocked) {
			visited.insert((((long long)b[0]) << 32) + b[1]);
		}
		visited.insert((((long long)source[0]) << 32) + source[1]);
		int dirs[4][2] = { -1, 0, 1, 0, 0, -1, 0, 1 };
		while (!que.empty()) {
			int sz = que.size();
			for (int i = 0; i < sz; i++) {
				int r = que.front().first, c = que.front().second;
				que.pop();
				for (auto& d : dirs) {
					int x = r + d[0], y = c + d[1];
					if (x == target[0] && y == target[1]) return true;
					vector<int> p{ x, y };
					if (x >= 0 && x < 1000000 && y >= 0 && y < 1000000 && visited.insert((((long long)x) << 32) + y).second) {
						que.push({ x, y });
						if (++cnt > 20000) return true;
					}
				}
			}
		}
		return false;
	}
};

void testIsEscapable() {
	vector<vector<int>> blocked;
	vector<int> source, target;
	/*
	[[100059, 100063], [100060, 100064], [100061, 100065], [100062, 100066], [100063, 100067], [100064, 100068], [100065, 100069], [100066, 100070], [100067, 100071], [100068, 100072], [100069, 100073], [100070, 100074], [100071, 100075], [100072, 100076], [100073, 100077], [100074, 100078], [100075, 100079], [100076, 100080], [100077, 100081], [100078, 100082], [100079, 100083], [100080, 100082], [100081, 100081], [100082, 100080], [100083, 100079], [100084, 100078], [100085, 100077], [100086, 100076], [100087, 100075], [100088, 100074], [100089, 100073], [100090, 100072], [100091, 100071], [100092, 100070], [100093, 100069], [100094, 100068], [100095, 100067], [100096, 100066], [100097, 100065], [100098, 100064], [100099, 100063], [100098, 100062], [100097, 100061], [100096, 100060], [100095, 100059], [100094, 100058], [100093, 100057], [100092, 100056], [100091, 100055], [100090, 100054], [100089, 100053], [100088, 100052], [100087, 100051], [100086, 100050], [100085, 100049], [100084, 100048], [100083, 100047], [100082, 100046], [100081, 100045], [100080, 100044], [100079, 100043], [100078, 100044], [100077, 100045], [100076, 100046], [100075, 100047], [100074, 100048], [100073, 100049], [100072, 100050], [100071, 100051], [100070, 100052], [100069, 100053], [100068, 100054], [100067, 100055], [100066, 100056], [100065, 100057], [100064, 100058], [100063, 100059], [100062, 100060], [100061, 100061], [100060, 100062]]
	[100079, 100063]
	[999948, 999967]
	*/
	cin >> blocked >> source >> target;
	Solution sol;
	Solution2 sol2;
	int N = 100;
	double start = clock();
	for (int i = 0; i < N; i++) {
		sol.isEscapePossible(blocked, source, target);
	}
	double duration = (clock() - start) / (double)CLOCKS_PER_SEC;
	cout << "Solution duration: " << duration << endl;
	start = clock();
	for (int i = 0; i < N; i++) {
		sol2.isEscapePossible(blocked, source, target);
	}
	duration = (clock() - start) / (double)CLOCKS_PER_SEC;
	cout << "Solution2 duration: " << duration << endl;

}