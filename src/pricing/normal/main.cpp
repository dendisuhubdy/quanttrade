/*************************************************************************
	> File Name: main.cpp
	> Author: Dendi Suhubdy and Prof. Tao pang
	> Mail: dasuhubd@ncsu.edu
	> Created Time: Wed Feb  3 12:50:23 2016
 ************************************************************************/

 #include <iostream>
 #include <cmath>
 #include <algorithm>
 #include <vector>
 #include <boost/math/distributions/normal.hpp>

#include "european.h"

using namespace std;

int main(void)
{
    double vol = 0.2;
    double curr_price = 1.00;
    double strike_price = 0.50;
    double maturity = 1.00;
    double int_rates = 0.05;

    european call(vol, curr_price, strike_price, maturity, int_rates);

    cout << "Call price black scholes " << call.price_blackscholes() << endl;
    cout << "Call price binomial " << call.price_binomial() << endl;

    return 0;
}
