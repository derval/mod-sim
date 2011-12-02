#include <iostream>
#include <string>

using namespace std;

#include "Source.h"


/* SOURCE CLASS IMPLEMENTATION */

Particle * Source::emitParticle()
{
  Particle * newParticle = new Particle(rng_,0,sourceEnergy_);
  return newParticle;
}

// constructor and destructor

Source::Source(gsl_rng * rng, double sourceEnergy): rng_(rng), sourceEnergy_(sourceEnergy)
{
}


Source::~Source()
{
}

// getters


// setters


// display


// operators
