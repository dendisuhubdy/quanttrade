#pragma once

#include "BoundaryCondition.h"
#include "TridiagonalOperator.h"

class BoundaryConditionNeumann
    : public BoundaryCondition
{
public:
    /**************************************************************************
     * Constructers and Destructers.
     **************************************************************************/
    BoundaryConditionNeumann();
    virtual ~BoundaryConditionNeumann();

    /**************************************************************************
     * inherited pure virtual functions.
     **************************************************************************/
    virtual double upperCondition( 
        const boost::numeric::ublas::vector<double>& rightHandSide) const = 0;
    virtual double lowerCondition( 
        const boost::numeric::ublas::vector<double>& rightHandSide) const = 0;
    virtual void operatorCondition(
        TridiagonalOperator& tridiagonalOperator) const;

private:
            
};

