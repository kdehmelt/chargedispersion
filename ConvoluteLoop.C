#include <TF1.h>
#include <TMath.h>
#include <TCanvas.h>
#include <TStopwatch.h>
#include <TPad.h>
#include <TFile.h>
#include <TH1.h>
#include "Math/Integrator.h"
#include "RLAfuncs.cxx"
#include "Qfuncs.cxx"

TF1 *fRLA, *fQ, *f_12;

double Func_1(double *, double *);// "detector response" function
double Func_2(double *, double *);// Q-function (charge dispersion)

double Func_12( double *, double *);// Multiplication: RLA*Q
//double Conv_12( double *, double *);// cumConvolution: [RLA*Q](t)

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
double Func_1(double *t, double *par) // The detector-response function
{
  double result;
  result = RLAfuncs::RLAconv(t[0], par[0], par[1], par[2], par[3]);
  //result = Qfuncs::TestBox(t[0]);
  return result;
}
//==============
double Func_2(double *t, double *par) // The charge dispersion function
{
  double result;
  result = Qfuncs::PadRect(t[0], par[0], par[1], par[2], par[3], par[4]);
  //result = Qfuncs::TestTri(t[0]);
  return result;
}
//==============
double Func_12( double *t, double *par ) // The multiplication of both functions
{
  return fRLA->Eval(t[0])*fQ->Eval( par[0] - t[0] );
}
//=============
/*
All I've done here compared to the original code is to 
get rid of anything that graphed the Qfuncs or RLA response
and modify the input so it takes two arrays instead of a long
list of ints and doubles. The only other difference is that I
am naming each histogram for clarity, using it's position.
Other than that, this is exactly the convolution code that 
Klaus has posted on the skipper physics link.
*/

void ConvoluteLoop(double * maspar, double * relativepos, char name[], char filename[], char title[], bool newFile)
{
  //unpacking the master parameter array. These are set in the parent class.
  TStopwatch clock;
  clock.Start();
  double R = maspar[5]; //75 micrometers in PowerPoint
  if(newFile==true){TFile f(filename,"RECREATE");}
  TFile f(filename,"UPDATE");
  int n = int(maspar[0]+.1);
  double tR = maspar[1];
  double sL = maspar[2];
  double tr = maspar[3];
  double tf = maspar[4];
  //unpacking the relative positions. Each pad sends these individually.
  double xl = relativepos[0];
  double xh = relativepos[1]; 
  double yl = relativepos[2];
  double yh = relativepos[3];
  double tmin = 0; double tmax = 2000;//2000;//, tc = 25; // in ns
  fRLA = new TF1("fRLA", Func_1, tmin, tmax, 4);// 4 params: t_R, sigmaL, t_r, t_f;
  fQ = new TF1("fQ", Func_2, tmin, tmax, 5);// 5 params: xl, xh, yl, yh, w
  // To be adjusted
  fRLA->SetParameters(tR, sL, tr, tf);//(double t_R, sigmaL, t_r, t_f)=(50.,13.,40.,2000.) all in ns
  fQ->SetParameters(xl, xh, yl, yh, R);//(xl, xh, yl, yh)=(-1, 1, -3, 3) all in mm
  fRLA->SetNpx(n);
  fQ->SetNpx(n);
  double tcplus = 0;
  double dt = (tmax-tmin)/double(n);
  TH1D *cumConv = new TH1D(name,title, n, tmin, tmax);
  cumConv->Reset();
  TH1D *cumInt = new TH1D("cumInt", "", n, tmin, tmax);
  cumInt->Reset();
  //~~Loop over T~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  for (int iT = 1; iT <= n; ++iT)
    {
      cumInt->Reset();
      tcplus = tmin + dt*iT; 
      f_12 = new TF1("f_12", Func_12, tmin, tmax, 1);
      // To be adjusted
      f_12->SetParameter(0, tcplus);// time parameter
      f_12->SetNpx(n);

      double tt = 0;
      double maxInt = 0;
      //~~Loop over t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
      for (int it = 1; it <= n; ++it)
  {
    tt = tmin + dt*it; 
    cumInt->SetBinContent(it, f_12->Integral(tmin,tt));

    if(f_12->Integral(tmin,tt) > maxInt)
      {
        maxInt = f_12->Integral(tmin,tt);
      }
  }
      
      cumConv->SetBinContent(iT, maxInt);//cumInt->GetBinContent(n)); WE ARE HERE
    }
  cumConv->GetXaxis()->SetTitle("Time in ns");
  cumConv->Write();
  delete cumConv;
  delete cumInt;
  cumConv = NULL;
  cumInt = NULL;
  f.Close();
  clock.Stop();
  cout << " Overall time: "; clock.Print(); cout << endl;
}
