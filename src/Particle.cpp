#include <iostream>
#include <string>

using namespace std;

#include "Particle.h"

/* PARTICLE CLASS IMPLEMENTATION */

double Particle::Propagation(Collimator * collimator, Detector * detector, double*** data)
{
  int idxData = 0;
  double mu = 0;
  
  while (energy_ > data[0][0][idxData] && idxData < (nLines-1)) {
    idxData++;
  }
  
  if ((mu = detector->getDensity() * data[0][4][idxData] * 100) == 0) { // en m-1
    cerr << "-- ERROR -- Attempted to divide by ZERO (mu = 1/lambda) !" << endl;
    exit(EXIT_FAILURE);
  }
  
  double L = exp_rand(mu,rng_);

  // if particle is in detector and interacts within the detector
  if ((detector->isIn(position_[0],position_[1])) && (detector->isIn(position_[0]+L*cos(theta_),position_[1]+L*sin(theta_)))) {
    position_[0] += L*cos(theta_);
    position_[1] += L*sin(theta_);
    return 1;
  }
  // else if particle is in detector but gets out
  else if (detector->isIn(position_[0],position_[1])) {
    return 0;
  }
  // else if particle is not in the detector
  else {
    if(cos(theta_) == 0)
      return 0;
    
    double yIntersec = 0;
    
    // if it's before collimator
    if(position_[0] <= collimator->getX()) {
      yIntersec = position_[1] + (collimator->getX() - position_[0])*tan(theta_);
      
      // if it doesn't get through collimator
      if((cos(theta_) < 0) || ((yIntersec < (collimator->getY() - (collimator->getDiameter())/2)) 
			       || (yIntersec > (collimator->getY() + (collimator->getDiameter())/2)))) 
	{
	  return 0;
	}
    }
    
    // if particle is after collimator or it got through collimator
    else {
      yIntersec = position_[1] + (detector->getX() - position_[0])*tan(theta_);
      // if particle doesn't reach the detector
      if((cos(theta_) < 0) || ((yIntersec < (detector->getY() - (detector->getDiameter())/2)) 
			       || (yIntersec > (detector->getY() + (detector->getDiameter())/2)))) 
	{
	  return 0;
	}
      // finally, if particle reaches detector !
      position_[0] = detector->getX();
      position_[1] = yIntersec;
      return 1;
    }
  }
}


interactionResult Particle::Interaction(double*** data){
  
  interactionResult result;
  result.nParticlesCreated = 0;
  result.depositedEnergy = 0;
  result.particlesCreated = NULL;
    
  int interactionType = selectInteractionType(data);
  
  switch (interactionType)
    {
    case 0:
      cerr << "-- DEBUG -- Na Compton scattering"<< endl;
      Compton(&result);
      break;
    case 1:
      cerr << "-- DEBUG -- Na Photoelectric effect"<< endl;
      PhotoElectric(0,&result);
      break;
    case 2:
      cerr << "-- DEBUG -- Na Pair production"<< endl;
      PairProduction(&result);
      break;
    case 3:
      cerr << "-- DEBUG -- I Compton scattering"<< endl;
      Compton(&result);
      break;
    case 4:
      cerr << "-- DEBUG -- I Photoelectric effect"<< endl;
      PhotoElectric(1, &result);
      break;
    case 5:
      cerr << "-- DEBUG -- I Pair production"<< endl;
      PairProduction(&result);
      break;
    default:
      exit(EXIT_FAILURE);
    }

  return result;
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
  dataNorm = data[0][4][idxData];
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
  
  cerr << "-- DEBUG -- Particle Energy : " << energy_ << endl;
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



void Particle::Compton(interactionResult * result)
{
  double comptonEnergy=0;
  double thetaCompton=0;
  double ksi=energy_/511; // 511keV electron energy
  thetaCompton=parametric_arbitrary_rand(compton_distrib,ksi,0,M_PI,1,rng_);
  
  comptonEnergy = energy_/(1+ksi*(1-cos(thetaCompton)));
  
  cerr<< "-- DEBUG -- ThetaCompton : " << thetaCompton << endl;
  
  double theta = theta_ + thetaCompton;
  while(theta > 2*M_PI)
    theta -= 2*M_PI;
  while(theta < 0)
    theta += 2*M_PI;

  result->nParticlesCreated = 1;
  result->depositedEnergy = energy_ - comptonEnergy;
  result->particlesCreated = new void * [result->nParticlesCreated];
  result->particlesCreated[0] = new Particle(rng_,comptonEnergy,theta,position_);
}

double compton_distrib(double x,double ksi){
  // double r=2.81794092e-15;pow(r,2)*
  return 1/pow(1+ksi*(1-cos(x)),2)*(1+pow(cos(x),2)+pow(ksi*(1-cos(x)),2)/(1+ksi*(1-cos(x))))/2;
}

void Particle::PairProduction(interactionResult * result)  
{
  double theta=uniform_rand(0,1,rng_)*M_PI;

  result->nParticlesCreated = 2;
  result->depositedEnergy = energy_ - 1022;
  result->particlesCreated = new void * [result->nParticlesCreated];
  result->particlesCreated[0] = new Particle(rng_,511,theta,position_);
  result->particlesCreated[1] = new Particle(rng_,511,theta+M_PI,position_);
}

void Particle::PhotoElectric(int atom, interactionResult * result)
{
  const double * Shells = 0;
  
  if (atom == 0){
    Shells = Na_Shells;
  }
  else if (atom == 1){
    Shells = I_Shells;
  }
  
  // Determination of the energy of the photoelectron
  int i=-1;
  double random;
  double electronEnergy = 0;
  while(electronEnergy == 0)
    {
      i++;
      random = uniform_rand(0,1,rng_);
      
      if (Shells[i] == 0)
	electronEnergy = energy_;
      else if (energy_ > Shells[i] && random < 0.9)
	electronEnergy = energy_ - Shells[i];
    }

  result->depositedEnergy = electronEnergy;

  // Auger / Fluo
  random = uniform_rand(0,1,rng_);
  
  if(random < I_Auger)
    {
      // AUGER
      cerr << "-- DEBUG -- Auger" << endl;
      
    }
  
  else
    {
      // FLUO
      cerr << "-- DEBUG -- Fluo " ;
      
      // K alpha
      if ( i == 0 ) {
	cerr << " (K alpha) " << endl;
	random = uniform_rand(0,1,rng_);
	double hnuFluo;
	if (random <= 0.5)
	  hnuFluo = I_Shells[0] - I_Shells[2]; // K alpha 1
	else
	  hnuFluo = I_Shells[0] - I_Shells[3]; // K alpha 2
	
	
	double theta=uniform_rand(0,1,rng_)*M_PI;
	
	result->nParticlesCreated = 1;
	result->particlesCreated = new void * [result->nParticlesCreated];
	result->particlesCreated[0] = new Particle(rng_,hnuFluo,theta,position_);
      }
      
      // not K
      else
	cerr << endl << "Ignoring fluorescence process (layer with a vacancy =/= K)" << endl;
      
    }
  
}



// constructor and destructor

Particle::Particle(gsl_rng * rng, double energy): rng_(rng), energy_(energy)
{}

Particle::Particle(gsl_rng * rng, double energy, double theta, double position[3]): rng_(rng), energy_(energy), theta_(theta)
{
  position_[0] = position[0];
  position_[1] = position[1];
}

Particle::~Particle()
{}

// getters

// setters
void Particle::setNext(Particle * next)
{next_ = next;}



// display


// operators
