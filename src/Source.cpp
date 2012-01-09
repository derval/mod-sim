#include <iostream>
#include <string>

using namespace std;

#include "Source.h"


/* SOURCE CLASS IMPLEMENTATION */

Particle * Source::emitParticle()
{
  double energy = gaussian_rand(energy_,sigma_,rng_);
  Particle * newParticle = new Particle(rng_,energy,uniform_rand(0,1,rng_)*2*M_PI,position_);
  return newParticle;
}

// constructor and destructor

Source::Source(gsl_rng * rng, sourceParameters sParam): rng_(rng), energy_(sParam.energy), sigma_(sParam.sigma)
{
  position_[0]=sParam.position[0];
  position_[1]=sParam.position[0];
}


Source::~Source()
{
}

// getters


// setters


// display


// operators
