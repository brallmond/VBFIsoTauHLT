void CountL1s(char* filename) {

    TFile *_file0 = TFile::Open(filename);

    TTree* tree = (TTree*)_file0->Get("demo/vbf");

    double nEvents = tree->Draw("nEvents", "nEvents>0", "goff");

    std::cout << nEvents << '\t' << "nEvents" << '\n' << std::endl;

    double passDiTauL1 = tree->Draw("nEvents", "passhltL1sDoubleTauBigOR>0", "goff");
    double passVBFDiJetOR = tree->Draw("nEvents", "passhltL1VBFDiJetOR>0", "goff");
    double passVBFDiJetIsoTau = tree->Draw("nEvents", "passhltL1VBFDiJetIsoTau>0", "goff");

    std::cout << passDiTauL1 << '\t' << "DiTau L1" << '\n'
              << passVBFDiJetOR << '\t' << "VBF Di Jet L1" << '\n'
              << passVBFDiJetIsoTau << '\t' << "VBF Iso Tau L1" << '\n'
              << std::endl;


}
