 #include "../include/ExtractData.h"
#include "../include/histograms.h"

#include "TFile.h"
#include "TNtuple.h"
#include "TMath.h"
#include "TTree.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TH1F.h"
#include "TKey.h"
#include "TVectorD.h"

int SaveGraphs(string prefix, string hname, int nlines, double bwidth[], double lores[][3]){

  TFile *f1 = new  TFile(TString(prefix)+".root","UPDATE");

  TKey *key = f1->FindKey(TString(hname)+"_LO");
  if(key != 0) {
    cout<< " ERROR:   HISTOGRAM "<<hname <<" in ROOT FILE: "<<TString(prefix)<<".root ALREADY EXISTS  --> STOP !"<<endl;
    return 0;
  }
  
  TKey *key2 = f1->FindKey("alphas_over_pi");
  if (key2 == 0)  {
    //    cout<<" Write Alpha"<<endl;
    TVectorD *a = new TVectorD(1);
    a[0] = alphasNLO/TMath::Pi();
    a->Write("alphas_over_pi");
  }

  f1->cd();

 double x[100], ex[100], y[100], ey[100];


 // leading order cont.
 for(int i=0; i<nlines; i++) {
   x[i]=lores[i][0];
   ex[i]=bwidth[i]/2.;
   y[i]=lores[i][1];
   ey[i]=lores[i][2];
 }

 TGraphErrors *LO = new TGraphErrors(nlines,x,y,ex,ey);
 LO->SetName(TString(hname)+"_LO");
 LO->Write();


 f1->Close();
 
 return 1;
}

int SaveGraphs(string prefix, string hname, int nlines, double bwidth[], double lores[][3], double nlores[][3], double res[][3]){

  TFile *f1 = new  TFile(TString(prefix)+".root","UPDATE");

  TKey *key = f1->FindKey(TString(hname)+"_LO");
  if(key != 0) {
    cout<< " ERROR:   HISTOGRAM "<<hname <<" in ROOT FILE: "<<TString(prefix)<<".root ALREADY EXISTS  --> STOP !"<<endl;
    return 0;
  }
  TKey *key2 = f1->FindKey("alphas_over_pi");
  if (key2 == 0)  {
    //    cout<<" Write Alpha"<<endl;
    TVectorD *a = new TVectorD(1);
    a[0] = alphasNLO/TMath::Pi();
    a->Write("alphas_over_pi");
  }

  f1->cd();

 double x[300], ex[300], y[300], ey[300];


 // leading order cont.
 for(int i=0; i<nlines; i++) {
   x[i]=lores[i][0];
   ex[i]=bwidth[i]/2.;
   y[i]=lores[i][1];
   ey[i]=lores[i][2];
 }

 TGraphErrors *LO = new TGraphErrors(nlines,x,y,ex,ey);
 LO->SetName(TString(hname)+"_LO");
 LO->Write();

 //next leading order cont.
 for(int i=0; i<nlines; i++) {
   x[i]=nlores[i][0];
   ex[i]=bwidth[i]/2.;
   y[i]=nlores[i][1];
   ey[i]=nlores[i][2];
 }

 TGraphErrors *NLO = new TGraphErrors(nlines,x,y,ex,ey);
 NLO->SetName(TString(hname)+"_NLO");
 NLO->Write();


 //total
 for(int i=0; i<nlines; i++) {
   x[i]=res[i][0];
   ex[i]=bwidth[i]/2.;
   y[i]=res[i][1];
   ey[i]=res[i][2];
 }

 TGraphErrors *TOTAL = new TGraphErrors(nlines,x,y,ex,ey);
 TOTAL->SetName(TString(hname));
 TOTAL->Write();
 
 
 f1->Close();
 
 return 1;
}

int CombineData(string prefix, string hname, double bwidth[],string output, bool bool_NLO){

  string procs_lo[] = {"born_gg","born_gqb","born_qg","born_qqb"};
  string procs_nlo[] = {"virtual_gg_merged","virtual_gqb","virtual_qg","virtual_qqb",
			"subtractions_18","subtractions_20",
			"subtractions_21","subtractions_24",
			"real_0_merged","real_1","real_3_merged","real_6",
			"real_7","real_8","real_9","real_11",
			"real_13",
			"real_14","real_15", "real_17"};
  int nlines;
  double N;
  
  double lores[300][3]={0}, nlores[300][3]={0}, res[300][3]={0};

  /*
   * Combine LO processes...
   */
  for (int iproc=0; iproc<4;iproc++){
    Parser parser(prefix+procs_lo[iproc]+".log", "THERMALIZE STOP",
		  "# Final result",hname);

    nlines = parser.lcount;
    N = parser.hcount;
    double avg[300][3]={0.};
    for(int j=0;j<nlines;j++){
      avg[j][0] = data[0][j][0];
      for(int i=0;i<N ;i++){
	if(data[i][j][2]>0) {
	  double wt=1./(data[i][j][2]*data[i][j][2]);
	  avg[j][1] += data[i][j][1]*wt;
	  avg[j][2] += wt;
	}
      }

      if( avg[j][2] >0 ){
	avg[j][1] /= avg[j][2];//sumwt;
	avg[j][2] =1/avg[j][2];///= (1- sumwt2);
      } else{
	avg[j][1]=0;
	avg[j][2]=0;
      }
	
      lores[j][0] = avg[j][0];
      lores[j][1] += avg[j][1];
      lores[j][2] += avg[j][2];
    
    }
  
  }
  
  for(int j=0;j<nlines;j++){
    lores[j][2] = sqrt( lores[j][2] );
  }
  cout << "# HISTONAME: "
       << hname << endl;
  cout<< "# nbins: "
      << nlines <<endl;
  cout << "# LO contribution: " << endl;
    
  for(int j=0; j<nlines; j++){
    cout << lores[j][0]
	 << " " << lores[j][1] * bwidth[j]
	 << " " << lores[j][2] * bwidth[j] << endl;
  }

  if(bool_NLO== true) {
  
  /*
   * Combine NLO processes...
   */
    for (int iproc=0; iproc<20;iproc++){
      Parser parser(prefix+procs_nlo[iproc]+".log", "THERMALIZE STOP",
		  "# Final result",hname);
      double fac=1;
      if (procs_nlo[iproc].find("proc7") != string::npos){
	fac = 5.;
      }
      if (procs_nlo[iproc].find("proc13") != string::npos){
	fac = 4.;
      }
      nlines=parser.lcount;
      N = parser.hcount;
      double avg[300][3]={0.};
      for(int j=0;j<nlines;j++){
        avg[j][0] = data[0][j][0];
        for(int i=0;i<N;i++){
	  if(data[i][j][2]>0) {
	    double wt=1./(data[i][j][2]*data[i][j][2]);
	    avg[j][1] += data[i][j][1]*wt;
	    avg[j][2] += wt;
	  }
	}
      
	if( avg[j][2] >0 ){
	  avg[j][1] /= avg[j][2];
	  avg[j][2] = sqrt (1.0/avg[j][2]);
	} else{
	  avg[j][1]=0;
	  avg[j][2]=0;
	}
		
        nlores[j][0] = avg[j][0];
        nlores[j][1] += fac * avg[j][1];
        nlores[j][2] += fac * avg[j][2] * avg[j][2]; 
      }
       
    }
    
    for(int j=0;j<nlines;j++){
      nlores[j][2] = sqrt( nlores[j][2] );
    }

    cout << "# NLO contribution: " << endl;
    for(int j=0;j<nlines;j++){
      cout << nlores[j][0]
	   << " " << nlores[j][1] * bwidth[j]
	   << " " << nlores[j][2] * bwidth[j] << endl;
    }
    
    // Combine LO and NLO
    for(int j=0;j<nlines;j++){
      res[j][0] = lores[j][0];
      res[j][1] = lores[j][1] + nlores[j][1];
      res[j][2] = sqrt( lores[j][2]*lores[j][2]
			+ nlores[j][2]*nlores[j][2]);
    }
    cout << "# TOTAL: " << endl;
    
    for(int j=0;j<nlines;j++){
      cout << res[j][0]
	   << " " << res[j][1] * bwidth[j]
	   << " " << res[j][2] * bwidth[j] << endl;
    }
  cout << "########################## " << endl;

  return SaveGraphs(output, hname, nlines, bwidth, lores, nlores, res);
  } else {
    return SaveGraphs(output, hname, nlines, bwidth, lores);
  }
}

int CombineData(string prefix, string hname, double bwidth,string output, bool bool_order){

  double bwidth_array[300];
  for(int i=0; i<100; i++) bwidth_array[i]=bwidth;
  
  return CombineData(prefix, hname, bwidth_array,output,bool_order);

}

int main(int argc, char* argv[6]){

  std::cout << "## Running Histogram Merging " << std::endl;
  std::cout<<"## Number of arguments (all as strings): "<<argc<<std::endl;
  if(argc < 7)    {
    std::cout << "## Not enough arguments provided"<<std::endl;
    std::cout<<"## Expected arguments: input_folder Energy (i.e. LHC14) PDF pole_mass scale (i.e. 1,2,0.5) ptcut  order (LO or NLO)"<<" "<<argv[1]<<std::endl;
    return 0;
  }

  TString order=TString(argv[6]);
  if(order != "NLO" && order != "LO")    std::cout << "## Wrong order of the chose calcualtion: LO or NLO ?"<<std::endl;
  
  bool bool_NLO=true;
  if(order=="LO") bool_NLO=false;
  

  //  std::cout<<"## input_folder: "<<" "<<argv[1]<<std::endl;
  std::cout<<"## Energy "<<" "<<argv[1]<<std::endl;
  std::cout<<"## PDF "<<" "<<argv[2]<<std::endl;
  std::cout<<"## mtpole "<<" "<<argv[3]<<std::endl;
  std::cout<<"## scale "<<" "<<argv[4]<<std::endl;
  std::cout<<"## ptcut "<<" "<<argv[5]<<std::endl;
  std::cout<<"## order (LO or NLO) "<<" "<<argv[6]<<std::endl;

  string prefix = "../../ready/"+string(argv[1])+"_"+string(argv[2])+"/output/"+string(argv[1])+"_"+string(argv[2])+"_mt"+string(argv[3])+"_pt"+string(argv[5])+"_mu"+string(argv[4])+"_";
  string output = "../../ready/"+string(argv[1])+"_"+string(argv[2])+"/rootfiles/"+string(argv[1])+"_"+string(argv[2])+"_mt"+string(argv[3])+"_pt"+string(argv[5])+"_mu"+string(argv[4]);

  std::cout<<"## "<<prefix<<endl;

  int value=0;
  for (unsigned i = 0; i<sizeof(hnames)/sizeof(string); i++){
    if ( hnames[i].find("_ATLAS7TeV_") != string::npos){
      value=CombineData(prefix,hnames[i],bwidth_ATLAS7TeV,output,bool_NLO);
      if(value==0) return 0;
    }
    if ( hnames[i].find("_ATLAS8TeV_") != string::npos){
      value=CombineData(prefix,hnames[i],bwidth_ATLAS8TeV,output,bool_NLO);
      if(value==0) return 0;
    }
    if ( hnames[i].find("_12_") != string::npos){
      value=CombineData(prefix,hnames[i],bwidth_12,output,bool_NLO);
      if(value==0) return 0;
    }
    if ( hnames[i].find("_24_") != string::npos){
      value=CombineData(prefix,hnames[i],bwidth_24,output,bool_NLO);
      if(value==0) return 0;
    }
    if ( hnames[i].find("_CMS13TeV_b2") != string::npos){
      value=CombineData(prefix,hnames[i],bwidth_CMS13TeV_b2,output,bool_NLO);
      if(value==0) return 0;
    } else {
      if ( hnames[i].find("_CMS13TeV_") != string::npos){
	value=CombineData(prefix,hnames[i],bwidth_CMS13TeV,output,bool_NLO);
	if(value==0) return 0;
      }
    }

    
  }

}
