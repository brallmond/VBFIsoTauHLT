void PrintCounts(char* filename) { 

  TFile *_file0 = TFile::Open(filename);
  TTree* tree = (TTree*)_file0->Get("outTree");

  double nEvents = tree->Draw("nEvents", "nEvents>0", "goff");
  std::cout << nEvents << '\t' << "Events Skimmed" << '\n' << std::endl;

  // InclusiveVBF
  double passInclusiveVBFHLT = tree->Draw("nEvents", "passInclusiveVBFHLT>0", "goff");
  double passInclusiveVBFOff = tree->Draw("nEvents", "passInclusiveVBFOff>0", "goff");
  double passInclusiveVBFBoth = tree->Draw("nEvents", "passInclusiveVBFHLT>0 && passInclusiveVBFOff>0", "goff");

  // VBF2DT
  double passVBF2DTHLT = tree->Draw("nEvents", "passVBF2DTHLT>0", "goff");
  double passVBF2DTOff = tree->Draw("nEvents", "passVBF2DTOff>0", "goff");
  double passVBF2DTBoth = tree->Draw("nEvents", "passVBF2DTHLT>0 && passVBF2DTOff>0", "goff");

  double passVBF2DTOldL1HLT = tree->Draw("nEvents", "passVBF2DTOldL1>0", "goff");
  double passVBF2DTOldL1Both = tree->Draw("nEvents", "passVBF2DTOldL1>0 && passVBF2DTOff>0", "goff");
 
  // VBF2DT Loose
  double passVBF2DTLooseHLT = tree->Draw("nEvents", "passVBF2DTLooseHLT>0", "goff");
  double passVBF2DTLooseBoth = tree->Draw("nEvents", "passVBF2DTLooseHLT>0 && passVBF2DTOff", "goff");  

  // DiTau  
  double passDiTau35HLT = tree->Draw("nEvents", "passDiTau35HLT>0", "goff");
  double passDiTau35Off = tree->Draw("nEvents", "passDiTau35Off>0", "goff");
  double passDiTau35Both = tree->Draw("nEvents", "passDiTau35HLT>0 && passDiTau35Off>0", "goff");

  double passDeepDiTau35HLT = tree->Draw("nEvents", "passDeepDiTau35HLT>0", "goff");
  double passDeepDiTau35Both = tree->Draw("nEvents", "passDeepDiTau35HLT>0 && passDiTau35Off>0", "goff");

  // ORs (only look at Boths)
  double passVBF2DTOldL1IncDeepDiTau = tree->Draw("nEvents", "(passVBF2DTOldL1>0 && passVBF2DTOff>0) || (passInclusiveVBFHLT>0 && passInclusiveVBFOff) || (passDeepDiTau35HLT>0 && passDiTau35Off)", "goff");
  double passVBFMediumIncDeepDiTau = tree->Draw("nEvents", "(passVBF2DTHLT>0 && passVBF2DTOff>0) || (passInclusiveVBFHLT>0 && passInclusiveVBFOff) || (passDeepDiTau35HLT>0 && passDiTau35Off)", "goff");
  double passVBFLooseIncDeepDiTau = tree->Draw("nEvents", "(passVBF2DTLooseHLT>0 && passVBF2DTOff>0) || (passInclusiveVBFHLT>0 && passInclusiveVBFOff) || (passDeepDiTau35HLT>0 && passDiTau35Off)", "goff");
  double passIncOldDiTau = tree->Draw("nEvents", "(passInclusiveVBFHLT>0 && passInclusiveVBFOff>0) || (passDiTau35HLT>0 && passDiTau35Off>0)", "goff");
  double passIncDeepDiTau = tree->Draw("nEvents", "(passInclusiveVBFHLT>0 && passInclusiveVBFOff>0) || (passDeepDiTau35HLT>0 && passDiTau35Off>0)", "goff");
  double passVBF2DTOldL1DeepDiTau = tree->Draw("nEvents", "(passVBF2DTOldL1>0 && passVBF2DTOff>0) || (passDeepDiTau35HLT>0 && passDiTau35Off>0)", "goff");
  double passVBF2DTDeepDiTau = tree->Draw("nEvents", "(passVBF2DTHLT>0 && passVBF2DTOff>0) || (passDeepDiTau35HLT>0 && passDiTau35Off>0)", "goff");
  double passVBF2DTLooseDeepDiTau = tree->Draw("nEvents", "(passVBF2DTLooseHLT>0 && passVBF2DTOff) || (passDeepDiTau35HLT>0 && passDiTau35Off>0)", "goff");

  std::cout << "Singles" << '\n'
            << passInclusiveVBFBoth << '\t' << "Inclusive VBF" << '\n'
            << passVBF2DTOldL1Both << '\t' << "VBF Medium L2NN Old L1" << '\n'
            << passVBF2DTBoth << '\t' << "VBF Medium L2NN" << '\n'
            << passVBF2DTLooseBoth << '\t' << "VBF Loose L2NN" << '\n'
            << passDiTau35Both << '\t' << "Old DiTau 35" << '\n'
            << passDeepDiTau35Both << '\t' << "Deep DiTau 35" << '\n'
            << "Doubles" << '\n'
            << passIncOldDiTau << '\t' << "Inclusive VBF OR Old DiTau 35" << '\n'
            << passIncDeepDiTau << '\t' << "Inclusive VBF OR Deep DiTau 35" << '\n'
            << passVBF2DTOldL1DeepDiTau << '\t' << "VBF Medium L2NN Old L1 OR Deep DiTau 35" << '\n'
            << passVBF2DTDeepDiTau << '\t' << "VBF Medium L2NN OR Deep DiTau 35" << '\n'
            << passVBF2DTLooseDeepDiTau << '\t' << "VBF Loose OR Deep DiTau 35" << '\n'
            << "Triples" << '\n'
            << passVBF2DTOldL1IncDeepDiTau << '\t' << "VBF Medium L2NN Old L1 OR Inclusive VBF OR Deep DiTau 35" << '\n'
            << passVBFMediumIncDeepDiTau << '\t' << "VBF Medium L2NN OR Inclusive VBF OR Deep DiTau 35" << '\n'
            << passVBFLooseIncDeepDiTau << '\t' << "VBF Loose OR Inclusive VBF OR Deep DiTau 35" << '\n'
            << std::endl;

}
