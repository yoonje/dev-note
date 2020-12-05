#include<set>
#include<iostream>
#include<functional>

using namespace std;

int main()
{
	set<int> set1;
	set1.insert(10);
	set1.insert(15);
	set1.insert(12);

	for (set<int>::iterator iter = set1.begin(); iter != set1.end() ; iter++) {
		cout << *iter << endl;
	}

	set<int>::iterator findIter = set1.find(15);

	if (findIter != set1.end()) {
		set1.insert(findIter,11);
	}

	for (set<int>::iterator iter = set1.begin(); iter !=set1.end() ; iter++) {
		cout << *iter << endl;
	}

	return 0;
}