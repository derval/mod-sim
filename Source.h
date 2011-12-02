#ifndef _SOURCE_H_INCLUDED
#define _SOURCE_H_INCLUDED

#include <iostream>
#include <string>

using namespace std;

#include "Particle.h"

/* SOURCE CLASS DEFINITION */

class Source 
{

 private:
  gsl_rng * rng_;
  double sourceEnergy_;

 protected:
  

 public:

  Particle * emitParticle();

  // constructor and destructor
  Source(gsl_rng * rng, double sourceEnergy);
  ~Source();
  
  // getters

  // setters

  // display

  // operators
  

};


#endif
