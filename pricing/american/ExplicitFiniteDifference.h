#pragma once

#include "FiniteDifferenceScheme.h"
#include "BoundaryCondition.h"
#include "TridiagonalOperator.h"

class ExplicitFiniteDifference 
    : public FiniteDifferenceScheme
{
public:
    /**************************************************************************
     * Constructers and Destructers.
     **************************************************************************/
    ExplicitFiniteDifference(
        const double upperValue,
        const double middleValue,
        const double lowerValue,
        const std::size_t dimension,
        const boost::shared_ptr<const BoundaryCondition>& boundaryCondition);
    virtual ~ExplicitFiniteDifference();

    /**************************************************************************
     * inherited pure virtual functions.
     **************************************************************************/
    virtual void doBackward(
        boost::numeric::ublas::vector<double>& rightHandSide,
        boost::numeric::ublas::vector<double>& results) const;
private:
    const double _upperValue;
    const double _middleValue;
    const double _lowerValue;
    const boost::shared_ptr<const BoundaryCondition> _boundaryCondition;
    const TridiagonalOperator _tridiagonalOperator;

            
};

