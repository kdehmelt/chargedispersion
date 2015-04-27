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
  void ToFile(double t[5], double &x, double &y,char n[],char fn[], bool e);
  void Report();
  
};

#endif /* __quink_H__ */
