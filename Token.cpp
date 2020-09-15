//
// Created by Nicky Valdecanas on 2020-02-29.
//

#include <iostream>
#include "Token.hpp"

Token::Token(): _name{""}, _eof{false}, _eol{false}, _symbol{'\0'},
_isWholeNumber{false}, _ind{false},_ded{false}, _relOp{""}, _string{""},_isString{false}{}

void Token::print() const {
    if( eol() ) std::cout << "EOL\n" ;
    else if( eof() )                    std::cout << "EOF" ;
    else if( isOpenParen() )  std::cout << "(" ;
    else if( isCloseParen() )  std::cout << ")" ;
    else if( isAssignmentOperator() )  std::cout << " = " ;
    else if( isSemiColon() )  std::cout << ";" ;
    else if( isMultiplicationOperator() )  std::cout << " * " ;
    else if( isAdditionOperator() )  std::cout << " + " ;
    else if( isSubtractionOperator() )  std::cout << " - " ;
    else if( isModuloOperator() )  std::cout << " % " ;
    else if( isDivisionOperator() )  std::cout << " / " ;
    else if( isName() )  std::cout << getName();
    else if( isWholeNumber() ) std::cout << getWholeNumber();
    else if( isString() ) std::cout << getString();
    else if( isLessThan() ) std::cout << " < ";
    else if( isGreaterThan() ) std::cout << " > ";
    else if( isLessThanOrEqual() ) std::cout << " <= ";
    else if( isGreaterThanOrEqual() ) std::cout << " >= ";
    else if( isDoubleEqual() ) std::cout << " == ";
    else if( isNotEqualTo() ) std::cout << " !=";
    else if( isFor() ) std::cout << " for ";
    else if( isPrint() ) std::cout << " print ";
    else if( isOpenBracket() ) std::cout << " { ";
    else if( isCloseBracket() ) std::cout << " } ";
    else if( isOpenBrace() ) std::cout << " [ ";
    else if( isCloseBrace() ) std::cout << " ] ";

    else if( isComma() ) std::cout << " , ";
    else if( isNotEqualTo2() ) std::cout << " <> ";
    else if( isIntegerDivisionOperator() ) std::cout << " // ";
    else if( isDot() ) std::cout  << " . ";
    else if( isIn() ) std::cout << " in ";
    else if( isRange() ) std::cout << " range ";
    else if( isColon() ) std::cout << " : ";
    else if( isIndent() ) std::cout << " INDENT ";
    else if( isDedent() ) std::cout << " DEDENT ";
    else if( isOr() ) std::cout << " or ";
    else if( isAnd() ) std::cout << " and ";
    else if( isNot() ) std::cout << " not ";
    else if( isIf() ) std::cout << " if ";
    else if( isElif() ) std::cout << " elif ";
    else if( isElse() ) std::cout << " else ";
    else if( isReturn() ) std::cout << " return ";
    else if( isAppend() ) std::cout << " append ";
    else if( isPop() ) std::cout << " pop ";
    else if( isDef() ) std::cout << " def ";

    else std::cout << "Uninitialized token.\n";
}
