#include "file_maker.h"

int file_maker(int * size, double ** outtable, const string &filename)
{
  
  char *a=new char[filename.size()+1];
  a[filename.size()]=0;
  memcpy(a,filename.c_str(),filename.size());
  
  ofstream outfile(a, ios::out | ios::trunc); // ouverture en écriture avec effacement du fichier ouvert
  
  delete [] a;
  
  int i,j;
  
  if(outfile)
    {
      // outfile << "il y a " << size[1] << " lignes et " << size[2] << " colonnes" << endl;

      for(i=0 ; i<size[0] ; i++){
	outfile << outtable[i][0];
	for(j=1; j<size[1] ; j++){
	  outfile << ";" << outtable[i][j] ;
	}
	outfile << endl;
      }

      outfile.close();
    }
  else
    cerr << "Impossible d'ouvrir le fichier !" << endl;

  return 0;
}
