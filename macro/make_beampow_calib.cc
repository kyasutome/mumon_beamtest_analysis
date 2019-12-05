void make_beampow_calib()
{

  TF1 *linear = new TF1("linear", "pol1", 0, 20000);
  double input[4] = {4398, 8748, 26150, 43670};
  double output[4] = {1603, 3344, 10170, 16950};
  double slope;

  TGraph *gra = new TGraph(4, output, input);
  linear->SetParameters(0, 0);
  gra->Fit(linear);
  double calc_ctfactor = linear->GetParameter(1);
  double ct_time_range = 80*pow(10, -9);
  double dynamic_range = 2; //V
  //cout << "calc= " << calc_ctfactor << '\n';

  TCanvas *c1 = new TCanvas("c1", "c1", 1000, 600);
  //TCanvas *c2 = new TCanvas("c2", "c2", 1000, 600);

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
  
  TH1D *ct_current = new TH1D("ct_current", "", 100, 0, 1000);  
  int N = inputtree->GetEntries();
  for(int ientry = 0; ientry<N; ientry++)
    {
      inputtree->GetEntry(ientry);
      
      double ctcurr = integral[0]*dynamic_range*calc_ctfactor*ct_time_range/50/pow(2, 14) * pow(10, 12);
      //C (クーロン)
      cout << ctcurr << '\n';
      ct_current->Fill(ctcurr);
    }

  c1->cd();
  ct_current->Draw("");
  ct_current->SetTitle("CT charge;CT (pC);Events");

}
