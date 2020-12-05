#include<iostream>
#include<vector>

using namespace std;


int main()
{
    vector<int> vector1;

    vector1.assign(7,4);

    int count = vector1.size();
    for(int i = 0 ; i < count; ++i){
        cout << "vector1: "<<vector1[i]<<endl;
    }
    cout << endl;

    vector<int> vector2;
    vector2.push_back(10);
    vector2.push_back(20);
    vector2.push_back(30);
    vector2.push_back(40);

    vector1.assign(vector2.begin(),vector2.end());
    count = vector1.size();
    for(int i = 0 ; i < count; ++i){
        cout << "vector1: "<<vector1[i]<<endl;
    }
    return 0;
}