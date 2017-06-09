#include "string.h"
#include <iostream>
#include <fstream>
#include "TH1F.h"
#include "TNtuple.h"
#include "TLorentzVector.h"
#include "TFile.h"
#include "TVector.h"
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

void readPUoutput_runningNLO() {

  int jmin=0;
  int jmax=24;//jmin+1;

  for(int jmass =6; jmass<7; jmass++) {


  TString file_pdf="CT10";
  TString file_energy="7TeV";
  TString file_mass="mt160";
  TString file_scale;
  TString file_kt="pt50";
  TString file_prefix;

  if(jmass==0) file_mass="mt160";
  if(jmass==1) file_mass="mt161";
  if(jmass==2) file_mass="mt162";
  if(jmass==3) file_mass="mt163";
  if(jmass==4) file_mass="mt164";
  if(jmass==5) file_mass="mt165";
  if(jmass==6) file_mass="mt166";
  if(jmass==7) file_mass="mt167";
  if(jmass==8) file_mass="mt168";
  if(jmass==9) file_mass="mt169";
  if(jmass==10) file_mass="mt170";

  int kmin=0;
  int kmax=3;

  // if(file_mass=="mt160") {kmin=0; kmax=3;}
  //if(file_mass=="mt172.5") {kmin=0; kmax=3;}

  for(int k=kmin; k<kmax; k++) {


  double alphasNLO=0;   
  double alphasNLO_NEW=0;

 if(file_mass=="Mt170"){
    if(file_pdf=="MSTW2008nlo90cl_") alphasNLO_NEW=0.109698; //for mt=170, mu=1
    if(file_pdf=="abm11_5n_nlo_") alphasNLO_NEW=0.107864;
    //if(file_pdf=="CT10_") alphasNLO_NEW=0.107864; CT10 utiliza las mismas que el codigo, que son las de cteq66
    if(file_pdf=="NNPDF_") alphasNLO_NEW=0.108718;
  }
  if(file_mass=="mt172.5"){
    if(file_pdf=="MSTW2008nlo90cl_") alphasNLO_NEW=0.109474; //for mt=172.5, mu=1
    if(file_pdf=="abm11_5n_nlo_") alphasNLO_NEW=0.107649; //for mt=172.5, mu=1
    // if(file_pdf=="CT10_") alphasNLO_NEW=0.107648; CT10 utiliza las mismas que el codigo, que son las de cteq66
    if(file_pdf=="NNPDF_") alphasNLO_NEW=0.108499;
  }

    if(k==0) file_scale="mu05";
    if(k==1) file_scale="mu1";
    if(k==2) file_scale="mu2";


    if(file_mass=="mt172.5") file_prefix="../../ttJ1725_samples/results.mt172.5_CT10_"+file_scale+"_pt50_";
    else file_prefix="../../NLOmtpole/ttj_";
    TString outputfile="../../rootfiles/"+file_pdf+"_"+file_energy+"_"+file_mass+"_"+file_scale+"_"+file_kt+"_NLO.root";

    ofstream fout ("../../logfiles/"+file_pdf+"_"+file_energy+"_"+file_mass+"_"+file_scale+"_"+file_kt+"_NLO.out");

    cout<<"output file: "<<outputfile<<endl;
    cout<<"output log:  "<<"../../logfiles/"+file_pdf+"_"+file_energy+"_"+file_mass+"_"+file_scale+"_"+file_kt+"_NLO.out"<<endl;
    std::vector<TString> file_string_;
    file_string_=samples(file_mass, file_pdf, file_scale);

    TString string_file;

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


    fout<<"# "<<endl;
    fout<<"# "<<endl;
    fout<<"######################################################################################################### "<<endl;
    fout<<"# ROOT FILE  "<<file_pdf+file_energy+"_"+file_mass+"_"+file_scale+"_"+file_kt+"_NLO.root"<<endl;
    fout<<"######################################################################################################### "<<endl;
    fout<<"# "<<endl;
    fout<<"# "<<endl;
   
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

    for(int j=jmin ; j<jmax; j++) {

      ifstream file;

      string_file=file_string_[j];

      string_file= string_file +".out";
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

      tempcross=0;
      if (file )  // abro el listado

	{
	  while (!file.eof() && store_stop.find("..done.") > 0 ) {
	    file >> store_yt;
	    if(store_yt.find("./main.exe") == 0) { 
	      string s1,s2,s3,s4,s5,s6,s7,s8,s9,s10,s11,s12,s13,s14;
	      if(j==0 || j==1 || j==3 || j>7) file >>s1>>s2>>s3>>s4>>s5>>s6>>s7>>s8>>s9>>s10>>s11>>s12>>s13>>s14;
	      else if(j==2) file >>s1>>s2>>s3>>s4>>s5>>s6>>s7>>s8>>s9>>s10>>s11>>s12>>s13;
	      else file >>s1>>s2>>s3>>s4>>s5>>s6>>s7>>s8>>s9>>s10>>s11>>s12;
	      fout<<"#file number " <<j<<endl;
	      fout<<"#File name: "<< string_file<<endl;
	      fout<<"#settings on the simulation: "<<endl;
	      if(j==0 || j==1 || j==3 || j==2 || j>11) 
		fout<<"#"<<store_yt<<"  "<< s1 <<" "<< s2 <<" "<< s3 <<" "<< s4 <<" "<< s5 <<" "<< s6 <<" "<< s7 <<" "<< s8<<" "<< s9<<" "<<s10<< " "<<s11<<" "<<s12<<" "<<s13<< endl;
	      else if(j>7 && j<12) 
		fout<<"#"<<store_yt<<"  "<< s1 <<" "<< s2 <<" "<< s3 <<" "<< s4 <<" "<< s5 <<" "<< s6 <<" "<< s7 <<" "<< s8<<" "<< s9<<" "<<s10<< " "<<s11<<" "<<s12<<" "<<s13<<endl;
	      else fout<<"#"<<store_yt<<"  "<< s1 <<" "<< s2 <<" "<< s3 <<" "<< s4 <<" "<< s5 <<" "<< s6 <<" "<< s7 <<" "<< s8<<" "<< s9<<" "<<s10<< " "<<s11<<" "<<s12<< endl;

	    }

	    if(store_yt.find("alphasNLO") == 0 ) { 
	      string equal;
	      double temp_alpha;
	      file >> equal >> temp_alpha;
	      fout<<"#"<<store_yt<<"  "<< temp_alpha <<endl;
	      alphasNLO=temp_alpha;
	      if(alphasNLO_NEW==0) alphasNLO_NEW=alphasNLO;
	    }

	    if(store_yt.find("LHAPDF:") == 0 && first==true) { 
	      string pdf;
	      file >> pdf;
	      fout<<"#"<<store_yt<<"  "<< pdf <<endl;
	      first=false;
	    }

	    if(store_yt.find("elapsed") == 0) { 
	      double time;
	      file >> time;
	      fout<<"#Total time of calc: "<<time/(3600.*24)<<" d"<<endl;
	    }


	    if(store_yt.find("ACCUMULATED") == 0) { 
	      string results, integral, integral2;
	      int n;
	      n++;
	      file >> results >> integral >> integral2>>tempcross;
	      file >> results >> results >> results >> results >> errortempcross;
	    }

	    if(store_yt.find("Final") == 0) bool_leer=true;

	    string s1,s2,s3,s4,s5,s6,s7,s8,s9,s10;

	    // if(store_yt.find("ITERATION") == 0) { 
	    //   string no, num, sx;
	    //   file >> no >> num >> sx >> sx >> sx;
	    //   file >> sx >> sx >> sx >> sx >> sx;
	    //   file >> sx >> sx >> sx >> sx >> sx >> sx;
	    //   file >> sx >> sx >> sx >> sx >> sx;
	    //   file >> sx >> sx >> sx >> sx >> sx >> sx;
	    //   file >> sx >> sx;
	    //   file >> sx >> s2;

	    //   if(num=="8.") bool_leer=true;
	    //   cout<<no<<" "<<num<<endl;
	    //   cout<<s2<<endl;
	    // }

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
	      fout<<"#              File Ok, n3 (atlas) distribution found "<<endl;

	      cout<<"#              File Ok, n3 (atlas) distribution found "<<string_file<<endl;

	      count_n3_ATLAS++;
	      if(count_n3_ATLAS>0){
		for(int i=0; i<6; i++) {	
		  double d1=0., d2=0., d3=0;
		  file >> d1 >> d2 >> d3;
		  x_ms_ATLAS[i]=d1;
		  y_n3_ATLAS[i]+=bin_ms_ATLAS[i]*factor*d2;
		  e_n3_ATLAS[i]+=pow(bin_ms_ATLAS[i]*factor*d3,2);

		  if(j<4) {
		    y_n3LO_ATLAS[i]+=bin_ms_ATLAS[i]*factor*d2;
		    e_n3LO_ATLAS[i]+=pow(bin_ms_ATLAS[i]*factor*d3,2);
		  }else {
		    y_n3NLO_ATLAS[i]+=bin_ms_ATLAS[i]*factor*d2;
		    e_n3NLO_ATLAS[i]+=pow(bin_ms_ATLAS[i]*factor*d3,2);
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
	    // n3ttbar binning de 6_opt
	    if(s2=="n3ttbar_6_opt") {
	      count_n3ttbar_ATLAS++;
	      if(count_n3ttbar_ATLAS>0){
		for(int i=0; i<6; i++) {	
		  double d1=0., d2=0., d3=0;
		  file >> d1 >> d2 >> d3;
		  y_n3ttbar_ATLAS[i]+=bin_ms_ATLAS[i]*factor*d2;
		  e_n3ttbar_ATLAS[i]+=pow(bin_ms_ATLAS[i]*factor*d3,2);
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

	  }//while
	}// if file


      cross+=factor*tempcross;
      errorcross+=factor*factor*errortempcross*errortempcross;


      fout<< "#Calculated Process Cross-Section = "<<factor*tempcross<<" +- "<<factor*sqrt(errortempcross)<<endl;
      if(j<4) {
	fout<< "#LO  contribution" <<endl;
	crossLO+=factor*tempcross;
	errorcrossLO+=factor*factor*errortempcross*errortempcross;
      } else {
	fout<< "#NLO  contribution" <<endl;
	crossNLO+=factor*tempcross;
	errorcrossNLO+=factor*factor*errortempcross*errortempcross;
      }
      fout<<"# "<<endl;

    }//for j, every process


    double A= crossLO/pow(alphasNLO/TMath::Pi(),3);
    double B= crossNLO/pow(alphasNLO/TMath::Pi(),4);

    double eA= errorcrossLO/pow(alphasNLO/TMath::Pi(),3);
    double eB= errorcrossNLO/pow(alphasNLO/TMath::Pi(),4);

    TString topmass( file_mass(2,4) );
    TString scalevalue;
    TString scalevalue1( file_scale(2,1) );
    TString scalevalue2( file_scale(file_scale.Sizeof()-2,1) );
    if(file_scale.Sizeof()-1==4) scalevalue=scalevalue1+"."+scalevalue2;
    if(file_scale.Sizeof()-1==3) scalevalue=scalevalue2;

      fout<<"# "<<endl;
      fout<<"# "<<endl;
      fout<< "####################################################" <<endl;
      fout<< "# SUMMARY RESULTS FOR: "<<file_pdf+file_energy+"_"+file_mass+"_"+file_scale+"_"+file_kt+"_NLO"<<endl;
      fout<< "# JETALGORITHM = antikt"<<endl;
      fout<< "# JETCONESIZE = 0.4"<<endl;
      fout<< "# JETMINIMUMPT = 50"<<endl;
      fout<< "# TOPPOLEMASS = "<<topmass<<endl;
      fout<< "# SCALEFACTOR = "<<scalevalue<<endl;
      fout<< "# SCALE = SCALEFACTOR x TOPPOLEMASS"<<endl;
      fout<< "# alpha_S(Q=Mt*mu) = "<< alphasNLO<< endl;
      // fout<< " alpha_S(Q=Mt*mu) = "<< alphasNLO_NEW<< " FOR CORRECTIONS "<< endl;
      fout<< "# SIGMA tt+Jet = "<<cross<<" +- "<<sqrt(errorcross)<<endl;
      //      fout<< " SIGMA tt+Jet = "<<crossLO*pow(alphasNLO_NEW/alphasNLO,3)+ crossNLO*pow(alphasNLO_NEW/alphasNLO,4)<<" with alpha_S corrections"<<endl;
      fout<< "# LO_SIGMA = "<< crossLO << " +- "<<sqrt(errorcrossLO)<<endl;
      fout<< "# NLO_SIGMA = "<< crossNLO << " +- "<<sqrt(errorcrossNLO)<<endl;
      fout<< "# SIGMA =   LO_SIGMA    +  NLO_SIGMA "<< endl;
      fout<< "# SIGMA = (alpha_S/Pi)^3 * Sigma_0 + (alpha_S/Pi)^4 * Sigma_1 "<< endl;
      fout<< "# Sigma_0= "<< A << endl;
      fout<< "# Sigma_1= "<< B <<endl;
      fout<< "# alpha_S/Pi = "<<alphasNLO/TMath::Pi()<< endl;
      fout<< "####################################################" <<endl;

      double e_x_eta[20], e_x_pt[20], e_x_e[40];
      double e_x_ms_24[24];
      double e_x_ms_12[12];
      double e_x_ms_ATLAS[6];



      for(int i=0; i<20; i++) {
	e_x_eta[i]=0.2;
	e_eta_t[i]=sqrt(e_eta_t[i]);
	e_eta_tb[i]=sqrt(e_eta_tb[i]);
	e_eta_ttb[i]=sqrt(e_eta_ttb[i]);
	e_eta_ttbj[i]=sqrt(e_eta_ttbj[i]);
	e_eta_g[i]=sqrt(e_eta_g[i]);

	e_x_pt[i]=16.7;
	e_pt_t[i]=sqrt(e_pt_t[i]);
	e_pt_tb[i]=sqrt(e_pt_tb[i]);
	e_pt_ttb[i]=sqrt(e_pt_ttb[i]);
	e_pt_ttbj[i]=sqrt(e_pt_ttbj[i]);
	e_pt_g[i]=sqrt(e_pt_g[i]);
      }

      for(int i=0; i<40; i++) {
	e_x_e[i]=0.2;
	e_e_t[i]=sqrt(e_e_t[i]);
	e_e_tb[i]=sqrt(e_e_tb[i]);
	e_e_ttb[i]=sqrt(e_e_ttb[i]);
	e_e_ttbj[i]=sqrt(e_e_ttbj[i]);
	e_e_g[i]=sqrt(e_e_g[i]);
      }


      TGraphErrors *eta_t = new TGraphErrors(20,x_eta,y_eta_t,e_x_eta,e_eta_t);
      TGraphErrors *eta_tb = new TGraphErrors(20,x_eta,y_eta_tb,e_x_eta,e_eta_tb);
      TGraphErrors *eta_ttb = new TGraphErrors(20,x_eta,y_eta_ttb,e_x_eta,e_eta_ttb);
      TGraphErrors *eta_ttbj = new TGraphErrors(20,x_eta,y_eta_ttbj,e_x_eta,e_eta_ttbj);
      TGraphErrors *eta_g = new TGraphErrors(20,x_eta,y_eta_g,e_x_eta,e_eta_g);

      TGraphErrors *pt_t = new TGraphErrors(20,x_pt,y_pt_t,e_x_pt,e_pt_t);
      TGraphErrors *pt_tb = new TGraphErrors(20,x_pt,y_pt_tb,e_x_pt,e_pt_tb);
      TGraphErrors *pt_ttb = new TGraphErrors(20,x_pt,y_pt_ttb,e_x_pt,e_pt_ttb);
      TGraphErrors *pt_ttbj = new TGraphErrors(20,x_pt,y_pt_ttbj,e_x_pt,e_pt_ttbj);
      TGraphErrors *pt_g = new TGraphErrors(20,x_pt,y_pt_g,e_x_pt,e_pt_g);

      TGraphErrors *e_t = new TGraphErrors(40,x_e,y_e_t,e_x_e,e_e_t);
      TGraphErrors *e_tb = new TGraphErrors(40,x_e,y_e_tb,e_x_e,e_e_tb);
      TGraphErrors *e_ttb = new TGraphErrors(40,x_e,y_e_ttb,e_x_e,e_e_ttb);
      TGraphErrors *e_ttbj = new TGraphErrors(40,x_e,y_e_ttbj,e_x_e,e_e_ttbj);
      TGraphErrors *e_g = new TGraphErrors(40,x_e,y_e_g,e_x_e,e_e_g);

      
      //-----------------------------------------------------------------------------
      TGraphErrors *N3_kt50_12 = new TGraphErrors;
      TGraphErrors *N3LO_kt50_12 = new TGraphErrors;
      TGraphErrors *N3NLO_kt50_12 = new TGraphErrors;
      TGraphErrors *A_kt50_12 = new TGraphErrors;
      TGraphErrors *B_kt50_12 = new TGraphErrors;
      TGraphErrors *N3_alphacorrected_12 = new TGraphErrors;

      TGraphErrors *n3_kt50_12 = new TGraphErrors;
      TGraphErrors *n3_alphacorrected_12 = new TGraphErrors;
      TGraphErrors *n3_approx_12 = new TGraphErrors;
      TGraphErrors *n3_approx_alphacorrected_12 = new TGraphErrors;


      TGraphErrors *N3ttbar_kt50_12 = new TGraphErrors;
      TGraphErrors *n3ttbar_kt50_12 = new TGraphErrors;

      //----------------------------------------------------------------------------
      //-----------------------------------------------------------------------------
      
      double A_12[12], B_12[12];
      double eA_12[12], eB_12[12];

      double y_corrected_12[12], ey_corrected_12[12];

      for(int i=0; i<12; i++) {
	A_12[i]=0.; B_12[i]=0.;
	eA_12[i]=0.; eB_12[i]=0.;
	y_corrected_12[i]=0; ey_corrected_12[i]=0;

	e_x_ms_12[i]=1.2/(2*12);
	e_n3_kt50_12[i]=sqrt(e_n3_kt50_12[i]);
	e_n3LO_kt50_12[i]=sqrt(e_n3LO_kt50_12[i]);
	e_n3NLO_kt50_12[i]=sqrt(e_n3NLO_kt50_12[i]);

	A_12[i]=y_n3LO_kt50_12[i]/pow(alphasNLO,3);
	B_12[i]=y_n3NLO_kt50_12[i]/pow(alphasNLO,4);
	eA_12[i]=sqrt(e_n3LO_kt50_12[i]/pow(alphasNLO,3));
	eB_12[i]=sqrt(e_n3NLO_kt50_12[i]/pow(alphasNLO,4));

	y_corrected_12[i]=A_12[i]*pow(alphasNLO_NEW,3)+B_12[i]*pow(alphasNLO_NEW,4);
	ey_corrected_12[i]=sqrt(pow(eA_12[i]*pow(alphasNLO_NEW,3),2)+pow(eB_12[i]*pow(alphasNLO_NEW,4),2));
      }

      N3_kt50_12 = new TGraphErrors(12,x_ms_12,y_n3_kt50_12,e_x_ms_12,e_n3_kt50_12);
      N3LO_kt50_12 = new TGraphErrors(12,x_ms_12,y_n3LO_kt50_12,e_x_ms_12,e_n3LO_kt50_12);
      N3NLO_kt50_12 = new TGraphErrors(12,x_ms_12,y_n3NLO_kt50_12,e_x_ms_12,e_n3NLO_kt50_12);
      A_kt50_12 = new TGraphErrors(12,x_ms_12,A_12,e_x_ms_12,eA_12);
      B_kt50_12 = new TGraphErrors(12,x_ms_12,B_12,e_x_ms_12,eB_12);
      N3_alphacorrected_12 = new TGraphErrors(12,x_ms_12,y_corrected_12,e_x_ms_12,ey_corrected_12);
      //-------------------------------------------------------------------------------------------------------

      double y_approx_12[12], ey_approx_12[12];
      double y_approx_corrected_12[12], ey_approx_corrected_12[12];

      for(int i=0; i<12; i++) {
	y_corrected_12[i]=0; ey_corrected_12[i]=0;
	y_approx_12[i]=0; ey_approx_12[i]=0;
	y_approx_corrected_12[i]=0; ey_approx_corrected_12[i]=0;

	y_n3_kt50_12[i]=(1./cross)*(y_n3_kt50_12[i])/0.1;
	e_n3_kt50_12[i]=(1./cross)*(e_n3_kt50_12[i]);

	double ya=A_12[i]+B_12[i]*alphasNLO_NEW;
	double yb=A+B*alphasNLO_NEW;
	double eya=sqrt(pow(eA_12[i],2)+pow(eB_12[i]*alphasNLO_NEW,2))/yb;

	y_corrected_12[i]=(ya/yb)/0.1;
	ey_corrected_12[i]=eya;

	y_approx_12[i]=(1./A)*(A_12[i]+(B_12[i]-(A_12[i]*B/A))*alphasNLO)/0.1;
	ey_approx_12[i]=0.;

	y_approx_corrected_12[i]=(1./A)*(A_12[i]+(B_12[i]-(A_12[i]*B/A))*alphasNLO_NEW)/0.1;
	ey_approx_corrected_12[i]=0.;
      }

      n3_kt50_12 = new TGraphErrors(12,x_ms_12,y_n3_kt50_12,e_x_ms_12,e_n3_kt50_12);
      n3_alphacorrected_12 = new TGraphErrors(12,x_ms_12,y_corrected_12,e_x_ms_12,ey_corrected_12);
      n3_approx_12 = new TGraphErrors(12,x_ms_12,y_approx_12,e_x_ms_12,ey_approx_12);
      n3_approx_alphacorrected_12 = new TGraphErrors(12,x_ms_12,y_approx_corrected_12,e_x_ms_12,ey_approx_corrected_12);

      //-------------------------------------------------------------------------------------------------------


      //-----------------------------------------------------------------------------
      //-----------------------------------------------------------------------------
      for(int i=0; i<12; i++) e_n3ttbar_kt50_12[i]=sqrt(e_n3ttbar_kt50_12[i]);
      N3ttbar_kt50_12 = new TGraphErrors(12,x_ms_12,y_n3ttbar_kt50_12,e_x_ms_12,e_n3ttbar_kt50_12);
      for(int i=0; i<12; i++) {
	e_n3ttbar_kt50_12[i]=(1./cross)*(e_n3ttbar_kt50_12[i]);
	y_n3ttbar_kt50_12[i]=(1./cross)*(y_n3ttbar_kt50_12[i])/0.1;
      }
      n3ttbar_kt50_12 = new TGraphErrors(12,x_ms_12,y_n3ttbar_kt50_12,e_x_ms_12,e_n3ttbar_kt50_12);
      //-----------------------------------------------------------------------------
      //-----------------------------------------------------------------------------




   //-----------------------------------------------------------------------------
      TGraphErrors *N3_kt50_24 = new TGraphErrors;
      TGraphErrors *N3LO_kt50_24 = new TGraphErrors;
      TGraphErrors *N3NLO_kt50_24 = new TGraphErrors;
      TGraphErrors *A_kt50_24 = new TGraphErrors;
      TGraphErrors *B_kt50_24 = new TGraphErrors;
      TGraphErrors *N3_alphacorrected_24 = new TGraphErrors;

      TGraphErrors *n3_kt50_24 = new TGraphErrors;
      TGraphErrors *n3_alphacorrected_24 = new TGraphErrors;
      TGraphErrors *n3_approx_24 = new TGraphErrors;
      TGraphErrors *n3_approx_alphacorrected_24 = new TGraphErrors;


      TGraphErrors *N3ttbar_kt50_24 = new TGraphErrors;
      TGraphErrors *n3ttbar_kt50_24 = new TGraphErrors;

      //----------------------------------------------------------------------------
      //-----------------------------------------------------------------------------
      
      double A_24[24], B_24[24];
      double eA_24[24], eB_24[24];

      double y_corrected_24[24], ey_corrected_24[24];

      for(int i=0; i<24; i++) {
	A_24[i]=0.; B_24[i]=0.;
	eA_24[i]=0.; eB_24[i]=0.;
	y_corrected_24[i]=0; ey_corrected_24[i]=0;

	e_x_ms_24[i]=1.2/(2*24);
	e_n3_kt50_24[i]=sqrt(e_n3_kt50_24[i]);
	e_n3LO_kt50_24[i]=sqrt(e_n3LO_kt50_24[i]);
	e_n3NLO_kt50_24[i]=sqrt(e_n3NLO_kt50_24[i]);

	A_24[i]=y_n3LO_kt50_24[i]/pow(alphasNLO,3);
	B_24[i]=y_n3NLO_kt50_24[i]/pow(alphasNLO,4);
	eA_24[i]=sqrt(e_n3LO_kt50_24[i]/pow(alphasNLO,3));
	eB_24[i]=sqrt(e_n3NLO_kt50_24[i]/pow(alphasNLO,4));

	double ya=A_24[i]+B_24[i]*alphasNLO_NEW;
	double yb=A+B*alphasNLO_NEW;
	double eya=sqrt(pow(eA_24[i],2)+pow(eB_24[i]*alphasNLO_NEW,2))/yb;
	y_corrected_24[i]=ya;
	ey_corrected_24[i]=eya;
      }


      N3_kt50_24 = new TGraphErrors(24,x_ms_24,y_n3_kt50_24,e_x_ms_24,e_n3_kt50_24);
      N3LO_kt50_24 = new TGraphErrors(24,x_ms_24,y_n3LO_kt50_24,e_x_ms_24,e_n3LO_kt50_24);
      N3NLO_kt50_24 = new TGraphErrors(24,x_ms_24,y_n3NLO_kt50_24,e_x_ms_24,e_n3NLO_kt50_24);
      A_kt50_24 = new TGraphErrors(24,x_ms_24,A_24,e_x_ms_24,eA_24);
      B_kt50_24 = new TGraphErrors(24,x_ms_24,B_24,e_x_ms_24,eB_24);
      N3_alphacorrected_24 = new TGraphErrors(24,x_ms_24,y_corrected_24,e_x_ms_24,ey_corrected_24);
      //-------------------------------------------------------------------------------------------------------

      double y_approx_24[24], ey_approx_24[24];
      double y_approx_corrected_24[24], ey_approx_corrected_24[24];

      for(int i=0; i<24; i++) {
	y_corrected_24[i]=0; ey_corrected_24[i]=0;
	y_approx_24[i]=0; ey_approx_24[i]=0;
	y_approx_corrected_24[i]=0; ey_approx_corrected_24[i]=0;

	y_n3_kt50_24[i]=(1./cross)*(y_n3_kt50_24[i])/0.05;
	e_n3_kt50_24[i]=(1./cross)*(e_n3_kt50_24[i])/0.05;

	y_corrected_24[i]=(A_24[i]*pow(alphasNLO_NEW,3)+B_24[i]*pow(alphasNLO_NEW,4))/(A*pow(alphasNLO_NEW,3)+B*pow(alphasNLO_NEW,4))/0.05;
	ey_corrected_24[i]=0.;//sqrt(pow(eA_24[i]*pow(alphasNLO,3),2)+pow(eB_24[i]*pow(alphasNLO,4),2));

	y_approx_24[i]=(1./A)*(A_24[i]+(B_24[i]-(A_24[i]*B/A))*alphasNLO)/0.05;
	ey_approx_24[i]=0.;

	y_approx_corrected_24[i]=(1./A)*(A_24[i]+(B_24[i]-(A_24[i]*B/A))*alphasNLO_NEW)/0.05;
	ey_approx_corrected_24[i]=0.;
      }

      n3_kt50_24 = new TGraphErrors(24,x_ms_24,y_n3_kt50_24,e_x_ms_24,e_n3_kt50_24);
      n3_alphacorrected_24 = new TGraphErrors(24,x_ms_24,y_corrected_24,e_x_ms_24,ey_corrected_24);
      n3_approx_24 = new TGraphErrors(24,x_ms_24,y_approx_24,e_x_ms_24,ey_approx_24);
      n3_approx_alphacorrected_24 = new TGraphErrors(24,x_ms_24,y_approx_corrected_24,e_x_ms_24,ey_approx_corrected_24);

      //-------------------------------------------------------------------------------------------------------

      //-----------------------------------------------------------------------------
      for(int i=0; i<24; i++) e_n3ttbar_kt50_24[i]=sqrt(e_n3ttbar_kt50_24[i]);
      N3ttbar_kt50_24 = new TGraphErrors(24,x_ms_24,y_n3ttbar_kt50_24,e_x_ms_24,e_n3ttbar_kt50_24);
      for(int i=0; i<24; i++) {
	e_n3ttbar_kt50_24[i]=(1./cross)*(e_n3ttbar_kt50_24[i])/0.05;
	y_n3ttbar_kt50_24[i]=(1./cross)*(y_n3ttbar_kt50_24[i])/0.05;
      }
      n3ttbar_kt50_24 = new TGraphErrors(24,x_ms_24,y_n3ttbar_kt50_24,e_x_ms_24,e_n3ttbar_kt50_24);
      //-----------------------------------------------------------------------------
      //-----------------------------------------------------------------------------


      //*************************************************************************************************************************************************************************
      // R 6 ATLAS
      //-----------------------------------------------------------------------------
      TGraphErrors *gN3_ATLAS = new TGraphErrors;
      TGraphErrors *gN3LO_ATLAS = new TGraphErrors;
      TGraphErrors *gN3NLO_ATLAS = new TGraphErrors;
      TGraphErrors *gA_ATLAS = new TGraphErrors;
      TGraphErrors *gB_ATLAS = new TGraphErrors;
      TGraphErrors *gN3_alphacorrected_ATLAS = new TGraphErrors;

      TGraphErrors *gn3_ATLAS = new TGraphErrors;
      TGraphErrors *gn3_alphacorrected_ATLAS = new TGraphErrors;
      TGraphErrors *gn3_approx_ATLAS = new TGraphErrors;
      TGraphErrors *gn3_approx_alphacorrected_ATLAS = new TGraphErrors;


      TGraphErrors *gN3ttbar_ATLAS = new TGraphErrors;
      TGraphErrors *gn3ttbar_ATLAS = new TGraphErrors;

      //----------------------------------------------------------------------------
      //-----------------------------------------------------------------------------
      
      double A_ATLAS[6], B_ATLAS[6];
      double eA_ATLAS[6], eB_ATLAS[6];

      double y_corrected_ATLAS[6], ey_corrected_ATLAS[6];

      for(int i=0; i<6; i++) {

	e_x_ms_ATLAS[i]= bin_ms_ATLAS[i]/2.;
	A_ATLAS[i]=0.; B_ATLAS[i]=0.;
	eA_ATLAS[i]=0.; eB_ATLAS[i]=0.;
	y_corrected_ATLAS[i]=0; ey_corrected_ATLAS[i]=0;

	e_n3_ATLAS[i]=sqrt(e_n3_ATLAS[i]);
	e_n3LO_ATLAS[i]=sqrt(e_n3LO_ATLAS[i]);
	e_n3NLO_ATLAS[i]=sqrt(e_n3NLO_ATLAS[i]);

	A_ATLAS[i]=y_n3LO_ATLAS[i]/pow(alphasNLO/TMath::Pi(),3);
	B_ATLAS[i]=y_n3NLO_ATLAS[i]/pow(alphasNLO/TMath::Pi(),4);
	eA_ATLAS[i]=sqrt(e_n3LO_ATLAS[i]/pow(alphasNLO/TMath::Pi(),3));
	eB_ATLAS[i]=sqrt(e_n3NLO_ATLAS[i]/pow(alphasNLO/TMath::Pi(),4));

	double ya=(A_ATLAS[i]+B_ATLAS[i]*alphasNLO_NEW/TMath::Pi())*pow(alphasNLO_NEW/TMath::Pi(),3);
	//	double yb=A+B*alphasNLO_NEW;
	//	double eya=sqrt(pow(eA_ATLAS[i],2)+pow(eB_ATLAS[i]*alphasNLO_NEW,2))/yb;
	y_corrected_ATLAS[i]=ya;
       	ey_corrected_ATLAS[i]=0;
      }


      gN3_ATLAS = new TGraphErrors(6,x_ms_ATLAS,y_n3_ATLAS,e_x_ms_ATLAS,e_n3_ATLAS);
      gN3LO_ATLAS = new TGraphErrors(6,x_ms_ATLAS,y_n3LO_ATLAS,e_x_ms_ATLAS,e_n3LO_ATLAS);
      gN3NLO_ATLAS = new TGraphErrors(6,x_ms_ATLAS,y_n3NLO_ATLAS,e_x_ms_ATLAS,e_n3NLO_ATLAS);
      gA_ATLAS = new TGraphErrors(6,x_ms_ATLAS,A_ATLAS,e_x_ms_ATLAS,eA_ATLAS);
      gB_ATLAS = new TGraphErrors(6,x_ms_ATLAS,B_ATLAS,e_x_ms_ATLAS,eB_ATLAS);
      gN3_alphacorrected_ATLAS = new TGraphErrors(6,x_ms_ATLAS,y_corrected_ATLAS,e_x_ms_ATLAS,ey_corrected_ATLAS);

      fout<< "# ATLAS binning N3 distribution "<<endl;
      fout<< "# HISTSTART " <<endl;
      fout<< "# DATASTART : centre-of-bin, data, errorestimate" <<endl;
      for(int i=0; i<6; i++) 
	fout<< x_ms_ATLAS[i]<<" "<<y_n3_ATLAS[i]<<" "<<e_n3_ATLAS[i]<<endl;

      fout<< "# DATAEND " <<endl;
      fout<< "# HISTEND " <<endl;

      //-------------------------------------------------------------------------------------------------------

      double y_approx_ATLAS[6], ey_approx_ATLAS[6];
      double y_approx_corrected_ATLAS[6], ey_approx_corrected_ATLAS[6];

      for(int i=0; i<6; i++) {
	y_corrected_ATLAS[i]=0; ey_corrected_ATLAS[i]=0;
	y_approx_ATLAS[i]=0; ey_approx_ATLAS[i]=0;
	y_approx_corrected_ATLAS[i]=0; ey_approx_corrected_ATLAS[i]=0;

	y_n3_ATLAS[i]=(1./cross)*(y_n3_ATLAS[i])/(e_x_ms_ATLAS[i]*2);
	e_n3_ATLAS[i]=(1./cross)*(e_n3_ATLAS[i])/(e_x_ms_ATLAS[i]*2);

	double ya, yb;
	ya=(A_ATLAS[i]*pow(alphasNLO_NEW/TMath::Pi(),3)+B_ATLAS[i]*pow(alphasNLO_NEW/TMath::Pi(),4));
	yb=(A*pow(alphasNLO_NEW/TMath::Pi(),3)+B*pow(alphasNLO_NEW/TMath::Pi(),4))*(e_x_ms_ATLAS[i]*2);
	y_corrected_ATLAS[i]=ya/yb;
	ey_corrected_ATLAS[i]=0.;//sqrt(pow(eA_ATLAS[i]*pow(alphasNLO,3),2)+pow(eB_ATLAS[i]*pow(alphasNLO,4),2));

	y_approx_ATLAS[i]=(1./A)*(A_ATLAS[i]+(B_ATLAS[i]-(A_ATLAS[i]*B/A))*(alphasNLO/TMath::Pi()))/(e_x_ms_ATLAS[i]*2);
	ey_approx_ATLAS[i]=0.;

	y_approx_corrected_ATLAS[i]=(1./A)*(A_ATLAS[i]+(B_ATLAS[i]-(A_ATLAS[i]*B/A))*(alphasNLO_NEW/TMath::Pi()))/(e_x_ms_ATLAS[i]*2);
	ey_approx_corrected_ATLAS[i]=0.;
      }

      gn3_ATLAS = new TGraphErrors(6,x_ms_ATLAS,y_n3_ATLAS,e_x_ms_ATLAS,e_n3_ATLAS);
      gn3_alphacorrected_ATLAS = new TGraphErrors(6,x_ms_ATLAS,y_corrected_ATLAS,e_x_ms_ATLAS,ey_corrected_ATLAS);
      gn3_approx_ATLAS = new TGraphErrors(6,x_ms_ATLAS,y_approx_ATLAS,e_x_ms_ATLAS,ey_approx_ATLAS);
      gn3_approx_alphacorrected_ATLAS = new TGraphErrors(6,x_ms_ATLAS,y_approx_corrected_ATLAS,e_x_ms_ATLAS,ey_approx_corrected_ATLAS);

      //-------------------------------------------------------------------------------------------------------

      //-----------------------------------------------------------------------------
      for(int i=0; i<6; i++) e_n3ttbar_ATLAS[i]=sqrt(e_n3ttbar_ATLAS[i]);
      gN3ttbar_ATLAS = new TGraphErrors(6,x_ms_ATLAS,y_n3ttbar_ATLAS,e_x_ms_ATLAS,e_n3ttbar_ATLAS);
      for(int i=0; i<6; i++) {
	e_n3ttbar_ATLAS[i]=(1./cross)*(e_n3ttbar_ATLAS[i])/(e_x_ms_ATLAS[i]*2);
	y_n3ttbar_ATLAS[i]=(1./cross)*(y_n3ttbar_ATLAS[i])/(e_x_ms_ATLAS[i]*2);
      }
      gn3ttbar_ATLAS = new TGraphErrors(6,x_ms_ATLAS,y_n3ttbar_ATLAS,e_x_ms_ATLAS,e_n3ttbar_ATLAS);
      //-----------------------------------------------------------------------------
      //-----------------------------------------------------------------------------


      TFile *f1 = new  TFile;
      f1 = new  TFile(outputfile,"RECREATE");
      
      TVectorD a(1);
      a[0] = alphasNLO/TMath::Pi();
      cout<<a[0]<<endl;
      a.Write("alphas_over_pi");

      TVectorD sigma(2);
      sigma[0] = cross;
      sigma[1] = errorcross;
      sigma.Write("sigma");

      TVectorD sigma0(2);
      sigma0[0] = A;
      sigma0[1] = eA;
      sigma0.Write("sigma0");

      TVectorD sigma1(2);
      sigma1[0] = B;
      sigma1[1] = eB;
      sigma1.Write("sigma1");

      eta_t->SetName("eta_t");
      eta_t->Write();
      eta_tb->SetName("eta_tb");
      eta_tb->Write();
      eta_ttb->SetName("eta_ttb");
      eta_ttb->Write();
      eta_ttbj->SetName("eta_ttbj");
      eta_ttbj->Write();
      eta_g->SetName("eta_g");
      eta_g->Write();

      pt_t->SetName("pt_t");
      pt_t->Write();
      pt_tb->SetName("pt_tb");
      pt_tb->Write();
      pt_ttb->SetName("pt_ttb");
      pt_ttb->Write();
      pt_ttbj->SetName("pt_ttbj");
      pt_ttbj->Write();
      pt_g->SetName("pt_g");
      pt_g->Write();

      e_t->SetName("e_t");
      e_t->Write();
      e_tb->SetName("e_tb");
      e_tb->Write();
      e_ttb->SetName("e_ttb");
      e_ttb->Write();
      e_ttbj->SetName("e_ttbj");
      e_ttbj->Write();
      e_g->SetName("e_g");
      e_g->Write();

      //----------------------------------------------------

      N3_kt50_12->SetName("N3_kt50_12");
      N3LO_kt50_12->SetName("N3LO_kt50_12");
      N3NLO_kt50_12->SetName("N3NLO_kt50_12");
      A_kt50_12->SetName("A_kt50_12");
      B_kt50_12->SetName("B_kt50_12");
      N3_alphacorrected_12->SetName("N3_alphacorrected_12");

      N3_kt50_12->Write();
      N3LO_kt50_12->Write();
      N3NLO_kt50_12->Write();
      A_kt50_12->Write();
      B_kt50_12->Write();
      N3_alphacorrected_12->Write();

      n3_kt50_12->SetName("n3_kt50_12");
      n3_alphacorrected_12->SetName("n3_alphacorrected_12");
      n3_approx_12->SetName("n3_approx_12");
      n3_approx_alphacorrected_12->SetName("n3_approx_alphacorrected_12");

      n3_kt50_12->Write();
      n3_alphacorrected_12->Write();
      n3_approx_12->Write();
      n3_approx_alphacorrected_12->Write();
      //----------------------------------------------------

      N3_kt50_24->SetName("N3_kt50_24");
      N3LO_kt50_24->SetName("N3LO_kt50_24");
      N3NLO_kt50_24->SetName("N3NLO_kt50_24");
      A_kt50_24->SetName("A_kt50_24");
      B_kt50_24->SetName("B_kt50_24");
      N3_alphacorrected_24->SetName("N3_alphacorrected_24");

      N3_kt50_24->Write();
      N3LO_kt50_24->Write();
      N3NLO_kt50_24->Write();
      A_kt50_24->Write();
      B_kt50_24->Write();
      N3_alphacorrected_24->Write();

      n3_kt50_24->SetName("n3_kt50_24");
      n3_alphacorrected_24->SetName("n3_alphacorrected_24");
      n3_approx_24->SetName("n3_approx_24");
      n3_approx_alphacorrected_24->SetName("n3_approx_alphacorrected_24");

      n3_kt50_24->Write();
      n3_alphacorrected_24->Write();
      n3_approx_24->Write();
      n3_approx_alphacorrected_24->Write();

      //----------------------------------------------------

      N3ttbar_kt50_24->SetName("Msttbar_kt50_24");
      N3ttbar_kt50_24->Write();

      n3ttbar_kt50_24->SetName("msttbar_kt50_24");
      n3ttbar_kt50_24->Write();

      //----------------------------------------------------
      // ATLAS!!
      gN3_ATLAS->SetName("N3_ATLAS");
      gN3LO_ATLAS->SetName("N3LO_ATLAS");
      gN3NLO_ATLAS->SetName("N3NLO_ATLAS");
      gA_ATLAS->SetName("N3_0_ATLAS");
      gB_ATLAS->SetName("N3_1_ATLAS");
      gN3_alphacorrected_ATLAS->SetName("N3_alphacorrected_ATLAS");

      gN3_ATLAS->Write();
      gN3LO_ATLAS->Write();
      gN3NLO_ATLAS->Write();
      gA_ATLAS->Write();
      gB_ATLAS->Write();
      gN3_alphacorrected_ATLAS->Write();

      gn3_ATLAS->SetName("n3_ATLAS");
      gn3_alphacorrected_ATLAS->SetName("n3_alphacorrected_ATLAS");
      gn3_approx_ATLAS->SetName("n3_approx_ATLAS");
      gn3_approx_alphacorrected_ATLAS->SetName("n3_approx_alphacorrected_ATLAS");

      gn3_ATLAS->Write();
      gn3_alphacorrected_ATLAS->Write();
      gn3_approx_ATLAS->Write();
      gn3_approx_alphacorrected_ATLAS->Write();
      //----------------------------------------------------
      gN3ttbar_ATLAS->SetName("Msttbar_ATLAS");
      gN3ttbar_ATLAS->Write();

      gn3ttbar_ATLAS->SetName("msttbar_ATLAS");
      gn3ttbar_ATLAS->Write();


    f1->Close();

    // TCanvas *canv = new TCanvas (file_energy+"_"+file_mass+"_"+file_scale+" kinematics",file_energy+"_"+file_mass+"_"+file_scale+" kinematics",600,600);
    // canv->Divide(2,1);
    // canv->cd(1);
    // gPad->SetGridx();
    // gPad->SetGridy();
    // pt_g->SetTitle("\\pt, proceso : "+file_energy+"_"+file_mass+"_"+file_scale);
    // pt_g->GetXaxis()->SetTitle("\\pt");
    // pt_g->GetYaxis()->SetTitle("pb");
    // pt_g->SetName("pt_g");
    // pt_g->SetLineColor(4);
    // pt_g->SetLineWidth(2);
    // pt_g->Draw("ALEP");
    // pt_t->SetName("pt_t");
    // pt_t->SetLineColor(1);
    // pt_t->SetLineWidth(2);
    // pt_t->Draw("LEP");
    // pt_tb->SetName("pt_tb");
    // pt_tb->SetLineColor(2);
    // pt_tb->SetLineWidth(2);
    // pt_tb->SetLineStyle(2);
    // pt_tb->Draw("LEP");

    // pt_ttb->SetName("pt_ttb");
    // pt_ttb->SetLineColor(3);
    // pt_ttb->SetLineWidth(2);
    // pt_ttb->SetLineStyle(2);
    // pt_ttb->Draw("LEP");

    // pt_ttbj->SetName("pt_ttbj");
    // pt_ttbj->SetLineColor(5);
    // pt_ttbj->SetLineWidth(2);
    // pt_ttbj->SetLineStyle(2);
    // pt_ttbj->Draw("LEP");

    // TLegend *leg = new TLegend(0.65,0.65,0.95,0.85);//Variables
    // leg->AddEntry("pt_t","pt_t","lep");
    // leg->AddEntry("pt_tb","pt_tb","lep");
    // leg->AddEntry("pt_ttb","pt_ttb","lep");
    // leg->AddEntry("pt_ttbj","pt_ttbj","lep");
    // leg->AddEntry("pt_g","pt_g","lep");
    // leg->Draw();

    // canv->cd(2);
    // gPad->SetGridx();
    // gPad->SetGridy();
    // eta_g->SetTitle("\\eta, proceso : "+file_energy+"_"+file_mass+"_"+file_scale);
    // eta_g->GetXaxis()->SetTitle("\\eta");
    // eta_g->GetYaxis()->SetTitle("pb");
    // eta_g->SetName("eta_g");
    // eta_g->SetLineColor(4);
    // eta_g->SetLineWidth(2);
    // eta_g->Draw("ALEP");
    // eta_t->SetName("eta_t");
    // eta_t->SetLineColor(1);
    // eta_t->SetLineWidth(2);
    // eta_t->Draw("LEP");
    // eta_tb->SetName("eta_tb");
    // eta_tb->SetLineColor(2);
    // eta_tb->SetLineWidth(2);
    // eta_tb->SetLineStyle(2);
    // eta_tb->Draw("LEP");

    // eta_ttb->SetName("eta_ttb");
    // eta_ttb->SetLineColor(3);
    // eta_ttb->SetLineWidth(2);
    // eta_ttb->SetLineStyle(2);
    // eta_ttb->Draw("LEP");

    // eta_ttbj->SetName("eta_ttbj");
    // eta_ttbj->SetLineColor(5);
    // eta_ttbj->SetLineWidth(2);
    // eta_ttbj->SetLineStyle(2);
    // eta_ttbj->Draw("LEP");

    // TLegend *leg2 = new TLegend(0.65,0.65,0.95,0.85);//Variables
    // leg2->AddEntry("eta_t","eta_t","lep");
    // leg2->AddEntry("eta_tb","eta_tb","lep");
    // leg2->AddEntry("eta_ttb","eta_ttb","lep");
    // leg2->AddEntry("eta_ttbj","eta_ttbj","lep");
    // leg2->AddEntry("eta_g","eta_g","lep");
    // leg2->Draw();
    
     
    // TCanvas *canv3 = new TCanvas (file_energy+"_"+file_mass+"_"+file_scale+" N3",file_energy+"_"+file_mass+"_"+file_scale+" N3",600,600);
    // canv3->Divide(2,1);
    // canv3->cd(1);
    // gPad->SetGridx();
    // gPad->SetGridy();

    // gN3_ATLAS->SetName("N3_ATLAS");
    // gN3_ATLAS->SetLineColor(2);
    // gN3_ATLAS->SetLineWidth(1);
    // gN3_ATLAS->SetLineStyle(1);
    // gN3_ATLAS->Draw("ALEP");

    // gN3LO_ATLAS->SetName("N3LO_ATLAS");
    // gN3LO_ATLAS->SetLineColor(6);
    // gN3LO_ATLAS->SetLineWidth(1);
    // gN3LO_ATLAS->SetLineStyle(1);
    // gN3LO_ATLAS->Draw("LEP");

    // gN3NLO_ATLAS->SetName("N3NLO_ATLAS");
    // gN3NLO_ATLAS->SetLineColor(4);
    // gN3NLO_ATLAS->SetLineWidth(1);
    // gN3NLO_ATLAS->SetLineStyle(1);
    // gN3NLO_ATLAS->Draw("LEP");

    // gN3_alphacorrected_ATLAS->SetName("N3_alphacorrected_ATLAS");
    // gN3_alphacorrected_ATLAS->SetLineColor(1);
    // gN3_alphacorrected_ATLAS->SetLineWidth(1);
    // gN3_alphacorrected_ATLAS->SetLineStyle(1);
    // gN3_alphacorrected_ATLAS->Draw("LEP");

    // TLegend *leg5 = new TLegend(0.65,0.65,0.95,0.85);//Variables
    // leg5->AddEntry("N3_ATLAS","N3 distribution","lep");
    // leg5->AddEntry("N3LO_ATLAS","N3 LO","lep");
    // leg5->AddEntry("N3NLO_ATLAS","N3 total - LO","lep");
    // leg5->AddEntry("N3_alphacorrected_ATLAS","N3 alpha corrections","lep");
    // leg5->Draw();

    // canv3->cd(2);
    // gPad->SetGridx();
    // gPad->SetGridy();

    // gB_ATLAS->SetName("B_ATLAS");
    // gB_ATLAS->SetLineColor(4);
    // gB_ATLAS->SetLineWidth(1);
    // gB_ATLAS->SetLineStyle(1);
    // gB_ATLAS->Draw("ALEP");

    // gA_ATLAS->SetName("A_ATLAS");
    // gA_ATLAS->SetLineColor(6);
    // gA_ATLAS->SetLineWidth(1);
    // gA_ATLAS->SetLineStyle(1);
    // gA_ATLAS->Draw("LEP");


    // TLegend *leg6 = new TLegend(0.65,0.65,0.95,0.85);//Variables
    // leg6->AddEntry("A_ATLAS","A= N3_{LO} / alphaS ^ 3","lep");
    // leg6->AddEntry("B_ATLAS","B= (N3_{NLO}-N3_{LO}) / alphaS ^ 4","lep");
    // leg6->Draw();


    // TCanvas *canv4 = new TCanvas (file_energy+"_"+file_mass+"_"+file_scale+" n3",file_energy+"_"+file_mass+"_"+file_scale+" n3",600,600);
    // canv4->cd(1);
    // gPad->SetGridx();
    // gPad->SetGridy();

    // gn3_ATLAS->SetName("n3_ATLAS");
    // gn3_ATLAS->SetLineColor(2);
    // gn3_ATLAS->SetLineWidth(1);
    // gn3_ATLAS->SetLineStyle(1);
    // gn3_ATLAS->Draw("ALEP");

    // gn3_alphacorrected_ATLAS->SetName("n3_alphacorrected_ATLAS");
    // gn3_alphacorrected_ATLAS->SetLineColor(1);
    // gn3_alphacorrected_ATLAS->SetLineWidth(1);
    // gn3_alphacorrected_ATLAS->SetLineStyle(1);
    // gn3_alphacorrected_ATLAS->Draw("LEP");

    // gn3_approx_ATLAS->SetName("n3_approx_ATLAS");
    // gn3_approx_ATLAS->SetLineColor(2);
    // gn3_approx_ATLAS->SetLineWidth(2);
    // gn3_approx_ATLAS->SetLineStyle(2);
    // gn3_approx_ATLAS->Draw("LEP");

    // gn3_approx_alphacorrected_ATLAS->SetName("n3_approx_alphacorrected_ATLAS");
    // gn3_approx_alphacorrected_ATLAS->SetLineColor(1);
    // gn3_approx_alphacorrected_ATLAS->SetLineWidth(2);
    // gn3_approx_alphacorrected_ATLAS->SetLineStyle(2);
    // gn3_approx_alphacorrected_ATLAS->Draw("LEP");

    // TLegend *leg7 = new TLegend(0.65,0.65,0.95,0.85);//Variables
    // leg7->AddEntry("n3_ATLAS","n3 distribution","lep");
    // leg7->AddEntry("n3_alphacorrected_ATLAS","n3 alpha corrections","lep");
    // leg7->AddEntry("n3_approx_ATLAS","n3, approximated","lep");
    // leg7->AddEntry("n3_approx_alphacorrected_ATLAS","n3 approximated, alpha corrections","lep");
    // leg7->Draw();


  }

  }

  } 



  //******************************************************************************************************************************************************
  //******************************************************************************************************************************************************

  /*int main()
    {
    plot_pythia_R3();
    }*/


 
  
  
