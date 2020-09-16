#include "Sensitivity.h"

std::vector<double> CrossSectionPoint(TString pdf="CT10",TString energy="13TeV", int mass=170, TString pt="30", TString scheme="pole"){

  TString folder= "../../rootfiles/";
  //  if(scheme == "running" ) folder = "../../rootfiles/runningmass/";
  TString mt="_mt"+TString::Format("%i",mass);
  if(scheme == "running" ) "_mtrun"+TString::Format("%i",mass);

  TString title="n3_12_";
   //---------------------------------------------------------------------------------------------------------
  // pt30
  //read reference value + scale variations
  TString filename = folder+energy+"_"+pdf+mt+"_pt30_mu1.root";
  TGraphErrors *gref = readGraphNotNorm(filename,title+"pt"+pt);

  filename = folder+energy+"_"+pdf+mt+"_pt30_mu2.root";
  TGraphErrors *gref2 = readGraphNotNorm(filename,title+"pt"+pt);

  filename = folder+energy+"_"+pdf+mt+"_pt30_mu0.5.root";
  TGraphErrors *gref05 = readGraphNotNorm(filename,title+"pt"+pt);

  double integral = 0, integral2=0, integral05=0;

  Double_t *y=gref->GetY();
  Double_t *y2=gref2->GetY();
  Double_t *y05=gref05->GetY();

  for(int i=0; i<gref05->GetN(); i++) {
    integral += y[i];
    integral2 += y2[i];
    integral05 += y05[i];
    cout<<i<<" "<<y[i]<<" "<<integral<<endl;;
  }
  std::vector<double> result;
  result.push_back(integral);
  result.push_back(integral2);
  result.push_back(integral05);
  return result;

}

void CrossSection(TString pdf="CT10",TString energy="13TeV", int massstart=168, int interval=10, TString pt="30", TString scheme="pole"){


  double x[100], ex[100], y[100], y05[100], y2[100];
  int n=0;
  for(int i=massstart; i<massstart+interval+1; i++){
    x[i-massstart]=i;
    ex[i-massstart]=0;
    std::vector<double> value;
    value=CrossSectionPoint(pdf, energy, i , pt, scheme);
    y[i-massstart]=value.at(0);
    y2[i-massstart]=value.at(1);
    y05[i-massstart]=value.at(2);
    n++;
    //  cout<<x[i-massstart]<<" "<<y[i-massstart]<<" "<<y05[i-massstart]<<" "<<y2[i-massstart]<<endl;
  }

  TGraph *cross = new TGraph(n,x,y);
  TGraph *cross2 = new TGraph(n,x,y2);
  TGraph *cross05 = new TGraph(n,x,y05);

  TCanvas *canv1 = new TCanvas ("canvas","canvas",1000,800);

  
  canv1->cd();
  cross->GetYaxis()->SetTitle("cross section [fb]");
  cross->GetXaxis()->SetTitle("M_{t} [GeV]");
  if(scheme=="running")   cross->GetXaxis()->SetTitle("m_{t}(m_{t}) [GeV]");
                                                                                                                                             
  cross->GetYaxis()->SetLabelSize(0.04);
  cross->GetXaxis()->SetLabelSize(0.04);
  cross->SetLineColor(1);
  cross->SetLineStyle(1);
  cross->SetLineWidth(2);
  cross->SetMarkerColor(1);
  cross->SetMarkerSize(0.);
  cross->Draw("alp");

  cross2->SetLineColor(2);
  cross2->SetLineStyle(2);
  cross2->SetLineWidth(2);
  cross2->SetMarkerColor(2);
  cross2->SetMarkerSize(0.);
  cross2->Draw("lp");
 
  cross05->SetLineColor(4);
  cross05->SetLineStyle(2);
  cross05->SetLineWidth(2);
  cross05->SetMarkerColor(4);
  cross05->SetMarkerSize(0.);
  cross05->Draw("lp");

  TLegend *leg1 = new TLegend(0.55,0.7,0.9,0.9);//Variables
  leg1->SetHeader(energy +", "+pdf + ", p_{T}^{jet}>"+pt+" GeV");
  leg1->AddEntry(cross,"#mu=m","lpe");
  leg1->AddEntry(cross2,"#mu=m*2","lpe");
  leg1->AddEntry(cross05,"#mu=m/2","lpe");
  leg1->SetLineWidth(0);
  leg1->SetFillColor(0);
  leg1->SetShadowColor(0);
  leg1->Draw();


}
