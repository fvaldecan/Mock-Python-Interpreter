//
// Created by Nicky Valdecanas on 2020-02-29.
//

#include "Statements.hpp"
//#include "Functions.hpp"
// Statement
Statement::Statement() {}

// Statements

Statements::Statements() : _indState{0},_isFunction{false} {}
Statements::Statements(int indentState) : _indState{indentState} {}
void Statements::addStatement(Statement *statement) { _statements.push_back(statement); }

void Statements::print() {
    //std::cout << "Printing Statements...\n";

    for (auto s: _statements) {
        std::cout << "\n";
        if(s == NULL) continue;
        for (int i = 0; i < _indState; i++)
            std::cout << " "; // exact spaces for indent
        s->indentState = _indState;
        s->print();
    }

}

void Statements::evaluate(SymTab &symTab) {
    //std::cout << "Evaluating Statements...\n";
    auto *funcs= new Functions();
    for (auto s: _statements) {
        if(s == NULL) continue;
        if(s->isFunction){
            funcs->addFunction(dynamic_cast<Function *>(s));
        } else {
            if(!funcs->getFunctionStack().empty()) {
                if(funcs->findFunction(dynamic_cast<Function *>(s))) {
                    s = funcs->returnFunction(dynamic_cast<Function *>(s));
                }
                std::vector<Statement*>stack;
                std::vector<Function*>functionStack = funcs->getFunctionStack();
                //funcs->setStack(functionStack);
                for(int i = 0; i < functionStack.size();i++){
                    Function *function = functionStack[i];
                    stack.push_back(function);
                }
                s->passStack(stack);
                //s->passFunctions(reinterpret_cast<Statement*>(funcs->returnFunction(dynamic_cast<Function *>(s))));

            }
            s->evaluate(symTab);
            std::cout << std::endl;
        }
    }
}
Function::Function(): _statements{} {}

Function::Function(std::string id, std::vector<std::string>paramenters,Statements *statements) :
    _id{id}, _paramenters{std::move(paramenters)},_statements{statements} {}

void Function::evaluate(SymTab &symTab) {
    if(paramenters().empty()) {
        statements()->evaluate(symTab);
    }
}

void Function::print() {
    std::cout <<"def "<< id() << "(";
    for(int i = 0; i < paramenters().size();i++){
        if(i != 0)std::cout << ",";
        std::cout << paramenters()[i];
    }
    std::cout << "):" << std::endl;
    statements()->print();
}


Functions::Functions(): _functionStack{} {}

void Functions::addFunction(Function *function) {
//    Function *newFunction = new Function()
    _functionStack.push_back(function);
}

bool Functions::findFunction(Function *function) {
    if(function == nullptr) return false;
    if(!getFunctionStack().empty()) {
        for (int i = 0; i < getFunctionStack().size(); i++) {
            std::string findFID = function->id();
            std::string stackFID = getFunctionStack()[i]->id();
            if (findFID == stackFID) {
                return true;
            }
        }
    }
    return false;
}

Function *Functions::returnFunction(Function *function) {
    for(int i = 0; i < getFunctionStack().size();i++){
        std::string findFID =function->id();
        std::string stackFID = getFunctionStack()[i]->id();
        if(findFID == stackFID ) {
            return getFunctionStack()[i];
        }
    }
}

void Functions::passFunctionStack(Statement *statement) {

}

CallStatement::CallStatement() : _testlist{} {}

CallStatement::CallStatement(std::string id, Testlist *testlist) :
        _id{std::move(id)}, _testlist{testlist} {}
void CallStatement::print() {
//    id().print();
    std::cout << id() << "(";
    if(testList() != nullptr) testList()->print();
    std::cout << ")";
}
bool CallStatement::callFinder(const Token& id){
    for(int i = 0; i < getFunctionStack().size();i++) {
        if (id.getName() == getFunctionStack()[i]->id())
            return true;
    }
}

void CallStatement::evaluate(SymTab &symTab){//,std::vector<Function*>stack) {
    //if()
//    std::vector<std::string>params;
//    //params.reserve(testList()->numTests());
//    for(int i = 0; i < testList()->numTests();i++){
//        params.push_back(testList()->at(i)->token().getName());
//    }
//    auto *function = new Function;
//    function->paramenters() = params;
//    std::vector<Function*>functions = getFunctionStack();
//    //Statement *function = passBackFunction();
//    //
//    //Functions *functions
}

TypeDescriptor *CallStatement::evaluateCallExpr(SymTab &symTab,std::vector<Statement*>stack,std::string id) {
//    Functions().setStack();
    //or(int i = 0; i < )
    std::cout << "HERE";
    //std::vector<Statement*>stack = this->_functionStack;
    for(int i = 0; i < stack.size();i++){
        //stack[i]->id();
    }
//    if(findFunction(this)){
//        Function *function = returnFunction(this);
//        SymTab symTab1;
//        for(int i = 0; i < function->paramenters().size(); i++){
//            //symTab1.setValueFor(function->pa)
//        }
//        function->evaluate(symTab1);
//    }
    //return nullptr;
}

AssignmentStatement::AssignmentStatement() :  _lhsVariable{""}, _rhsExpression{nullptr},_testlist{nullptr},_subscription{nullptr} {}

AssignmentStatement::AssignmentStatement(std::string lhsVar, ExprNode *rhsExpr):
        _lhsVariable{lhsVar}, _rhsExpression{rhsExpr},_testlist{nullptr},_subscription{nullptr} {}

AssignmentStatement::AssignmentStatement(std::string lhsVar, Testlist *testlist):
    _lhsVariable{lhsVar}, _rhsExpression{nullptr}, _testlist{testlist},  _subscription{nullptr} {}

AssignmentStatement::AssignmentStatement(std::string lhsVar, ExprNode*subscription, ExprNode *rhsExpr):
        _lhsVariable{lhsVar}, _rhsExpression{rhsExpr}, _testlist{nullptr},_subscription{subscription} {}

//AssignmentStatement::AssignmentStatement(std::string lhsVar,ExprNode*subscription, Testlist *testlist):
//        _lhsVariable{lhsVar}, _rhsExpression{nullptr}, _testlist{testlist}, _subscription{subscription} {}

void AssignmentStatement::evaluate(SymTab &symTab) {
    //std::cout << "Evaluating Assignment Statement...\n";
    //std::cout << "----ASSIGN-START---- \n";
    if(rhsExpression() != nullptr) {
        if(subscription() == nullptr) {
            //rhsExpression() = reinterpret_cast<CallStatement*>(rhsExpression());
            //rhsExpression()->passStack();
            TypeDescriptor *rhs = rhsExpression()->evaluate(symTab);
            //std::cout << "OUTSIDE";
            if(rhs == nullptr){
                //std::cout << "INSIDE";
                auto *callback = reinterpret_cast<CallStatement *>(rhsExpression());
                callback->passStack(this->_functionStack);
                rhs = callback->evaluateCallExpr(symTab,_functionStack,rhsExpression()->token().getName());
            } //rhs = rhsExpression()->evaluate(symTab);
            symTab.setValueFor(lhsVariable(), rhs);
        }else{ // subscription ID[index]

            TypeDescriptor *value = symTab.getValueFor(lhsVariable());
            std::vector<TypeDescriptor*>array = value->getArray();
            TypeDescriptor *rhs = rhsExpression()->evaluate(symTab);
            TypeDescriptor *sub = subscription()->evaluate(symTab);
            double index = sub->getNumber();
            for(int i = 0; i < array.size();i++){
                if(i == index){
                    array[i] = rhs;
                }
            }
            TypeDescriptor *updatedArray = new ArrayDescriptor(array);
            symTab.setValueFor(lhsVariable(),updatedArray); //Update array


        }
    }else{
        std::vector<TypeDescriptor*>array;
        TypeDescriptor *first = testlist()->at(0)->evaluate(symTab);
        array.push_back(first);
        for(int i = 1; i < testlist()->numTests(); i++){
            TypeDescriptor *element = testlist()->at(i)->evaluate(symTab);
            if(first->type() != element->type()){
                std::cout << "ELEMENT TYPES NO CONSISTENT ";
                exit(1);
            }
            array.push_back(element);
        }
        TypeDescriptor *list = new ArrayDescriptor(array);
        symTab.setValueFor(lhsVariable(),list);
    }
    //std::cout << "-----ASSIGN-END----- \n";

}

std::string &AssignmentStatement::lhsVariable() {
    return _lhsVariable;
}

ExprNode *&AssignmentStatement::rhsExpression() {
    return _rhsExpression;
}
ExprNode *&AssignmentStatement::subscription() {
    return _subscription;
}

Testlist *&AssignmentStatement::testlist() {
    return _testlist;
}
void AssignmentStatement::print() {
    //std::cout << "Printing Assignment Statement...\n";
    if(subscription() == nullptr) std::cout << lhsVariable() << " = ";
    else {
        std::cout << lhsVariable() << "[";
        subscription()->print();
        std::cout << "] = ";
    }

    if (rhsExpression() == nullptr){
        std::cout << " [ ";
        testlist()->print();
        std::cout << " ] ";
    }
    else rhsExpression()->print();
}



// ForStatement

ForStatement::ForStatement() {}

ForStatement::ForStatement(ExprNode *id, Testlist *testlist, Statements *stmts) :
    _id{id}, _testlist{testlist}, _stmts{stmts} {}

ExprNode *&ForStatement::id() {
    return _id;
}
Testlist *&ForStatement::testlist(){
    return _testlist;
}

Statements *&ForStatement::statements() {
    return _stmts;
}
void ForStatement::evaluate(SymTab &symTab) {
    //std::cout << "-----FOR-START-----\n";
    Range *instance = nullptr;
    if(testlist()->numTests() == 1) {
        instance = new Range(testlist()->at(0)->evaluate(symTab)->getNumber());
    }
    else if(testlist()->numTests() == 2) {
        instance = new Range(testlist()->at(0)->evaluate(symTab)->getNumber(),
                testlist()->at(1)->evaluate(symTab)->getNumber());
    }else{
        instance = new Range(testlist()->at(0)->evaluate(symTab)->getNumber(),
                             testlist()->at(1)->evaluate(symTab)->getNumber(),
                             testlist()->at(2)->evaluate(symTab)->getNumber());
    }

    while(instance->condition()) {
        auto *curVal = new TypeDescriptor(TypeDescriptor::NUMBER, instance->next(), id()->token().getName());
        symTab.setValueFor(id()->token().getName(), curVal);
        statements()->evaluate(symTab);
    }
    //std::cout << "------FOR-END------\n";

}

void ForStatement::print() {

    std::cout << "for ";
    _id->print();
    std::cout << " in range(";
    _testlist->print();
    std::cout << ") :" << std::endl;
    std::cout << "     ";
    _stmts->print();
    std::cout << "";

}



//PrintStatement

PrintStatement::PrintStatement() : _testlist{} {}

PrintStatement::PrintStatement(Testlist *testlist) : _testlist{testlist} {}



void PrintStatement::evaluate(SymTab &symTab) {
    //std::cout << "----PRINT-START---- \n";
    std::vector<ExprNode*>testlist = testList()->getTestlist();
    for (ExprNode *exprNode : testlist) {
        TypeDescriptor typeDescriptor = *exprNode->evaluate(symTab);
        if(typeDescriptor.type() == TypeDescriptor::NUMBER)
            std::cout << typeDescriptor.getNumber() << " " << std::endl;
        else if(typeDescriptor.type() == TypeDescriptor::STRING)
            std::cout << typeDescriptor.getString() << " " << std::endl;
        else { //ARRAY
            std::vector<TypeDescriptor*>array = typeDescriptor.getArray();
            std::cout << "[";
            if(array[0]->type() == TypeDescriptor::NUMBER) {
                for (int i = 0; i < array.size(); i++) {
                    if(i != 0) std::cout << ", ";
                    std::cout << array[i]->getNumber();
                }
            } else{ // String Elements
                for (int i = 0; i < array.size(); i++) {
                    if(i != 0) std::cout << ", ";
                    std::cout << array[i]->getString();
                }
            }
            std::cout << "]";//<< std::endl;
        }
    }
    //std::cout << "-----PRINT-END----- \n";
}

void PrintStatement::print() {
    std::cout << "print ";
    std::vector<ExprNode*>testlist = testList()->getTestlist();
    for(ExprNode* exprNode : testlist){
        exprNode->print();
        std::cout << ", ";
    }
    std::cout << "\b\b ";
    std::cout << std::endl;

}


//std::vector<ExprNode *> &PrintStatement::testList() { return _testlist; }
//IfStatement::IfStatement() : //_testsAndSuites{} {}
//
//IfStatement::IfStatement(std::vector<std::pair<ExprNode*,Statements*>>testsAndSuites) : _testsAndSuites{std::move(testsAndSuites)} {}
IfStatement::IfStatement() : _cond{nullptr}, _stmts{nullptr}, _elif{nullptr} {}
IfStatement::IfStatement(ExprNode* condition, Statements* statements) : _cond{condition}, _stmts{statements}, _elif{nullptr} {}
IfStatement::IfStatement(ExprNode* condition, Statements* statements, IfStatement* elif) : _cond{condition}, _stmts{statements}, _elif{elif} {}
void IfStatement::evaluate(SymTab &symTab) {
    if((_cond == nullptr) || (_cond->evaluate(symTab)->_number > 0)) _stmts->evaluate(symTab);
    else if(_elif != nullptr) _elif->evaluate(symTab);
//    std::vector<std::pair<ExprNode *, Statements *>> testsAndSuites = getTestsAndSuites();
//    int i = 0;
//    bool elseStatement = true;
//    while(i < testsAndSuites.size()){
//        if (testsAndSuites[i].first == nullptr) {i++; continue;}
//        if(testsAndSuites[i].first->evaluate(symTab)->getNumber() != 0) {
//            testsAndSuites[i].second->evaluate(symTab);
//            elseStatement = false;
//        }
//        i++;
//    }
//    if (elseStatement)
//        testsAndSuites[i-1].second->evaluate(symTab);
}

void IfStatement::print() {
    //std::cout << "Printing If Statement...\n";
    std::cout << "if "; _cond->print(); std::cout << ":";
    _stmts->print();
    IfStatement* next = _elif;
    while(next != nullptr) {
        if (next->_cond == nullptr){
            std::cout << std::endl;
            for (int i = 0; i < indentState; i++)
                std::cout << " ";
            std::cout << "else";
        } else {
            std::cout << std::endl;
            for (int i = 0; i < indentState; i++)
                std::cout << " ";
            std::cout << "elif "; next->_cond->print();
        }
        std::cout << ":";
        next->_stmts->print();
        next = next->_elif;
    }
//    std::vector<std::pair<ExprNode*,Statements*>>testsAndSuites = getTestsAndSuites();
//    for(int i = 0; i < testsAndSuites.size();i++){
//        if(i == 0) {
//            std::cout << "if ";
//            testsAndSuites[i].first->print();
//            std::cout <<" : \n";
//            std::cout << "     ";
//            testsAndSuites[i].second->print();
//        }
//        else if( testsAndSuites[i].first == nullptr) {
//            std::cout << "else ";
//            std::cout << " : \n";
//            std::cout << "     ";
//            testsAndSuites[i].second->print();
//        }
//        else{
//            std::cout << "elif ";
//            testsAndSuites[i].first->print();
//            std::cout <<" : \n";
//            std::cout << "     ";
//            testsAndSuites[i].second->print();
//        }
//    }
}
void IfStatement::setElif(IfStatement *elif) { _elif = elif; }
//std::vector<std::pair<ExprNode *, Statements *>> &IfStatement::getTestsAndSuites() {
//    return _testsAndSuites;
//}


ArrayOps::ArrayOps() {}

ArrayOps::ArrayOps(ExprNode *id, Token op, ExprNode *test) :
    _id{id}, _op{std::move(op)}, _test{test} {}

void ArrayOps::print() {
    _id->print();

    std::cout << ".";
    _op.print();
    std::cout << "(";
    if(_test != nullptr)
        _test->print();
    std::cout << ")";
    std::cout << std::endl;
}

void ArrayOps::evaluate(SymTab &symTab) {
    TypeDescriptor *value = symTab.getValueFor(_id->token().getName());
    std::vector<TypeDescriptor*>array = value->getArray();
    if(_op.getName() == "append"){
        if(_test->evaluate(symTab)->type() == TypeDescriptor::NUMBER){
            TypeDescriptor *newElement = new NumberDescriptor(_test->evaluate(symTab)->getNumber());
            array.push_back(newElement);
        }else{
            TypeDescriptor *newElement = new StringDescriptor(_test->evaluate(symTab)->getString());
            array.push_back(newElement);
        }

    }else{ // pop
        if(_test== nullptr) { //pop Last
            array.pop_back();
        }else{
            int index = _test->evaluate(symTab)->getNumber();
            array.erase(array.begin()+ index -1);
        }
    }
    TypeDescriptor *updatedArray = new ArrayDescriptor(array);
    symTab.setValueFor(_id->token().getName(),updatedArray);

}




ReturnStatement::ReturnStatement() {}

ReturnStatement::ReturnStatement(ExprNode *test) : _test{test} {}

void ReturnStatement::evaluate(SymTab &symTab) {

}

void ReturnStatement::print() {
    std::cout <<"return ";
    getTest()->print();
}





