#ifndef _PARTICLE_H_INCLUDED
#define _PARTICLE_H_INCLUDED

#include <iostream>
#include <string>

using namespace std;

#include "random.h"
#include "interaction_data.h"

/* PARTICLE CLASS DEFINITION */

/* Particle Types */
#define PHOTON 0
#define ELECTRON 1
#define POSITRON 2
#define IODINE 3
#define SODIUM 4


typedef struct
{
  int nParticlesCreated;
  void ** particlesCreated;
  double depositedEnergy;
} interactionResult;


class Particle
{
  
 private:

  // Random Number Generator
  gsl_rng * rng_;
  // Energy
  double energy_;
  // Position
  double position_[3]; 
  // Direction
  double theta_, phi_; 

  // Previous and next particle in the stack
  Particle * next_;   

  // Private functions
  int selectInteractionType(double *** data);
  void PhotoElectric(int atom, interactionResult * result);

  
 protected:
  
  
 public:
  
  double Propagation(double lambda);
  interactionResult Interaction(double *** data);  

  // constructor and destructor
  Particle(gsl_rng * rng, double energy);
  ~Particle();
  
  // getters
  double getX(){return position_[0];};
  double getY(){return position_[1];};
  double getZ(){return position_[2];};
  Particle * getNext(){return next_;};
  double getEnergy(){return energy_;};

  // setters

  void setNext(Particle * next);

  // display

  // operators
  

};


#endif
