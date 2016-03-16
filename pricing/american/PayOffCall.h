#pragma once

#include "PayOff.h"

class PayOffCall 
    : public PayOff
{
public:
    PayOffCall(const double strike);
    virtual ~PayOffCall();

    virtual double operator()(const double spot) const;
    
private:
    const double _strike;            
};

