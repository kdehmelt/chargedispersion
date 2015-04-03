// @(#)Qfuncs:$Id$
// Authors: KD Jan-26-2015

/*************************************************************************
 * Copyright (C) None.                                                   *
 * All rights reserved.                                                  *
**************************************************************************/

#ifndef __Qfuncs_H__
#define __Qfuncs_H__

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// Qfuncs                                                               //
//                                                                      //
// Single functions for charge dispersion as a function of time         //
// basically integrated geometries as they "see" induced signals        //
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

namespace Qfuncs {
  double PadRect(double tt=0, double xl=1, double xh=1, double yl=1, double yh=1, double w = 1);
  double TestBox(double tt=0);
  double TestTri(double tt=0);
}

#endif
