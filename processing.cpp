/***************************
 * DATA PROCESSING PROGRAM 
 * by ANTOINE GAUME
 ***************************/

/* System Headers */
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>

/* System Config */
using namespace std;

/* Project Headers */

/* ROOT Headers */
#include "TROOT.h"
#include "TRint.h"
#include "TBenchmark.h"
#include "TApplication.h"
#include "TCanvas.h"
#include "TPaveLabel.h"
#include "TH1.h"
#include "TF1.h"

// Quadratic background function
Double_t background(Double_t *x, Double_t *par) {
   return par[0] + par[1]*x[0] + par[2]*x[0]*x[0];
}

// Lorenzian Peak function
Double_t gaussianPeak(Double_t *x, Double_t *par) {
  return (par[0]*exp(-1.*(par[1]-x[0])*(par[1]-x[0])/(2*par[2]*par[2])));
}

// Sum of background and peak function
Double_t fitFunction(Double_t *x, Double_t *par) {
  return gaussianPeak(x,&par[0]);
  //    return gaussianPeak(x,&par[0]) + background(x,&par[3]);
}


/* Main Program */
int main(int argc, char * argv[])
{ 
  // 3 for gaussian fit / 6 for gaussin + noise fit
  int nFitParam = 3;

  // Welcome message
  cerr << "\n== DATA PROCESSING - CMI 2011-2012 ==\n" << endl;
  
  // Display configuration of the data processing
  cerr << "No configuration yet" << endl;
  
  // Declaring ROOT variables
  TCanvas *canvas;
  TApplication *theApp;
  TH1 *histo;

  
  theApp=new TApplication("App", &argc, argv);
  
  canvas = new TCanvas("c", "Simulation Projet", 400, 400);
  canvas->cd();
  canvas->Update();

  histo  = new TH1F("histo","Charge Distribution", 500, 0, 100);

  ifstream file("data",ios::in);
  if(file)
    {
      double output;
      while(!file.eof())
        {
	  file >> output;
	  histo->Fill(output,1.);
        }
      file.close();
    }  


  TF1 *fitFcn = new TF1("fitFcn",fitFunction,0.,100.,nFitParam);
  fitFcn->SetNpx(500);
  fitFcn->SetLineWidth(1);
  fitFcn->SetLineColor(kMagenta);
  fitFcn->SetParameters(50,1.,2.,500,49,1.);
  histo->Fit("fitFcn","R");
  

  histo->Draw("E");

  theApp->Run();


  // Cleaning
  
  
  return 0;
}
 
