#include <utility>

//
// Created by Nicky Valdecanas on 2020-02-29.
//

#ifndef CS460_PROJECT3_STATEMENTS_HPP
#define CS460_PROJECT3_STATEMENTS_HPP

#include <iostream>
#include <vector>

#include "ArithExpr.hpp"
#include "SymTab.hpp"
#include "Testlist.hpp"
#include "Range.hpp"

// The Statement (abstract) class serves as a super class for all statements that
// are defined in the language. Ultimately, statements have to be evaluated.
// Therefore, this class defines evaluate, a pure-virtual function to make
// sure that all subclasses of Statement provide an implementation for this
// function.

class Statement{
public:
    Statement();

    virtual void print() = 0;
    virtual void evaluate(SymTab &symTab) = 0;

     //    void passFunctions(Statement *statement){
//        _statements.push_back(statement);
//    }
    virtual void passStack(std::vector<Statement*>stack) {
        _statements = stack;
    }
    //virtual std::string id(){return _id; }
    //Statement *passBackFunction(){ return _function; }
    int indentState = 0;
    bool isFunction = false;

private:
    std::vector<Statement*>_statements;
    std::string _id;

};


// Statements is a collection of Statement. For example, all statements in a function
// can be represented by an instance of Statements.
class Statements {

public:
    Statements();
    Statements(int indentState);
    void addStatement(Statement *statement);
    void evaluate(SymTab &symTab);
    void print();


private:
    std::vector<Statement *> _statements;
    int _indState = 0;
    bool _isFunction = false;

};


class Function : public Statement{
public:
    Function();
    Function(std::string id, std::vector<std::string>_paramenters, Statements *stmts);
    std::vector<std::string>paramenters(){ return _paramenters; }
    Statements *statements() { return  _statements; }

    virtual std::string id() { return  _id; }
    virtual void evaluate(SymTab &symTab);
    virtual void print();
private:
    std::string _id;
    std::vector<std::string>_paramenters;
    Statements *_statements;

};
class Functions{
    public:
    Functions();
    std::vector<Function*> getFunctionStack(){ return _functionStack; }
    void addFunction(Function *function);
    bool findFunction(Function *function);
    Function *returnFunction(Function *function);
    void setStack(std::vector<Function*>stack){
        _functionStack = stack;
    }
    void passFunctionStack(Statement *statement);

private:
    std::vector<Function*>_functionStack;
};

class CallStatement : public Function, Functions{
public:
    CallStatement();
    CallStatement(std::string id, Testlist *testlist);
    Testlist *testList() { return _testlist; }
    std::string id(){ return  _id; }
    bool callFinder(const Token& id);
    void evaluate(SymTab &symTab);//,std::vector<Function*>stack);
    TypeDescriptor *evaluateCallExpr(SymTab &symTab,std::vector<Statement*>stack,std::string id);
    virtual void print();
    virtual void passStack(std::vector<Statement*>stack){
        _functionStack = std::move(stack);
    }
private:
    std::string _id;
    Testlist *_testlist;
    std::vector<Statement*>_functionStack;

};

class ReturnStatement : public Statement{
public:
    ReturnStatement();
    ReturnStatement(ExprNode *test);
    ExprNode *getTest(){ return _test; }
    virtual void evaluate(SymTab &symTab);
    virtual void print();

private:
    ExprNode *_test;
    std::vector<Function*>_functionStack;

};
// AssignmentStatement represents the notion of an lValue having been assigned an rValue.
// The rValue is an expression.

class AssignmentStatement : public Function,Functions{//public Statement {
public:
    AssignmentStatement();
    AssignmentStatement(std::string lhsVar, ExprNode *rhsExpr);
    AssignmentStatement(std::string lhsVar, Testlist *testlist);
    AssignmentStatement(std::string lhsVar, ExprNode *subscription, ExprNode *rhsExpr);
//    AssignmentStatement(std::string lhsVar, ExprNode *subscription, Testlist *testlist);
// No 2D array
    std::string &lhsVariable();
    ExprNode *&rhsExpression();
    ExprNode *&subscription();
    Testlist *&testlist();
    virtual void passStack(std::vector<Statement*>stack){
        _functionStack = stack;
    }
    virtual void evaluate(SymTab &symTab);
    virtual void print();

private:
    std::string _lhsVariable;
    ExprNode *_rhsExpression;
    Testlist *_testlist;
    ExprNode *_subscription;
    std::vector<Statement*>_functionStack;

};

class ForStatement : public Statement {
public:
    ForStatement();

    ForStatement(ExprNode *id, Testlist *testlist, Statements *stmts);
    ExprNode *&id();
    Testlist *&testlist();
    Statements *&statements();
    virtual void evaluate(SymTab &symTab);
    virtual void print();
    virtual void passStack(std::vector<Statement*>stack){
        _functionStack = stack;
    }

private:

    ExprNode * _id;
    Testlist * _testlist;
    Statements *_stmts;
    std::vector<Statement*>_functionStack;

};

class IfStatement : public Statement{
public:
    IfStatement();
    IfStatement(ExprNode* cond, Statements* statements);
    IfStatement(ExprNode* cond, Statements* statements, IfStatement* elif);
    void setElif(IfStatement* elif);
    //IfStatement(std::vector<std::pair<ExprNode*,Statements*>>testsAndSuites);
    //std::vector<std::pair<ExprNode*,Statements*>>&getTestsAndSuites();
    virtual void evaluate(SymTab &symTab);
    virtual void print();
    virtual void passStack(std::vector<Statement*>stack){
        _functionStack = stack;
    }

private:
    ExprNode* _cond;
    Statements* _stmts;
    IfStatement* _elif;
    std::vector<Statement*>_functionStack;

    //std::vector<std::pair<ExprNode*,Statements*>>_testsAndSuites;
};
class PrintStatement : public Statement {
public:
    PrintStatement();
    PrintStatement(Testlist *testlist); //std::string lhsVar, ExprNode *rhsExpr);
    Testlist *testList() { return _testlist; }
    virtual void evaluate(SymTab &symTab);
    virtual void print();
    virtual void passStack(std::vector<Statement*>stack){
        _functionStack = stack;
    }


private:
    Testlist *_testlist;
    std::vector<Statement*>_functionStack;

};

class ArrayOps : public Statement{
public:
    ArrayOps();
    ArrayOps(ExprNode *id,Token op, ExprNode *test);
    virtual void evaluate(SymTab &symTab);
    virtual void print();

private:
    ExprNode * _id;
    Token _op;
    ExprNode * _test;
};




#endif //CS460_PROJECT3_STATEMENTS_HPP
