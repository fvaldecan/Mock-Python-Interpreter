.SUFFIXES: .o .cpp .x

CFLAGS = -ggdb -std=c++17
objects =  Token.o Tokenizer.o Parser.o ArithExpr.o SymTab.o Statements.o Range.o Testlist.o Descriptor.o main.o

statement.x: $(objects)
	g++ $(CFLAGS) -o statement.x $(objects)

.cpp.o:
	g++ $(CFLAGS) -c $< -o $@

Token.o:  Token.cpp Token.hpp
Tokenizer.o: Tokenizer.cpp Tokenizer.hpp Token.hpp
ArithExpr.o: ArithExpr.cpp ArithExpr.hpp Token.hpp SymTab.hpp
SymTab.o: SymTab.cpp SymTab.hpp Descriptor.hpp Range.hpp
Parser.o: Parser.cpp Token.hpp Parser.hpp Tokenizer.hpp SymTab.hpp ArithExpr.hpp Statements.hpp Testlist.hpp
Statements.o: Statements.cpp Statements.hpp ArithExpr.hpp Token.hpp SymTab.hpp Testlist.hpp Range.hpp
Descriptor.o: Descriptor.cpp Descriptor.hpp
Testlist.o: Testlist.cpp Testlist.hpp ArithExpr.hpp
Range.o: Range.cpp Range.hpp SymTab.hpp
main.o: main.cpp Token.hpp Tokenizer.hpp Parser.hpp SymTab.hpp ArithExpr.hpp Statements.hpp Range.hpp Testlist.hpp Descriptor.hpp

clean:
	rm -fr *.o *~ *.x
