#ifndef _COLLIMATOR_H_INCLUDED
#define _COLLIMATOR_H_INCLUDED

#include <iostream>
#include <string>


typedef struct {
  double position[2];
  double diameter;
} collimatorParameters;


/* COLLIMATOR CLASS DEFINITION */

class Collimator 
{
  
 private:
  double position_[2];
  double diameter_;
  
 protected:
  
  
 public:
  
  // constructor and destructor
  Collimator(collimatorParameters parameters);
  ~Collimator();
  
  // getters
  double getX(){return position_[0];};
  double getY(){return position_[1];};
  double getDiameter(){return diameter_;};
 
  // setters

  // display

  // operators
  

};


#endif
