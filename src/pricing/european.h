/*************************************************************************
	> File Name: europeanoptin.h
	> Author: 
	> Mail: 
	> Created Time: Tue 02 Feb 2016 10:47:15 PM EST
 ************************************************************************/

#ifndef _EUROPEANOPTION_H
#define _EUROPEANOPTION_H

#include "option.h"

template<class T>
class european :public option<T> {
public:
    european(T volatility, T curr_price, T strike_price, T maturity, T int_rates);
    ~european();
    price_fdm();
    price_binomial();
    price_blackscholes();
private:
    T p_volatility;
    T p_curr_price;
    T p_strike_price;
    T p_maturity;
    T p_int_rates;
    unsigned int p_steps;
};

#endif
