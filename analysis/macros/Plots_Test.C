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


void Plots_Test2() {
 
  gROOT->Reset();
  SetAtlasStyle();
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);
  
  TString pdf="CT10";
  TString energy="LHC13";
  int mass=165;
  int deltamass=2;
  TString scheme="running";

  TString title = "n3_12_";
  TString filename = "./"+energy+"_"+pdf+"_mtrun"+TString::Format("%i",mass)+"_pt30_mu1_5p_2.root";
  TGraphErrors *gref = readGraph(filename,title+"pt30",true);
  
  filename = "./"+energy+"_"+pdf+"_mtrun"+TString::Format("%i",mass)+"_pt30_mu1_2p.root";
  TGraphErrors *gref_scale_up = readGraph(filename,title+"pt30",true);

  filename = "./"+energy+"_"+pdf+"_mtrun"+TString::Format("%i",mass)+"_pt30_mu1_5p.root";
  TGraphErrors *gref_scale_down = readGraph(filename,title+"pt30",true);

  /* filename = "../../rootfiles/"+energy+"_"+pdf+"_mtrun"+TString::Format("%i",mass+deltamass)+"_pt30_mu1.root";
  TGraphErrors *g_up = readGraph(filename,title+"pt50",false);

  filename = "../../rootfiles/"+energy+"_"+pdf+"_mtrun"+TString::Format("%i",mass-deltamass)+"_pt30_mu1.root";
  TGraphErrors *g_down = readGraph(filename,title+"pt50",false);*/

 
  /* TH1F* h_gref_scale_up = Histo(gref_scale_up);
  TH1F* h_gref = Histo(gref);
  TH1F* h_gref_scale_down = Histo(gref_scale_down);
  */
  /* TH1F* h_g_up = Histo(g_up);
  TH1F* h_g_down = Histo(g_down);*/

  TCanvas *canv0 = new TCanvas ("new0","new0",1000,800);

  // h_gref_scale_up->Divide(h_gref);
  //  h_gref_scale_down->Divide(h_gref);
    
  canv0->cd();
  gref_scale_up->GetYaxis()->SetTitle("#Rgothic(m(m)=X, #mu=Y)");
  gref_scale_up->GetXaxis()->SetTitle("#rho_{s}");
  //  gref_scale_up->GetYaxis()->SetRangeUser(0,3.6);
  //gref_scale_up->GetXaxis()->SetRangeUser(0,1);
  gref_scale_up->GetYaxis()->SetLabelSize(0.04);
  gref_scale_up->GetXaxis()->SetLabelSize(0.04);
  gref_scale_up->SetLineColor(kGreen);
  gref_scale_up->SetLineStyle(2);
  gref_scale_up->SetLineWidth(2);
  gref_scale_up->SetMarkerColor(kGreen);
  gref_scale_up->SetMarkerSize(0.);
  gref_scale_up->Draw("alpe");
  
  gref->SetLineColor(kBlack);
  gref->SetLineStyle(1);
  gref->SetLineWidth(2);
  gref->SetMarkerColor(kBlack);
  gref->SetMarkerSize(0.);
  gref->Draw("lpe");

  gref_scale_down->SetLineColor(kBlue);
  gref_scale_down->SetLineStyle(1);
  gref_scale_down->SetLineWidth(1);
  gref_scale_down->SetMarkerColor(kBlue);
  gref_scale_down->SetMarkerSize(0.);
  gref_scale_down->Draw("lpe");

  /* h_g_up->SetLineColor(2);
  h_g_up->SetLineStyle(1);
  h_g_up->SetLineWidth(2);
  h_g_up->SetMarkerColor(2);
  h_g_up->SetMarkerSize(0.);
  h_g_up->Draw("hsame");

  h_g_down->SetLineColor(4);
  h_g_down->SetLineStyle(1);
  h_g_down->SetLineWidth(2);
  h_g_down->SetMarkerColor(4);
  h_g_down->SetMarkerSize(0.);
  h_g_down->Draw("hsame");*/

 
  /*  TLegend *leg0 = new TLegend(0.55,0.7,0.9,0.9);//Variables
  leg0->SetHeader(energy+", p_{T}^{jet} > 50 GeV");
  leg0->AddEntry(h_gref_scale_down,"5Points","l");//TString::Format("m(m)=%i GeV, #mu=2#timesm(m)",mass),"l");
  leg0->AddEntry(h_gref_scale_up,"2Points","l");//TString::Format("m(m)=%i GeV, #mu=2#timesm(m)",mass),"l");
  leg0->AddEntry(h_gref,"Fit","l");*/
  /*  leg0->AddEntry(h_gref_scale_down,TString::Format("m(m)=%i GeV, #mu=m(m)/2",mass),"l");
  leg0->AddEntry(h_g_up,TString::Format("m(m)=%i GeV, #mu=m(m)",mass+5),"l");
  leg0->AddEntry(h_g_down,TString::Format("m(m)=%i GeV, #mu=m(m)",mass-5),"l");*/

  /* leg0->SetLineWidth(0);
  leg0->SetFillColor(0);
  leg0->SetShadowColor(0);
  leg0->Draw();*/


  
  

}


 
  
  
void Plots_Test() {
 
  gROOT->Reset();
  SetAtlasStyle();
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);
  
  TString pdf="CT10";
  TString energy="LHC13";
  int mass=171;
  int deltamass=2; 
  TString scheme="running";

  TString filename = "./"+energy+"_"+pdf+"_mt"+TString::Format("%i",mass)+"_pt30_mu1_simpleaverage.root";
  TGraphErrors *gsimple_LO = readGraphNotNorm(filename,"n3_24_pt30_LO");
  TGraphErrors *gsimple_NLO = readGraphNotNorm(filename,"n3_24_pt30_NLO");
  TGraphErrors *gsimple = readGraphNotNorm(filename,"n3_24_pt30");

  filename = "./"+energy+"_"+pdf+"_mt"+TString::Format("%i",mass)+"_pt30_mu1_weightedaverage.root";
  TGraphErrors *gweighted_LO = readGraphNotNorm(filename,"n3_24_pt30_LO");
  TGraphErrors *gweighted_NLO = readGraphNotNorm(filename,"n3_24_pt30_NLO");
  TGraphErrors *gweighted = readGraphNotNorm(filename,"n3_24_pt30");
  

  TH1F* h_gsimple_LO= Histo(gsimple_LO);
  TH1F* h_gsimple_NLO= Histo(gsimple_NLO);
  TH1F* h_gsimple= Histo(gsimple);

  TH1F* h_gweighted_LO= Histo(gweighted_LO);
  TH1F* h_gweighted_NLO= Histo(gweighted_NLO);
  TH1F* h_gweighted= Histo(gweighted);

  TCanvas *canv0 = new TCanvas ("new0","new0",1400,600);
  canv0->Divide(3,1);
  // h_gref_scale_up->Divide(h_gref);
  //  h_gref_scale_down->Divide(h_gref);
    
  canv0->cd(1);
  h_gsimple_LO->GetYaxis()->SetTitle("#sigma");
  h_gsimple_LO->GetXaxis()->SetTitle("#rho_{s}");
  h_gsimple_LO->SetLineColor(2);
  h_gsimple_LO->SetLineStyle(1);
  h_gsimple_LO->SetLineWidth(2);
  h_gsimple_LO->SetMarkerColor(2);
  h_gsimple_LO->SetMarkerSize(0.);
  h_gsimple_LO->GetYaxis()->SetRangeUser(0,1.5*h_gsimple_LO->GetMaximum());
  h_gsimple_LO->Draw("h");

  h_gweighted_LO->SetLineColor(4);
  h_gweighted_LO->SetLineStyle(2);
  h_gweighted_LO->SetLineWidth(2);
  h_gweighted_LO->SetMarkerColor(4);
  h_gweighted_LO->SetMarkerSize(0.);
  h_gweighted_LO->Draw("hsame");


  TLegend *leg_LO = new TLegend(0.4,0.85,1.0,1.0);//Variables
  leg_LO->SetHeader(energy+", p_{T}^{jet} > 50 GeV: LO contr");
  leg_LO->AddEntry(h_gsimple_LO,"Simple Average","l");//TString::Format("m(m)=%i GeV, #mu=2#timesm(m)",mass),"l");
  leg_LO->AddEntry(h_gweighted_LO,"Weighted average","l");//TString::Format("m(m)=%i GeV, #mu=2#timesm(m)",mass),"l");
  leg_LO->SetLineWidth(0);
  leg_LO->SetFillColor(0);
  leg_LO->SetShadowColor(0);
  leg_LO->Draw();

  canv0->cd(2);
  h_gsimple_NLO->GetYaxis()->SetTitle("#sigma");
  h_gsimple_NLO->GetXaxis()->SetTitle("#rho_{s}");
  h_gsimple_NLO->SetLineColor(2);
  h_gsimple_NLO->SetLineStyle(1);
  h_gsimple_NLO->SetLineWidth(2);
  h_gsimple_NLO->SetMarkerColor(2);
  h_gsimple_NLO->SetMarkerSize(0.);
  h_gsimple_NLO->GetYaxis()->SetRangeUser(0,1.5*h_gsimple_NLO->GetMaximum());
  h_gsimple_NLO->Draw("h");

  h_gweighted_NLO->SetLineColor(4);
  h_gweighted_NLO->SetLineStyle(2);
  h_gweighted_NLO->SetLineWidth(2);
  h_gweighted_NLO->SetMarkerColor(4);
  h_gweighted_NLO->SetMarkerSize(0.);
  h_gweighted_NLO->Draw("hsame");


  TLegend *leg_NLO = new TLegend(0.4,0.85,1.0,1.0);//Variables
  leg_NLO->SetHeader(energy+", p_{T}^{jet} > 50 GeV: NLO contr");
  leg_NLO->AddEntry(h_gsimple_NLO,"Simple Average","l");//TString::Format("m(m)=%i GeV, #mu=2#timesm(m)",mass),"l");
  leg_NLO->AddEntry(h_gweighted_NLO,"Weighted average","l");//TString::Format("m(m)=%i GeV, #mu=2#timesm(m)",mass),"l");
  leg_NLO->SetLineWidth(0);
  leg_NLO->SetFillColor(0);
  leg_NLO->SetShadowColor(0);
  leg_NLO->Draw();

   canv0->cd(3);
  h_gsimple->GetYaxis()->SetTitle("#sigma");
  h_gsimple->GetXaxis()->SetTitle("#rho_{s}");
  h_gsimple->SetLineColor(2);
  h_gsimple->SetLineStyle(1);
  h_gsimple->SetLineWidth(2);
  h_gsimple->SetMarkerColor(2);
  h_gsimple->SetMarkerSize(0.);
  h_gsimple->GetYaxis()->SetRangeUser(0,1.5*h_gsimple->GetMaximum());
  h_gsimple->Draw("h");

  h_gweighted->SetLineColor(4);
  h_gweighted->SetLineStyle(2);
  h_gweighted->SetLineWidth(2);
  h_gweighted->SetMarkerColor(4);
  h_gweighted->SetMarkerSize(0.);
  h_gweighted->Draw("hsame");


  TLegend *leg = new TLegend(0.4,0.85,1.0,1.0);//Variables
  leg->SetHeader(energy+", p_{T}^{jet} > 50 GeV: LO+NLO contr");
  leg->AddEntry(h_gsimple,"Simple Average","l");//TString::Format("m(m)=%i GeV, #mu=2#timesm(m)",mass),"l");
  leg->AddEntry(h_gweighted,"Weighted average","l");//TString::Format("m(m)=%i GeV, #mu=2#timesm(m)",mass),"l");
  leg->SetLineWidth(0);
  leg->SetFillColor(0);
  leg->SetShadowColor(0);
  leg->Draw();

}


 
  
  
