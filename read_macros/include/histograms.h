

using namespace std;

double bwidth_12=0.1;
double bwidth_24=0.05;


double bwidth_ATLAS7TeV[] = {0.25, 0.075, 0.1, 0.1, 0.150,0.325};
double bwidth_ATLAS8TeV[] = {0.25, 0.075, 0.1, 0.1, 0.150, 0.05, 0.05,0.225};

double bwidth_CMS13TeV[] = {0.18, 0.04, 0.05, 0.05, 0.06, 0.07,0.08, 0.09, 0.09, 0.29};
double bwidth_CMS13TeV_b2[] = {0.185, 0.05, 0.05, 0.05, 0.055, 0.06, 0.07, 0.1, 0.09, 0.29};


//Including CMS
string hnames[] = {"n3_ATLAS7TeV_pt30","n3_ATLAS7TeV_pt50","n3_ATLAS7TeV_pt75","n3_ATLAS7TeV_pt100",
		   "n3_ATLAS8TeV_pt30","n3_ATLAS8TeV_pt50","n3_ATLAS8TeV_pt75","n3_ATLAS8TeV_pt100",
		   "n3_12_pt30","n3_12_pt50","n3_12_pt75","n3_12_pt100",
		   "n3_24_pt30","n3_24_pt50","n3_24_pt75","n3_24_pt100",
		   "n3_CMS13TeV_pt30","n3_CMS13TeV_pt50","n3_CMS13TeV_pt75","n3_CMS13TeV_pt100",
		   "n3_CMS13TeV_pt30_eta2p4","n3_CMS13TeV_pt50_eta2p4","n3_CMS13TeV_pt75_eta2p4","n3_CMS13TeV_pt100_eta2p4",
		   "n3_CMS13TeV_b2_pt30","n3_CMS13TeV_b2_pt50","n3_CMS13TeV_b2_pt75","n3_CMS13TeV_b2_pt100",
                   "n3_CMS13TeV_b2_pt30_eta2p4","n3_CMS13TeV_b2_pt50_eta2p4","n3_CMS13TeV_b2_pt75_eta2p4","n3_CMS13TeV_b2_pt100_eta2p4"};
		   

//Not including CMS
//string hnames[] = {"n3_ATLAS7TeV_pt30","n3_ATLAS7TeV_pt50","n3_ATLAS7TeV_pt75","n3_ATLAS7TeV_pt100","n3_ATLAS8TeV_pt30","n3_ATLAS8TeV_pt50","n3_ATLAS8TeV_pt75","n3_ATLAS8TeV_pt100","n3_12_pt30","n3_12_pt50","n3_12_pt75","n3_12_pt100","n3_24_pt30","n3_24_pt50","n3_24_pt75","n3_24_pt100"};
