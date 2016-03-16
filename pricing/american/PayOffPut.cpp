#include "PayOffPut.h"

PayOffPut::PayOffPut(const double strike) 
    :
    _strike(strike)
{
    
}
PayOffPut::~PayOffPut() 
{
}

double PayOffPut::operator()(const double spot) const
{
    return std::max(0.0, _strike - spot);
}
