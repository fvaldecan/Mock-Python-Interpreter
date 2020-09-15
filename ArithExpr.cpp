//
// Created by Nicky Valdecanas on 2020-02-29.
//

#include<iostream>
#include "ArithExpr.hpp"
#include "Statements.hpp"

// ArithExprNode
ExprNode::ExprNode(Token token): _token{token}, _isCall{false} {}

Token ExprNode::token() { return _token; }

// InfixExprNode functions
InfixExprNode::InfixExprNode(Token tk) : ExprNode{tk}, _left(nullptr), _right(nullptr) {}

ExprNode *&InfixExprNode::left() { return _left; }

ExprNode *&InfixExprNode::right() { return _right; }

TypeDescriptor *InfixExprNode::evaluate(SymTab &symTab) {
    // Evaluates an infix expression using a post-order traversal of the expression tree.
    TypeDescriptor *lValue = left()->evaluate(symTab);
    TypeDescriptor *rValue = right()->evaluate(symTab);
    std::string op;
    if(token().symbol())
        op = token().symbol();
    else if(token().isRelOp())
        op = (token().getOp());
    if( token().isAdditionOperator() ) {
        TypeDescriptor *sum = addOperator(lValue,rValue);
        return sum;
    } else if(token().isSubtractionOperator()) {
        TypeDescriptor *difference = subOperator(lValue,rValue);
        return difference;
    }else if(token().isMultiplicationOperator()) {
        TypeDescriptor *product = multOperator(lValue, rValue);
        return product;
    }
    else if(token().isDivisionOperator()) {
        TypeDescriptor *quotient = divOperator(lValue, rValue);
        return quotient;
    }
    else if( token().isModuloOperator() ) {
        TypeDescriptor *product = modDivOperator(lValue, rValue);
        return product;
    }
    else if( token().isIntegerDivisionOperator() ) {
        TypeDescriptor *intQuotient = intDivOperator(lValue,rValue);
        return intQuotient;
    }
    else if( token().isLessThan()){
        TypeDescriptor *lessCheck = lessThanOperator(lValue, rValue);
        return lessCheck;
    }
    else if( token().isLessThanOrEqual()){
        TypeDescriptor *lessEqCheck = lessThanEqOperator(lValue, rValue);
        return lessEqCheck;
    }
    else if( token().isGreaterThan()){
        TypeDescriptor *greaterCheck = greatThanOperator(lValue, rValue);
        return greaterCheck;
    }
    else if( token().isGreaterThanOrEqual()){
        TypeDescriptor *greaterEqCheck = greatThanEqOperator(lValue, rValue);
        return greaterEqCheck;
    }
    else if( token().isDoubleEqual()) {
        TypeDescriptor *equalCheck = equalToOperator(lValue, rValue);
        return equalCheck;
    }
    else if( token().isNotEqualTo() || token().isNotEqualTo2() || token().isNot() ) {
        TypeDescriptor *notEqualCheck = notEqualToOperator(lValue, rValue);
        return notEqualCheck;
    }
    else if( token().isOr() ){
        TypeDescriptor *orCheck = orOperator(lValue, rValue);
        std::string boolLeft, boolRight;
        boolLeft = lValue->getNumber() ? "true" : "false";
        boolRight = rValue->getNumber() ? "true" : "false";
        std::cout << "TypeDescriptor *orOperator: " << boolLeft  << " or " << boolRight << std::endl;

        return orCheck;

    }
    else if( token().isAnd() ) {
        TypeDescriptor *andCheck = andOperator(lValue, rValue);
        std::string boolLeft, boolRight;
        boolLeft = lValue->getNumber() ? "true" : "false";
        boolRight = rValue->getNumber() ? "true" : "false";
        std::cout << "TypeDescriptor *andOperator: " << boolLeft  << " and " << boolRight << std::endl;
        return andCheck;
    }else {
        std::cout << "InfixExprNode::evaluate: don't know how to evaluate this operator\n";
        token().print();
        std::cout << std::endl;
        exit(2);
    }
}

void InfixExprNode::print() {
    _left->print();
    std::cout << " ";
    token().print();
    std::cout << " ";
    _right->print();
}

// WHoleNumber
WholeNumber::WholeNumber(Token token): ExprNode{std::move(token)} {}

void WholeNumber::print() {
    token().print();
}

TypeDescriptor *WholeNumber::evaluate(SymTab &symTab) {
    double value = token().getWholeNumber();
    auto *numValue = new NumberDescriptor(value);
    //std::cout << "WholeNumber::evaluate: returning " << value << std::endl;
    return numValue;
}

// Variable

Variable::Variable(Token token): ExprNode{std::move(token)} {}

void Variable::print() {
    token().print();
}

TypeDescriptor *Variable::evaluate(SymTab &symTab) {
    if( ! symTab.isDefined(token().getName())) {
        std::cout << "Use of undefined variable, " << token().getName() << std::endl;
        exit(1);
    }
    std::string valueName = token().getName();
    TypeDescriptor *value = symTab.getValueFor(valueName);
    if(value->type() == TypeDescriptor::NUMBER) {
        double numValue = value->getNumber();
        //std::cout << "Variable::evaluate: returning " << numValue << std::endl;
    }else {
        std::string stringValue = value->getString();
        //std::cout << "Variable::evaluate: returning " << stringValue << std::endl;

    }
    return value;
}
String::String(Token token): ExprNode{std::move(token)} {}

void String::print() {
    std::cout << '"';
    token().print();
    std::cout << '"';
}


TypeDescriptor* String::evaluate(SymTab &symTab) {
    std::string value = token().getString();
    auto *stringValue = new StringDescriptor(value);
    //std::cout << "String::evaluate: returning " << value << std::endl;
    return stringValue;
}

SubExpr::SubExpr(Token id,ExprNode *test): ExprNode{std::move(id)},_test{test} {}
void SubExpr::print() {
    token().print();
    std::cout << '[';
    _test->print();//index
    std::cout << ']';
}


TypeDescriptor* SubExpr::evaluate(SymTab &symTab) {
//    TypeDescriptor *array = symTab.getValueFor(token().getName());
    std::vector<TypeDescriptor *> array = symTab.getValueFor(token().getName())->getArray();
    double index = _test->evaluate(symTab)->getNumber();
    for (int i = 0; i < array.size(); i++) {
        if (i == index)
            return new NumberDescriptor(array[i]->getNumber());
    }
    //If reaches this point then index out of bounds
    std::cout << "Out of bounds index error! Can't index at " << index << std::endl;
    exit(2);
}
LengthExpr::LengthExpr(Token id): ExprNode{std::move(id)}{}
void LengthExpr::print() {
    std::cout << "len(";
    token().print();
    std::cout << ")";
}


TypeDescriptor* LengthExpr::evaluate(SymTab &symTab) {
//    TypeDescriptor *array = symTab.getValueFor(token().getName());
    double size = symTab.getValueFor(token().getName())->getArray().size();
    return new NumberDescriptor(size);
}
//    std::string value = token().getString();
//    auto *stringValue = new StringDescriptor(value);
//    //std::cout << "String::evaluate: returning " << value << std::endl;
//    return stringValue;

//

CallExpr::CallExpr(Token id,std::vector<ExprNode*>testList): ExprNode{std::move(id)},_list{std::move(testList)}, _isCall{true}{}

void CallExpr::print() {
    token().print();
    std::cout << "(";
    for(int i = 0; i < list().size();i++) {
        if(i != 0) std::cout << ",";
        std::cout << list()[i]->token().getName();
    }
    std::cout << ")";

}

TypeDescriptor *CallExpr::evaluate(SymTab &symTab) {
    auto *funcFinder = new CallStatement;
    if(funcFinder->callFinder(token()))
        funcFinder->evaluate(symTab);
    return nullptr;
}
//ArrayExpr::ArrayExpr(Testlist *arrayList): ExprNode{}{}
//
//void ArrayExpr::print() {
//
//}
//
//TypeDescriptor *ArrayExpr::evaluate(SymTab &symTab) {
//    return nullptr;

