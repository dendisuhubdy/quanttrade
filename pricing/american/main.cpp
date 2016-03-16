#include "PayOffCall.h"
#include "PayOffPut.h"
#include "CalculatorExplicit.h"
#include "CalculatorImplicit.h"
#include "CalculatorCrankNicolson.h"
#include "BoundaryConditionCall.h"
#include "BoundaryConditionPut.h"
#include "ExplicitFiniteDifference.h"
#include "ImplicitFiniteDifference.h"
#include "CrankNicolson.h"
#include "FiniteDifference.h"
#include "StepConditionNull.h"
#include "StepConditionAmerican.h"

#include <boost/shared_ptr.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <iostream>

void initializeStocks(
    boost::numeric::ublas::vector<double>& stocks,
    const double spot,
    const double spaceStepSize,
    const std::size_t numberOfTimeSteps)
{
    const std::size_t gridSize = 2 * numberOfTimeSteps + 1;
    for (std::size_t rowIndex = 0; rowIndex < gridSize; ++rowIndex) {
        stocks[rowIndex] = spot * exp(
            static_cast<int>(rowIndex - numberOfTimeSteps) * spaceStepSize);
    }
}

void initializeRightHandSide(
    boost::numeric::ublas::vector<double>& rightHandSide,
    const boost::numeric::ublas::vector<double>& stocks,
    const boost::shared_ptr<const PayOff>& payOff)
{
    for (std::size_t rowIndex = 0; rowIndex < rightHandSide.size(); ++rowIndex) {
        rightHandSide[rowIndex] = payOff->operator()(stocks[rowIndex]);
    }
}

double time_european_fdm()
{
    //std::cout << "**********************************************************************" << std::endl
    //          << "* European Call Option by Explicit Finite Difference." << std::endl
    //          << "**********************************************************************" << std::endl;
    
    //parameters
    const double strike = 100.0;
    const double maturity = 1.0;
    const double spot = 100.0;
    const double volatility = 0.2;
    const double interestRate = 0.06;
    const double dividend = 0.03;
    const std::size_t numberOfTimeSteps = 3;
    const double spaceStepSize = 0.2;
    
    clock_t startTime = clock();
    //precomputing variables
    const std::size_t gridSize = 2 * numberOfTimeSteps + 1;
    boost::numeric::ublas::vector<double> stocks(gridSize);
    initializeStocks(stocks, spot, spaceStepSize, numberOfTimeSteps);
    const CalculatorExplicit calculator(strike, maturity, volatility, 
        interestRate, dividend, numberOfTimeSteps, spaceStepSize);
    const double upperValue = calculator.calculateUpperValue();
    const double middleValue = calculator.calculateMiddleValue();
    const double lowerValue = calculator.calculateLowerValue();

    //payoff
    const boost::shared_ptr<const PayOff> payOff(new PayOffCall(strike));

    //initial value
    boost::numeric::ublas::vector<double> rightHandSide(gridSize);
    initializeRightHandSide(rightHandSide, stocks, payOff);

    //boundary condition
   const boost::shared_ptr<const BoundaryCondition> boundaryConditionCall(
       new BoundaryConditionCall(stocks));

   //Finite difference scheme
   const boost::shared_ptr<const FiniteDifferenceScheme> scheme(
       new ExplicitFiniteDifference(upperValue, middleValue, lowerValue,
            gridSize, boundaryConditionCall));

   //step condition
   const boost::shared_ptr<const StepCondition> stepCondition(
       new StepConditionNull());

   //making finite difference
   FiniteDifference finiteDifference(stocks, numberOfTimeSteps);
   
   //calculate price
   boost::numeric::ublas::vector<double> results = 
       finiteDifference.doScheme(scheme, stepCondition, rightHandSide);
   //std::cout << "the European option costs " 
   //          << double( clock() - startTime ) / (double)CLOCKS_PER_SEC<< " seconds." << std::endl;

   //std::cout << "result" << results << std::endl;
   //std::cout << std::endl;
   return double( clock() - startTime ) / (double)CLOCKS_PER_SEC;

}

double time_american_explicit()
{

    //std::cout << "**********************************************************************" << std::endl
    //          << "* American Put Option by Explicit Finite Difference." << std::endl
    //          << "**********************************************************************" << std::endl;
    /**********************************************************************
     * American Put Option by Explicit Finite Difference. Figure3.9.
     **********************************************************************/
    //parameters
    const double strike = 100.0;
    const double maturity = 1.0;
    const double spot = 100.0;
    const double volatility = 0.2;
    const double interestRate = 0.06;
    const double dividend = 0.03;
    const std::size_t numberOfTimeSteps = 3;
    const double spaceStepSize = 0.2;

    clock_t startTime = clock();
    //precomputing variables
    const std::size_t gridSize = 2 * numberOfTimeSteps + 1;
    boost::numeric::ublas::vector<double> stocks(gridSize);
    initializeStocks(stocks, spot, spaceStepSize, numberOfTimeSteps);
    const CalculatorExplicit calculator(strike, maturity, volatility, 
        interestRate, dividend, numberOfTimeSteps, spaceStepSize);
    const double upperValue = calculator.calculateUpperValue();
    const double middleValue = calculator.calculateMiddleValue();
    const double lowerValue = calculator.calculateLowerValue();

    //payoff
    const boost::shared_ptr<const PayOff> payOff(new PayOffPut(strike));

    //initial value
    boost::numeric::ublas::vector<double> rightHandSide(gridSize);
    initializeRightHandSide(rightHandSide, stocks, payOff);

    //boundary condition
   const boost::shared_ptr<const BoundaryCondition> boundaryCondition(
       new BoundaryConditionPut(stocks));

   //Finite difference scheme
   const boost::shared_ptr<const FiniteDifferenceScheme> scheme(
       new ExplicitFiniteDifference(upperValue, middleValue, lowerValue,
            gridSize, boundaryCondition));

   //step condition
   const boost::shared_ptr<const StepCondition> stepCondition(
       new StepConditionAmerican(stocks, payOff));

   //making finite difference
   FiniteDifference finiteDifference(stocks, numberOfTimeSteps);
   //calculate price
   boost::numeric::ublas::vector<double> results = 
       finiteDifference.doScheme(
           scheme, stepCondition, rightHandSide);
   //std::cout << "the American put option with the Explicit FDM method costs" 
   //     << double( clock() - startTime ) / (double)CLOCKS_PER_SEC<< " seconds." << std::endl;

   //std::cout << "result" << results << std::endl;

   //std::cout << std::endl;
   return double( clock() - startTime ) / (double)CLOCKS_PER_SEC;

}

double time_american_implicit()
{
    //std::cout << "**********************************************************************" << std::endl
    //          << "* American Put Option by Implicit Finite Difference." << std::endl
    //          << "**********************************************************************" << std::endl;
    /**********************************************************************
     * American Put Option by Implicit Finite Difference. Figure3.13.
     **********************************************************************/
    //parameters
    const double strike = 100.0;
    const double maturity = 1.0;
    const double spot = 100.0;
    const double volatility = 0.2;
    const double interestRate = 0.06;
    const double dividend = 0.03;
    const std::size_t numberOfTimeSteps = 3;
    const double spaceStepSize = 0.2;

    //precomputing variables
    const std::size_t gridSize = 2 * numberOfTimeSteps + 1;
    boost::numeric::ublas::vector<double> stocks(gridSize);
    initializeStocks(stocks, spot, spaceStepSize, numberOfTimeSteps);
    const CalculatorImplicit calculator(strike, maturity, volatility, 
        interestRate, dividend, numberOfTimeSteps, spaceStepSize);
    const double upperValue = calculator.calculateUpperValue();
    const double middleValue = calculator.calculateMiddleValue();
    const double lowerValue = calculator.calculateLowerValue();

    //payoff
    const boost::shared_ptr<const PayOff> payOff(new PayOffPut(strike));

    //initial value
    boost::numeric::ublas::vector<double> rightHandSide(gridSize);
    initializeRightHandSide(rightHandSide, stocks, payOff);

    //boundary condition
   const boost::shared_ptr<const BoundaryCondition> boundaryCondition(
       new BoundaryConditionPut(stocks));

   //Finite difference scheme
   const boost::shared_ptr<const FiniteDifferenceScheme> scheme(
       new ImplicitFiniteDifference(upperValue, middleValue, lowerValue,
            gridSize, boundaryCondition));

   //step condition
   const boost::shared_ptr<const StepCondition> stepCondition(
       new StepConditionAmerican(stocks, payOff));

   //making finite difference
   FiniteDifference finiteDifference(stocks, numberOfTimeSteps);
   clock_t startTime = clock();
   //calculate price
   boost::numeric::ublas::vector<double> results = 
       finiteDifference.doScheme(
           scheme, stepCondition, rightHandSide);
   //std::cout << "the American put option with an implicit FDM method costs " 
   //          << double( clock() - startTime ) / (double)CLOCKS_PER_SEC<< " seconds." << std::endl;

   //std::cout << "result" << results << std::endl;
   //std::cout << std::endl;
   return double( clock() - startTime ) / (double)CLOCKS_PER_SEC;

}
double time_american_CN()
{
    /*
    std::cout << "**********************************************************************" << std::endl
              << "* American Put Option by Crank-Nicolson." << std::endl
              << "**********************************************************************" << std::endl;
    */
    /**********************************************************************
     * American Put Option by Crank-Nicolson. Figure3.16.
     **********************************************************************/
    
    //parameters
    const double strike = 100.0;
    const double maturity = 1.0;
    const double spot = 100.0;
    const double volatility = 0.2;
    const double interestRate = 0.06;
    const double dividend = 0.03;
    const std::size_t numberOfTimeSteps = 3;
    const double spaceStepSize = 0.2;

    
    clock_t startTime = clock();
    //precomputing variables
    const std::size_t gridSize = 2 * numberOfTimeSteps + 1;
    boost::numeric::ublas::vector<double> stocks(gridSize);
    initializeStocks(stocks, spot, spaceStepSize, numberOfTimeSteps);
    const CalculatorCrankNicolson calculator(strike, maturity, volatility, 
        interestRate, dividend, numberOfTimeSteps, spaceStepSize);
    const double upperValue = calculator.calculateUpperValue();
    const double middleValue = calculator.calculateMiddleValue();
    const double lowerValue = calculator.calculateLowerValue();

    //std::cout << upperValue << std::endl;
    //std::cout << middleValue << std::endl;
    //std::cout << lowerValue << std::endl;


    //payoff
    const boost::shared_ptr<const PayOff> payOff(new PayOffPut(strike));

    //initial value
    boost::numeric::ublas::vector<double> rightHandSide(gridSize);
    initializeRightHandSide(rightHandSide, stocks, payOff);

    //boundary condition
   const boost::shared_ptr<const BoundaryCondition> boundaryCondition(
       new BoundaryConditionPut(stocks));

   //Finite difference scheme
   const boost::shared_ptr<const FiniteDifferenceScheme> scheme(
       new CrankNicolson(upperValue, middleValue, lowerValue,
            gridSize, boundaryCondition));

   //step condition
   const boost::shared_ptr<const StepCondition> stepCondition(
       new StepConditionAmerican(stocks, payOff));

   //making finite difference
   FiniteDifference finiteDifference(stocks, numberOfTimeSteps);
   
   //calculate price
   boost::numeric::ublas::vector<double> results = 
       finiteDifference.doScheme(
           scheme, stepCondition, rightHandSide);
   //std::cout << "The American put option with Crank-Nicolson costs "
   //          << double( clock() - startTime ) / (double)CLOCKS_PER_SEC<< " seconds." << std::endl;

   //std::cout << "result" << results << std::endl;
   return double(clock() - startTime ) / (double)CLOCKS_PER_SEC;
}

int main(int argc, char const* argv[])
{
    const int counter = 50;
    double sum = 0;
    for (int i = 0; i <= counter; i++)
    {
        sum += time_european_fdm();
    }

    std::cout << "average timing for European option calculation is " << sum/counter << std::endl;

    sum = 0;
    for (int i = 0; i <= counter; i++)
    {
        sum += time_american_explicit();
    }

    std::cout << "average timing for American put option Explicit method calculation is " << sum/counter << std::endl;
    
    sum = 0;
    for (int i = 0; i <= counter; i++)
    {
        sum += time_american_implicit();
    }

    std::cout << "average timing for American put Implicit method  calculation is " << sum/counter << std::endl;
    
    sum = 0;
    for (int i = 0; i <= counter; i++)
    {
        sum += time_american_CN();
    }

    std::cout << "average timing for American put option CN method calculation is " << sum/counter << std::endl;

    return 0;
}
