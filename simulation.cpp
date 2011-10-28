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




/* Main Program */
int main(int argc, char * argv[])
{ 

  // Welcome message
  cerr << "\n== SIMULATION PROJECT - CMI 2011-2012 ==\n" << endl;

  // Number of events
  int nEvents = 100;
  if (argc == 2) 
    nEvents = atoi(*++argv);

  // Random Generator initialization
  gsl_rng * rand_gen = initialize_rand();

  // Display configuration of the simulation
  cerr << "--- Number of Events : " << nEvents << endl;


  // Create the experiment
  Experiment * experiment = new Experiment(rand_gen);

  
  // Proceed to a given number of events
  int i = 0;
  for (i=1;i <= nEvents;i++){
    experiment->event(i,nEvents);
  }

  experiment->showStack();


  // Cleaning
  delete(experiment);
  gsl_rng_free (rand_gen);

  return 0;
}
 
