#include "Plots.h"

void Sens_scale_pt(TString pdf="CT10",TString energy="13TeV", float mass=170, int interval=4, TString ptsim="pt30", TString order="", TString title="n3_24_", TString scheme="pole"){

  TString folder_root="rootfiles_CMS";

  TString folder= "../../"+folder_root+"/";

  TString mt="_mt";
  if(scheme == "running" ) mt="_mtrun";
   //---------------------------------------------------------------------------------------------------------
  // pt30
  //read reference value + scale variations

  TString s_mass, s_mass_up, s_mass_down;

  if( (mass - (int)mass) >0 ) {
    s_mass = TString::Format("%.1f",mass);
    s_mass_up=TString::Format("%.1f",mass+interval);
    s_mass_down=TString::Format("%.1f",mass-interval);
  } else {
    s_mass = TString::Format("%i",mass);
    s_mass_up=TString::Format("%i",mass+interval);
    s_mass_down=TString::Format("%i",mass-interval);
  }
  
  TString filename = folder+energy+"_"+pdf+mt+s_mass+"_"+ptsim+"_mu1"+".root";
  TGraphErrors *gref_pt30 = readGraph(filename,title+"pt30"+order,false);
  TGraphErrors *gref_StatErrors_pt30 = readGraphStatErrors(filename,title+"pt30"+order);

  filename = folder+energy+"_"+pdf+mt+s_mass+"_"+ptsim+"_mu2.root";
  TGraphErrors *gref_up_pt30 = readGraph(filename,title+"pt30"+order,false);

  filename = folder+energy+"_"+pdf+mt+s_mass+"_"+ptsim+"_mu0.5.root";
  TGraphErrors *gref_down_pt30 = readGraph(filename,title+"pt30"+order,false);

  TGraphErrors *gref_errors_pt30 = GraphErrors3(gref_pt30,gref_up_pt30,gref_down_pt30);
  TGraphErrors *errors_pt30 = Errors3(gref_pt30,gref_up_pt30,gref_down_pt30);

  //read other mass reference values
  filename = folder+energy+"_"+pdf+mt+s_mass_up+"_"+ptsim+"_mu1"+".root";
  TGraphErrors *g_up_pt30 = readGraph(filename,title+"pt30"+order,false);
  filename = folder+energy+"_"+pdf+mt+s_mass_down+"_"+ptsim+"_mu1"+".root";
  TGraphErrors *g_down_pt30 = readGraph(filename,title+"pt30"+order,false);
  
  //---------------------------------------------------------------------------------------------------------
  // pt50
  //read reference value + scale variations
  filename = folder+energy+"_"+pdf+mt+s_mass+"_"+ptsim+"_mu1"+".root";
  TGraphErrors *gref_pt50 = readGraph(filename,title+"pt50"+order,false);
  TGraphErrors *gref_StatErrors_pt50 = readGraphStatErrors(filename,title+"pt50"+order);

  filename = folder+energy+"_"+pdf+mt+s_mass+"_"+ptsim+"_mu2.root";
  TGraphErrors *gref_up_pt50 = readGraph(filename,title+"pt50"+order,false);

  filename = folder+energy+"_"+pdf+mt+s_mass+"_"+ptsim+"_mu0.5.root";
  TGraphErrors *gref_down_pt50 = readGraph(filename,title+"pt50"+order,false);

  TGraphErrors *gref_errors_pt50 = GraphErrors3(gref_pt50,gref_up_pt50,gref_down_pt50);
  TGraphErrors *errors_pt50 = Errors3(gref_pt50,gref_up_pt50,gref_down_pt50);

  //read other mass reference values
  filename = folder+energy+"_"+pdf+mt+s_mass_up+"_"+ptsim+"_mu1"+".root";
  TGraphErrors *g_up_pt50 = readGraph(filename,title+"pt50"+order,false);
  filename = folder+energy+"_"+pdf+mt+s_mass_down+"_"+ptsim+"_mu1"+".root";
  TGraphErrors *g_down_pt50 = readGraph(filename,title+"pt50"+order,false);


  //---------------------------------------------------------------------------------------------------------
  // pt75
  //read reference value + scale variations
  filename = folder+energy+"_"+pdf+mt+s_mass+"_"+ptsim+"_mu1"+".root";
  TGraphErrors *gref_pt75 = readGraph(filename,title+"pt75"+order,false);
  TGraphErrors *gref_StatErrors_pt75 = readGraphStatErrors(filename,title+"pt75"+order);

  filename = folder+energy+"_"+pdf+mt+s_mass+"_"+ptsim+"_mu2.root";
  TGraphErrors *gref_up_pt75 = readGraph(filename,title+"pt75"+order,false);

  filename = folder+energy+"_"+pdf+mt+s_mass+"_"+ptsim+"_mu0.5.root";
  TGraphErrors *gref_down_pt75 = readGraph(filename,title+"pt75"+order,false);

  TGraphErrors *gref_errors_pt75 = GraphErrors3(gref_pt75,gref_up_pt75,gref_down_pt75);
  TGraphErrors *errors_pt75 = Errors3(gref_pt75,gref_up_pt75,gref_down_pt75);

  //read other mass reference values
  filename = folder+energy+"_"+pdf+mt+s_mass_up+"_"+ptsim+"_mu1"+".root";
  TGraphErrors *g_up_pt75 = readGraph(filename,title+"pt75"+order,false);
  filename = folder+energy+"_"+pdf+mt+s_mass_down+"_"+ptsim+"_mu1"+".root";
  TGraphErrors *g_down_pt75 = readGraph(filename,title+"pt75"+order,false);

  
  //---------------------------------------------------------------------------------------------------------
  // pt100
  //read reference value + scale variations
  filename = folder+energy+"_"+pdf+mt+s_mass+"_"+ptsim+"_mu1"+".root";
  TGraphErrors *gref_pt100 = readGraph(filename,title+"pt100"+order,false);
  TGraphErrors *gref_StatErrors_pt100 = readGraphStatErrors(filename,title+"pt100"+order);

  filename = folder+energy+"_"+pdf+mt+s_mass+"_"+ptsim+"_mu2.root";
  TGraphErrors *gref_up_pt100 = readGraph(filename,title+"pt100"+order,false);

  filename = folder+energy+"_"+pdf+mt+s_mass+"_"+ptsim+"_mu0.5.root";
  TGraphErrors *gref_down_pt100 = readGraph(filename,title+"pt100"+order,false);

  TGraphErrors *gref_errors_pt100 = GraphErrors3(gref_pt100,gref_up_pt100,gref_down_pt100);
  TGraphErrors *errors_pt100 = Errors3(gref_pt100,gref_up_pt100,gref_down_pt100);

  /// read other mass reference values

  filename = folder+energy+"_"+pdf+mt+s_mass_up+"_"+ptsim+"_mu1"+".root";
  TGraphErrors *g_up_pt100 = readGraph(filename,title+"pt100"+order,false);
  filename = folder+energy+"_"+pdf+mt+s_mass_down+"_"+ptsim+"_mu1"+".root";
  TGraphErrors *g_down_pt100 = readGraph(filename,title+"pt100"+order,false);

  /// --------------------------------------------------------------------------------------------------------
  /// --------------------------------------------------------------------------------------------------------

  std::vector<TGraphErrors*> dist_vector;
  dist_vector.push_back(gref_pt30);
  dist_vector.push_back(gref_pt50);
  dist_vector.push_back(gref_pt75);
  dist_vector.push_back(gref_pt100);

  std::vector<TString> label_vector;
  label_vector.push_back("pt>30 GeV");
  label_vector.push_back("pt>50 GeV");
  label_vector.push_back("pt>75 GeV");
  label_vector.push_back("pt>100 GeV");
  
  DrawVector(dist_vector,"distr_canvas",label_vector,TString::Format("#Rgothic(mt=%i GeV,pole,mu=1)",mass), "#rho_{s}",scheme,"Binning 0.05");
  
 //--------

  std::vector<TGraphErrors*> errors_vector;
  errors_vector.push_back(errors_pt30);
  errors_vector.push_back(errors_pt50);
  errors_vector.push_back(errors_pt75);
  errors_vector.push_back(errors_pt100);


  DrawVector(errors_vector,"deltamu_canvas",label_vector,"#Delta #Rgothic(scale) /#Rgothic", "#rho_{s}",scheme,"Binning 0.05");

  //--------
  TGraphErrors *sens_pt30 = Sens3(gref_errors_pt30,g_up_pt30,g_down_pt30,mass,interval);
  TGraphErrors *sens_pt50 = Sens3(gref_errors_pt50,g_up_pt50,g_down_pt50,mass,interval);
  TGraphErrors *sens_pt75 = Sens3(gref_errors_pt75,g_up_pt75,g_down_pt75,mass,interval);
  TGraphErrors *sens_pt100 = Sens3(gref_errors_pt100,g_up_pt100,g_down_pt100,mass,interval);

  std::vector<TGraphErrors*> sens_vector;
  sens_vector.push_back(sens_pt30);
  sens_vector.push_back(sens_pt50);
  sens_vector.push_back(sens_pt75);
  sens_vector.push_back(sens_pt100);


  DrawVector(sens_vector,"sens_canvas",label_vector,"S #times m_{top}(173) [GeV]", "#rho_{s}",scheme,"Binning 0.05");

  //--------
  TGraphErrors *senserror_pt30 = SensError3(gref_errors_pt30,g_up_pt30,g_down_pt30,mass,interval);
  TGraphErrors *senserror_pt50 = SensError3(gref_errors_pt50,g_up_pt50,g_down_pt50,mass,interval);
  TGraphErrors *senserror_pt75 = SensError3(gref_errors_pt75,g_up_pt75,g_down_pt75,mass,interval);
  TGraphErrors *senserror_pt100 = SensError3(gref_errors_pt100,g_up_pt100,g_down_pt100,mass,interval);

  std::vector<TGraphErrors*> senserror_vector;
  senserror_vector.push_back(senserror_pt30);
  senserror_vector.push_back(senserror_pt50);
  senserror_vector.push_back(senserror_pt75);
  senserror_vector.push_back(senserror_pt100);


  DrawVector(senserror_vector,"senserror_canvas",label_vector,"#Delta(scale) #times S^{-1} [GeV]", "#rho_{s}",scheme,"Binning 0.05");

   //--------
  TGraphErrors *sensStatError_pt30 = SensError3(gref_StatErrors_pt30,g_up_pt30,g_down_pt30,mass,interval);
  TGraphErrors *sensStatError_pt50 = SensError3(gref_StatErrors_pt50,g_up_pt50,g_down_pt50,mass,interval);
  TGraphErrors *sensStatError_pt75 = SensError3(gref_StatErrors_pt75,g_up_pt75,g_down_pt75,mass,interval);
  TGraphErrors *sensStatError_pt100 = SensError3(gref_StatErrors_pt100,g_up_pt100,g_down_pt100,mass,interval);

  std::vector<TGraphErrors*> sensStatError_vector;
  sensStatError_vector.push_back(sensStatError_pt30);
  sensStatError_vector.push_back(sensStatError_pt50);
  sensStatError_vector.push_back(sensStatError_pt75);
  sensStatError_vector.push_back(sensStatError_pt100);


  DrawVector(sensStatError_vector,"sensStatError_canvas",label_vector,"#Delta(stats - naive) #times S^{-1} [GeV]", "#rho_{s}",scheme,"Binning 0.05");
 

}


void Sens_scale_bin(TString pdf="CT10",TString energy="13TeV", float mass=170, int interval=4, TString ptsim="pt30", TString order="", TString title="n3_",  TString pt="50", TString scheme="pole"){

  TString folder_root="rootfiles_CMS";

  TString folder= "../../"+folder_root+"/";
  TString mt="_mt";
  if(scheme == "running" ) mt="_mtrun";


  TString s_mass, s_mass_up, s_mass_down;

  if( (mass - (int)mass) >0 ) {
    s_mass = TString::Format("%.1f",mass);
    s_mass_up=TString::Format("%.1f",mass+interval);
    s_mass_down=TString::Format("%.1f",mass-interval);
  } else {
    s_mass = TString::Format("%i",mass);
    s_mass_up=TString::Format("%i",mass+interval);
    s_mass_down=TString::Format("%i",mass-interval);
  }
   //---------------------------------------------------------------------------------------------------------
  // bin CMS
  //read reference value + scale variations
  TString filename = folder+energy+"_"+pdf+mt+s_mass+"_"+ptsim+"_mu1"+".root";
  TGraphErrors *gref_CMS = readGraph(filename,title+"CMS13TeV_pt"+pt);
  TGraphErrors *gref_StatErrors_CMS = readGraphStatErrors(filename,title+"CMS13TeV_pt"+pt);

  filename = folder+energy+"_"+pdf+mt+s_mass+"_"+ptsim+"_mu2.root";
  TGraphErrors *gref_up_CMS = readGraph(filename,title+"CMS13TeV_pt"+pt);

  filename = folder+energy+"_"+pdf+mt+s_mass+"_"+ptsim+"_mu0.5.root";
  TGraphErrors *gref_down_CMS = readGraph(filename,title+"CMS13TeV_pt"+pt);
  
  TGraphErrors *gref_errors_CMS = GraphErrors3(gref_CMS,gref_up_CMS,gref_down_CMS);
  TGraphErrors *errors_CMS = Errors3(gref_CMS,gref_up_CMS,gref_down_CMS);

  //read other mass reference values
  filename = folder+energy+"_"+pdf+mt+s_mass_up+"_"+ptsim+"_mu1"+".root";
  TGraphErrors *g_up_CMS = readGraph(filename,title+"CMS13TeV_pt"+pt);
  filename = folder+energy+"_"+pdf+mt+s_mass_down+"_"+ptsim+"_mu1"+".root";
  TGraphErrors *g_down_CMS = readGraph(filename,title+"CMS13TeV_pt"+pt);
  
  
  //---------------------------------------------------------------------------------------------------------
  // bin 12
  //read reference value + scale variations
  filename = folder+energy+"_"+pdf+mt+s_mass+"_"+ptsim+"_mu1"+".root";
  TGraphErrors *gref_12 = readGraph(filename,title+"12_pt"+pt);
  TGraphErrors *gref_StatErrors_12 = readGraphStatErrors(filename,title+"12_pt"+pt);

  filename = folder+energy+"_"+pdf+mt+s_mass+"_"+ptsim+"_mu2.root";
  TGraphErrors *gref_up_12 = readGraph(filename,title+"12_pt"+pt);

  filename = folder+energy+"_"+pdf+mt+s_mass+"_"+ptsim+"_mu0.5.root";
  TGraphErrors *gref_down_12 = readGraph(filename,title+"12_pt"+pt);

  TGraphErrors *gref_errors_12 = GraphErrors3(gref_12,gref_up_12,gref_down_12);
  TGraphErrors *errors_12 = Errors3(gref_12,gref_up_12,gref_down_12);

  //read other mass reference values
  filename = folder+energy+"_"+pdf+mt+s_mass_up+"_"+ptsim+"_mu1"+".root";
  TGraphErrors *g_up_12 = readGraph(filename,title+"12_pt"+pt);
  filename = folder+energy+"_"+pdf+mt+s_mass_down+"_"+ptsim+"_mu1"+".root";
  TGraphErrors *g_down_12 = readGraph(filename,title+"12_pt"+pt);


  //---------------------------------------------------------------------------------------------------------
  // bin 24
  //read reference value + scale variations
  filename = folder+energy+"_"+pdf+mt+s_mass+"_"+ptsim+"_mu1"+".root";
  TGraphErrors *gref_24 = readGraph(filename,title+"24_pt"+pt);
  TGraphErrors *gref_StatErrors_24 = readGraphStatErrors(filename,title+"24_pt"+pt);

  filename = folder+energy+"_"+pdf+mt+s_mass+"_"+ptsim+"_mu2.root";
  TGraphErrors *gref_up_24 = readGraph(filename,title+"24_pt"+pt);

  filename = folder+energy+"_"+pdf+mt+s_mass+"_"+ptsim+"_mu0.5.root";
  TGraphErrors *gref_down_24 = readGraph(filename,title+"24_pt"+pt);

  TGraphErrors *gref_errors_24 = GraphErrors3(gref_24,gref_up_24,gref_down_24);
  TGraphErrors *errors_24 = Errors3(gref_24,gref_up_24,gref_down_24);

  //read other mass reference values
  filename = folder+energy+"_"+pdf+mt+s_mass_up+"_"+ptsim+"_mu1"+".root";
  TGraphErrors *g_up_24 = readGraph(filename,title+"24_pt"+pt);
  filename = folder+energy+"_"+pdf+mt+s_mass_down+"_"+ptsim+"_mu1"+".root";
  TGraphErrors *g_down_24 = readGraph(filename,title+"24_pt"+pt);
  
  std::vector<TGraphErrors*> dist_vector;
  dist_vector.push_back(gref_errors_CMS);
  dist_vector.push_back(gref_errors_12);
  dist_vector.push_back(gref_errors_24);

  std::vector<TString> label_vector;
  label_vector.push_back("CMS 13TeV binning");
  label_vector.push_back("0.1 binning");
  label_vector.push_back("0.05 binning");
  
  DrawVector(dist_vector,"distr_canvas",label_vector,TString::Format("#Rgothic(mt=%i GeV,pole,mu=1)",mass), "#rho_{s}",scheme,"pt>"+pt+" GeV");

   //--------

  std::vector<TGraphErrors*> errors_vector;
  errors_vector.push_back(errors_CMS);
  errors_vector.push_back(errors_12);
  errors_vector.push_back(errors_24);


  DrawVector(errors_vector,"deltamu_canvas",label_vector,"#Delta #Rgothic(scale) /#Rgothic", "#rho_{s}",scheme,"pt>"+pt+" GeV");

  //--------
  TGraphErrors *sens_CMS = Sens3(gref_errors_CMS,g_up_CMS,g_down_CMS,mass,interval);
  TGraphErrors *sens_12 = Sens3(gref_errors_12,g_up_12,g_down_12,mass,interval);
  TGraphErrors *sens_24 = Sens3(gref_errors_24,g_up_24,g_down_24,mass,interval);

  std::vector<TGraphErrors*> sens_vector;
  sens_vector.push_back(sens_CMS);
  sens_vector.push_back(sens_12);
  sens_vector.push_back(sens_24);

  DrawVector(sens_vector,"sens_canvas",label_vector,"S^{-1}", "#rho_{s}",scheme,"pt>"+pt+" GeV");
  //g_down_CMS->Draw("alp");
  
  //--------
  TGraphErrors *senserror_CMS = SensError3(gref_errors_CMS,g_up_CMS,g_down_CMS,mass,interval);
  TGraphErrors *senserror_12 = SensError3(gref_errors_12,g_up_12,g_down_12,mass,interval);
  TGraphErrors *senserror_24 = SensError3(gref_errors_24,g_up_24,g_down_24,mass,interval);

  std::vector<TGraphErrors*> senserror_vector;
  senserror_vector.push_back(senserror_CMS);
  senserror_vector.push_back(senserror_12);
  senserror_vector.push_back(senserror_24);


  DrawVector(senserror_vector,"senserror_canvas",label_vector,"#Delta(scale) #times S^{-1} [GeV]", "#rho_{s}",scheme,"pt>"+pt+" GeV");

   //--------
  TGraphErrors *sensStatError_CMS = SensError3(gref_StatErrors_CMS,g_up_CMS,g_down_CMS,mass,interval);
  TGraphErrors *sensStatError_12 = SensError3(gref_StatErrors_12,g_up_12,g_down_12,mass,interval);
  TGraphErrors *sensStatError_24 = SensError3(gref_StatErrors_24,g_up_24,g_down_24,mass,interval);

  std::vector<TGraphErrors*> sensStatError_vector;
  sensStatError_vector.push_back(sensStatError_CMS);
  sensStatError_vector.push_back(sensStatError_12);
  sensStatError_vector.push_back(sensStatError_24);


  DrawVector(sensStatError_vector,"sensStatError_canvas",label_vector,"#Delta(stats - naive) #times S^{-1} [GeV]", "#rho_{s}",scheme,"pt>"+pt+" GeV");
 

}
