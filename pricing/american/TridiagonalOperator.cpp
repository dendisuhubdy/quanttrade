#include "TridiagonalOperator.h"

/******************************************************************************
 * Constructers and Destructers.
 ******************************************************************************/
TridiagonalOperator::TridiagonalOperator(
    const boost::numeric::ublas::vector<double>& upperDiagonal,
    const boost::numeric::ublas::vector<double>& middleDiagonal,
    const boost::numeric::ublas::vector<double>& lowerDiagonal)
    :
    _upperDiagonal(upperDiagonal),
    _middleDiagonal(middleDiagonal),
    _lowerDiagonal(lowerDiagonal)
{

}

TridiagonalOperator::TridiagonalOperator(
    const double upperValue,
    const double middleValue,
    const double lowerValue,
    const std::size_t rowLength,
    const boost::shared_ptr<const BoundaryCondition>& boundaryCondition)
    :
    _upperDiagonal(rowLength, upperValue),
    _middleDiagonal(rowLength, middleValue),
    _lowerDiagonal(rowLength, lowerValue)
{
    boundaryCondition->operatorCondition(*this);
}

TridiagonalOperator::~TridiagonalOperator()
{
}

/******************************************************************************
 * member functions.
 ******************************************************************************/
void TridiagonalOperator::solve(
    boost::numeric::ublas::vector<double>& rightHandSide,
    boost::numeric::ublas::vector<double>& results) const
{
    boost::numeric::ublas::vector<double> transformedVariable1(_middleDiagonal.size());
    boost::numeric::ublas::vector<double> transformedVariable2(_middleDiagonal.size());

    calculateTransformedVariables(rightHandSide, transformedVariable1, transformedVariable2);

    substituteTransFormedVariables(results, transformedVariable1, transformedVariable2);
}

void TridiagonalOperator::setFirstRow(const double middle, const double upper)
{
    const std::size_t lastIndex = _middleDiagonal.size() - 1;

    _middleDiagonal[lastIndex] = middle;
    _upperDiagonal[lastIndex] = upper;
}

void TridiagonalOperator::setEndRow(const double lower, const double middle)
{
    _middleDiagonal[0] = middle;
    _lowerDiagonal[0] = lower;
}

/******************************************************************************
 * private functions.
 ******************************************************************************/
void TridiagonalOperator::calculateTransformedVariables(
    const boost::numeric::ublas::vector<double>& rightHandSide,
    boost::numeric::ublas::vector<double>& transformedVariable1,
    boost::numeric::ublas::vector<double>& transformedVariable2) const
{
    transformedVariable1[0] = _middleDiagonal[0];
    transformedVariable2[0] = rightHandSide[0];

    for (std::size_t rowIndex = 1; rowIndex < _middleDiagonal.size(); ++rowIndex) {
        transformedVariable1[rowIndex] = _middleDiagonal[rowIndex]
            - _lowerDiagonal[rowIndex - 1] * _upperDiagonal[rowIndex]
                / transformedVariable1[rowIndex - 1];
        transformedVariable2[rowIndex] = rightHandSide[rowIndex]
            - _upperDiagonal[rowIndex] * transformedVariable2[rowIndex - 1]
                / transformedVariable1[rowIndex - 1];
        //std::cout << "temp2:" << transformedVariable2[rowIndex] << std::endl;
    }
}

void TridiagonalOperator::substituteTransFormedVariables(
    boost::numeric::ublas::vector<double>& results,
    const boost::numeric::ublas::vector<double>& transformedVariable1,
    const boost::numeric::ublas::vector<double>& transformedVariable2) const
{
    const std::size_t lastIndex = _middleDiagonal.size() - 1;
    results[lastIndex] =
        (transformedVariable2[lastIndex])
            / transformedVariable1[lastIndex];

    for (std::size_t rowIndex = _middleDiagonal.size() - 2; rowIndex > 0; --rowIndex) {
        results[rowIndex] =
            (transformedVariable2[rowIndex] - _lowerDiagonal[rowIndex] * results[rowIndex + 1])
            / transformedVariable1[rowIndex];
    }


}
