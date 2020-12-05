#include<map>
#include<iostream>
#include<string>
using namespace std;

int main()
{
	multimap<int, int> mm;

	mm.insert(pair<int, int>(60, 30));
	mm.insert(pair<int, int>(50, 20));
	mm.insert(pair<int, int>(10, 20));

	multimap<int, int>::iterator iter;

	cout << "mm.size() " << mm.size() << endl;
	cout << "mm.count(10) " << mm.count(10) << endl;
	cout << "mm.upper() " << mm.upper_bound(10)->first << endl;

	multimap<int, string> mm2;
	mm2.insert(pair<int, string>(10, "C"));
	mm2.insert(pair<int, string>(20, "C++"));
	mm2.insert(pair<int, string>(30, "Java"));
	mm2.insert(pair<int, string>(40, "Java Script"));
	mm2.insert(pair<int, string>(50, "Go"));

	multimap<int, string>::iterator iter2;
	multimap<int, string>::iterator upper_iter = mm2.upper_bound(10);
	multimap<int, string>::iterator lower_iter = mm2.lower_bound(20);

	cout << "mm2.size() " << mm2.size() << endl;
	cout << "mm2.count(10) " << mm2.count(10) << endl;

	for (iter2 = mm2.begin(); iter2 != mm2.end(); iter2++) {
		cout << iter2->first << "," << iter2->second << endl;
	}


	return 0;
}