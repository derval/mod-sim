#ifndef DEF_DETECTOR
#define DEF_DETECTOR

#include <iostream>
#include <string>

using namespace std;


typedef struct {
  double position[2];
  double diameter;
  double width;
} detectorParameters;

/* DETECTOR CLASS DEFINITION */

class Detector 
{
    
 private:
  
  static const double efficiency_ = 0.04; //efficiency  ~  4%  (taux  de  luminescence  du  scintillateur = η*ξ)
  //η : Rendement = 30% (nombre de paires électron-trou créées par un électron)
  //ξ : Coefficient de luminescence = 13% (proportion d’énergie transformée en scintillation).
  static const double W_ = 6e-3; // W = 6 eV Energie d'exitation
  static const double QE_ = 0.11; //QE ~ 11% (efficacité quantique de la photocathode du multiplicateur
  static const double CE_ = 0.95; //CE ~  95%  (efficacité  de  collection  de  l’électron  de  conversion  par  la  première dynode
  static const double G_ = 10e5;
  static const double density_ = 3.67; //en kg/m3 ou g/cm3

  double position_[2];
  double diameter_, width_;
  
 protected:
  

 public:

  double scintillation(double electronEnergy);
  double photomultiplication(double nPhotons);
  int isIn(double x, double y);

  // constructor and destructor
  Detector(detectorParameters parameters);
  ~Detector();
  
  // getters
  double getDensity() {return density_;};
  double getX(){return position_[0];};
  double getY(){return position_[1];};
  double getDiameter() {return diameter_;};

  // setters

  // display

  // operators
 

};

#endif
