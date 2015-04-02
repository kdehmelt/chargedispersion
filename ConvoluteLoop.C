#include <TF1.h>
#include <TMath.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TPad.h>
#include <TFile.h>
#include <TStopwatch.h>
#include <TSystem.h>
#include "Math/Integrator.h"
#include "RLAfuncs.cxx"
#include "Qfuncs.cxx"

//TList* hList = new TList();      // list of histograms to store
TDatime now;
//TFile* outfile = new TFile(Form("PRF_all_%i.root",now.Convert()), "RECREATE");
TFile* outfile = new TFile("PRF_all.root", "RECREATE");
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
  result = Qfuncs::PadRect(t[0], par[0], par[1], par[2], par[3]);
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

void ConvoluteLoop(double * maspar, double * relativepos, bool endOfLoop)
{
  TStopwatch clock;
  clock.Start();
  //unpacking the master parameter array. These are set in the parent class.
  double w = 0.25;
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
  unsigned int li = relativepos[4];
  unsigned int lx = relativepos[5];
  unsigned int ly = relativepos[6];
  double x0 = relativepos[7];
  double y0 = relativepos[8];

  char newname[40];
  char histofilename[40];
  char logfilename[40];
  sprintf(newname,"PRF_li_%i_lx_%i_ly_%i",li, lx, ly);
  //TFile* outfile = new TFile(Form("%s.root",newname), "RECREATE");
  double tmin = 0; double tmax = 2000;//, tc = 25; // in ns
  fRLA = new TF1("fRLA", Func_1, tmin, tmax, 4);// 4 params: t_R, sigmaL, t_r, t_f;
  fQ = new TF1("fQ", Func_2, tmin, tmax, 5);// 5 params: xl, xh, yl, yh, w
  // To be adjusted
  fRLA->SetParameters(tR, sL, tr, tf);//(double t_R, sigmaL, t_r, t_f)=(50.,13.,40.,2000.) all in ns
  fQ->SetParameters(xl, xh, yl, yh, w);//(xl, xh, yl, yh)=(-1, 1, -3, 3) all in mm
  fRLA->SetNpx(n);
  fQ->SetNpx(n);
  double tcplus = 0;
  double dt = (tmax-tmin)/double(n);
  cout << "dt is " << dt << " ns" << endl;
  char name[80];
  sprintf(name,"(%2.2f,%2.2f) to (%2.2f,%2.2f) with chg-ctr at (%2.2f,%2.2f)",xl,yl,xh,yh,x0,y0);
  TH1D *cumConv = new TH1D("Signal",name, n, tmin, tmax);
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
      
      cumConv->SetBinContent(iT, maxInt);//cumInt->GetBinContent(n));
    }
  cumConv->GetXaxis()->SetTitle("Time in ns");
  cumConv->GetYaxis()->SetTitle("Charge in a.u.");
  //cumConv->Draw();
  cumConv->GetYaxis()->SetRangeUser(0,5000);
  cumConv->SetName(newname);
  //hList->Add(Form("%s",newname));

  cumConv->Write(newname,TObject::kWriteDelete);
  cumInt->Delete();
  if(endOfLoop) 
    {
      //hList->Write();      
      cout << "Closing histogram-file." << endl;
      outfile->Close();
      int timenow = now.Convert();
      sprintf(histofilename,"PRF_all_%i.root",timenow);
      sprintf(logfilename,"output_%i.log",timenow);
      gSystem->Rename("PRF_all.root",histofilename);//Form("PRF_all_%i.root",now.Convert()));
      gSystem->Rename("output.log",logfilename);//Form("output_%i.log",now.Convert()));
      cout << " Histos/logs in " << histofilename << "/" << logfilename << endl;
    }
  clock.Stop();
  cout << " Overall time: "; clock.Print(); cout << endl;
}
