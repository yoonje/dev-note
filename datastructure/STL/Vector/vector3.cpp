#include<iostream>
#include<vector>

using namespace std;


int main()
{
    vector<int> vector1;

    vector1.push_back(10);
    vector1.push_back(20);
    vector1.push_back(30);
    vector1.push_back(40);
    vector1.push_back(50);
    
    int count = vector1.size();

    for(int i= 0 ; i< count ; i++){
        cout << "vector1: " << vector1[i] << endl;
    }
    cout << endl;

    cout << "erase 테스트 1" << endl;

    vector1.erase(vector1.begin());

    count = vector1.size();
    cout << count;
    for(int i=0 ; i<count ;++i){
         cout << "vector1: " << vector1[i] << endl;
    }
    cout << endl;

    cout << endl << "erase 테스트" << endl;

    vector<int>::iterator iter = vector1.begin();
    vector1.erase(iter, vector1.end());

    return 0;
}