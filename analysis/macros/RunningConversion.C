
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
#include "TGraphAsymmErrors.h"
#include "TH1F.h"
#include "TH1.h"
#include "TH2F.h"
#include "TImage.h"
#include "../include/R_LOderivative.h"


void Conversion(TString energy = "LHC13", TString pdf="CT10", TString distribution="n3_24_pt30",float mass=163,TString scale="1",float delta_m=0.5, TFile *f1=NULL, std::streambuf* osbuf = nullptr, bool write=true){

  TString mt=TString::Format("%.0f",mass);
  TString s_delta="05";
  if(delta_m==1.0) s_delta="1";
  if(delta_m==0.25) s_delta="025";
  
  // ---------------------------------------------------------------------------
  // R CONVERSION PART
  
  //1 Read the bin size, needed for th normnalization
  std::vector<double> width;
  cout<<"READ BINS "<<endl;
  width=width_bin(energy,pdf,distribution,mt,scale);

  std::vector<double> rho_s_v;
  cout<<"READ bins 2 "<<endl;
  rho_s_v=bin(energy,pdf,distribution,mt,scale);


  int nbins=width.size();

  double rho_s[100];
  for (int j=0; j<nbins; j++) rho_s[j]=rho_s_v.at(j);

  double erho_s[100];
  for (int j=0; j<nbins; j++) erho_s[j]=width.at(j);

  
  
  //Calculate the LO derivative using two points (+delta, -delta)
  std::vector<double> der;
  der=get_LOderivative_5p(energy,pdf,distribution+"_LO",mass,scale,delta_m);

  //2 Extract the NLO N3 distribution (not normalized) and the alpha_s value (over pi)
  std::vector<double> value_0;
  value_0=get_Distribution(energy,pdf,distribution+"_LO",mt,scale);//get only the LO contribution

  std::vector<double>  value_1;
  value_1=get_Distribution(energy,pdf,distribution,mt,scale);//get full NLO distribution
  
  //3 alpha s value
  double alphas;
  alphas=as(energy,pdf,mt,scale);
  
  // 4 Make the conversion
  double cross_running[100];
  double cross_pole[100];
  double cross_pole_LO[100];

  double ecross_running[100];
  double ecross_pole[100];
  // rhos values, are fixed

  
  double integral_running=0;// inclusive cross section in the running mass scheme
  double integral_pole=0;// inclusive cross section in the pole mass scheme

  // we apply the poor's man conversion to the running mass scheme
  for(int i=0; i< nbins ; i++) {

    
    cross_running[i] = value_1[2*i] +
      alphas*  der[2*i]  * mass *4/3;

    ecross_running[i] = sqrt( pow(value_1[2*i+1],2) + pow(alphas*  der[2*i+1]  * mass *4/3 , 2) );
    
    integral_running+=cross_running[i];
     
    cross_pole_LO[i] = value_0[2*i];
    cross_pole[i] = value_1[2*i];
    ecross_pole[i] = value_1[2*i+1];

    integral_pole+=cross_pole[i];
  }


  // ---------------------------------------------------------------------------
  // SAVING ROOT OBJECTS PART
  // the non normalized N3 distribution
  TGraphErrors * N3_pole = new TGraphErrors(nbins,rho_s,cross_pole,erho_s,ecross_pole);
  TGraphErrors * N3 = new TGraphErrors(nbins,rho_s,cross_running,erho_s,ecross_running);
  
  if(write == true) {

    std::ostream fout(osbuf? osbuf : std::cout.rdbuf());
    
    // WRITTING FILES
    f1->cd();
    TKey *key = f1->FindKey("alphas_over_pi");
    if (key == 0)  {
      TVectorD a(1);
      a[0] =alphas;
      a.Write("alphas_over_pi");

      fout<< "## Pole to running top mass conversion routine for:"<<endl;
      fout<<"# m(m)="<<mt<<" GeV"<<endl;
      fout<<"# deltamass="<<delta_m<< " GeV"<<endl;
      fout<<"# scale_factor= "<<scale<<endl;
      fout<< "# PDF: "<<pdf<<endl;
      fout<< "# alphas_over_pi = "<<alphas<<endl;
      fout<<"## INFO: bin_center, bin_width, derivative_Distribution_pole_LO, Distribution_pole_LO, Distribution_pole_NLO, Distribution_running_NLO"<<endl;

    }

    N3->SetName(distribution);
    N3->SetTitle(distribution);
    N3->Write();

    fout<< "# HISTONAME: "<<distribution<<endl;
    fout<< "# nbins: "<<nbins<<endl;
    
    for(int i=0; i< nbins ; i++) 
      fout<<rho_s_v[i]<<" "<< width[i]<<" "<< der[2*i]<<" "<<cross_pole_LO[i]<<" "<<cross_pole[i]<<" "<<cross_running[i]<<endl;
  }

  

}


void RunningConversion() {

  TString energy="LHC13";
  TString pdf="CT10";

  for(int j=157; j<170; j++) {
    
    double mass=double(j);

    for(int k=0; k<3; k++){

      TString scale="1";
      if(k==1) scale="0.5";
      if(k==2) scale="2";
      string hnames[] = {"n3_ATLAS7TeV_pt30","n3_ATLAS7TeV_pt50","n3_ATLAS7TeV_pt75","n3_ATLAS7TeV_pt100","n3_ATLAS8TeV_pt30","n3_ATLAS8TeV_pt50","n3_ATLAS8TeV_pt75","n3_ATLAS8TeV_pt100","n3_12_pt30","n3_12_pt50","n3_12_pt75","n3_12_pt100","n3_24_pt30","n3_24_pt50","n3_24_pt75","n3_24_pt100"};
      
      TString outputfile = "../../rootfiles/"+energy+"_"+pdf+"_mtrun"+TString::Format("%.0f",mass)+"_pt30_mu"+scale+".root";
      TFile *f1 = new  TFile;
      f1 = new  TFile(outputfile,"RECREATE");
      cout<<outputfile<<endl;


      ofstream fout ("../../logfiles/"+energy+"_"+pdf+"_mtrun"+TString::Format("%.0f",mass)+"_pt30_mu"+scale+".log");
      for (unsigned i = 0; i<sizeof(hnames)/sizeof(string); i++){
	cout<<" hnames "<<hnames[i]<<endl;
	Conversion("LHC13","CT10",TString(hnames[i]),mass,scale,0.5, f1,fout.rdbuf(),true);
      }
    }

  }
}

