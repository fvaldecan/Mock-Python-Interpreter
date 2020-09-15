//
// Created by Nicky Valdecanas on 2020-02-29.
//


#include <iostream>
#include <string>
#include "Tokenizer.hpp"
std::string Tokenizer::readName() {
    // This function is called when it is known that
    // the first character in input is an alphabetic character.
    // The function reads and returns all characters of the name.

    std::string name;
    char c;
    while( inStream.get(c) && isalnum(c) ) {
        name += c;
    }
    if(inStream.good())  // In the loop, we have read one char too many.
        inStream.putback(c);
    return name;
}
std::string Tokenizer::readRelOp(){
    std::string op;
    char c;
    while(inStream.get(c) && c != ' '){
        op += c;
    }
    if(op.length() > 2) {
        std::cout << "Invalid Operator.\n";
        exit(1);
    }
    if(inStream.good())  // In the loop, we have read one char too many.
        inStream.putback(c);
    return op;
}
double Tokenizer::readInteger() {
    // This function is called when it is known that
    // the first character in input is a digit.
    // The function reads and returns all remaining digits.

    double doubleStr = 0;
    std::string str;
    char c;
    bool decimal = false;
    while( ((inStream.peek() == '.') && !decimal) || isdigit(inStream.peek())) {
        inStream.get(c);
        if(c == '.')
            decimal = true;
        str += c;
    }
    doubleStr = std::stod(str);
    return doubleStr;
}
Tokenizer::Tokenizer(std::ifstream &stream): ungottenToken{false}, inStream{stream}, lastToken{},parsingANewLine{true}{indents.push(0);}//,dedents{0}{}

Token Tokenizer::getToken() {

    if (ungottenToken) {
        ungottenToken = false;
        return lastToken;
    }

    char c;
    int spaces = 0;
    while( inStream.get(c) && isspace(c) && c != '\n' )  // Skip spaces but not new-line chars.
        spaces++;

    if (c == '#') while (inStream.get(c) && c != '\n');  // Skip spaces and new-line chars.;

    if(inStream.bad()) {
        std::cout << "Error while reading the input stream in Tokenizer.\n";
        exit(1);
    }


    Token token;

    if (inStream.eof()) {
        if(indents.size() > 1){
            indents.pop();
            token.isDedent() = true;
            inStream.unget();
        } else token.eof() = true;
    } else if(parsingANewLine && spaces != indents.top()){ //Indent Handling
        if (spaces > indents.top()) {
            inStream.unget();
            token.setIndent(spaces);
            indents.push(spaces);
        } else if (spaces < indents.top()) {
            std::stack<int>indentsCopy = indents;
            while(!indentsCopy.empty()){
                if(spaces == indentsCopy.top())
                    break;
                indentsCopy.pop();
            }
            if(indentsCopy.empty()){
                std::cout << "BAD DEDENT: " << spaces << " spaces.\n";
                exit(1);
            } else {
                indents.pop();
                token.isDedent() = true;
                for (int i = spaces; i >= 0; i--)
                    inStream.unget();
            }
        }
    }
//    else if (spaces > indents.top() && parsingANewLine) {
//        indents.push(spaces);
//        inStream.putback(c);
//        token.isIndent() = true;
//        parsingANewLine = false;
//    } else if (spaces < indents.top() && parsingANewLine && c != '\n') {
//        while (!indents.empty()) {
//            indents.pop();
//            dedents++;
//            if(indents.top() == spaces)
//                break;
//
//        }
//        if (indents.empty()) {
//            std::cout << "Indentation error..." << std::endl;
//            exit(2);
//        }
//        inStream.putback(c);
//        token.isDedent() = true;
//        parsingANewLine = false;
//    }
    else if (c == '\n') {  // will not ever be the case unless new-line characters are not supressed.
        //parsingANewLine = true;
        token.eol() = true;
    } else if (isdigit(c)) { // a integer?
        // put the digit back into the input stream so
        // we read the entire number in a function
        inStream.putback(c);
        token.setWholeNumber(readInteger());
        //parsingANewLine = false;
    } else if (c == '>') {
        inStream.putback(c);
        token.setOp(readRelOp());
    } else if (c == '<') {
        inStream.putback(c);
        token.setOp(readRelOp());
    } else if (c == '!') {
        inStream.putback(c);
        token.setOp(readRelOp());
    } else if (c == '=') {
        if (inStream.peek() == '=') {
            inStream.putback(c);
            token.setOp(readRelOp());

        } else token.symbol(c);
    } else if (c == '"') {
        std::string str;
        while (inStream.peek() != '"') {
            inStream.get(c);
            str += c;
        }
        inStream.get(c);
        token.setString(str);

    } else if ((c == '/') && (inStream.peek() == '/')) {
        std::string str;
        str += c;
        inStream.get(c);
        str += c;
        token.setOp(str);
    } else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%') token.symbol(c);
    else if (c == ';') token.symbol(c);
    else if (c == ':') token.symbol(c);
    else if (c == '(' || c == ')') token.symbol(c);
    else if (c == '{' || c == '}') token.symbol(c);
    else if (c == '[' || c == ']') token.symbol(c);
    else if (c == ',') token.symbol(c);
    else if (c == '.') token.symbol(c);
    else if (isalpha(c)) {  // an identifier?
        // put c back into the stream so we can read the entire name in a function.
        inStream.putback(c);
        token.setName(readName());
        //parsingANewLine = false;
    } else {
        std::cout << "Unknown character in input. ->" << c << "<-" << std::endl;
        exit(1);
    }
    parsingANewLine = token.eol() || token.isDedent();


    _tokens.push_back(token);
    return lastToken = token;
}

void Tokenizer::ungetToken() {
    ungottenToken = true;
}

void Tokenizer::printProcessedTokens() {
    for (auto iter = _tokens.begin(); iter != _tokens.end(); ++iter) {
        iter->print();
        std::cout << std::endl;
    }
}

int Tokenizer::getIndent() { return indents.top(); }
