#ifndef _PARTICLE_H_INCLUDED
#define _PARTICLE_H_INCLUDED

#include <iostream>
#include <string>

using namespace std;

#include "random.h"
#include "interaction_data.h"

#include "Detector.h"
#include "Collimator.h"

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

double compton_distrib(double x,double ksi);


class Particle
{
  
 private:

  // Random Number Generator
  gsl_rng * rng_;
  // Energy
  double energy_;

  // Position
  double position_[2]; 
  // Direction
  double theta_;

  // Next particle in the stack
  Particle * next_;   

  // Private functions
  int selectInteractionType(double *** data);
  void Compton(interactionResult * result);
  void PhotoElectric(int atom, interactionResult * result);
  void PairProduction(interactionResult * result);
  void AugerFluo(int atom, interactionResult * result, const double * Shells, double probaAuger, int emptyShell);

  
 protected:
  
  
 public:
  
  double Propagation(Collimator * collimator, Detector * detector, double *** data);
  interactionResult Interaction(double *** data);  

  // constructor and destructor
  Particle(gsl_rng * rng, double energy);
  Particle(gsl_rng * rng, double energy, double theta, double * position);
  ~Particle();
  
  // getters
  double getX(){return position_[0];};
  double getY(){return position_[1];};
  Particle * getNext(){return next_;};
  double getEnergy(){return energy_;};

  // setters

  void setNext(Particle * next);

  // display

  // operators
  

};


#endif
