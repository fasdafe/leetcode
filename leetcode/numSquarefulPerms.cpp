// # 996

#include "utils.h"

using namespace std;

class Solution {
private:
    vector<vector<int>> memo;
    unordered_map<int, vector<int>> graph;
public:
    int numSquarefulPerms(vector<int>& A) {
        int n = A.size();
        // this is a problem to find the number of
        // Hamilton paths in a graph where two nodes
        // i and j are adjacent if A[i]+A[j] is a
        // perfect square
        
        memo = vector<vector<int>>(n, vector<int>(1<<n, -1));
        
        for(int i = 0; i < n; i++){
            for(int j = i+1; j < n; j++){
                int x = A[i], y = A[j], z = int(sqrt(x+y)+0.5);
                if(z*z==x+y) {
                    graph[i].push_back(j);
                    graph[j].push_back(i);
                }
            }
        }
        
        int res = 0;
        for(int i = 0; i < n; i++) res += dfs(i, 1<<i);
        
        unordered_map<int, int> count;
        for(auto a : A) count[a]++;
        
        vector<int> factorial(13, 1);
        for(int i = 1; i <= 12; i++) factorial[i] = i*factorial[i-1];
        
        for(auto c : count) res /= factorial[c.second];
        
        return res;
    }
    
    int dfs(int i, int visited){
        if(visited == (1<<memo.size())-1) return 1;
        if(memo[i][visited] >= 0) return memo[i][visited];
        int res = 0;
        for(auto j : graph[i])
            if((visited & (1<<j)) == 0)
                res += dfs(j, visited | (1<<j));
        memo[i][visited] = res;
        return res;
    }
};

void testNumSquarefulPerms(){
	Solution mysolution;
	int nums[] = {1, 8, 17};
	vector<int> A(nums, nums+3);
	cout << A << endl 
		<< mysolution.numSquarefulPerms(A) << endl;
}