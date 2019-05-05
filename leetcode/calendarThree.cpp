// #732
#include "utils.h"
using namespace std;

class MyCalendarThree {
private:
	map<int, int> delta;
public:
    MyCalendarThree() {
        
    }
    
    int book(int start, int end) {
        delta[start]++;
		delta[end]--;
		int res = 0, m = 0;
		for(auto &d : delta){
			res += d.second;
			if(res > m) m = res;
		}
		return m;
    }
};

/**
 * Your MyCalendarThree object will be instantiated and called as such:
 * MyCalendarThree obj = new MyCalendarThree();
 * int param_1 = obj.book(start,end);
 */

class MyCalendarThree1 {
private:
    map<int, int> count;
    int res;
public:
    MyCalendarThree1() {
        count[-1] = 0;
		res = 0;
    }

    int book(int s, int e) {
        auto start = count.emplace(s, (--count.lower_bound(s))->second).first;
        auto end = count.emplace(e, (--count.lower_bound(e))->second).first;
        for (auto i = start; i != end; ++i) res = max(res, ++(i->second));
        return res;
    }
};

void testMyCalendarThree() {
	MyCalendarThree1 cal;
	cal.book(10, 20); // returns 1
	cal.book(50, 60); // returns 1
	cal.book(10, 40); // returns 2
	cal.book(5, 15); // returns 3
	cal.book(5, 10); // returns 3
	cal.book(25, 55); // returns 3
}