void make_history_plots_inrun()

{
  TCanvas *c1 = new TCanvas("c1", "c1", 1000, 600);
  TCanvas *c2 = new TCanvas("c2", "c2", 1000, 600);

  double pedestal[3];
  double rms[3];
  double peak[3];
  double integral[3];
  int entry;  

  TString filename = "../process/run_00060.root";
  TFile* inputfile = new TFile(filename, "read");
  TTree *inputtree = (TTree*)inputfile->Get("tree");
  inputtree->SetBranchAddress("entry", &entry);
  inputtree->SetBranchAddress("pedestal", pedestal);
  inputtree->SetBranchAddress("rms", rms);
  inputtree->SetBranchAddress("peak", peak);
  inputtree->SetBranchAddress("integral", integral);

  TH2D *history_emtovct = new TH2D("history_emtovct", "",
				   100, 0, 1000, 100, 0, 10000);
  TH2D *history_emtovsi = new TH2D("history_emtovsi", "",
				   100, 0, 1000, 100, 0, 10000);

  int N = inputtree->GetEntries();
  for(int ientry = 0; ientry<N; ientry++)
    {
      inputtree->GetEntry(ientry);
      double ratio_emt_ct;
      double ratio_emt_si;

      ratio_emt_ct = peak[2]/peak[0];
      ratio_emt_si = peak[1]/peak[0];
      //cout << "ratio_emt_ct= " << ratio_emt_ct << " ratio_emt_si= "
      //	   << ratio_emt_si << '\n';
      
      history_emtovct->Fill(ratio_emt_ct, entry);
      history_emtovsi->Fill(ratio_emt_si, entry);

    }

  c1->cd();
  history_emtovct->Draw("colz");

  c2->cd();
  history_emtovsi->Draw("colz");

}
