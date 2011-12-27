#include <iostream>
#include <string>

using namespace std;

#include "Detector.h"


/* DETECTOR CLASS IMPLEMENTATION */

double Detector::scintillation(double electronEnergy)
{
       return efficiency_*electronEnergy/W_;
}

double Detector::photomultiplication(double nPhotons)
{
       return nPhotons * QE_ * CE_ * G_;
}

// constructor and destructor

Detector::Detector()
{
}


Detector::~Detector()
{
}

// getters


// setters


// display


// operators




