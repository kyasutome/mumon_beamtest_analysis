#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <vector>
#include <cmath>
#include "TH1.h"
#include "TH2.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TF1.h"
#include "TString.h"
#include "TTree.h"

#include "qualitycheck.h"

//#define dataout(dt) std::cout<<#dt"="<<dt<<std::endl;
using namespace std;

int main(int argc, char *argv[]){

  int run = 0;
  int daqid = 0;

  int c = -1;
  while((c = getopt(argc, argv, "r:d:")) != -1)
    {
      switch(c){
      case 'r':
	run = atoi(optarg);
	break;
      case 'd':
	daqid = atoi(optarg);
	break;
      }
    }

  if(daqid==0 || run==0)
    {
      cout << "!!! usage !!!" << '\n';
      cout << "-r : input a run number" << '\n';
      cout << "-d : input a ID for daqpc (1, 2, 3)" << '\n';
      exit(0);
    }
	
  int startbin = 600;
  int endbin = 900;
  int binnum = endbin - startbin;
  
  const int data = 2050; //number of samples
  const int nch = 3;
  const int range = 17000;

  int chnum;
  int channel[nch];
  int num[nch] = {};
  int entry[nch] = {};
  double array[nch][data] = {};  //waveform

  //for pedestal calculation
  double pedestal[nch];
  //int pedtime = 200;
  TF1 *f;
  double sigma[nch], rms[nch];
 
  //for charge calculation
  double integral[nch];
  double peak[nch];

  //TFile to save TTree
  TString ofn = Form("./process/run_000%d.root", run);
  TFile *fout = new TFile(ofn, "recreate");

  //define TTree
  TTree * tree = new TTree("tree", "");

  //define branches
  tree->Branch("chnum", &chnum, "chnum/I");
  tree->Branch("channel", channel, "channel[3]/I");
  tree->Branch("entry", &entry, "entry/I");
  tree->Branch("binnum", &binnum, "binnum/I");
  tree->Branch("array", array, "array[3][2050]/D");  //waveform
  tree->Branch("pedestal", pedestal, "pedestal[3]/D"); //pedestal
  tree->Branch("rms", rms, "rms[3]/D");
  tree->Branch("peak", peak, "peak[3]/D"); 
  tree->Branch("integral", integral, "integral[3]/D");

  //input filename
  TString filename[nch];
  for(int ich = 0; ich < nch; ich++){
    filename[ich] = Form("./rawdata/data/daqpc%d/run000%d/run000%d_ch%i.txt", daqid, run, run, ich);
    }

  ifstream fin[nch];

    for(int ich = 0; ich < nch; ich++){
      fin[ich].open(filename[ich]);
    }

    //    while(!fin[2].eof()){
    //for ( int itest = 0; itest < 5; itest++ ) {

    
  while ( ! fin[ 0 ].eof() 
       && ! fin[ 1 ].eof() 
       && ! fin[ 2 ].eof() ) 
    {
    
      for(int ich = 0; ich < nch; ich++){
      double dummy = 0.; 
      double value = 0.;
      double charge = 0;
      double min = 17000;

      //TH1D* waveH = new TH1D(Form("wave_ch%d_%d", ich, num[ich]), "wave", data, 0, data);
      TH1D* pedeHist = new TH1D(Form("h_ch%d_%d", ich, num[ich]), "pedestal", range, 0, range);
      
      for(int i = 0; i < 2; i++){
        fin[ich] >> dummy;
      }

      for(int i = 0; i < startbin; i++){
        fin[ich] >> dummy;
	array[ich][i] = dummy;
      }      

      for(int i = startbin; i < endbin; i++){  //where signal is
	fin[ich] >> value;
	array[ich][i] = value;
	charge = charge + value;
	

	if(value < min){
	  min = value;
	}

      }

      for(int i = endbin; i < data; i++){
	fin[ich] >> value;
	array[ich][i] = value;
	pedeHist->Fill(value);
      }

      if(pedeHist->Fit("gaus","Q",0, range) == -1)
	{
	  delete pedeHist;
	  cout << "entry " << num[0] << '\n';
	  cout << "Fit failed. This event is skipped." << '\n';
	  continue;
	}

      f = pedeHist->GetFunction("gaus");
      pedestal[ich] = f->GetParameter(1);
      sigma[ich] = f->GetParameter(2);
      delete pedeHist;

      if(pedcheck(pedestal[ich]))
	{
	  peak[ich] = abs(min - pedestal[ich]);
	  integral[ich] = abs(charge - pedestal[ich]*binnum);
	  rms[ich] = sigma[ich];
	}
      if(!pedcheck(pedestal[ich]))
	{
	  pedestal[ich] = -1;
	  peak[ich] = -1;
	  integral[ich] = -1;
	  rms[ich] = -1;	  
	}      


      entry[ich] = num[ich];
      num[ich] = num[ich] + 1;
      channel[ich] = ich;

      } //loop ich

      if(num[0]%100==0) cout << "processing : " << num[0] << '\n';
      tree->Fill();
    }//while loop
  
  fout->cd();
  tree->Write();
  fout->Close();

  cout << "done!" << '\n';
 }

