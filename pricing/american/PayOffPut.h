#pragma once

#include "PayOff.h"

class PayOffPut 
    : public PayOff
{
public:
    PayOffPut(const double strike);
    virtual ~PayOffPut();

    virtual double operator()(const double spot) const;
    
private:
    const double _strike;            
};

