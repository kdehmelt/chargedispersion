#include "aragorn.h"
#include "quink.C"
#include <iostream>
#include <TCanvas.h>
#include <TStopwatch.h>
#include <TFile.h>
#include <Riostream.h>

using namespace std;

double matpar [5] = {40, 50, 13, 40, 2000}; //Parameters of the materials and the detector/electronics

aragorn *aragorn::__instance=0;

aragorn::aragorn() {cout << "Their pace is quickening." << endl;}   //Just to confirm it runs correctly
void aragorn::Construct()
{
  if(TheQuinks.size()>0){cout<<"This setup has already been constructed.";}
  else
    {
      for(int j=hh;j<2*hh*rows;j=j+2*hh)
	{ //Creating all quinks, one row at at time and then moving down a row.
	  for(int i=hw;i<2*hw*columns;i=i+2*hw)
	    {
	      quink * newest =(new quink(double(i-hw),double(i+hw),double(j-hh),double(j+hh)));
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

void aragorn::SetChargeCloud(double a, double b) 
{
  a =0, b = 0;
  //eventually this function will hopefully
  // take some x and y position and turn it
  // into a circle of charge with a dense
  // center and diffuse radial charge.
  // for today however, it does nothing.
}

void aragorn::Event()
{
  int lxmax, lymax;
  double x0, y0, stSzX, stSzY; //x and y coordinate of charge cloud and stepsize for PRF
  ifstream in;
  in.open("prfinput.dat");//Form("%sbasic.dat",dir.Data()))
  /*
  cout << " Where should the charge cloud hit? (5 mm, 6 (9) mm for Dixit setup)" << endl;
  cout << " How many steps in x/y?" << endl;
  cout << " PRF Step-size in x/y-direction in mm?" << endl;

  cin >> x0 >> y0 >> lxmax >> lymax >> stSzX >> stSzY;
*/
  in >> x0 >> y0 >> lxmax >> lymax >> stSzX >> stSzY;
  cout << " The charge cloud will be at x0 = " << x0 << " and y0 = " << y0 << endl;
  cout << lxmax << " steps in x, " << lymax << " steps in y." << endl; 
  cout << " PRF Step-size in x/y-direction is " << stSzX << " / " << stSzY << endl;

  //TCanvas* c1 = new TCanvas("c1", "Readout", 800, 600);
  //c1->Divide(columns,rows);
  TStopwatch loopclock;
  loopclock.Start();
  bool endOfLoop = false;
  for(unsigned int i =1; i<=TheQuinks.size(); i++)
    {
      //c1->cd(i);
      TheQuinks[i-1]->Display(matpar, x0, y0, lxmax, lymax, stSzX, stSzY, i, endOfLoop);
      cout<< i <<" Pad(s) have been calculated for.\n";
    }
  loopclock.Stop();
  cout << endl; loopclock.Print(); cout << endl;
}
// This is just a function to make sure that the setup was constructed correctly
void aragorn::CheckPad(int n)
{
  TheQuinks[n]->Report();
}
