/*************************************************************************
	> File Name: fdm_main.cpp
	> Author: 
	> Mail: 
	> Created Time: Wed Feb  3 13:22:02 2016
 ************************************************************************/

#include "payoff.h"
#include "option.h"
#include "pde.h"
#include "fdm.h"

int main(int argc, char **argv) {
  // Create the option parameters
  double K = 120.00;  // Strike price
  double r = 0.05;   // Risk-free rate (5%)
  double v = 0.2;    // Volatility of the underlying (20%)
  double T = 2.00;    // One year until expiry

  // FDM discretisation parameters
  double x_dom = 100.0;       // Spot goes from [0.0, 1.0]
  unsigned long J = 20; 
  double t_dom = T;         // Time period as for the option
  unsigned long N = 20;     

  // Create the PayOff and Option objects
  PayOff* pay_off_call = new PayOffCall(K);
  VanillaOption* call_option = new VanillaOption(K, r, T, v, pay_off_call);

  // Create the PDE and FDM objects
  BlackScholesPDE* bs_pde = new BlackScholesPDE(call_option);
  FDMEulerExplicit fdm_euler(x_dom, J, t_dom, N, bs_pde);

  // Run the FDM solver
  fdm_euler.step_march();

  // Delete the PDE, PayOff and Option objects
  delete bs_pde;
  delete call_option;
  delete pay_off_call;

  return 0;
}

