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



std::vector<TString> samples(TString file_mass, TString file_pdf, TString file_scale, TString order="NLO"){

  std::vector<TString> output;

  TString file_string_0, file_string_1, file_string_2, file_string_3, file_string_4;
  TString file_string_5, file_string_6, file_string_7, file_string_8, file_string_9;
  TString file_string_10, file_string_11, file_string_12, file_string_13, file_string_14;
  TString file_string_15, file_string_16, file_string_17, file_string_18, file_string_19;
  TString file_string_20, file_string_21, file_string_22, file_string_23, file_string_24, file_string_25;

  //   if(file_mass=="mt161" || file_mass=="mt163" || file_mass=="mt165" ||  file_mass=="mt167" || file_mass=="mt168"  || file_mass=="mt169"|| file_mass=="mt170"  ){

    if( file_pdf=="MSTW2008nlo" || file_pdf=="NNPDF10"){
      file_string_0="../../NLOmtpole/results_"+file_pdf+"/dist."+file_mass+"_"+file_pdf+"_"+file_scale+"_pt50_10000.born_gg";
      file_string_1="../../NLOmtpole/results_"+file_pdf+"/dist."+file_mass+"_"+file_pdf+"_"+file_scale+"_pt50_10000.born_qqb";
      file_string_2="../../NLOmtpole/results_"+file_pdf+"/dist."+file_mass+"_"+file_pdf+"_"+file_scale+"_pt50_10000.born_qg";
      file_string_3="../../NLOmtpole/results_"+file_pdf+"/dist."+file_mass+"_"+file_pdf+"_"+file_scale+"_pt50_10000.born_gqb";
      
      file_string_4="../../NLOmtpole/results_"+file_pdf+"/dist."+file_mass+"_"+file_pdf+"_"+file_scale+"_pt50_10000.virtual_gg";
      file_string_5="../../NLOmtpole/results_"+file_pdf+"/dist."+file_mass+"_"+file_pdf+"_"+file_scale+"_pt50_10000.virtual_qqb";
      file_string_6="../../NLOmtpole/results_"+file_pdf+"/dist."+file_mass+"_"+file_pdf+"_"+file_scale+"_pt50_10000.virtual_qg";
      file_string_7="../../NLOmtpole/results_"+file_pdf+"/dist."+file_mass+"_"+file_pdf+"_"+file_scale+"_pt50_10000.virtual_gqb";
      
      file_string_8="../../NLOmtpole/results_"+file_pdf+"/dist."+file_mass+"_"+file_pdf+"_"+file_scale+"_pt50_10000.real_proc0";
      file_string_9="../../NLOmtpole/results_"+file_pdf+"/dist."+file_mass+"_"+file_pdf+"_"+file_scale+"_pt50_10000.real_proc1";
      file_string_10="../../NLOmtpole/results_"+file_pdf+"/dist."+file_mass+"_"+file_pdf+"_"+file_scale+"_pt50_10000.real_proc3";
      file_string_11="../../NLOmtpole/results_"+file_pdf+"/dist."+file_mass+"_"+file_pdf+"_"+file_scale+"_pt50_10000.real_proc6";
      file_string_12="../../NLOmtpole/results_"+file_pdf+"/dist."+file_mass+"_"+file_pdf+"_"+file_scale+"_pt50_10000.real_proc7";
      file_string_13="../../NLOmtpole/results_"+file_pdf+"/dist."+file_mass+"_"+file_pdf+"_"+file_scale+"_pt50_10000.real_proc8";
      file_string_14="../../NLOmtpole/results_"+file_pdf+"/dist."+file_mass+"_"+file_pdf+"_"+file_scale+"_pt50_10000.real_proc9";
      file_string_15="../../NLOmtpole/results_"+file_pdf+"/dist."+file_mass+"_"+file_pdf+"_"+file_scale+"_pt50_10000.real_proc11";
      file_string_16="../../NLOmtpole/results_"+file_pdf+"/dist."+file_mass+"_"+file_pdf+"_"+file_scale+"_pt50_10000.real_proc13";
      file_string_17="../../NLOmtpole/results_"+file_pdf+"/dist."+file_mass+"_"+file_pdf+"_"+file_scale+"_pt50_10000.real_proc14";
      file_string_18="../../NLOmtpole/results_"+file_pdf+"/dist."+file_mass+"_"+file_pdf+"_"+file_scale+"_pt50_10000.real_proc15";
      file_string_19="../../NLOmtpole/results_"+file_pdf+"/dist."+file_mass+"_"+file_pdf+"_"+file_scale+"_pt50_10000.real_proc17";
      
      file_string_20="../../NLOmtpole/results_"+file_pdf+"/dist."+file_mass+"_"+file_pdf+"_"+file_scale+"_pt50_10000.subtractions_proc18";
      file_string_21="../../NLOmtpole/results_"+file_pdf+"/dist."+file_mass+"_"+file_pdf+"_"+file_scale+"_pt50_10000.subtractions_proc20";
      file_string_22="../../NLOmtpole/results_"+file_pdf+"/dist."+file_mass+"_"+file_pdf+"_"+file_scale+"_pt50_10000.subtractions_proc21";
      file_string_23="../../NLOmtpole/results_"+file_pdf+"/dist."+file_mass+"_"+file_pdf+"_"+file_scale+"_pt50_10000.subtractions_proc24";
    }

  if(  file_pdf=="NNPDF10" && file_mass=="mt169" ){
      file_string_0="../../NLOmtpole/results_"+file_pdf+"/dist."+file_mass+"_"+file_pdf+"_"+file_scale+"_pt50_25000.born_gg";
      file_string_1="../../NLOmtpole/results_"+file_pdf+"/dist."+file_mass+"_"+file_pdf+"_"+file_scale+"_pt50_25000.born_qqb";
      file_string_2="../../NLOmtpole/results_"+file_pdf+"/dist."+file_mass+"_"+file_pdf+"_"+file_scale+"_pt50_25000.born_qg";
      file_string_3="../../NLOmtpole/results_"+file_pdf+"/dist."+file_mass+"_"+file_pdf+"_"+file_scale+"_pt50_25000.born_gqb";
      
      file_string_4="../../NLOmtpole/results_"+file_pdf+"/dist."+file_mass+"_"+file_pdf+"_"+file_scale+"_pt50_10000.virtual_gg";
      file_string_5="../../NLOmtpole/results_"+file_pdf+"/dist."+file_mass+"_"+file_pdf+"_"+file_scale+"_pt50_25000.virtual_qqb";
      file_string_6="../../NLOmtpole/results_"+file_pdf+"/dist."+file_mass+"_"+file_pdf+"_"+file_scale+"_pt50_25000.virtual_qg";
      file_string_7="../../NLOmtpole/results_"+file_pdf+"/dist."+file_mass+"_"+file_pdf+"_"+file_scale+"_pt50_25000.virtual_gqb";
      
      file_string_8="../../NLOmtpole/results_"+file_pdf+"/dist."+file_mass+"_"+file_pdf+"_"+file_scale+"_pt50_10000.real_proc0";
      file_string_9="../../NLOmtpole/results_"+file_pdf+"/dist."+file_mass+"_"+file_pdf+"_"+file_scale+"_pt50_25000.real_proc1";
      file_string_10="../../NLOmtpole/results_"+file_pdf+"/dist."+file_mass+"_"+file_pdf+"_"+file_scale+"_pt50_10000.real_proc3";
      file_string_11="../../NLOmtpole/results_"+file_pdf+"/dist."+file_mass+"_"+file_pdf+"_"+file_scale+"_pt50_25000.real_proc6";
      file_string_12="../../NLOmtpole/results_"+file_pdf+"/dist."+file_mass+"_"+file_pdf+"_"+file_scale+"_pt50_25000.real_proc7";
      file_string_13="../../NLOmtpole/results_"+file_pdf+"/dist."+file_mass+"_"+file_pdf+"_"+file_scale+"_pt50_25000.real_proc8";
      file_string_14="../../NLOmtpole/results_"+file_pdf+"/dist."+file_mass+"_"+file_pdf+"_"+file_scale+"_pt50_25000.real_proc9";
      file_string_15="../../NLOmtpole/results_"+file_pdf+"/dist."+file_mass+"_"+file_pdf+"_"+file_scale+"_pt50_25000.real_proc11";
      file_string_16="../../NLOmtpole/results_"+file_pdf+"/dist."+file_mass+"_"+file_pdf+"_"+file_scale+"_pt50_25000.real_proc13";
      file_string_17="../../NLOmtpole/results_"+file_pdf+"/dist."+file_mass+"_"+file_pdf+"_"+file_scale+"_pt50_25000.real_proc14";
      file_string_18="../../NLOmtpole/results_"+file_pdf+"/dist."+file_mass+"_"+file_pdf+"_"+file_scale+"_pt50_25000.real_proc15";
      file_string_19="../../NLOmtpole/results_"+file_pdf+"/dist."+file_mass+"_"+file_pdf+"_"+file_scale+"_pt50_25000.real_proc17";
      
      file_string_20="../../NLOmtpole/results_"+file_pdf+"/dist."+file_mass+"_"+file_pdf+"_"+file_scale+"_pt50_25000.subtractions_proc18";
      file_string_21="../../NLOmtpole/results_"+file_pdf+"/dist."+file_mass+"_"+file_pdf+"_"+file_scale+"_pt50_25000.subtractions_proc20";
      file_string_22="../../NLOmtpole/results_"+file_pdf+"/dist."+file_mass+"_"+file_pdf+"_"+file_scale+"_pt50_25000.subtractions_proc21";
      file_string_23="../../NLOmtpole/results_"+file_pdf+"/dist."+file_mass+"_"+file_pdf+"_"+file_scale+"_pt50_25000.subtractions_proc24";
    }



  output.push_back(file_string_0);
  output.push_back(file_string_1);
  output.push_back(file_string_2);
  output.push_back(file_string_3);
  if(order=="NLO") {
    output.push_back(file_string_4);
    output.push_back(file_string_5);
    output.push_back(file_string_6);
    output.push_back(file_string_7);
    output.push_back(file_string_8);
    output.push_back(file_string_9);
    output.push_back(file_string_10);
    output.push_back(file_string_11);
    output.push_back(file_string_12);
    output.push_back(file_string_13);
    output.push_back(file_string_14);
    output.push_back(file_string_15);
    output.push_back(file_string_16);
    output.push_back(file_string_17);
    output.push_back(file_string_18);
    output.push_back(file_string_19);
    output.push_back(file_string_20);
    output.push_back(file_string_21);
    output.push_back(file_string_22);
    output.push_back(file_string_23);
    output.push_back(file_string_24);
    output.push_back(file_string_25);
    cout<<" You are reading all NLO processes, samples.h " << endl;
  }
  return output;
}



std::vector<TString> samples_LO(TString file_mass, TString file_pdf, TString file_scale){

  std::vector<TString> output;

  TString file_string_0, file_string_1, file_string_2, file_string_3;

  file_string_0="dist.LO."+file_mass+"_"+file_pdf+"_"+file_scale+"_pt50_10000.born_gg";
  file_string_1="dist.LO."+file_mass+"_"+file_pdf+"_"+file_scale+"_pt50_10000.born_qqb";
  file_string_2="dist.LO."+file_mass+"_"+file_pdf+"_"+file_scale+"_pt50_10000.born_qg";
  file_string_3="dist.LO."+file_mass+"_"+file_pdf+"_"+file_scale+"_pt50_10000.born_gqb";

  output.push_back(file_string_0);
  output.push_back(file_string_1);
  output.push_back(file_string_2);
  output.push_back(file_string_3);

  return output;
}

