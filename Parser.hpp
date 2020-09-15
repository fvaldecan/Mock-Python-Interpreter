//
// Created by Nicky Valdecanas on 2020-02-29.
//

#ifndef CS460_PROJECT3_PARSER_HPP
#define CS460_PROJECT3_PARSER_HPP


#include "Token.hpp"
#include "Tokenizer.hpp"
#include "SymTab.hpp"
#include "ArithExpr.hpp"
#include "Statements.hpp"
#include "Testlist.hpp"
#include<vector>
#include<iostream>
#include<map>
class Parser {
public:
    Parser(Tokenizer &tokenizer) : tokenizer{tokenizer} {}

    //Functions *returnFunctionStack();
    Statements *fileInput();
    Statement *stmt();

    Statement *compStmt();
    Statement *simpStmt();

    ArrayOps *arrayOps(ExprNode *id);
    CallStatement *callStmt(ExprNode *id);
    ExprNode *call(Token id);

    ReturnStatement *returnStmt();

    //SubscriptionStatement *subStmt(ExprNode *id);
    Testlist *arrayInit();
    PrintStatement *printStmt();
    Testlist *testList();
    ExprNode *test();
    ExprNode *compareExpr();
    Token compareOp();
    ExprNode *sub();
    ExprNode *len();
    ExprNode *exprOrTest();
    ExprNode *exprAndTest();
    ExprNode *exprNotTest();
    ExprNode *arithExpr();
    ExprNode *term();
    ExprNode *factor();
    ExprNode *atom(Token tok);
    ExprNode *variableID();
    AssignmentStatement *assignStmt(ExprNode *id);
    ForStatement *forStmt();
    Statements *suite();
    IfStatement *ifStmt();
    std::vector<std::string>parameterList();
    Function *function();
private:
    Tokenizer &tokenizer;
    //Functions *_functions = new Functions();
    void die(std::string where, std::string message, Token &token);


};


#endif //CS460_PROJECT3_PARSER_HPP
