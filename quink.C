#include "quink.h"
#include <iostream>
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

// This is just a function used to make sure it was constructed correctly.
void quink::Report()
{
  char name[40];
  sprintf(name,"(%2.2f,%2.2f) to (%2.2f,%2.2f)",xl,yl,xh,yh);
  cout<<name<<endl;
}

void quink::ToFile(double t[5], double &x, double &y, char n[], char fn[], bool newFile)
{
 double relativepos [4];
 // creating the relative positions, taking the positions of the pad
 // and subtracting the position of the charge cloud hit
 relativepos[0] = (xl-x); 
 relativepos[1] = (xh-x); 
 relativepos[2] = (yl-y); 
 relativepos[3] = (yh-y);
 char title[80];
 sprintf(title,"(%2.2f,%2.2f) to (%2.2f,%2.2f) with chg-ctr at (%2.2f,%2.2f)",relativepos[0],relativepos[1],relativepos[2],relativepos[3],x,y);
 // Pass the array with all of the material constants
 // and the relative position to the convolution
 ConvoluteLoop(t,relativepos,n,fn,title,newFile);
}
