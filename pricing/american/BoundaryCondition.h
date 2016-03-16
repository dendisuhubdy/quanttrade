#pragma once

class TridiagonalOperator;

#include "TridiagonalOperator.h"

#include <boost/numeric/ublas/vector.hpp>

class BoundaryCondition
{
public:
    /**************************************************************************
     * Constructers and Destructers.
     **************************************************************************/
    BoundaryCondition();
    virtual ~BoundaryCondition();

    /**************************************************************************
     * pure virtual functions.
     **************************************************************************/
    virtual double upperCondition( 
        const boost::numeric::ublas::vector<double>& rightHandSide) const = 0;
    virtual double lowerCondition( 
        const boost::numeric::ublas::vector<double>& rightHandSide) const = 0;
    virtual void operatorCondition(TridiagonalOperator& tridiagonalOperator) const = 0;

private:
            
};

