#pragma once

#include "StepCondition.h"

class StepConditionNull 
    : public StepCondition
{
public:
    /**************************************************************************
     * Constructers and Destructers.
     **************************************************************************/
    StepConditionNull();
    virtual ~StepConditionNull();

    /**************************************************************************
     * inherited pure virtual functions.
     **************************************************************************/
    virtual void applyAfterBackward(
        boost::numeric::ublas::vector<double>& previousStep) const;
private:
};

