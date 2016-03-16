#pragma once

class Calculator 
{
public:
    /**************************************************************************
     * Constructers and Destructers.
     **************************************************************************/
    Calculator();
    virtual ~Calculator();

    /**************************************************************************
     * pure virtual functions.
     **************************************************************************/
    virtual double calculateUpperValue() const = 0;
    virtual double calculateMiddleValue() const = 0;
    virtual double calculateLowerValue() const = 0;
    
private:
            
};

