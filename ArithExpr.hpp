//
// Created by Nicky Valdecanas on 2020-02-29.
//

#ifndef CS460_PROJECT3_ARITHEXPR_HPP
#define CS460_PROJECT3_ARITHEXPR_HPP


#include "Token.hpp"
#include "SymTab.hpp"
//#include "Statements.hpp"

//#include "Testlist.hpp"
// Classes in this file define the internal representation of arithmetic expressions.


// An ArithExprNode serves as the base class (super class) for arithmetic expression.
// It forces the derived classes (subclasses) to implement two functions, print and
// evaluate.
class ExprNode {
public:
    ExprNode(Token token);
    Token token();
    virtual void print() = 0;
    virtual TypeDescriptor *evaluate(SymTab &symTab) = 0;
//    virtual void passStack() {
//    }
    virtual bool isCallback(){ return _isCall;}
private:
    Token _token;
    bool _isCall;
};


// An InfixExprNode is useful to represent binary arithmetic operators.
class InfixExprNode: public ExprNode {  // An expression tree node.

public:
    InfixExprNode(Token tk);

    ExprNode *&left();
    ExprNode *&right();
    virtual void print();
    virtual TypeDescriptor *evaluate(SymTab &symTab);

private:
    ExprNode *_left, *_right;
};

// WholeNumber is a leaf-node in an expression tree. It corresponds to
// a terminal in the production rules of the grammar that describes the
// syntax of arithmetic expressions.

class WholeNumber: public ExprNode {
public:
    WholeNumber(Token token);
    virtual void print();
    virtual TypeDescriptor *evaluate(SymTab &symTab);
};

// Varialbe is a leaf-node in an expression tree. It corresponds to
// a terminal in the production rules of the grammar that describes the
// syntax of arithmetic expressions.

class Variable: public ExprNode {
public:
    Variable(Token token);
    virtual void print();
    virtual TypeDescriptor *evaluate(SymTab &symTab);
};

class String: public ExprNode {
public:
    String(Token token);
    virtual void print();
    virtual TypeDescriptor *evaluate(SymTab &symTab);
};

class SubExpr: public ExprNode{
public:
    SubExpr(Token id,ExprNode *test);
    virtual void print();
    virtual TypeDescriptor *evaluate(SymTab &symTab);
private:
    ExprNode *_test;
};
class LengthExpr: public ExprNode{
public:
    LengthExpr(Token id);
    virtual void print();
    virtual TypeDescriptor *evaluate(SymTab &symTab);
};
class CallExpr: public ExprNode{
public:

    CallExpr(Token id, std::vector<ExprNode*>testList);
    std::vector<ExprNode*>list(){ return _list; }
    //std::vector<Function*>stack(){ return _stack; }
    virtual void print();
    virtual TypeDescriptor *evaluate(SymTab &symTab);
    virtual bool isCallback(){ return _isCall; }
private:
    std::vector<ExprNode*>_list;
    //std::vector<Function*>_stack;
    bool _isCall;
};
//class ArrayExpr: public ExprNode {
//public:
//    ArrayExpr(Testlist *arrayList);
//    virtual void print();
//    virtual TypeDescriptor *evaluate(SymTab &symTab);
//};
#endif //CS460_PROJECT3_ARITHEXPR_HPP
