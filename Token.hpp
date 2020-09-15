//
// Created by Nicky Valdecanas on 2020-02-29.
//

#ifndef CS460_PROJECT3_TOKEN_HPP
#define CS460_PROJECT3_TOKEN_HPP


#include<string>

class Token {

public:
    Token();

    bool &eof()  { return _eof; }
    bool &eol()  { return _eol; }

    bool eof() const { return _eof; }
    bool eol() const  { return _eol; }
    bool isComma() const { return _symbol == ','; }
    bool isOpenParen() const  { return _symbol == '('; }
    bool isCloseParen() const { return _symbol == ')'; }

    bool isOpenBracket() const { return _symbol == '{'; }
    bool isCloseBracket() const { return _symbol == '}'; }

    bool isOpenBrace() const { return _symbol == '['; }
    bool isCloseBrace() const { return _symbol == ']'; }

    bool &isIndent()  { return _ind; }
    bool &isDedent()  { return _ded; }

    bool isIndent() const { return _ind; }
    bool isDedent() const { return _ded; }
    void setIndent(int n) { _wholeNumber = n; _ind = true;}
    void symbol(char c) { _symbol = c; }
    char symbol() { return _symbol; }
    bool isSemiColon() const { return _symbol == ';'; }
    bool isColon() const { return _symbol == ':'; }
    bool isAssignmentOperator() const              { return _symbol == '='; }
    bool isMultiplicationOperator() const { return _symbol == '*'; }
    bool isAdditionOperator() const       { return _symbol == '+'; }
    bool isSubtractionOperator() const    { return _symbol == '-'; }
    bool isModuloOperator() const         { return _symbol == '%'; }
    bool isDivisionOperator() const       { return _symbol == '/'; }
    bool isDot() const { return _symbol == '.'; }
    bool isIntegerDivisionOperator() const    { return _relOp == "//"; }
    bool isArithmeticOperator() const { return isAdditionOperator() || isSubtractionOperator(); }
    bool isTermOperator() const {
        return isMultiplicationOperator()
        || isDivisionOperator()
        || isModuloOperator()
        || isIntegerDivisionOperator();
    }

    bool isLessThan() const { return _relOp == "<"; }
    bool isGreaterThan() const { return _relOp == ">"; }
    bool isLessThanOrEqual() const { return  _relOp == "<="; }
    bool isGreaterThanOrEqual() const { return _relOp == ">="; }
    bool isDoubleEqual() const { return  _relOp == "=="; }
    bool isNotEqualTo() const { return _relOp == "!="; }
    bool isNotEqualTo2() const { return _relOp == "<>"; }
    bool isComparisonOperator() const{
        return isLessThan()
        || isLessThanOrEqual()
        || isGreaterThan()
        || isGreaterThanOrEqual()
        || isDoubleEqual()
        || isNotEqualTo()
        || isNotEqualTo2();
    }
    bool isSimple() const {
        return isPrint() || isName();
    }
    bool isCompound() const {
        return isFor() || isIf() || isDef();
    }
    bool isKeyword() const { return isFor() || isPrint(); } //_keyword.length() > 0; }
    std::string getKeyword() const { return _name; }
    void setKeyword(std::string keyword) {  _name = keyword; }

    bool isOr() const{ return _name == "or"; }
    bool isAnd() const { return _name == "and"; }
    bool isNot() const { return _name == "not"; }
    bool isFor() const { return _name == "for"; }
    bool isPrint() const { return _name == "print"; }
    bool isIn() const { return _name == "in"; }
    bool isIf() const{ return _name == "if"; }
    bool isElif() const { return _name == "elif"; }
    bool isElse() const { return _name == "else"; }
    bool isRange() const { return _name == "range"; }
    bool isReturn() const{ return _name == "return"; }
    bool isRelOp() const { return isComparisonOperator(); }
    bool isAppend() const { return _name == "append";};
    bool isPop() const { return _name == "pop";};
    bool isDef() const { return _name == "def"; }
    bool isArrayOp()  const { return isAppend() || isPop(); }

    std::string getOp() const { return _relOp; }
    void setOp(std::string op){
        _relOp = op;
        _name = _relOp;
        _isString = true;}

    bool isName() const                   { return _name.length() > 0; }
    std::string getName() const                  { return _name; }
    void setName(std::string n) { _name = n; }

    //Changed so it returns a double to accept floats
    bool &isWholeNumber() { return _isWholeNumber; }
    bool isWholeNumber() const { return _isWholeNumber; }
    double getWholeNumber() const { return _wholeNumber; }
    void setWholeNumber(double n) {
        _wholeNumber = n;
        isWholeNumber() = true;
    }
    bool isString() const {return _isString;}
    std::string getString() const { return _string;}
    void setString(std::string s) {
        _string = std::move(s);
        _isString = true;
    }
    //Make similar for string
    void print() const;

private:
    std::string _name;
    std::string _relOp;

    bool _eof, _eol, _ind, _ded;
    bool _isWholeNumber;
    bool _isString;

    char _symbol;
    double _wholeNumber;
    std::string _string;

};

#endif  //CS460_PROJECT3_TOKEN_HPP
