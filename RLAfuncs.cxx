// @(#)RLAfuncs:$Id$
// Authors: KD Jan-26-2015

/*************************************************************************
 * Copyright (C) None.                                                   *
 * All rights reserved.                                                  *
**************************************************************************/

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// RLAfuncs                                                             //
//                                                                      //
// Single functions R, L, A -> all as a function of t                   //
// RLA analytical convolution                                           //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include "RLAfuncs.h"
#include "TMath.h"
#include <iostream>
using namespace TMath;

//______________________________________________________________________________
double RLAfuncs::Rfunc(double *t, double *par)
{
   // Calculate rise time function
  //double t_R, sigmaL, t_r, t_f;//sigmaL in ns: 50.,13.,40.,2000.
  double R;
  double tt = t[0];  
  double t_R = par[0];
  
  if(tt<=0)
    {
      R = 0;
    }
  else if(tt>0 && tt<t_R)
    {
      R = tt/t_R;
    }
  else
    {
      R =1;
    }
  return R;
}
//______________________________________________________________________________
double RLAfuncs::Lfunc(double *t, double *par)
{
  //double sigmaL, t_R, t_r, t_f;//sigmaL in ns
  double tt = t[0];
  double sigmaL = par[1];
  double L = 1/(sigmaL*Sqrt(2*Pi()))*Exp(-Power(tt/sigmaL,2)/2);
  return L;
}
//______________________________________________________________________________
double RLAfuncs::Afunc(double *t, double *par)
{
  //double sigmaL, t_R, t_r, t_f;//sigmaL in ns
  double A = 0;
  double tt = t[0];  
  double t_r = par[2];
  double t_f = par[3];
  if(tt<=0)
    {
      A = 0;
    }
  else if(tt > 0)
    {
      A = Exp(-tt/t_f)*(1-Exp(-tt/t_r));
    }
  return A;
}
//______________________________________________________________________________
double RLAfuncs::RLAconv( double tt, double t_R, double sigmaL, double t_r, double t_f) //double *t, double *par)
{
  //double sigmaL, t_R, t_r, t_f
  /*
  double tt = t[0];  
  double t_R = par[0];
  double sigmaL = par[1];
  double t_r = par[2];
  double t_f = par[3];
  */
  double a = 1/t_f;
  double b = 1/t_f + 1/t_r;
  double twotR = 2*t_R;
  double sLsq2 = sigmaL*sqrt(double(2));
  double aExp = Exp(Power(sigmaL*a,2)/2-a*tt);
  double bExp = Exp(Power(sigmaL*b,2)/2-b*tt);
  double aErf = Erf((tt-t_R-Power(sigmaL,2)*a)/sLsq2);
  double bErf = Erf((tt-t_R-Power(sigmaL,2)*b)/sLsq2);
  //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
  double summ1RLA = aExp*(aErf+1);
  double summ2RLA = bExp*(bErf+1);
  double summ3RLA = aExp*Exp(a*t_R)*(aErf+1);
  double summ4RLA = bExp*Exp(b*t_R)*(bErf+1);
  double summ5RLA = aExp*(Erf((tt-Power(sigmaL,2)*a)/sLsq2)-aErf);
  double summ6RLA = bExp*(Erf((tt-Power(sigmaL,2)*b)/sLsq2)-bErf);
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  double RLA = (summ1RLA - summ2RLA - summ3RLA + summ4RLA + summ5RLA - summ6RLA)/(twotR);  

  return RLA;
}



  // double summ1RLA = aExp*(aErf+1);
  // double summ2RLA = bExp*(bErf+1);
  // double summ3RLA = aExp*Exp(a*t_R)*(Erf((tt-twotR-Power(sigmaL,2)*a)/sLsq2)+1);
  // double summ4RLA = bExp*Exp(b*t_R)*(Erf((tt-twotR-Power(sigmaL,2)*b)/sLsq2)+1);
  // double summ5RLA = aExp*(Erf((tt-Power(sigmaL,2)*a)/sLsq2)+aErf);
  // double summ6RLA = bExp*(Erf((tt-Power(sigmaL,2)*b)/sLsq2)+bErf);
  // double RLA = (summ1RLA - summ2RLA + summ3RLA - summ4RLA + summ5RLA - summ6RLA)/(twotR); 