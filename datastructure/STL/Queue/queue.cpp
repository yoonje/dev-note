#include <iostream>
#include <queue>
 
using namespace std;
 
int main(void) {
    priority_queue<int> pq1; //max heap 생성 
     
    priority_queue<int, vector<int> , greater<int> > pq2; //min heap 생성 
     
    cout<<pq1.empty()<<endl; //우선순위 큐가 비어있는지 검사 
     
    pq1.push(20);
    pq1.push(30);
    pq1.push(40);
     
    cout<<pq1.top() <<endl; //top 값 반환 
     
    pq1.push(50); 
     
    cout<<pq1.top() <<endl;
     
    pq1.pop(); //top에 있는 값 삭제 
     
    cout<<pq1.top() <<endl;
    cout<<pq1.size()<<endl; //사이즈 반환 
     
    pq2.push(20); 
    pq2.push(30);
    pq2.push(40);
     
    cout<<pq2.top() <<endl; //가장 작은 값인 20 반환 (top)
     
    pq2.push(10);
     
    cout<<pq2.top() <<endl; //가장 작은 값인 10 반환 (top) 
     
    pq2.pop();
     
    cout<<pq2.top() <<endl; //가장 작은 값인 20 반환 (top)
    cout<<pq2.size()<<endl;
     
    return 0;
}