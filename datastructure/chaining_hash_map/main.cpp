#include "HashChainMap.h"

int main() {
    HashChainMap hm;
    Node * a = new Node("do", "반복");
    Node * b = new Node("for", "반복");
    Node * c = new Node("if", "분기");
    Node * d = new Node("case", "분기");
    Node * e = new Node("else", "분기");
    Node * f = new Node("function", "함수");
    hm.addRecord(a);
    hm.addRecord(b);
    hm.addRecord(c);
    hm.addRecord(d);
    hm.addRecord(e);
    hm.addRecord(f);
    hm.display();
    hm.searchNode("case");
    hm.searchNode("else");
    hm.searchNode("class");
    return 0;
}