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
    option();
    ~option();
    T price(T vol, T cur_price, T strike_price, T maturity, T int_rates);
protected:
    T volatility;
    T current_price;
    T strike_price;
    T maturity;
    T int_rates;
};

#endif
