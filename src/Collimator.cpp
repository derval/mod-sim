#include <iostream>
#include <string>

using namespace std;

#include "Collimator.h"

Collimator::Collimator(collimatorParameters parameters): diameter_(parameters.diameter)
{
  position_[0] = parameters.position[0];
  position_[1] = parameters.position[1];
}

Collimator::~Collimator()
{}
