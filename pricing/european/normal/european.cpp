/*************************************************************************
	> File Name: europeanoption.cpp
	> Author: Dendi Suhubdy and Prof Tao Pang
	> Mail: dasuhubd@ncsu.edu
	> Created Time: Tue 02 Feb 2016 10:46:42 PM EST
 ************************************************************************/

 #include <iostream>
 #include <cmath>
 #include <algorithm>
 #include <vector>
 #include <boost/math/distributions/normal.hpp>

#include "european.h"

using namespace std;
using boost::math::normal;

european::european(double volatility, double curr_price, double strike_price, double maturity, double int_rates)
{
    this->p_steps = 100;
    this->p_volatility = volatility;
    this->p_curr_price = curr_price;
    this->p_strike_price = strike_price;
    this->p_maturity = maturity;
    this->p_int_rates = int_rates;
}

double european::price_binomial()
{
    double R = exp(p_int_rates*(p_maturity/p_steps));
    double rinv = 1.0/R;
    double u = exp(p_volatility*sqrt(p_maturity/p_steps));
    double uu = u*u;
    double d = 1.0/u;
    double p_up = (R-d)/(u-d);
    double p_down = 1.0 - p_up;
    vector<double> prices(p_steps + 1);
    prices[0] = p_curr_price*pow(d, p_steps);
    for (int i =0; i<= p_steps; ++i) {
        prices[i] = uu*prices[i-1];
    }
    vector<double> call_values(p_steps+1);
    for (int i = 0; i<= p_steps; ++i) {
        call_values[i] = max(0.0, (prices[i] - p_strike_price));
    }
    for (int p_steps = p_steps - 1; p_steps >= 0; --p_steps) {
        for (int i = 0; i<= p_steps; ++i) {
            call_values[i] = (p_up*call_values[i+1]+p_down*call_values[i]*rinv);
        }
    }

    return call_values[0];
}

double european::price_blackscholes()
{
    double d1 = (log(p_curr_price/p_strike_price) + (p_int_rates + (p_volatility*p_volatility)/2)*p_maturity)/(p_volatility*sqrt(p_maturity));
    double d2 = d1 - p_volatility*sqrt(p_maturity);
    normal N;
    double  result = p_curr_price*cdf(N, d1) - cdf(N, d2)*p_curr_price*exp(-p_int_rates*p_maturity);
    return result;
}
