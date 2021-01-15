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


TH1F *Histo(TGraphErrors* graph, TString distribution = "n3_12_") {


  Double_t *y;
  Double_t *ey;
  y=graph->GetY();
  ey=graph->GetEY();

  
  if(distribution=="n3_12_" || distribution=="n3_24_" ) {
    int n=12;
    if(distribution=="n3_12_") n=12;
    if(distribution=="n3_24_") n=24;
    
    //  int n=2;
    TH1F* h = new TH1F("h","h",n,-0.1,1.1); // the histogram (you should set the number of bins, the title etc)

    for(int i=0; i < graph->GetN(); ++i) {
      h->SetBinContent(i+1,y[i]);
      h->SetBinError(i+1,ey[i]);
    }
    
    return h;
  }

  if(distribution=="n3_CMS13TeV_" ){

    Float_t bins[] = {0, 0.18, 0.22, 0.27, 0.32, 0.38, 0.45,0.53, 0.62, 0.71, 1.0};
    Int_t  binnum = sizeof(bins)/sizeof(Float_t) - 1;
    TH1F *h = new TH1F("h","h",binnum,bins);
    for(int i=0; i < graph->GetN(); ++i) {
      h->SetBinContent(i+1,y[i]);
      h->SetBinError(i+1,ey[i]);
    }

    return h;    
    
  }

  cout<<" Error when converting Graph to Histogram Histo() "<< "distribution="<<distribution<<endl;
  return NULL;

}

TGraphErrors* readGraph(TString filename,TString title) {

  TFile _file(filename);
  double integral=0;
  TGraphErrors *results = (TGraphErrors*) _file.Get(title.Data());

  Double_t *y=results->GetY();
  Double_t *ey=results->GetEY();
  Double_t *ex=results->GetEX();
 
  for(int i=0; i<results->GetN(); i++) integral+=y[i]*ex[i]*2.;

  for(int i=0; i<results->GetN(); i++) {
    y[i]=y[i]/(integral);
    ey[i]=ey[i]/(integral);
  }
					 

  _file.Close();
  return results;
}

void Plots2Dist_mass( TString scheme="pole", TString energy="LHC13",  TString pdf ="CT18NLO", TString title="n3_24_",TString ptcut="pt50", float mass=173){

   
  TString folder_root="../../data/LHC13_CT18NLO/rootfiles/";

  gROOT->Reset();
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);

  TString s_mass, s_mass_up, s_mass_down;

  if( (mass - (int)mass) >0 ) {
    s_mass = TString::Format("%.1f",mass);
    s_mass_up = TString::Format("%.1f",mass+5);
    s_mass_down = TString::Format("%.1f",mass-5);

  } else {
    s_mass = TString::Format("%i",(int)mass);
    s_mass_up = TString::Format("%i",(int)(mass+5));
    s_mass_down = TString::Format("%i",(int)(mass-5));

  }
  
  // read files
  TString filename = folder_root+"/"+energy+"_"+pdf+"_mt"+s_mass+"_pt30_mu1.root";
  if(scheme=="pole") filename = folder_root+"/"+energy+"_"+pdf+"_mt"+s_mass+"_pt30_mu1.root";
  cout<<filename<<endl;
  TGraphErrors *gref = readGraph(filename,title+ptcut);
  
  filename = folder_root+"/"+energy+"_"+pdf+"_mt"+s_mass_up+"_pt30_mu1.root";
  if(scheme=="pole")  filename = folder_root+"/"+energy+"_"+pdf+"_mt"+s_mass_up+"_pt30_mu1.root";
  TGraphErrors *gref_mass_up = readGraph(filename,title+ptcut);
  
  filename = folder_root+"/"+energy+"_"+pdf+"_mt"+s_mass_down+"_pt30_mu1.root";
  if(scheme=="pole") filename = folder_root+"/"+energy+"_"+pdf+"_mt"+s_mass_down+"_pt30_mu1.root";
  TGraphErrors *gref_mass_down = readGraph(filename,title+ptcut);


  // Draw TGraphs
  TCanvas *canv0 = new TCanvas ("new_mass0","new_mass0",1000,800);
  canv0->cd();
  gref_mass_up->GetYaxis()->SetTitle("#Rgothic(M_{t}=X, #mu=Y)");
  gref_mass_up->GetXaxis()->SetTitle("#rho_{s}");
  gref_mass_up->GetYaxis()->SetRangeUser(0,3.5);
  gref_mass_up->GetXaxis()->SetRangeUser(0,1);
  gref_mass_up->GetYaxis()->SetLabelSize(0.04);
  gref_mass_up->GetXaxis()->SetLabelSize(0.04);
  gref_mass_up->SetLineColor(kGray);
  gref_mass_up->SetLineStyle(2);
  gref_mass_up->SetLineWidth(4);
  gref_mass_up->SetMarkerColor(kGray);
  gref_mass_up->SetMarkerSize(0.);
  gref_mass_up->Draw("alp");
  
  gref->SetLineColor(kBlack);
  gref->SetLineStyle(1);
  gref->SetLineWidth(3);
  gref->SetMarkerColor(kBlack);
  gref->SetMarkerSize(0.);
  gref->Draw("lp");

  gref_mass_down->SetLineColor(kOrange);
  gref_mass_down->SetLineStyle(2);
  gref_mass_down->SetLineWidth(3);
  gref_mass_down->SetMarkerColor(kOrange);
  gref_mass_down->SetMarkerSize(0.);
  gref_mass_down->Draw("lp");

 
  TLegend *leg0 = new TLegend(0.55,0.7,0.9,0.9);//Variables
  leg0->SetHeader(energy+", CT18NLO, "+ptcut);
  leg0->AddEntry(gref_mass_up,TString::Format("M_{t}=%s GeV, #mu=M_{t}",s_mass_up.Data()),"lep");
  leg0->AddEntry(gref,TString::Format("M_{t}=%s GeV, #mu=M_{t}",s_mass.Data()),"lep");
  leg0->AddEntry(gref_mass_down,TString::Format("M_{t}=%s GeV, #mu=M_{t}",s_mass_down.Data()),"lep");
  leg0->Draw();


  // Draw Histograms
  TH1F* h_gref_mass_up = Histo(gref_mass_up,title);
  TH1F* h_gref = Histo(gref,title);
  TH1F* h_gref_mass_down = Histo(gref_mass_down,title);
  
  TCanvas *canv1 = new TCanvas ("new_mass1","new_mass1",1000,800);
  canv1->cd();
  h_gref_mass_up->Divide(h_gref);
  h_gref_mass_up->GetYaxis()->SetTitle("ratio #Rgothic");
  h_gref_mass_up->GetXaxis()->SetTitle("#rho_{s}");
  // h_gref_mass_up->GetYaxis()->SetRangeUser(0,3.5);
  h_gref_mass_up->GetXaxis()->SetRangeUser(0,1);
  h_gref_mass_up->GetYaxis()->SetLabelSize(0.04);
  h_gref_mass_up->GetXaxis()->SetLabelSize(0.04);
  h_gref_mass_up->SetLineColor(kGray);
  h_gref_mass_up->SetLineStyle(2);
  h_gref_mass_up->SetLineWidth(4);
  h_gref_mass_up->SetMarkerColor(kGray);
  h_gref_mass_up->SetMarkerSize(0.);
  h_gref_mass_up->Draw("h");
  
  //h_gref->SetLineColor(kBlack);
  // h_gref->SetLineStyle(1);
  // h_gref->SetLineWidth(3);
  // h_gref->SetMarkerColor(kBlack);
  // h_gref->SetMarkerSize(0.);
  //  h_gref->Draw("hsame");

  h_gref_mass_down->Divide(h_gref);
  h_gref_mass_down->SetLineColor(kOrange);
  h_gref_mass_down->SetLineStyle(2);
  h_gref_mass_down->SetLineWidth(3);
  h_gref_mass_down->SetMarkerColor(kOrange);
  h_gref_mass_down->SetMarkerSize(0.);
  h_gref_mass_down->Draw("hsame");

 
  TLegend *leg1 = new TLegend(0.55,0.7,0.9,0.9);//Variables
  leg1->SetHeader(energy+", CT18NLO, "+ptcut);
  leg1->AddEntry(gref_mass_up,TString::Format("M_{t}=%s GeV / M_{t}=%s GeV , #mu=M_{t}",s_mass_up.Data(),s_mass.Data()),"lep");
  //leg1->AddEntry(gref,TString::Format("M_{t}=%s GeV, #mu=M_{t}",s_mass.Data()),"lep");
  leg1->AddEntry(gref_mass_down,TString::Format("M_{t}=%s GeV / M_{t}=%s GeV , #mu=M_{t}",s_mass_down.Data(),s_mass.Data()),"lep");
  leg1->Draw();
  
}



void Plots2Dist_scale( TString scheme="pole", TString energy="LHC13", TString pdf ="CT18NLO", TString title="n3_24_",TString ptcut="pt50", float mass=173){

   
  TString folder_root="../../data/LHC13_CT18NLO/rootfiles/";

  gROOT->Reset();
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);

  TString s_mass, s_mass_up, s_mass_down;

  if( (mass - (int)mass) >0 ) {
    s_mass = TString::Format("%.1f",mass);
  } else {
    s_mass = TString::Format("%i",(int)mass);
  }
  
  // read files
  TString filename = folder_root+"/"+energy+"_"+pdf+"_mt"+s_mass+"_pt30_mu1.root";
  if(scheme=="pole") filename = folder_root+"/"+energy+"_"+pdf+"_mt"+s_mass+"_pt30_mu1.root";
  cout<<filename<<endl;
  TGraphErrors *gref = readGraph(filename,title+ptcut);
  
  filename = folder_root+"/"+energy+"_"+pdf+"_mt"+s_mass+"_pt30_mu2.root";
  if(scheme=="pole")  filename = folder_root+"/"+energy+"_"+pdf+"_mt"+s_mass+"_pt30_mu2.root";
  TGraphErrors *gref_scale_up = readGraph(filename,title+ptcut);
  
  filename = folder_root+"/"+energy+"_"+pdf+"_mt"+s_mass+"_pt30_mu0.5.root";
  if(scheme=="pole") filename = folder_root+"/"+energy+"_"+pdf+"_mt"+s_mass+"_pt30_mu0.5.root";
  TGraphErrors *gref_scale_down = readGraph(filename,title+ptcut);


  // Draw TGraphs
  TCanvas *canv0 = new TCanvas ("new0","new0",1000,800);
  canv0->cd();
  gref_scale_up->GetYaxis()->SetTitle("#Rgothic(M_{t}=X, #mu=Y)");
  gref_scale_up->GetXaxis()->SetTitle("#rho_{s}");
  gref_scale_up->GetYaxis()->SetRangeUser(0,3.5);
  gref_scale_up->GetXaxis()->SetRangeUser(0,1);
  gref_scale_up->GetYaxis()->SetLabelSize(0.04);
  gref_scale_up->GetXaxis()->SetLabelSize(0.04);
  gref_scale_up->SetLineColor(kGray);
  gref_scale_up->SetLineStyle(2);
  gref_scale_up->SetLineWidth(4);
  gref_scale_up->SetMarkerColor(kGray);
  gref_scale_up->SetMarkerSize(0.);
  gref_scale_up->Draw("alp");
  
  gref->SetLineColor(kBlack);
  gref->SetLineStyle(1);
  gref->SetLineWidth(3);
  gref->SetMarkerColor(kBlack);
  gref->SetMarkerSize(0.);
  gref->Draw("lp");

  gref_scale_down->SetLineColor(kOrange);
  gref_scale_down->SetLineStyle(2);
  gref_scale_down->SetLineWidth(3);
  gref_scale_down->SetMarkerColor(kOrange);
  gref_scale_down->SetMarkerSize(0.);
  gref_scale_down->Draw("lp");

 
  TLegend *leg0 = new TLegend(0.55,0.7,0.9,0.9);//Variables
  leg0->SetHeader(energy+", CT18NLO, "+ptcut);
  leg0->AddEntry(gref_scale_up,TString::Format("M_{t}=%s GeV, #mu=2#timesM_{t}",s_mass.Data()),"lep");
  leg0->AddEntry(gref,TString::Format("M_{t}=%s GeV, #mu=M_{t}",s_mass.Data()),"lep");
  leg0->AddEntry(gref_scale_down,TString::Format("M_{t}=%s GeV, #mu=M_{t}/2",s_mass.Data()),"lep");
  leg0->Draw();


  // Draw Histograms
  TH1F* h_gref_scale_up = Histo(gref_scale_up,title);
  TH1F* h_gref = Histo(gref,title);
  TH1F* h_gref_scale_down = Histo(gref_scale_down,title);
  
  TCanvas *canv1 = new TCanvas ("new1","new1",1000,800);
  canv1->cd();
  h_gref_scale_up->Divide(h_gref);
  h_gref_scale_up->GetYaxis()->SetTitle("ratio #Rgothic");
  h_gref_scale_up->GetXaxis()->SetTitle("#rho_{s}");
  // h_gref_scale_up->GetYaxis()->SetRangeUser(0,3.5);
  h_gref_scale_up->GetXaxis()->SetRangeUser(0,1);
  h_gref_scale_up->GetYaxis()->SetLabelSize(0.04);
  h_gref_scale_up->GetXaxis()->SetLabelSize(0.04);
  h_gref_scale_up->SetLineColor(kGray);
  h_gref_scale_up->SetLineStyle(2);
  h_gref_scale_up->SetLineWidth(4);
  h_gref_scale_up->SetMarkerColor(kGray);
  h_gref_scale_up->SetMarkerSize(0.);
  h_gref_scale_up->Draw("h");
  
  //h_gref->SetLineColor(kBlack);
  // h_gref->SetLineStyle(1);
  // h_gref->SetLineWidth(3);
  // h_gref->SetMarkerColor(kBlack);
  // h_gref->SetMarkerSize(0.);
  //  h_gref->Draw("hsame");

  h_gref_scale_down->Divide(h_gref);
  h_gref_scale_down->SetLineColor(kOrange);
  h_gref_scale_down->SetLineStyle(2);
  h_gref_scale_down->SetLineWidth(3);
  h_gref_scale_down->SetMarkerColor(kOrange);
  h_gref_scale_down->SetMarkerSize(0.);
  h_gref_scale_down->Draw("hsame");

 
  TLegend *leg1 = new TLegend(0.55,0.7,0.9,0.9);//Variables
  leg1->SetHeader(energy+", CT18NLO, "+ptcut);
  leg1->AddEntry(gref_scale_up,TString::Format("M_{t}=%s GeV, #mu=2#timesM_{t}/#mu=M_{t}",s_mass.Data()),"lep");
  //leg1->AddEntry(gref,TString::Format("M_{t}=%s GeV, #mu=M_{t}",s_mass.Data()),"lep");
  leg1->AddEntry(gref_scale_down,TString::Format("M_{t}=%s GeV, #mu=0.5M_{t} / #mu=M_{t}",s_mass.Data()),"lep");
  leg1->Draw();
  
}

 
  
  

void Plots2Dist_pdf( TString scheme="pole", TString energy="LHC13",  TString title="n3_24_",TString ptcut="pt50", float mass=173){

  TString pdf1="CT18NLO";
  TString folder_root1="../../data/LHC13_"+pdf1+"/rootfiles/";

  TString pdf2="CT10nlo";
  TString folder_root2="../../data/LHC13_"+pdf2+"/rootfiles/";

  TString pdf3="CT10";
  TString folder_root3="../../data/LHC13_"+pdf3+"/rootfiles/";

  TString pdf4="MMHT2014nlo68cl";
  TString folder_root4="../../data/LHC13_"+pdf4+"/rootfiles/";

  TString pdf5="ABMP16_5_nlo";
  TString folder_root5="../../data/LHC13_"+pdf5+"/rootfiles/";
  
  gROOT->Reset();
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);

  TString s_mass, s_mass_up, s_mass_down;

  if( (mass - (int)mass) >0 ) {
    s_mass = TString::Format("%.1f",mass);
  } else {
    s_mass = TString::Format("%i",(int)mass);
  }
  
  // read files
  TString filename = folder_root1+"/"+energy+"_"+pdf1+"_mt"+s_mass+"_pt30_mu1.root";
  if(scheme=="pole") filename = folder_root1+"/"+energy+"_"+pdf1+"_mt"+s_mass+"_pt30_mu1.root";
  cout<<filename<<endl;
  TGraphErrors *gref = readGraph(filename,title+ptcut);
  
  filename = folder_root2+"/"+energy+"_"+pdf2+"_mt"+s_mass+"_pt30_mu1.root";
  if(scheme=="pole")  filename = folder_root2+"/"+energy+"_"+pdf2+"_mt"+s_mass+"_pt30_mu1.root";
  TGraphErrors *gref_pdf2 = readGraph(filename,title+ptcut);
  
  filename = folder_root3+"/"+energy+"_"+pdf3+"_mt"+s_mass+"_pt30_mu1.root";
  if(scheme=="pole") filename = folder_root3+"/"+energy+"_"+pdf3+"_mt"+s_mass+"_pt30_mu1.root";
  TGraphErrors *gref_pdf3 = readGraph(filename,title+ptcut);

  filename = folder_root4+"/"+energy+"_"+pdf4+"_mt"+s_mass+"_pt30_mu1.root";
  if(scheme=="pole") filename = folder_root4+"/"+energy+"_"+pdf4+"_mt"+s_mass+"_pt30_mu1.root";
  TGraphErrors *gref_pdf4 = readGraph(filename,title+ptcut);


  filename = folder_root5+"/"+energy+"_"+pdf5+"_mt"+s_mass+"_pt30_mu1.root";
  if(scheme=="pole") filename = folder_root5+"/"+energy+"_"+pdf5+"_mt"+s_mass+"_pt30_mu1.root";
  TGraphErrors *gref_pdf5 = readGraph(filename,title+ptcut);


  // Draw TGraphs
  TCanvas *canv0 = new TCanvas ("newpdf0","newpdf0",1000,800);
  canv0->cd();
  gref_pdf2->GetYaxis()->SetTitle("#Rgothic(M_{t}=X, #mu=Y)");
  gref_pdf2->GetXaxis()->SetTitle("#rho_{s}");
  gref_pdf2->GetYaxis()->SetRangeUser(0,3.5);
  gref_pdf2->GetXaxis()->SetRangeUser(0,1);
  gref_pdf2->GetYaxis()->SetLabelSize(0.04);
  gref_pdf2->GetXaxis()->SetLabelSize(0.04);
  gref_pdf2->SetLineColor(kGray);
  gref_pdf2->SetLineStyle(2);
  gref_pdf2->SetLineWidth(4);
  gref_pdf2->SetMarkerColor(kGray);
  gref_pdf2->SetMarkerSize(0.);
  gref_pdf2->Draw("alp");
  
  gref->SetLineColor(kBlack);
  gref->SetLineStyle(1);
  gref->SetLineWidth(3);
  gref->SetMarkerColor(kBlack);
  gref->SetMarkerSize(0.);
  gref->Draw("lp");

  gref_pdf3->SetLineColor(kOrange);
  gref_pdf3->SetLineStyle(2);
  gref_pdf3->SetLineWidth(3);
  gref_pdf3->SetMarkerColor(kOrange);
  gref_pdf3->SetMarkerSize(0.);
  gref_pdf3->Draw("lp");

  gref_pdf4->SetLineColor(kBlue);
  gref_pdf4->SetLineStyle(3);
  gref_pdf4->SetLineWidth(2);
  gref_pdf4->SetMarkerColor(kBlue);
  gref_pdf4->SetMarkerSize(0.);
  gref_pdf4->Draw("lp");

  gref_pdf5->SetLineColor(kMagenta);
  gref_pdf5->SetLineStyle(1);
  gref_pdf5->SetLineWidth(1);
  gref_pdf5->SetMarkerColor(kMagenta);
  gref_pdf5->SetMarkerSize(0.);
  gref_pdf5->Draw("lp");

 
  TLegend *leg0 = new TLegend(0.55,0.7,0.9,0.9);//Variables
  leg0->SetHeader(energy+", "+ptcut);
  leg0->AddEntry(gref,pdf1,"lep");
  leg0->AddEntry(gref_pdf2,pdf2,"lep");
  leg0->AddEntry(gref_pdf3,pdf3,"lep");
  leg0->AddEntry(gref_pdf4,pdf4,"lep");
  leg0->AddEntry(gref_pdf5,pdf5,"lep");

  leg0->Draw();


   // Draw Histograms
  TH1F* h_gref_pdf2 = Histo(gref_pdf2,title);
  TH1F* h_gref = Histo(gref,title);
  TH1F* h_gref_pdf3 = Histo(gref_pdf3,title);
  TH1F* h_gref_pdf4 = Histo(gref_pdf4,title);
  TH1F* h_gref_pdf5 = Histo(gref_pdf5,title);

  TCanvas *canv1 = new TCanvas ("newpdf1","newpdf1",1000,800);
  canv1->cd();
  h_gref_pdf2->Divide(h_gref);
  h_gref_pdf2->GetYaxis()->SetTitle("ratio #Rgothic");
  h_gref_pdf2->GetXaxis()->SetTitle("#rho_{s}");
  // h_gref_pdf2->GetYaxis()->SetRangeUser(0,3.5);
  h_gref_pdf2->GetXaxis()->SetRangeUser(0,1);
  h_gref_pdf2->GetYaxis()->SetLabelSize(0.04);
  h_gref_pdf2->GetXaxis()->SetLabelSize(0.04);
  
  h_gref_pdf2->SetLineColor(kGray);
  h_gref_pdf2->SetLineStyle(2);
  h_gref_pdf2->SetLineWidth(4);
  h_gref_pdf2->SetMarkerColor(kGray);
  h_gref_pdf2->SetMarkerSize(0.);
  h_gref_pdf2->Draw("h");

  h_gref_pdf3->Divide(h_gref);
  h_gref_pdf3->SetLineColor(kOrange);
  h_gref_pdf3->SetLineStyle(2);
  h_gref_pdf3->SetLineWidth(3);
  h_gref_pdf3->SetMarkerColor(kOrange);
  h_gref_pdf3->SetMarkerSize(0.);
  h_gref_pdf3->Draw("hsame");

  h_gref_pdf4->Divide(h_gref);
  h_gref_pdf4->SetLineColor(kBlue);
  h_gref_pdf4->SetLineStyle(3);
  h_gref_pdf4->SetLineWidth(2);
  h_gref_pdf4->SetMarkerColor(kBlue);
  h_gref_pdf4->SetMarkerSize(0.);
  h_gref_pdf4->Draw("hsame");

  h_gref_pdf5->Divide(h_gref);
  h_gref_pdf5->SetLineColor(kMagenta);
  h_gref_pdf5->SetLineStyle(1);
  h_gref_pdf5->SetLineWidth(1);
  h_gref_pdf5->SetMarkerColor(kMagenta);
  h_gref_pdf5->SetMarkerSize(0.);
  h_gref_pdf5->Draw("hsame");

  TLegend *leg1 = new TLegend(0.55,0.7,0.9,0.9);//Variables
  leg1->SetHeader(energy+", "+ptcut);
  leg1->AddEntry(h_gref_pdf2,pdf2+"/"+pdf1,"lep");
  leg1->AddEntry(h_gref_pdf3,pdf3+"/"+pdf1,"lep");
  leg1->AddEntry(h_gref_pdf4,pdf4+"/"+pdf1,"lep");
  leg1->AddEntry(h_gref_pdf5,pdf5+"/"+pdf1,"lep");

  leg1->Draw();
  
}


 
void Plots2Dist(){

  //void Plots2Dist_scale( TString scheme="pole", TString energy="LHC13",  TString title="n3_24_",TString ptcut="pt50", float mass=173){

  Plots2Dist_pdf("pole","LHC13","n3_24_","pt50",173);
  Plots2Dist_scale("pole","LHC13","CT18NLO","n3_24_","pt50",173);
  Plots2Dist_mass("pole","LHC13","CT18NLO","n3_24_","pt50",173);

  //  Plots2Dist_pdf("running","LHC13","n3_12_","pt50",173);
  //Plots2Dist_scale("running","LHC13","CT18NLO","n3_12_","pt50",173);
  //Plots2Dist_mass("running","LHC13","CT18NLO","n3_12_","pt50",173);

}
