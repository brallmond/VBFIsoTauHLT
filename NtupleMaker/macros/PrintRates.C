void PrintRates(char* filename) { 

  TFile *_file0 = TFile::Open(filename);
  TTree* tree = (TTree*)_file0->Get("outTree");

  // Data stats
  double nEvents = tree->Draw("nEvents", "nEvents>0", "goff");
  std::cout << nEvents << '\t' << "Events Skimmed" << std::endl;

  // get # of LS
  // spent over 2 hours looking for how to do this, doing it by hand
  // the documentation for ROOT is really lacking for a student.
  // dataset of EphHLT 323755
  // number lumis
  // 1,  2,  3,  4,  5,  6,  7,  8,
  // 246, 333, 
  // make hist obj, clone lumisSize, store max as int, print
  //TH1F* dummyH =  (TH1F*)Clone->()("dummyH", "", 300, 0, 300);
  //tree->Draw("lumisSize >> dummyH", "lumisSize>0", "goff");
  //double lumisSizeMax = dummyH->GetMaximumBin();
  //std::cout << lumisSizeMax << '\t' << "Lumis size" << std::endl;

  // L1s
  // InclusiveVBF L1

  double passhltL1VBFDiJetOR = tree->Draw("nEvents", "passhltL1VBFDiJetOR>0", "goff");

  // VBFIsoTau L1
  double passhltL1VBFDiJetIsoTau = tree->Draw("nEvents", "passhltL1VBFDiJetIsoTau>0", "goff");

  // VBFIsoTau L1 old version
  double passhltL1VBFDiJetIsoTauNoer = tree->Draw("nEvents", "passhltL1VBFDiJetIsoTauNoer>0", "goff");

  // DiTau OR of L1s
  double passhltL1sDoubleTauBigOR = tree->Draw("nEvents", "passDiTau32L1>0", "goff");

  // 3 L1 OR
  double threeL1OR = tree->Draw("nEvents", "passDiTau32L1>0 || passhltL1VBFDiJetIsoTau>0 || passhltL1VBFDiJetOR>0", "goff");
  // 2 L1 OR
  double twoL1OR = tree->Draw("nEvents", "passDiTau32L1>0 || passhltL1VBFDiJetOR>0", "goff");
  double pureIsoTau = threeL1OR-twoL1OR;

  // HLTs
  // InclusiveVBF
  double passInclusiveVBFHLT = tree->Draw("nEvents", "passInclusiveVBFHLT>0", "goff");

  // VBF2DT
  double passVBF2DTHLT = tree->Draw("nEvents", "passVBF2DTHLT>0", "goff");

  double passVBF2DTOldL1HLT = tree->Draw("nEvents", "passVBF2DTOldL1>0", "goff");
 
  // VBF2DT Loose
  double passVBF2DTLooseHLT = tree->Draw("nEvents", "passVBF2DTLooseHLT>0", "goff");

  // DiTau  
  double passDiTau35HLT = tree->Draw("nEvents", "passDiTau35HLT>0", "goff");

  double passDeepDiTau35HLT = tree->Draw("nEvents", "passDeepDiTau35HLT>0", "goff");

  // Math Consts for rate estimate
  double revFreq = 11245.6;
  double nBunches = 2544; 
  double rateFactor = revFreq*nBunches/nEvents;

  // ORs (only look at Boths)

  std::cout << rateFactor << '\t' << "rate factor" << std::endl;
  std::cout << "Count" << '\t' << "Rate" << '\t' << "Label" << std::endl;
  std::cout << "L1s" << std::endl;
  std::cout << "Singles" << '\n'
            << passhltL1VBFDiJetOR << '\t' << passhltL1VBFDiJetOR*rateFactor << '\t' << "Inclusive VBF L1" << '\n'
            << passhltL1VBFDiJetIsoTau << '\t' << passhltL1VBFDiJetIsoTau*rateFactor << '\t' << "VBF Iso Tau L1" << '\n'
            << passhltL1VBFDiJetIsoTauNoer << '\t' << passhltL1VBFDiJetIsoTau*rateFactor << '\t' << "VBF Iso Tau Old L1" << '\n'
            << passhltL1sDoubleTauBigOR << '\t' << passhltL1sDoubleTauBigOR*rateFactor << '\t' << "DiTau L1 OR" << '\n' 
            << "Pure Iso Tau" << '\n'
            << pureIsoTau << '\t' << pureIsoTau*rateFactor << '\t' << "3 OR - 2 OR = Exclusively VBFIsoTau L1" << '\n'
            << std::endl;
  std::cout << "HLTs" << std::endl;
  std::cout << "Singles" << '\n'
            << passInclusiveVBFHLT << '\t' << "Inclusive VBF HLT" << '\n'
            << passVBF2DTHLT << '\t' << "VBF Iso Tau HLT" << '\n'
            << passVBF2DTOldL1HLT << '\t' << "VBF Iso Tau Old L1 HLT" << '\n'
            << passVBF2DTLooseHLT << '\t' << "VBF Iso Tau LOOSE HLT" << '\n'
            << passDiTau35HLT << '\t' << "DiTau35 HLT" << '\n'
            << passDeepDiTau35HLT << '\t' << "Deep DiTau35 HLT" << '\n'
            << std::endl;

}
