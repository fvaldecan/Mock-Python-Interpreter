#include <utility>

//
// Created by Nicky Valdecanas on 2020-02-29.
//

#include <vector>
#include <iostream>

#include "Token.hpp"
#include "Parser.hpp"
#include "Statements.hpp"

// Parser functions

void Parser::die(std::string where, std::string message, Token &token) {
    std::cout << where << " " << message << std::endl;
    token.print();
    std::cout << std::endl;
    std::cout << "\nThe following is a list of tokens that have been identified up to this point.\n";
    tokenizer.printProcessedTokens();
    exit(1);
}

//Functions *Parser::returnFunctionStack(){
//    return _functions;
//}
Statements *Parser::fileInput() {
    // file_input: {NEWLINE | stmt}* ENDMARKER
    auto *stmts = new Statements();
//    auto *funcs = new Functions();
    Token tok = tokenizer.getToken();
    while(!tok.eof()) {
        while(tok.eol())
            tok = tokenizer.getToken();
        tokenizer.ungetToken();
        Statement *statement = stmt();
        if(tok.isDef()) {
            statement->isFunction = true;
            //_functions->addFunction(dynamic_cast<Function *>(statement));
        }
        stmts->addStatement(statement);

        tok = tokenizer.getToken();
        while (tok.eol())
            tok = tokenizer.getToken();
//        if(tok.isDedent()){
//            tokenizer.ungetToken();
//            return stmts;
//        }
//
//        if(tok.eol()){
//        //    return stmts;
//        }
        //tok = tokenizer.getToken();
        //if(tok.isDedent()) break;


    }
    tokenizer.ungetToken();
    return stmts;
}
Statement *Parser::stmt() {
    //stmt: simple_stmt | compound_stmt

    Token tok = tokenizer.getToken();
    if (tok.isCompound()){
        tokenizer.ungetToken();
        Statement *compoundStatement = compStmt();
        return compoundStatement;

    } else if(tok.isSimple()) {
        tokenizer.ungetToken();
        Statement *simpleStatment = simpStmt();
        Token eol = tokenizer.getToken();
        if(!eol.eol() && !eol.eof())
            if(eol.isDedent())
                tokenizer.ungetToken();
            else die("Parser::stnt", "Expected a EOL token, instead got", eol);
        return simpleStatment;

    } else return nullptr;
}
Statement *Parser::simpStmt() {
    // stimple_stmt: (print_stmt | assign_stmt | array_ops | call_stmt | return_stmt) NEWLINE

    Token tok = tokenizer.getToken();
    tokenizer.ungetToken();
    if (tok.isPrint()){
        tokenizer.ungetToken();
        PrintStatement *printStatement = printStmt();
        return printStatement;
    } else if (tok.isReturn()){
        ReturnStatement *returnStatement = returnStmt();
        return returnStatement;
    }else if(tok.isName()) {
        ExprNode *id = variableID();
        Token op = tokenizer.getToken();
        tokenizer.ungetToken();
        if(op.isAssignmentOperator() || op.isOpenBrace()) {
            AssignmentStatement *assignmentStatement = assignStmt(id);
            return assignmentStatement;
        } else if(op.isDot()){
            ArrayOps *arrayOperator = arrayOps(id);
            return arrayOperator;
        } else if(op.isOpenParen()){
            CallStatement *callStatement = callStmt(id);
            return callStatement;
        }

    } else return nullptr;


}
Statement *Parser::compStmt() {
    //compound_stmt: for_stmt

    Token tok = tokenizer.getToken();
    if (tok.isFor()){
        tokenizer.ungetToken();
        ForStatement *forStatement = forStmt();
        return forStatement;
    } else if (tok.isIf()){
        tokenizer.ungetToken();
        IfStatement *ifStatement = ifStmt();
        return ifStatement;
    } else if(tok.isDef()){
        tokenizer.ungetToken();
        Function *func = function();
        return func;
    } else return nullptr;
}
IfStatement *Parser::ifStmt() {
    std::vector<std::pair<ExprNode*, Statements*>>totalTestSuites;
    Token boolKeyword = tokenizer.getToken();
    if (!boolKeyword.isIf())
        die("Parser::ifStmt", "Expected an 'if' token, instead got", boolKeyword);
    ExprNode *ifConditionTest = test();

    Token colon = tokenizer.getToken();
    if(!colon.isColon())
        die("Parser::ifStmt", "Expected a colon, instead got", colon);
    Statements* stmts = suite();

    auto *ifStmt = new IfStatement(ifConditionTest, stmts);
    boolKeyword = tokenizer.getToken();
    IfStatement* prevIf = ifStmt;
    while (boolKeyword.isElif()) {
        ifConditionTest = test();
        boolKeyword = tokenizer.getToken();
        if (!boolKeyword.isColon())
            die("Parser::ifStmt", "Expected a colon, instead got", boolKeyword);
        stmts = suite();
        auto *elif = new IfStatement(ifConditionTest, stmts);
        prevIf->setElif(elif);
        prevIf = elif;
        boolKeyword = tokenizer.getToken();
    }
    if(boolKeyword.isElse()){
        boolKeyword = tokenizer.getToken();
        if (!boolKeyword.isColon())
            die("Parser::ifStmt", "Expected a colon, instead got", boolKeyword);
        stmts = suite();
        auto *elseStmt = new IfStatement(nullptr, stmts);
        prevIf->setElif(elseStmt);
    } else
        tokenizer.ungetToken();
    return ifStmt;

}
ForStatement *Parser::forStmt() {
    //for_stmt: 'for' '(' assign_stmt ';' test ';' assign_stmt ')' '{'NEWLINE
    //                  stmt '}' NEWLINE

    Token forKeyword = tokenizer.getToken();
    if(!forKeyword.isFor())
        die("Parser::forStmt", "Expected a 'for' token, instead got", forKeyword);

    ExprNode * id = variableID();
    Token varID = id->token();
    if(!varID.isName()) {
        die("Parser::forStmt", "Expected an ID token",varID);
    }
    Token inKeyword = tokenizer.getToken();
    if(!inKeyword.isIn()){
        die("Parser::forStmt", "Expected an 'in' token, instead got", inKeyword);
    }
    Token rangeKeyword = tokenizer.getToken();
    if(!rangeKeyword.isRange())
        die("Parser::forStmt", "Expected a 'range' token, instead got", rangeKeyword);
    Token openParen = tokenizer.getToken();
    if(!openParen.isOpenParen())
        die("Parser::forStmt", "Expected a '(' token, instead got", openParen);

    Testlist *list = testList();
    if(list->numTests() < 1 || list->numTests() > 3){
        std::cout << "Parser::forStmt, Expected 1-3 arguments, instead got, " <<  list->numTests() << std::endl;
        exit(2);
    }

    Token closeParen = tokenizer.getToken();
    if(!closeParen.isCloseParen())
        die("Parser::forStmt", "Expected a ')' token, instead got", closeParen);
    Token colon = tokenizer.getToken();
    if(!colon.isColon())
        die("Parser::forStmt", "Expected a 'L' token, instead got", colon);
    Statements *stmts =  suite();

    return new ForStatement(id, list, stmts);



}




PrintStatement *Parser::printStmt() {
    //'print' [ testlist ]


    Token printKeyword = tokenizer.getToken();
    if (!printKeyword.isPrint())
        die("Parser::printStmt", "Expected a name token, instead got", printKeyword);
    Testlist *list = nullptr;
    Token tok = tokenizer.getToken();

    if (!tok.eol()) {
        tokenizer.ungetToken();
        list = testList();
    } else{
        tokenizer.ungetToken();
        return nullptr;
    }
    auto *printStatement = new PrintStatement(list);
    return printStatement;
}
Testlist *Parser::testList() {
    // testlist: test { ',' test }*

    auto *list = new Testlist();
    Token closeParen = tokenizer.getToken();
    tokenizer.ungetToken(); //empty parameters
    if(closeParen.isCloseParen()) return nullptr;
    ExprNode *var = test();
    list->addTest(var);
    Token tok = tokenizer.getToken();
    while (tok.isComma()){
        list->addTest(test());
        tok = tokenizer.getToken();
    }
    tokenizer.ungetToken();
    return list;
}
ExprNode *Parser::test() {
    // test: or_test
    ExprNode * comparison = exprOrTest();
    return comparison;
}
ExprNode *Parser::exprOrTest(){
    ExprNode *andTest = exprAndTest();
    Token orOp = tokenizer.getToken();
    while (orOp.isOr()){
        auto *p = new InfixExprNode(orOp);
        p->left() = andTest;
        p->right() = exprAndTest();
        andTest = p;
        orOp = tokenizer.getToken();
    }
    tokenizer.ungetToken();
    return andTest;
}
ExprNode *Parser::exprAndTest(){
    ExprNode *notTest = exprNotTest();
    Token andOp = tokenizer.getToken();
    while (andOp.isAnd()){
        auto *p = new InfixExprNode(andOp);
        p->left() = notTest;
        p->right() = exprNotTest();
        notTest = p;
        andOp = tokenizer.getToken();
    }
    tokenizer.ungetToken();
    return notTest;

}
ExprNode *Parser::exprNotTest(){
    Token notOp = tokenizer.getToken();
    tokenizer.ungetToken();
    if(notOp.isNot()){
        ExprNode *notTest = exprNotTest();
        return notTest;
    }else {
        ExprNode *comparison = compareExpr();
        return comparison;
    }
}
ExprNode *Parser::compareExpr() {

    // comparison: arith_expr {comp_op arith_expr}*

    ExprNode *left = arithExpr();
    Token tok = tokenizer.getToken();
    while (tok.isComparisonOperator()) {
        tokenizer.ungetToken();
        Token op = compareOp();
        auto *p = new InfixExprNode(op);
        p->left() = left;
        p->right() = arithExpr();
        left = p;
        tok = tokenizer.getToken();
    }
    tokenizer.ungetToken();
    return left;
}
Token Parser::compareOp() {
    // comp_op:  < > == >= <= <> !=

    Token compOp = tokenizer.getToken();
    if(!compOp.isComparisonOperator())
        die("Parser::compareOp", "Expected comparison operator, instead got", compOp);
    return compOp;
}
ExprNode *Parser::arithExpr() {
    // arith_expr: term { ( + | - ) term}*

    ExprNode *left = term();
    Token op = tokenizer.getToken();
    while (op.isArithmeticOperator()) {
        auto *p = new InfixExprNode(op);
        p->left() = left;
        p->right() = term();
        left = p;
        op = tokenizer.getToken();
    }
    tokenizer.ungetToken();
    return left;
}
ExprNode *Parser::term() {
    // term: factor { * | / | % | // ) factor}*

    ExprNode *left = factor();
    Token op = tokenizer.getToken();

    while ( op.isTermOperator() ) {
        auto *p = new InfixExprNode(op);
        p->left() = left;
        p->right() = factor();
        left = p;
        op = tokenizer.getToken();
    }
    tokenizer.ungetToken();
    return left;
}
ExprNode *Parser::factor() {
    // factor: { - } factor | atom

    Token op = tokenizer.getToken();
    if(op.isSubtractionOperator()){
        auto* negativeNumber = new InfixExprNode(op);
        Token t;
        t.setWholeNumber(0);
        negativeNumber->left() = new WholeNumber(t);
        ExprNode* f = factor();
        negativeNumber->right() = f;
        return negativeNumber;
    } else{ //if(op.isName()) {
        //tokenizer.ungetToken();
        Token check = tokenizer.getToken();
        tokenizer.ungetToken();
        if(check.isOpenBrace()) {//subscription
            return new SubExpr(op,sub()); //ID[test]
        }else if(op.getName() == "len"
        && check.isOpenParen()){
            return len();
        }else if(check.isOpenParen() && op.isName()){// cal
            return call(op);
        }else {
            ExprNode *a = atom(op);
            return a;
        }

    }
}
ExprNode *Parser::atom(Token tok) {
    // atom: ID | NUMBER | STRING+ | ( test )
    // This function parses the grammar rules:

    // <primary> -> [0-9]+
    // <primary> -> [_a-zA-Z][_a-zA-Z0-9]*
    // <primary> -> (<expr>)

    //Token tok = tokenizer.getToken();
    if (tok.isWholeNumber() )
        return new WholeNumber(tok);
    else if( tok.isName() ) {
        tokenizer.ungetToken();
        //ExprNode * id = variableID();
        return new Variable(tok);;
    }
    else if (tok.isOpenParen()) {
        ExprNode *p = test();
        Token closeParen = tokenizer.getToken();
        if (!closeParen.isCloseParen())
            die("Parser::primary", "Expected close-parenthesis, instead got", closeParen);
        return p;
    } else if(tok.isString())
        return new String(tok);

    die("Parser::primary", "Unexpected token", tok);
    return nullptr;  // Will not reach this statement!
}
ExprNode *Parser::variableID() {
    Token tok = tokenizer.getToken();
    return new Variable(tok);
}

Statements *Parser::suite() {

    Token endOfLine = tokenizer.getToken();
    if(!endOfLine.eol())
        die("Parser::suite", "Expected eol(), instead got", endOfLine);
    while(endOfLine.eol())
         endOfLine = tokenizer.getToken();
    //tokenizer.ungetToken();
    //Token indent = tokenizer.getToken();
    if (!endOfLine.isIndent())
        die("Parser::suite", "Expected INDENT, instead got", endOfLine);
    //stmts = fileInput();
    auto *stmts = new Statements(tokenizer.getIndent());
    stmts->addStatement(stmt());
    Token newStmt = tokenizer.getToken();
    while(newStmt.isName()){
        tokenizer.ungetToken();
        stmts->addStatement(stmt());
        newStmt = tokenizer.getToken();
    }
    while(newStmt.eol())
        newStmt = tokenizer.getToken();

    if(!newStmt.isDedent())
        die("Parser::suite", "Expected dedent, instead got", newStmt);

    return stmts;


}
AssignmentStatement *Parser::assignStmt(ExprNode *id) {

    //assign_stmt: ID '=' test

//    Token varName = tokenizer.getToken();
//    if (!varName.isName())
//        die("Parser::assignStmt", "Expected a name token, instead got", varName);
    Token openBrace = tokenizer.getToken();
    if (!openBrace.isOpenBrace()) { // ID =
        if (!openBrace.isAssignmentOperator())
            die("Parser::assignStmt", "Expected an equal sign, instead got", openBrace);
        openBrace = tokenizer.getToken();
        if (!openBrace.isOpenBrace()) {
            tokenizer.ungetToken();
            ExprNode *rightHandSideExpr = test();
            return new AssignmentStatement(id->token().getName(), rightHandSideExpr);
        } else{
            Testlist *arrayTestlist = arrayInit();
//            Token closeBrace = tokenizer.getToken();
//            if (!closeBrace.isCloseBrace())
//                die("Parser::assignStmt", "Expected an ] sign, instead got", closeBrace);
            return new AssignmentStatement(id->token().getName(), arrayTestlist);
        }
    }else{ //  ID[...] =
        tokenizer.ungetToken();
        ExprNode *subscription = sub();
        openBrace = tokenizer.getToken();
        if (!openBrace.isAssignmentOperator())
            die("Parser::assignStmt", "Expected an equal sign, instead got", openBrace);
        openBrace = tokenizer.getToken();
        if (!openBrace.isOpenBrace()) { // test
            tokenizer.ungetToken();
            ExprNode *rightHandSideExpr = test();
            return new AssignmentStatement(id->token().getName(), subscription, rightHandSideExpr);
        }
//        } else{ // [...]
//            Testlist *arrayTestlist = arrayInit();
////            Token closeBrace = tokenizer.getToken();
////            if (!closeBrace.isCloseBrace())
////                die("Parser::assignStmt", "Expected an ] sign, instead got", closeBrace);
//            return new AssignmentStatement(id->token().getName(),subscription, arrayTestlist);
//        }
    }





}
ArrayOps *Parser::arrayOps(ExprNode *id) {
    Token dot = tokenizer.getToken();
    if (!dot.isDot())
        die("Parser::arrayOps", "Expected an . sign, instead got", dot);
    Token arrayOp = tokenizer.getToken();
    if (!arrayOp.isArrayOp())
        die("Parser::arrayOps", "Expected an 'append' or 'pop' sign, instead got", arrayOp);
    Token openParen = tokenizer.getToken();
    if (!openParen.isOpenParen())
        die("Parser::arrayOps", "Expected an ( sign, instead got", openParen);
    Token closeParen = tokenizer.getToken();
    if(closeParen.isCloseParen())
        return new ArrayOps(id,arrayOp, nullptr);
    else {
        tokenizer.ungetToken();
        ExprNode *arrayTest = test();
        closeParen = tokenizer.getToken();
        if (!closeParen.isCloseParen())
            die("Parser::arrayOps", "Expected an ) sign, instead got", closeParen);
        return new ArrayOps(id, arrayOp, arrayTest);
    }
}
CallStatement *Parser::callStmt(ExprNode *id) {
    Token openParen = tokenizer.getToken();
    if (!openParen.isOpenParen())
        die("Parser::callStmt", "Expected an ( sign, instead got", openParen);
    Testlist *callTestlist = testList();
    Token closeParen = tokenizer.getToken();
    if (!closeParen.isCloseParen())
        die("Parser::callStmt", "Expected an ) sign, instead got", closeParen);
    return new CallStatement(id->token().getName(), callTestlist);
    //return call(id);
}
ExprNode *Parser::call(Token id) {
    Token openParen = tokenizer.getToken();
    if (!openParen.isOpenParen())
        die("Parser::callStmt", "Expected an ( sign, instead got", openParen);
    Testlist *callTestlist = testList();
    std::vector<ExprNode*>newArray;
    for(int i = 0; i < callTestlist->numTests();i++){
        newArray.push_back(callTestlist->at(i));
    }
    Token closeParen = tokenizer.getToken();
    if (!closeParen.isCloseParen())
        die("Parser::callStmt", "Expected an ) sign, instead got", closeParen);
//    CallStatement *callStatement = new CallStatement(id.getName(), callTestlist);
    auto *callExpr = new CallExpr(id, newArray);

    return callExpr;
    //CallExpr *callExpr = new CallExpr()
    //callToken.setWholeNumber(callStatement->evaluate());
    //return new WholeNumber(callToken);

}

ReturnStatement *Parser::returnStmt() {
    Token returnKeyword = tokenizer.getToken();
    if(!returnKeyword.isReturn())
        die("Parser::returnStmt", "Expected an return sign, instead got", returnKeyword);
    ExprNode *returnTest = test();
    return new ReturnStatement(returnTest);
}

Testlist *Parser::arrayInit() {
//    Token openBrace = tokenizer.getToken();
//    if (!openBrace.isOpenBrace())
//        die("Parser::arrayInit", "Expected an [ sign, instead got", openBrace);
    Testlist * arrayTestlist = testList();
    Token closeBrace = tokenizer.getToken();
    if (!closeBrace.isCloseBrace())
        die("Parser::arrayInit", "Expected an ] sign, instead got", closeBrace);
    return arrayTestlist;
}

ExprNode *Parser::sub() {
    Token openBrace = tokenizer.getToken();
    if (!openBrace.isOpenBrace())
        die("Parser::sub", "Expected an [ sign, instead got", openBrace);
    ExprNode *subTest = test();
    Token closeBrace = tokenizer.getToken();
    if (!closeBrace.isCloseBrace())
        die("Parser::sub", "Expected an ] sign, instead got", closeBrace);
    return subTest;

}

ExprNode *Parser::len() {
    Token openParen = tokenizer.getToken();
    if (!openParen.isOpenParen())
        die("Parser::sub", "Expected an ( sign, instead got", openParen);
    ExprNode *id = variableID();
    Token closeParen = tokenizer.getToken();
    if (!closeParen.isCloseParen())
        die("Parser::sub", "Expected an ) sign, instead got", closeParen);
    return new LengthExpr(id->token());
}
Function *Parser::function(){
    Token def = tokenizer.getToken();
    ExprNode *id = variableID();
    Token openParen = tokenizer.getToken();
    if (!openParen.isOpenParen())
        die("Parser::functionDef", "Expected an ( sign, instead got", openParen);
    //Parameter List
    std::vector<std::string>params = parameterList();
    Token closeParen = tokenizer.getToken();
    if (!closeParen.isCloseParen())
        die("Parser::functionDef", "Expected an ) sign, instead got", closeParen);
    Token colon = tokenizer.getToken();
    if (!closeParen.isCloseParen())
        die("Parser::functionDef", "Expected an : sign, instead got", colon);
    Statements *statements = suite();
    return new Function(id->token().getName(),params,statements);

}


std::vector<std::string>Parser::parameterList(){
    std::vector<std::string>params;
    Token param = tokenizer.getToken();
    while(!param.isCloseParen()){
        params.push_back(param.getName());
        Token comma = tokenizer.getToken();
        if(comma.isCloseParen()) break;
        if(!comma.isComma())
            die("Parser::parameterList", "Expected an , sign, instead got", comma);
        param = tokenizer.getToken();
    }
    tokenizer.ungetToken();
    return params;
}

//SubscriptionStatement *Parser::subStmt(ExprNode *id) {
//    Token openBrace = tokenizer.getToken();
//    if (!openBrace.isOpenBrace())
//        die("Parser::sub", "Expected an [ sign, instead got", openBrace);
//    ExprNode *subTest = test();
//    Token closeBrace = tokenizer.getToken();
//    if (!closeBrace.isCloseBrace())
//        die("Parser::sub", "Expected an ] sign, instead got", closeBrace);
//    return new SubscriptionStatement(id,subTest);
//}
