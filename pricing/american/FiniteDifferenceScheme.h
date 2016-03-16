#pragma once

#include <boost/numeric/ublas/vector.hpp>

class FiniteDifferenceScheme 
{
public:
    /**************************************************************************
     * Constructers and Destructers.
     **************************************************************************/
    FiniteDifferenceScheme();
    virtual ~FiniteDifferenceScheme();

    /**************************************************************************
     * pure virtual functions.
     **************************************************************************/
    virtual void doBackward(
        boost::numeric::ublas::vector<double>& rightHandSide,
        boost::numeric::ublas::vector<double>& results) const = 0;
private:
            
};

