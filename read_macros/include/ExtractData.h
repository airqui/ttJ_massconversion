//#include "ttyctrl.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <stdio.h>
#include <algorithm>

using namespace std;

double data[300][300][3]={0.};
float alphasNLO=0.;
int first=0;

class Parser {
public:
  int hcount,lcount;//, itcount;
private:
  ifstream in;
  string filename;
  // Everything before this tag is ignored when parsing the file:
  string start;   
  // Everything after this tag is ignored when parsing the file: 
  string end;     
  // Histogram we want to extract: 
  string histname;
  

  int findstart(){
    // Read the file line-by-line until we find the start tag:
    string line;
    while ( !in.eof() ){
      getline(in,line);
      if(first==0) {
	if ( line.find("#  Standard Model Parameters:") != string::npos ) {
	  cout<<"# -------------------------------------------------------------"<<endl;
	  cout<<"#  Standard Model Parameters: "<<endl;
	  int inside=0;
	  while(inside<35){
	    getline(in,line);
	    if(inside==15) {
	      int n = line.length(); 
	      char char_array[n + 1]; 
	      std::strcpy(char_array, line.c_str());
	      std::sscanf(char_array,"%*s %*s %*s %f",&alphasNLO);
	    }     
	    inside++;
	  }
	  first=1;
 	}
      }
      
      if ( line.find(start) != string::npos ) 
	return 0;
    }
    return -1;
  }

  void parse(){
    hcount=0;
    string line;
        
    if ( findstart() ){
      cout << "Cannot find start tag when parsing: " << filename << endl;
      cout << "Abort program" << endl;
      exit(1);
    }
    
    while( !in.eof() ){
      getline(in,line);
      if ( line.find(end) != string::npos ){
	break;
      }


      /*  if ( read_cross == true && line.find("#  ITERATION NO  ") != string::npos ) {
	int n = line.length(); 
	char char_array[n + 1]; 
	std::strcpy(char_array, line.c_str());
	int i=0;
	string str[20];
	std::sscanf(char_array,"#  ITERATION NO   %*i.   INTEGRAL = %f",&cross[itcount]);
	cout<<itcount<<" "<<cross[itcount]<<endl;
	itcount++;
	}*/
      
      //      if ( line.find("# HISTSTART: " + histname) != string::npos ){
      if (  (line.find("# HISTSTART: " + histname) != string::npos)
	    && ( ("# HISTSTART: " + histname).length() == line.length() ) )  {
	lcount=0;
	int inside=1;
	while(inside){
	  getline(in,line);
	  if ( line.find("# HISTEND") != string::npos ){
	    inside=0;
	    break;
	  }
	  // cout << "-- "<< hcount << "--"<< line << endl;
	  stringstream(line) >> data[hcount][lcount][0]
			     >> data[hcount][lcount][1]
			     >> data[hcount][lcount][2];
	  lcount++;
	}
	hcount++;
      }
    }
  }

public:
  Parser(string filename_, string start_, string end_, string histname_) :
    filename(filename_), start(start_), end(end_),  histname(histname_){
    
    in.open(filename.c_str());

    if (in.is_open() != 1){
      cout << "Cannot open data file " << filename << endl;
      exit(1);
    } else {
#ifdef DEBUG      
      cout << "Processing " << filename << "..." << endl;
#endif
    }
    parse();
  };

};




/*int main(){
  string hnames_old[] = {"n3_12", "n3ttbar_12", "n3ttbar_24", "n3_8_opt",
		     "n3ttbar_8_opt", "n3_6_opt", "n3ttbar_6_opt"};
  string hnames[] = {"n3_12_pt30","n3_12_pt50","n3_12_pt75","n3_12_pt100","n3_24_pt30","n3_24_pt50","n3_24_pt75","n3_24_pt100"};
  
  string prefix = "/home/irles/ownCloudCNRS/ttJ/ttJ_massconversion_bk2/output_202008/14TeV_CT10_mt170_mu1_pt30_";

  double bwidth7TeV[] = {0.25, 0.075, 0.1, 0.1, 0.150,0.325};
  double bwidth8TeV[] = {0.25, 0.075, 0.1, 0.1, 0.150, 0.05, 0.05,0.225};

  double bwidth_12[] = {-0.1,0.0,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0,1.1};
  double bwidth_24[] = {-0.1,-0.05,0.0,05,0.1,0.15,0.2,0.25,0.3,0.35,0.4,0.45,0.5,0.55,0.6,0.65,0.7,0.75,0.8,0.85,0.9,0.95,1.0,1.05,1.1};

    
  //  CombineData(prefix,hnames[6]);
  for (int i = 0; i<sizeof(hnames)/sizeof(string); i++){
    if ( hnames[i].find("_12_") != string::npos){
      CombineData(prefix,hnames[i],bwidth_12);
    }
    if ( hnames[i].find("_24_") != string::npos){
      CombineData(prefix,hnames[i],bwidth_24);
    }
  }

  }*/
