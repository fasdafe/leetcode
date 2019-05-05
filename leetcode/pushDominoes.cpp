// #838
#include "utils.h"
using namespace std;

class Solution {
public:
    string pushDominoes(string dominoes) {
        int n = dominoes.size();
        vector<int> fromRight(n, 0), fromLeft(n, 0);
        int lastRight = dominoes[n-1] == 'L' ? n-1 : n;
        for(int i = n-2; i >= 0; i--) {
            if(dominoes[i] == '.') {
                if(lastRight < n) fromRight[i] = lastRight - i;
			}
            else if(dominoes[i] == 'L') lastRight = i;
            else lastRight = n;
        }
        int lastLeft = dominoes[0] == 'R' ? 0 : -1;
        for(int i = 1; i < n; i++) {
            if(dominoes[i] == '.') {
                if(lastLeft >= 0) fromLeft[i] = i - lastLeft;
			}
            else if(dominoes[i] == 'R') lastLeft = i;
            else lastLeft = -1;
        }
        string res = dominoes;
        for(int i = 0; i < n; i++) {
            if(fromLeft[i] && fromRight[i]) {
                if(fromLeft[i] < fromRight[i]) res[i] = 'R';
                else if(fromLeft[i] > fromRight[i]) res[i] = 'L';
            }
            else if(fromLeft[i]) res[i] = 'R';
            else if(fromRight[i]) res[i] = 'L';
        }
        return res;
    }
};

class Solution1 {
public:
    string pushDominoes(string dominoes) {
        string res = "";
        dominoes = "L" + dominoes + "R";
        for (int i = 0, j = 1; j < dominoes.size(); ++j) {
            if (dominoes[j] == '.') continue;
            int mid = j - i - 1;
            if (i > 0) res += dominoes[i];
            if (dominoes[i] == dominoes[j]) res += string(mid, dominoes[i]);
            else if (dominoes[i] == 'L' && dominoes[j] == 'R') res += string(mid, '.');
            else res += string(mid / 2, 'R') + string(mid % 2, '.') + string(mid / 2, 'L');
            i = j;
        }
        return res;
    }
};

class Solution2 {
public:
    string pushDominoes(string dominoes) {
        int n = dominoes.size();
        vector<int> cnt(n);
        for (int i = 1; i < n; ++i) {
            if (dominoes[i - 1] == 'R' && dominoes[i] == '.') {
                dominoes[i] = 'R';
                cnt[i] = cnt[i - 1] + 1;
            }
        }
        for (int i = n - 2, cur = 0; i >= 0; --i) {
            if (dominoes[i + 1] != 'L') continue;
            cur = cnt[i + 1] + 1;
            if (dominoes[i] == '.' || cnt[i] > cur) {
                dominoes[i] = 'L';
                cnt[i] = cur;
            } else if (dominoes[i] == 'R' && cnt[i] == cur) {
                dominoes[i] = '.';
            }
        }
        return dominoes;
    }
};

void testPushDominoes(){
	string dominoes;
	cin >> dominoes;
	Solution1 mysol;
	string res = mysol.pushDominoes(dominoes);
	cout << res << endl;
}