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
#include "../include/AtlasStyle.C"
#include "../include/AtlasLabels.h"
using namespace std;

TH1F *Histo(TGraphErrors* graph, int n=12) {

  //  int n=2;
  TH1F* h = new TH1F("h","h",n,-0.1,1.1); // the histogram (you should set the number of bins, the title etc)

  Double_t *y;
  Double_t *ey;
  y=graph->GetY();
  ey=graph->GetEY();
  
  for(int i=0; i < graph->GetN(); ++i) {
    h->SetBinContent(i+1,y[i]);
    h->SetBinError(i+1,ey[i]);
  }

  return h;

}


TGraphErrors* NormGraphs(TGraphErrors* g, TGraphErrors *gref) {

  Double_t *x=gref->GetX();
  Double_t *y=gref->GetY();
  Double_t *ex=gref->GetEX();
  Double_t *ey=gref->GetEY();
  
  Double_t *y_ratio=g->GetY();


  double x_new[100], y_new[100], ex_new[100], ey_new[100];
  int n=0;
  
  for(int i=0; i<gref->GetN(); i++) {
    x_new[i]=x[i];
    ex_new[i]=ex[i];

    if(y[i]>0 && y_ratio[i]!=0) {
      if(y_ratio[i]<0 ) y_new[n] = 0;
      else y_new[n]=y_ratio[i]/y[i];
      x_new[n]=x[i];
      ex_new[n]=ex[i];
      n++;
      ey_new[n]=0;
    }

  }

  TGraphErrors* result = new TGraphErrors(n,x_new,y_new,ex_new,ey_new);

  return result;
}

TGraphErrors* NormGraphs(TGraphErrors* g, TGraphErrors *gref, int nbins_avoid) {

  Double_t *x=gref->GetX();
  Double_t *y=gref->GetY();
  Double_t *ex=gref->GetEX();
  Double_t *ey=gref->GetEY();
  
  Double_t *y_ratio=g->GetY();


  double x_new[100], y_new[100], ex_new[100], ey_new[100];
  int n=0;
  
  for(int i=0; i<gref->GetN(); i++) {

    if(i>(nbins_avoid-1) && i< (gref->GetN()-nbins_avoid)  ){
      //  if(y[i]>0 && y_ratio[i]!=0) {
	if(y_ratio[i]<0 ) y_new[n] = 0;
	else y_new[n]=y_ratio[i]/y[i];
	x_new[n]=x[i];
	ex_new[n]=ex[i];
	n++;
	ey_new[n]=0;
	//  }
    }
  } 

  TGraphErrors* result = new TGraphErrors(n,x_new,y_new,ex_new,ey_new);

  return result;
}

TGraphErrors* readGraphNotNorm(TString filename,TString title) {

  TFile _file(filename);
  cout<<filename<<" "<<title<<endl;
  TGraphErrors *results = (TGraphErrors*) _file.Get(title.Data());

  return results;
}


TGraphErrors* readGraph(TString filename,TString title, bool errors=true) {

  TFile _file(filename);
  cout<<filename<<" "<<title<<endl;
  double integral=0;
  TGraphErrors *results = (TGraphErrors*) _file.Get(title.Data());

  Double_t *y=results->GetY();
  Double_t *ey=results->GetEY();
  Double_t *ex=results->GetEX();

  //  for(int i=0; i<results->GetN(); i++) if(y[i]<0) y[i]=0;
  
  for(int i=0; i<results->GetN(); i++) integral+=y[i]*ex[i]*2.;

  for(int i=0; i<results->GetN(); i++) {
    y[i]=y[i]/(integral);
    ey[i]=ey[i]/(integral);
  }
					 
  if(errors==false) {
    for(int i=0; i<results->GetN(); i++) {
      ey[i]=0;
      ex[i]=0;
    }
  }
    
  _file.Close();
  return results;
}

TGraphErrors* readGraphStatErrors(TString filename,TString title) {

  TFile _file(filename);
  cout<<filename<<" "<<title<<endl;
  double integral=0;
  TGraphErrors *results = (TGraphErrors*) _file.Get(title.Data());

  Double_t *y=results->GetY();
  Double_t *ey=results->GetEY();
  Double_t *ex=results->GetEX();

  for(int i=0; i<results->GetN(); i++) integral+=y[i]*ex[i]*2.;

  integral = integral;

  for(int i=0; i<results->GetN(); i++) {

    double N_y=y[i]*130. *0.05*ex[i]*2.;
    double N_t=integral*130. *0.05;

    y[i]=y[i]/(integral);
    ey[i]=(sqrt(N_y)/(N_t));
  }
					 
    
  _file.Close();
  return results;
}

/*TGraphErrors* readGraph(TString filename,TString title, bool errors=true) {

  cout<<filename<< endl;

  TFile _file(filename);

  TGraphErrors *results = (TGraphErrors*) _file.Get(title.Data());
  

    
  _file.Close();
  return results;
}*/

TGraphErrors* readNormGraph(TString filename,TString title, TString pt, bool errors=true) {

  cout<<filename<< endl;

  TFile _file(filename);
  TString title_pt=title+pt;
  cout<<filename<< " "<<title_pt<<endl;

  TGraphErrors *results = (TGraphErrors*) _file.Get(title_pt.Data());

  double integral=0;
  Double_t *y=results->GetEX();

  /* if(errors==false) {
    Double_t *ey=results->GetEY();
    Double_t *ex=results->GetEX();

    for(int i=0; i<results->GetN(); i++) {
      ey[i]=0;
      ex[i]=0;
    }

    }*/
    
  _file.Close();
  return results;
}

TGraphErrors* readGraphCp(TString filename,TString title, TString pt, bool errors=true) {

  double Cp[4];


  TFile _file(filename);
  TString title_pt=title+pt;
  cout<<filename<< " "<<title_pt<<endl;

  TGraphErrors *results = (TGraphErrors*) _file.Get(title_pt.Data());
  Double_t *y=results->GetY();

  if(title=="RAPIDITY_CMS_mtt_300_400_" ) {
    Cp[0]=1.033;
    Cp[1]=1.031;
    Cp[2]=1.035;
    Cp[3]=1.037;
    cout<<" Correction Cp, " <<title<<endl;
  } else {
    if(title=="RAPIDITY_CMS_mtt_400_500_" ) {
      Cp[0]=1.036;
      Cp[1]=1.034;
      Cp[2]=1.036;
      Cp[3]=1.037;
      cout<<" Correction Cp, " <<title<<endl;
    } else {
      if(title=="RAPIDITY_CMS_mtt_500_1500_" ) {
	Cp[0]=1.024;
	Cp[1]=1.024;
	Cp[2]=1.025;
	Cp[3]=1.022;
	cout<<" Correction Cp, " <<title<<endl;
      } else {
	if(title!="RAPIDITY_CMS_mtt_1500_" ) {
	  cout<< "readGraphCp, incorrect graph name: "<<title<<endl;
	  return NULL;
	}
      }
    }
  }

  for(int i=0; i<results->GetN(); i++) {
    y[i]*=Cp[i];
  }

  
  Double_t *ey=results->GetEY();
  Double_t *ex=results->GetEX();

  /* if(errors==true){
    for(int i=0; i<results->GetN(); i++) {
      ey[i]*=Cp[i];
    }
  } else {
    for(int i=0; i<results->GetN(); i++) {
      ey[i]=0;
      ex[i]=0;
    }
    }*/
    
  _file.Close();
  return results;
}



TGraphErrors* Errors3(TGraphErrors* gref, TGraphErrors *gref_up, TGraphErrors *gref_down) {

  Double_t *x=gref->GetX();
  Double_t *y=gref->GetY();
  Double_t *ex=gref->GetEX();
  Double_t *ey=gref->GetEY();
  
  Double_t *y_up=gref_up->GetY();
  Double_t *y_down=gref_down->GetY();

  double x_new[100], y_new[100], ex_new[100], ey_new[100];
  int n=0;
  
  for(int i=0; i<gref->GetN(); i++) {
  
    if(y[i]>0) {
      x_new[n]=x[i];
      ex_new[n]=ex[i]; 
      y_new[n]=(fabs(y_up[i]-y[i])+fabs(y[i]-y_down[i]))/(2.*y[i]);
      ey_new[n]=0;
      n++;
    }
    
  }

  TGraphErrors* result = new TGraphErrors(n,x_new,y_new,ex_new,ey_new);

  return result;
}



TGraphErrors* GraphErrors3(TGraphErrors* gref, TGraphErrors *gref_up, TGraphErrors *gref_down) {

  Double_t *x=gref->GetX();
  Double_t *y=gref->GetY();
  Double_t *ex=gref->GetEX();
  Double_t *ey=gref->GetEY();
  
  Double_t *y_up=gref_up->GetY();
  Double_t *y_down=gref_down->GetY();

  double x_new[100], y_new[100], ex_new[100], ey_new[100];
  int n=0;
  
  for(int i=0; i<gref->GetN(); i++) {
  
    //  if(y[i]>0) {
      x_new[n]=x[i];
      ex_new[n]=0; 
      ey_new[n]=(fabs(y_up[i]-y[i])+fabs(y[i]-y_down[i]))/(2.);
      y_new[n]=y[i];
      n++;
      // }
    
  } 

  TGraphErrors* result = new TGraphErrors(n,x_new,y_new,ex_new,ey_new);

  return result;
}

TGraphErrors* GraphErrors3(TGraph* gref, TGraph *gref_up, TGraph *gref_down) {

  Double_t *x=gref->GetX();
  Double_t *y=gref->GetY();
  
  Double_t *y_up=gref_up->GetY();
  Double_t *y_down=gref_down->GetY();

  double x_new[100], y_new[100], ex_new[100], ey_new[100];
  int n=0;
  
  for(int i=0; i<gref->GetN(); i++) {
  
      x_new[n]=x[i];
      ex_new[n]=0; 
      ey_new[n]=(fabs(y_up[i]-y[i])+fabs(y[i]-y_down[i]))/(2.);
      y_new[n]=y[i];
      n++;
    
  }


  TGraphErrors* result = new TGraphErrors(n,x_new,y_new,ex_new,ey_new);

  return result;
}


TGraphErrors* Sens3_error8TeV(TGraphErrors *gref,TGraphErrors *g_up,TGraphErrors *g_down,int mass=170, int interval=4) {

  Double_t *x=gref->GetX();
  Double_t *y=gref->GetY();
  Double_t *ex=gref->GetEX();
  Double_t *ey=gref->GetEY();
  
  Double_t *y_up=g_up->GetY();
  Double_t *y_down=g_down->GetY();

  double x_new[100], y_new[100], ex_new[100], ey_new[100];
  int n=0;

  double ey_8TeV[100];
  ey_8TeV[0]=sqrt(pow(0.007,2)+pow(0.027,2))/0.179;
  ey_8TeV[1]=sqrt(pow(0.085,2)+pow(0.188,2))/1.169;
  ey_8TeV[2]=sqrt(pow(0.099,2)+pow(0.11,2))/2.226;
  ey_8TeV[3]=sqrt(pow(0.115,2)+pow(0.111,2))/2.296;
  ey_8TeV[4]=sqrt(pow(0.087,2)+pow(0.0091,2))/1.982;
  ey_8TeV[5]=sqrt(pow(0.135,2)+pow(0.112,2))/1.138;
  ey_8TeV[6]=sqrt(pow(0.077,2)+pow(0.0078,2))/0.690;
  ey_8TeV[7]=sqrt(pow(0.022,2)+pow(0.0034,2))/0.113;

  ey_8TeV[0]=sqrt(pow(0.01,2))/0.140;
  ey_8TeV[1]=sqrt(pow(0.068,2))/1.140;
  ey_8TeV[2]=sqrt(pow(0.079,2))/2.126;
  ey_8TeV[3]=sqrt(pow(0.098,2))/2.444;
  ey_8TeV[4]=sqrt(pow(0.071,2))/2.172;
  ey_8TeV[5]=sqrt(pow(0.091,2))/1.142;
  ey_8TeV[6]=sqrt(pow(0.049,2))/0.585;
  ey_8TeV[7]=sqrt(pow(0.008,2))/0.046;


  double mass_resolution=0;
  for(int i=0; i<gref->GetN(); i++) {
    x_new[i]=x[i];
    ex_new[i]=ex[i];
    if(y[i]!=0) {
      double s= (fabs(y_up[i]-y[i])/double(interval) +  fabs(y_down[i]-y[i])/double(interval) ) / (2*y[i]);
      y_new[i]=ey_8TeV[i]/s;//(y[i]*s);
      if(i>0) mass_resolution+=1/(y_new[i]*y_new[i]);

    } else y_new[i]=0;
    ey_new[i]=0;//fabs(y_up[i]-y_down[i])/2.;
    n++;
  }


  TGraphErrors* result = new TGraphErrors(n,x_new,y_new,ex_new,ey_new);

  return result;
}

TGraphErrors* Sens3(TGraph *gref,TGraph *g_up,TGraph *g_down,int mass=170, int interval=4) {

  Double_t *x=gref->GetX();
  Double_t *y=gref->GetY();
  Double_t *ex=gref->GetEX();
  Double_t *ey=gref->GetEY();
  
  Double_t *y_up=g_up->GetY();
  Double_t *y_down=g_down->GetY();

  double x_new[100], y_new[100], ex_new[100], ey_new[100];
  int n=0;
  
  for(int i=0; i<gref->GetN(); i++) {
    if(y[i]>0) {
      x_new[n]=x[i];
      ex_new[n]=ex[i];
      double s= (fabs(y_up[i]-y[i])/double(interval) +  fabs(y_down[i]-y[i])/double(interval) ) / (2*y[i]);
      y_new[n]=s;
      ey_new[n]=0;
      n++;
      //      cout<<s<<endl;
    } 
  }

  TGraphErrors* result = new TGraphErrors(n,x_new,y_new,ex_new,ey_new);

  return result;
}

TGraphErrors* SensError3(TGraph *gref,TGraph *g_up,TGraph *g_down,int mass=170, int interval=4) {

  Double_t *x=gref->GetX();
  Double_t *y=gref->GetY();
  Double_t *ex=gref->GetEX();
  Double_t *ey=gref->GetEY();
  
  Double_t *y_up=g_up->GetY();
  Double_t *y_down=g_down->GetY();

  double x_new[100], y_new[100], ex_new[100], ey_new[100];
  int n=0;
  
  for(int i=0; i<gref->GetN(); i++) {

    if(y[i]>0) {
      x_new[n]=x[i];
      ex_new[n]=ex[i];
      double s= (fabs(y_up[i]-y[i])/double(interval) +  fabs(y_down[i]-y[i])/double(interval) ) / (2*y[i]);
      y_new[n]=ey[i]/(y[i]*s);
      ey_new[n]=0;
      n++;
    } 
  }

  TGraphErrors* result = new TGraphErrors(n,x_new,y_new,ex_new,ey_new);

  return result;
}




TGraphErrors* CMSobs_arxiv(int bin_mtt=0) {

  double y_mtt_300[4], y_mtt_400[4], y_mtt_500[4];
  double ey_mtt_300[4], ey_mtt_400[4], ey_mtt_500[4];


  y_mtt_300[0]=6.493; ey_mtt_300[0]=5.9;
  y_mtt_300[1]=6.231; ey_mtt_300[1]=5.1;
  y_mtt_300[2]=5.557; ey_mtt_300[2]=5.5;
  y_mtt_300[3]=2.482; ey_mtt_300[3]=5.2;
  y_mtt_400[0]=12.20; ey_mtt_400[0]=3.1;
  y_mtt_400[1]=10.83; ey_mtt_400[1]=2.7;
  y_mtt_400[2]=8.512; ey_mtt_400[2]=3.5;
  y_mtt_400[3]=3.283; ey_mtt_400[3]=3.1;
  y_mtt_500[0]=15.56; ey_mtt_500[0]=1.7;
  y_mtt_500[1]=13.62; ey_mtt_500[1]=1.0;
  y_mtt_500[2]=9.834; ey_mtt_500[2]=2.5;
  y_mtt_500[3]=2.700; ey_mtt_500[3]=3.6;

  double binsize[4];
  binsize[0]=0.35;
  binsize[1]=0.4;
  binsize[2]=0.4;
  binsize[3]=1.35;

  double x[4];
  x[0]=0.175;
  x[1]=0.55;
  x[2]=0.95;
  x[3]=1.825;

  double ex[4];
  for(int i=0; i<4; i++) ex[i]=binsize[i]/2.;


  for(int i=0; i<4; i++) {
    y_mtt_300[i]*=0.01;
    y_mtt_400[i]*=0.01;
    y_mtt_500[i]*=0.01;
  }

  double integral =0;
  for(int i=0; i<4; i++) {
    integral += y_mtt_300[i];
    integral += y_mtt_400[i];
    integral += y_mtt_500[i];
  }

  /*  for(int i=0; i<4; i++) {
    y_mtt_300[i]/=(integral);///binsize[i]);
    y_mtt_400[i]/=(integral);///binsize[i]);
    y_mtt_500[i]/=(integral);///binsize[i]);
    }*/

  for(int i=0; i<4; i++) {
    ey_mtt_300[i]*=(0.01*y_mtt_300[i]);
    ey_mtt_400[i]*=(0.01*y_mtt_400[i]);
    ey_mtt_500[i]*=(0.01*y_mtt_500[i]);
  }


  TGraphErrors *res1 = new TGraphErrors(4,x,y_mtt_300,ex,ey_mtt_300);
  TGraphErrors *res2 = new TGraphErrors(4,x,y_mtt_400,ex,ey_mtt_400);
  TGraphErrors *res3 = new TGraphErrors(4,x,y_mtt_500,ex,ey_mtt_500);

  if(bin_mtt==1) return res1;
  if(bin_mtt==2) return res2;
  if(bin_mtt==3) return res3;

  return NULL;
}

void DrawThree_pt(TGraphErrors *gref,TGraphErrors *g_up,TGraphErrors *g_down, int mass=170, TString canvasname="canvas0",TString titley="#Rgothic(#rho_{s},m_{t}^{pole})", TString titlex="#font[52]{#rho_{s}}", TString scheme="pole"){

  
  // -----------------------------------------------------------------
  // --- plot stuff
  TCanvas *canv1 = new TCanvas (canvasname,canvasname,1000,800);
 
 
  canv1->cd();
  gref->GetYaxis()->SetTitle(titley);
  gref->GetXaxis()->SetTitle(titlex);
  //  gref->GetYaxis()->SetRangeUser(0,3.6);
  //gref->GetXaxis()->SetRangeUser(0,1);
  gref->GetYaxis()->SetLabelSize(0.04);
  gref->GetXaxis()->SetLabelSize(0.04);
  gref->SetLineColor(2);
  gref->SetLineStyle(1);
  gref->SetLineWidth(2);
  gref->SetMarkerColor(2);
  gref->SetMarkerSize(0.);
  gref->Draw("alp");

  g_up->SetLineColor(4);
  g_up->SetLineStyle(2);
  g_up->SetLineWidth(2);
  g_up->SetMarkerColor(4);
  g_up->SetMarkerSize(0.);
  g_up->Draw("lp");

  g_down->SetLineColor(1);
  g_down->SetLineStyle(1);
  g_down->SetLineWidth(2);
  g_down->SetMarkerColor(1);
  g_down->SetMarkerSize(0.);
  g_down->Draw("lp");

  TLegend *leg1 = new TLegend(0.55,0.7,0.9,0.9);//Variables
  if(scheme=="pole") leg1->SetHeader("13 TeV "+TString::Format("M_{t}^{pole}=%i GeV, #mu=M_{t}^{pole}",mass));
  if(scheme=="running") leg1->SetHeader("13 TeV "+TString::Format("m_{t}(m_{t})=%i GeV, #mu=m_{t}(m_{t})",mass));
  leg1->AddEntry(gref,"p_{T}^{jet}>30 GeV","lpe");
  leg1->AddEntry(g_up,"p_{T}^{jet}>50 GeV","lpe");
  leg1->AddEntry(g_down,"p_{T}^{jet}>100 GeV","lpe");

  leg1->SetLineWidth(0);
  leg1->SetFillColor(0);
  leg1->SetShadowColor(0);
  leg1->Draw();
   


}


void DrawThree_bin(TGraphErrors *gref,TGraphErrors *g_up,TGraphErrors *g_down, int mass=170, TString canvasname="canvas0",TString titley="#Rgothic(#rho_{s},m_{t}^{pole})", TString titlex="#font[52]{#rho_{s}}", TString scheme="pole"){

  
  // -----------------------------------------------------------------
  // --- plot stuff
  TCanvas *canv1 = new TCanvas (canvasname,canvasname,1000,800);
 
 
  canv1->cd();
  gref->GetYaxis()->SetTitle(titley);
  gref->GetXaxis()->SetTitle(titlex);
  //  gref->GetYaxis()->SetRangeUser(0,3.6);
  //gref->GetXaxis()->SetRangeUser(0,1);
  gref->GetYaxis()->SetLabelSize(0.04);
  gref->GetXaxis()->SetLabelSize(0.04);
  gref->SetLineColor(2);
  gref->SetLineStyle(1);
  gref->SetLineWidth(2);
  gref->SetMarkerColor(2);
  gref->SetMarkerSize(0.);
  gref->Draw("alp");

  g_up->SetLineColor(4);
  g_up->SetLineStyle(2);
  g_up->SetLineWidth(2);
  g_up->SetMarkerColor(4);
  g_up->SetMarkerSize(0.);
  g_up->Draw("lp");

  g_down->SetLineColor(1);
  g_down->SetLineStyle(1);
  g_down->SetLineWidth(2);
  g_down->SetMarkerColor(1);
  g_down->SetMarkerSize(0.);
  g_down->Draw("lp");

  TLegend *leg1 = new TLegend(0.55,0.7,0.9,0.9);//Variables
  if(scheme=="pole") leg1->SetHeader("13 TeV "+TString::Format("M_{t}^{pole}=%i GeV, #mu=M_{t}^{pole}",mass));
  if(scheme=="running") leg1->SetHeader("13 TeV "+TString::Format("m_{t}(m_{t})=%i GeV, #mu=m_{t}(m_{t})",mass));
  leg1->AddEntry(gref,"8 TeV bining","lpe");
  leg1->AddEntry(g_up,"0.1 binning","lpe");
  leg1->AddEntry(g_down,"0.05 binning","lpe");

  leg1->SetLineWidth(0);
  leg1->SetFillColor(0);
  leg1->SetShadowColor(0);
  leg1->Draw();
   


}

void DrawThree(TGraph *gref,TGraph *g_up,TGraph *g_down,int mass=170, int interval=4, TString pt="pt50", TString canvasname="canvas0",TString titley="#Rgothic(#rho_{s},m_{t}^{pole})", TString titlex="#font[52]{#rho_{s}}", TString scheme="pole", TGraph *cms=NULL){

  
  // -----------------------------------------------------------------
  // --- plot stuff
  TCanvas *canv1 = new TCanvas (canvasname,canvasname,1000,800);
 
 
  canv1->cd();
  gref->GetYaxis()->SetTitle(titley);
  gref->GetXaxis()->SetTitle(titlex);
  gref->GetYaxis()->SetRangeUser(0,0.21);
  //gref->GetXaxis()->SetRangeUser(0,1);
  gref->GetYaxis()->SetLabelSize(0.04);
  gref->GetXaxis()->SetLabelSize(0.04);
  gref->SetLineColor(1);
  gref->SetLineStyle(1);
  gref->SetLineWidth(2);
  gref->SetMarkerColor(1);
  gref->SetMarkerSize(0.);
  gref->SetFillStyle(3003);
  gref->SetFillColor(1);
  gref->Draw("alp3");

  g_up->SetLineColor(2);
  g_up->SetLineStyle(2);
  g_up->SetLineWidth(2);
  g_up->SetMarkerColor(2);
  g_up->SetMarkerSize(0.);
  g_up->Draw("lp");

  g_down->SetLineColor(4);
  g_down->SetLineStyle(2);
  g_down->SetLineWidth(2);
  g_down->SetMarkerColor(4);
  g_down->SetMarkerSize(0.);
  g_down->Draw("lp");

  if(cms!=NULL)  {
    cms->SetLineColor(1);
    cms->SetLineStyle(1);
    cms->SetLineWidth(1);
    cms->SetMarkerColor(1);
    cms->SetMarkerStyle(20);
    cms->SetMarkerSize(1.0);
    cms->Draw("pe");
  }

  TLegend *leg1 = new TLegend(0.55,0.7,0.9,0.9);//Variables
  leg1->SetHeader("13 TeV, "+pt);
  if(scheme=="pole") {
    leg1->AddEntry(gref,TString::Format("m_{t}^{pole}=%i GeV, #mu=m_{t}^{pole}",mass),"l");
    leg1->AddEntry(gref,"scale variations (#mu=2#times m_{t}^{pole}, m_{t}^{pole}/2)","f");
    leg1->AddEntry(g_up,TString::Format("m_{t}^{pole}=%i GeV, #mu=m_{t}^{pole}",mass+interval),"l");
    leg1->AddEntry(g_down,TString::Format("m_{t}^{pole}=%i GeV, #mu=m_{t}^{pole}",mass-interval),"l");
  }
  if(scheme=="running") {
    leg1->AddEntry(gref,TString::Format("m_{t}(m_{t})=%i GeV, #mu=m_{t}(m_{t})",mass),"l");
    leg1->AddEntry(gref,"scale variations (#mu=2#times m_{t}(m_{t}), m_{t}(m_{t})/2)","f");
    leg1->AddEntry(g_up,TString::Format("m_{t}(m_{t})=%i GeV, #mu=m_{t}(m_{t})",mass+interval),"l");
    leg1->AddEntry(g_down,TString::Format("m_{t}(m_{t})=%i GeV, #mu=m_{t}(m_{t})",mass-interval),"l");
  } 
  if(cms!=NULL) leg1->AddEntry(cms,"CMS result","pe");

  leg1->SetLineWidth(0);
  leg1->SetFillColor(0);
  leg1->SetShadowColor(0);
  leg1->Draw();
   


}

void DrawSens(TGraphErrors *sens, int mass=170, int interval=4, TString canvasname="canvas_sens",TString titley="#Delta#Rgothic(#mu) #times Sensitivity [GeV]", TString titlex="#font[52]{#rho_{s}}", TString scheme="pole"){

 
  // -----------------------------------------------------------------
  // --- plot stuff
  TCanvas *canv1 = new TCanvas (canvasname,canvasname,1000,800);
 
 
  canv1->cd();
  sens->GetYaxis()->SetTitle(titley);
  sens->GetXaxis()->SetTitle(titlex);
  // sens->GetXaxis()->SetRangeUser(0,1);
  // sens->GetYaxis()->SetRangeUser(0,15);
  sens->GetYaxis()->SetLabelSize(0.04);
  sens->GetXaxis()->SetLabelSize(0.04);
  sens->SetLineColor(2);
  sens->SetLineStyle(1);
  sens->SetLineWidth(2);
  sens->SetMarkerColor(2);
  sens->SetMarkerSize(0.);
  sens->SetFillStyle(3003);
  sens->SetFillColor(2);
  sens->Draw("alp");
  

  TLegend *leg1 = new TLegend(0.6,0.7,0.9,0.9);//Variables
  leg1->SetHeader("13 TeV, "+scheme);
  leg1->SetLineWidth(0);
  leg1->SetFillColor(0);
  leg1->SetShadowColor(0);
  leg1->Draw();
   


}


void DrawSens3(std::vector<TGraphErrors *> sens,  TString canvasname,std::vector<TString> label, TString titley="#Delta#Rgothic(#mu) #times Sensitivity [GeV]", TString titlex="y_{t#bar{t}}",TString scheme="pole", TString pt="30GeV"){

  if(sens.size()<1) cout<<" DrawSens3 --> graph dimension ==0 " <<endl;

  // -----------------------------------------------------------------
  // --- plot stuff
  TCanvas *canv1 = new TCanvas (canvasname,canvasname,1000,800);
  
  TLegend *leg1 = new TLegend(0.4,0.7,0.9,0.9);//Variables
  leg1->SetHeader("13 TeV, "+scheme+", "+pt);
  
  canv1->cd();
  gPad->SetLogy();
  sens.at(0)->GetYaxis()->SetTitle(titley);
  sens.at(0)->GetXaxis()->SetTitle(titlex);
  sens.at(0)->GetYaxis()->SetLabelSize(0.04);
  sens.at(0)->GetXaxis()->SetLabelSize(0.04);
  sens.at(0)->GetYaxis()->SetRangeUser(0,20);

  sens.at(0)->SetLineColor(1);
  sens.at(0)->SetLineStyle(1);
  sens.at(0)->SetLineWidth(2);
  sens.at(0)->SetMarkerColor(1);
  sens.at(0)->SetMarkerSize(1.0);
  sens.at(0)->SetMarkerStyle(20);
  sens.at(0)->Draw("alp");
  leg1->AddEntry(sens.at(0),label.at(0),"lp");

  if(sens.size()>1) {
    sens.at(1)->SetLineColor(kOrange);
    sens.at(1)->SetLineStyle(2);
    sens.at(1)->SetLineWidth(6);
    sens.at(1)->SetMarkerColor(kOrange);
    sens.at(1)->SetMarkerSize(1);
    sens.at(1)->SetMarkerStyle(21);
    sens.at(1)->Draw("lp");
    leg1->AddEntry(sens.at(1),label.at(1),"lp");

  }

  if(sens.size()>2) {
    sens.at(2)->SetLineColor(kGreen+2);
    sens.at(2)->SetLineStyle(1);
    sens.at(2)->SetLineWidth(3);
    sens.at(2)->SetMarkerColor(kGreen+2);
    sens.at(2)->SetMarkerSize(1);
    sens.at(2)->SetMarkerStyle(22);
    sens.at(2)->Draw("lp");
    leg1->AddEntry(sens.at(2),label.at(2),"lp");
  }

  if(sens.size()>3) {
    sens.at(3)->SetLineColor(kBlue);
    sens.at(3)->SetLineStyle(1);
    sens.at(3)->SetLineWidth(3);
    sens.at(3)->SetMarkerColor(kBlue);
    sens.at(3)->SetMarkerSize(0.);
    sens.at(3)->Draw("lp");
    leg1->AddEntry(sens.at(3),label.at(3),"lp");
  }
    

  leg1->SetLineWidth(0);
  leg1->SetFillColor(0);
  leg1->SetShadowColor(0);
  leg1->Draw();
   


}



void DrawVector(std::vector<TGraphErrors *> sens,  TString canvasname,std::vector<TString> label, TString titley="#Delta#Rgothic(#mu) #times Sensitivity [GeV]", TString titlex="y_{t#bar{t}}",TString scheme="pole", TString pt="30GeV"){

  if(sens.size()<1) cout<<" DrawSens3 --> graph dimension ==0 " <<endl;

  // -----------------------------------------------------------------
  // --- plot stuff
  TCanvas *canv1 = new TCanvas (canvasname,canvasname,1000,800);
  
  TLegend *leg1 = new TLegend(0.6,0.7,0.98,0.9);//Variables
  leg1->SetHeader("13 TeV, "+scheme+", "+pt);
  leg1->SetFillStyle(0);
  
  canv1->cd();
  // gPad->SetLogy();
  gPad->SetGridx();
  gPad->SetGridy();

  sens.at(0)->GetYaxis()->SetTitle(titley);
  sens.at(0)->GetXaxis()->SetTitle(titlex);
  sens.at(0)->GetYaxis()->SetLabelSize(0.04);
  sens.at(0)->GetXaxis()->SetLabelSize(0.04);

  Double_t *y=sens.at(0)->GetY();
  double max=0;
  for(int i=0; i<sens.at(0)->GetN(); i++)if (y[i]>max) max=y[i];;

  sens.at(0)->GetYaxis()->SetRangeUser(0.,max*2);

  sens.at(0)->SetLineColor(1);
  sens.at(0)->SetLineStyle(1);
  sens.at(0)->SetLineWidth(2);
  sens.at(0)->SetMarkerColor(1);
  sens.at(0)->SetMarkerSize(1.0);
  sens.at(0)->SetMarkerStyle(20);
  sens.at(0)->Draw("alp");

  leg1->AddEntry(sens.at(0),label.at(0),"lp");

  if(sens.size()>1) {
    sens.at(1)->SetLineColor(kOrange);
    sens.at(1)->SetLineStyle(2);
    sens.at(1)->SetLineWidth(6);
    sens.at(1)->SetMarkerColor(kOrange);
    sens.at(1)->SetMarkerSize(1);
    sens.at(1)->SetMarkerStyle(21);
    sens.at(1)->Draw("lp");
    leg1->AddEntry(sens.at(1),label.at(1),"lp");

  }

  if(sens.size()>2) {
    sens.at(2)->SetLineColor(kBlue);
    sens.at(2)->SetLineStyle(1);
    sens.at(2)->SetLineWidth(3);
    sens.at(2)->SetMarkerColor(kBlue);
    sens.at(2)->SetMarkerSize(1);
    sens.at(2)->SetMarkerStyle(22);
    sens.at(2)->Draw("lp");
    leg1->AddEntry(sens.at(2),label.at(2),"lp");
  }

  if(sens.size()>3) {
    sens.at(3)->SetLineColor(kGreen+2);
    sens.at(3)->SetLineStyle(1);
    sens.at(3)->SetLineWidth(3);
    sens.at(3)->SetMarkerColor(kGreen+2);
    sens.at(3)->SetMarkerSize(0.);
    sens.at(3)->Draw("lp");
    leg1->AddEntry(sens.at(3),label.at(3),"lp");
  }
    

  leg1->SetLineWidth(0);
  leg1->SetFillColor(0);
  leg1->SetShadowColor(0);
  leg1->Draw();
   


}




void ReferencePlots(TString scheme="running", TString pdf="CT10", TString energy="LHC13", TString distribution="n3_12_", TString ptcut="pt50", int mass=170, int deltamass=5) {
 
  gROOT->Reset();
  SetAtlasStyle();
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);


  TString title = distribution;
  TString filename = "../../rootfiles/"+energy+"_"+pdf+"_mtrun"+TString::Format("%i",mass)+"_pt30_mu1.root";
  if(scheme=="pole") filename = "../../rootfiles/"+energy+"_"+pdf+"_mt"+TString::Format("%i",mass)+"_pt30_mu1.root";
  TGraphErrors *gref = readGraph(filename,title+ptcut,false);
  
  filename = "../../rootfiles/"+energy+"_"+pdf+"_mtrun"+TString::Format("%i",mass)+"_pt30_mu2.root";
  if(scheme=="pole")  filename = "../../rootfiles/"+energy+"_"+pdf+"_mt"+TString::Format("%i",mass)+"_pt30_mu2.root";
  TGraphErrors *gref_scale_up = readGraph(filename,title+ptcut,false);
  
  filename = "../../rootfiles/"+energy+"_"+pdf+"_mtrun"+TString::Format("%i",mass)+"_pt30_mu0.5.root";
  if(scheme=="pole") filename = "../../rootfiles/"+energy+"_"+pdf+"_mt"+TString::Format("%i",mass)+"_pt30_mu0.5.root";
  TGraphErrors *gref_scale_down = readGraph(filename,title+ptcut,false);

  filename = "../../rootfiles/"+energy+"_"+pdf+"_mtrun"+TString::Format("%i",mass+deltamass)+"_pt30_mu1.root";
  if(scheme=="pole") filename = "../../rootfiles/"+energy+"_"+pdf+"_mt"+TString::Format("%i",mass+deltamass)+"_pt30_mu1.root";
  TGraphErrors *g_up = readGraph(filename,title+ptcut,false);

  filename = "../../rootfiles/"+energy+"_"+pdf+"_mtrun"+TString::Format("%i",mass-deltamass)+"_pt30_mu1.root";
  if(scheme=="pole") filename = "../../rootfiles/"+energy+"_"+pdf+"_mt"+TString::Format("%i",mass-deltamass)+"_pt30_mu1.root";
  TGraphErrors *g_down = readGraph(filename,title+ptcut,false);

  int n=12;
  if(distribution=="n3_12_") n=12;
  if(distribution=="n3_24_") n=24;

  TH1F* h_gref_scale_up = Histo(gref_scale_up,n);
  TH1F* h_gref = Histo(gref,n);
  TH1F* h_gref_scale_down = Histo(gref_scale_down,n);

  TH1F* h_g_up = Histo(g_up,n);
  TH1F* h_g_down = Histo(g_down,n);

  TCanvas *canv0 = new TCanvas ("new0","new0",1000,800);
   
  canv0->cd();
  if(scheme=="running")h_gref_scale_up->GetYaxis()->SetTitle("#Rgothic(m(m)=X, #mu=Y)");
  else h_gref_scale_up->GetYaxis()->SetTitle("#Rgothic(M_{t}=X, #mu=Y)");
  h_gref_scale_up->GetXaxis()->SetTitle("#rho_{s}");
  gref_scale_up->GetYaxis()->SetRangeUser(0,3.5);
  //gref_scale_up->GetXaxis()->SetRangeUser(0,1);
  h_gref_scale_up->GetYaxis()->SetLabelSize(0.04);
  h_gref_scale_up->GetXaxis()->SetLabelSize(0.04);
  h_gref_scale_up->SetLineColor(kGray);
  h_gref_scale_up->SetLineStyle(2);
  h_gref_scale_up->SetLineWidth(4);
  h_gref_scale_up->SetMarkerColor(kGray);
  h_gref_scale_up->SetMarkerSize(0.);
  h_gref_scale_up->Draw("h");
  
  h_gref->SetLineColor(kBlack);
  h_gref->SetLineStyle(1);
  h_gref->SetLineWidth(3);
  h_gref->SetMarkerColor(kBlack);
  h_gref->SetMarkerSize(0.);
  h_gref->Draw("hsame");

  h_gref_scale_down->SetLineColor(kOrange);
  h_gref_scale_down->SetLineStyle(2);
  h_gref_scale_down->SetLineWidth(3);
  h_gref_scale_down->SetMarkerColor(kOrange);
  h_gref_scale_down->SetMarkerSize(0.);
  h_gref_scale_down->Draw("hsame");

 
  TLegend *leg0 = new TLegend(0.55,0.7,0.9,0.9);//Variables
  leg0->SetHeader(energy+", "+ptcut);
  if(scheme=="running") {
    leg0->AddEntry(h_gref_scale_up,TString::Format("m(m)=%i GeV, #mu=2#timesm(m)",mass),"l");
    leg0->AddEntry(h_gref,TString::Format("m(m)=%i GeV, #mu=m(m)",mass),"l");
    leg0->AddEntry(h_gref_scale_down,TString::Format("m(m)=%i GeV, #mu=m(m)/2",mass),"l");
  } else {
    leg0->AddEntry(h_gref_scale_up,TString::Format("M_{t}=%i GeV, #mu=2#timesM_{t}",mass),"l");
    leg0->AddEntry(h_gref,TString::Format("M_{t}=%i GeV, #mu=M_{t}",mass),"l");
    leg0->AddEntry(h_gref_scale_down,TString::Format("M_{t}=%i GeV, #mu=M_{t}/2",mass),"l");
  }

  leg0->SetLineWidth(0);
  leg0->SetFillColor(0);
  leg0->SetShadowColor(0);
  leg0->Draw();


  
 TCanvas *canv1 = new TCanvas ("new1","new1",1000,800);
   
  canv1->cd();
  if(scheme=="running") h_gref->GetYaxis()->SetTitle("#Rgothic(m(m)=X, #mu=Y)");
  else h_gref->GetYaxis()->SetTitle("#Rgothic(M_{t}=X, #mu=Y)");
  h_gref->GetXaxis()->SetTitle("#rho_{s}");
  gref->GetYaxis()->SetRangeUser(0,3.5);
  //gref->GetXaxis()->SetRangeUser(0,1);
  h_gref->GetYaxis()->SetLabelSize(0.04);
  h_gref->GetXaxis()->SetLabelSize(0.04);
  h_gref->SetLineColor(kBlack);
  h_gref->SetLineStyle(1);
  h_gref->SetLineWidth(2);
  h_gref->SetMarkerColor(kBlack);
  h_gref->SetMarkerSize(0.);
  h_gref->Draw("h");
  
  h_g_up->SetLineColor(2);
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
  h_g_down->Draw("hsame");

 
  TLegend *leg1 = new TLegend(0.55,0.7,0.9,0.9);//Variables
  leg1->SetHeader(energy+", "+ptcut);
  if(scheme=="running") {
    leg1->AddEntry(h_gref,TString::Format("m(m)=%i GeV, #mu=m(m)",mass),"l");
    leg1->AddEntry(h_g_up,TString::Format("m(m)=%i GeV, #mu=m(m)",mass+deltamass),"l");
    leg1->AddEntry(h_g_down,TString::Format("m(m)=%i GeV, #mu=m(m)",mass-deltamass),"l");
  } else {
    leg1->AddEntry(h_gref,TString::Format("M_{t}=%i GeV, #mu=M_{t}",mass),"l");
    leg1->AddEntry(h_g_up,TString::Format("M_{t}=%i GeV, #mu=M_{t}",mass+deltamass),"l");
    leg1->AddEntry(h_g_down,TString::Format("M_{t}=%i GeV, #mu=M_{t}",mass-deltamass),"l");
  }

  leg1->SetLineWidth(0);
  leg1->SetFillColor(0);
  leg1->SetShadowColor(0);
  leg1->Draw();
  
  // -------------------------------------------------------------------
  
  TGraphErrors *g_scale_down = NormGraphs(gref_scale_down,gref,2);
  TGraphErrors *g_scale_up = NormGraphs(gref_scale_up,gref,2);

  TGraphErrors *g_mass_up= NormGraphs(g_up,gref,2);
  TGraphErrors *g_mass_down = NormGraphs(g_down,gref,2);


  TCanvas *canv2 = new TCanvas ("new2","new2",1000,800);
   
  canv2->cd();
  if(scheme=="running")g_scale_up->GetYaxis()->SetTitle("#Rgothic(m(m)=X, #mu=Y) / reference");
  else g_scale_up->GetYaxis()->SetTitle("#Rgothic(M_{t}=X, #mu=Y) / reference");
  g_scale_up->GetXaxis()->SetTitle("#rho_{s}");
  g_scale_up->GetYaxis()->SetRangeUser(0,3);
  //g_scale_up->GetXaxis()->SetRangeUser(0,1);
  g_scale_up->GetYaxis()->SetLabelSize(0.04);
  g_scale_up->GetXaxis()->SetLabelSize(0.04);
  g_scale_up->SetLineColor(kGray);
  g_scale_up->SetLineStyle(2);
  g_scale_up->SetLineWidth(4);
  g_scale_up->SetMarkerColor(kGray);
  g_scale_up->SetMarkerSize(0.);
  g_scale_up->Draw("alp");

  g_scale_down->SetLineColor(kGray+2);
  g_scale_down->SetLineStyle(1);
  g_scale_down->SetLineWidth(1);
  g_scale_down->SetMarkerColor(kGray+2);
  g_scale_down->SetMarkerSize(0.);
  g_scale_down->Draw("lp");

  g_mass_up->SetLineColor(2);
  g_mass_up->SetLineStyle(1);
  g_mass_up->SetLineWidth(2);
  g_mass_up->SetMarkerColor(2);
  g_mass_up->SetMarkerSize(0.);
  g_mass_up->Draw("lp");

  g_mass_down->SetLineColor(4);
  g_mass_down->SetLineStyle(1);
  g_mass_down->SetLineWidth(2);
  g_mass_down->SetMarkerColor(4);
  g_mass_down->SetMarkerSize(0.);
  g_mass_down->Draw("lp");

 

  TLegend *leg2 = new TLegend(0.55,0.7,0.9,0.9);//Variables
  leg2->SetHeader(energy+", "+ptcut);
  if(scheme=="running") {
    leg2->AddEntry(g_scale_up,TString::Format("m(m)=%i GeV, #mu=2#timesm(m)",mass),"lpe");
    leg2->AddEntry(g_scale_down,TString::Format("m(m)=%i GeV, #mu=m(m)/2",mass),"lpe");
    leg2->AddEntry(g_mass_up,TString::Format("m(m)=%i GeV, #mu=m(m)",mass+5),"lpe");
    leg2->AddEntry(g_mass_down,TString::Format("m(m)=%i GeV, #mu=m(m)",mass-5),"lpe");
  } else {
    leg2->AddEntry(g_scale_up,TString::Format("M_{t}=%i GeV, #mu=2#timesM_{t}",mass),"lpe");
    leg2->AddEntry(g_scale_down,TString::Format("M_{t}=%i GeV, #mu=M_{t}/2",mass),"lpe");
    leg2->AddEntry(g_mass_up,TString::Format("M_{t}=%i GeV, #mu=M_{t}",mass+5),"lpe");
    leg2->AddEntry(g_mass_down,TString::Format("M_{t}=%i GeV, #mu=M_{t}",mass-5),"lpe");
  }

  leg2->SetLineWidth(0);
  leg2->SetFillColor(0);
  leg2->SetShadowColor(0);
  leg2->Draw();

}

