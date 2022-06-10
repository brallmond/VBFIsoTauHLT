void PrintNevents(char* filename) { 

  TFile *_file0 = TFile::Open(filename);
  TTree* tree = (TTree*)_file0->Get("demo/vbf");

  //int nEvents = tree->Draw("nEvents", "nEvents>0 && ( (lumiBlock>= 38 && lumiBlock <= 81) || (lumiBlock >= 84 && lumiBlock <= 171) )", "goff");
  //
  int nEvents = tree->Draw("nEvents", "nEvents>0", "goff");
  int passDeepIncVBFHLT = tree->Draw("nEvents", "passDeepInclusiveVBFHLT>0", "goff");
  int passAltDeepIncVBFHLT = tree->Draw("nEvents", "passAltDeepInclusiveVBFHLT>0", "goff");

  std::cout << nEvents << '\t' << "Events Skimmed" << std::endl;
  std::cout << passDeepIncVBFHLT << '\t' << "pass deep inclusive VBF HLT" << std::endl;
  std::cout << passAltDeepIncVBFHLT << '\t' << "pass alternate deep inclusive VBF HLT" << std::endl;

}
