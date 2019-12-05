#include <iostream>
#include <fstream>

#include "TText.h"

using namespace std;

void WriteFitResult(double par_x[], double par_y[], bool warning[])
{
  TString texts_for_x1, texts_for_x2;
  TString texts_for_y1, texts_for_y2;
  double center = 3.5;
  int lowerlimit = 2;
  int upperlimit = 5;
  
  texts_for_x1.Form("Center X : %lf", par_x[1]);
  texts_for_x2.Form("Sigma X : %lf", par_x[2]);
  texts_for_y1.Form("Center Y : %lf", par_y[1]);
  texts_for_y2.Form("Sigma Y : %lf", par_y[2]);

  if(par_x[1] < lowerlimit || par_x[1] > upperlimit)
    {
      warning[0] = true;
    }

  if(par_y[1] < lowerlimit || par_y[1] > upperlimit)
    {
      warning[1] = true;
    }

  TText *t23_x1 = new TText(0.05, 0.8, texts_for_x1);
  t23_x1->SetTextSize(0.1);
  if(warning[0]) t23_x1->SetTextColor(kRed);
  t23_x1->Draw("");
  TText *t23_x2 = new TText(0.05, 0.65, texts_for_x2);
  t23_x2->SetTextSize(0.1);
  t23_x2->Draw("");
  TText *t23_y1 = new TText(0.05, 0.35, texts_for_y1);
  t23_y1->SetTextSize(0.1);
  if(warning[1]) t23_y1->SetTextColor(kRed);
  t23_y1->Draw("");
  TText *t23_y2 = new TText(0.05, 0.2, texts_for_y2);
  t23_y2->SetTextSize(0.1);
  t23_y2->Draw("");
}

// Det 0:CT, 1:Si, 2:EMT
void StabilityCheck(int det, int adcsum, bool warning[])
{
  int lowerlimit[3] = {pow(10, 5), pow(10, 5), pow(10, 5)};
  int upperlimit[3] = {pow(10, 7), pow(10, 7), pow(10, 7)};

  if(adcsum < lowerlimit[det] || adcsum > upperlimit[det])
    {
      warning[det] = true;
    }
}
