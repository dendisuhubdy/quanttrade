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

#include "option.h"
#include "european.h"

using namespace std;
using boost::math::normal;

template<class T>
european<T>::european(T volatility, T curr_price, T strike_price, T maturity, T int_rates)
{
    this->p_steps = 1000;
    this->p_volatility = volatility;
    this->p_curr_price = curr_price;
    this->p_strike_price = strike_price;
    this->p_maturity = maturity;
    this->p_int_rates = int_rates;
}

template<class T>
T european<T>::price_binomial()
{
    T R = epx(p_int_rates*(p_maturity/p_steps));
    T rinv = 1.0/R;
    T u = exp(p_volatility*sqrt(p_maturity/p_steps));
    T uu = u*u;
    T d = 1.0/u;
    T p_up = (R-d)/(u-d);
    T p_down = 1.0 - p_up;
    vector<T> prices(p_steps + 1); 
    prices[0] = p_curr_price*pow(d, p_steps);
    for (int i =0; i<= p_steps; ++i) {
        prices[i] = uu*prices[i-1];
    }
    vector<T> call_values(p_steps+1);
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

template<class T>
T european<T>::price_blackscholes()
{
    T d1 = (log(p_curr_price/p_strike_price) + (p_int_rates + (p_volatility*p_volatility)/2)*p_maturity)/(p_volatility*sqrt(p_maturity));
    T d2 = d1 - p_volatility*sqrt(p_maturity);
    normal N;
    T  result = p_curr_price*cdf(N, d1) - cdf(N, d2)*p_curr_price*exp(-p_int_rates*p_maturity);
    return result;
}

template<class T>
T european<T>::price_fdm()
{
    
}

