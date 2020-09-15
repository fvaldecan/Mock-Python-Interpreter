#include <utility>



//
// Created by Nicky Valdecanas on 2020-03-18.
//

#ifndef CS460_PROJECT3_DESCRIPTOR_HPP
#define CS460_PROJECT3_DESCRIPTOR_HPP


#include <string>
#include <iostream>
#include <vector>
#include <utility>
struct TypeDescriptor {
    enum types {NUMBER, STRING, BOOLEAN, ARRAY};

    explicit TypeDescriptor(types type, double number = 0, std::string string = "", double boolean = 0,std::vector<TypeDescriptor*>array = {}):
        _type{type}, _number{number}, _string{std::move(string)} , _boolean(boolean), _array{std::move(array)}{}

    double getNumber(){return _number;}
    std::string getString(){return _string;}
    double getBoolean() { return _boolean;}
    std::vector<TypeDescriptor*>getArray() { return _array; }

    types &type() {return _type;}
    double _number;
    std::string _string;
    double _boolean;
    std::vector<TypeDescriptor*>_array;
    virtual ~TypeDescriptor() = default;

private:
    types _type;
};

struct NumberDescriptor: public TypeDescriptor {
    explicit NumberDescriptor(double value):  TypeDescriptor(NUMBER, value, "",false,{}), _number{value} {}
    double _number;
};
struct StringDescriptor: public TypeDescriptor {
    explicit StringDescriptor(const std::string& value):  TypeDescriptor(STRING, 0, value,false,{}), _string{value} {}
    std::string _string;
};
struct BooleanDescriptor: public TypeDescriptor {
    explicit BooleanDescriptor(const double & value):  TypeDescriptor(BOOLEAN,0,"",value,{}), _boolean{value} {}
    double _boolean;
};
struct ArrayDescriptor: public TypeDescriptor {
    explicit ArrayDescriptor(std::vector<TypeDescriptor*>array):  TypeDescriptor(ARRAY, 0, "",false, array), _array{array} {}
    std::vector<TypeDescriptor*> _array;
};
//Arithmetic Operators
TypeDescriptor *addOperator(TypeDescriptor *leftValue, TypeDescriptor *rightValue);
TypeDescriptor *subOperator(TypeDescriptor *leftValue, TypeDescriptor *rightValue);
TypeDescriptor *multOperator(TypeDescriptor *leftValue, TypeDescriptor *rightValue);
TypeDescriptor *divOperator(TypeDescriptor *leftValue, TypeDescriptor *rightValue);
TypeDescriptor *modDivOperator(TypeDescriptor *leftValue, TypeDescriptor *rightValue);
TypeDescriptor *intDivOperator(TypeDescriptor *leftValue, TypeDescriptor *rightValue);

//Comparison Operators
TypeDescriptor *equalToOperator(TypeDescriptor *leftValue, TypeDescriptor *rightValue);
TypeDescriptor *notEqualToOperator(TypeDescriptor *leftValue, TypeDescriptor *rightValue);
TypeDescriptor *lessThanOperator(TypeDescriptor *leftValue, TypeDescriptor *rightValue);
TypeDescriptor *greatThanOperator(TypeDescriptor *leftValue, TypeDescriptor *rightValue);
TypeDescriptor *lessThanEqOperator(TypeDescriptor *leftValue, TypeDescriptor *rightValue);
TypeDescriptor *greatThanEqOperator(TypeDescriptor *leftValue, TypeDescriptor *rightValue);
TypeDescriptor *orOperator(TypeDescriptor *leftValue, TypeDescriptor *rightValue);
TypeDescriptor *andOperator(TypeDescriptor *leftValue, TypeDescriptor *rightValue);




#endif //CS460_PROJECT3_DESCRIPTOR_HPP
