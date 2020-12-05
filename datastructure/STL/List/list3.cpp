#include<iostream>
#include<list>

using namespace std;

int main()
{
    list<int> list1;
    list<int> list2;
    list1.push_back(20);
    list1.push_back(30);

    cout << "»ğÀÔ Å×½ºÆ® 1" << endl;
    list<int>::iterator iterBeg = list1.begin();
    list1.insert(iterBeg, 100);

    list<int>::iterator iterEnd = list1.end();                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               
    for(list<int>::iterator iterBeg = list1.begin(); iterBeg != iterEnd ; iterBeg++){
        cout << "list 1 :" << *iterBeg<<endl;
    }

    cout << "»ğÀÔ Å×½ºÆ® 2" << endl;
    iterBeg = list1.begin();
    ++iterBeg;
    list1.insert(iterBeg, 2, 200);

    iterEnd = list1.end();                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               
    for(list<int>::iterator iterBeg = list1.begin(); iterBeg != iterEnd ; iterBeg++){
        cout << "list 1 :" << *iterBeg<<endl;
    }

    cout << "»ğÀÔ Å×½ºÆ® 3" << endl;
    list2 = list1;
    iterEnd = list2.end();                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               
    for(list<int>::iterator iterBeg = list2.begin(); iterBeg != iterEnd ; iterBeg++){
        cout << "list 2 :" << *iterBeg<<endl;
    }

    return 0;
}