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
#include "TString.h"

using namespace std;

//  for(int i=0; i<2 ; i++) {

double as(TString folder="../../roofiles/", TString energy ="LHC13", TString pdf ="CT10",TString mt="164", TString scale="1"){

  TString s_mt=folder+energy+"_"+pdf+"_mt"+mt+"_pt30_mu"+scale+".root";

  cout<<" ------------------------------ " <<s_mt<<endl;
  TFile f_mt(s_mt);
  TVectorD* alphaspi = (TVectorD*) f_mt.Get("alphas_over_pi");

  double value = ( (*alphaspi) )[0];
  cout<<value<<endl;
  return value;

}


std::vector<double> get_Distribution(TString folder="../../roofiles/", TString energy ="LHC13", TString pdf ="CT10",TString distribution="n3_24_pt30",TString mt="164", TString scale="1"){

  TString s_mt=folder+energy+"_"+pdf+"_mt"+mt+"_pt30_mu"+scale+".root";
  cout<<s_mt<<endl;
  TFile f_mt(s_mt);
  TGraphErrors* N3_mt = (TGraphErrors*) f_mt.Get(distribution);
  Double_t *n3_mt=N3_mt->GetY();
  Double_t *en3_mt=N3_mt->GetEY();

  std::vector<double> value;
  for(int i=0; i<N3_mt->GetN(); i++) {
    value.push_back(n3_mt[i]);
    value.push_back(en3_mt[i]);
  }
 
  return value;

}

std::vector<double> width_bin(TString folder="../../roofiles/", TString energy ="LHC13", TString pdf ="CT10", TString distribution="n3_24_pt30",TString mt="164", TString scale="1"){

  TString s_mt=folder+energy+"_"+pdf+"_mt"+mt+"_pt30_mu"+scale+".root";
  cout<<" width_bin "<<s_mt<<endl;
  
  TFile *f_mt = new TFile(s_mt,"READ");
  TGraphErrors* N3_mt = (TGraphErrors*) f_mt->Get(distribution);
  Double_t *en3_mt=N3_mt->GetEX();

  std::vector<double> value;
  for(int i=0; i<N3_mt->GetN(); i++) {
    value.push_back(en3_mt[i]);
  }
  
  cout<<" aaa" <<endl;
  f_mt->Close();
  cout<<" aaa" <<endl;

  return value;

}

std::vector<double> bin(TString folder="../../roofiles/", TString energy ="LHC13", TString pdf ="CT10",TString distribution="n3_24_pt30",TString mt="164", TString scale="1"){

  TString s_mt=folder+energy+"_"+pdf+"_mt"+mt+"_pt30_mu"+scale+".root";
  cout<<" bins "<<s_mt<<endl;

  TFile f_mt(s_mt);
  TGraphErrors* N3_mt = (TGraphErrors*) f_mt.Get(distribution);
  Double_t *n3_mt=N3_mt->GetX();

  std::vector<double> value;
  for(int i=0; i<N3_mt->GetN(); i++) {
    value.push_back(n3_mt[i]);
  }
  
  f_mt.Close();
  return value;

}

std::vector<double> get_LOderivative_5p(TString folder="../../roofiles/", TString energy ="LHC13", TString pdf ="CT10",TString distribution="n3_24_pt30_LO", float mt_value=164, TString scale="1", double delta=0.5, bool draw=false){


  double par_aL[100], par_bL[100];
  double par_eaL[100], par_ebL[100];

  TString mt=TString::Format("%.f",mt_value);
  TString mtplus2=TString::Format("%.0f",mt_value+2*delta);
  TString mtplus=TString::Format("%.1f",mt_value+delta);
  TString mtminus=TString::Format("%.1f",mt_value-delta);
  TString mtminus2=TString::Format("%.0f",mt_value-2*delta);

  cout<<mt<<" "<<mtminus<<" "<<mtplus<<endl;

  TString s_mtminus2=folder+energy+"_"+pdf+"_mt"+mtminus2+"_pt30_mu"+scale+".root";
  TString s_mtminus=folder+energy+"_"+pdf+"_mt"+mtminus+"_pt30_mu"+scale+".root";
  TString s_mt=folder+energy+"_"+pdf+"_mt"+mt+"_pt30_mu"+scale+".root";
  TString s_mtplus=folder+energy+"_"+pdf+"_mt"+mtplus+"_pt30_mu"+scale+".root";
  TString s_mtplus2=folder+energy+"_"+pdf+"_mt"+mtplus2+"_pt30_mu"+scale+".root";


  TFile f_mtminus2(s_mtminus2);
  TGraphErrors* N3_mtminus2 = (TGraphErrors*) f_mtminus2.Get(distribution);
  Double_t *n3_mtminus2=N3_mtminus2->GetY();
  Double_t *en3_mtminus2=N3_mtminus2->GetEY();

  TFile f_mtminus(s_mtminus);
  TGraphErrors* N3_mtminus = (TGraphErrors*) f_mtminus.Get(distribution);
  Double_t *n3_mtminus=N3_mtminus->GetY();
  Double_t *en3_mtminus=N3_mtminus->GetEY();

  TFile f_mt(s_mt);
  TGraphErrors* N3_mt = (TGraphErrors*) f_mt.Get(distribution);
  Double_t *n3_mt=N3_mt->GetY();
  Double_t *en3_mt=N3_mt->GetEY();

  TFile f_mtplus(s_mtplus);
  TGraphErrors* N3_mtplus = (TGraphErrors*) f_mtplus.Get(distribution);
  Double_t *n3_mtplus=N3_mtplus->GetY();
  Double_t *en3_mtplus=N3_mtplus->GetEY();

  TFile f_mtplus2(s_mtplus2);
  TGraphErrors* N3_mtplus2 = (TGraphErrors*) f_mtplus2.Get(distribution);
  Double_t *n3_mtplus2=N3_mtplus2->GetY();
  Double_t *en3_mtplus2=N3_mtplus2->GetEY();
  int nbins=N3_mtplus2->GetN();

  double ybin[100][5];
  double eybin[100][5];
  double xmass[100][5], exmass[100][5];
 
  TGraphErrors *bin[100];

  int nbins_positive[100];
  
  for(int j=0; j<nbins; j++) {
    
    xmass[j][0]=mt_value-2*delta;  
    xmass[j][1]=mt_value-delta;  
    xmass[j][2]=mt_value;
    xmass[j][3]=mt_value+delta;
    xmass[j][4]=mt_value+2*delta;

    for(int i=0; i<5; i++) {

      exmass[j][i]=0;
  
      ybin[j][i]=0;
      eybin[j][i]=0;
      
      if(i==0) ybin[j][i]=n3_mtminus2[j];
      if(i==1) ybin[j][i]=n3_mtminus[j];
      if(i==2) ybin[j][i]=n3_mt[j];
      if(i==3) ybin[j][i]=n3_mtplus[j];
      if(i==4) ybin[j][i]=n3_mtplus2[j];

      if(i==0) eybin[j][i]=en3_mtminus2[j];
      if(i==1) eybin[j][i]=en3_mtminus[j];
      if(i==2) eybin[j][i]=en3_mt[j];
      if(i==3) eybin[j][i]=en3_mtplus[j];
      if(i==4) eybin[j][i]=en3_mtplus2[j];

      //   if(ybin[j][i] > 0 ) nbins_positive[j][i]=1;
    }
    nbins_positive[j]=0;
    for(int i=0; i<5; i++) {
      if(ybin[j][i] > 0 ) {
	ybin[j][nbins_positive[j]]=ybin[j][i];
	eybin[j][nbins_positive[j]]=eybin[j][i];
	xmass[j][nbins_positive[j]]=xmass[j][i];
	nbins_positive[j]++;
      }
    }
  }

  f_mt.Close();
  f_mtplus.Close();
  f_mtminus.Close();

  for(int j=0; j<nbins; j++)  bin[j] = new TGraphErrors(nbins_positive[j],xmass[j],ybin[j],exmass[j],eybin[j]);



  // -------------------------------------------------------------------
  // Fit polynomial 1
  //----------------------------------------------------------------------

  for(int j=0; j<nbins; j++) {
      TF1 *f2 = new TF1("f2", "[0]+[1]*(x)", 150, 170);
      bin[j]->Fit("f2","E");
      par_aL[j]=f2->GetParameter(0);  par_bL[j]=f2->GetParameter(1); 
      par_eaL[j]=f2->GetParError(0);  par_ebL[j]=f2->GetParError(1);
  }

  if(draw==true) {
    gROOT->Reset();
    gStyle->SetOptFit(0);
    gStyle->SetOptStat(0);
    gStyle->SetTitle(0);


    double up_height     = 0.8; // please tune so that the upper figures size will meet your requirement
    double dw_correction = 1.55;//1.40; // please tune so that the smaller canvas size will work in your environment
    double font_size_dw  = 0.03;
    double title_offset  = 1.1;
    double title_size  = 0.05;
    double dw_height    = (1. - up_height) * dw_correction;
  
    TCanvas *canvas= new TCanvas ("fit","fit",1800,1600);
    canvas->Divide(3,3);//nbins/3+1,3);

    TLegend *leg2= new TLegend(0.75,0.6,0.85,0.85);

    for(int j=0; j<nbins; j++) {

      canvas->cd(j+1);
      TF1 *f2 = new TF1("f2", "[0]+[1]*(x)", 150, 170);
      bin[j]->Fit("f2","E");
      par_aL[j]=f2->GetParameter(0);  par_bL[j]=f2->GetParameter(1);
      par_eaL[j]=f2->GetParError(0);  par_ebL[j]=f2->GetParError(1);
    
      bin[j]->SetTitle(TString::Format("bin %i",j));
      // bin[j]->GetYaxis()->SetRangeUser(0.,0.5);
      bin[j]->GetXaxis()->SetRangeUser(150,175);
      bin[j]->GetXaxis()->SetLabelSize(font_size_dw);
      bin[j]->GetYaxis()->SetLabelSize(font_size_dw);
      bin[j]->GetYaxis()->SetTitleSize(title_size);
      bin[j]->GetXaxis()->SetTitleSize(title_size);
      // bin[j]->GetYaxis()->CenterTitle();
      bin[j]->GetYaxis()->SetTitleOffset(title_offset);
      if(scale== "mu1")    bin[j]->GetYaxis()->SetTitle(distribution+"^{0} (m_{t}^{pole},#rho_{s},#mu=m_{t}^{pole})");
      if(scale== "mu05")    bin[j]->GetYaxis()->SetTitle(distribution+"^{0} (m_{t}^{pole},#rho_{s},#mu=0.5 m_{t}^{pole})");
      if(scale== "mu2")    bin[j]->GetYaxis()->SetTitle(distribution+"^{0} (m_{t}^{pole},#rho_{s},#mu=2  m_{t}^{pole})");

      bin[j]->GetXaxis()->SetTitle("m_{t}^{pole} [GeV]");
      bin[j]->GetYaxis()->SetTitle("#sigma [fb]");

      bin[j]->SetLineWidth(1);
      bin[j]->SetLineColor(1);
      bin[j]->SetLineStyle(1);
      bin[j]->SetMarkerSize(0.8);
      bin[j]->SetMarkerStyle(4);
      bin[j]->SetMarkerColor(1);
      bin[j]->SetName("bin[j]");
      bin[j]->Draw("ap");
    
      if(j==0) {
    	leg2 = new TLegend(0.5,0.75,0.9,0.9);
    	leg2->AddEntry(bin[j],"t#bar{t}+1Jet @ NLO (fix. order)" ,"pe");
    	leg2->AddEntry(f2,"best fit to a+b(m_{t}^{pole})" ,"l");
    	leg2->SetLineWidth(10);
    	leg2->SetLineColor(0);
    	leg2->SetFillColor(0);
      }
      leg2->Draw();
    }

    canvas->Print("../../logfiles/"+distribution+"fitLO_mt"+mt+"_"+scale+".eps");
  } 

  ofstream fout ("../../logfiles/conversion/fitLO_"+distribution+"_mt"+mt+"_"+scale+TString::Format("_deltaM_%.1f.log",delta).Data());
  

  fout<<" "<<endl;
  fout<<" "<<endl;
  fout<<"######################################################################################################### "<<endl;
  fout<<"#   FIT TO LEADING ORDER"<<endl;
  fout<<"######################################################################################################### "<<endl;
  fout<<" "<<endl;
  fout<<" "<<endl;
  fout<<"#   "<<distribution<<endl;
  for(int j=0; j<nbins; j++) {
    double fivepoints1=(n3_mtplus2[j]-n3_mtminus2[j])/(4.*delta);
    double threepoints=(n3_mtplus[j]-n3_mtminus[j])/(2*delta);
    double fivepoints= (fivepoints1+threepoints)/2.;

    fout<<" bin:  "<<j<<endl;
    fout<<"                         Sigma_ttj^0 (Pol1)          = "<<par_aL[j]<<"("<<par_eaL[j]<<") + "<<par_bL[j]<<"("<<par_ebL[j]<<") *mt"<<endl;
    fout<<"                         dSigma_ttj^0 / dmt (Pol1)   = "<<par_bL[j]<< " +- "<<par_ebL[j]<<endl;
    fout<<"                         dSigma_ttj^0 / dmt (interp) 3p= "<<threepoints<<endl;
    fout<<"                         dSigma_ttj^0 / dmt (interp) 5p= "<<fivepoints1<<endl;
    fout<<"                         dSigma_ttj^0 / dmt (interp) 5p, average= "<<fivepoints<<endl;
    fout<<"                         values:, "<<distribution<<"_mtminus= "<<n3_mtminus[j]<<" "<<distribution<<"_mtplus= "<< n3_mt[j]<<" "<<distribution<<"_mtplus= "<< n3_mtplus[j]<<endl;
    fout<<" "<<endl;
  }
    
  std::vector<double> der;
  for(int i=0; i<nbins; i++) {
    double fivepoints=(n3_mtplus2[i]-n3_mtplus[i])/delta + (n3_mtplus[i]-n3_mt[i])/delta + (n3_mt[i]-n3_mtminus[i])/delta + (n3_mtminus[i]-n3_mtminus2[i])/delta ;
    //  der.push_back(fivepoints/4.);
    der.push_back(par_bL[i]);
    der.push_back(par_ebL[i]);

  }
    
  return der;

}


std::vector<double> get_LOderivative(TString folder="../../roofiles/", TString energy ="LHC13", TString pdf ="CT10",TString distribution="n3_24_pt30_LO", float mt_value=164, TString scale="1", double delta=0.5, bool draw=true){

  gROOT->Reset();
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);


  double up_height     = 0.8; // please tune so that the upper figures size will meet your requirement
  double dw_correction = 1.55;//1.40; // please tune so that the smaller canvas size will work in your environment
  double font_size_dw  = 0.05;
  double title_offset  = 1.;
  double title_size  = 0.075;
  double dw_height    = (1. - up_height) * dw_correction;

  double par_a[100], par_b[100], par_c[100];
  double par_ea[100], par_eb[100], par_ec[100];

  double par_aL[100], par_bL[100];
  double par_eaL[100], par_ebL[100];

  TString mt=TString::Format("%.f",mt_value);
  TString mtplus=TString::Format("%.1f",mt_value+delta);
  TString mtminus=TString::Format("%.1f",mt_value-delta);
  cout<<mt<<" "<<mtminus<<" "<<mtplus<<endl;

  TString s_mtminus=folder+energy+"_"+pdf+"_mt"+mtminus+"_pt30_mu"+scale+".root";
  TString s_mt=folder+energy+"_"+pdf+"_mt"+mt+"_pt30_mu"+scale+".root";
  TString s_mtplus=folder+energy+"_"+pdf+"_mt"+mtplus+"_pt30_mu"+scale+".root";


  TFile f_mtminus(s_mtminus);
  cout<<s_mtminus<<" "<<distribution<<endl;
  TGraphErrors* N3_mtminus = (TGraphErrors*) f_mtminus.Get(distribution);
  Double_t *n3_mtminus=N3_mtminus->GetY();
  Double_t *en3_mtminus=N3_mtminus->GetEY();

  TFile f_mt(s_mt);
  TGraphErrors* N3_mt = (TGraphErrors*) f_mt.Get(distribution);
  Double_t *n3_mt=N3_mt->GetY();
  Double_t *en3_mt=N3_mt->GetEY();

  TFile f_mtplus(s_mtplus);
  TGraphErrors* N3_mtplus = (TGraphErrors*) f_mtplus.Get(distribution);
  Double_t *n3_mtplus=N3_mtplus->GetY();
  Double_t *en3_mtplus=N3_mtplus->GetEY();
  int nbins=N3_mtplus->GetN();

  double ybin[100][3];
  double eybin[100][3];
  double xmass[100][3], exmass[100][3];
 
  TGraphErrors *bin[100];

  for(int j=0; j<nbins; j++) {
    xmass[j][0]=mt_value-delta;  
    xmass[j][1]=mt_value;  
    xmass[j][2]=mt_value+delta;
      
    for(int i=0; i<3; i++) {

      exmass[j][i]=0;
  
      ybin[j][i]=0;
      eybin[j][i]=0;
      
      if(i==0) ybin[j][i]=n3_mtminus[j];
      if(i==1) ybin[j][i]=n3_mt[j];
      if(i==2) ybin[j][i]=n3_mtplus[j];
      
      if(i==0) eybin[j][i]=en3_mtminus[j];
      if(i==1) eybin[j][i]=en3_mt[j];
      if(i==2) eybin[j][i]=en3_mtplus[j];

    }
  }

  f_mt.Close();
  f_mtplus.Close();
  f_mtminus.Close();

  for(int j=0; j<nbins; j++)  bin[j] = new TGraphErrors(3,xmass[j],ybin[j],exmass[j],eybin[j]);



  // -------------------------------------------------------------------
  // Fit polynomial 1
  //----------------------------------------------------------------------

  for(int j=0; j<nbins; j++) {
    TF1 *f2 = new TF1("f2", "[0]+[1]*(x)", -2, 2);
    bin[j]->Fit("f2","E");
    par_aL[j]=f2->GetParameter(0);  par_bL[j]=f2->GetParameter(1); 
    par_eaL[j]=f2->GetParError(0);  par_ebL[j]=f2->GetParError(1);
  }

  if(draw==true){
    TCanvas *canvas= new TCanvas ("fit","fit",1800,1600);
    canvas->Divide(nbins/3+1,3);

    TLegend *leg2= new TLegend(0.75,0.6,0.85,0.85);

    for(int j=0; j<nbins; j++) {

      canvas->cd(j+1);
      // bin[j]->GetYaxis()->SetRangeUser(0.,0.5);    
      bin[j]->GetXaxis()->SetRangeUser(150,175);
      bin[j]->GetXaxis()->SetLabelSize(font_size_dw);
      bin[j]->GetYaxis()->SetLabelSize(font_size_dw);
      bin[j]->GetYaxis()->SetTitleSize(title_size);
      bin[j]->GetYaxis()->CenterTitle();
      bin[j]->GetYaxis()->SetTitleOffset(title_offset);
      if(scale== "mu1")    bin[j]->GetYaxis()->SetTitle(distribution+"^{0} (m_{t}^{pole},#rho_{s},#mu=m_{t}^{pole})");
      if(scale== "mu05")    bin[j]->GetYaxis()->SetTitle(distribution+"^{0} (m_{t}^{pole},#rho_{s},#mu=0.5 m_{t}^{pole})");
      if(scale== "mu2")    bin[j]->GetYaxis()->SetTitle(distribution+"^{0} (m_{t}^{pole},#rho_{s},#mu=2  m_{t}^{pole})");

      bin[j]->GetXaxis()->SetTitle("m_{t}^{pole} [GeV]");
    
      bin[j]->SetLineWidth(1);
      bin[j]->SetLineColor(1);
      bin[j]->SetLineStyle(1);
      bin[j]->SetMarkerSize(0.8);
      bin[j]->SetMarkerStyle(4);
      bin[j]->SetMarkerColor(1);
      bin[j]->SetName("bin[j]");
      bin[j]->Draw("ap");
    
      if(j==0) {
	leg2 = new TLegend(0.5,0.75,0.9,0.9);
	leg2->AddEntry(bin[j],"t#bar{t}+1Jet @ NLO (fix. order)" ,"pe");
	leg2->AddEntry(bin[j],"best fit to a+b(m_{t}^{pole})" ,"l");
	leg2->SetLineWidth(10);
	leg2->SetLineColor(0);
	leg2->SetFillColor(0);
      }
      leg2->Draw(); 
    }

    canvas->Print("../../logfiles/conversion/"+distribution+"fitLO_mt"+mt+"_"+scale+".eps");
  }
   

  ofstream fout ("../../logfiles/conversion/fitLO_"+distribution+"_mt"+mt+"_"+scale+TString::Format("_deltaM_%.1f.log",delta).Data());

  /* for(int i=0; i<nbins; i++) {
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
     //    if( (n3_mtplus[i]-n3_mtminus[i]) > 0.0) {
     //  cout<< " Wrong derivative sign for bin "<< i <<endl;
     //  fout<< " Wrong derivative sign for bin "<< i <<endl;
     // }
     }*/


  fout<<" "<<endl;
  fout<<" "<<endl;
  fout<<"######################################################################################################### "<<endl;
  fout<<"#   FIT TO LEADING ORDER"<<endl;
  fout<<"######################################################################################################### "<<endl;
  fout<<" "<<endl;
  fout<<" "<<endl;
  fout<<"#   "<<distribution<<endl;
  for(int j=0; j<nbins; j++) {
    fout<<" bin:  "<<j<<endl;
    fout<<"                         Sigma_ttj^0 (Pol1)          = "<<par_aL[j]<<"("<<par_eaL[j]<<") + "<<par_bL[j]<<"("<<par_ebL[j]<<") *mt"<<endl;
    fout<<"                         dSigma_ttj^0 / dmt (Pol1)   = "<<par_bL[j]<<endl;
    fout<<"                         dSigma_ttj^0 / dmt (interp) = "<<(n3_mtplus[j]-n3_mtminus[j])/(2.*delta)<<endl;
    fout<<"                         values:, "<<distribution<<"_mtminus= "<<n3_mtminus[j]<<" "<<distribution<<"_mtplus= "<< n3_mt[j]<<" "<<distribution<<"_mtplus= "<< n3_mtplus[j]<<endl;
    fout<<" "<<endl;
  }
    
  std::vector<double> der;
  for(int i=0; i<nbins; i++) der.push_back(par_bL[i]);//(n3_mtplus[i]-n3_mtminus[i]) );//par_bL[i]);
    
  return der;

}
