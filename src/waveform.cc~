// headers
//
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
//
#include "TROOT.h"
#include "TH1.h"
#include "TFile.h"
#include "TTree.h"
#include "TApplication.h"
#include "TCanvas.h"
#include "TString.h"
#include "TStyle.h"
#include "TLegend.h"

using namespace std;


int main( int argc, char* argv[] )
{
  // input file and branch structure 
  //
  TFile* infile = new TFile( argv[ 1 ] ); 
  const int detector = atoi( argv[ 2 ] ); 
    // [1] CT, [2] Si, [3] EMT
  const int nevent = atoi( argv[ 3 ] ); // event number
  //
  TTree* tree = (TTree*)infile->Get( "tree" );
  Int_t entry;
  tree->SetBranchAddress( "entry", &entry );
  Double_t array[3][2050];
  tree->SetBranchAddress( "array", array );
  
  // output drawing
  // 
  TApplication app( "app", 0, 0, 0, 0 );
  TCanvas* canvas = new TCanvas( "canvas", "canvas", 1 );
  gPad->SetLeftMargin( 0.11 );
  gPad->SetRightMargin( 0.05 );
  TH1D* hist = new TH1D( "", "", 2050, 0, 2050 );
  hist->SetXTitle( "Sample (4 ns/sample)" );
  hist->SetYTitle( "ADC" );
  hist->GetXaxis()->SetLabelSize( 0.03 );
  hist->GetYaxis()->SetLabelSize( 0.03 );
  hist->SetLineColor(2);
  
  // process
  // 
  Int_t nentry = tree->GetEntries();
  for ( Int_t ientry = 0; ientry < nentry; ientry++ )
  {
    if ( ientry != nevent ) continue; 
    tree->GetEntry( ientry );
    // 

    if ( detector == 1 ) {       // CT 
      for ( int i = 0; i < 2050; i++ ) {  
        hist->Fill( i, array[1][i] );
      }
    }
    else if ( detector == 2 ) {  // Si  
      for ( int i = 0; i < 2050; i++ ) {  
        hist->Fill( i, array[2][i] );
      }
    }
    else if ( detector == 3 ) {  // EMT 
      for ( int i = 0; i < 2050; i++ ) {  
        hist->Fill( i, array[3][i] );
      }
    }
  }//loop ientry
   

  // drawing 
  //
  gStyle->SetOptStat( 0 );
  gStyle->SetGridStyle( 3 );
  gStyle->SetGridWidth( 1 );
  canvas->SetGridx( 1 );
  canvas->SetGridy( 1 );
  //
  hist->Draw("hist");
  canvas->Update();

  app.Run();

  return 0;
}


