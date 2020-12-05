#include<set>
#include<iostream>

using namespace std;

int main()
{
	set<int> set1;
	set1.insert(10);
	set1.insert(20);
	set1.insert(30);
	set1.insert(2);
	set1.insert(100);

	for (set<int>::iterator iter = set1.begin(); iter != set1.end() ; iter++) {
		cout << *iter << endl;
	}

	set<int>::iterator iter = set1.begin();
	iter++;
	set1.insert(iter, 90);

	cout << "90을 추가 후 set1의 모든 요소 출력" << endl;


	for (set<int>::iterator iter = set1.begin(); iter != set1.end(); iter++) {
		cout << *iter << endl;
	}

	return 0;
}