#include<set>
#include<iostream>

using namespace std;

int main()
{
	multiset<int> ms;

	ms.insert(9);
	ms.insert(10);
	ms.insert(11);
	ms.insert(12);
	ms.insert(13);

	multiset<int>::iterator iter;
	for (iter = ms.begin(); iter != ms.end() ; iter++) {
		cout << *iter << " " << endl;
	}

	multiset<int>::iterator start;
	multiset<int>::iterator end;

	start = ms.lower_bound(10);
	end = ms.upper_bound(12);

	for (iter = start; iter != end; iter++) {
		cout << *iter << " " << endl;
	}

	return 0;
}