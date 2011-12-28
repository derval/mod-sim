#ifndef _EXPERIMENT_H_INCLUDED
#define _EXPERIMENT_H_INCLUDED

#include <iostream>
#include <string>
#include <gsl/gsl_math.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

using namespace std;

#include "Source.h"
#include "Detector.h"
#include "Particle.h"
#include "interaction_data.h"


/* EXPERIMENT CLASS DEFINITION */

class Experiment
{

 private:
  // Random Generator
  gsl_rng * rng_;

  // Interaction data
  double *** data;
  
  // Particule Source
  Source * source_;
  
  // Detector
  Detector * detector_;

  // 1st Particle in Stack
  Particle * topOfStack_;

 protected:
  

 public:

  void event(int nEvent, int nEvents);
  void add2stack(Particle * particle);
  void removeTopOfStack();

  // constructor and destructor
  Experiment(gsl_rng * rng, double sourceEnergy, double sourceSigma);
  ~Experiment();
  
  // getters
  Particle * getTopOfStack(){return topOfStack_;};

  // setters
  void setTopOfStack(Particle * particle);

  // display
  void showStack();

  // operators
  

};


#endif
