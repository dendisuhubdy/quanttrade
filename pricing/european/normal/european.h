/*************************************************************************
	> File Name: europeanoptin.h
	> Author:
	> Mail:
	> Created Time: Tue 02 Feb 2016 10:47:15 PM EST
 ************************************************************************/
 #ifndef _EUROPEAN_H
 #define _EUROPEAN_H

 #include <iostream>
 #include <cmath>
 #include <algorithm>
 #include <vector>
 #include <boost/math/distributions/normal.hpp>

class european{
public:
    european(double volatility, double curr_price, double strike_price, double maturity, double int_rates);
    double price_binomial();
    double price_blackscholes();
private:
    double p_volatility;
    double p_curr_price;
    double p_strike_price;
    double p_maturity;
    double p_int_rates;
    unsigned int p_steps;
};

#endif
