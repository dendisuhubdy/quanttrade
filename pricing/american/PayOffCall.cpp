#include "PayOffCall.h"

PayOffCall::PayOffCall(const double strike) 
    :
    _strike(strike)
{
    
}
PayOffCall::~PayOffCall() 
{
}

double PayOffCall::operator()(const double spot) const
{
    return std::max(0.0, spot - _strike);
}
