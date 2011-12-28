#include <iostream>
#include <string>

using namespace std;

#include "Source.h"


/* SOURCE CLASS IMPLEMENTATION */

Particle * Source::emitParticle()
{
  double energy = gaussian_rand(sourceEnergy_,sourceSigma_,rng_);
  Particle * newParticle = new Particle(rng_,energy);
  return newParticle;
}

// constructor and destructor

Source::Source(gsl_rng * rng, double sourceEnergy, double sourceSigma): rng_(rng), sourceEnergy_(sourceEnergy), sourceSigma_(sourceSigma)
{
}


Source::~Source()
{
}

// getters


// setters


// display


// operators
