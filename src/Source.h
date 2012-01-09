#ifndef _SOURCE_H_INCLUDED
#define _SOURCE_H_INCLUDED

#include <iostream>
#include <string>

using namespace std;

#include "Particle.h"

typedef struct {
  double position[2];
  double energy;
  double sigma;
} sourceParameters;


/* SOURCE CLASS DEFINITION */

class Source 
{

 private:
  gsl_rng * rng_;
  double energy_;
  double sigma_; // Standard deviation of the gaussian distribution of emitted particles energies
  double position_[2];

 protected:
  

 public:

  Particle * emitParticle();

  // constructor and destructor
  Source(gsl_rng * rng, sourceParameters sParam
);
  ~Source();
  
  // getters

  // setters

  // display

  // operators
  

};


#endif
