#include "CalculatorCrankNicolson.h"
#include "utilities.h"

/******************************************************************************
 * Constructers and Destructers.
 ******************************************************************************/
CalculatorCrankNicolson::CalculatorCrankNicolson(
    const double strike,
    const double maturity,
    const double volatility,
    const double interestRate,
    const double dividend,
    const std::size_t numberOfTimeSteps,
    const double spaceStepSize)
    :
    _strike(strike),
    _volatility(volatility),
    _interestRate(interestRate),
    _dividend(dividend),
    _timeStepSize(maturity / numberOfTimeSteps),
    _spaceStepSize(spaceStepSize),
    _drift(interestRate - dividend - 0.5 * squared(volatility))
{
    
}
CalculatorCrankNicolson::~CalculatorCrankNicolson() 
{
}


double CalculatorCrankNicolson::calculateUpperValue() const
{
    return - 0.25 * _timeStepSize 
        * (squared(_volatility / _spaceStepSize) - _drift / _spaceStepSize);
}

double CalculatorCrankNicolson::calculateMiddleValue() const
{
    return 1.0 + _timeStepSize * squared(_volatility / _spaceStepSize) * 0.5
        + _interestRate * _timeStepSize * 0.5;
}

double CalculatorCrankNicolson::calculateLowerValue() const
{
    return  - 0.25 * _timeStepSize 
        * (squared(_volatility / _spaceStepSize) + _drift / _spaceStepSize);
}

