#include<iostream>
#include<list>

using namespace std;

template <typename T> class COMPARE_ITEM
{
    public:
    bool operator() (const T A, const T B) const
    {
        return A.ItemCd < B.ItemCd;
    }
};

class Item
{
    public:
    Item(int ItemCd, int buyMoney)
    {
        ItemCd = ItemCd;
        buyMoney = buyMoney;
    }
    int ItemCd;
    int buyMoney;
};

int main()
{
    list<int> list1;
    list1.push_back(20);
    list1.push_back(10);
    list1.push_back(30);
    list1.push_back(40);

    cout << "Sort 올림차순" << endl;
    list1.sort();

    list<int>::iterator iterEnd = list1.end();
    for(list<int>::iterator iter = list1.begin(); iter != iterEnd ;++iter){
        cout << "list1 : " << *iter << endl;
    }

    cout << "Sort 내림차순" << endl;
    list1.sort(greater<int>());
    
    iterEnd = list1.end();
    for(list<int>::iterator iter = list1.begin(); iter !=iterEnd ;++iter){
        cout << "list1 :" << *iter << endl;
    }

    cout << "사용자 정의 Sort" << endl;

    list<Item> Itemlist;

    Item item1(20,100);
    Item item2(10,200);
    Item item3(30,300);
    
    Itemlist.push_back(item1);
    Itemlist.push_back(item2);
    Itemlist.push_back(item3);

    Itemlist.sort(COMPARE_ITEM<Item>());
    list<Item>::iterator iterEnd2 = Itemlist.end();
    for(list<Item>::iterator iter = Itemlist.begin(); iter != iterEnd2 ;++iter){
        cout << "Itemlist :" << iter->ItemCd << endl;
    }
    return 0;
}