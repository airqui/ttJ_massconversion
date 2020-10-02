#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include "TFile.h"
#include "TNtuple.h"
#include "TMath.h"
#include "TMatrixD.h"
#include "TTree.h"
#include "TLorentzVector.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TH1F.h"
#include "TF1.h"
#include "TH1.h"
#include "TH2F.h"
#include "TImage.h"
#include "../include/Plots.h"

Double_t z[100],ez[100], rho[100],erho[100];
Double_t par_a[100],par_b[100], par_c[100];
int bintoremove=9;
double mass=0;
double emass=0;

double integral_recorded=0;

const Int_t nbins=12;

double bin_size=1.2/double(nbins);
//______________________________________________________________________________

Double_t func_pol1(int i,Double_t *par)
{
  Double_t value;
  value=(par_a[i]+par_b[i]*(par[0]-173.)+par_c[i]*(par[0]-173.)*(par[0]-173));
   // value=z[i];
  return value;
 
}

double func_pol1_(int i, double calc_m)
{
  Double_t value;
  value=(par_a[i]+par_b[i]*(calc_m-173.));
   // value=z[i];
  return value;
 
}

//______________________________________________________________________________
void fcn_theory(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
{
  Int_t i;
  
  //calculate chisquare
  Double_t chisq = 0;
  Double_t delta;

  for (i=0;i<nbins; i++) {
    if(i!=bintoremove && z[i]>0 && func_pol1(i,par)>0) {
      delta  = pow(z[i]-integral_recorded*bin_size*func_pol1(i,par),2)/(bin_size*func_pol1(i,par));
      chisq += delta;
    }
  }
  f = chisq;
}

//______________________________________________________________________________
void fcn_error(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
{
  Int_t i;
  
  //calculate chisquare
  Double_t chisq = 0;
  Double_t delta;

  for (i=2;i<nbins; i++) {
    if(i!=bintoremove && z[i]>0 && func_pol1(i,par)>0) {
      delta  = pow(z[i]-func_pol1(i,par),2)/(ez[i]);//(integral_recorded*bin_size*func_pol1(i,par));
      //      cout<<i<<" "<<z[i]<<" "<<integral_recorded*bin_size*func_pol1(i,par)<<" "<<integral_recorded<<" "<<func_pol1(i,par)<<endl;
      chisq += delta;
    }
  }
  f = chisq;
}

void parametrize_fitfunction(TString pdf="CT10",TString energy="13TeV", int mass=170, int interval=10, int step=1, TString scheme="pole", TString scale="mu1", TString title="n3_24_pt50")
{

  gROOT->Reset();
  SetAtlasStyle();
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);

  std::vector<TGraphErrors *> masspoints;
  for(int i=0; i<interval; i++){
    TString mt="_mt";
    if(scheme == "running" ) mt="_mtrun";
     TString file="../../rootfiles_LHC13_1/"+energy+"_"+pdf+mt+TString::Format("%i",mass+i)+"_pt30_"+scale+".root";
     masspoints.push_back(readGraph(file,title,true));
  }

  std::vector<TGraphErrors *> bin;

  for(int i=0; i<masspoints.at(0)->GetN(); i++) {

    double yv[100], xv[100], eyv[100], exv[100];
    int n=0;

    for(int j=0; j<masspoints.size(); j++){
      
      Double_t *y=masspoints.at(j)->GetY();
      Double_t *ey=masspoints.at(j)->GetEY();
      yv[j]=y[i];
      eyv[j]=ey[i]; 
      xv[j]=double(mass)+double(j)*double(step);
      //      cout<<i<<" "<<j<<" "<<xv[j]<<" "<<yv[j]<<endl;
      exv[j]=0;
      n++;
    }
    TGraphErrors * temp = new TGraphErrors(n,xv,yv,exv,eyv);
    bin.push_back(temp);
  }

  //  TCanvas *canvas= new TCanvas ("fit1","fit1",1200,1800);
  //canvas->Divide(5,5);
  

  for(int i=0; i<masspoints.at(0)->GetN(); i++) {
    TF1 *ftemp = new TF1("ftemp", "[0]+[1]*(x-173)+[2]*(x-173)*(x-173)");
    bin.at(i)->Fit("ftemp","EQ");
    par_a[i]=ftemp->GetParameter(0);
    par_b[i]=ftemp->GetParameter(1);
    par_c[i]=ftemp->GetParameter(2);

    //canvas->cd(i+1);
    //bin.at(i)->GetYaxis()->SetRangeUser(0,3);
    //bin.at(i)->Draw("alp");
    
  }


}



void Fit(bool error = true){

  //for(int i=0; i<4; i++) std::cout<<z[i]<<" "<<rho[i]<<"    ....     "<<std::endl;

  TMinuit *gMinuit = new TMinuit(1);  //initialize TMinuit with a maximm of 5 params
  if (error == true) gMinuit->SetFCN(fcn_error);
  else gMinuit->SetFCN(fcn_theory);

  //gMinuit->SetFCN(fcn_cov);

  // gMinuit->mnhelp("*");
  // gMinuit->mnhelp("SET");

  Double_t arglist[10];
  Int_t ierflg = 0;

  arglist[0] = 1;
  gMinuit->mnexcm("SET ERR", arglist ,1,ierflg);

  // Set starting values and step sizes for parameters
  static Double_t vstart[1] = {170};
  static Double_t step[1] = {0.05 };
  gMinuit->mnparm(0, "mass", vstart[0], step[0], 0,0,ierflg);

  // Now ready for minimization step
  arglist[0] = 500;
  arglist[1] = 1.;
  gMinuit->mnexcm("MIGRAD", arglist ,2,ierflg);
  gMinuit->mnmnos();

  // Print results
  Double_t amin,edm,errdef;
  Int_t nvpar,nparx,icstat;
  gMinuit->mnstat(amin,edm,errdef,nvpar,nparx,icstat); 
  //gMinuit->mnprin(3,amin); 

  Int_t npars = gMinuit->GetNumPars();
  Double_t *covar = new Double_t[npars*npars];
  gMinuit->mnemat(covar,npars); 

  //  cout<<covar[0][0]<<endl;


  cout<<"  "<<endl;
  cout<<" -------------------------------------------------------- "<<endl;
  gMinuit->GetParameter(0,mass,emass);
  cout<<" FIT RESULT: "<<mass<< " +- "<<emass<<"  GeV"<<endl;
  cout<<" -------------------------------------------------------- "<<endl;
  


}

void extraerdatos(TString pdf="CT10",TString energy="13TeV", int mass=170,  TString scheme="pole", TString scale="mu1", TString title="n3_24_pt50")
{

  TString mt="_mt";
  if(scheme == "running" ) mt="_mtrun";
  TString file="../../rootfiles_LHC13_1/"+energy+"_"+pdf+mt+TString::Format("%i",mass)+"_pt30_"+scale+".root";
  TGraphErrors * masspoint = readGraph(file,title,true);
  
  Double_t *y=masspoint->GetY();
  Double_t *ey=masspoint->GetEY();
  Double_t *ex=masspoint->GetEX();
  Double_t *x=masspoint->GetX();

  double  integral=0;
  for(int i=0; i<masspoint->GetN(); i++) {
    if(y[i]>0) {
      y[i]*=bin_size*130*100;
      ey[i]*=bin_size*130*100;
      integral+=y[i];
    }
  }
  for(int i=0; i<masspoint->GetN(); i++) {
    if(y[i]>0) {
      z[i]=y[i];
      ez[i]=ey[i];
    } else {
      z[i]=0;
      ez[i]=0;
    }
  }
  integral_recorded=integral;

}
void extraerdatos_randomize(TString pdf="CT10",TString energy="13TeV", int mass=170,  TString scheme="pole", TString scale="mu1", TString title="n3_24_pt50", int seed=0)
{

  TString mt="_mt";
  if(scheme == "running" ) mt="_mtrun";
  TString file="../../rootfiles_LHC13_1/"+energy+"_"+pdf+mt+TString::Format("%i",mass)+"_pt30_"+scale+".root";
  TGraphErrors * masspoint = readGraphNotNorm(file,title);
  Double_t *y=masspoint->GetY();
  Double_t *ey=masspoint->GetEY();
  Double_t *ex=masspoint->GetEX();
  Double_t *x=masspoint->GetX();

  double ynew[200], xnew[200], eynew[200], exnew[200];

  double integral = 0;
  for(int i=0; i<masspoint->GetN(); i++) {
    double ytemp=y[i]*bin_size*100*130*0.05;
    
    TRandom *r3 = new TRandom1();
    r3->SetSeed(seed);
    if(y[i]>0) {
      ynew[i] = r3->Gaus(ytemp,sqrt(fabs(ytemp)));
      eynew[i]=sqrt(ytemp);
      exnew[i]=ex[i];
      xnew[i]=x[i];
      if(ytemp>0) integral += ytemp;
    } else {
      ynew[i]=0;
      eynew[i]=0;
    }
  }
  integral_recorded=integral;
  for(int i=0; i<masspoint->GetN(); i++) {
    z[i]=ynew[i];///(integral*ex[i]*2);
    ez[i]=eynew[i];///(integral*ex[i]*2);
  }
  
}


void extraerdatos_randomize_scale(TString pdf="CT10",TString energy="13TeV", int mass=170,  TString scheme="pole", TString scale="mu1", TString scale_up="mu2", TString scale_down="mu0.5", TString title="n3_24_pt50", int seed=0)
{

  TString mt="_mt";
  if(scheme == "running" ) mt="_mtrun";
  TString file="../../rootfiles_LHC13_1/"+energy+"_"+pdf+mt+TString::Format("%i",mass)+"_pt30_"+scale+".root";
  TGraphErrors * masspoint = readGraphNotNorm(file,title);

  file="../../rootfiles_LHC13_1/"+energy+"_"+pdf+mt+TString::Format("%i",mass)+"_pt30_"+scale_up+".root";
  TGraphErrors * masspoint_up = readGraphNotNorm(file,title);
  
  file="../../rootfiles_LHC13_1/"+energy+"_"+pdf+mt+TString::Format("%i",mass)+"_pt30_"+scale_down+".root";
  TGraphErrors * masspoint_down = readGraphNotNorm(file,title);
  
  Double_t *y=masspoint->GetY();
  Double_t *yup=masspoint_up->GetY();
  Double_t *ydown=masspoint_down->GetY();

  Double_t *ey=masspoint->GetEY();
  Double_t *ex=masspoint->GetEX();
  Double_t *x=masspoint->GetX();

  double ynew[200], xnew[200], eynew[200], exnew[200];

  double integral = 0;
  for(int i=0; i<masspoint->GetN(); i++) {
    double ytemp=y[i]*bin_size;
    double eytemp=max(fabs(ydown[i]-yup[i]),max(fabs(y[i]-yup[i]),fabs(ydown[i]-y[i])))*bin_size;

    TRandom *r3 = new TRandom1();
    r3->SetSeed(seed);
    if(y[i]>0) {
      ynew[i] = r3->Gaus(ytemp,eytemp);
      eynew[i]=eytemp;
      exnew[i]=ex[i];
      xnew[i]=x[i];
      if(ytemp>0) integral += ytemp;
    } else {
      ynew[i]=0;
      eynew[i]=0;
    }
  }
  integral_recorded=integral;
  for(int i=0; i<masspoint->GetN(); i++) {
    z[i]=ynew[i];///(integral*ex[i]*2);
    ez[i]=eynew[i];///(integral*ex[i]*2);
  }
  
}

 
/*
//______________________________________________________________________________
void plotChiSq(TString title="")
{

  //calculate chisquare
  double chisq = 0;
  double delta=0;
  
  TGraph *chi0;
  TGraph *chi1;
  TGraph *chi2;
  TGraph *chi3;
  TGraph *chi4;
  TGraph *chi5;

  TCanvas *canv1 = new TCanvas ("figure0","figure0",800,600);
  TLegend *leg1 = new TLegend(0.7,0.6,0.9,0.9);//Variables


  for(int jbin=0; jbin<6; jbin++) {
    
    int counter;
    double ychi[300], xchi[300];

    for(int counter=0; counter<200; counter++) {
      //counter++;
      double jmass = counter* 15. / 200. + 160.;
      double chisq=0;
      for (int i=0;i<6; i++) {
	for (int j=0;j<6; j++) {
	  if(i!=jbin && j!=jbin) {
	    delta  = (z[i]-func_pol1_(i,jmass))/func_pol1_(j,jmass);
	    chisq += delta;
	  }
	}
      }
      //     cout<<jmass<<" "<<chisq<<endl;

      if(counter >0) {

	xchi[counter-1]=0; ychi[counter-1]=0;
	xchi[counter-1]=jmass;
	ychi[counter-1]=chisq;
      }
    }
    TGraph *g= new TGraph(counter-1,xchi,ychi);
    //chisqgraphs.push_back(g);
    if(jbin==0) chi0 = new TGraph(counter-1,xchi,ychi);
    if(jbin==1) chi1 = new TGraph(counter-1,xchi,ychi);
    if(jbin==2) chi2 = new TGraph(counter-1,xchi,ychi);
    if(jbin==3) chi3 = new TGraph(counter-1,xchi,ychi);
    if(jbin==4) chi4 = new TGraph(counter-1,xchi,ychi);
    if(jbin==5) chi5 = new TGraph(counter-1,xchi,ychi);

    // g->Draw("alp"); 
    //    cout<<    chisqgraphs.size() <<endl;

  }
    
 
 
   canv1->cd();
   g =  (TGraph*)chi0->Clone();	
   if(title=="mu2") g->SetTitle("#font[52]{#Rgothic(m(m),#mu=2m) fit to data}");
   if(title=="mu1") g->SetTitle("#font[52]{#Rgothic(m(m),#mu=m) fit to data}");//to data}");
   if(title=="mu05") g->SetTitle("#font[52]{#Rgothic(m(m),#mu=m/2) fit to data}");//to data}");
   //  if(title=="mu1") g->SetTitle("#font[52]{t#bar{t}+1-Jet, #mu=m(m), at NLO fit to data}");
   //  if(title=="mu05") g->SetTitle("#font[52]{t#bar{t}+1-Jet, #mu=m(m)/2, at NLO fit to data}");

   g->GetYaxis()->SetTitle("#font[52]{#chi^{2}}");
   g->GetXaxis()->SetTitle("#font[52]{m(m)} [GeV]");
   g->GetYaxis()->SetRangeUser(-1,10);
   g->GetXaxis()->CenterTitle();
   g->GetYaxis()->CenterTitle();
   g->GetYaxis()->SetLabelSize(0.05);
   g->GetXaxis()->SetLabelSize(0.05);
   g->SetLineColor(2);
   g->SetLineStyle(2);
   g->SetLineWidth(2);
   g->SetMarkerColor(2);
   g->SetMarkerSize(0.);
   g->Draw("alp"); 

   leg1->AddEntry(g,"#font[42]{Excluding bin }0","l"); 

    for(int j=1; j<6; j++) {
      if(j==1) g =  (TGraph*)chi1->Clone();	
      if(j==2) g =  (TGraph*)chi2->Clone();	
      if(j==3) g =  (TGraph*)chi3->Clone();	
      if(j==4) g =  (TGraph*)chi4->Clone();	
      if(j==5) g =  (TGraph*)chi5->Clone();	

      g->SetLineColor(j+2);
      g->SetLineStyle(j+2);
      g->SetLineWidth(2);
      g->SetMarkerColor(j+2);
      g->SetMarkerSize(0.);
      g->Draw("lp");
      leg1->AddEntry(g,"#font[42]{Excluding bin }"+TString::Format("%i",j),"l");
    }
    leg1->SetFillColor(0);
    leg1->SetShadowColor(0);
    leg1->Draw();

    canv1->Print("ChiS_"+title+".eps");


}

*/
