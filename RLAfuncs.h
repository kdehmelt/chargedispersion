// @(#)RLAfuncs:$Id$
// Authors: KD Jan-26-2015

/*************************************************************************
 * Copyright (C) None.                                                   *
 * All rights reserved.                                                  *
**************************************************************************/

#ifndef __RLAfuncs_H__
#define __RLAfuncs_H__

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// RLAfuncs                                                             //
//                                                                      //
// Single functions R, L, A -> all as a function of t                   //
// RLA analytical convolution                                           //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

/*
#ifndef ROOT_Rtypes
#include "Rtypes.h"
#endif
#ifndef ROOT_TMathBase
#include "TMathBase.h"
#endif

#include "TError.h"
#include <algorithm>
#include <limits>
#include <cmath>
*/

namespace RLAfuncs {
  double Rfunc(double *t, double *par);
  double Lfunc(double *t, double *par);
  double Afunc(double *t, double *par);
  double RLAconv(double tt=0, double t_R=1, double sigmaL=1, double t_r=1, double t_f=1);//double *t, double *par)//double *t, double *par);
}

#endif
