#ifndef RANDOM_H
#define RANDOM_H

const double PI = 3.1415926535897932385;

#include <iostream>
#include <string>

#include <gsl/gsl_math.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

/* RANDOM NUMBER GENERATORS */

gsl_rng * initialize_rand();

// Uniform distribution between LOWER and UPPER using RAND_GEN
double uniform_rand(double lower, double upper, gsl_rng * rand_gen);

// Exponential distribution (p(x) = param * exp(-param * x))
double exp_rand(double param, gsl_rng * rand_gen);

// Gaussian distribution
double gaussian_rand(double mu, double sq_sigma, gsl_rng * rand_gen);

// Specific distribution according to distribution function DISTRIBUTION
double arbitrary_rand(double (*distribution)(double x), double lower_dist, double upper_dist, 
		     double max_distrib, gsl_rng * rand_gen);

double parametric_arbitrary_rand(double (*distribution)(double x, double p), double parameter, double lower_dist, double upper_dist, 
		     double max_distrib, gsl_rng * rand_gen);

// +1 or -1 random creator
double sign_rand(gsl_rng * rand_gen);


#endif
