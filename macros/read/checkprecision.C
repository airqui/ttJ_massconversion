#include "string.h"
#include <iostream>
#include <fstream>
#include "TH1F.h"
#include "TNtuple.h"
#include "TLorentzVector.h"
#include "TFile.h"
#include "TMath.h"
#include "TClass.h"
#include "TROOT.h"
#include "TCanvas.h"
#include "TGraphErrors.h"
#include "TLegend.h"
#include "TString.h"
#include "../include/samples.h"
#include <vector>

using namespace std;

void checkprecision() {

  int jmin=0;
  int jmax=24;//jmin+1;

  TString file_pdf="CT10";
  TString file_energy="7TeV";
  TString file_mass="mt166";
  TString file_scale;
  TString file_kt="kt50";
  TString file_prefix;



  double alphasNLO=0;   
  double alphasNLO_NEW=0;

  double bin_eta= 0.6;//x_eta_t[1]-x_eta_t[0];
  double bin_pt= 50;//x_pt_t[1]-x_pt_t[0];
  double bin_e= 50;//x_pt_t[1]-x_pt_t[0];
  double bin_ms= 0.1;//x_pt_t[1]-x_pt_t[0];

  double bin_ms_ATLAS[6];//x_pt_t[1]-x_pt_t[0];

  bin_ms_ATLAS[0]=0.25;
  bin_ms_ATLAS[1]=0.075;
  bin_ms_ATLAS[2]=0.1;
  bin_ms_ATLAS[3]=0.1;
  bin_ms_ATLAS[4]=0.15;
  bin_ms_ATLAS[5]=0.325;

   
  //#########################################################################################################
  //#
  //#              Definir variables
  //#
  //#########################################################################################################
   double x_eta[20];
    double y_eta_t[20], e_eta_t[20];
    double y_eta_tb[20], e_eta_tb[20];
    double y_eta_ttb[20], e_eta_ttb[20];
    double y_eta_ttbj[20], e_eta_ttbj[20];
    double y_eta_g[20], e_eta_g[20];

    double x_pt[20];
    double y_pt_t[20], e_pt_t[20];
    double y_pt_tb[20], e_pt_tb[20];
    double y_pt_ttb[20], e_pt_ttb[20];
    double y_pt_ttbj[20], e_pt_ttbj[20];
    double y_pt_g[20], e_pt_g[20];

    double x_e[40];
    double y_e_t[40], e_e_t[40];
    double y_e_tb[40], e_e_tb[40];
    double y_e_ttb[40], e_e_ttb[40];
    double y_e_ttbj[40], e_e_ttbj[40];
    double y_e_g[40], e_e_g[40];


    for(int i=0; i<20; i++) { 
      x_eta[i]=0.;
      y_eta_t[i]=0.; e_eta_t[i]=0.;
      y_eta_g[i]=0.; e_eta_g[i]=0.;
      y_eta_tb[i]=0.; e_eta_tb[i]=0.;
      y_eta_ttb[i]=0.; e_eta_ttb[i]=0.;
      y_eta_ttbj[i]=0.; e_eta_ttbj[i]=0.;

      x_pt[i]=0.;
      y_pt_t[i]=0.; e_pt_t[i]=0.;
      y_pt_g[i]=0.; e_pt_g[i]=0.;
      y_pt_tb[i]=0.; e_pt_tb[i]=0.;
      y_pt_ttb[i]=0.; e_pt_ttb[i]=0.;
      y_pt_ttbj[i]=0.; e_pt_ttbj[i]=0.;
    }


    for(int i=0; i<40; i++) { 
      x_e[i]=0.;
      y_e_t[i]=0.; e_e_t[i]=0.;
      y_e_g[i]=0.; e_e_g[i]=0.;
      y_e_tb[i]=0.; e_e_tb[i]=0.;
      y_e_ttb[i]=0.; e_e_ttb[i]=0.;
      y_e_ttbj[i]=0.; e_e_ttbj[i]=0.;
    }

    double x_ms_12[12];
    double y_n3_kt50_12[12], e_n3_kt50_12[12];
    double y_n3LO_kt50_12[12], e_n3LO_kt50_12[12];
    double y_n3NLO_kt50_12[12], e_n3NLO_kt50_12[12];

    double y_n3ttbar_kt50_12[12], e_n3ttbar_kt50_12[12];


    for(int i=0; i<12; i++) {  
      x_ms_12[i]=0; 
      y_n3_kt50_12[i]=0., e_n3_kt50_12[i]=0.;
      y_n3LO_kt50_12[i]=0., e_n3LO_kt50_12[i]=0.;
      y_n3NLO_kt50_12[i]=0., e_n3NLO_kt50_12[i]=0.;
      y_n3ttbar_kt50_12[i]=0., e_n3ttbar_kt50_12[i]=0.;
    }

    double x_ms_24[24];
    double y_n3_kt50_24[24], e_n3_kt50_24[24];
    double y_n3LO_kt50_24[24], e_n3LO_kt50_24[24];
    double y_n3NLO_kt50_24[24], e_n3NLO_kt50_24[24];
    double y_n3ttbar_kt50_24[24], e_n3ttbar_kt50_24[24];

    for(int i=0; i<24; i++) {  
      x_ms_24[i]=0; 
      y_n3_kt50_24[i]=0., e_n3_kt50_24[i]=0.;
      y_n3LO_kt50_24[i]=0., e_n3LO_kt50_24[i]=0.;
      y_n3NLO_kt50_24[i]=0., e_n3NLO_kt50_24[i]=0.;
      y_n3ttbar_kt50_24[i]=0., e_n3ttbar_kt50_24[i]=0.;
    }

  double x_ms_ATLAS[6];
  double y_n3_ATLAS[6], e_n3_ATLAS[6];
  double y_n3LO_ATLAS[6], e_n3LO_ATLAS[6];
  double y_n3NLO_ATLAS[6], e_n3NLO_ATLAS[6];
  double y_n3ttbar_ATLAS[6], e_n3ttbar_ATLAS[6];

  for(int i=0; i<6; i++) {  
    x_ms_ATLAS[i]=0; 
    y_n3_ATLAS[i]=0., e_n3_ATLAS[i]=0.;
    y_n3LO_ATLAS[i]=0., e_n3LO_ATLAS[i]=0.;
    y_n3NLO_ATLAS[i]=0., e_n3NLO_ATLAS[i]=0.;
    y_n3ttbar_ATLAS[i]=0., e_n3ttbar_ATLAS[i]=0.;
  }


  double tempcross=0, errortempcross=0;
  double cross=0, errorcross=0;
  double crossLO=0, errorcrossLO=0;
  double crossNLO=0, errorcrossNLO=0;


  //#########################################################################################################
  //#########################################################################################################
  //#########################################################################################################
  //#########################################################################################################

  TCanvas *canv1 = new TCanvas (file_energy+"_"+file_mass+"_"+file_scale+" error R, processes",file_energy+"_"+file_mass+"_"+file_scale+" error R, processes",1200,800);
  canv1->Divide(4,6);

  TCanvas *canv2 = new TCanvas (file_energy+"_"+file_mass+"_"+file_scale+" Relative error R, processes",file_energy+"_"+file_mass+"_"+file_scale+" Relative error R, processes",1200,800);
  canv2->Divide(4,6);

  //TCanvas *canv4 = new TCanvas (file_energy+"_"+file_mass+"_"+file_scale+" Error contribution by processes",file_energy+"_"+file_mass+"_"+file_scale+" Error contribution by processes",1200,800);
  //canv4->Divide(4,6);



  // TCanvas *canv3 = new TCanvas (file_energy+"_"+file_mass+"_"+file_scale+" Error total",file_energy+"_"+file_mass+"_"+file_scale+" Error total",1200,800);
  //canv3->Divide(2,1);

  // TCanvas *canv2 = new TCanvas (file_energy+"_"+file_mass+"_"+file_scale+" error R, total",file_energy+"_"+file_mass+"_"+file_scale+" error R, total",1200,800);


  ofstream fout ("../../logfiles/precision_"+file_pdf+"_"+file_energy+"_"+file_mass+"_"+file_kt+"_NLO.out");
  fout<<" "<<endl;
  fout<<" "<<endl;
  fout<<"//######################################################################################################### "<<endl;
  fout<<"   ANALYSIS OF:  "<<file_pdf+file_energy+"_"+file_mass+"_"+file_scale+"_"+file_kt+"_NLO.root"<<endl;
  fout<<"//######################################################################################################### "<<endl;
  fout<<" "<<endl;
  fout<<" "<<endl;

  TGraphErrors *gerrorrel_total = new TGraphErrors();
  TGraphErrors *gerror_total = new TGraphErrors();
  double error_total[6];
  double errorrel_total[6];

  for(int kscale=0; kscale<3; kscale++) {

    for(int i=0; i<6; i++) {
      error_total[i]= 0;
      errorrel_total[i]= 0;
    }

    if(kscale==0) file_scale="mu1";
    if(kscale==1) file_scale="mu05";
    if(kscale==2) file_scale="mu2";

    file_prefix="";
    TString outputfile="../../rootfiles/"+file_pdf+"_"+file_energy+"_"+file_mass+"_"+file_scale+"_"+file_kt+"_NLO.root";


    cout<<"output file: "<<outputfile<<endl;
    cout<<"output log:  "<<"../../logfiles/"+file_pdf+"_"+file_energy+"_"+file_mass+"_"+file_scale+"_"+file_kt+"_NLO.out"<<endl;
    std::vector<TString> file_string_;
    file_string_=samples(file_mass, file_pdf, file_scale);

    TString string_file;

    for(int j=jmin ; j<jmax; j++) {

      ifstream file;
      TString process;
      string_file=file_string_[j];
  
      string_file= file_prefix + string_file +".out";
      file.open(string_file);

      cout<<string_file<<endl;
      //return;

      double count_eta_t=0, count_eta_tb=0, count_eta_g=0, count_eta_ttb=0,count_eta_ttbj=0;
      double count_e_t=0, count_e_tb=0, count_e_g=0, count_e_ttb=0,count_e_ttbj=0;
      double count_pt_t=0, count_pt_tb=0, count_pt_g=0, count_pt_ttb=0,count_pt_ttbj=0;

      double count_n3_kt50=0, count_n3ttbar_kt50=0;
      double count_n3_kt50_12=0, count_n3ttbar_kt50_12=0;
      double count_n3_ATLAS=0, count_n3ttbar_ATLAS=0;

      //#########################################################################################################
      //#########################################################################################################

      //          LEER

      //#########################################################################################################
      //#########################################################################################################

      string store_yt;
      string store_stop;
      string s1, s2;
      bool first=true;
      bool bool_leer=false;

      double factor=1.;
      if(j==12) factor=5.;
      if(j==16) factor=4.;
      if( j != 12 && j != 16) factor=1;


      if (file )  // abro el listado

	{
	  while (!file.eof() && store_stop.find("..done.") > 0 ) {
	    file >> store_yt;
	    if(store_yt.find("./main.exe") == 0) { 
	      string s1,s2,s3,s4,s5,s6,s7,s8,s9,s10,s11,s12;
	      file >>s1>>s2>>s3>>s4>>s5>>s6>>s7>>s8>>s9>>s10>>s11>>s12;
	      fout<< "file number " <<j<<endl;
	      fout<<"File name: "<< string_file<<endl;
	      fout<<"settings on the simulation: "<<endl;
	      fout<<store_yt<<"  "<< s1 <<" "<< s2 <<" "<< s3 <<" "<< s4 <<" "<< s5 <<" "<< s6 <<" "<< s7 <<" "<< s8<<" "<< s9<<" "<<s10<< " "<<s11<<" "<<s12<< endl;
	    }

	    if(store_yt.find("alphasNLO") == 0 ) { 
	      string equal;
	      double temp_alpha;
	      file >> equal >> temp_alpha;
	      fout<<store_yt<<"  "<< temp_alpha <<endl;
	      alphasNLO=temp_alpha;
	      if(alphasNLO_NEW==0) alphasNLO_NEW=alphasNLO;
	    }

	    if(store_yt.find("LHAPDF:") == 0 && first==true) { 
	      string pdf;
	      file >> pdf;
	      fout<<store_yt<<"  "<< pdf <<endl;
	      first=false;
	    }

	    if(store_yt.find("elapsed") == 0) { 
	      double time;
	      file >> time;
	      fout<<"Total time of calc: "<<time/(3600.*24)<<" d"<<endl;
	    }

	    if(store_yt.find("ACCUMULATED") == 0) { 
	      string results, integral, integral2;
	      tempcross=0.;
	      int n;
	      n++;
	      file >> results >> integral >> integral2>>tempcross;
	      file >> results >> results >> results >> results >> errortempcross;
	    }

	    if(store_yt.find("Final") == 0) bool_leer=true;
	    string s1,s2,s3,s4,s5,s6,s7,s8,s9,s10;
 
	    if(store_yt.find("DATASTART") == 0 && bool_leer==true) { 
	      file >> s1 >> s2 >> s3;
	      file >> s1 >> s2;
	      file >> s1 >> s2;
	      file >> s3 >> s4 >> s5 >> s6 >> s7;
	    }
	    //-----------------------------------------------------
	    // guardo eta top
	    if(s2=="eta_t") {
	      count_eta_t++;
	      if(count_eta_t>0){
		for(int i=0; i<20; i++) {	
		  double d1=0., d2=0., d3=0;
		  file >> d1 >> d2 >> d3;
		  x_eta[i]=d1;
		  y_eta_t[i]+=bin_eta*factor*d2;
		  e_eta_t[i]+=pow(bin_eta*factor*d3,2);
		}
	      }
	      file >> s1 >> s2;
	      file >> s3 >> s4 >> s5 >> s6;
	      file >> s1 >> s2;

	      file >> s1 >> s2 >> s3;
	      file >> s1 >> s2;
	      file >> s1 >> s2;
	      file >> s3 >> s4 >> s5 >> s6 >> s7;
	    }

	    //-----------------------------------------------------
	    //-----------------------------------------------------
	    // guardo eta top
	    if(s2=="eta_g") {
	      count_eta_g++;
	      if(count_eta_g>0){
		for(int i=0; i<20; i++) {	
		  double d1=0., d2=0., d3=0;
		  file >> d1 >> d2 >> d3;
		  y_eta_g[i]+=bin_eta*factor*d2;
		  e_eta_g[i]+=pow(bin_eta*factor*d3,2);
		}
	      }
		
	      file >> s1 >> s2;
	      file >> s3 >> s4 >> s5 >> s6;
	      file >> s1 >> s2;

	      file >> s1 >> s2 >> s3;
	      file >> s1 >> s2;
	      file >> s1 >> s2;
	      file >> s3 >> s4 >> s5 >> s6 >> s7;
	    } 

	    //-----------------------------------------------------
	    //-----------------------------------------------------
	    // guardo eta top
	    if(s2=="eta_tb") {
	      count_eta_tb++;
	      if(count_eta_tb>0){
		for(int i=0; i<20; i++) {	
		  double d1=0., d2=0., d3=0;
		  file >> d1 >> d2 >> d3;
		  y_eta_tb[i]+=bin_eta*factor*d2;
		  e_eta_tb[i]+=pow(bin_eta*factor*d3,2);
		}
	      }
	      file >> s1 >> s2;
	      file >> s3 >> s4 >> s5 >> s6;
	      file >> s1 >> s2;

	      file >> s1 >> s2 >> s3;
	      file >> s1 >> s2;
	      file >> s1 >> s2;
	      file >> s3 >> s4 >> s5 >> s6 >> s7;
	    }
	    //-----------------------------------------------------
	    //-----------------------------------------------------

	    //-----------------------------------------------------
	    //-----------------------------------------------------
	    // guardo eta top
	    if(s2=="eta_ttb") {
	      count_eta_ttb++;
	      if(count_eta_ttb>0){
		for(int i=0; i<20; i++) {	
		  double d1=0., d2=0., d3=0;
		  file >> d1 >> d2 >> d3;
		  y_eta_ttb[i]+=bin_eta*factor*d2;
		  e_eta_ttb[i]+=pow(bin_eta*factor*d3,2);
		}
	      }
	      file >> s1 >> s2;
	      file >> s3 >> s4 >> s5 >> s6;
	      file >> s1 >> s2;

	      file >> s1 >> s2 >> s3;
	      file >> s1 >> s2;
	      file >> s1 >> s2;
	      file >> s3 >> s4 >> s5 >> s6 >> s7;
	    }
	    //-----------------------------------------------------
	    //-----------------------------------------------------

	    //-----------------------------------------------------
	    //-----------------------------------------------------
	    // guardo eta ttb+jet
	    if(s2=="eta_ttbj") {
	      count_eta_ttbj++;
	      if(count_eta_ttbj>0){
		for(int i=0; i<20; i++) {	
		  double d1=0., d2=0., d3=0;
		  file >> d1 >> d2 >> d3;
		  y_eta_ttbj[i]+=bin_eta*factor*d2;
		  e_eta_ttbj[i]+=pow(bin_eta*factor*d3,2);
		}
	      }
	      file >> s1 >> s2;
	      file >> s3 >> s4 >> s5 >> s6;
	      file >> s1 >> s2;

	      file >> s1 >> s2 >> s3;
	      file >> s1 >> s2;
	      file >> s1 >> s2;
	      file >> s3 >> s4 >> s5 >> s6 >> s7;
	    }
	    //-----------------------------------------------------

	    // guardo pt top
	    if(s2=="pt_t") {
	      count_pt_t++;
	      if(count_pt_t>0){
		for(int i=0; i<20; i++) {	
		  double d1=0., d2=0., d3=0;
		  file >> d1 >> d2 >> d3;
		  x_pt[i]=d1;
		  y_pt_t[i]+=bin_pt*factor*d2;
		  e_pt_t[i]+=pow(bin_pt*factor*d3,2);
		}
	      }
	      file >> s1 >> s2;
	      file >> s3 >> s4 >> s5 >> s6;
	      file >> s1 >> s2;

	      file >> s1 >> s2 >> s3;
	      file >> s1 >> s2;
	      file >> s1 >> s2;
	      file >> s3 >> s4 >> s5 >> s6 >> s7;
	    }

	    //-----------------------------------------------------
	    //-----------------------------------------------------
	    // guardo pt top
	    if(s2=="pt_g") {
	      count_pt_g++;
	      if(count_pt_g>0){
		for(int i=0; i<20; i++) {	
		  double d1=0., d2=0., d3=0;
		  file >> d1 >> d2 >> d3;
		  y_pt_g[i]+=bin_pt*factor*d2;
		  e_pt_g[i]+=pow(bin_pt*factor*d3,2);
		}
	      }
		
	      file >> s1 >> s2;
	      file >> s3 >> s4 >> s5 >> s6;
	      file >> s1 >> s2;

	      file >> s1 >> s2 >> s3;
	      file >> s1 >> s2;
	      file >> s1 >> s2;
	      file >> s3 >> s4 >> s5 >> s6 >> s7;
	    } 

	    //-----------------------------------------------------
	    //-----------------------------------------------------
	    // guardo pt top
	    if(s2=="pt_tb") {
	      count_pt_tb++;
	      if(count_pt_tb>0){
		for(int i=0; i<20; i++) {	
		  double d1=0., d2=0., d3=0;
		  file >> d1 >> d2 >> d3;
		  y_pt_tb[i]+=bin_pt*factor*d2;
		  e_pt_tb[i]+=pow(bin_pt*factor*d3,2);
		}
	      }
	      file >> s1 >> s2;
	      file >> s3 >> s4 >> s5 >> s6;
	      file >> s1 >> s2;

	      file >> s1 >> s2 >> s3;
	      file >> s1 >> s2;
	      file >> s1 >> s2;
	      file >> s3 >> s4 >> s5 >> s6 >> s7;
	    }
	    //-----------------------------------------------------
	    //-----------------------------------------------------

	    //-----------------------------------------------------
	    //-----------------------------------------------------
	    // guardo pt top
	    if(s2=="pt_ttb") {
	      count_pt_ttb++;
	      if(count_pt_ttb>0){
		for(int i=0; i<20; i++) {	
		  double d1=0., d2=0., d3=0;
		  file >> d1 >> d2 >> d3;
		  y_pt_ttb[i]+=bin_pt*factor*d2;
		  e_pt_ttb[i]+=pow(bin_pt*factor*d3,2);
		}
	      }
	      file >> s1 >> s2;
	      file >> s3 >> s4 >> s5 >> s6;
	      file >> s1 >> s2;

	      file >> s1 >> s2 >> s3;
	      file >> s1 >> s2;
	      file >> s1 >> s2;
	      file >> s3 >> s4 >> s5 >> s6 >> s7;
	    }
	    //-----------------------------------------------------
	    //-----------------------------------------------------

	    //-----------------------------------------------------
	    //-----------------------------------------------------
	    // guardo pt ttb+jet
	    if(s2=="pt_ttbj") {
	      count_pt_ttbj++;
	      if(count_pt_ttbj>0){
		for(int i=0; i<20; i++) {	
		  double d1=0., d2=0., d3=0;
		  file >> d1 >> d2 >> d3;
		  y_pt_ttbj[i]+=bin_pt*factor*d2;
		  e_pt_ttbj[i]+=pow(bin_pt*factor*d3,2);
		}
	      }
	      file >> s1 >> s2;
	      file >> s3 >> s4 >> s5 >> s6;
	      file >> s1 >> s2;

	      file >> s1 >> s2 >> s3;
	      file >> s1 >> s2;
	      file >> s1 >> s2;
	      file >> s3 >> s4 >> s5 >> s6 >> s7;
	    }

	    //-----------------------------------------------------
	    // guardo e top
	    if(s2=="e_t") {
	      count_e_t++;
	      if(count_e_t>0){
		for(int i=0; i<40; i++) {	
		  double d1=0., d2=0., d3=0;
		  file >> d1 >> d2 >> d3;
		  x_e[i]=d1;
		  y_e_t[i]+=bin_e*factor*d2;
		  e_e_t[i]+=pow(bin_e*factor*d3,2);
		}
	      }
	      file >> s1 >> s2;
	      file >> s3 >> s4 >> s5 >> s6;
	      file >> s1 >> s2;

	      file >> s1 >> s2 >> s3;
	      file >> s1 >> s2;
	      file >> s1 >> s2;
	      file >> s3 >> s4 >> s5 >> s6 >> s7;
	    }

	    //-----------------------------------------------------
	    //-----------------------------------------------------
	    // guardo e top
	    if(s2=="e_g") {
	      count_e_g++;
	      if(count_e_g>0){
		for(int i=0; i<40; i++) {	
		  double d1=0., d2=0., d3=0;
		  file >> d1 >> d2 >> d3;
		  y_e_g[i]+=bin_e*factor*d2;
		  e_e_g[i]+=pow(bin_e*factor*d3,2);
		}
	      }
		
	      file >> s1 >> s2;
	      file >> s3 >> s4 >> s5 >> s6;
	      file >> s1 >> s2;

	      file >> s1 >> s2 >> s3;
	      file >> s1 >> s2;
	      file >> s1 >> s2;
	      file >> s3 >> s4 >> s5 >> s6 >> s7;
	    } 

	    //-----------------------------------------------------
	    //-----------------------------------------------------
	    // guardo e top
	    if(s2=="e_tb") {
	      count_e_tb++;
	      if(count_e_tb>0){
		for(int i=0; i<40; i++) {	
		  double d1=0., d2=0., d3=0;
		  file >> d1 >> d2 >> d3;
		  y_e_tb[i]+=bin_e*factor*d2;
		  e_e_tb[i]+=pow(bin_e*factor*d3,2);
		}
	      }
	      file >> s1 >> s2;
	      file >> s3 >> s4 >> s5 >> s6;
	      file >> s1 >> s2;

	      file >> s1 >> s2 >> s3;
	      file >> s1 >> s2;
	      file >> s1 >> s2;
	      file >> s3 >> s4 >> s5 >> s6 >> s7;
	    }
	    //-----------------------------------------------------
	    //-----------------------------------------------------

	    //-----------------------------------------------------
	    //-----------------------------------------------------
	    // guardo e top
	    if(s2=="e_ttb") {
	      count_e_ttb++;
	      if(count_e_ttb>0){
		for(int i=0; i<40; i++) {	
		  double d1=0., d2=0., d3=0;
		  file >> d1 >> d2 >> d3;
		  y_e_ttb[i]+=bin_e*factor*d2;
		  e_e_ttb[i]+=pow(bin_e*factor*d3,2);
		}
	      }
	      file >> s1 >> s2;
	      file >> s3 >> s4 >> s5 >> s6;
	      file >> s1 >> s2;

	      file >> s1 >> s2 >> s3;
	      file >> s1 >> s2;
	      file >> s1 >> s2;
	      file >> s3 >> s4 >> s5 >> s6 >> s7;
	    }
	    //-----------------------------------------------------
	    //-----------------------------------------------------

	    //-----------------------------------------------------
	    //-----------------------------------------------------
	    // guardo e ttb+jet
	    if(s2=="e_ttbj") {
	      count_e_ttbj++;
	      if(count_e_ttbj>0){
		for(int i=0; i<40; i++) {	
		  double d1=0., d2=0., d3=0;
		  file >> d1 >> d2 >> d3;
		  y_e_ttbj[i]+=bin_e*factor*d2;
		  e_e_ttbj[i]+=pow(bin_e*factor*d3,2);
		}
	      }
	      file >> s1 >> s2;
	      file >> s3 >> s4 >> s5 >> s6;
	      file >> s1 >> s2;

	      file >> s1 >> s2 >> s3;
	      file >> s1 >> s2;
	      file >> s1 >> s2;
	      file >> s3 >> s4 >> s5 >> s6 >> s7;
	    }
	  
	    //-----------------------------------------------------
	    //-----------------------------------------------------
	    // n3 binning de 12
	    if(s2=="n3_12") {
	      count_n3_kt50_12++;
	      if(count_n3_kt50_12>0){
		for(int i=0; i<12; i++) {	
		  double d1=0., d2=0., d3=0;
		  file >> d1 >> d2 >> d3;
		  x_ms_12[i]=d1;
		  y_n3_kt50_12[i]+=bin_ms*factor*d2;
		  e_n3_kt50_12[i]+=pow(bin_ms*factor*d3,2);

		  if(j<4) {
		    y_n3LO_kt50_12[i]+=bin_ms*factor*d2;
		    e_n3LO_kt50_12[i]+=pow(bin_ms*factor*d3,2);
		  }else {
		    y_n3NLO_kt50_12[i]+=bin_ms*factor*d2;
		    e_n3NLO_kt50_12[i]+=pow(bin_ms*factor*d3,2);
		  }

		}
	      }
	      
	      file >> s1 >> s2;
	      file >> s3 >> s4 >> s5 >> s6;
	      file >> s1 >> s2;

	      file >> s1 >> s2 >> s3;
	      file >> s1 >> s2;
	      file >> s1 >> s2;
	      file >> s3 >> s4 >> s5 >> s6 >> s7;
	    }
	    //-----------------------------------------------------
	    //-----------------------------------------------------
	    //-----------------------------------------------------
	    // n3ttbar binning de 12
	    if(s2=="n3ttbar_12") {
	      count_n3ttbar_kt50_12++;
	      if(count_n3ttbar_kt50_12>0){
		for(int i=0; i<12; i++) {	
		  double d1=0., d2=0., d3=0;
		  file >> d1 >> d2 >> d3;
		  y_n3ttbar_kt50_12[i]+=bin_ms*factor*d2;
		  e_n3ttbar_kt50_12[i]+=pow(bin_ms*factor*d3,2);
		}
	      }
	      file >> s1 >> s2;
	      file >> s3 >> s4 >> s5 >> s6;
	      file >> s1 >> s2;

	      file >> s1 >> s2 >> s3;
	      file >> s1 >> s2;
	      file >> s1 >> s2;
	      file >> s3 >> s4 >> s5 >> s6 >> s7;
	    }
	    //-----------------------------------------------------
	    // n3 binning de 24
	    if(s2=="n3_24") {
	      count_n3_kt50++;
	      if(count_n3_kt50>0){
		for(int i=0; i<24; i++) {	
		  double d1=0., d2=0., d3=0;
		  file >> d1 >> d2 >> d3;
		  x_ms_24[i]=d1;
		  y_n3_kt50_24[i]+=bin_ms*0.5*factor*d2;
		  e_n3_kt50_24[i]+=pow(bin_ms*0.5*factor*d3,2);

		  if(j<4) {
		    y_n3LO_kt50_24[i]+=bin_ms*0.5*factor*d2;
		    e_n3LO_kt50_24[i]+=pow(bin_ms*0.5*factor*d3,2);
		  }else {
		    y_n3NLO_kt50_24[i]+=bin_ms*0.5*factor*d2;
		    e_n3NLO_kt50_24[i]+=pow(bin_ms*0.5*factor*d3,2);
		  }

		}
	      }
	      file >> s1 >> s2;
	      file >> s3 >> s4 >> s5 >> s6;
	      file >> s1 >> s2;

	      file >> s1 >> s2 >> s3;
	      file >> s1 >> s2;
	      file >> s1 >> s2;
	      file >> s3 >> s4 >> s5 >> s6 >> s7;
	    }
	    //-----------------------------------------------------
	    //-----------------------------------------------------
	    // n3ttbar binning de 24
	    if(s2=="n3ttbar_24") {
	      count_n3ttbar_kt50++;
	      if(count_n3ttbar_kt50>0){
		for(int i=0; i<24; i++) {	
		  double d1=0., d2=0., d3=0;
		  file >> d1 >> d2 >> d3;
		  y_n3ttbar_kt50_24[i]+=bin_ms*0.5*factor*d2;
		  e_n3ttbar_kt50_24[i]+=pow(bin_ms*0.5*factor*d3,2);
		}
	      }
	      file >> s1 >> s2;
	      file >> s3 >> s4 >> s5 >> s6;
	      file >> s1 >> s2;

	      file >> s1 >> s2 >> s3;
	      file >> s1 >> s2;
	      file >> s1 >> s2;
	      file >> s3 >> s4 >> s5 >> s6 >> s7;
	    }
	    //-----------------------------------------------------
	    //-----------------------------------------------------
	    //-----------------------------------------------------
	    // n3 binning de 6_opt
	    if(s2=="n3_6_opt") {
	      count_n3_ATLAS++;
	      if(count_n3_ATLAS>0){
		for(int i=0; i<6; i++) {	
		  double d1=0., d2=0., d3=0;
		  file >> d1 >> d2 >> d3;
		  x_ms_ATLAS[i]=d1;
		  y_n3_ATLAS[i]=bin_ms_ATLAS[i]*factor*d2;
		  e_n3_ATLAS[i]=pow(bin_ms_ATLAS[i]*factor*d3,2);
		  if(j<4) {
		    y_n3LO_ATLAS[i]=bin_ms_ATLAS[i]*factor*d2;
		    e_n3LO_ATLAS[i]=pow(bin_ms_ATLAS[i]*factor*d3,2);
		  }else {
		    y_n3NLO_ATLAS[i]=bin_ms_ATLAS[i]*factor*d2;
		    e_n3NLO_ATLAS[i]=pow(bin_ms_ATLAS[i]*factor*d3,2);
		  }

		}
	      }
	      file >> s1 >> s2;
	      file >> s3 >> s4 >> s5 >> s6;
	      file >> s1 >> s2;

	      file >> s1 >> s2 >> s3;
	      file >> s1 >> s2;
	      file >> s1 >> s2;
	      file >> s3 >> s4 >> s5 >> s6 >> s7;
	    }
	 

	  }//while
	}// if file


      cross+=factor*tempcross;
      errorcross+=factor*factor*errortempcross*errortempcross;


      fout<< "Calculated Process Cross-Section = "<<factor*tempcross<<" +- "<<factor*sqrt(errortempcross)<<endl;
      if(j<4) {
	fout<< "LO  contribution" <<endl;
	crossLO+=factor*tempcross;
	errorcrossLO+=factor*factor*errortempcross*errortempcross;
      } else {
	fout<< "NLO  contribution" <<endl;
	crossNLO+=factor*tempcross;
	errorcrossNLO+=factor*factor*errortempcross*errortempcross;
      }
      fout<<" "<<endl;

      //*************************************************************************************************************************************************************************
      // R 6 ATLAS
      //-----------------------------------------------------------------------------
      TGraphErrors *gerrorrel_ATLAS = new TGraphErrors();
      TGraphErrors *gerrorrel2_ATLAS = new TGraphErrors();
      TGraphErrors *gerror_ATLAS = new TGraphErrors();
      double errordivy[6];
      double e_x_ms_ATLAS[6];
      double error_scale[6];

      if(kscale==0) {
	error_scale[0]=7.22362e-05;
	error_scale[1]=0.000317179;
	error_scale[2]=0.000863475;
	error_scale[3]=0.00136778;
	error_scale[4]=0.00205781;
	error_scale[5]=0.000899194;
      }
      if(kscale==1) {
	error_scale[0]=0.000221128;
	error_scale[1]=0.000870391;
	error_scale[2]=0.00271859;
	error_scale[3]=0.00488142;
	error_scale[4]=0.00640075;
	error_scale[5]=0.00291341;
      }

      if(kscale==2) {
	error_scale[0]=0.000221128;
	error_scale[1]=0.000870391;
	error_scale[2]=0.00271859;
	error_scale[3]=0.00488142;
	error_scale[4]=0.00640075;
	error_scale[5]=0.00291341;
      }

      for(int i=0; i<6; i++) {
	e_x_ms_ATLAS[i]= bin_ms_ATLAS[i]/2.;
	errordivy[i]=fabs(e_n3_ATLAS[i]/y_n3_ATLAS[i]);

	error_scale[i]=e_n3_ATLAS[i]/error_scale[i];

	error_total[i]+= pow(e_n3_ATLAS[i],2);
	errorrel_total[i]+=y_n3_ATLAS[i];
      }

      gerror_ATLAS = new TGraphErrors(6,x_ms_ATLAS,e_n3_ATLAS,0,0);
      gerrorrel_ATLAS = new TGraphErrors(6,x_ms_ATLAS,errordivy,0,0);
      gerrorrel2_ATLAS = new TGraphErrors(6,x_ms_ATLAS,error_scale,0,0);

      canv1->cd(j+1);
      gerror_ATLAS->GetYaxis()->SetLabelSize(0.1);
      gerror_ATLAS->SetName(process);
      gerror_ATLAS->SetTitle(process);
      gerror_ATLAS->GetYaxis()->SetRangeUser(-0.001,0.001);

      if(kscale==0) gerror_ATLAS->Draw("alp");
      else{
	gerror_ATLAS->SetLineColor(kscale+1);//("l*");
	gerror_ATLAS->SetMarkerColor(kscale+1);//("l*");
	gerror_ATLAS->Draw("lp");
      }

      canv2->cd(j+1);
      gerrorrel_ATLAS->GetYaxis()->SetLabelSize(0.1);
      gerrorrel_ATLAS->SetName(process);
      gerrorrel_ATLAS->SetTitle(process);
      //gerrorrel_ATLAS->GetYaxis()->SetRangeUser(-0.001,0.001);

      if(kscale==0) gerrorrel_ATLAS->Draw("alp");
      else{
	gerrorrel_ATLAS->SetLineColor(kscale+1);//("l*");
	gerrorrel_ATLAS->SetMarkerColor(kscale+1);//("l*");
	gerrorrel_ATLAS->Draw("lp");
      }


    }//for j, every process



    double A= crossLO/pow(alphasNLO,3);
    double B= crossNLO/pow(alphasNLO,4);


    fout<<" "<<endl;
    fout<<" "<<endl;
    fout<< " ----------------------------------------------------" <<endl;
    fout<< " ####################################################" <<endl;
    fout<< " FINAL RESULTS FOR: "<<file_pdf+file_energy+"_"+file_mass+"_"+file_scale+"_"+file_kt+"_NLO"<<endl;
    fout<< " alpha_S(Q=Mt*mu) = "<< alphasNLO<< " used in the calculations"<< endl;
    fout<< " alpha_S(Q=Mt*mu) = "<< alphasNLO_NEW<< " FOR CORRECTIONS "<< endl;
    fout<< " SIGMA tt+Jet = "<<cross<<" +- "<<sqrt(errorcross)<<endl;
    fout<< " SIGMA tt+Jet = "<<crossLO*pow(alphasNLO_NEW/alphasNLO,3)+ crossNLO*pow(alphasNLO_NEW/alphasNLO,4)<<" with alpha_S corrections"<<endl;
    //fout << " +- "<<pow(alphasNLO_NEW,2)*sqrt(pow(3*crossLO*errorcrossLO,2)+pow(4*crossNLO*errorcrossNLO,2))<<" with alpha_S corrections"<<endl;
    fout<< " LO_SIGMA = "<< crossLO << " +- "<<sqrt(errorcrossLO)<<endl;
    fout<< " NLO_SIGMA = "<< crossNLO << " +- "<<sqrt(errorcrossNLO)<<endl;
    fout<< " SIGMA =   LO_SIGMA    +  NLO_SIGMA "<< endl;
    fout<< " SIGMA = alpha_S^3 * A + alpha_S^4 * B "<< endl;
    fout<< " A= "<< crossLO/pow(alphasNLO,3)<< "   B= "<< crossNLO/pow(alphasNLO,4)<<endl;
    fout<< " ####################################################" <<endl;
    fout<< " ----------------------------------------------------" <<endl;
  
  }
   
  

} 



//******************************************************************************************************************************************************
//******************************************************************************************************************************************************

/*int main()
  {
  plot_pythia_R3();
  }*/


 
  
  
