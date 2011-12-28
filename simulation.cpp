/******************************
 * MAIN PROGRAM FOR SIMULATION
 * by ANTOINE GAUME
 ******************************/

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


// ALL ENERGY IN ALL PROGRAMS IN keV


/* Main Program */
int main(int argc, char * argv[])
{ 
  // Default Source Parameters
  double sourceEnergy = 49.5; // keV
  double sourceSigma = 2; // keV

  // Welcome message
  cerr << "\n========================================" << endl
       << "== SIMULATION PROJECT - CMI 2011-2012 ==" << endl
       << "========================================\n" << endl;


  // Number of events
  int nEvents = 1;
  
  if (argc == 3) {
      nEvents = atoi(argv[1]);
      sourceEnergy = atof(argv[2]);
    }
  
  else if (argc != 1 && argc != 3) {
      cerr << "-- ERROR -- Proper use is ./simulation OR ./simulation <number of events> <source energy (keV)>" << endl << endl;
      exit(EXIT_FAILURE);
    }

  // Random Number Generator initialization
  gsl_rng * rng = initialize_rand();


  // Display configuration of the simulation
  cerr << "-- CONFIG -- Source Energy : " << sourceEnergy << " keV" << endl;
  cerr << "-- CONFIG -- Source Energy Standard Deviation : " <<
  cerr << "-- CONFIG -- Number of Events : " << nEvents << endl;
  cerr << endl;


  // Create the experiment (energy in keV)
  Experiment * experiment = new Experiment(rng,sourceEnergy,sourceSigma);

  cerr << endl;

  // Proceed to a given number of events
  int i = 0;
  for (i=1;i <= nEvents;i++){
    experiment->event(i,nEvents);
  }
  
  // Cleaning
  delete(experiment);
  gsl_rng_free (rng);

  return 0;
}
 
