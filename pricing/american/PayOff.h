#pragma once

#include <boost/numeric/ublas/vector.hpp>

class PayOff 
{
public:
    /**************************************************************************
     * Constructers and Destructers
     **************************************************************************/
    PayOff();
    virtual ~PayOff();

    /**************************************************************************
     * pure virtual functions.
     **************************************************************************/
    virtual double operator()(const double spot) const = 0;

private:
            
};

