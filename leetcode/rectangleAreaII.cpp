// #850
#include "utils.h"
using namespace std;

class Solution {
private:
	struct Node {
		int left, right, bottom, top;
		long long covered;
		Node *leftChild, *rightChild;
		Node(int left, int bottom, int right, int top) : left(left), right(right), bottom(bottom), top(top), covered(0), leftChild(NULL), rightChild(NULL) {}
		~Node() {
			delete leftChild;
			delete rightChild;
		}
		bool inside(const vector<int>& rect) {
			return insideX(rect) && insideY(rect);
		}
		bool insideX(const vector<int>& rect) {
			return (rect[0] <= left) && (rect[2] >= right);
		}
		bool insideY(const vector<int>& rect) {
			return (rect[1] <= bottom) && (rect[3] >= top);
		}
		bool overlap(const vector<int>& rect) {
			return min(rect[2], right) > max(rect[0], left) && min(rect[3], top) > max(rect[1], bottom);
		}
		long long calcArea() {
			return ((long long)(right - left))*((long long)(top - bottom));
		}
	};
	Node *root;
	void add(Node *node, const vector<int>& rect) {
		//cout << "[(" << node->left << ", " << node->bottom << "), (" << node->right << ", " << node->top << ")]" << endl;
		if (!node->overlap(rect) || node->covered == node->calcArea()) return;
		if (node->inside(rect)) {
			//long t = node->calcArea();
			//cout << "[(" << node->left << ", " << node->bottom << "), (" << node->right << ", " << node->top << ")]" << endl;
			//cout << "add area = " << node->calcArea() - node->covered << endl;
			node->covered = node->calcArea();
		}
		else {
			if (node->leftChild) {

			}
			else if (node->insideY(rect)) {
				int mid = node->left + (node->right - node->left) / 2;
				node->leftChild = new Node(node->left, node->bottom, mid, node->top);
				node->rightChild = new Node(mid, node->bottom, node->right, node->top);
			}
			else {
				int mid = node->bottom + (node->top - node->bottom) / 2;
				node->leftChild = new Node(node->left, node->bottom, node->right, mid);
				node->rightChild = new Node(node->left, mid, node->right, node->top);
			}
			add(node->leftChild, rect);
			add(node->rightChild, rect);
			node->covered = node->leftChild->covered + node->rightChild->covered;
		}
		if(node->covered == node->calcArea()) {
			delete node->leftChild;
			delete node->rightChild;
			node->leftChild = NULL;
			node->rightChild = NULL;
		}
	}
public:
	int rectangleArea(const vector<vector<int>> &rectangles) {
		root = new Node(0, 0, 1000000000, 1000000000);
		for (auto & rect : rectangles) {
			cout << " -------- add " << rect << " --------- " << endl;
			add(root, rect);
			cout << " -------- area after add = " << root->covered << endl;
		}
		return root->covered % 1000000007;
	}
};

class Solution2 {
private:
    struct Node {
        int start, end;
        vector<int> lows, highs;
        Node *left, *right;
        Node(int s, int e, const vector<int> &l, const vector<int> &h) : start(s), end(e), lows(l), highs(h), left(NULL), right(NULL){}
        long long area() {
            return 0;
        }
        bool overlap(const vector<int>& rect){
            return max(start, rect[0]) < min(end, rect[2]);
        }
        bool inside(const vector<int>& rect){
            return start >= rect[0] && end <= rect[2];
        }
        long long add(const vector<int>& rect) {
			//cout << "[" << start << ", " << end << "): ";
            int delta = 0;
			int d1 = lower_bound(highs.begin(), highs.end(), rect[1]) - highs.begin();
            int d2 = upper_bound(lows.begin(), lows.end(), rect[3]) - lows.begin();
            if(lows.empty() || d1 == highs.size()) {
                lows.push_back(rect[1]);
                highs.push_back(rect[3]);
                delta = rect[3] - rect[1];
            }
            else {
                int oldlen = 0;
                for(int i = d1; i < d2; i++)
                    oldlen += highs[i] - lows[i];
                int newlow = min(rect[1], lows[d1]);
                int newhigh = max(rect[3], d2 ? highs[d2-1] : 0);
                delta = newhigh - newlow - oldlen;
                
				if(d2 == 0 || oldlen == 0) {
					lows.insert(lows.begin() + d1, rect[1]);
					highs.insert(highs.begin() + d1, rect[3]);
				}
				else {
					lows[d1] = newlow;
					highs[d1] = newhigh;
					lows.erase(lows.begin() + d1 + 1, lows.begin() + d2);
					highs.erase(highs.begin() + d1 + 1, highs.begin() + d2);
				}
            }
			//cout << lows << ", " << highs << endl;
            return (long long)(end - start) * (long long)delta;
        }
    };
    Node *root;
    long long total;
    
    void add(Node *node, const vector<int>& rect){
        if(!node->overlap(rect)) return;
        if(node->left) {
            add(node->left, rect);
            add(node->right, rect);
        }
        else if(node->inside(rect)){
            total += node->add(rect);
        }
        else {
            int mid = node->start + (node->end - node->start) / 2;
            node->left = new Node(node->start, mid, node->lows, node->highs);
            node->right = new Node(mid, node->end, node->lows, node->highs);
            add(node->left, rect);
            add(node->right, rect);
        }
    }
public:
    int rectangleArea(vector<vector<int>>& rectangles) {
        root = new Node(0, 1000000000, vector<int>(), vector<int>());
        total = 0;
        for(auto &rect : rectangles) add(root, rect);
        return total % 1000000007;
    }
};

class Solution3 {
public:
    int rectangleArea(vector<vector<int>>& rectangles) {
        vector<int> x;
        for (auto& rect : rectangles) {
            x.push_back(rect[0]);
            x.push_back(rect[2]);
        }
        sort(x.begin(), x.end());
        x.erase(unique(x.begin(), x.end()), x.end());
        unordered_map<int, int> xi;
        for (size_t i = 0; i < x.size(); i++) {
            xi[x[i]] = i;
        }
        vector<vector<int>> lines;
        for (auto& rect : rectangles) {
            //lines.emplace_back(vector<int>{rect[1], 1, rect[0], rect[2]});
            //lines.emplace_back(vector<int>{rect[3], -1, rect[0], rect[2]});
        }
        sort(lines.begin(), lines.end());

        const int M = 1e9 + 7;
        SegmentTree tree(x);
        long long y0 = 0, len = 0, area = 0;
        for (auto& line : lines) {
            long long y = line[0], val = line[1], x1 = line[2], x2 = line[3];
            area = (area + (y - y0) * len) % M;
            y0 = y;
            
            len = tree.update(xi[x1], xi[x2], val);
        }
        return area % M;
    }
    
private:
    class SegmentTree {
    public:
        SegmentTree(vector<int>& x) : n(x.size()), x(x), cnt(4 * n), len(4 * n) {
        }
        
        int update(int l, int r, int val) {
            return update(0, 0, n - 1, l, r, val);
        }
        
        int update(int k, int lo, int hi, int i, int j, int val) {
            if (j <= lo || i >= hi) {
                return 0;
            }
            if (i <= lo && hi <= j) {
                cnt[k] += val;
                return pushup(k, lo, hi);
            }
            int mid = (lo + hi) / 2;
            if (j <= mid) {
                update(2 * k + 1, lo, mid, i, j, val);
            } else if (i >= mid) {
                update(2 * k + 2, mid, hi, i, j, val);
            } else {
                update(2 * k + 1, lo, mid, i, mid, val);
                update(2 * k + 2, mid, hi, mid, j, val);
            }
            return pushup(k, lo, hi);
        }
        
        int pushup(int k, int lo, int hi) {
            if (cnt[k] > 0) {
                len[k] = x[hi] - x[lo];
            } else if (lo + 1 == hi) {
                len[k] = 0;
            } else {
                len[k] = len[2 * k + 1] + len[2 * k + 2];
            }
            return len[k];
        }

    private:
        const int n;
        const vector<int>& x;
        vector<int> cnt, len;
    };
};

class Solution4 {
public:
    int rectangleArea(vector<vector<int>>& rectangles) {
        int mod = 1000000000 + 7;
        vector<int> x(1, 0);
        for (auto r : rectangles) {
            x.push_back(r[0]);
            x.push_back(r[2]);
        }
        sort(x.begin(), x.end());
        vector<int>::iterator end_unique = unique(x.begin(), x.end());
        x.erase(end_unique, x.end());
        unordered_map<int, int> x_i;
        for (int i = 0; i < x.size(); ++i) {
            x_i[x[i]] = i;
        }
        vector<int> count(x.size(), 0);
        vector<vector<int>> L;
        for (auto r : rectangles) {
            int x1 = r[0], y1 = r[1], x2 = r[2], y2 = r[3];
            //L.push_back({y1, x1, x2, 1});
            //L.push_back({y2, x1, x2, -1});
        }
        sort(L.begin(), L.end());
        long long cur_y = 0, cur_x_sum = 0, area = 0;
        for (auto l : L) {
            long long  y = l[0], x1 = l[1], x2 = l[2], sig = l[3];
            area = (area + (y - cur_y) * cur_x_sum) % mod;
            cur_y = y;
            for (int i = x_i[x1]; i < x_i[x2]; i++)
                count[i] += sig;
            cur_x_sum = 0;
            for (int i = 0; i < x.size(); ++i) {
                if (count[i] > 0)
                    cur_x_sum += x[i + 1] - x[i];
            }
        }
        return area;
    }
};

void testRectangleAreaII() {
	vector<vector<int>> rectangles;
	cin >> rectangles;
	printVectorNewline(rectangles);
	Solution2 mysol;
	int a = mysol.rectangleArea(rectangles);
	cout << "The total covered area is " << a << endl;
}