/*************************************************************************
	> File Name: vanilla.cpp
	> Author: 
	> Mail: 
	> Created Time: Wed Feb  3 13:06:46 2016
 ************************************************************************/

#ifndef __VANILLA_OPTION_CPP
#define __VANILLA_OPTION_CPP

#include "option.h"

VanillaOption::VanillaOption() {}

VanillaOption::VanillaOption(double _K, double _r, double _T, 
                             double _sigma, PayOff* _pay_off) : 
  K(_K), r(_r), T(_T), sigma(_sigma), pay_off(_pay_off) {}

#endif
