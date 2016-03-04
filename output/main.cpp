/*************************************************************************
	> File Name: main.cpp
	> Author: Dendi Suhubdy and Prof. Tao pang 
	> Mail: dasuhubd@ncsu.edu
	> Created Time: Wed Feb  3 12:50:23 2016
 ************************************************************************/

#include <iostream>

//todo:  use absolute paths not relative paths, think python
#include "../pricing/european/normal/european.h"
#include "../pricing/european/fdm/option.h"

int main()
{
    double vol = 0.2;
    double curr_price = 100.00;
    double strike_price = 120.00;
    double maturity = 2.00;
    double int_rates = 0.05;
 
	european *call = new european(vol, curr_price, strike_price, maturity, int_rates);
    
    std::cout << "Call price black scholes " << call->price_blackscholes() << std::endl;
    std::cout << "Call price binomial " << call->price_binomial() << std::endl;

	delete call;

    return 0;
}
