//
// Created by Nicky Valdecanas on 4/4/20.
//

#ifndef CS460_PROJECT3_TESTLIST_HPP
#define CS460_PROJECT3_TESTLIST_HPP

#include "ArithExpr.hpp"

#include <vector>
class Testlist {
public:
    Testlist();
    std::vector<ExprNode*>getTestlist(){ return _list; }
    int numTests(){ return _list.size(); }
    void addTest(ExprNode* test){ _list.push_back(test); }
    ExprNode *at(int i){ return _list[i]; }
    void print();
private:
    std::vector<ExprNode*>_list;
};


#endif //CS460_PROJECT3_TESTLIST_HPP
