#include "aragorn.h"
#include "quink.C"
#include <iostream>
#include <TCanvas.h>
#include <TStopwatch.h>
#include <TSystem.h>
#include <fstream>
#include <TFile.h>
#include <TLatex.h>

using namespace std;

double matpar [6] = {40, 60, 13, 40, 2000, 0}; //Parameters of the materials and the detector
TDatime now;

float aragorn::hw;
float aragorn::hh;
int aragorn::rows;
int aragorn::columns;

aragorn *aragorn::__instance=0;

aragorn::aragorn() {cout << "Their pace is quickening." << endl;}   //Just to confirm it runs correctly

void aragorn::Construct()
{
  ifstream in;
  in.open("Construct.dat");
  int c,r;
  double a,b;
  in>>a>>b>>c>>r;
  Sethw(a);
  Sethh(b);
  Setcol(c);
  Setrow(r);
  if(TheQuinks.size()>0){cout<<"This setup has already been constructed.";}
  else
  {
   for(int j=1;j<=2*rows;j+=2)                         
   {                           //Creating all quinks, one row at at time and then moving down a row.
     for(int i=1;i<=2*columns;i+=2)
     {
       quink * newest =(new quink(double(i*hw-hw),double(i*hw+hw),double(j*hh-hh),double(j*hh+hh)));
       TheQuinks.push_back(newest);
     }
   }
   cout<<"Take some rest. These borders are well protected."<<endl;
  }
}

void aragorn::Report()
{
  cout << "The number of Quinks is: ";
  cout << TheQuinks.size()<<endl;
}

void aragorn::SetChargeCloud(double a,double b) 
{
  // eventually this function will hopefully
  // take some x and y position and turn it
  // into a circle of charge with a dense
  // center and diffuse radial charge.
  // for today however, it does nothing.
}

// This is just a function to make sure that the setup was constructed correctly
void aragorn::CheckPad(int n)
{
  if(n>TheQuinks.size()-1){cout<<"This is not a valid pad number.";}
  else if (n<0){cout<<"This is not a valid pad number";}
  else{TheQuinks[n]->Report();}
}

void aragorn::Observe()
{
  int n = 7;
  vector < vector<double> > values(n+1);
  int step = 40/(n); //tmax divided by the number of time samples
  TH1F * h1 = new TH1F();
  char buffer [50];
  TCanvas * c1 = new TCanvas("c1","Progression of Charge");
  //TFile f("C:\\Users\\Overlord\\Desktop\\Programs\\Research\\ChargeDiv\\PRF\\PRFData3.root");
  TFile f("C:\\root_v5.34.25\\macros\\SmallPads.root");
  for (int i = 0; i <= n; ++i)
  {
    for (int k = 1; k < TheQuinks.size()+1; ++k)
    {
      sprintf(buffer,"Pad_li_%i",k);
      h1 = (TH1F*)f.Get(buffer);
      values[i].push_back(h1->GetBinContent(i*step+1)); //Value at a time i(index)*n(step size)
      delete(h1);
    }
  }
  c1->Divide(4,2); //The product of these need to be the n value +1;
  double max;
  double myval;
  for (int i = 0; i <= n; ++i)
  {
    max = abs(values[i][12]);
    c1->cd(i+1);
    gPad->Divide(columns,rows,0,0);
    for (int j = 0; j < values[i].size(); ++j)
    {
      gPad->cd(j+1);
      myval = abs(values[i][j]);
      if(myval>.95*max){gPad->SetFillColor(kRed);}
      else if((myval<.95*max)&&(myval>=.5*max)){gPad->SetFillColor(kRed+1);}
      else if((myval<.5*max)&&(myval>=.3*max)){gPad->SetFillColor(kRed+2);}
      else if((myval<.3*max)&&(myval>=.1*max)){gPad->SetFillColor(kRed+3);}
      else if((myval<.1*max)&&(myval>=.01*max)){gPad->SetFillColor(kRed+4);}
      else {gPad->SetFillColor(kBlack);}
      gPad->Draw();
      c1->cd(i+1);
    }
  }
}

void aragorn::SingleEvent()
{
  ifstream in;
  in.open("Input.dat");
  in.clear();
  double x1,y1;
  in>>x1>>y1;
  in.close();
  char name[40];
  bool newFile = true;
  char filename[40];
  int timenow=now.Convert();
  sprintf(filename,"Single_%i.root",timenow);
  for (int j = 0; j<TheQuinks.size(); ++j)
  {
    if(j==1){newFile=false;}
    sprintf(name,"Pad_li_%i",j+1);
    TheQuinks[j]->ToFile(matpar, x1, y1, name, filename, newFile);
    cout<<"Pad "<<j+1<<" Calculation Complete."<<endl;
  }
}

void aragorn::MakePRF()
{
  ifstream in;
  in.open("Input.dat");
  double x1,y1,stepx,stepy,xtemp,ytemp;
  int xev,yev;
  in>>x1>>y1>>stepx>>stepy>>xev>>yev;
  in.close();
  char name[40];
  char filename[40];
  bool newFile = true;
  int timenow=now.Convert();
  sprintf(filename,"PRF_%i.root",timenow);
  TStopwatch loopclock;
  loopclock.Start();
  for(int j=0;j<yev;++j)
  {
    ytemp=y1+j*stepy;
    for(int i=0;i<xev;++i)
    {
      xtemp=x1+i*stepx;
      for (int k = 0; k<TheQuinks.size(); ++k)
      {
        if(k==1){newFile=false;}
        sprintf(name,"PRF_li_%i_lx_%i_ly_%i",k+1,i,j);
        TheQuinks[k]->ToFile(matpar, xtemp, ytemp, name, filename, newFile);
      }
      cout<<i+1<<" x-event done."<<endl;
    }
  }
  loopclock.Stop();
  cout << endl; loopclock.Print(); cout << endl;
}

void aragorn::VaryResistance()
{
  ifstream in;
  in.open("Input.dat");
  double x1,y1,stepx,stepy,xtemp,ytemp,r1,stepr;
  int xev,yev,rev;
  in>>x1>>y1>>stepx>>stepy>>xev>>yev>>r1>>stepr>>rev;
  in.close();
  cout<<"R start "<<r1<<" step size "<<stepr<<" number of events "<<rev<<endl;
  cin.get();
  char name[40];
  char filename[40];
  bool newFile = true;
  int timenow=now.Convert();
  sprintf(filename,"ResistorsVariation_%i.root",timenow);
  TStopwatch loopclock;
  loopclock.Start();
for (int r = 0; r <rev; ++r)
{
  matpar[5] = 1000*(r1+r*stepr);
  cout<<" Resistance for this run is "<<matpar[5]<<endl;
  for(int j=0;j<yev;++j)
  {
    ytemp=y1+j*stepy;
    for(int i=0;i<xev;++i)
    {
      xtemp=x1+i*stepx;
      for (int k = 0; k<TheQuinks.size(); ++k)
      {
        if(k==1){newFile=false;}
        sprintf(name,"PRF_li_%i_lx_%i_ly_%i",k+1,i,j);
        TheQuinks[k]->ToFile(matpar, xtemp, ytemp, name, filename, newFile);
      }
      cout<<i+1<<" x-event done."<<endl;
    }
  }
}
  loopclock.Stop();
  cout << endl; loopclock.Print(); cout << endl;
}

void aragorn::Examine(vector< vector<double> > x)
{
  for(int i=0;i<x.size();i++)
  {
    for(int j=0;j<x[i].size();j++)
    {
      cout<<x[i][j]<<" ";
    }
    cout<<endl;
  }
}
