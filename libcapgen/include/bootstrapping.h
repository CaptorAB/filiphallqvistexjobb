#ifndef BOOTSTRAPPING_H
#define BOOTSTRAPPING_H

#include <vector>

using namespace std;

void adjust_credit_par_rates(vector<double> &par_rates);

vector<double> bootstrap_discount_factors(vector<double> &par_rates);

vector<double> compute_forward_rates(vector<double> &discount_factors);

void adjust_ufr_forward_rates(vector<double> &forward_rates);

vector<double> compute_discount_factors(vector<double> &forward_rates);

vector<double> compute_zero_coupon_rates(vector<double> &discount_factors);

#endif