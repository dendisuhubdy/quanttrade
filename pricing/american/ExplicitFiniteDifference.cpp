#include "ExplicitFiniteDifference.h"

#include <boost/numeric/ublas/io.hpp>

/******************************************************************************
 * Constructers and Destructers.
 ******************************************************************************/
ExplicitFiniteDifference::ExplicitFiniteDifference(
    const double upperValue,
    const double middleValue,
    const double lowerValue,
    const std::size_t dimension,
    const boost::shared_ptr<const BoundaryCondition>& boundaryCondition)
    :
    _upperValue(upperValue),
    _middleValue(middleValue),
    _lowerValue(lowerValue),
    _boundaryCondition(boundaryCondition),
    _tridiagonalOperator(0.0, 1.0, 0.0, dimension, boundaryCondition)
{
}

ExplicitFiniteDifference::~ExplicitFiniteDifference() 
{
}

/******************************************************************************
 * inherited pure virtual functions.
 ******************************************************************************/
void ExplicitFiniteDifference::doBackward(
    boost::numeric::ublas::vector<double>& rightHandSide,
    boost::numeric::ublas::vector<double>& results) const
{
    boost::numeric::ublas::vector<double> workingCopy(rightHandSide);

    //before solve
    for (std::size_t rowIndex = 1; rowIndex < rightHandSide.size() - 1; ++rowIndex) {
        rightHandSide[rowIndex] = workingCopy[rowIndex + 1] * _lowerValue 
            + workingCopy[rowIndex] * _middleValue 
            + workingCopy[rowIndex - 1] * _upperValue;
    }
    const double lastIndex = rightHandSide.size() - 1;
    rightHandSide[lastIndex] = _boundaryCondition->upperCondition(rightHandSide);
    rightHandSide[0] = _boundaryCondition->lowerCondition(rightHandSide);

    //solve
    _tridiagonalOperator.solve(rightHandSide, results);

}

