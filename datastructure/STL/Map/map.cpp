#include<iostream>
#include<map>
#include<string>
using namespace std;

class Item {
public:
	char name[32];
	char kind;
	int BuyMoney;
	int SkillCd;
};

int main()
{
	map<const char*, Item> Items;
	map<const char*, Item>::iterator iter;

	typedef pair<const char*, Item> ItemPair;

	Item item1;
	Item item2;
	Item item3;

	strncpy(item1.name, "긴칼", 10);
	strncpy(item2.name, "방패", 10);
	strncpy(item3.name, "해머", 10);

	item1.kind = 1;
	item2.kind = 2;
	item3.kind = 3;

	item1.BuyMoney = 100;
	item2.BuyMoney = 200;
	item3.BuyMoney = 300;

	item1.SkillCd = 0;
	item2.SkillCd = 1;
	item3.SkillCd = 2;

	Items.insert(map<char*, Item>::value_type(item2.name, item2));
	Items.insert(ItemPair(item1.name, item1));

	if (false == Items.empty()) {
		cout << "저장된 아이템 개수" << Items.size() << endl;
	}

	for (iter = Items.begin(); iter != Items.end(); iter++) {
		cout << "이름: " << iter->first << "가격: " << iter->second.BuyMoney << endl;
	}

	iter = Items.find("긴칼");

	if (iter == Items.end()) {
		cout << "아이템 긴칼이 없습니다." << endl;
	}
	
	map < const char*, Item, less<const char*>> Items2;
	map < const char*, Item, less<const char*>>::iterator iter2;

	Items2.insert(map<const char*, Item>::value_type(item2.name, item2));

	Items2[item3.name] = item3;

	for (iter2 = Items2.begin(); iter2 != Items2.end(); iter2++) {
		cout << "이름: " << iter2->first << "가격: " << iter2->second.BuyMoney << endl;
	}
	
	iter2 = Items2.find("해머");
	if (iter2 != Items2.end()) {
		Items2.erase(iter2);
	}

	return 0;
}