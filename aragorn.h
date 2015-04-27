#ifndef __aragorn_H__
#define __aragorn_H__


//
//  Hello EIC Fans:
//
//    Welcome to aragorn.  Aragorn is the Tracker of the Ring Bearer.
//
//
//                                                SAZ, MB, & TKH
//                                                2-27-2013
//

#include <vector>

class quink;

class aragorn
{
 private:
  static float hw;    //half of the width of each pad
  static float hh;    //half of the height of each pad
  static int columns; //How many pads in a row
  static int rows; // How many pads in each column
 public:
  static aragorn* instance()
  {
    if (__instance) return __instance;
    __instance = new aragorn();
    return __instance;
  }
  virtual ~aragorn() {}

  std::vector <quink *> TheQuinks;
  void Sethw(double a){hw=a;}
  void Sethh(double b){hh=b;}
  void Setrow(int r){rows=r;}
  void Setcol(int c){columns=c;}
  void Report();
  void Construct(); //
  void SingleEvent();
  void SetChargeCloud(double,double);
  void Observe();
  void CheckPad(int);
  void MakePRF();
  void VaryResistance();
  void Examine(vector< vector<double> >);
  aragorn();
  static aragorn *__instance;

};

#endif /* __aragorn_H__ */
