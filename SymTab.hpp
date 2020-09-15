//
// Created by Nicky Valdecanas on 2020-02-29.
//

#ifndef CS460_PROJECT3_SYMTAB_HPP
#define CS460_PROJECT3_SYMTAB_HPP


#include <string>
#include <map>
#include "Descriptor.hpp"
#include "Range.hpp"
// This is a flat and integer-based symbol table. It allows for variables to be
// initialized, determines if a give variable has been defined or not, and if
// a variable has been defined, it returns its value.

class SymTab {
public:
    void setValueFor(std::string vName, TypeDescriptor *value);
    bool isDefined(std::string vName);
    TypeDescriptor *getValueFor(std::string vName);
    void print();

private:
    std::map<std::string, TypeDescriptor*> symTab;
};
#endif  //CS460_PROJECT3_SYMTAB_HPP
