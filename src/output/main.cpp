/*************************************************************************
	> File Name: main.cpp
	> Author: Dendi Suhubdy and Prof. Tao pang 
	> Mail: dasuhubd@ncsu.edu
	> Created Time: Wed Feb  3 12:50:23 2016
 ************************************************************************/

#include <iostream>

#include "../pricing/european.h"
#include "../pricing/option.h"

using namespace std;

int main()
{
    double vol = 0.2;
    double curr_price = 100.00;
    double strike_price = 120.00;
    double maturity = 2.00;
    double int_rates = 0.05;
    
    european<double> call(vol, curr_price, strike_price, maturity, int_rates);
    
    cout << "Call price black scholes " << call.price_blackscholes() << endl;
    cout << "Call price binomial " << call.price_binomial() << endl;

    return 0;
}
