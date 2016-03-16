#include "BoundaryConditionPut.h"

/******************************************************************************
 * Constructers and Destructers.
 ******************************************************************************/
BoundaryConditionPut::BoundaryConditionPut(
    const boost::numeric::ublas::vector<double>& stocks)
    :
    _stocks(stocks)
{
    
}
BoundaryConditionPut::~BoundaryConditionPut() 
{
}

/******************************************************************************
 * inherited pure virtual functions.
 ******************************************************************************/
double BoundaryConditionPut::upperCondition(
    const boost::numeric::ublas::vector<double>& rightHandSide) const
{
    return 0.0;
}

double BoundaryConditionPut::lowerCondition(
    const boost::numeric::ublas::vector<double>& rightHandSide) const
{
    return - _stocks[1] + _stocks[0];
}

