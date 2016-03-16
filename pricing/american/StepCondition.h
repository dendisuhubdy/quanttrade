#pragma once

#include <boost/numeric/ublas/vector.hpp>

class StepCondition 
{
public:
    /**************************************************************************
     * Constructers and Destructers.
     **************************************************************************/
    StepCondition();
    virtual ~StepCondition();

    /**************************************************************************
     * inherited pure virtual functions.
     **************************************************************************/
    virtual void applyAfterBackward(
        boost::numeric::ublas::vector<double>& previousStep) const = 0;

private:
            
};

