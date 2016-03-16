#pragma once

#include "Calculator.h"

#include <iostream>

class CalculatorCrankNicolson
    : public Calculator
{
public:
    CalculatorCrankNicolson(
        const double strike,
        const double maturity,
        const double volatility,
        const double interestRate,
        const double dividend,
        const std::size_t numberOfTimeSteps,
        const double spaceStepSize);
    virtual ~CalculatorCrankNicolson();

    virtual double calculateUpperValue() const;
    virtual double calculateMiddleValue() const;
    virtual double calculateLowerValue() const;
    
private:
    const double _strike;
    const double _volatility;
    const double _interestRate;
    const double _dividend;
    const double _timeStepSize;
    const double _spaceStepSize;
    const double _drift;
};

