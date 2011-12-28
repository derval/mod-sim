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
  cerr << "-- INFO -- New Event" << endl;
  
  int i = 0;  
  double scintillationEnergy = 0;
  
  // Source emits a particle that is added to the stack
  add2stack(source_ -> emitParticle());
  
  // Processing the stack
  while (topOfStack_ != 0)
    {
      Particle * current = topOfStack_;
      cerr << "Taking care of particle " << current << endl;
      removeTopOfStack();
      current -> Propagation(1); // Particle moves...
      interactionResult result = current -> Interaction(data); // then interacts.
      scintillationEnergy += result.depositedEnergy;

      delete current;
      current = 0;
      
      // Adding to the stack the particles resulting from previous interaction
      for (i=0; i < result.nParticlesCreated; i++)
	add2stack((Particle*)result.particlesCreated[i]);
    }

  cout << detector_->photomultiplication(detector_->scintillation(scintillationEnergy)) << endl;
  cerr << "-- DEBUG -- Collected charge : " << detector_->photomultiplication(detector_->scintillation(scintillationEnergy)) << endl << endl;
}

void Experiment::add2stack(Particle * particle)
{
  particle -> setNext(topOfStack_);
  topOfStack_ = particle;
}

void Experiment::removeTopOfStack()
{
  if(topOfStack_ != 0)
    {
      Particle * currentFirst = topOfStack_;
      
      if(currentFirst -> getNext() != 0)
	{
	  topOfStack_ = currentFirst -> getNext();
	  currentFirst -> setNext(0);
	}
      else
	{topOfStack_ = 0;}
    }
  else
    cerr << "-- ERROR -- Attempted to remove a particule from an empty stack !" << endl;
}

// constructor and destructor

Experiment::Experiment(gsl_rng * rng, double sourceEnergy, double sourceSigma):rng_(rng), topOfStack_(0)
{
  source_ = new Source(rng_,sourceEnergy, sourceSigma);
  detector_ = new Detector();
  
  // Loading Interaction Data
  int i,j = 0;
  data = new double ** [2];
  for(i = 0; i < 2; i++)
    {
      data[i] = new double * [nColumns];
      for(j = 0; j < nColumns; j++)
	data[i][j] = new double [nLines];
    }
  
  initData(data);
}


Experiment::~Experiment()
{
  delete source_;
  delete detector_;

  // Deleting Interaction Data
  int i,j = 0;
  for(i = 0; i < 2; i++) {
    for(j = 0; j < nColumns; j++) {
      delete [] data[i][j];
      data[i][j] = 0;
    }
    delete [] data[i];
    data[i] = 0;
  }
  delete [] data;
  data = 0;

}

// getters


// setters
void Experiment::setTopOfStack(Particle * particle)
{
  topOfStack_ = particle;
}


// display

void Experiment::showStack()
{
  cerr << "-- PARTICLE STACK : " << endl;
  
  if(topOfStack_ != 0)
    {
      Particle * current = topOfStack_;
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
