#include <iostream>
#include <string>

using namespace std;

#include "Source.h"


/* SOURCE CLASS IMPLEMENTATION */

sourceEmission Source::emitParticle(int sourceType)
{
  sourceEmission emission;
  emission.nParticlesEmitted = 0;
  
  switch(sourceType) {
    
  case 22 : {
    // Na22 Source
    emission.nParticlesEmitted = 2;
    emission.particlesEmitted = new Particle * [emission.nParticlesEmitted];
    emission.particlesEmitted[0] = new Particle(rng_,1022,uniform_rand(0,1,rng_)*2*M_PI,position_);
    emission.particlesEmitted[1] = new Particle(rng_,500,uniform_rand(0,1,rng_)*2*M_PI,position_);
    break;
  }
    
  default : {
    // SIMPLE SOURCE (1 GAMMA - 1 ENERGY)
    double energy = gaussian_rand(energy_,sigma_,rng_);
    emission.nParticlesEmitted = 1;
    emission.particlesEmitted = new Particle * [emission.nParticlesEmitted];
    emission.particlesEmitted[0] = new Particle(rng_,energy,uniform_rand(0,1,rng_)*2*M_PI,position_);
    break;
  }
  }
  return emission;
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
