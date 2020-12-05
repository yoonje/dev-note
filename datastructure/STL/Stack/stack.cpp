#include <iostream>
#include <stack>
 
using namespace std;
 
int main(void) {
    stack<int> s; //스택 생성 
     
    cout<<s.empty()<<endl; //초기 스택은 비어있으므로 1 출력 
    s.push(4); //4 푸시 
    s.push(2); //2 푸시 
    s.push(3); //3 푸시 
    cout<<s.top()<<endl; //가장위에 있는 값을 반환 
    s.pop(); //가장 위에 있는 값을 삭제 
    cout<<s.top()<<endl; 
     
    cout<<s.empty()<<endl;
    cout<<s.size()<<endl; //스택의 사이즈 반환 
     
      
    return 0;
}
