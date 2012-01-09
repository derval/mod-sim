#include "histo_maker.h"

void histo_maker(int n, double* omega, double hmax)
{
  //Histogramme
  int i;
  int ncolumns = 2;
  int nbhist = 1000;
  double hmin = 1;
  double *histogram = new double [nbhist];
  double *N = new double [nbhist];
  double **outtable = new double* [nbhist];
  for( i=0 ; i < nbhist ; i++ )
    outtable[i] = new double[ncolumns]; //2:nb de colonnes

  size_t nhist = size_t(nbhist);
  gsl_histogram *h = gsl_histogram_alloc(nhist);
  gsl_histogram_set_ranges_uniform (h, hmin, hmax);

  for (i = 0 ; i < n ; i++) {
    gsl_histogram_increment (h, omega[i]);
  }

  for (i = 0 ; i < nbhist ; i++) {
    histogram[i] = gsl_histogram_get (h, i);
    //N[i] = (-(double(nbhist) - 1) / 2 + i) * hmax * 2 / nbhist;
    N[i] = hmin + (hmax - hmin) * (i + 1/2.) / nbhist ;
    outtable[i][0]=N[i];
    outtable[i][1]=histogram[i];
  }

  gsl_histogram_free (h);

  int *size = new int [2];
  size[0] = nbhist; // lignes
  size[1] = ncolumns; // colonnes
  string filename="histo_result.csv";
  //écriture dans les fichiers (taille, pointeur vers un tableau, nom fichier)
  file_maker(size, outtable, filename);

  size[0] = n;
  size[1] = 1;

  double **outtable2 = new double* [n];
  for( i=0 ; i < n ; i++ )
    outtable2[i] = new double[2]; //1:nb de colonnes

  filename = "raw_result.csv";
  for ( i = 0 ; i < n ; i++) {
    outtable2[i][0] = omega[i];
    outtable2[i][1] = 0;
  }

  file_maker(size, outtable2, filename);
  delete [] size;

  // ménage
  delete [] outtable;
  delete [] outtable2;
  delete [] omega;
  delete [] N;
  delete [] histogram;

}
