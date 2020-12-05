#include<iostream>
#include<list>

using namespace std;

int main()
{
    list<int> list1;
    
    list1.push_back(10);
    list1.push_back(20);
    list1.push_back(30);

    list<int>::iterator iter = list1.begin();

    while(iter != list1.end()){
        cout << "erase:" << list1.front() << endl;
        list1.erase(iter);
        iter = list1.begin();
    }

    list1.push_back(10);
    list1.push_back(20);
    list1.push_back(30);

    cout << "erase:"<< 10 << endl;
    list1.remove(10);

    iter = list1.begin();
    cout << list1.front();
    return 0;
}