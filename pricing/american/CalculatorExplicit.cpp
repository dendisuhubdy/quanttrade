#include "CalculatorExplicit.h"
#include "utilities.h"

/******************************************************************************
 * Constructers and Destructers.
 ******************************************************************************/
CalculatorExplicit::CalculatorExplicit(
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
CalculatorExplicit::~CalculatorExplicit() 
{
}


double CalculatorExplicit::calculateUpperValue() const
{
    return 0.5 * _timeStepSize 
        * (squared(_volatility / _spaceStepSize) - _drift / _spaceStepSize);
}

double CalculatorExplicit::calculateMiddleValue() const
{
    return 1.0 - _timeStepSize * squared(_volatility / _spaceStepSize)
        - _interestRate * _timeStepSize;
}

double CalculatorExplicit::calculateLowerValue() const
{
    return 0.5 * _timeStepSize 
        * (squared(_volatility / _spaceStepSize) + _drift / _spaceStepSize);
}

