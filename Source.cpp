#include <iostream>
#include <string>

using namespace std;

#include "Source.h"


/* SOURCE CLASS IMPLEMENTATION */

Particle * Source::emitParticle()
{
  Particle * newParticle = new Particle(1);
  return newParticle;
}

// constructor and destructor

Source::Source()
{
}


Source::~Source()
{
}

// getters


// setters


// display


// operators
