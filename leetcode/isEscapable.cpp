#include "utils.h"

using namespace std;

class Solution {
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
		unordered_set<long long> visited, bset;
		for (auto& b : blocked) {
			bset.insert((((long long)b[0]) << 32) + b[1]);
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

					vector<int> p{ x, y };
					if (x >= 0 && x < 1000000 && y >= 0 && y < 1000000) {
						long long l = (((long long)x) << 32) + y;
						if (visited.count(l) == 0 && bset.count(l) == 0)
						{
							if (x == target[0] && y == target[1]) return true;
							que.push({ x, y });
							visited.insert((((long long)x) << 32) + y);
							cnt++;
							if (cnt > 20000) return true;
						}
					}
				}
			}
		}
		return false;
	}
};