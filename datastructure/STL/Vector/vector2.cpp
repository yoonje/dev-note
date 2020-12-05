#include<iostream>
#include<vector>

using namespace std;


int main()
{

    vector<int> vector1;

    vector1.push_back(20);
    vector1.push_back(30);

    cout << "»ðÀÔÅ×½ºÆ®1"<<endl;

    vector<int>::iterator iterBeg = vector1.begin();
    vector1.insert(iterBeg,100);

    vector<int>::iterator iterEnd = vector1.end();
    for(vector<int>::iterator iter = vector1.begin(); iter != iterEnd ;++iter){
        cout << "vector1 :" << *iter << endl;
    }

    cout << "»ðÀÔÅ×½ºÆ®2"<<endl;
    iterBeg = vector1.begin();
    vector1.insert(iterBeg,2,200);

    iterEnd = vector1.end();
    for(vector<int>::iterator iter = vector1.begin(); iter !=iterEnd; ++iter){
        cout << "vector1 :" << *iter << endl;
    }

     cout << "»ðÀÔÅ×½ºÆ®3"<<endl;

    vector<int> vector2;
    vector2.push_back(1000);
    vector2.push_back(2000);
    vector2.push_back(3000);

    vector<int>::iterator iter = vector1.begin();
    vector1.insert(iter,vector2.begin(),vector2.end());

    iterEnd = vector1.end();
    for(vector<int>::iterator iter = vector1.begin() ; iter != iterEnd ; ++iter){
        cout << "vector1 :" << *iter << endl;
    }

    return 0;
}