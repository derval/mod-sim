#include <iostream>
#include <string>

using namespace std;

#include "Particle.h"

/* PARTICLE CLASS IMPLEMENTATION */

double Particle::propagation(double lambda)
{
  double L = 0;
  double exp_probability = exp_rand(1, rng_);
  cout << "Jean Paul : " << exp_probability << endl;
  return L;
}

void Particle::interaction()
{}

// constructor and destructor

Particle::Particle(gsl_rng * rng, int type, double energy): rng_(rng), type_(type), energy_(energy)
{}

Particle::~Particle()
{}

// getters


// setters
void Particle::setNext(Particle * next)
{next_ = next;};

void Particle::setPrev(Particle * prev)
{prev_ = prev;};


// display


// operators
