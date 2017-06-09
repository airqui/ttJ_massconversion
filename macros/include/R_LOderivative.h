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

using namespace std;

//  for(int i=0; i<2 ; i++) {

double as(TString mt="164", TString scale="mu1"){

  TString s_mt="../../rootfiles/CT10_7TeV_mt"+mt+"_"+scale+"_pt50_NLO.root";
  
  TFile f_mt(s_mt);
  TVectorD* alphaspi = (TVectorD*) f_mt.Get("alphas_over_pi");

  double value = alphaspi(0);
  return value;

}


std::vector<double> N3_NLO(TString mt="164", TString scale="mu1"){

  TString s_mt="../../rootfiles/CT10_7TeV_mt"+mt+"_"+scale+"_pt50_NLO.root";
  
  TFile f_mt(s_mt);
  TGraphErrors* N3_mt = (TGraphErrors*) f_mt.Get("N3_ATLAS");
  Double_t *n3_mt=N3_mt->GetY();
  Double_t *en3_mt=N3_mt->GetEY();

  std::vector<double> value;
  for(int i=0; i<6; i++) {
    value.push_back(n3_mt[i]);
    value.push_back(en3_mt[i]);
  }
 
  return value;

}


std::vector<double> width_bin(TString mt="164", TString scale="mu1"){

  TString s_mt="../../rootfiles/CT10_7TeV_mt"+mt+"_"+scale+"_pt50_NLO.root";
  
  TFile f_mt(s_mt);
  TGraphErrors* N3_mt = (TGraphErrors*) f_mt.Get("N3_ATLAS");
  Double_t *en3_mt=N3_mt->GetEX();

  std::vector<double> value;
  for(int i=0; i<6; i++) {
    value.push_back(en3_mt[i]);
  }
 
  return value;

}

std::vector<double> N3_LOderivative(TString mt="164", TString scale="mu1", double delta=0.5, bool draw=true){

  gROOT->Reset();

  gROOT->LoadMacro("../include/AtlasStyle.C");
  gROOT->LoadMacro("../include/AtlasLabels.C");
  SetAtlasStyle();
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);


  double up_height     = 0.8; // please tune so that the upper figures size will meet your requirement
  double dw_correction = 1.55;//1.40; // please tune so that the smaller canvas size will work in your environment
  double font_size_dw  = 0.05;
  double title_offset  = 1.;
  double title_size  = 0.075;
  double dw_height    = (1. - up_height) * dw_correction;

  double par_a[8], par_b[8], par_c[8];
  double par_ea[8], par_eb[8], par_ec[8];

  double par_aL[8], par_bL[8];
  double par_eaL[8], par_ebL[8];


  TString s_mtminus="../../rootfiles/CT10_7TeV_mt"+mt+"_minus05_"+scale+"_pt50_LO.root";
  TString s_mt="../../rootfiles/CT10_7TeV_mt"+mt+"_"+scale+"_pt50_LO.root";
  TString s_mtplus="../../rootfiles/CT10_7TeV_mt"+mt+"_plus05_"+scale+"_pt50_LO.root";


  TFile f_mtminus(s_mtminus);
  TGraphErrors* N3_mtminus = (TGraphErrors*) f_mtminus.Get("N3_ATLAS");
  Double_t *n3_mtminus=N3_mtminus->GetY();
  Double_t *en3_mtminus=N3_mtminus->GetEY();

  TFile f_mt(s_mt);
  TGraphErrors* N3_mt = (TGraphErrors*) f_mt.Get("N3_ATLAS");
  Double_t *n3_mt=N3_mt->GetY();
  Double_t *en3_mt=N3_mt->GetEY();

  TFile f_mtplus(s_mtplus);
  TGraphErrors* N3_mtplus = (TGraphErrors*) f_mtplus.Get("N3_ATLAS");
  Double_t *n3_mtplus=N3_mtplus->GetY();
  Double_t *en3_mtplus=N3_mtplus->GetEY();

 
  Double_t xmass[10], exmass[10];
  TMatrixD ybin(6,10);
  TMatrixD eybin(6,10);

  Double_t ybin1[10], ybin2[10], ybin3[10], ybin4[10], ybin5[10], ybin6[10];
  Double_t eybin1[10], eybin2[10], eybin3[10], eybin4[10], eybin5[10], eybin6[10];

  double mass=0;
  if( mt == "160") mass=160;
  if( mt == "161") mass=161;
  if( mt == "162") mass=162;
  if( mt == "163") mass=163;
  if( mt == "164") mass=164;
  if( mt == "165") mass=165;
  if( mt == "166") mass=166;
  if( mt == "167") mass=167;
  if( mt == "168") mass=168;
  if( mt == "169") mass=169;
  if( mt == "170") mass=180;

  xmass[0]=mass-delta;  
  xmass[1]=mass;  
  xmass[2]=mass+delta;  


  for(int i=0; i<3; i++) {
    for(int j=0; j<6; j++) {
      ybin[j][i]=0;
      eybin[j][i]=0;
    }
  }

  for(int i=0; i<3; i++) {
    for(int j=0; j<6; j++) {
      if(i==0) ybin[j][i]=n3_mtminus[j];
      if(i==1) ybin[j][i]=n3_mt[j];
      if(i==2) ybin[j][i]=n3_mtplus[j];

      if(i==0) eybin[j][i]=en3_mtminus[j];
      if(i==1) eybin[j][i]=en3_mt[j];
      if(i==2) eybin[j][i]=en3_mtplus[j];
    }
  }

  for(int i=0; i<3; i++){

    ybin1[i]=0;
    ybin2[i]=0;
    ybin3[i]=0;
    ybin4[i]=0;
    ybin5[i]=0;
    ybin6[i]=0;

    eybin1[i]=0;
    eybin2[i]=0;
    eybin3[i]=0;
    eybin4[i]=0;
    eybin5[i]=0;
    eybin6[i]=0;

    ybin1[i]=ybin[0][i];
    ybin2[i]=ybin[1][i];
    ybin3[i]=ybin[2][i];
    ybin4[i]=ybin[3][i];
    ybin5[i]=ybin[4][i];
    ybin6[i]=ybin[5][i];

    eybin1[i]=eybin[0][i];
    eybin2[i]=eybin[1][i];
    eybin3[i]=eybin[2][i];
    eybin4[i]=eybin[3][i];
    eybin5[i]=eybin[4][i];
    eybin6[i]=eybin[5][i];

  }

  //  for(int i=0; i<5; i++) cout<<xmass[i]<<" "<<ybin1[i]<<" "<<eybin1[i]<<endl;

  TGraphErrors *bin1 = new TGraphErrors(3,xmass,ybin1,0,eybin1);
  TGraphErrors *bin2 = new TGraphErrors(3,xmass,ybin2,0,eybin2);
  TGraphErrors *bin3 = new TGraphErrors(3,xmass,ybin3,0,eybin3);
  TGraphErrors *bin4 = new TGraphErrors(3,xmass,ybin4,0,eybin4);
  TGraphErrors *bin5 = new TGraphErrors(3,xmass,ybin5,0,eybin5);
  TGraphErrors *bin6 = new TGraphErrors(3,xmass,ybin6,0,eybin6);


  // -------------------------------------------------------------------
  // Fit polynomial 1
  //----------------------------------------------------------------------

  TF1 *f2 = new TF1("f2", "[0]+[1]*(x)", -2, 2);
  bin1->Fit("f2","E");
  par_aL[0]=f2->GetParameter(0);  par_bL[0]=f2->GetParameter(1); 
  par_eaL[0]=f2->GetParError(0);  par_ebL[0]=f2->GetParError(1); 

  TF1 *f3 = new TF1("f3", "[0]+[1]*(x)", -2, 3);
  bin2->Fit("f3","E");
  par_aL[1]=f3->GetParameter(0);  par_bL[1]=f3->GetParameter(1); 
  par_eaL[1]=f3->GetParError(0);  par_ebL[1]=f3->GetParError(1); 
  
  TF1 *f4 = new TF1("f4", "[0]+[1]*(x)", -2, 3);
  bin3->Fit("f4","E");
  par_aL[2]=f4->GetParameter(0);  par_bL[2]=f4->GetParameter(1); 
  par_eaL[2]=f4->GetParError(0);  par_ebL[2]=f4->GetParError(1); 
 
  TF1 *f5 = new TF1("f5", "[0]+[1]*(x)", -2, 2);
  bin4->Fit("f5","E");
  par_aL[3]=f5->GetParameter(0);  par_bL[3]=f5->GetParameter(1); 
  par_eaL[3]=f5->GetParError(0);  par_ebL[3]=f5->GetParError(1); 

  TF1 *f6 = new TF1("f6", "[0]+[1]*(x)", -2, 2);
  bin5->Fit("f6","E");
  par_aL[4]=f6->GetParameter(0);  par_bL[4]=f6->GetParameter(1); 
  par_eaL[4]=f6->GetParError(0);  par_ebL[4]=f6->GetParError(1); 

  TF1 *f7 = new TF1("f7", "[0]+[1]*(x)", -2, 2);
  bin6->Fit("f7","E");
  par_aL[5]=f7->GetParameter(0);  par_bL[5]=f7->GetParameter(1); 
  par_eaL[5]=f7->GetParError(0);  par_ebL[5]=f7->GetParError(1); 


  if(draw==true){
    TCanvas *canvas= new TCanvas ("fit","fit",1800,1600);
    canvas->Divide(2,3);
    
    canvas->cd(1);
    // bin1->GetYaxis()->SetRangeUser(0.,0.5);    
    bin1->GetXaxis()->SetRangeUser(150,175);
    bin1->GetXaxis()->SetLabelSize(font_size_dw);
    bin1->GetYaxis()->SetLabelSize(font_size_dw);
    bin1->GetYaxis()->SetTitleSize(title_size);
    bin1->GetYaxis()->CenterTitle();
    bin1->GetYaxis()->SetTitleOffset(title_offset);
    if(scale== "mu1")    bin1->GetYaxis()->SetTitle("N_{3}^{0} (m_{t}^{pole},#rho_{s},#mu=m_{t}^{pole})");
    if(scale== "mu05")    bin1->GetYaxis()->SetTitle("N_{3}^{0} (m_{t}^{pole},#rho_{s},#mu=0.5 m_{t}^{pole})");
    if(scale== "mu2")    bin1->GetYaxis()->SetTitle("N_{3}^{0} (m_{t}^{pole},#rho_{s},#mu=2  m_{t}^{pole})");

    bin1->GetXaxis()->SetTitle("m_{t}^{pole} [GeV]");
    
    bin1->SetLineWidth(1);
    bin1->SetLineColor(1);
    bin1->SetLineStyle(1);
    bin1->SetMarkerSize(0.8);
    bin1->SetMarkerStyle(4);
    bin1->SetMarkerColor(1);
    bin1->SetName("bin1");
    bin1->Draw("ap");
    
    myText(0.25,0.3,1,"t#bar{t}+1Jet @ NLO (fix. order) for 0<#rho_{s}<0.25");
    myText(0.25,0.2,1,"m_{t}^{pole} parametrization to a 1st degree pol.");
    
    
    leg2 = new TLegend(0.5,0.75,0.9,0.9);
    leg2->AddEntry("bin1","t#bar{t}+1Jet @ NLO (fix. order)" ,"pe");
    leg2->AddEntry("bin1","best fit to a+b(m_{t}^{pole})" ,"l");
    leg2->SetLineWidth(10);
    leg2->SetLineColor(0);
    leg2->SetFillColor(0);
    leg2->Draw(); 
    
    canvas->cd(2);
    //bin2->GetYaxis()->SetRangeUser(1.0,1.5);
    bin2->GetXaxis()->SetRangeUser(150,175);
    bin2->GetXaxis()->SetLabelSize(font_size_dw);
    bin2->GetYaxis()->SetLabelSize(font_size_dw);
    bin2->GetYaxis()->SetTitleSize(title_size);
    bin2->GetYaxis()->CenterTitle();
    bin2->GetYaxis()->SetTitleOffset(title_offset);
    if(scale== "mu1")    bin2->GetYaxis()->SetTitle("N_{3}^{0} (m_{t}^{pole},#rho_{s},#mu=m_{t}^{pole})");
    if(scale== "mu05")   bin2->GetYaxis()->SetTitle("N_{3}^{0} (m_{t}^{pole},#rho_{s},#mu=0.5 m_{t}^{pole})");
    if(scale== "mu2")    bin2->GetYaxis()->SetTitle("N_{3}^{0} (m_{t}^{pole},#rho_{s},#mu=2  m_{t}^{pole})");
    bin2->GetXaxis()->SetTitle("m_{t}^{pole} [GeV]");
    
    bin2->SetLineWidth(1);
    bin2->SetLineColor(1);
    bin2->SetLineStyle(1);
    bin2->SetMarkerSize(0.8);
    bin2->SetMarkerStyle(4);
    bin2->SetMarkerColor(1);
    bin2->SetName("bin2");
    bin2->Draw("ap");
    
    myText(0.25,0.3,1,"t#bar{t}+1Jet @ NLO (fix. order) for 0.25<#rho_{s}<0.325");
    myText(0.25,0.2,1,"m_{t}^{pole} parametrization to a 1st degree pol.");
    
    
    leg2 = new TLegend(0.5,0.75,0.9,0.9);
    leg2->AddEntry("bin2","t#bar{t}+1Jet @ NLO (fix. order)" ,"pe");
    leg2->AddEntry("bin2","best fit to a+b(m_{t}^{pole})" ,"l");
    leg2->SetLineWidth(10);
    leg2->SetLineColor(0);
    leg2->SetFillColor(0);
    leg2->Draw();

    canvas->cd(3);
    //bin3->GetYaxis()->SetRangeUser(1.9,2.4);
    bin3->GetXaxis()->SetRangeUser(150,175);
    bin3->GetXaxis()->SetLabelSize(font_size_dw);
    bin3->GetYaxis()->SetLabelSize(font_size_dw);
    bin3->GetYaxis()->SetTitleSize(title_size);
    bin3->GetYaxis()->CenterTitle();
    bin3->GetYaxis()->SetTitleOffset(title_offset);
    if(scale== "mu1")    bin3->GetYaxis()->SetTitle("N_{3}^{0} (m_{t}^{pole},#rho_{s},#mu=m_{t}^{pole})");
    if(scale== "mu05")   bin3->GetYaxis()->SetTitle("N_{3}^{0} (m_{t}^{pole},#rho_{s},#mu=0.5 m_{t}^{pole})");
    if(scale== "mu2")    bin3->GetYaxis()->SetTitle("N_{3}^{0} (m_{t}^{pole},#rho_{s},#mu=2  m_{t}^{pole})");
    bin3->GetXaxis()->SetTitle("m_{t}^{pole} [GeV]");
    
    bin3->SetLineWidth(1);
    bin3->SetLineColor(1);
    bin3->SetLineStyle(1);
    bin3->SetMarkerSize(0.8);
    bin3->SetMarkerStyle(4);
    bin3->SetMarkerColor(1);
    bin3->SetName("bin3");
    bin3->Draw("ap");

    myText(0.25,0.3,1,"t#bar{t}+1Jet @ NLO (fix. order) for 0.325<#rho_{s}<0.425");
    myText(0.25,0.2,1,"m_{t}^{pole} parametrization to a 1st degree pol.");
   
    
    leg2 = new TLegend(0.5,0.75,0.9,0.9);
    leg2->AddEntry("bin3","t#bar{t}+1Jet @ NLO (fix. order)" ,"pe");
    leg2->AddEntry("bin3","best fit to a+b(m_{t}^{pole})" ,"l");
    leg2->SetLineWidth(10);
    leg2->SetLineColor(0);
    leg2->SetFillColor(0);
    leg2->Draw();

    canvas->cd(4);
    //bin4->GetYaxis()->SetRangeUser(2.4,2.9);
    bin4->GetXaxis()->SetRangeUser(150,175);
    bin4->GetXaxis()->SetLabelSize(font_size_dw);
    bin4->GetYaxis()->SetLabelSize(font_size_dw);
    bin4->GetYaxis()->SetTitleSize(title_size);
    bin4->GetYaxis()->CenterTitle();
    bin4->GetYaxis()->SetTitleOffset(title_offset);
    if(scale== "mu1")    bin4->GetYaxis()->SetTitle("N_{3}^{0} (m_{t}^{pole},#rho_{s},#mu=m_{t}^{pole})");
    if(scale== "mu05")   bin4->GetYaxis()->SetTitle("N_{3}^{0} (m_{t}^{pole},#rho_{s},#mu=0.5 m_{t}^{pole})");
    if(scale== "mu2")    bin4->GetYaxis()->SetTitle("N_{3}^{0} (m_{t}^{pole},#rho_{s},#mu=2  m_{t}^{pole})");
    bin4->GetXaxis()->SetTitle("m_{t}^{pole} [GeV]");
    
    bin4->SetLineWidth(1);
    bin4->SetLineColor(1);
    bin4->SetLineStyle(1);
    bin4->SetMarkerSize(0.8);
    bin4->SetMarkerStyle(4);
    bin4->SetMarkerColor(1);
    bin4->SetName("bin4");
    bin4->Draw("ap");

    myText(0.25,0.3,1,"t#bar{t}+1Jet @ NLO (fix. order) for 0.425<#rho_{s}<0.525");
    myText(0.25,0.2,1,"m_{t}^{pole} parametrization to a 1st degree pol.");
   
    
    leg2 = new TLegend(0.5,0.75,0.9,0.9);
    leg2->AddEntry("bin4","t#bar{t}+1Jet @ NLO (fix. order)" ,"pe");
    leg2->AddEntry("bin4","best fit to a+b(m_{t}^{pole})" ,"l");
    leg2->SetLineWidth(10);
    leg2->SetLineColor(0);
    leg2->SetFillColor(0);
    leg2->Draw();

    canvas->cd(5);
    //bin5->GetYaxis()->SetRangeUser(1.9,2.4);
    bin5->GetXaxis()->SetRangeUser(150,175);
    bin5->GetXaxis()->SetLabelSize(font_size_dw);
    bin5->GetYaxis()->SetLabelSize(font_size_dw);
    bin5->GetYaxis()->SetTitleSize(title_size);
    bin5->GetYaxis()->CenterTitle();
    bin5->GetYaxis()->SetTitleOffset(title_offset);
    if(scale== "mu1")    bin5->GetYaxis()->SetTitle("N_{3}^{0} (m_{t}^{pole},#rho_{s},#mu=m_{t}^{pole})");
    if(scale== "mu05")   bin5->GetYaxis()->SetTitle("N_{3}^{0} (m_{t}^{pole},#rho_{s},#mu=0.5 m_{t}^{pole})");
    if(scale== "mu2")    bin5->GetYaxis()->SetTitle("N_{3}^{0} (m_{t}^{pole},#rho_{s},#mu=2  m_{t}^{pole})");
    bin5->GetXaxis()->SetTitle("m_{t}^{pole} [GeV]");
    
    bin5->SetLineWidth(1);
    bin5->SetLineColor(1);
    bin5->SetLineStyle(1);
    bin5->SetMarkerSize(0.8);
    bin5->SetMarkerStyle(4);
    bin5->SetMarkerColor(1);
    bin5->SetName("bin5");
    bin5->Draw("ap");

    myText(0.25,0.3,1,"t#bar{t}+1Jet @ NLO (fix. order) for 0.525<#rho_{s}<0.675");
    myText(0.25,0.2,1,"m_{t}^{pole} parametrization to a 1st degree pol.");
   
    
    leg2 = new TLegend(0.5,0.75,0.9,0.9);
    leg2->AddEntry("bin5","t#bar{t}+1Jet @ NLO (fix. order)" ,"pe");
    leg2->AddEntry("bin5","best fit to a+b(m_{t}^{pole})" ,"l");
    leg2->SetLineWidth(10);
    leg2->SetLineColor(0);
    leg2->SetFillColor(0);
    leg2->Draw();

    canvas->cd(6);
    //bin6->GetYaxis()->SetRangeUser(0.,0.5);
    bin6->GetXaxis()->SetRangeUser(150,175);
    bin6->GetXaxis()->SetLabelSize(font_size_dw);
    bin6->GetYaxis()->SetLabelSize(font_size_dw);
    bin6->GetYaxis()->SetTitleSize(title_size);
    bin6->GetYaxis()->CenterTitle();
    bin6->GetYaxis()->SetTitleOffset(title_offset);
    if(scale== "mu1")    bin6->GetYaxis()->SetTitle("N_{3}^{0} (m_{t}^{pole},#rho_{s},#mu=m_{t}^{pole})");
    if(scale== "mu05")   bin6->GetYaxis()->SetTitle("N_{3}^{0} (m_{t}^{pole},#rho_{s},#mu=0.5 m_{t}^{pole})");
    if(scale== "mu2")    bin6->GetYaxis()->SetTitle("N_{3}^{0} (m_{t}^{pole},#rho_{s},#mu=2  m_{t}^{pole})");
    bin6->GetXaxis()->SetTitle("m_{t}^{pole} [GeV]");
    
    bin6->SetLineWidth(1);
    bin6->SetLineColor(1);
    bin6->SetLineStyle(1);
    bin6->SetMarkerSize(0.8);
    bin6->SetMarkerStyle(4);
    bin6->SetMarkerColor(1);
    bin6->SetName("bin6");
    bin6->Draw("ap");

    myText(0.25,0.3,1,"t#bar{t}+1Jet @ NLO (fix. order) for 0.675<#rho_{s}<1.0");
    myText(0.25,0.2,1,"m_{t}^{pole} parametrization to a 1st degree pol.");
   
    
    leg2 = new TLegend(0.5,0.75,0.9,0.9);
    leg2->AddEntry("bin6","t#bar{t}+1Jet @ NLO (fix. order)" ,"pe");
    leg2->AddEntry("bin6","best fit to a+b(m_{t}^{pole})" ,"l");
    leg2->SetLineWidth(10);
    leg2->SetLineColor(0);
    leg2->SetFillColor(0);
    leg2->Draw();

    canvas->Print("../../logfiles/conversion/fitLO_mt"+mt+"_"+scale+".eps");
  }
   

  ofstream fout ("../../logfiles/conversion/fitLO_mt"+mt+"_"+scale+".log");

  for(int i=0; i<6; i++) {
    if( fabs((par_bL[i]-(n3_mtplus[i]-n3_mtminus[i]))) / par_bL[i] > 0.01) {
      cout<< " Polynomial and poor's man derivative are so much different for the bin "<< i <<" "<<fabs((par_bL[i]-(n3_mtplus[i]-n3_mtminus[i]))) / par_bL[i]<<endl;
      fout<< " Polynomial and poor's man derivative are so much different for the bin "<< i <<" "<<fabs((par_bL[i]-(n3_mtplus[i]-n3_mtminus[i]))) / par_bL[i]<<endl;
    }
    if( fabs(n3_mtplus[i]-n3_mt[i]) / n3_mt[i] > 0.04) {
      cout<< " Hugh difference between plus and nominal N3, for the bin "<< i+1 <<" "<<fabs(n3_mtplus[i]-n3_mt[i]) / n3_mt[i] <<endl;
      fout<< " Hugh difference between plus and nominal N3, for the bin "<< i+1 <<" "<<fabs(n3_mtplus[i]-n3_mt[i]) / n3_mt[i] <<endl;
    }
    if( fabs(n3_mtminus[i]-n3_mt[i]) / n3_mt[i] > 0.04) {
      cout<< " Hugh difference between minus and nominal N3, for the bin "<< i+1 <<" "<<fabs(n3_mtminus[i]-n3_mt[i]) / n3_mt[i]<<endl;
      fout<< " Hugh difference between minus and nominal N3, for the bin "<< i+1 <<" "<<fabs(n3_mtminus[i]-n3_mt[i]) / n3_mt[i]<<endl;
    }
    if( (n3_mtplus[i]-n3_mtminus[i]) > 0.0) {
      cout<< " Wrong derivative sign for bin "<< i <<endl;
      fout<< " Wrong derivative sign for bin "<< i <<endl;
    }
  }


  fout<<" "<<endl;
  fout<<" "<<endl;
  fout<<"######################################################################################################### "<<endl;
  fout<<"#   FIT TO LEADING ORDER"<<endl;
  fout<<"######################################################################################################### "<<endl;
  fout<<" "<<endl;
  fout<<" "<<endl;
  fout<<" rhos from 0 to 0.25 "<<endl;
  fout<<"                         Sigma_ttj^0 (Pol1)          = "<<par_aL[0]<<"("<<par_eaL[0]<<") + "<<par_bL[0]<<"("<<par_ebL[0]<<") *mt"<<endl;
  fout<<"                         dSigma_ttj^0 / dmt (Pol1)   = "<<par_bL[0]<<endl;
  fout<<"                         dSigma_ttj^0 / dmt (interp) = "<<(n3_mtplus[0]-n3_mtminus[0])<<endl;
  fout<<"                         values:, n3_mtminus= "<<n3_mtminus[0]<<" n3_mtplus= "<< n3_mt[0]<<" n3_mtplus= "<< n3_mtplus[0]<<endl;
  fout<<" "<<endl;
  fout<<" rhos from 0.25 to 0.325 "<<endl;
  fout<<"                         Sigma_ttj^0 (Pol1) = "<<par_aL[1]<<"("<<par_eaL[1]<<") + "<<par_bL[1]<<"("<<par_ebL[1]<<") *mt"<<endl;
  fout<<"                         dSigma_ttj^0 / dmt (Pol1)   = "<<par_bL[1]<<endl;
  fout<<"                         dSigma_ttj^0 / dmt (interp) = "<<(n3_mtplus[1]-n3_mtminus[1])<<endl;
  fout<<"                         values:, n3_mtminus= "<<n3_mtminus[1]<<" n3_mtplus= "<< n3_mt[1]<<" n3_mtplus= "<< n3_mtplus[1]<<endl;
  fout<<" "<<endl;
  fout<<" rhos from 0.325 to 0.425 "<<endl;
  fout<<"                         Sigma_ttj^0 (Pol1) = "<<par_aL[2]<<"("<<par_eaL[2]<<") + "<<par_bL[2]<<"("<<par_ebL[2]<<") *mt"<<endl;
  fout<<"                         dSigma_ttj^0 / dmt (Pol1)   = "<<par_bL[2]<<endl;
  fout<<"                         dSigma_ttj^0 / dmt (interp) = "<<(n3_mtplus[2]-n3_mtminus[2])<<endl;
  fout<<"                         values:, n3_mtminus= "<<n3_mtminus[2]<<" n3_mtplus= "<< n3_mt[2]<<" n3_mtplus= "<< n3_mtplus[2]<<endl;
  fout<<" "<<endl;
  fout<<" rhos from 0.425 to 0.525 "<<endl;
  fout<<"                         Sigma_ttj^0 (Pol1) = "<<par_aL[3]<<"("<<par_eaL[3]<<") + "<<par_bL[3]<<"("<<par_ebL[3]<<") *mt"<<endl;
  fout<<"                         dSigma_ttj^0 / dmt (Pol1)   = "<<par_bL[3]<<endl;
  fout<<"                         dSigma_ttj^0 / dmt (interp) = "<<(n3_mtplus[3]-n3_mtminus[3])<<endl;
  fout<<"                         values:, n3_mtminus= "<<n3_mtminus[3]<<" n3_mtplus= "<< n3_mt[3]<<" n3_mtplus= "<< n3_mtplus[3]<<endl;
  fout<<" "<<endl;
  fout<<" rhos from 0.525 to 0.675 "<<endl;
  fout<<"                         Sigma_ttj^0 (Pol1) = "<<par_aL[4]<<"("<<par_eaL[4]<<") + "<<par_bL[4]<<"("<<par_ebL[4]<<") *mt"<<endl;
  fout<<"                         dSigma_ttj^0 / dmt (Pol1)   = "<<par_bL[4]<<endl;
  fout<<"                         dSigma_ttj^0 / dmt (interp) = "<<(n3_mtplus[4]-n3_mtminus[4])<<endl;
  fout<<"                         values:, n3_mtminus= "<<n3_mtminus[4]<<" n3_mtplus= "<< n3_mt[4]<<" n3_mtplus= "<< n3_mtplus[4]<<endl;
  fout<<" "<<endl;
  fout<<" rhos from 0.675 to 1.0 "<<endl;
  fout<<"                         Sigma_ttj^0 (Pol1) = "<<par_aL[5]<<"("<<par_eaL[5]<<") + "<<par_bL[5]<<"("<<par_ebL[5]<<") *mt"<<endl;
  fout<<"                         dSigma_ttj^0 / dmt (Pol1)   = "<<par_bL[5]<<endl;
  fout<<"                         dSigma_ttj^0 / dmt (interp) = "<<(n3_mtplus[5]-n3_mtminus[5])<<endl;
  fout<<"                         values:, n3_mtminus= "<<n3_mtminus[5]<<" n3_mtplus= "<< n3_mt[5]<<" n3_mtplus= "<< n3_mtplus[5]<<endl;
  fout<<" "<<endl; 

  std::vector<double> der;
  for(int i=0; i<6; i++) der.push_back( (n3_mtplus[i]-n3_mtminus[i]) );//par_bL[i]);
  
  
  return der;

}



std::vector<double> R_LOderivative_wrong(TString scale="mu1", bool SecondOrder=false, bool draw=true, double mt=163){

  gROOT->Reset();

  gROOT->LoadMacro("AtlasStyle.C");
  gROOT->LoadMacro("AtlasLabels.C");
  SetAtlasStyle();
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);


  double up_height     = 0.8; // please tune so that the upper figures size will meet your requirement
  double dw_correction = 1.55;//1.40; // please tune so that the smaller canvas size will work in your environment
  double font_size_dw  = 0.05;
  double title_offset  = 1.;
  double title_size  = 0.075;
  double dw_height    = (1. - up_height) * dw_correction;

  double par_a[8], par_b[8], par_c[8];
  double par_ea[8], par_eb[8], par_ec[8];

  double par_aL[8], par_bL[8];
  double par_eaL[8], par_ebL[8];


  TString s_m159="../rootfiles/CT10_7TeV_mt159_"+scale+"_kt50_LO.root";
  TString s_m160="../rootfiles/CT10_7TeV_mt160_"+scale+"_kt50_LO.root";
  TString s_m161="../rootfiles/CT10_7TeV_mt161_"+scale+"_kt50_LO.root";
  TString s_m162="../rootfiles/CT10_7TeV_mt162_"+scale+"_kt50_LO.root";
  TString s_m163="../rootfiles/CT10_7TeV_mt163_"+scale+"_kt50_LO.root";
  TString s_m164="../rootfiles/CT10_7TeV_mt164_"+scale+"_kt50_LO.root";
  TString s_m165="../rootfiles/CT10_7TeV_mt165_"+scale+"_kt50_LO.root";
  TString s_m166="../rootfiles/CT10_7TeV_mt166_"+scale+"_kt50_LO.root";
  TString s_m167="../rootfiles/CT10_7TeV_mt167_"+scale+"_kt50_LO.root";

  TFile f_m159(s_m159);
  TGraphErrors* N3_0_mt159 = (TGraphErrors*) f_m159.Get("N3_0_ATLAS");
  Double_t *n3_mt159=N3_0_mt159->GetY();
  Double_t *en3_mt159=N3_0_mt159->GetEY();

  TFile f_m160(s_m160);
  TGraphErrors* N3_0_mt160 = (TGraphErrors*) f_m160.Get("N3_0_ATLAS");
  Double_t *n3_mt160=N3_0_mt160->GetY();
  Double_t *en3_mt160=N3_0_mt160->GetEY();

  TFile f_m161(s_m161);
  TGraphErrors* N3_0_mt161 = (TGraphErrors*) f_m161.Get("N3_0_ATLAS");
  Double_t *n3_mt161=N3_0_mt161->GetY();
  Double_t *en3_mt161=N3_0_mt161->GetEY();

  TFile f_m162(s_m162);
  TGraphErrors* N3_0_mt162 = (TGraphErrors*) f_m162.Get("N3_0_ATLAS");
  Double_t *n3_mt162=N3_0_mt162->GetY();
  Double_t *en3_mt162=N3_0_mt162->GetEY();

  TFile f_m163(s_m163);
  TGraphErrors* N3_0_mt163 = (TGraphErrors*) f_m163.Get("N3_0_ATLAS");
  Double_t *n3_mt163=N3_0_mt163->GetY();
  Double_t *en3_mt163=N3_0_mt163->GetEY();

  TFile f_m164(s_m164);
  TGraphErrors* N3_0_mt164 = (TGraphErrors*) f_m164.Get("N3_0_ATLAS");
  Double_t *n3_mt164=N3_0_mt164->GetY();
  Double_t *en3_mt164=N3_0_mt164->GetEY();

  TFile f_m165(s_m165);
  TGraphErrors* N3_0_mt165 = (TGraphErrors*) f_m165.Get("N3_0_ATLAS");
  Double_t *n3_mt165=N3_0_mt165->GetY();
  Double_t *en3_mt165=N3_0_mt165->GetEY();

  TFile f_m166(s_m166);
  TGraphErrors* N3_0_mt166 = (TGraphErrors*) f_m166.Get("N3_0_ATLAS");
  Double_t *n3_mt166=N3_0_mt166->GetY();
  Double_t *en3_mt166=N3_0_mt166->GetEY();

  TFile f_m167(s_m167);
  TGraphErrors* N3_0_mt167 = (TGraphErrors*) f_m167.Get("N3_0_ATLAS");
  Double_t *n3_mt167=N3_0_mt167->GetY();
  Double_t *en3_mt167=N3_0_mt167->GetEY();

 
  Double_t xmass[10], exmass[10];
  TMatrixD ybin(6,9);
  TMatrixD eybin(6,9);

  Double_t ybin1[10], ybin2[10], ybin3[10], ybin4[10], ybin5[10], ybin6[10];
  Double_t eybin1[10], eybin2[10], eybin3[10], eybin4[10], eybin5[10], eybin6[10];

  xmass[0]=159;  
  xmass[1]=160;  
  xmass[2]=161;  
  xmass[3]=162;  
  xmass[4]=163;
  xmass[5]=164;
  xmass[6]=165;
  xmass[7]=166;
  xmass[8]=167;

  for(int i=0; i<9; i++) {
    for(int j=0; j<6; j++) {
      ybin[j][i]=0;
      eybin[j][i]=0;
    }
  }

  for(int i=0; i<9; i++) {
    for(int j=0; j<6; j++) {
      if(i==0) ybin[j][i]=n3_mt159[j];
      if(i==1) ybin[j][i]=n3_mt160[j];
      if(i==2) ybin[j][i]=n3_mt161[j];
      if(i==3) ybin[j][i]=n3_mt162[j];
      if(i==4) ybin[j][i]=n3_mt163[j];
      if(i==5) ybin[j][i]=n3_mt164[j];
      if(i==6) ybin[j][i]=n3_mt165[j];
      if(i==7) ybin[j][i]=n3_mt166[j];
      if(i==8) ybin[j][i]=n3_mt167[j];

      if(i==0) eybin[j][i]=en3_mt159[j];
      if(i==1) eybin[j][i]=en3_mt160[j];
      if(i==2) eybin[j][i]=en3_mt161[j];
      if(i==3) eybin[j][i]=en3_mt162[j];
      if(i==4) eybin[j][i]=en3_mt163[j];
      if(i==5) eybin[j][i]=en3_mt164[j];
      if(i==6) eybin[j][i]=en3_mt165[j];
      if(i==7) eybin[j][i]=en3_mt166[j];
      if(i==8) eybin[j][i]=en3_mt167[j];
    }
  }

  for(int i=0; i<9; i++){

    ybin1[i]=0;
    ybin2[i]=0;
    ybin3[i]=0;
    ybin4[i]=0;
    ybin5[i]=0;
    ybin6[i]=0;

    eybin1[i]=0;
    eybin2[i]=0;
    eybin3[i]=0;
    eybin4[i]=0;
    eybin5[i]=0;
    eybin6[i]=0;

    ybin1[i]=ybin[0][i];
    ybin2[i]=ybin[1][i];
    ybin3[i]=ybin[2][i];
    ybin4[i]=ybin[3][i];
    ybin5[i]=ybin[4][i];
    ybin6[i]=ybin[5][i];

    eybin1[i]=eybin[0][i];
    eybin2[i]=eybin[1][i];
    eybin3[i]=eybin[2][i];
    eybin4[i]=eybin[3][i];
    eybin5[i]=eybin[4][i];
    eybin6[i]=eybin[5][i];

  }

  //  for(int i=0; i<5; i++) cout<<xmass[i]<<" "<<ybin1[i]<<" "<<eybin1[i]<<endl;

  TGraphErrors *bin1 = new TGraphErrors(9,xmass,ybin1,0,eybin1);
  TGraphErrors *bin2 = new TGraphErrors(9,xmass,ybin2,0,eybin2);
  TGraphErrors *bin3 = new TGraphErrors(9,xmass,ybin3,0,eybin3);
  TGraphErrors *bin4 = new TGraphErrors(9,xmass,ybin4,0,eybin4);
  TGraphErrors *bin5 = new TGraphErrors(9,xmass,ybin5,0,eybin5);
  TGraphErrors *bin6 = new TGraphErrors(9,xmass,ybin6,0,eybin6);


  // -------------------------------------------------------------------
  // Fit polynomial 1
  //----------------------------------------------------------------------

  TF1 *f2 = new TF1("f2", "[0]+[1]*(x)", -2, 2);
  bin1->Fit("f2","E");
  par_aL[0]=f2->GetParameter(0);  par_bL[0]=f2->GetParameter(1); 
  par_eaL[0]=f2->GetParError(0);  par_ebL[0]=f2->GetParError(1); 

  TF1 *f3 = new TF1("f3", "[0]+[1]*(x)", -2, 3);
  bin2->Fit("f3","E");
  par_aL[1]=f3->GetParameter(0);  par_bL[1]=f3->GetParameter(1); 
  par_eaL[1]=f3->GetParError(0);  par_ebL[1]=f3->GetParError(1); 
  
  TF1 *f4 = new TF1("f4", "[0]+[1]*(x)", -2, 3);
  bin3->Fit("f4","E");
  par_aL[2]=f4->GetParameter(0);  par_bL[2]=f4->GetParameter(1); 
  par_eaL[2]=f4->GetParError(0);  par_ebL[2]=f4->GetParError(1); 
 
  TF1 *f5 = new TF1("f5", "[0]+[1]*(x)", -2, 2);
  bin4->Fit("f5","E");
  par_aL[3]=f5->GetParameter(0);  par_bL[3]=f5->GetParameter(1); 
  par_eaL[3]=f5->GetParError(0);  par_ebL[3]=f5->GetParError(1); 

  TF1 *f6 = new TF1("f6", "[0]+[1]*(x)", -2, 2);
  bin5->Fit("f6","E");
  par_aL[4]=f6->GetParameter(0);  par_bL[4]=f6->GetParameter(1); 
  par_eaL[4]=f6->GetParError(0);  par_ebL[4]=f6->GetParError(1); 

  TF1 *f7 = new TF1("f7", "[0]+[1]*(x)", -2, 2);
  bin6->Fit("f7","E");
  par_aL[5]=f7->GetParameter(0);  par_bL[5]=f7->GetParameter(1); 
  par_eaL[5]=f7->GetParError(0);  par_ebL[5]=f7->GetParError(1); 

  // -------------------------------------------------------------------
  // Fit polynomial 2
  //----------------------------------------------------------------------
 
  TF1 *f2 = new TF1("f2", "[0]+[1]*(x)+[2]*pow(x,2)");
  bin1->Fit("f2","E");
  par_a[0]=f2->GetParameter(0);  par_b[0]=f2->GetParameter(1);  par_c[0]=f2->GetParameter(2); 
  par_ea[0]=f2->GetParError(0);  par_eb[0]=f2->GetParError(1);  par_ec[0]=f2->GetParError(2); 
    
  TF1 *f3 = new TF1("f3", "[0]+[1]*(x)+[2]*pow(x,2)");
  bin2->Fit("f3","E");
  par_a[1]=f3->GetParameter(0);  par_b[1]=f3->GetParameter(1);  par_c[1]=f3->GetParameter(2); 
  par_ea[1]=f2->GetParError(0);  par_eb[1]=f2->GetParError(1);  par_ec[1]=f2->GetParError(2); 

  TF1 *f4 = new TF1("f4", "[0]+[1]*(x)+[2]*pow(x,2)");
  bin3->Fit("f4","E");
  par_a[2]=f4->GetParameter(0);  par_b[2]=f4->GetParameter(1);  par_c[2]=f4->GetParameter(2); 
  par_ea[2]=f2->GetParError(0);  par_eb[2]=f2->GetParError(1);  par_ec[2]=f2->GetParError(2); 

  TF1 *f5 = new TF1("f5", "[0]+[1]*(x)+[2]*pow(x,2)");
  bin4->Fit("f5","E");
  par_a[3]=f5->GetParameter(0);  par_b[3]=f5->GetParameter(1);  par_c[3]=f5->GetParameter(2); 
  par_ea[3]=f2->GetParError(0);  par_eb[3]=f2->GetParError(1);  par_ec[3]=f2->GetParError(2); 
    
  TF1 *f6 = new TF1("f6", "[0]+[1]*(x)+[2]*pow(x,2)");
  bin5->Fit("f6","E");
  par_a[4]=f6->GetParameter(0);  par_b[4]=f6->GetParameter(1);  par_c[4]=f6->GetParameter(2);
  par_ea[4]=f2->GetParError(0);  par_eb[4]=f2->GetParError(1);  par_ec[4]=f2->GetParError(2); 

  TF1 *f7 = new TF1("f7", "[0]+[1]*(x)+[2]*pow(x,2)");
  bin6->Fit("f7","E");
  par_a[5]=f7->GetParameter(0);  par_b[5]=f7->GetParameter(1);  par_c[5]=f7->GetParameter(2);
  par_ea[5]=f2->GetParError(0);  par_eb[5]=f2->GetParError(1);  par_ec[5]=f2->GetParError(2); 

  if(draw==true){
    TCanvas *canvas= new TCanvas ("fit","fit",1800,1600);
    canvas->Divide(2,3);
    
    canvas->cd(1);
    // bin1->GetYaxis()->SetRangeUser(0.,0.5);    
    bin1->GetXaxis()->SetRangeUser(150,175);
    bin1->GetXaxis()->SetLabelSize(font_size_dw);
    bin1->GetYaxis()->SetLabelSize(font_size_dw);
    bin1->GetYaxis()->SetTitleSize(title_size);
    bin1->GetYaxis()->CenterTitle();
    bin1->GetYaxis()->SetTitleOffset(title_offset);
    if(scale== "mu1")    bin1->GetYaxis()->SetTitle("#sigma^{0} (m_{t}^{pole},#rho_{s},#mu=m_{t}^{pole})");
    if(scale== "mu05")    bin1->GetYaxis()->SetTitle("#sigma^{0} (m_{t}^{pole},#rho_{s},#mu=0.5 m_{t}^{pole})");
    if(scale== "mu2")    bin1->GetYaxis()->SetTitle("#sigma^{0} (m_{t}^{pole},#rho_{s},#mu=2  m_{t}^{pole})");

    bin1->GetXaxis()->SetTitle("m_{t}^{pole} [GeV]");
    
    bin1->SetLineWidth(1);
    bin1->SetLineColor(1);
    bin1->SetLineStyle(1);
    bin1->SetMarkerSize(0.8);
    bin1->SetMarkerStyle(4);
    bin1->SetMarkerColor(1);
    bin1->SetName("bin1");
    bin1->Draw("ap");
    
    myText(0.25,0.3,1,"t#bar{t}+1Jet @ NLO (fix. order) for 0<#rho_{s}<0.25");
    myText(0.25,0.2,1,"m_{t}^{pole} parametrization to a 2nd degree pol.");
    
    
    leg2 = new TLegend(0.5,0.75,0.9,0.9);
    leg2->AddEntry("bin1","t#bar{t}+1Jet @ NLO (fix. order)" ,"pe");
    leg2->AddEntry("bin1","best fit to a+b(m_{t}^{pole})+c(m_{t}^{pole})^{2}" ,"l");
    leg2->SetLineWidth(10);
    leg2->SetLineColor(0);
    leg2->SetFillColor(0);
    leg2->Draw(); 
    
    canvas->cd(2);
    //bin2->GetYaxis()->SetRangeUser(1.0,1.5);
    bin2->GetXaxis()->SetRangeUser(150,175);
    bin2->GetXaxis()->SetLabelSize(font_size_dw);
    bin2->GetYaxis()->SetLabelSize(font_size_dw);
    bin2->GetYaxis()->SetTitleSize(title_size);
    bin2->GetYaxis()->CenterTitle();
    bin2->GetYaxis()->SetTitleOffset(title_offset);
    if(scale== "mu1")    bin2->GetYaxis()->SetTitle("#sigma^{0} (m_{t}^{pole},#rho_{s},#mu=m_{t}^{pole})");
    if(scale== "mu05")   bin2->GetYaxis()->SetTitle("#sigma^{0} (m_{t}^{pole},#rho_{s},#mu=0.5 m_{t}^{pole})");
    if(scale== "mu2")    bin2->GetYaxis()->SetTitle("#sigma^{0} (m_{t}^{pole},#rho_{s},#mu=2  m_{t}^{pole})");
    bin2->GetXaxis()->SetTitle("m_{t}^{pole} [GeV]");
    
    bin2->SetLineWidth(1);
    bin2->SetLineColor(1);
    bin2->SetLineStyle(1);
    bin2->SetMarkerSize(0.8);
    bin2->SetMarkerStyle(4);
    bin2->SetMarkerColor(1);
    bin2->SetName("bin2");
    bin2->Draw("ap");
    
    myText(0.25,0.3,1,"t#bar{t}+1Jet @ NLO (fix. order) for 0.25<#rho_{s}<0.325");
    myText(0.25,0.2,1,"m_{t}^{pole} parametrization to a 2nd degree pol.");
    
    
    leg2 = new TLegend(0.5,0.75,0.9,0.9);
    leg2->AddEntry("bin2","t#bar{t}+1Jet @ NLO (fix. order)" ,"pe");
    leg2->AddEntry("bin2","best fit to a+b(m_{t}^{pole})+c(m_{t}^{pole})^{2}" ,"l");
    leg2->SetLineWidth(10);
    leg2->SetLineColor(0);
    leg2->SetFillColor(0);
    leg2->Draw();

    canvas->cd(3);
    //bin3->GetYaxis()->SetRangeUser(1.9,2.4);
    bin3->GetXaxis()->SetRangeUser(150,175);
    bin3->GetXaxis()->SetLabelSize(font_size_dw);
    bin3->GetYaxis()->SetLabelSize(font_size_dw);
    bin3->GetYaxis()->SetTitleSize(title_size);
    bin3->GetYaxis()->CenterTitle();
    bin3->GetYaxis()->SetTitleOffset(title_offset);
    if(scale== "mu1")    bin3->GetYaxis()->SetTitle("#sigma^{0} (m_{t}^{pole},#rho_{s},#mu=m_{t}^{pole})");
    if(scale== "mu05")   bin3->GetYaxis()->SetTitle("#sigma^{0} (m_{t}^{pole},#rho_{s},#mu=0.5 m_{t}^{pole})");
    if(scale== "mu2")    bin3->GetYaxis()->SetTitle("#sigma^{0} (m_{t}^{pole},#rho_{s},#mu=2  m_{t}^{pole})");
    bin3->GetXaxis()->SetTitle("m_{t}^{pole} [GeV]");
    
    bin3->SetLineWidth(1);
    bin3->SetLineColor(1);
    bin3->SetLineStyle(1);
    bin3->SetMarkerSize(0.8);
    bin3->SetMarkerStyle(4);
    bin3->SetMarkerColor(1);
    bin3->SetName("bin3");
    bin3->Draw("ap");

    myText(0.25,0.3,1,"t#bar{t}+1Jet @ NLO (fix. order) for 0.325<#rho_{s}<0.425");
    myText(0.25,0.2,1,"m_{t}^{pole} parametrization to a 2nd degree pol.");
   
    
    leg2 = new TLegend(0.5,0.75,0.9,0.9);
    leg2->AddEntry("bin3","t#bar{t}+1Jet @ NLO (fix. order)" ,"pe");
    leg2->AddEntry("bin3","best fit to a+b(m_{t}^{pole})+c(m_{t}^{pole})^{2}" ,"l");
    leg2->SetLineWidth(10);
    leg2->SetLineColor(0);
    leg2->SetFillColor(0);
    leg2->Draw();

    canvas->cd(4);
    //bin4->GetYaxis()->SetRangeUser(2.4,2.9);
    bin4->GetXaxis()->SetRangeUser(150,175);
    bin4->GetXaxis()->SetLabelSize(font_size_dw);
    bin4->GetYaxis()->SetLabelSize(font_size_dw);
    bin4->GetYaxis()->SetTitleSize(title_size);
    bin4->GetYaxis()->CenterTitle();
    bin4->GetYaxis()->SetTitleOffset(title_offset);
    if(scale== "mu1")    bin4->GetYaxis()->SetTitle("#sigma^{0} (m_{t}^{pole},#rho_{s},#mu=m_{t}^{pole})");
    if(scale== "mu05")   bin4->GetYaxis()->SetTitle("#sigma^{0} (m_{t}^{pole},#rho_{s},#mu=0.5 m_{t}^{pole})");
    if(scale== "mu2")    bin4->GetYaxis()->SetTitle("#sigma^{0} (m_{t}^{pole},#rho_{s},#mu=2  m_{t}^{pole})");
    bin4->GetXaxis()->SetTitle("m_{t}^{pole} [GeV]");
    
    bin4->SetLineWidth(1);
    bin4->SetLineColor(1);
    bin4->SetLineStyle(1);
    bin4->SetMarkerSize(0.8);
    bin4->SetMarkerStyle(4);
    bin4->SetMarkerColor(1);
    bin4->SetName("bin4");
    bin4->Draw("ap");

    myText(0.25,0.3,1,"t#bar{t}+1Jet @ NLO (fix. order) for 0.425<#rho_{s}<0.525");
    myText(0.25,0.2,1,"m_{t}^{pole} parametrization to a 2nd degree pol.");
   
    
    leg2 = new TLegend(0.5,0.75,0.9,0.9);
    leg2->AddEntry("bin4","t#bar{t}+1Jet @ NLO (fix. order)" ,"pe");
    leg2->AddEntry("bin4","best fit to a+b(m_{t}^{pole})+c(m_{t}^{pole})^{2}" ,"l");
    leg2->SetLineWidth(10);
    leg2->SetLineColor(0);
    leg2->SetFillColor(0);
    leg2->Draw();

    canvas->cd(5);
    //bin5->GetYaxis()->SetRangeUser(1.9,2.4);
    bin5->GetXaxis()->SetRangeUser(150,175);
    bin5->GetXaxis()->SetLabelSize(font_size_dw);
    bin5->GetYaxis()->SetLabelSize(font_size_dw);
    bin5->GetYaxis()->SetTitleSize(title_size);
    bin5->GetYaxis()->CenterTitle();
    bin5->GetYaxis()->SetTitleOffset(title_offset);
    if(scale== "mu1")    bin5->GetYaxis()->SetTitle("#sigma^{0} (m_{t}^{pole},#rho_{s},#mu=m_{t}^{pole})");
    if(scale== "mu05")   bin5->GetYaxis()->SetTitle("#sigma^{0} (m_{t}^{pole},#rho_{s},#mu=0.5 m_{t}^{pole})");
    if(scale== "mu2")    bin5->GetYaxis()->SetTitle("#sigma^{0} (m_{t}^{pole},#rho_{s},#mu=2  m_{t}^{pole})");
    bin5->GetXaxis()->SetTitle("m_{t}^{pole} [GeV]");
    
    bin5->SetLineWidth(1);
    bin5->SetLineColor(1);
    bin5->SetLineStyle(1);
    bin5->SetMarkerSize(0.8);
    bin5->SetMarkerStyle(4);
    bin5->SetMarkerColor(1);
    bin5->SetName("bin5");
    bin5->Draw("ap");

    myText(0.25,0.3,1,"t#bar{t}+1Jet @ NLO (fix. order) for 0.525<#rho_{s}<0.675");
    myText(0.25,0.2,1,"m_{t}^{pole} parametrization to a 2nd degree pol.");
   
    
    leg2 = new TLegend(0.5,0.75,0.9,0.9);
    leg2->AddEntry("bin5","t#bar{t}+1Jet @ NLO (fix. order)" ,"pe");
    leg2->AddEntry("bin5","best fit to a+b(m_{t}^{pole})+c(m_{t}^{pole})^{2}" ,"l");
    leg2->SetLineWidth(10);
    leg2->SetLineColor(0);
    leg2->SetFillColor(0);
    leg2->Draw();

    canvas->cd(6);
    //bin6->GetYaxis()->SetRangeUser(0.,0.5);
    bin6->GetXaxis()->SetRangeUser(150,175);
    bin6->GetXaxis()->SetLabelSize(font_size_dw);
    bin6->GetYaxis()->SetLabelSize(font_size_dw);
    bin6->GetYaxis()->SetTitleSize(title_size);
    bin6->GetYaxis()->CenterTitle();
    bin6->GetYaxis()->SetTitleOffset(title_offset);
    if(scale== "mu1")    bin6->GetYaxis()->SetTitle("#sigma^{0} (m_{t}^{pole},#rho_{s},#mu=m_{t}^{pole})");
    if(scale== "mu05")   bin6->GetYaxis()->SetTitle("#sigma^{0} (m_{t}^{pole},#rho_{s},#mu=0.5 m_{t}^{pole})");
    if(scale== "mu2")    bin6->GetYaxis()->SetTitle("#sigma^{0} (m_{t}^{pole},#rho_{s},#mu=2  m_{t}^{pole})");
    bin6->GetXaxis()->SetTitle("m_{t}^{pole} [GeV]");
    
    bin6->SetLineWidth(1);
    bin6->SetLineColor(1);
    bin6->SetLineStyle(1);
    bin6->SetMarkerSize(0.8);
    bin6->SetMarkerStyle(4);
    bin6->SetMarkerColor(1);
    bin6->SetName("bin6");
    bin6->Draw("ap");

    myText(0.25,0.3,1,"t#bar{t}+1Jet @ NLO (fix. order) for 0.675<#rho_{s}<1.0");
    myText(0.25,0.2,1,"m_{t}^{pole} parametrization to a 2nd degree pol.");
   
    
    leg2 = new TLegend(0.5,0.75,0.9,0.9);
    leg2->AddEntry("bin6","t#bar{t}+1Jet @ NLO (fix. order)" ,"pe");
    leg2->AddEntry("bin6","best fit to a+b(m_{t}^{pole})+c(m_{t}^{pole})^{2}" ,"l");
    leg2->SetLineWidth(10);
    leg2->SetLineColor(0);
    leg2->SetFillColor(0);
    leg2->Draw();

    canvas->Print("../logfiles/fitLO_"+scale+".eps");
  }
   

  ofstream fout ("../logfiles/fitLO.log");
  fout<<" "<<endl;
  fout<<" "<<endl;
  fout<<"//######################################################################################################### "<<endl;
  fout<<"   FIT TO LEADING ORDER"<<endl;
  fout<<"//######################################################################################################### "<<endl;
  fout<<" "<<endl;
  fout<<" "<<endl;
  fout<<" rhos from 0 to 0.25 "<<endl;
  fout<<"                         Sigma_ttj^0 (Pol1) = "<<par_aL[0]<<"("<<par_eaL[0]<<") + "<<par_bL[0]<<"("<<par_ebL[0]<<") *mt"<<endl;
  fout<<"                         dSigma_ttj^0 / dmt = "<<par_bL[0]<<endl;
  fout<<" "<<endl;
  fout<<"                         Sigma_ttj^0 (Pol2)= "<<par_a[0]<<"("<<par_ea[0]<<") + "<<par_b[0]<<"("<<par_eb[0]<<") *mt"<<" + "<<par_c[0]<<"("<<par_ec[0]<<") *mt^2"<<endl;
  fout<<"                         dSigma_ttj^0 / dmt = "<<par_b[0]<<"+"<<"2*mt*"<<par_c[0]<<endl;
  fout<<"                         dSigma_ttj^0 / dmt("<<mt<<") = "<<par_b[0]+2*mt*par_c[0]<<endl;
  fout<<" "<<endl;
  fout<<" rhos from 0.25 to 0.325 "<<endl;
  fout<<"                         Sigma_ttj^0 (Pol1) = "<<par_aL[1]<<"("<<par_eaL[1]<<") + "<<par_bL[1]<<"("<<par_ebL[1]<<") *mt"<<endl;
  fout<<"                         dSigma_ttj^0 / dmt = "<<par_bL[1]<<endl;
  fout<<" "<<endl;
  fout<<"                         Sigma_ttj^0 (Pol2)= "<<par_a[1]<<"("<<par_ea[1]<<") + "<<par_b[1]<<"("<<par_eb[1]<<") *mt"<<" + "<<par_c[1]<<"("<<par_ec[1]<<") *mt^2"<<endl;
  fout<<"                         dSigma_ttj^0 / dmt = "<<par_b[1]<<"+"<<"2*mt*"<<par_c[1]<<endl;
  fout<<"                         dSigma_ttj^0 / dmt("<<mt<<") = "<<par_b[1]+2*mt*par_c[1]<<endl;
  fout<<" "<<endl;
  fout<<" rhos from 0.325 to 0.425 "<<endl;
  fout<<"                         Sigma_ttj^0 (Pol1) = "<<par_aL[2]<<"("<<par_eaL[2]<<") + "<<par_bL[2]<<"("<<par_ebL[2]<<") *mt"<<endl;
  fout<<"                         dSigma_ttj^0 / dmt = "<<par_bL[2]<<endl;
  fout<<" "<<endl;
  fout<<"                         Sigma_ttj^0 (Pol2)= "<<par_a[2]<<"("<<par_ea[2]<<") + "<<par_b[2]<<"("<<par_eb[2]<<") *mt"<<" + "<<par_c[2]<<"("<<par_ec[2]<<") *mt^2"<<endl;
  fout<<"                         dSigma_ttj^0 / dmt = "<<par_b[2]<<"+"<<"2*mt*"<<par_c[2]<<endl;
  fout<<"                         dSigma_ttj^0 / dmt("<<mt<<") = "<<par_b[2]+2*mt*par_c[2]<<endl;
  fout<<" "<<endl;
  fout<<" rhos from 0.425 to 0.525 "<<endl;
  fout<<"                         Sigma_ttj^0 (Pol1) = "<<par_aL[3]<<"("<<par_eaL[3]<<") + "<<par_bL[3]<<"("<<par_ebL[3]<<") *mt"<<endl;
  fout<<"                         dSigma_ttj^0 / dmt = "<<par_bL[3]<<endl;
  fout<<" "<<endl;
  fout<<"                         Sigma_ttj^0 (Pol2)= "<<par_a[3]<<"("<<par_ea[3]<<") + "<<par_b[3]<<"("<<par_eb[3]<<") *mt"<<" + "<<par_c[3]<<"("<<par_ec[3]<<") *mt^2"<<endl;
  fout<<"                         dSigma_ttj^0 / dmt = "<<par_b[3]<<"+"<<"2*mt*"<<par_c[3]<<endl;
  fout<<"                         dSigma_ttj^0 / dmt("<<mt<<") = "<<par_b[3]+2*mt*par_c[3]<<endl;
  fout<<" "<<endl;
  fout<<" rhos from 0.525 to 0.675 "<<endl;
  fout<<"                         Sigma_ttj^0 (Pol1) = "<<par_aL[4]<<"("<<par_eaL[4]<<") + "<<par_bL[4]<<"("<<par_ebL[4]<<") *mt"<<endl;
  fout<<"                         dSigma_ttj^0 / dmt = "<<par_bL[4]<<endl;
  fout<<" "<<endl;
  fout<<"                         Sigma_ttj^0 (Pol2)= "<<par_a[4]<<"("<<par_ea[4]<<") + "<<par_b[4]<<"("<<par_eb[4]<<") *mt"<<" + "<<par_c[4]<<"("<<par_ec[4]<<") *mt^2"<<endl;
  fout<<"                         dSigma_ttj^0 / dmt = "<<par_b[4]<<"+"<<"2*mt*"<<par_c[4]<<endl;
  fout<<"                         dSigma_ttj^0 / dmt("<<mt<<") = "<<par_b[4]+2*mt*par_c[4]<<endl;
  fout<<" "<<endl;
  fout<<" rhos from 0.675 to 1.0 "<<endl;
  fout<<"                         Sigma_ttj^0 (Pol1) = "<<par_aL[5]<<"("<<par_eaL[5]<<") + "<<par_bL[5]<<"("<<par_ebL[5]<<") *mt"<<endl;
  fout<<"                         dSigma_ttj^0 / dmt = "<<par_bL[5]<<endl;
  fout<<" "<<endl;
  fout<<"                         Sigma_ttj^0 (Pol2)= "<<par_a[5]<<"("<<par_ea[5]<<") + "<<par_b[5]<<"("<<par_eb[5]<<") *mt"<<" + "<<par_c[5]<<"("<<par_ec[5]<<") *mt^2"<<endl;
  fout<<"                         dSigma_ttj^0 / dmt = "<<par_b[5]<<"+"<<"2*mt*"<<par_c[5]<<endl;
  fout<<"                         dSigma_ttj^0 / dmt("<<mt<<") = "<<par_b[5]+2*mt*par_c[5]<<endl;
  fout<<" "<<endl;

  std::vector<double> der;
  if(SecondOrder==true) {
    for(int i=0; i<6; i++) der.push_back(par_b[i]+2*mt*par_c[i]);
  } else {
    for(int i=0; i<6; i++) der.push_back(par_bL[i]);
  }
  
  return der;

}


