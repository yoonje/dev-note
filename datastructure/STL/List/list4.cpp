#include<iostream>
#include<list>

using namespace std;

int main()
{
    list<int> list1;

    list1.push_front(10);
    list1.push_front(20);
    list1.push_front(30);
    list1.push_front(40);
    
    cout<< "erase Å×½ºÆ® 1" << endl;

    list1.erase(list1.begin());

    list<int>::iterator iterEnd = list1.end();
    for(list<int>::iterator iter = list1.begin(); iter !=iterEnd; ++iter){
        cout << "list 1 : " << *iter << endl;
    }
    cout << endl;

    list<int>::iterator iter = list1.begin();
    ++iter;
    list1.erase(iter,list1.end());

    iterEnd = list1.end();
    for( iter = list1.begin(); iter != iterEnd; ++iter){
        cout << "list 1 : "<< *iter <<endl;
    }
    return 0;
}