// @(#)Qfuncs:$Id$
// Authors: KD Jan-26-2015

/*************************************************************************
 * Copyright (C) None.                                                   *
 * All rights reserved.                                                  *
**************************************************************************/

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// Qfuncs                                                               //
//                                                                      //
// Single functions Q for various geometries and shapes,                //
// all as a function of t                                               //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include "Qfuncs.h"
#include "TMath.h"

using namespace TMath;

//______________________________________________________________________________
double Qfuncs::PadRect(double tt, double xl, double xh, double yl, double yh, double w)
{
  // Calculate dispersion of charge across 2-D resistive anode 
  double N = 8000;// in q_e, typical COMPASS GEM value
  double R = 2*530000;// Ohms per square
  double C = 0.21E-12;// 0.21pF/mm^2
  //double w = 250E-3;// in mm
  /*
  double tt = t[0];  
  double xl = par[0];//1;// in mm
  double xh = par[1];//3;// in mm
  double yl = par[2];//1;// in mm
  double yh = par[3];//7;// in mm
  */

  double Qpad;// = 1/Sqrt(4*t/(R*C)+2*Power(w,2));
  if(tt>0)
    {
      double S = Sqrt(4*(tt*Power(double(10),-9))/(R*C)+2*Power(w,2));
      double diffxErf = Erf(xh/S)-Erf(xl/S);
      double diffyErf = Erf(yh/S)-Erf(yl/S);      
      Qpad = N/4 * ( diffxErf*diffyErf);
    }
  else
    {
      Qpad = 0;
    }
  return Qpad;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
double Qfuncs::TestTri(double tt)
{
  double tri;
  if(tt>0&&tt<2)
    {
      tri = tt;
    }
  else if(tt>=2&&tt<4)
    {
      tri = 4 - tt;
    }
  else
    {
      tri = 0;
    }
  return tri;
}

double Qfuncs::TestBox(double tt)
{
  double box;
  if(tt>0&&tt<4)
    {
      box = 2;
    }
  else
    {
      box = 0;
    }
  return box;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
