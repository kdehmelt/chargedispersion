#include "quink.h"
#include <iostream>
#include <cstring>
#include "TCanvas.h"
#include "ConvoluteLoop.C"

using namespace std;

quink::quink(double Xl, double Xh,double Yl, double Yh)
{
  xl = Xl;
  xh = Xh;
  yl = Yl;
  yh = Yh;
}

void quink::Display(double t[5], double &x, double &y) //Start time, end time, sample interval, and position of charge cloud.
{
 vector<double> Readings;
 double relativepos [4];
 // creating the relative positions, taking the positions of the pad
 // and subtracting the position of the charge cloud hit
 relativepos[0] = (xl-x); 
 relativepos[1] = (xh-x); 
 relativepos[2] = (yl-y); 
 relativepos[3] = (yh-y);
 // Pass the array with all of the material constants
 // and the relative position to the convolution
 ConvoluteLoop(t,relativepos);
}
// This is just a function used to make sure it was constructed correctly.
void quink::Report()
{
  char name[40];
  sprintf(name,"(%g,%g) to (%g,%g)",xl,yl,xh,yh);
  cout<<name<<endl;
}
