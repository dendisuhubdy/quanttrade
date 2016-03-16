#include "StepConditionAmerican.h"

/******************************************************************************
 * Constructers and Destructers.
 ******************************************************************************/
StepConditionAmerican::StepConditionAmerican(
    const boost::numeric::ublas::vector<double>& stocks,
    const boost::shared_ptr<const PayOff>& payOff)
    :
    _stocks(stocks),
    _payOff(payOff)
{
    
}
StepConditionAmerican::~StepConditionAmerican() 
{
}

/******************************************************************************
 * inherited pure virtual functions.
 ******************************************************************************/
void StepConditionAmerican::applyAfterBackward(
    boost::numeric::ublas::vector<double>& previousStep) const
{
    for (std::size_t dimensionIndex = 0; dimensionIndex < previousStep.size(); 
        ++dimensionIndex) {
        
        previousStep[dimensionIndex] = 
            std::max(previousStep[dimensionIndex], 
                _payOff->operator()(_stocks[dimensionIndex]));
    }
}
