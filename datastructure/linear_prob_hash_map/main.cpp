#include "HashMap.h"

int main() {
    HashMap hm;
    hm.addLinearProb("do", "반복");
    hm.addLinearProb("for", "반복");
    hm.addLinearProb("if", "분기");
    hm.addLinearProb("case", "분기");
    hm.addLinearProb("else", "분기");
    hm.addLinearProb("function", "함수");
    hm.display();
    hm.searchLinearProb("class");
    hm.searchLinearProb("case");
    hm.searchLinearProb("else");
    return 0;
}