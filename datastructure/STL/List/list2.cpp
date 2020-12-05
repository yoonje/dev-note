#include<iostream>
#include<list>

using namespace std;

class Item{
public:
    Item(int itemCd, int buyMoney)
    {
        ItemCd = itemCd;
        buyMoney = buyMoney;
    }
    int ItemCd;
    int BuyMoney;
};

int main()
{                                                                                                                        
    list<Item> Itemlist;

    Item item1(1,2000);
    Itemlist.push_front(item1);

    Item item2(2,3000);
    Itemlist.push_front(item2);

    Item item3(3,4000);
    Itemlist.push_front(item3);

    list<Item>::iterator iterEnd = Itemlist.end();
    for(list<Item>::iterator iterBeg = Itemlist.begin(); iterBeg != iterEnd ; ++iterBeg){
        cout<< "아이템 코드: "<< iterBeg->ItemCd<<endl;
    }

    // 앞 데이터 삭제
    Itemlist.pop_front();
    Item front_item = Itemlist.front();
    cout<< "아이템 코드: "<<front_item.ItemCd << endl;

    // 마지막 데이터 삭제
    Itemlist.pop_back();
    Item back_item = Itemlist.back();
    cout<< "아이템 코드 "<<back_item.ItemCd << endl;
    
    if(false == Itemlist.empty()){
        list<Item>::size_type count = Itemlist.size();
        cout << "남아 있는 아이템의 개수: "<< count << endl;
    }

    Itemlist.clear();

    list<Item>::size_type count = Itemlist.size();
    cout << "남아 있는 아이템의 개수: "<< count << endl;

    return 0;
}