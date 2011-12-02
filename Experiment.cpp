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

  while (firstInStack_ != 0)
    {
      cerr << "Taking care of particle " << current << endl;
      this -> removeFirstInStack();
      current -> propagation(1);
      delete current;
    }
  
}

void Experiment::add2stack(Particle * particle)
{
  particle -> setNext(firstInStack_);
  particle -> setPrev(0);
  if(firstInStack_ != 0)
    firstInStack_ -> setPrev(particle);
  firstInStack_ = particle;
}

void Experiment::removeFirstInStack()
{
  if(firstInStack_ != 0)
    {
      Particle * currentFirst = firstInStack_;
      
      if(currentFirst -> getNext() != 0)
	{
	  firstInStack_ = currentFirst -> getNext();
	  firstInStack_ -> setPrev(0);
	}
      else
	{
	  firstInStack_ = 0;
	}
    }
  else
    cerr << "-- ERROR -- Attempted to remove a particule from an empty stack !" << endl;
}

// constructor and destructor

Experiment::Experiment(gsl_rng * rng, double sourceEnergy):rng_(rng), firstInStack_(0)
{
  source_ = new Source(rng_,sourceEnergy);
}


Experiment::~Experiment()
{
  delete source_;
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
  cerr << "-- PARTICLE STACK : " << endl;
  
  if(firstInStack_ != 0)
    {
      Particle * current = firstInStack_;
      do
	{
	  cerr << current << endl;
	  current = current -> getNext();
	}  while(current != 0);
    }
  else
    cerr << "-- The particle stack is empty." << endl;
  cerr << "-- END OF STACK \n" << endl;
}

// operators
