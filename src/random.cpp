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

double exp_rand(double param, gsl_rng * rand_gen)
{
  double random = -1 * 1/param * gsl_sf_log(gsl_rng_uniform(rand_gen));
  return random;
}

double gaussian_rand(double mu, double sq_sigma, gsl_rng * rand_gen)
{
  double random = sqrt(-2 * gsl_sf_log(gsl_rng_uniform(rand_gen))) * 
    cos(2*PI*gsl_rng_uniform(rand_gen));
  random = mu + random * sq_sigma;
  return random;
}

double arbitrary_rand(double (*distribution)(double x), double lower_dist, double upper_dist, double max_distrib, gsl_rng * rand_gen)
{
  double u=0;
  double v=0;
  
  if( (upper_dist-lower_dist) <= 0 ){
    cerr << "-- ERROR -- Attempted to use a wrong distribution in arbitrary_law (min/max)!" << endl;
    exit(EXIT_FAILURE);
  }
  
  if( max_distrib <= 0 ){
    cerr << "-- ERROR -- Attempted to use a wrong distribution in arbitrary_law (max_distrib) !" << endl;
    exit(EXIT_FAILURE);
  }
  
  do {
    u=gsl_rng_uniform(rand_gen);
    v=(upper_dist-lower_dist)*gsl_rng_uniform(rand_gen);
  }while ( u > (*distribution)(v) / max_distrib );
  return v;
}

double parametric_arbitrary_rand(double (*distribution)(double x, double p), double parameter, double lower_dist, double upper_dist, double max_distrib, gsl_rng * rand_gen)
{
  double u=0;
  double v=0;
  
  if( (upper_dist-lower_dist) <= 0 ){
    cerr << "-- ERROR -- Attempted to use a wrong distribution in arbitrary_law (min/max)!" << endl;
    exit(EXIT_FAILURE);
  }
  
  if( max_distrib <= 0 ){
    cerr << "-- ERROR -- Attempted to use a wrong distribution in arbitrary_law (max_distrib) !" << endl;
    exit(EXIT_FAILURE);
  }
  
  do {
    u=gsl_rng_uniform(rand_gen);
    v=(upper_dist-lower_dist)*gsl_rng_uniform(rand_gen);
  }while ( u > distribution(v,parameter) / max_distrib );
  return v;
}


double sign_rand(gsl_rng * rand_gen)
{
  double random;
  if (uniform_rand(0,1,rand_gen) > 0.5)
    random = 1;
  else
    random = -1;
  return random;
}
