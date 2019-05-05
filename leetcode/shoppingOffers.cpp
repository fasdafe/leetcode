// LeetCode #638: Shopping Offers
#include "utils.h"

using namespace std;

int helper(const vector<int>& disc, int start, const vector<vector<int>>& spec, const vector<int>& needs, vector<int>& solution){
	//
	//cout << "------- START -------" << endl
	//	<< "disc = " << disc << endl
	//	<< "start = " << start << endl
	//	<< "spec = " << spec << endl
	//	<< "needs = " << needs << endl
	//	<< "solution = " << solution << endl
	//	<< "------- END --------" << endl;
	//
	if(start == disc.size()) return 0;
	solution[start] = 0;
	int best = helper(disc, start+1, spec, needs, solution), cur, i;
	if(disc[start] <= 0) return best;
	vector<int> remains = needs, saved = solution;
	while(true){
		for(i = 0; i < remains.size(); i++) {
			remains[i] -= spec[start][i];
			if(remains[i] < 0) break;
		}
		if(i < remains.size()) break;
		solution[start]++;
		cur = helper(disc, start+1, spec, remains, solution) + solution[start] * disc[start];
		if(cur > best){
			best = cur;
			saved = solution;
		}
	}
	solution = saved;
	return best;
}

int shoppingOffers(vector<int>& price, vector<vector<int>>& special, vector<int>& needs) {
	int nItems = price.size(), nOffer = special.size();
	vector<int> discount(nOffer), solution(nOffer);
	for(int i = 0; i < nOffer; i++){
		discount[i] = inner_product(price.begin(),price.end(),special[i].begin(),0) - special[i].back();
	}

	int savings = helper(discount, 0, special, needs, solution);
	cout << "Price = " << price << endl
		<< "Offers = " << special << endl
		<< "Needs = " << needs << endl
		<< "Solution = " << solution << endl
		<< "Optimal price = ";
	return inner_product(price.begin(),price.end(),needs.begin(),0)-savings;
}


void testShoppingOffers(){
//	[2,5]
//[[3,0,5],[1,2,10]]
//[3,2]
	//typedef int tp[3];
	//tp ss[] = {{3,0,5},{1,2,10}};
	const int N = 3;
	int p[] = {2,5}, sp[][N] = {{3,0,5},{1,2,10}}, nd[] = {3,2};
	vector<int> price = arrayToVector(p, 2), needs = arrayToVector(nd, 2);
	vector<vector<int>> special = arrayToVector2D<int>(sp, sizeof(sp)/sizeof(int[N]), N);
	cout << shoppingOffers(price, special, needs) << endl;
}