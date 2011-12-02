#ifndef _PARTICLE_H_INCLUDED
#define _PARTICLE_H_INCLUDED

#include <iostream>
#include <string>

using namespace std;

#include "random.h"

/* PARTICLE CLASS DEFINITION */

/* Particle Types */
#define PHOTON 0
#define ELECTRON 1
#define POSITRON 2
#define IODINE 3
#define SODIUM 4


class Particle 
{
  
 private:
  
  // Random Number Generator
  gsl_rng * rng_;
  // Particle Type
  int type_;
  // Energy
  double energy_;
  // Position
  double position_[3]; 
  // Direction
  double theta_, phi_; 

  // Previous and next particle in the stack
  Particle * next_; 
  Particle * prev_;
  
  
 protected:
  
  
 public:
  
  double propagation(double lambda);
  void interaction(void);

  // constructor and destructor
  Particle(gsl_rng * rng, int type, double energy);
  ~Particle();
  
  // getters
  int getType(){return type_;};
  double getX(){return position_[0];};
  double getY(){return position_[1];};
  double getZ(){return position_[2];};
  Particle * getNext(){return next_;};
  Particle * getPrev(){return prev_;};
 
  // setters

  void setNext(Particle * next);
  void setPrev(Particle * prev);

  // display

  // operators
  

};


#endif
