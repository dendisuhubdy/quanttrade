#include "BoundaryConditionCall.h"

/******************************************************************************
 * Constructers and Destructers.
 ******************************************************************************/
BoundaryConditionCall::BoundaryConditionCall(
    const boost::numeric::ublas::vector<double>& stocks)
    :
    _stocks(stocks)
{
    
}
BoundaryConditionCall::~BoundaryConditionCall() 
{
}

/******************************************************************************
 * inherited pure virtual functions.
 ******************************************************************************/
double BoundaryConditionCall::upperCondition(
    const boost::numeric::ublas::vector<double>& rightHandSide) const
{
    const std::size_t lastIndex = _stocks.size() - 1;
    return - _stocks[lastIndex - 1] + _stocks[lastIndex];
}

double BoundaryConditionCall::lowerCondition(
    const boost::numeric::ublas::vector<double>& rightHandSide) const
{
    return 0.0;
}


/******************************************************************************
 * virtual functions.
 ******************************************************************************/
