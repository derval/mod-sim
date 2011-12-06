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
#include "interaction_data.h"
#include "Experiment.h"




/* Main Program */
int main(int argc, char * argv[])
{ 

  // Welcome message
  cerr << "\n========================================" << endl
       << "== SIMULATION PROJECT - CMI 2011-2012 ==" << endl
       << "========================================\n" << endl;


  // Number of events
  int nEvents = 100;
  if (argc == 2) 
    nEvents = atoi(argv[1]);


  // Random Number Generator initialization
  gsl_rng * rng = initialize_rand();


  // Loading Interaction Data
  int i,j = 0;
  double *** data = new double ** [2];
  for(i = 0; i < 2; i++)
    {
      data[i] = new double * [nColumns];
      for(j = 0; j < nColumns; j++)
	data[i][j] = new double [nLines];
    }
  
  initData(data);


  // Display configuration of the simulation
  cerr << "--- Number of Events : " << nEvents << endl;
  cerr << endl;


  // Create the experiment (energy in eV)
  Experiment * experiment = new Experiment(rng,1000000);

  
  // Proceed to a given number of events
  i = 0;
  for (i=1;i <= nEvents;i++){
    experiment->event(i,nEvents);
  }
  
  // Cleaning
  delete(experiment);
  gsl_rng_free (rng);

  return 0;
}
 
