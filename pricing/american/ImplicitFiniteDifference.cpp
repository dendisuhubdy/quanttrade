#include "ImplicitFiniteDifference.h"

#include <boost/numeric/ublas/io.hpp>

/******************************************************************************
 * Constructers and Destructers.
 ******************************************************************************/
ImplicitFiniteDifference::ImplicitFiniteDifference(
    const double upperValue,
    const double middleValue,
    const double lowerValue,
    const std::size_t dimension,
    const boost::shared_ptr<const BoundaryCondition>& boundaryCondition)
    :
    _boundaryCondition(boundaryCondition),
    _tridiagonalOperator(upperValue, middleValue, lowerValue, 
        dimension, boundaryCondition)
{
    
}
ImplicitFiniteDifference::~ImplicitFiniteDifference() 
{
}


/******************************************************************************
 * inherited pure virtual functions.
 ******************************************************************************/
void ImplicitFiniteDifference::doBackward(
    boost::numeric::ublas::vector<double>& rightHandSide,
    boost::numeric::ublas::vector<double>& results) const
{
    const std::size_t lastIndex = rightHandSide.size() - 1;
    rightHandSide[lastIndex] = _boundaryCondition->upperCondition(rightHandSide);
    rightHandSide[0] = _boundaryCondition->lowerCondition(rightHandSide);

    _tridiagonalOperator.solve(rightHandSide, results);
}

