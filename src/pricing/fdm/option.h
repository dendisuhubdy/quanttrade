/*************************************************************************
	> File Name: vanilla.h
	> Author: 
	> Mail: 
	> Created Time: Wed Feb  3 13:06:16 2016
 ************************************************************************/

#ifndef _VANILLA_H
#define _VANILLA_H

#include "payoff.h"

class VanillaOption {
     public:
      PayOff* pay_off;

      double K;
      double r;
      double T;
      double sigma;

      VanillaOption();
      VanillaOption(double _K, double _r, double _T, 
                                   double _sigma, PayOff* _pay_off);

};

#endif
