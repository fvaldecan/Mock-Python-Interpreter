#include <iostream>
#include <vector>
#include "Token.hpp"
#include "Tokenizer.hpp"
#include "Parser.hpp"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cout << "usage: " << argv[0] << " nameOfAnInputFile\n";
        exit(1);
    }
    std::ifstream inputStream;
    inputStream.open(argv[1], std::ios::in);
    if (!inputStream.is_open()) {
        std::cout << "Unable top open " << argv[1] << ". Terminating...";
        perror("Error when attempting to open the input file.");
        exit(2);
    }
    // Create tokens from Python file 
    Tokenizer tokenizer(inputStream); 

    // Parse tokens converting into matched Python statements
    Parser parser(tokenizer); 
    Statements *statements = parser.fileInput();

    Token lastToken = tokenizer.getToken();
    if (!lastToken.eof()) {
        std::cout << "Unexpected token in input." << std::endl;
        lastToken.print();
        exit(1);
    }
    // Use Symbol table to map variables and data types
    SymTab symTab;
    std::cout << "INPUT\n";
    std::cout << "********\n";
    statements->print();

    std::cout << "OUTPUT\n";
    std::cout << "********\n";

    // Evaluate and calculate Python statements and expressions
    statements->evaluate(symTab);
    std::cout << std::endl << "Symbol table contains the following variables.\n";
    symTab.print();

    return 0;
}