#pragma once

#include "FiniteDifferenceScheme.h"
#include "StepCondition.h"


class FiniteDifference
{
public:
    /**************************************************************************
     * Constructers and Destructers.
     **************************************************************************/
    FiniteDifference(
        const boost::numeric::ublas::vector<double>& stocks,
        const std::size_t numberOfTimeSteps);
    virtual ~FiniteDifference();

    /**************************************************************************
     * member functions.
     **************************************************************************/
    boost::numeric::ublas::vector<double> doScheme(
        const boost::shared_ptr<const FiniteDifferenceScheme> scheme,
        const boost::shared_ptr<const StepCondition> stepCondition,
        boost::numeric::ublas::vector<double>& rightHandSide) const;

private:
    const boost::numeric::ublas::vector<double> _stocks;
    const std::size_t _numberOfTimeSteps;
            
};


