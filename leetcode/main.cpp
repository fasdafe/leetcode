#include "utils.h"

void test(int id);

int main(){
	using namespace std;
	int id;

	while(1)
	{
		id = 0;
		cout << "Type problem id: ";
		cin >> id;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		if(id == 0) break;
		test(id);
	}

	return 0;
}