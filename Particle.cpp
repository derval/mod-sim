#include <iostream>
#include <string>

using namespace std;

#include "Particle.h"

/* PARTICLE CLASS IMPLEMENTATION */

double Particle::Propagation(double lambda)
{
  double L = 0;
  double exp_probability = exp_rand(1, rng_);
  cerr << "-- DEBUG -- Rand : " << exp_probability << endl;
  return L;
}


int Particle::selectInteractionType(double *** data)
{
  int interactionType;
  double cNa, peNa, ppNa, cI, peI, ppI;
  double dataNorm = 0;
  int idxData = 0;
  while (energy_ > data[0][0][idxData] && idxData < (nLines-1)) {
    idxData++;
  }
  dataNorm = (Na_A*(data[0][1][idxData]+data[0][2][idxData]+data[0][3][idxData])+I_A*(data[1][1][idxData]+data[1][2][idxData]+data[1][3][idxData]))/(Na_A+I_A);
  if (dataNorm <= 0){
    cerr << "-- ERROR -- Problem during selectInteractionType" << endl;
    exit(EXIT_FAILURE);
  }
  
  cNa = Na_A*data[0][1][idxData]/(Na_A+I_A);
  peNa = Na_A*data[0][2][idxData]/(Na_A+I_A);
  ppNa = Na_A*data[0][3][idxData]/(Na_A+I_A);
  cI = I_A*data[1][1][idxData]/(Na_A+I_A);
  peI = I_A*data[1][2][idxData]/(Na_A+I_A);
  ppI = I_A*data[1][3][idxData]/(Na_A+I_A);
  
  /*	cerr << "dataNorm : " << dataNorm <<endl;
	cerr << "sum p : " << (peNa+cNa+ppNa+cI+peI+ppI) <<endl;
	cerr << "data[0][0]["<<idxData<<"] : " << data[0][0][idxData] <<endl;
	cerr << "cNa : " << cNa/dataNorm <<endl;
	cerr << "peNa : " << peNa/dataNorm <<endl;
	cerr << "ppNa : " << ppNa/dataNorm <<endl;
	cerr << "cI : " << cI/dataNorm <<endl;
	cerr << "peI : " << peI/dataNorm <<endl;
	cerr << "ppI : " << ppI/dataNorm <<endl;*/

  cerr << "NRJ " << energy_ << endl;
  double x = uniform_rand(0,dataNorm,rng_);
  
  //cerr<<"x= "<<x<<endl;
  
  if (x<=cNa) {
    interactionType=0;//Compton Na
  }
  else if (x>cNa && x<=(cNa+peNa)) {
    interactionType=1;//Photoelectric Na
  }
  else if (x>(cNa+peNa) && x<=(cNa+peNa+ppNa)) {
    interactionType=2;//Pair Production Na
  }
  else if (x>(cNa+peNa+ppNa) && x<=(cNa+peNa+ppNa+cI)) {
    interactionType=3;//Compton Na
  }
  else if (x>(cNa+peNa+ppNa+cI) && x<=(peNa+cNa+ppNa+cI+peI)) {
    interactionType=4;//Photoelectric Na
  }
  else if (x>(cNa+peNa+ppNa+cI+peI) && x<=dataNorm) {
    interactionType=5;//Pair Production Na
  }
  else {
    cerr << "-- ERROR -- Problem during selectInteractionType" << endl;
    exit(EXIT_FAILURE);
  }
  return interactionType;
}

interactionResult Particle::Interaction(double*** data){
  
  interactionResult result;
  int interactionType = selectInteractionType(data);
    
  switch (interactionType)
    {
    case 0:
      {
	cerr << "-- DEBUG -- Na Compton scattering"<< endl;
	break;
      }
      
    case 1:
      {
	cerr << "-- DEBUG -- Na Photoelectric effect"<< endl;
	break;
      }
      
    case 2:
      {
	cerr << "-- DEBUG -- Na Pair production"<< endl;	
	break;
      }
      
    case 3:
      {
	cerr << "-- DEBUG -- I Compton scattering"<< endl;
	break;
      }
      
    case 4:
      {
	cerr << "-- DEBUG -- I Photoelectric effect"<< endl;
	
	// Determination of the energy of the photoelectron
	double electronEnergy = 0;
	double random;
	int i = 0;

	while(electronEnergy == 0)
	  {
	    random = uniform_rand(0,1,rng_);

	    if (I_Shells[i] == 0)
	      electronEnergy = energy_;
	    else if (energy_ > I_Shells[i] && random < 0.9)
	      electronEnergy = energy_ - I_Shells[i];

	    i++;
	  }
	
	cout << electronEnergy << endl;

	// Auger / Fluo
	random = uniform_rand(0,1,rng_);
	
	if(random < I_Auger)
	  {
	    // AUGER
	    cout << "Auger" << endl;
	  }
	else
	  {
	    // FLUO
	    cout << "Fluo" << endl;
	  }

	break;
      }
    
    case 5:
      {
	cerr << "-- DEBUG -- I Pair production"<< endl;	
	break;
      }
      
    default:
      exit(EXIT_FAILURE);
    }

  result.nParticlesCreated = 1;
  result.depositedEnergy = 35.97;
  result.particlesCreated = new void * [result.nParticlesCreated];
  result.particlesCreated[0] = new Particle(rng_,0,25);

  return result;
}

// constructor and destructor

Particle::Particle(gsl_rng * rng, int type, double energy): rng_(rng), type_(type), energy_(energy)
{}

Particle::~Particle()
{}

// getters

// setters
void Particle::setNext(Particle * next)
{next_ = next;};



// display


// operators
