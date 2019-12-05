void make_correlation_emt_ct()

{

  TCanvas *c1 = new TCanvas("c1", "c1", 1000, 600);
  TCanvas *c2 = new TCanvas("c2", "c2", 1000, 600);
  TCanvas *c3 = new TCanvas("c3", "c3", 1000, 600);

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

  TH2D *corr_integral_emt_ct = new TH2D("corr_integral_emt_ct", "",
				    100, 0, 2000, 100, 0, 100000);
  TH2D *corr_integral_emt_si = new TH2D("corr_integral_emt_si", "",
				    100, 0, 1000, 100, 0, 100000);
  TH2D *corr_peak_emt_si = new TH2D("corr_peak_emt_si", "",
				    100, 0, 2000, 100, 0, 2000);

    int N = inputtree->GetEntries();
    for(int ientry = 0; ientry<N; ientry++)
      {
	inputtree->GetEntry(ientry);       
	corr_integral_emt_ct->Fill(integral[0], integral[2]);
	corr_integral_emt_si->Fill(integral[1], integral[2]);	
	corr_peak_emt_si->Fill(peak[1], peak[2]);
      }

  c1->cd();
  corr_integral_emt_ct->Draw("colz");
  c2->cd();
  corr_integral_emt_si->Draw("colz");
  c3->cd();
  corr_peak_emt_si->Draw("colz");

}
