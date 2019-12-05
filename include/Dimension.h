#ifndef _Dimension_H
#define _Dimension_H

#include<iostream>
#include<sstream>
#include<fstream>

using namespace std;

class Dimension{
 private:
  int channelmap[2][2][32];

 public:
  Dimension();
  ~Dimension();

  bool get_array_coordinate(int filenum, int channel, int *x, int *y);
  
};

#endif
