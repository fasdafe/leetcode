#ifndef _UTILS_H_
#define _UTILS_H_

#include <vector>
#include <iostream>
#include <ctime>
#include <string>
#include <queue>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <numeric>
#include <stack>
#include <sstream>
#include <functional>

template < typename T >
void printVector(const std::vector<T>& v, size_t n){
	size_t k = min(n, v.size());
	std::cout << "[";
	for(size_t i = 0; i+1 < k; i++)
		std::cout << v[i] << ", ";
	if(k) std::cout << v[k-1];
	std::cout << "]" << std::endl;
}

template < typename T >
void printVector(const std::vector<T>& v){
	//printVector(v, v.size());
	std::cout << v << std::endl;
}

template < typename T >
void printVectorNewline(const std::vector<T>& v, size_t n){
	size_t k = min(n, v.size());
	std::cout << "[" << std::endl;
	for(size_t i = 0; i+1 < k; i++)
		std::cout << v[i] << ", " << std::endl;
	if(k) std::cout << v[k-1] << std::endl;
	std::cout << "]" << std::endl;
}

template <typename T, typename S>
std::ostream& operator<<(std::ostream& os, const std::pair<T, S>& p){
	os << "(" << p.first << "," << p.second << ")";
	return os;
}

template < typename T >
void printVectorNewline(const std::vector<T>& v){
	printVectorNewline(v, v.size());
}

template < typename T >
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v){
	size_t k = v.size();
	os << "[";
	for(size_t i = 0; i+1 < k; i++)
		os << v[i] << ", ";
	if(k) os << v[k-1];
	return os << "]";
}

//template < typename T >
//std::ostream& operator<<(std::ostream& os, const std::vector<std::vector<T>>& v){
//	size_t k = v.size();
//	os << "[";
//	for(size_t i = 0; i+1 < k; i++)
//		os << v[i] << ", ";
//	if(k) os << v[k-1];
//	return os << "]";
//}

// https://stackoverflow.com/questions/6964819/function-already-defined-error-in-c
// https://stackoverflow.com/questions/14517546/how-can-a-c-header-file-include-implementation
// https://en.wikipedia.org/wiki/One_Definition_Rule
// if keyword "inline" is not used below, then One Definition Rule is violated if this header 
// in included in multiple files. We can also declare the function as "static", but "inline" 
// is more efficient. We can also implement the function as a template!
//template < typename T >
//std::istream& operator>>(std::istream& is, std::vector<T>& v){
//	T val;
//	v.clear();
//	char c;
//	std::cin >> c;
//	if(c == '{' || c == '['){
//		while(is >> val >> c) {
//			v.push_back(val);
//			if(c == '}' || c == ']') break;
//		}
//	}
//	is.clear();
//	std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
//	return is;
//}

template <typename T>
bool operator>>(const std::string& s, T& t) {
	std::stringstream ss;
	ss << s;
	return static_cast<bool>(ss >> t);
}

template <typename T>
bool operator>>(std::string& s, std::vector<T>& v) {
	//std::copy(std::istream_iterator<T>(is), std::istream_iterator<T>(),
	//	std::back_inserter(v));
	using namespace std;
	
	s.erase(s.begin());
	if(!s.empty()) s.pop_back();

	v.clear();

	if(s.find('[')==string::npos){ // 1D array
		T item;
		stringstream ss; 
		ss << s;
		string subs;
		while(!ss.eof()){
			ss >> subs;
			if(subs.length() > 0 && subs.back() == ',') subs.pop_back();
			if(subs >> item)
				v.push_back(item);
			else{
				v.clear();
				return false;
			}
			subs = "";
		}
	}
	else{
		string subs;
		size_t first = 0, last = 0, net, cur;
		T t;

		while(1){
			first = s.find('[', first);
			if(first == string::npos) break;
			cur = first;
			net = 0;
			do{
				if(s[cur] == '[') net++;
				else if(s[cur] == ']') net--;
				cur++;
			}while(cur<s.size() && net>0);

			subs = s.substr(first, cur-first);
			if(!(subs >> t)) return false;
			v.push_back(t);
			first = cur;
		}
	}
	return true;
}


template <typename T>
std::stringstream& operator>>(std::stringstream& ss, std::vector<T>& v) {
	std::string s = ss.str();
	s >> v;
	//ss.clear();
	//ss.ignore(numeric_limits<streamsize>::max(), '\n');
	return ss;
}

template <typename T>
std::istream& operator>>(std::istream& is, std::vector<T>& v) {
	//std::copy(std::istream_iterator<T>(is), std::istream_iterator<T>(),
	//	std::back_inserter(v));
	using namespace std;
	string s;
	getline(is, s);
	//is.clear();
	//is.ignore(numeric_limits<streamsize>::max(), '\n');

	s >> v;

	return is;
}

template < typename T >
std::vector<T> arrayToVector(T* ar, int n){
	std::vector<T> v(n);
	for(int i = 0; i < n; i++){
		v[i] = *(ar+i);
	}
	return v;
}

template < typename T >
std::vector<std::vector<T>> arrayToVector2D(void* ar, int m, int n){
	std::vector<std::vector<T>> v(m, std::vector<T>(n));
	T *p = (T*)ar;
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			v[i][j] = *(p+i*n+j);
		}
	}
	return v;
}

//template < typename T >
//std::vector<std::vector<T>> arrayToVector2D(T* ar, int m, int n){
//	std::vector<std::vector<T>> v(m, std::vector<T>(n));
//	//T *p = (T*)ar;
//	for(int i = 0; i < m; i++){
//		for(int j = 0; j < n; j++){
//			v[i][j] = *(ar+i*n+j);
//		}
//	}
//	return v;
//}


//Definition for a binary tree node.
template < typename T >
struct TTreeNode {
    T val;
    TTreeNode *left;
    TTreeNode *right;
    TTreeNode(T x) : val(x), left(NULL), right(NULL) {}
};

template < typename T >
TTreeNode<T>* buildBinaryTree(const std::vector<std::string>& v){
	if(v.empty()) return NULL;
	using namespace std;
	T val;
	TTreeNode<T>* root, *cur;
	if(v[0] >> val) root = new TTreeNode<T>(val);
	else return NULL;
	queue<TTreeNode<T>*> q;
	q.push(root);
	int pos = 1, n = v.size();
	while(!q.empty()){
		cur = q.front();
		q.pop();
		if(pos < n && v[pos] != "null") {
			v[pos] >> val;
			cur->left = new TTreeNode<T>(val);
			q.push(cur->left);
		}
		if(pos+1 < n && v[pos+1] != "null") {
			v[pos+1] >> val;
			cur->right = new TTreeNode<T>(val);
			q.push(cur->right);
		}
		pos += 2;
	}
	return root;
}

template <typename T>
void printBinaryTree(TTreeNode<T> *root, bool newline = false){
	using namespace std;
	if(root == NULL) cout << "[]" << endl;
	queue<TTreeNode<T>*> que;
	que.push(root);
	string s;
	s = "[" + to_string(root->val);
	while(!que.empty()){
		if(newline) s += "\n";
		int k = que.size();
		for(int i = 0; i < k; i++){
			TTreeNode<T> *node = que.front();
			que.pop();
			//if(que.empty()) 
			if(node->left) {
				s += ", " + to_string(node->left->val);
				que.push(node->left);
			}
			else s += ", null";
			if(node->right) {
				s += ", " + to_string(node->right->val);
				que.push(node->right);
			}
			else s += ", null";
		}
	}
	s += "]";
	cout << s << endl;
}


typedef TTreeNode<int> TreeNode;

#endif