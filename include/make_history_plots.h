#include <iostream>
#include <fstream>
#include <vector>

#include "TString.h"

using namespace std;

void make_filelist(vector<TString>*filelist)
{
  
  ifstream fin("./list/filelist.txt");

  cout << "analized file list......." << '\n';
  while(!fin.eof())
    {
      TString temp;
      fin >> temp;
      temp.Form("./process/%s.root", temp.Data());
      filelist->push_back(temp);      
    }

  filelist->pop_back();

  for(int i=0; i<filelist->size(); i++)
    {
      cout << "filename= " << filelist->at(i) << '\n';
    }

}
