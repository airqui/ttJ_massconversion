#include <iostream>
#include <string>
#include <algorithm>
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
#include "TF1.h"
#include "TH1.h"
#include "TH2F.h"
#include "TImage.h"
#include "TMinuit.h"
#include "Fit_pol.h"


double calc_average(std::vector<double>masa_temp )
{
  double average=0;
  for(int i=0; i<masa_temp.size(); i++) {
    average+=masa_temp.at(i);
  }
  average/=masa_temp.size();
  return average;
}

double calc_std(std::vector<double>masa_temp, double average )
{
  double std=0;
  for(int i=0; i<masa_temp.size(); i++) {
    std+= (average-masa_temp.at(i))*(average-masa_temp.at(i));
  }

  std=sqrt(std/masa_temp.size());
  return std;
}


int scalevariations(TString pdf="CT18NLO",int iter=1000){

  double  masa_pt[4];
  double  emasa_pt[4];

  TString pt[4];
  pt[0]="n3_12_pt30";
  pt[1]="n3_12_pt50";
  pt[2]="n3_12_pt75";
  pt[3]="n3_12_pt100";

  for(int j=0; j<4; j++) {
      
    parametrize_fitfunction("CT18NLO","LHC13", 158,9,1, "running", "mu1",pt[j]);
	
    std::vector<double>masa_temp;
    for(int k=0; k<iter; k++) {
      TRandom *r = new TRandom1();
      int seed=r->Integer((j+1)*(k+1)*99999);
      extraerdatos_randomize_scale("CT18NLO","LHC13", 166,"running", "mu1","mu2","mu0.5",pt[j],seed);
      Fit(false);
      masa_temp.push_back(mass);
    }
	
    double average=calc_average(masa_temp);
    double std_dev=calc_std(masa_temp,average);
    
    masa_pt[j]=average;
    emasa_pt[j]=std_dev;
  
  }

   
  for(int j=0; j<4; j++) cout<<pt[j]<<"  Mass (mu1)=" << masa_pt[j] <<"+-  "<<emasa_pt[j]<<" GeV "<<endl;

  double x[4];
 
  for(int j=0; j<4; j++){
    x[j]=30;
    if(j>0) x[j]=x[j-1]+25;
    if(j==1) x[j]=x[j-1]+20;
  }
  
  TGraph* g = new TGraph(4,x,emasa_pt);

  SetAtlasStyle();
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);


  TCanvas * canvas = new TCanvas("canvas","canvas",1000,800);
  gPad->SetGridx();
  gPad->SetGridy();

  g->GetYaxis()->SetRangeUser(-5,5);
  g->GetYaxis()->SetTitle("#Delta M_{t} [GeV]");
  g->GetXaxis()->SetTitle("p_{T}-cut [GeV]");
  g->SetLineColor(1);
  g->SetLineWidth(2);
  g->Draw("al");

  TLegend *leg1 = new TLegend(0.6,0.7,0.98,0.9);//Variables
  leg1->SetFillStyle(0);
  leg1->AddEntry(g,"Symmetrized error","l");
  leg1->Draw();

  
  
  return 0;
}


int PDFVarPole(TString scale="mu1", int bin_exclude=5){

  std::vector<std::vector<double> >masa_pt;
  std::vector<std::vector<double> >emasa_pt;

  TString pt[4];
  pt[0]=TString::Format("n3_%i_pt30",nbins);
  pt[1]=TString::Format("n3_%i_pt50",nbins);
  pt[2]=TString::Format("n3_%i_pt75",nbins);
  pt[3]=TString::Format("n3_%i_pt100",nbins);

  bintoremove=bin_exclude;

  for(int j=0; j<4; j++) {

    std::vector<double>masa;
      
    for(int i=0; i<3; i++) {
	
      if(i==0) parametrize_fitfunction("MMHT2014nlo68cl","LHC13", 168,10,1, "pole", "mu1",pt[j]);
      if(i==1) parametrize_fitfunction("CT18NLO","LHC13", 168,10,1, "pole", "mu1",pt[j]);
      if(i==2) parametrize_fitfunction("ABMP16_5_nlo","LHC13", 168,10,1, "pole", "mu1",pt[j]);
      extraerdatos("CT18NLO","LHC13", 173,"pole","mu1",pt[j]);
	
      Fit(false);// if false, the Chi2 is defined as : pow(data - theory,2)/theory
      //if true, then pow(data - theory,2)/error_data --> where the error data can be set in extraerdatos by assuming an efficency of reconstruction, for example.
      masa.push_back(mass);
    }
    masa_pt.push_back(masa);
  }

  double x[4];
  double yup[4];
  double ydown[4];
  double y[4];
  
  for(int j=0; j<masa_pt.size(); j++){
    cout<<pt[j]<<" CT18NLO  " << masa_pt.at(j).at(1) <<" GeV;   MMHT2014nlo68cl "<<masa_pt.at(j).at(0)-masa_pt.at(j).at(1)<<" GeV;  ABMP16_5_nlo: "<<masa_pt.at(j).at(0)-masa_pt.at(j).at(2)<<" GeV"<<endl;

    x[j]=30;
    if(j>0) x[j]=x[j-1]+25;
    if(j==1) x[j]=x[j-1]+20;
    yup[j]=masa_pt.at(j).at(0)-masa_pt.at(j).at(1);
    ydown[j]=masa_pt.at(j).at(0)-masa_pt.at(j).at(2);
  }

  TGraph* g_up = new TGraph(4,x,yup);
  TGraph* g_down = new TGraph(4,x,ydown);

  SetAtlasStyle();
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);


  TCanvas * canvas = new TCanvas("canvas_pdf","canvas_pdf",1000,800);
  gPad->SetGridx();
  gPad->SetGridy();

  g_up->GetYaxis()->SetRangeUser(-5,5);
  g_up->GetYaxis()->SetTitle("#Delta M_{t} [GeV]");
  g_up->GetXaxis()->SetTitle("p_{T}-cut [GeV]");
  g_up->SetLineColor(2);
  g_up->SetLineWidth(2);
  g_up->Draw("al");
  g_down->SetLineColor(4);
  g_down->SetLineWidth(2);
  g_down->Draw("l");

  TLegend *leg1 = new TLegend(0.6,0.7,0.98,0.9);//Variables
  leg1->SetFillStyle(0);
  leg1->AddEntry(g_up,"MMHT2014nlo68cl","l");
  leg1->AddEntry(g_down,"ABMP16_5_nlo","l");
  leg1->Draw();
  
  return 0;
}



int ScaleVarPole(TString pdf="CT18NLO", int bin_exclude=5){

  std::vector<std::vector<double> >masa_pt;
  std::vector<std::vector<double> >emasa_pt;

  TString pt[4];
  pt[0]=TString::Format("n3_%i_pt30",nbins);
  pt[1]=TString::Format("n3_%i_pt50",nbins);
  pt[2]=TString::Format("n3_%i_pt75",nbins);
  pt[3]=TString::Format("n3_%i_pt100",nbins);

  bintoremove=bin_exclude;

  for(int j=0; j<4; j++) {

    std::vector<double>masa;
      
    for(int i=0; i<3; i++) {
	
      if(i==0) parametrize_fitfunction(pdf,"LHC13", 168,10,1, "pole", "mu0.5",pt[j]);
      if(i==1) parametrize_fitfunction(pdf,"LHC13", 168,10,1, "pole", "mu1",pt[j]);
      if(i==2) parametrize_fitfunction(pdf,"LHC13", 168,10,1, "pole", "mu2",pt[j]);
      extraerdatos(pdf,"LHC13", 173,"pole","mu1",pt[j]);
	
      Fit(false);// if false, the Chi2 is defined as : pow(data - theory,2)/theory
      //if true, then pow(data - theory,2)/error_data --> where the error data can be set in extraerdatos by assuming an efficency of reconstruction, for example.
      masa.push_back(mass);
    }
    masa_pt.push_back(masa);
  }

  double x[4];
  double yup[4];
  double ydown[4];
  double y[4];
  
  for(int j=0; j<masa_pt.size(); j++){
    cout<<pt[j]<<"  Mass (mu1): " << masa_pt.at(j).at(1) <<" GeV;    DeltaMass (mu2): "<<masa_pt.at(j).at(2)-masa_pt.at(j).at(1)<<" GeV;   DeltaMass (mu0.5): "<<masa_pt.at(j).at(0)-masa_pt.at(j).at(1)<<" GeV"<<endl;

    x[j]=30;
    if(j>0) x[j]=x[j-1]+25;
    if(j==1) x[j]=x[j-1]+20;
    yup[j]=masa_pt.at(j).at(2)-masa_pt.at(j).at(1);
    ydown[j]=masa_pt.at(j).at(0)-masa_pt.at(j).at(1);
    y[j]=max(fabs(masa_pt.at(j).at(2)-masa_pt.at(j).at(0)),max(fabs(masa_pt.at(j).at(2)-masa_pt.at(j).at(1)),fabs(masa_pt.at(j).at(0)-masa_pt.at(j).at(1))))/2.;
  }

  TGraph* g_up = new TGraph(4,x,yup);
  TGraph* g_down = new TGraph(4,x,ydown);
  TGraph* g = new TGraph(4,x,y);

  SetAtlasStyle();
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);


  TCanvas * canvas = new TCanvas("canvas","canvas",1000,800);
  gPad->SetGridx();
  gPad->SetGridy();

  g->GetYaxis()->SetRangeUser(-5,5);
  g->GetYaxis()->SetTitle("#Delta M_{t} [GeV]");
  g->GetXaxis()->SetTitle("p_{T}-cut [GeV]");
  g->SetLineColor(1);
  g->SetLineWidth(2);
  g->Draw("al");
  g_up->SetLineColor(2);
  g_up->SetLineWidth(2);
  g_up->Draw("l");
  g_down->SetLineColor(4);
  g_down->SetLineWidth(2);
  g_down->Draw("l");

  TLegend *leg1 = new TLegend(0.6,0.7,0.98,0.9);//Variables
  leg1->SetFillStyle(0);
  leg1->AddEntry(g,"Symmetrized error","l");
  leg1->AddEntry(g_up,"#mu=2#timesM_{t}","l");
  leg1->AddEntry(g_down,"#mu=M_{t}/2","l");
  leg1->Draw();
  
  return 0;
}


int ScaleVarPole2(TString pdf="CT18NLO"){

  std::vector<std::vector<std::vector<double>> >masa_pt;
  TString pt[4];
  pt[0]=TString::Format("n3_%i_pt30",nbins);
  pt[1]=TString::Format("n3_%i_pt50",nbins);
  pt[2]=TString::Format("n3_%i_pt75",nbins);
  pt[3]=TString::Format("n3_%i_pt100",nbins);

  for(int j=0; j<4; j++) {

    std::vector<std::vector<double> >masa;
      
    for(int i=0; i<3; i++) {
	
      if(i==0) parametrize_fitfunction(pdf,"LHC13", 168,10,1, "pole", "mu0.5",pt[j]);
      if(i==1) parametrize_fitfunction(pdf,"LHC13", 168,10,1, "pole", "mu1",pt[j]);
      if(i==2) parametrize_fitfunction(pdf,"LHC13", 168,10,1, "pole", "mu2",pt[j]);
      extraerdatos(pdf,"LHC13", 173,"pole", "mu1",pt[j]);

      std::vector<double >masa_bin;

      for(int k=0; k<nbins; k++) {
	bintoremove=k;
	Fit(false);
	masa_bin.push_back(mass);
      }
      masa.push_back(masa_bin);
    }
    masa_pt.push_back(masa);
  }

  TGraph* g_pt[4];
  
  for(int j=0; j<masa_pt.size(); j++){

    double x[100];
    double y[100];
    int n=0;
    for(int k=0; k<masa_pt.at(j).at(0).size(); k++) {
	x[k]=k;
	y[k]=max(fabs(masa_pt.at(j).at(2).at(k)-masa_pt.at(j).at(0).at(k)),max(fabs(masa_pt.at(j).at(2).at(k)-masa_pt.at(j).at(1).at(k)),fabs(masa_pt.at(j).at(0).at(k)-masa_pt.at(j).at(1).at(k))))/2.;
	n++;
    }
    g_pt[j] = new TGraph(n,x,y);
  }


  SetAtlasStyle();
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);


  TCanvas * canvas = new TCanvas("canvas2","canvas2",1000,800);
  gPad->SetGridx();
  gPad->SetGridy();

  TLegend *leg1 = new TLegend(0.6,0.7,0.98,0.9);//Variables
  leg1->SetFillStyle(0);

  for(int j=0; j<masa_pt.size(); j++){
    
    g_pt[j]->SetLineColor(j+1);
    g_pt[j]->SetLineWidth(2);
    if(j==0) {
      g_pt[j]->GetYaxis()->SetRangeUser(-5,5);
      g_pt[j]->GetYaxis()->SetTitle("#Delta M_{t} [GeV] (symmetrised)");
      g_pt[j]->GetXaxis()->SetTitle("Excluded bin");
      g_pt[j]->Draw("al");
    } else g_pt[j]->Draw("l");
    leg1->AddEntry(g_pt[j],pt[j],"l");
  }

  leg1->Draw();

  return 0;
}

int ScaleVarRun(TString pdf="CT18NLO", int bin_exclude=9){

  std::vector<std::vector<double> >masa_pt;
  std::vector<std::vector<double> >emasa_pt;

  TString pt[4];
  pt[0]=TString::Format("n3_%i_pt30",nbins);
  pt[1]=TString::Format("n3_%i_pt50",nbins);
  pt[2]=TString::Format("n3_%i_pt75",nbins);
  pt[3]=TString::Format("n3_%i_pt100",nbins);

  
  bintoremove=bin_exclude;
  for(int j=0; j<4; j++) {

    std::vector<double>masa;
      
    for(int i=0; i<3; i++) {
	
      if(i==0) parametrize_fitfunction(pdf,"LHC13", 158,10,1, "running", "mu0.5",pt[j]);
      if(i==1) parametrize_fitfunction(pdf,"LHC13", 158,10,1, "running", "mu1",pt[j]);
      if(i==2) parametrize_fitfunction(pdf,"LHC13", 158,10,1, "running", "mu2",pt[j]);
      extraerdatos(pdf,"LHC13", 173,"pole", "mu1",pt[j]);
	
      //extraerdatos(pdf,"LHC13", 173,"pole", "mu1",pt[j]);
      Fit(false);
      masa.push_back(mass);
    }
    masa_pt.push_back(masa);
  }

  double x[4];
  double yup[4];
  double ydown[4];
  double y[4];
  
  for(int j=0; j<masa_pt.size(); j++){
    cout<<pt[j]<<"  Mass (mu1): " << masa_pt.at(j).at(1) <<" GeV;    DeltaMass (mu2): "<<masa_pt.at(j).at(2)-masa_pt.at(j).at(1)<<" GeV;   DeltaMass (mu0.5): "<<masa_pt.at(j).at(0)-masa_pt.at(j).at(1)<<" GeV"<<endl;

    x[j]=30;
    if(j>0) x[j]=x[j-1]+25;
    if(j==1) x[j]=x[j-1]+20;
    yup[j]=masa_pt.at(j).at(2)-masa_pt.at(j).at(1);
    ydown[j]=masa_pt.at(j).at(0)-masa_pt.at(j).at(1);
    y[j]=max(fabs(masa_pt.at(j).at(2)-masa_pt.at(j).at(0)),max(fabs(masa_pt.at(j).at(2)-masa_pt.at(j).at(1)),fabs(masa_pt.at(j).at(0)-masa_pt.at(j).at(1))))/2.;
  }

  TGraph* g_up = new TGraph(4,x,yup);
  TGraph* g_down = new TGraph(4,x,ydown);
  TGraph* g = new TGraph(4,x,y);

  SetAtlasStyle();
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);


  TCanvas * canvas = new TCanvas("canvas","canvas",1000,800);
  gPad->SetGridx();
  gPad->SetGridy();

  g->GetYaxis()->SetRangeUser(-5,5);
  g->GetYaxis()->SetTitle("#Delta m_{t}(m_{t}) [GeV]");
  g->GetXaxis()->SetTitle("p_{T}-cut [GeV]");
  g->SetLineColor(1);
  g->SetLineWidth(2);
  g->Draw("al");
  g_up->SetLineColor(2);
  g_up->SetLineWidth(2);
  g_up->Draw("l");
  g_down->SetLineColor(4);
  g_down->SetLineWidth(2);
  g_down->Draw("l");

  TLegend *leg1 = new TLegend(0.6,0.7,0.98,0.9);//Variables
  leg1->SetFillStyle(0);
  leg1->AddEntry(g,"Symmetrized error","l");
  leg1->AddEntry(g_up,"#mu=2#times m_{t}(m_{t})","l");
  leg1->AddEntry(g_down,"#mu=m_{t}(m_{t})/2","l");
  leg1->Draw();
  
  return 0;
}

int ScaleVarRun2(TString pdf="CT18NLO"){

  TString pt[4];
  pt[0]=TString::Format("n3_%i_pt30",nbins);
  pt[1]=TString::Format("n3_%i_pt50",nbins);
  pt[2]=TString::Format("n3_%i_pt75",nbins);
  pt[3]=TString::Format("n3_%i_pt100",nbins);

  
  std::vector<std::vector<std::vector<double>> >masa_pt;

  for(int j=0; j<4; j++) {

    std::vector<std::vector<double> >masa;
      
    for(int i=0; i<3; i++) {
	
      if(i==0) parametrize_fitfunction(pdf,"LHC13", 158,10,1, "running", "mu0.5",pt[j]);
      if(i==1) parametrize_fitfunction(pdf,"LHC13", 158,10,1, "running", "mu1",pt[j]);
      if(i==2) parametrize_fitfunction(pdf,"LHC13", 158,10,1, "running", "mu2",pt[j]);
      extraerdatos(pdf,"LHC13", 164,"running", "mu1",pt[j]);

      std::vector<double >masa_bin;

      for(int k=0; k<nbins; k++) {
	bintoremove=k;
	Fit(false);
	masa_bin.push_back(mass);
      }
      masa.push_back(masa_bin);
    }
    masa_pt.push_back(masa);
  }

  TGraph* g_pt[4];
  
  for(int j=0; j<masa_pt.size(); j++){

    double x[100];
    double y[100];
    int n=0;
    for(int k=0; k<masa_pt.at(j).at(0).size(); k++) {
	x[k]=k;
	y[k]=max(fabs(masa_pt.at(j).at(2).at(k)-masa_pt.at(j).at(0).at(k)),max(fabs(masa_pt.at(j).at(2).at(k)-masa_pt.at(j).at(1).at(k)),fabs(masa_pt.at(j).at(0).at(k)-masa_pt.at(j).at(1).at(k))))/2.;
	n++;
    }
    g_pt[j] = new TGraph(n,x,y);
  }


  SetAtlasStyle();
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);


  TCanvas * canvas = new TCanvas("canvas2","canvas2",1000,800);
  gPad->SetGridx();
  gPad->SetGridy();

  TLegend *leg1 = new TLegend(0.6,0.7,0.98,0.9);//Variables
  leg1->SetFillStyle(0);

  for(int j=0; j<masa_pt.size(); j++){
    
    g_pt[j]->SetLineColor(j+1);
    g_pt[j]->SetLineWidth(2);
    if(j==0) {
      g_pt[j]->GetYaxis()->SetRangeUser(-5,5);
      g_pt[j]->GetYaxis()->SetTitle("#Delta m_{t}(m_{t}) [GeV] (symmetrised)");
      g_pt[j]->GetXaxis()->SetTitle("Excluded bin");
      g_pt[j]->Draw("al");
    } else g_pt[j]->Draw("l");
    leg1->AddEntry(g_pt[j],pt[j],"l");
  }

  leg1->Draw();

  return 0;
}



int statvariations(TString pdf="CT18NLO",int iter=1000){

  double  masa_pt[4];
  double  emasa_pt[4];

  TString pt[4];
  pt[0]="n3_24_pt30";
  pt[1]="n3_24_pt50";
  pt[2]="n3_24_pt75";
  pt[3]="n3_24_pt100";
  
  for(int j=0; j<4; j++) {
      
    parametrize_fitfunction(pdf,"LHC13", 168,10,1, "pole", "mu1",pt[j]);
	
    std::vector<double>masa_temp;
    for(int k=0; k<iter; k++) {
      TRandom *r = new TRandom1();
      int seed=r->Integer((j+1)*(k+1)*99999);
      extraerdatos_randomize(pdf,"LHC13", 173,"pole", "mu1",pt[j],seed);
      Fit(false);
      masa_temp.push_back(mass);
    }
	
    double average=calc_average(masa_temp);
    double std_dev=calc_std(masa_temp,average);
    
    masa_pt[j]=average;
    emasa_pt[j]=std_dev;
  
  }

   
  for(int j=0; j<4; j++) cout<<pt[j]<<"  Mass (mu1)=" << masa_pt[j] <<"+-  "<<emasa_pt[j]<<" GeV "<<endl;
  
  return 0;
}


int makeFit_pol(){



  //POLE
  nbins=24;
  for (int i=0; i<100; i++) bin_size[i]=1.2/double(nbins);
  int scale=ScaleVarPole("CT18NLO",5);
  int scale2=ScaleVarPole2("CT18NLO");
  int pdf=PDFVarPole("CT18NLO",5);

  //Running
  //nbins=12;
  //for (int i=0; i<100; i++) bin_size[i]=1.2/double(nbins);
  //int scale=ScaleVarRun("CT18NLO",9);
  //int scale2=ScaleVarRun2("CT18NLO");

  return 0;
}


