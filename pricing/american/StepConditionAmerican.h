#pragma once

#include "PayOff.h"
#include "StepCondition.h"

#include <boost/shared_ptr.hpp>

class StepConditionAmerican 
    : public StepCondition
{
public:
    /**************************************************************************
     * Constructers and Destructers.
     **************************************************************************/
    StepConditionAmerican(
        const boost::numeric::ublas::vector<double>& stocks,
        const boost::shared_ptr<const PayOff>& payOff);
    virtual ~StepConditionAmerican();

    /**************************************************************************
     * inherited pure virtual functions.
     **************************************************************************/
    virtual void applyAfterBackward(
        boost::numeric::ublas::vector<double>& previousStep) const;
private:
    const boost::numeric::ublas::vector<double> _stocks;
    const boost::shared_ptr<const PayOff> _payOff;
};

