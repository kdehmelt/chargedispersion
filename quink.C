#include "quink.h"
#include <iostream>
#include <cstring>
#include "TCanvas.h"
#include "ConvoluteLoop.C"

using namespace std;

quink::quink(double Xl, double Xh, double Yl, double Yh)
{
  xl = Xl;
  xh = Xh;
  yl = Yl;
  yh = Yh;
}

void quink::Display(double t[5], double &x0, double &y0, int &lxmax, int &lymax, double &stSzX, double &stSzY, unsigned int &li, bool &endOfLoop) //Start time, end time, sample interval info, and position of charge cloud.
{
 vector<double> Readings;
 double relativepos [9];// offsets for the pads from w.r.t. charge cloud center, plus where are we in the loop (li, lx, ly)
 // creating the relative positions, taking the positions of the pad
 // and subtracting the position of the charge cloud hit
 // int lxmax = 10, lymax = 2;// define the loop boundaries
 for(int lx = 0; lx <= lxmax/*20*/; lx++)// scan along x-axis of pad
    {
      for(int ly = 0; ly <= lymax/*5*/; ly++)// scan along y-axis of pad
	{
	  cout << " li, lx, ly -- " << li << " -- " << lx << " -- " << ly << endl;
	  relativepos[0] = (xl-(x0+lx*stSzX));//wrong brackets position fixed
	  relativepos[1] = (xh-(x0+lx*stSzX)); 
	  relativepos[2] = (yl-(y0+ly*stSzY)); 
	  relativepos[3] = (yh-(y0+ly*stSzY));
	  relativepos[4] = li;
	  relativepos[5] = lx;
	  relativepos[6] = ly;
	  relativepos[7] = x0;
	  relativepos[8] = y0;
	  cout << " relXl, relXh, relYl, relYh -- " << relativepos[0] << " -- " << relativepos[1] << " -- " << relativepos[2] << " -- " << relativepos[3] << endl;
	  // Pass the array with all of the material constants
	  // and the relative position to the convolution
	  if(lx == lxmax && ly == lymax && li == 6) endOfLoop = true;
	  ConvoluteLoop(t,relativepos,endOfLoop);
	}
    }
}
// This is just a function used to make sure it was constructed correctly.
void quink::Report()
{
  char name[40];
  sprintf(name,"(%2.2f,%2.2f) to (%2.2f,%2.2f)",xl,yl,xh,yh);
  cout<<name<<endl;
}
