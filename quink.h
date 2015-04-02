#ifndef __quink_H__
#define __quink_H__


//
//  Hello EIC Fans:
//
//    Welcome to quink. 
//


#include <vector>
#include <iostream>
using namespace std;


class quink
{
 protected:
  double xh,xl,yh,yl;
 public:
  quink(double, double, double, double);  
  virtual ~quink() {}
  /*
  double Getxl(){return xl;}
  double Getxh(){return xh;}
  double Getyl(){return yl;}
  double Getyh(){return yh;}
*/
  void Display(double t[5], double &x, double &y, int &ix, int &iy, double &sX, double &sY, unsigned int &i, bool &endOfLoop);
  void Report();
  
};

#endif /* __quink_H__ */
