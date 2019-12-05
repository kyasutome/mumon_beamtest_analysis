#include <iostream>
#include <fstream>

using namespace std;

bool pedcheck(double pedestal)
{
  double lowcut_ped = 8000;
  double highcut_ped = 8500;
  bool temp = false;
  if(pedestal>lowcut_ped && pedestal<highcut_ped)
    {
      temp = true;
    }
  else temp = false;

  //cout << "true? = " << temp << '\n';

  return temp;  
}
