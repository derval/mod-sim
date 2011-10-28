/* System Headers */
#include <iostream>
#include <string>
#include <math.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

/* System Config */
using namespace std;

/* Project Headers */
#include "random.h"		
#include "Experiment.h"		


/* EXPERIMENT CLASS IMPLEMENTATION */

void Experiment::event(int nEvent, int nEvents)
{
  /*
  //cout << uniform_rand(0,1,rand_gen_);
  //cout << exp_rand(1,rand_gen_);
  cout << gaussian_rand(10,3,rand_gen_);
  //cout << specific_rand(sin,0,100,10,rand_gen_);
  
  if(nEvent != nEvents)
    cout << endl;
  */

  Particle * current = source_ -> emitParticle();
  add2stack(current);
}

void Experiment::add2stack(Particle * particle)
{
  particle -> setNext(firstInStack_);
  particle -> setPrev(0);
  if(firstInStack_ != 0)
    firstInStack_ -> setPrev(particle);
  firstInStack_ = particle;
}

// constructor and destructor

Experiment::Experiment(gsl_rng * rand_gen):rand_gen_(rand_gen), firstInStack_(0)
{
  source_ = new Source();
}


Experiment::~Experiment()
{
}

// getters


// setters
void Experiment::setFirstInStack(Particle * particle)
{
  firstInStack_ = particle;
}


// display

void Experiment::showStack()
{
  cerr << endl << "-- PARTICLE STACK : --" << endl;
  Particle * current = firstInStack_;
  do
    {
      cout << "particule !" << endl;
      current = current -> getNext();
    }  while(current != 0);
}

// operators
