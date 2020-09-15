//
// Created by Nicky Valdecanas on 2020-02-29.
//


#include <iostream>
#include "SymTab.hpp"


void SymTab::setValueFor(std::string vName, TypeDescriptor *value) {
    // Define a variable by setting its initial value.
//    if(value->type() == TypeDescriptor::NUMBER
//    || value->type() == TypeDescriptor::BOOLEAN) {
//        double numValue = value->getNumber();
//        if(value->type() == TypeDescriptor::BOOLEAN){
//            if(numValue > 0) numValue = 1;
//        }
//        std::cout << "SymTab::setValueFor: " << vName << " contains " << numValue << std::endl;
//    }else{
//        std::string stringValue = value->getString();
//        std::cout << "SymTab::setValueFor: " << vName << " contains " << stringValue << std::endl;
//
//    }
    symTab[vName] = value;
}

bool SymTab::isDefined(std::string vName) {
    return symTab.find(vName) != symTab.end();
}

TypeDescriptor *SymTab::getValueFor(std::string vName) {
    if( ! isDefined(vName)) {
        std::cout << "SymTab::getValueFor: " << vName << " has not been defined.\n";
        exit(1);
    }
    TypeDescriptor *value = symTab[vName];
//    if(value->type() == TypeDescriptor::NUMBER) {
//        double numValue = value->getNumber();
//        std::cout << "SymTab::getValueFor: " << vName << " contains " << numValue << std::endl;
//    } else if(value->type() == TypeDescriptor::BOOLEAN) {
//        if(value->getBoolean())
//            std::cout << "SymTab::getValueFor: " << vName << " contains true" << std::endl;
//        else{
//            std::cout << "SymTab::getValueFor: " << vName << " contains false" << std::endl;
//        }
//    }else{
//        std::string stringValue = value->getString();
//        std::cout << "SymTab::getValueFor: " << vName << " contains " << stringValue << std::endl;
//
//    }
    return value;

}

void SymTab::print() {
    for(auto [var, value] : symTab ) {
        if (value->type() == TypeDescriptor::NUMBER)
            std::cout << var << " = " << value->getNumber() << std::endl;
        else if (value->type() == TypeDescriptor::STRING) std::cout << var << " = " << value->getString() << std::endl;
        else { //Array
            std::cout << var << " = [";
            std::vector<TypeDescriptor*>array = value->getArray();

            for(int i = 0; i < array.size();i++){
                if(i != 0) std::cout << ", ";
                if(array[i]->type() == TypeDescriptor::NUMBER) std::cout << array[i]->getNumber();
                else std::cout << array[i]->getString();
            }
            std::cout << "] " << std::endl;

        }
    }

}