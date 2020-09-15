//
// Created by Nicky Valdecanas on 4/5/20.
//

#ifndef CS460_PROJECT3_RANGE_HPP
#define CS460_PROJECT3_RANGE_HPP

#include "SymTab.hpp"
class Range {
public:
    Range();
    Range(double rangeValue);  // set initValue to zero and stepValue to 1.
    Range(double initValue, double rangeValue);  // set stepVlaue to 1.
    Range(double initValue, double rangeValue, double stepValue);
    double getRange() { return _rangeValue; }
    double getInit() { return _initValue; }
    double getStep() { return _stepValue; }
    bool condition() { return _initValue < _rangeValue; }
    double next();       // the value to be assigned to the loop counter.

private:
    double _initValue, _stepValue, _rangeValue;
};


#endif //CS460_PROJECT3_RANGE_HPP
