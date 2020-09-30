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


void Plots_WorldAv() {

  //  folder_root="rootfiles_worldav";

  
  gROOT->Reset();
  SetAtlasStyle();
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);
  
  TString pdf="CT10";
  TString energy="LHC13";
  float mass=172.5;
  TString scheme="pole";

  TString title = "n3_24_";
  TString filename = "../../rootfiles_worldav/"+energy+"_"+pdf+"_mt"+TString::Format("%.1f",mass)+"_pt30_mur1_muf1.root";
  cout<<filename<<endl;
  TGraphErrors *gref = readGraph(filename,title+"pt50",true);
  filename = "../../rootfiles_worldav/"+energy+"_"+pdf+"_mt"+TString::Format("%.1f",mass)+"_pt30_mur2_muf2.root";
  TGraphErrors *gref_up = readGraph(filename,title+"pt50",true);
  filename = "../../rootfiles_worldav/"+energy+"_"+pdf+"_mt"+TString::Format("%.1f",mass)+"_pt30_mur0.5_muf0.5.root";
  TGraphErrors *gref_down = readGraph(filename,title+"pt50",true);

  filename = "../../rootfiles_worldav/"+energy+"_"+pdf+"_mt"+TString::Format("%.1f",mass)+"_pt30_mur1_muf0.5.root";
  TGraphErrors *gref_1 = readGraph(filename,title+"pt50",false);
    
  filename = "../../rootfiles_worldav/"+energy+"_"+pdf+"_mt"+TString::Format("%.1f",mass)+"_pt30_mur1_muf2.root";
  TGraphErrors *gref_2 = readGraph(filename,title+"pt50",false);

  filename = "../../rootfiles_worldav/"+energy+"_"+pdf+"_mt"+TString::Format("%.1f",mass)+"_pt30_mur2_muf1.root";
  TGraphErrors *gref_3 = readGraph(filename,title+"pt50",false);

  filename = "../../rootfiles_worldav/"+energy+"_"+pdf+"_mt"+TString::Format("%.1f",mass)+"_pt30_mur0.5_muf1.root";
  TGraphErrors *gref_4 = readGraph(filename,title+"pt50",false);


  std::vector<TGraphErrors*> dist_vector;
  dist_vector.push_back(gref);
  dist_vector.push_back(gref_up);
  dist_vector.push_back(gref_down);
  dist_vector.push_back(gref_1);
  dist_vector.push_back(gref_2);
  dist_vector.push_back(gref_3);
  dist_vector.push_back(gref_4);

  std::vector<TString> label_vector;
  label_vector.push_back("#mu_{R}=#mu_{F}=1");
  label_vector.push_back("#mu_{R}=#mu_{F}=2");
  label_vector.push_back("#mu_{R}=#mu_{F}=0.5");
  label_vector.push_back("#mu_{R}!=#mu_{F}");

  
  DrawVector2(dist_vector,"distr_canvas",label_vector,TString::Format("#Rgothic(mt=%1f GeV,pole)",mass), "#rho_{s}",scheme,"Binning 0.05");

}


 
  
  
