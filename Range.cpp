//
// Created by Nicky Valdecanas on 4/5/20.
//

#include "Range.hpp"
Range::Range() {}
Range::Range(double rangeValue){
    _initValue = 0;
    _rangeValue = rangeValue;
    _stepValue = 1;
}
Range::Range(double initValue, double rangeValue) {
    _initValue = initValue;
    _rangeValue = rangeValue;
    _stepValue = 1;
}

Range::Range(double initValue, double rangeValue, double stepValue){
    _initValue = initValue;
    _rangeValue = rangeValue;
    _stepValue = stepValue;
}


double Range::next() {
    double i = _initValue;
    _initValue += _stepValue;
    return i;
}




