#include "stdafx.h"
#include "processing.h"


processing::processing(std::vector<t_securitydata>data)
{
	/*
	initialize class
	*/
	for (int i = 0; i < data.size(); i++) {
		for (int j = 0; j < sizeof(t_securitydata); j++) {
			if (j == 0) {
				m_price.push_back(data[i].price);
			}
			else if (j == 1) {
				m_perc_shares_out.push_back(data[i].price);
			}
			else if (j == 2) {
				m_eq_shares_out.push_back(data[i].price);
			}
		}
	}
}

processing::~processing()
{
	/*
	destructor
	return nothing
	*/
}

double processing::calculateindex()
{
	/*
	recalculate the number of securities in the vectors
	after each adjustments there are N new numbers of securities
	*/
	security_numbers = m_price.size();
	double sum = 0;
	for (int i = 0; i < security_numbers; i++) {
		sum += m_price[i] * m_perc_shares_out[i] * m_eq_shares_out[i];
	}
	double divisor = 1000;
	index = sum/divisor;
	return index;
}

double processing::divisor()
{
	double divisor_history = 1000;
	return divisor_history;
}