#include <iostream>
#include <string>

#include "random.h"

#include <time.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_sf_log.h>
#include <math.h>

using namespace std;


/* RANDOM NUMBER GENERATORS */

gsl_rng * initialize_rand()
{
  gsl_rng * rand_gen;
  rand_gen = gsl_rng_alloc(gsl_rng_taus);
  gsl_rng_set(rand_gen,time(NULL));
  return rand_gen;
}

double uniform_rand(double lower, double upper, gsl_rng * rand_gen)
{
  double random = lower + (upper - lower) * gsl_rng_uniform(rand_gen);
  return random;
}

double exp_rand(double lambda, gsl_rng * rand_gen)
{
  double random = -1 * 1 / lambda * gsl_sf_log(gsl_rng_uniform(rand_gen));
  return random;
}

double gaussian_rand(double mu, double sq_sigma, gsl_rng * rand_gen)
{
  double random = sqrt(-2 * gsl_sf_log(gsl_rng_uniform(rand_gen))) * 
    cos(2*PI*gsl_rng_uniform(rand_gen));
  random = mu + random * sq_sigma;
  return random;
}

double specific_rand(double (*distribution)(double x), double lower_dist, double upper_dist, 
		     double max_distrib, gsl_rng * rand_gen)
{
  short done = 0;

  while(done == 0)
    {
      double uniform = gsl_rng_uniform(rand_gen);
      double uniform_lu = uniform_rand(lower_dist, upper_dist, rand_gen);
      if(1 / max_distrib * (*distribution)(uniform_lu) > uniform)
	{
	  done = 1;
	  return uniform_lu;
	}
    }

  return 0;
}
