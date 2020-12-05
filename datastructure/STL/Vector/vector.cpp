#include<iostream>
#include<vector>

using namespace std;

class RoomUser{
public:
    int CharCd;
    int Level;
};


int main()
{
    RoomUser RoomUser1;
    RoomUser1.CharCd = 1;
    RoomUser1.Level = 10;

    RoomUser RoomUser2;
    RoomUser2.CharCd = 2;
    RoomUser2.Level = 20;

    vector<RoomUser> RoomUsers;

    RoomUsers.push_back(RoomUser1);
    RoomUsers.push_back(RoomUser2);

    int UserCount = RoomUsers.size();

    for (vector<RoomUser>::iterator iter = RoomUsers.begin(); iter != RoomUsers.end(); ++iter){
        cout << "유저코드 : " << iter->CharCd << endl;
        cout << "유저레벨 : " << iter->Level << endl;
    }
     cout<<endl;

    for(int i = 0 ; i<UserCount; i++){
        cout << "유저코드 : " << RoomUsers[i].CharCd << endl;
        cout << "유저레벨 : " << RoomUsers[i].Level << endl;
    }

    RoomUser& FirstRoomUser = RoomUsers.front();
    cout << "첫 번째 유저의 레벨" << FirstRoomUser.Level << endl;

    RoomUser& LastRoomUser = RoomUsers.back();
    cout<< "마지막 유저의 레벨" << LastRoomUser.Level << endl;

    RoomUser& RoomUserAt = RoomUsers.at(1);

    RoomUsers.pop_back();

    UserCount = RoomUsers.size();
    cout<< "현재 방에 있는 유저 수:" << UserCount << endl;
    return 0;
}