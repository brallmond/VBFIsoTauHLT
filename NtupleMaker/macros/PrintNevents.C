void PrintNevents(char* filename) { 

  TFile *_file0 = TFile::Open(filename);
  TTree* tree = (TTree*)_file0->Get("demo/vbf");

  int nEvents = tree->Draw("nEvents", "nEvents>0 && ( (lumiBlock>= 38 && lumiBlock <= 81) || (lumiBlock >= 84 && lumiBlock <= 171) )", "goff");
  std::cout << nEvents << '\t' << "Events Skimmed" << '\n' << std::endl;

}
