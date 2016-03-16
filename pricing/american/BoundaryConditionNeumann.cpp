#include "BoundaryConditionNeumann.h"

/******************************************************************************
 * Constructers and Destructers.
 ******************************************************************************/
BoundaryConditionNeumann::BoundaryConditionNeumann()
{
    
}
BoundaryConditionNeumann::~BoundaryConditionNeumann() 
{
}

/******************************************************************************
 * virtual functions.
 ******************************************************************************/
void BoundaryConditionNeumann::operatorCondition(
    TridiagonalOperator& tridiagonalOperator) const
{
    tridiagonalOperator.setFirstRow(1.0, -1.0);
    tridiagonalOperator.setEndRow(1.0, -1.0);
}

