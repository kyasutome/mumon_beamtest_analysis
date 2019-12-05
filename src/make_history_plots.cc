#include <iostream>
#include <fstream>
#include <vector>

#include "TFile.h"
#include "TTree.h"
#include "TF1.h"
#include "TH2.h"
#include "TString.h"
#include "TCanvas.h"
#include "TApplication.h"

#include "make_history_plots.h"

using namespace std;

int main(int argc, char *argv[])
{

  TApplication app( "app", 0, 0, 0, 0 );

  TCanvas *c1 = new TCanvas("c1", "c1", 1000, 600);
  TCanvas *c2 = new TCanvas("c2", "c2", 1000, 600);

  TH2D *history_emtoverct = new TH2D("history_emtoverct", "", 100, 0, 10000, 100, 0, 10);
  TH2D *history_emtoversi = new TH2D("history_emtoversi", "", 100, 0, 10000, 100, 0, 10);
  
  double pedestal[3];
  double rms[3];
  double peak[3];
  double integral[3];
  int entry;
  int totalentry=0;
  
  TString filename;
  TFile *inputfile;
  TTree *inputtree;
  int nfile=0;

  vector<TString> filelist;
  make_filelist(&filelist);
  nfile = filelist.size();

  cout << "total number of files = " << nfile << '\n';

  for(int ifile=0; ifile<nfile; ifile++)
  //for(int ifile=0; ifile<0; ifile++)
    {
      filename = filelist.at(ifile);
      inputfile = new TFile(filename, "read");
      inputtree = (TTree*)inputfile->Get("tree");
      inputtree->SetBranchAddress("entry", &entry);
      inputtree->SetBranchAddress("pedestal", pedestal);
      inputtree->SetBranchAddress("rms", rms);
      inputtree->SetBranchAddress("peak", peak);
      inputtree->SetBranchAddress("integral", integral);      
      
      int N = inputtree->GetEntries();
      for(int ientry = 0; ientry<N; ientry++)
	{
	  inputtree->GetEntry(ientry);
	  double ratio_emt_ct;
	  double ratio_emt_si;
	  
	  ratio_emt_ct = peak[2]/peak[0];
	  ratio_emt_si = peak[1]/peak[0];

	  //cout << "entry= " << totalentry  << " ratio_emt_ct= " 
	  //    << ratio_emt_ct << " ratio_emt_si= " << ratio_emt_si  << '\n';
	  
	  history_emtoverct->Fill(totalentry, ratio_emt_ct);
	  history_emtoversi->Fill(totalentry, ratio_emt_si);	  
	  
	  totalentry++;
	}      

    }

  c1->cd();  
  history_emtoverct->Draw("colz");
  c2->cd();
  history_emtoversi->Draw("colz");

  c1->Update();
  c2->Update();

  app.Run();
 
  return 0;
}
