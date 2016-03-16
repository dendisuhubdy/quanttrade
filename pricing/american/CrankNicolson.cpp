#include "CrankNicolson.h"

#include <boost/numeric/ublas/io.hpp>

/******************************************************************************
 * Constructers and Destructers.
 ******************************************************************************/
CrankNicolson::CrankNicolson(
    const double upperValue,
    const double middleValue,
    const double lowerValue,
    const std::size_t dimension,
    const boost::shared_ptr<const BoundaryCondition>& boundaryCondition)
    :
    _upperValue(upperValue),
    _middleValue(middleValue),
    _lowerValue(lowerValue),
    _boundaryCondtion(boundaryCondition),
    _tridiagonalOperator(lowerValue, middleValue, upperValue, 
        dimension, boundaryCondition)
{
}

CrankNicolson::~CrankNicolson() 
{
}

/******************************************************************************
 * inherited pure virtual functions.
 ******************************************************************************/
void CrankNicolson::doBackward(
    boost::numeric::ublas::vector<double>& rightHandSide,
    boost::numeric::ublas::vector<double>& results) const
{
    boost::numeric::ublas::vector<double> workingCopy(rightHandSide);

    //berfore solve
    for (std::size_t rowIndex = 1; rowIndex < rightHandSide.size() - 1; ++rowIndex) {
        rightHandSide[rowIndex] = 
            - workingCopy[rowIndex + 1] * _lowerValue 
            - workingCopy[rowIndex] * (_middleValue - 2.0)
            - workingCopy[rowIndex - 1] * _upperValue;
    }
    const std::size_t lastIndex = workingCopy.size() - 1;
    rightHandSide[lastIndex] = _boundaryCondtion->upperCondition(rightHandSide);
    rightHandSide[0] = _boundaryCondtion->lowerCondition(rightHandSide);
    //std::cout << "afterBdd:" << rightHandSide << std::endl;
    

    //solve
    _tridiagonalOperator.solve(rightHandSide, results);

    //after solve
}

