#include "aragorn.h"
#include "quink.C"
#include <iostream>
#include "TCanvas.h"

using namespace std;

double matpar [5] = {30, 60, 13, 40, 2000}; //Parameters of the materiasl and the detector

aragorn *aragorn::__instance=0;

aragorn::aragorn() {cout << "Their pace is quickening." << endl;}   //Just to confirm it runs correctly

/* NONE OF THIS IS CORRECT ANYMORE, BUT I WILL FIX IT SOON
The following is an example of how the quink array would look, with the quinks numbered as if they have already
correctly been associated with each other for x and y equal to 4:
                                              On top is electrode 0
                                             ------------------------- 
                                           | 42  43 44  45  46  47  48 |
                                           | 35  36 37  38  39  40  41 |                   
                                           | 28  29 30  31  32  33  34 | On the right is electrode 1
                On the left is electrode 3 | 21  22 23  24  25  26  27 |        
                                           | 14  15 16  17  18  19  20 |
                                           | 7   8   9  10  11  12  13 |
                                           | 0   1   2   3   4   5   6 |
                                             -------------------------
                                             On bottom is electrode 2
*/
void aragorn::Construct()
{
  if(TheQuinks.size()>0){cout<<"This setup has already been constructed.";}
  else
  {
   for(int j=hh;j<2*hh*rows;j=j+2*hh)                         
   {                           //Creating all quinks, one row at at time and then moving down a row.
     for(int i=hw;i<2*hw*columns;i=i+2*hw)
     {
       quink * newest =(new quink(double(i-hw),double(i+hw),double(j-hh),double(j+hh)));
       TheQuinks.push_back(newest);
     }
   }
   cout<<"Take some rest. These borders are well protected."<<endl;
  }
}

void aragorn::Report()
{
  cout << "The number of Quinks is: ";
  cout << TheQuinks.size()<<endl;
}

void aragorn::SetChargeCloud(double a,double b) 
{
  //eventually this function will hopefully
  // take some x and y position and turn it
  // into a circle of charge with a dense
  // center and diffuse radial charge.
  // for today however, it does nothing.
}

void aragorn::Event()
{
  double x1,y1; //x and y coordinate of charge cloud 
  
  cout<<"Where should the charge cloud hit?"<<endl;
  cin>>x1>>y1;
  TCanvas* c1 = new TCanvas("c1", "Readout", 800, 600);
  c1->Divide(columns,rows);
  for(int i =1;i<=TheQuinks.size();i++)
  {
    c1->cd(i);
    TheQuinks[i-1]->Display(matpar, x1, y1);
    cout<<i<<" Pads have been calculated for.\n";
  }
}
// This is just a function to make sure that the setup was constructed correctly
void aragorn::CheckPad(int n)
{
  TheQuinks[n]->Report();
}
