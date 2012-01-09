#ifndef _HISTO_H_INCLUDED
#define _HISTO_H_INCLUDED

#include <iostream>
#include <gsl/gsl_histogram.h>
#include "file_maker.h"

using namespace std;

void histo_maker(int n, double * omega, double hmax);

#endif
