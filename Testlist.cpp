//
// Created by Nicky Valdecanas on 4/4/20.
//

#include "Testlist.hpp"

Testlist::Testlist(): _list{}{}

void Testlist::print() {
    std::vector<ExprNode*>list = getTestlist();
    for(int i = 0; i < numTests();i++){
        if(i != 0)
            std::cout << ", ";
        at(i)->print();
    }
//    for (auto e: _list) {
//        e->print();
//        std::cout << ", ";
//    }
}
