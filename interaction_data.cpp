#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

#include "interaction_data.h"

int initData(double *** data)
{
  if(loadData(data[0],"lib/Na_data.csv") == 0)
    cerr << "--- Sodium Data Loading : SUCCESS" << endl;
  else
    {cerr << "--- Sodium Data Loading : ERROR" << endl;
      return -1;}
  
  if(loadData(data[1],"lib/I_data.csv") == 0)
    cerr << "--- Iodine Data Loading : SUCCESS" << endl;
  else
    {cerr << "--- Iodine Data Loading : ERROR" << endl;
      return -1;}
  
  return 0;
}

int loadData(double ** dataArray, string dataPath)
{
  // Loading file
  ifstream dataFile(dataPath.c_str());

  if(!dataFile) 
    {cout<<"Error opening data file ("<< dataPath << ")" << endl;
      return -1;
    }

  int column = 0;
  int row = 0;
  
  // While not at the end of file
  while(!dataFile.eof())
    {
      string temp, line;
      stringstream linestream;

      // Extract next line
      dataFile >> line;;
      linestream << line;
      
      column = 0;
      
      // Read each value in line separated by ','
      while(getline(linestream,temp,','))
	{
	  // Store read value in dataArray
	  dataArray[column][row] = atof(temp.c_str());
	  column++;
	}
      row++;
    }
  
  return 0;
}
