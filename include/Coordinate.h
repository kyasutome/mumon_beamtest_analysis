#ifndef _Dimension_C
#define _Dimension_C

#include <iostream>
#include <sstream>
#include <fstream>
#include "Dimension.h"

using namespace std;

Dimension::Dimension()
{
  TString pathtofile = "/home/parallels/Documents/MUMON-EMT/mumon-emt-beamtest/interface/make_profile/info/siarray.txt";
  ifstream fin(pathtofile.Data());
  int temp[5];

  for(int i=0; i<32; i++)
    {
      fin >> temp[0] >> temp[1] >> temp[2] >> temp[3] >> temp[4];

      channelmap[0][0][i] = temp[1]; //ax
      channelmap[0][1][i] = temp[2]; //ay
      channelmap[1][0][i] = temp[3]; //bx
      channelmap[1][1][i] = temp[4]; //by
    }

  fin.close();
  cout << "Read Channel map" << '\n';
}

Dimension::~Dimension(){
}

bool Dimension::get_array_coordinate(int filenum, int channel, int *x, int *y)
{
  *x = channelmap[filenum][0][channel];
  *y = channelmap[filenum][1][channel];

  return true;
}

#endif
