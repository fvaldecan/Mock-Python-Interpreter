//
// Created by Nicky Valdecanas on 2020-03-18.
//

#include "Descriptor.hpp"
#include <cmath>



TypeDescriptor *addOperator(TypeDescriptor *leftValue, TypeDescriptor *rightValue){
    if(leftValue->type() == TypeDescriptor::NUMBER){
        auto *numSum = new  NumberDescriptor(leftValue->getNumber() + rightValue->getNumber());
        //std::cout << "TypeDescriptor* addOperator: " << leftValue->getNumber() << " + " << rightValue->getNumber() << std::endl;
        return numSum;
    }else if(leftValue->STRING){

        auto *stringSum = new StringDescriptor( leftValue->getString()  + rightValue->getString() );
        return stringSum;
    }else{
        std::cout << "Unknown type. Terminating" << std::endl;
        exit(2);
    }
}
TypeDescriptor *subOperator(TypeDescriptor *leftValue, TypeDescriptor *rightValue){
    if(leftValue->type() == TypeDescriptor::NUMBER){
        auto *numSum = new  NumberDescriptor(leftValue->getNumber() - rightValue->getNumber());
        //std::cout << "TypeDescriptor *subOperator: " << leftValue->getNumber() << " - " << rightValue->getNumber() << std::endl;
        return numSum;
    }else if(leftValue->STRING){
        std::cout << "TypeDescriptor *subOperator: " << leftValue->getString()  << " - " << rightValue->getString()  << std::endl;
        std::cout << "Cannot subtract:" << leftValue->getString()  << " - " << rightValue->getString()  << std::endl;
        exit(2);
    }else{
        std::cout << "Unknown type. Terminating..." << std::endl;
        exit(2);
    }
}
TypeDescriptor *multOperator(TypeDescriptor *leftValue, TypeDescriptor *rightValue){
    if(leftValue->type() == TypeDescriptor::NUMBER
    && rightValue->type() == TypeDescriptor::NUMBER){
        auto *numProduct = new  NumberDescriptor(leftValue->getNumber() * rightValue->getNumber());
        //std::cout << "TypeDescriptor *multOperator: " << leftValue->getNumber() << " * " << rightValue->getNumber() << std::endl;
        return numProduct;
    }else if(leftValue->type() == TypeDescriptor::STRING
    && rightValue->type() == TypeDescriptor::STRING){
        std::cout << "TypeDescriptor *multOperator: " << leftValue->getString()  << " * " << rightValue->getString()  << std::endl;
        std::cout << "Cannot multiply:" << leftValue->getString()  << " * " << rightValue->getString()  << std::endl;
        exit(2);
    }else{
        if(std::fmod(leftValue->getNumber(),1) == 0
        ||std::fmod(rightValue->getNumber(),1) == 0){
            double range = 0;
            std::string stringValue;
            if(leftValue->type() == TypeDescriptor::NUMBER){
                range = leftValue->getNumber();
                stringValue = rightValue->getString();
            }
            else{
                range = rightValue->getNumber();
                stringValue = leftValue->getString();
            }
            std::string finalValue;
            for(int i = 0; i < range; i++){
                finalValue += stringValue;
            }
            auto *stringProduct = new StringDescriptor(finalValue);
            return stringProduct;
        }
        else{
            std::cout << "Unknown type. Terminating..." << std::endl;
            exit(2);
        }
    }
}
TypeDescriptor *divOperator(TypeDescriptor *leftValue, TypeDescriptor *rightValue){
    if(leftValue->type() == TypeDescriptor::NUMBER
    && rightValue->type() == TypeDescriptor::NUMBER){
        auto *numSum = new  NumberDescriptor(leftValue->getNumber() / rightValue->getNumber());
        //std::cout << "TypeDescriptor *divOperator: " << leftValue->getNumber() << " / " << rightValue->getNumber() << std::endl;
        return numSum;
    }else if(leftValue->type() == TypeDescriptor::STRING
    || rightValue->type() == TypeDescriptor::STRING){
        std::cout << "TypeDescriptor *divOperator: " << leftValue->getString()  << " / " << rightValue->getString()  << std::endl;
        std::cout << "Cannot divide:" << leftValue->getString()  << " / " << rightValue->getString()  << std::endl;
        exit(2);
    }else{
        std::cout << "Unknown type. Terminating..." << std::endl;
        exit(2);
    }
}
TypeDescriptor *modDivOperator(TypeDescriptor *leftValue, TypeDescriptor *rightValue){
    if(leftValue->type() == TypeDescriptor::NUMBER
    && rightValue->type() == TypeDescriptor::NUMBER){
        auto *remainder = new  NumberDescriptor(fmod(leftValue->getNumber(), rightValue->getNumber()));
        //std::cout << "TypeDescriptor *modDivOperator: " << leftValue->getNumber() << " % " << rightValue->getNumber() << std::endl;
        return remainder;
    }else if(leftValue->type() == TypeDescriptor::STRING
    || rightValue->type() == TypeDescriptor::STRING ){

        std::cout << "TypeDescriptor *modDivOperator: " << leftValue->getString()  << " % " << rightValue->getString()  << std::endl;
        std::cout << "Cannot do modular division:" << leftValue->getString()  << " % " << rightValue->getString()  << std::endl;
        exit(2);
    }else{
        std::cout << "Unknown type. Terminating..." << std::endl;
        exit(2);
    }
}
TypeDescriptor *intDivOperator(TypeDescriptor *leftValue, TypeDescriptor *rightValue){
    //std::cout << "TypeDescriptor *modDivOperator: " << leftValue->getNumber() << " // " << rightValue->getNumber() << std::endl;
    TypeDescriptor *intQuotient = divOperator(leftValue, rightValue);
    intQuotient->_number = (int)intQuotient->_number;
    return intQuotient;
}
TypeDescriptor *lessThanOperator(TypeDescriptor *leftValue, TypeDescriptor *rightValue){
    if(leftValue->type() == TypeDescriptor::NUMBER
       && rightValue->type() == TypeDescriptor::NUMBER){
        auto *numLess = new  NumberDescriptor(leftValue->getNumber() < rightValue->getNumber() ? 1.0 : 0.0);
        //std::cout << "TypeDescriptor *lessThanOperator: " << leftValue->getNumber() << " < " << rightValue->getNumber() << std::endl;
        return numLess;
    }else if(leftValue->type() == TypeDescriptor::STRING
             && rightValue->type() == TypeDescriptor::STRING ){
        auto *stringLess = new  NumberDescriptor(leftValue->getString()  < rightValue->getString()  ? 1.0 : 0.0);
        //std::cout << "TypeDescriptor *lessThanOperator: " << leftValue->getString()  << " <  " << rightValue->getString()  << std::endl;
        return stringLess;
    }else{
        std::cout << "Unknown type. Terminating..." << std::endl;
        exit(2);
    }
}
TypeDescriptor *lessThanEqOperator(TypeDescriptor *leftValue, TypeDescriptor *rightValue){
    if(leftValue->type() == TypeDescriptor::NUMBER
       && rightValue->type() == TypeDescriptor::NUMBER){
        auto *numLessEq = new  NumberDescriptor(leftValue->getNumber() <= rightValue->getNumber() ? 1.0 : 0.0);
        //std::cout << "TypeDescriptor *lessThanEqOperator: " << leftValue->getNumber() << " <= " << rightValue->getNumber() << std::endl;
        return numLessEq;
    }else if(leftValue->type() == TypeDescriptor::STRING
             && rightValue->type() == TypeDescriptor::STRING ){
        auto *stringLessEq = new  NumberDescriptor(leftValue->getString()  <= rightValue->getString()  ? 1.0 : 0.0);
        //std::cout << "TypeDescriptor *lessThanEqOperator: " << leftValue->getString()  << " <=  " << rightValue->getString()  << std::endl;
        return stringLessEq;
    }else{
        std::cout << "Unknown type. Terminating..." << std::endl;
        exit(2);
    }
}
TypeDescriptor *greatThanOperator(TypeDescriptor *leftValue, TypeDescriptor *rightValue){
    if(leftValue->type() == TypeDescriptor::NUMBER
       && rightValue->type() == TypeDescriptor::NUMBER){
        auto *numGreater = new  NumberDescriptor(leftValue->getNumber() > rightValue->getNumber() ? 1.0 : 0.0);
        //std::cout << "TypeDescriptor *greatThanOperator: " << leftValue->getNumber() << " > " << rightValue->getNumber() << std::endl;
        return numGreater;
    }else if(leftValue->type() == TypeDescriptor::STRING
             && rightValue->type() == TypeDescriptor::STRING ){
        auto *stringGreater = new  NumberDescriptor(leftValue->getString()  >= rightValue->getString()  ? 1.0 : 0.0);
        //std::cout << "TypeDescriptor *greatThanOperator: " << leftValue->getString()  << " >  " << rightValue->getString()  << std::endl;
        return stringGreater;
    }else{
        std::cout << "Unknown type. Terminating..." << std::endl;
        exit(2);
    }
}
TypeDescriptor *greatThanEqOperator(TypeDescriptor *leftValue, TypeDescriptor *rightValue){
    if(leftValue->type() == TypeDescriptor::NUMBER
    && rightValue->type() == TypeDescriptor::NUMBER){
        auto *numGreaterEq = new  NumberDescriptor(leftValue->getNumber() >= rightValue->getNumber() ? 1.0 : 0.0);
        //std::cout << "TypeDescriptor *greatThanEqOperator: " << leftValue->getNumber() << " >= " << rightValue->getNumber() << std::endl;
        return numGreaterEq;
    }else if(leftValue->type() == TypeDescriptor::STRING
    && rightValue->type() == TypeDescriptor::STRING ){
        auto *stringGreaterEq = new  NumberDescriptor(leftValue->getString()  >= rightValue->getString()  ? 1.0 : 0.0);
        //std::cout << "TypeDescriptor *greatThanEqOperator: " << leftValue->getString()  << " >= " << rightValue->getString()  << std::endl;
        return stringGreaterEq;
    }else{
        std::cout << "Unknown type. Terminating..." << std::endl;
        exit(2);
    }
}
TypeDescriptor *equalToOperator(TypeDescriptor *leftValue, TypeDescriptor *rightValue){
    if(leftValue->type() == TypeDescriptor::NUMBER
    && rightValue->type() == TypeDescriptor::NUMBER){
        auto *numEqual = new  NumberDescriptor(leftValue->getNumber() == rightValue->getNumber() ? 1.0 : 0.0);
        //std::cout << "TypeDescriptor *equalToOperator: " << leftValue->getNumber() << " == " << rightValue->getNumber() << std::endl;
        return numEqual;
    }else if(leftValue->type() == TypeDescriptor::STRING
    && rightValue->type() == TypeDescriptor::STRING ){
        auto *stringEqual = new  NumberDescriptor(leftValue->getString()  == rightValue->getString()  ? 1.0 : 0.0);
        //std::cout << "TypeDescriptor *equalToOperator: " << leftValue->getString()  << " == " << rightValue->getString()  << std::endl;
        return stringEqual;
    }else{
        std::cout << "Unknown type. Terminating..." << std::endl;
        exit(2);
    }
}
TypeDescriptor *notEqualToOperator(TypeDescriptor *leftValue, TypeDescriptor *rightValue){
    if(leftValue->type() == TypeDescriptor::NUMBER
       && rightValue->type() == TypeDescriptor::NUMBER){
        auto *numEqual = new  NumberDescriptor(leftValue->getNumber() != rightValue->getNumber() ? 1.0 : 0.0);
        //std::cout << "TypeDescriptor *notEqualToOperator: " << leftValue->getNumber() << " != " << rightValue->getNumber() << std::endl;
        return numEqual;
    }else if(leftValue->type() == TypeDescriptor::STRING
             && rightValue->type() == TypeDescriptor::STRING ){
        auto *stringEqual = new  NumberDescriptor(leftValue->getString()  != rightValue->getString()  ? 1.0 : 0.0);
        //std::cout << "TypeDescriptor *notEqualToOperator: " << leftValue->getString()  << " != " << rightValue->getString() << std::endl;
        return stringEqual;
    }else{
        std::cout << "Unknown type. Terminating..." << std::endl;
        exit(2);
    }
}
TypeDescriptor *orOperator(TypeDescriptor *leftValue, TypeDescriptor *rightValue){
    if(leftValue->type() == TypeDescriptor::NUMBER
       && rightValue->type() == TypeDescriptor::NUMBER){
        auto *numEqual = new NumberDescriptor(leftValue->getNumber() == 1.0 || rightValue->getNumber() == 1.0);
        return numEqual;
    }
}
TypeDescriptor *andOperator(TypeDescriptor *leftValue, TypeDescriptor *rightValue){
    if(leftValue->type() == TypeDescriptor::NUMBER
       && rightValue->type() == TypeDescriptor::NUMBER){
        auto *numEqual = new NumberDescriptor(leftValue->getNumber() == 1.0 && rightValue->getNumber() == 1.0);
        return numEqual;
    }
}