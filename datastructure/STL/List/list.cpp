#include<iostream>
#include<list>

using namespace std;

int main()
{
    list<int> list1;
    list<int>::iterator iter= list1.begin();
    int a=0;
    int i=0;
    while(i < 10){
        a=list1.size();
        list1.push_front(a);
        i++;
    }

    for(list<int>::iterator iter= list1.begin(); iter != list1.end(); iter++){
        cout << "listÀÇ ¿ä¼Ò" << *iter << endl;
        cout << list1.front()++ << endl;
        cout << list1.begin()<< endl;
    }


    return 0;
}