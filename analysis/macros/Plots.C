#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include "TFile.h"
#include "TNtuple.h"
#include "TMath.h"
#include "TTree.h"
#include "TLorentzVector.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TH1F.h"
#include "TH1.h"
#include "TH2F.h"
#include "TImage.h"
#include "../include/CrossSection.h"

using namespace std;


void Plots() {

  //pole
  //ReferencePlots("running", "CT10", "LHC13", "n3_24_", "pt50", 163,4);
  //Sens_scale_pt("CT10","LHC13", 173, 2, "pt30", "","n3_ATLAS8TeV_","pole");
  //Sens_scale_bin("CT10","LHC13", 172, 2, "pt30", "","n3_","50","pole");
  //  CrossSection("CT10","LHC13", 158, 12, "50", "running");


  ////running
  //  ReferencePlots("running", "CT10", "LHC13", "n3_24_", "pt50", 163,4);
  //Sens_scale_pt("CT10","LHC13", 163, 4, "pt30", "","n3_24_","running");
  Sens_scale_bin("CT10","LHC13", 164, 2, "pt30", "","n3_","50","running");
  // CrossSection("CT10","LHC13", 158, 12, "50", "running");
}


 
  
  
