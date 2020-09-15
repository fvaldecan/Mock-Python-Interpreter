//
// Created by Nicky Valdecanas on 2020-02-29.
//

#ifndef CS460_PROJECT3_TOKENIZER_HPP
#define CS460_PROJECT3_TOKENIZER_HPP


#include <fstream>
#include <vector>
#include "Token.hpp"
#include <stack>

class Tokenizer {

public:
    Tokenizer(std::ifstream &inStream);
    Token getToken();
    void ungetToken();
    void printProcessedTokens();
    int getIndent();
    //void subtractDedents();

    //std::stack<int>initializeStack(){ indents.push(0); }

private:
    Token lastToken;
    bool ungottenToken;
    std::ifstream &inStream;
    std::vector<Token> _tokens;
    std::string readName();
    std::string readRelOp();
    double readInteger();
    std::stack<int>indents;
    bool parsingANewLine;
    //int dedents;
};

#endif  //CS460_PROJECT3_TOKENIZER_HPP
