{
  gROOT->ProcessLine(".L aragorn.C+");
  gROOT->ProcessLine(".L quink.C+");
  gROOT->ProcessLine(".L Qfuncs.cxx+");
  gROOT->ProcessLine(".L RLAfuncs.cxx+");
  gROOT->ProcessLine(".L ConvoluteLoop.C+");
  gROOT->ProcessLine("aragorn t");
  gROOT->ProcessLine("t.Construct()");
  gROOT->ProcessLine("t.Event()");
  //gROOT->ProcessLine("gStyle->SetOptStat(0)");
  //gROOT->ProcessLine("ConvoluteRLAQ()");
}
