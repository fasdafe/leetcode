// LC # 399: evaluate divisions

#include "utils.h"

using namespace std;

class Solution {
private:
    vector<int> parents;
    vector<double> division; // stores the value of variable parents[i] / value of variable i
    vector<int> ranks;
    unordered_map<string, int> variables;
public:
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        int nVar = 0;
        for(auto &eq : equations) {
            for(string &var : eq) {
                if(variables.count(var) == 1) continue;
                else {
                    parents.push_back(nVar);
                    variables[var] = nVar++;
                }
            }
        }
        ranks = vector<int>(nVar, 0);
        division = vector<double>(nVar, 1.0);
        
        for(int i = 0; i < equations.size(); i++) {
            union_helper(variables[equations[i][0]], variables[equations[i][1]], values[i]);
        }
        
        vector<double> results;
        for(auto &q : queries) {
            if(variables.count(q[0]) == 0 || variables.count(q[1]) == 0 || find(variables[q[0]]) != find(variables[q[1]]))
                results.push_back(-1.0);
            else results.push_back(division[variables[q[1]]] / division[variables[q[0]]]);
        }
        return results;
    }
    
    int find(int i) {
        if(parents[i] != i) {
            int p = parents[i];
            parents[i] = find(parents[i]);
            division[i] *= division[p];
        }
        return parents[i];
    }
    
    bool union_helper(int x, int y, double d) {
        int px = find(x), py = find(y);
        if(px == py) return false;
        if(ranks[px] < ranks[py]) {
            parents[px] = py;
            division[px] = division[y] / d / division[x];
        }
        else {
            parents[py] = px;
            division[py] = division[x] * d / division[y];
            if(ranks[px] == ranks[py]) ranks[px]++;
        }
        return true;
    }
};

void testCalcEquation() {
	vector<vector<string>> equations;
	vector<double> values;
	vector<vector<string>> queries;

	cin >> equations >> values >> queries;

	vector<double> results;
	Solution sol;
	results = sol.calcEquation(equations, values, queries);
	cout << results << endl;
}