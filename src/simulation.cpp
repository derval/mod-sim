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
#include "histo_maker.h"		
#include "Experiment.h"


// ALL ENERGY IN ALL PROGRAMS IN keV


/* Main Program */
int main(int argc, char * argv[])
{ 
  
  // Welcome message
  cerr << "\n========================================" << endl
       << "== SIMULATION PROJECT - CMI 2011-2012 ==" << endl
       << "========================================\n" << endl;
  
  
  ////////////////
  // PARAMETERS //
  ////////////////
  //
  // Source Parameters
  sourceParameters sParam;
  sParam.position[0] = 0; //
  sParam.position[1] = 0; // m
  sParam.energy = 49.5; // keV
  sParam.sigma = 0; // keV
  // Detector Parameters
  detectorParameters dParam;
  dParam.position[0] = 0.05; // m
  dParam.position[1] = 0; // m
  dParam.diameter = 0.05; // m
  dParam.width = 0.05; // m
  // Collimator Parameters
  collimatorParameters cParam;
  cParam.position[0] = 0.01; // m
  cParam.position[1] = 0; // m
  cParam.diameter = 0.05; // m
  
  if(cParam.position[0] >= (dParam.position[0] - dParam.width/2)) {
    cerr << "-- ERROR -- Collimator must be placed before detector on x axis. Please change parameters." << endl;
    exit(EXIT_FAILURE);
  }
  
  // Number of events
  int nEvents = 1;
  
  if (argc == 3) {
      nEvents = atoi(argv[1]);
      sParam.energy = atof(argv[2]);
    }
  
  else if (argc != 1 && argc != 3) {
      cerr << "-- ERROR -- Proper use is ./simulation OR ./simulation <number of events> <source energy (keV)>" << endl << endl;
      exit(EXIT_FAILURE);
    }



  // Random Number Generator initialization
  gsl_rng * rng = initialize_rand();



  // Display configuration of the simulation
  cerr << "-- CONFIG -- Source Energy : " << sParam.energy << " keV" << endl;
  cerr << "-- CONFIG -- Source Energy Standard Deviation : " << sParam.sigma << " keV" << endl;
  cerr << "-- CONFIG -- Number of Events : " << nEvents << endl;
  cerr << endl;


  // Create the experiment (energy in keV)
  Experiment * experiment = new Experiment(rng,sParam,dParam,cParam);

  cerr << endl;

  // Proceed to a given number of events and store the energies deposited
  double * scintillationEnergies = new double [nEvents];
  int i = 0;
  for (i=0;i < nEvents;i++){
    scintillationEnergies[i] = experiment->event();
  }
  
  // Histo maker
  histo_maker(nEvents,scintillationEnergies,sParam.energy*1.1);

  // Cleaning
  delete(experiment);
  gsl_rng_free (rng);
  
  return 0;
}
 
