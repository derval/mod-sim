#include <iostream>
#include <string>

using namespace std;

#include "Particle.h"


/* PARTICLE CLASS IMPLEMENTATION */

void Particle::propagation()
{}

void Particle::interaction()
{}

// constructor and destructor

Particle::Particle(int type): type_(type)
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
