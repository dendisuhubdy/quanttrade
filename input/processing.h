#pragma once

#include <vector>

#include "input.h"

class processing
{
public:
	processing(std::vector<t_securitydata>data);
	~processing();
	double calculateindex();
	double divisor();
private:
	std::vector<double> m_price;
	std::vector<double> m_perc_shares_out;
	std::vector<double> m_eq_shares_out;
	std::vector<double> divisor_history;
	int security_numbers;
	double index;

};

