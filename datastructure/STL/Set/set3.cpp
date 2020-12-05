#include<set>
#include<iostream>
#include<functional>

using namespace std;

class Player {
public:
	Player() {}
	~Player() {}
	int m_Level;
};

template<typename T>
struct LEVEL_COMPARE : public binary_function<T, T, bool> {
	bool operator() (const T& player1, const T& player2) const
	{
		return player1->m_Level > player2->m_Level;
	}
};

int main()
{
	set<Player*, LEVEL_COMPARE<Player*>> PlayerList;

	Player* pPlayer1 = new Player;
	pPlayer1->m_Level = 10;
	Player* pPlayer2 = new Player;
	pPlayer1->m_Level = 20;
	Player* pPlayer3 = new Player;
	pPlayer1->m_Level = 30;

	PlayerList.insert(pPlayer1);
	PlayerList.insert(pPlayer2);
	PlayerList.insert(pPlayer3);

	for (set<Player*, LEVEL_COMPARE<Player*>>::iterator iter = PlayerList.begin(); iter != PlayerList.end() ; iter++) {
		cout << (*iter)->m_Level << endl;
	}

	set<Player*, LEVEL_COMPARE<Player*>>::iterator FindPlayer = PlayerList.find(pPlayer2);
	if (FindPlayer != PlayerList.end()){
		cout << "pPlayer4를 찾았습니다." << endl;
		cout << "pPlayer4를 삭제." << endl;
		PlayerList.erase(FindPlayer);
	}
	else {
		cout << "pPlayer4를 못 찾았습니다." << endl;
	}
	
	cout << "Total Player Count: " << PlayerList.size() << endl;

	PlayerList.clear();

	if(PlayerList.empty()){
		cout << "Player가 없습니다." << endl;
	}

	delete pPlayer1;
	delete pPlayer2;
	delete pPlayer3;

	return 0;
}