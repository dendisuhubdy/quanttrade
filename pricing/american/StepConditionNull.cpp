#include "StepConditionNull.h"

/******************************************************************************
 * Constructers and Destructers.
 ******************************************************************************/
StepConditionNull::StepConditionNull() 
{
}

StepConditionNull::~StepConditionNull() 
{
}

/******************************************************************************
 * inherited pure virtual functions.
 ******************************************************************************/
void StepConditionNull::applyAfterBackward(
    boost::numeric::ublas::vector<double>& previousStep) const
{
}
