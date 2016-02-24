/*************************************************************************
	> File Name: payoff.cpp
	> Author: 
	> Mail: 
	> Created Time: Wed Feb  3 13:05:06 2016
 ************************************************************************/

#ifndef __PAY_OFF_CPP
#define __PAY_OFF_CPP

#include "payoff.h"

PayOff::PayOff() {}

// ==========
// PayOffCall
// ==========

// Constructor with single strike parameter
PayOffCall::PayOffCall(const double& _K) { K = _K; }

// Over-ridden operator() method, which turns PayOffCall into a function object
double PayOffCall::operator() (const double& S) const {
  return std::max(S-K, 0.0); // Standard European call pay-off
}

// =========
// PayOffPut
// =========

// Constructor with single strike parameter
PayOffPut::PayOffPut(const double& _K) {
  K = _K;
}

// Over-ridden operator() method, which turns PayOffPut into a function object
double PayOffPut::operator() (const double& S) const {
  return std::max(K-S, 0.0); // Standard European put pay-off
}

#endif
