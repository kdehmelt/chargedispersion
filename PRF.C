#include <TFile.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TMultiGraph.h>
#include <TH1.h>
#include <iostream>
using namespace std;
void PRF()
{
	TFile f(//Enter path to root file containing histograms here);
	vector< vector<double> > maxima(44);
	TH1F * h1 = new TH1F();
	char buffer [50];
	int a=0;
	double sum=0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			for (int k = 1; k < 11; k++)
			{
				sprintf(buffer,"PRF_li_%i_lx_%i_ly_%i",k,j,i);
				h1 = (TH1F*)f.Get(buffer);
				maxima[a].push_back(h1->GetBinContent(h1->GetMaximumBin()));
				delete(h1);
			}
		  	sum=0;
		 	for (int i = 0; i < maxima[a].size(); ++i)
		  	{
		  		sum+=maxima[a][i];
		 	}
		  	maxima[a].push_back(sum);
		 	a++;
		}
	}
	// Insert whichever PRF generating script you'd like to see the PRF for below this comment:
	// This script does nothing without adding a PRFType!
}
