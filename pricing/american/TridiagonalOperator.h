#pragma once

class BoundaryCondition;

#include "BoundaryCondition.h"

#include <boost/numeric/ublas/vector.hpp>
#include <boost/shared_ptr.hpp>

class TridiagonalOperator 
{
public:
    /**************************************************************************
     * Constructers and Destructers.
     **************************************************************************/
    TridiagonalOperator(
        const boost::numeric::ublas::vector<double>& upperDiagonal,
        const boost::numeric::ublas::vector<double>& middleDiagonal,
        const boost::numeric::ublas::vector<double>& lowerDiagonal);
    TridiagonalOperator(
        const double upperValue,
        const double middleValue,
        const double lowerValue,
        const std::size_t rowLength,
        const boost::shared_ptr<const BoundaryCondition>& boundaryCondiion);
    virtual ~TridiagonalOperator();

    /**************************************************************************
     * member functions.
     **************************************************************************/
    void solve(
        boost::numeric::ublas::vector<double>& rightHandSide,
        boost::numeric::ublas::vector<double>& results) const;
    void setFirstRow(const double middle, const double upper);
    void setEndRow(const double lower, const double middle);
        
private:
    /**************************************************************************
     * private variables.
     **************************************************************************/   
    boost::numeric::ublas::vector<double> _upperDiagonal;
    boost::numeric::ublas::vector<double> _middleDiagonal;
    boost::numeric::ublas::vector<double> _lowerDiagonal;

    /**************************************************************************
     * pure virtual functions.
     **************************************************************************/
    void calculateTransformedVariables(
        const boost::numeric::ublas::vector<double>& rightHandSide,
        boost::numeric::ublas::vector<double>& transformedVariable1,
        boost::numeric::ublas::vector<double>& transformedVariable2) const;
    void substituteTransFormedVariables(
        boost::numeric::ublas::vector<double>& results,
        const boost::numeric::ublas::vector<double>& transformedVariable1,
        const boost::numeric::ublas::vector<double>& transformedVariable2) const;
};

