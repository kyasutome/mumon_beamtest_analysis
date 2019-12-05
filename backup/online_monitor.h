#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "TArc.h"

using namespace std;

void PlaySound(char *file)
{
  static char cmd[256];

  if (strlen(file) > 200) return;
  sprintf(cmd, "paplay %s &> /dev/null &", file);
  system(cmd);
}

bool checkFileExistence(const std::string& str)
{
  std::ifstream ifs(str);
  return ifs.is_open();
}

void find_latestdir(TString *filename, TString *runname, char rawdir[])
{
  struct stat st;
  char tempfile[256];
  char dummy1[256];
  char dummy2[256];
  //char dirname[256] = "./data2/";
  int latest_timestamp = 0;
  char latestdir[256];
  char temprun[256];
  DIR* dp=opendir(rawdir);
  sprintf(dummy1, "%s", rawdir);
  strcat(dummy1, "/./"); 
  sprintf(dummy2, "%s", rawdir);
  strcat(dummy2, "/../"); 
  //struct _finddata_t fdata;
  
  if (dp!=NULL)
    {
      struct dirent* dent;
      do{
        dent = readdir(dp);
	if (dent!=NULL)
          {
	    sprintf(tempfile, "%s/%s/", rawdir, dent->d_name);

	    if(strcmp(tempfile, dummy1)!=0)
	      {
		if(strcmp(tempfile, dummy2)!=0)		  
		  {
		    stat(tempfile, &st);
		    int timestamp = st.st_ctime;
		    //cout << tempfile << " " << timestamp << '\n';                                                                       
		    if(timestamp > latest_timestamp)
		      {
			latest_timestamp = timestamp;
			sprintf(temprun, "%s", dent->d_name);
			sprintf(latestdir, "%s", tempfile);
		      }
		  }
	      }
	  }
      }while(dent!=NULL);
      closedir(dp);
    }
  filename->Form("%s", latestdir);
  runname->Form("%s", temprun);
}

int getcurrentfiletime(TString filename)
{
  struct stat st;
  string file = filename.Data();
  stat(file.c_str(), &st);
  return st.st_ctime;
}

void readthrough(ifstream *file, int inum, const int num, int *used)
{

  int count=0;

  for(int i=0; i<2; i++)
    {
      double dummy;
      *file >> dummy;
    }


  for(int i=0; i<num; i++)
    {
      *file >> used[count];
      count++;
    }
}

int Sumcalc(int pedestal, int data[])
{
  int nsample = 2049;
  int sum=0;
  for(int i=0; i<nsample; i++)
    {
      sum += data[i] - pedestal;
    }
  return sum;
}

int Pedcalc(int startpoint, int endpoint, int data[])
{
  int sum=0;
  for(int i=startpoint; i<endpoint; i++)
    {
      sum += (double)data[i]/(endpoint-startpoint);
    }

  return sum;
}

void Fill_the_point(TH2D *hist, int x, int y, int dx, int dy)
{
  TBox *box = new TBox(x-dx, y-dy, x+dx, y+dy);
  box->SetFillColor(kRed);
  box->Draw("same");
}

