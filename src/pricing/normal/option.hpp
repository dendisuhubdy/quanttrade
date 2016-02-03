/*************************************************************************
	> File Name: option.h
	> Author: Dendi Suhubdy 
	> Mail: dasuhubd@ncsu.edu
	> Created Time: Tue 02 Feb 2016 10:22:20 PM EST
 ************************************************************************/

#ifndef _OPTION_H 
#define _OPTION_H

template<class T>
class option{
public:
    option(T volatility, T curr_price, T strike_price, T maturity, T int_rates);
    ~option();
    T price();
protected:
    T volatility;
    T current_price;
    T strike_price;
    T maturity;
    T int_rates;
};

#endif
