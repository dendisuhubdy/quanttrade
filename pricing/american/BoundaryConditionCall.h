#pragma once

#include "BoundaryConditionNeumann.h"

class BoundaryConditionCall
    : public BoundaryConditionNeumann
{
public:
    /**************************************************************************
     * Constructers and Destructers.
     **************************************************************************/
    BoundaryConditionCall(
        const boost::numeric::ublas::vector<double>& stocks);
    virtual ~BoundaryConditionCall();

    /**************************************************************************
     * inherited pure virtual functions.
     **************************************************************************/
    virtual double upperCondition( 
        const boost::numeric::ublas::vector<double>& rightHandSide) const;
    virtual double lowerCondition( 
        const boost::numeric::ublas::vector<double>& rightHandSide) const;

private:
    const boost::numeric::ublas::vector<double>& _stocks;
            
};

