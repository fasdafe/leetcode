// #731: https://leetcode.com/problems/my-calendar-ii/
#include "utils.h"
using namespace std;

class MyCalendarTwo {
private:
	map<int, int> delta;
public:
    MyCalendarTwo() {
        
    }
    
    bool book(int start, int end) {
        delta[start]++;
        delta[end]--;
        int booked = 0;
        for (auto &d : delta) {
            booked += d.second;
            if (booked == 3) {
                delta[start]--;
                delta[end]++;
                return false;
            }
        }
        return true;
    }
};

/**
 * Your MyCalendarTwo object will be instantiated and called as such:
 * MyCalendarTwo* obj = new MyCalendarTwo();
 * bool param_1 = obj->book(start,end);
 */

class MyCalendarTwo1 {
public:
    MyCalendarTwo1() {}
    
    bool book(int start, int end) {
        for (auto a : s2) {
            if (start >= a.second || end <= a.first) continue;
            else return false;
        }
        for (auto a : s1) {
            if (start >= a.second || end <= a.first) continue;
            else s2.insert(make_pair(max(start, a.first), min(end, a.second)));
        }
        s1.insert(make_pair(start, end));
        return true;
    }

private:
    set<pair<int, int>> s1, s2;
};

void testMyCalendarTwo(){
	MyCalendarTwo1 cal;
	int t[] = {26, 35, 26, 32, 25, 32, 18, 26, 40, 45, 19, 26, 48, 50, 1, 6, 46, 50, 11, 18};
	int n = sizeof(t)/sizeof(int);
	vector<int> start, end;
	for(int i = 0; i < n; ){
		start.push_back(t[i++]);
		end.push_back(t[i++]);
	}
	for (int i = 0; i < n/2; i++) {
		cout << "[" << start[i] << ", " << end[i] << "): ";
		bool b = cal.book(start[i], end[i]);
		cout << (b ? "true" : "false") << endl;
	}
}