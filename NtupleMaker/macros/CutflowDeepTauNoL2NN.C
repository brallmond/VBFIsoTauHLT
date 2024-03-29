void CutflowDeepTauNoL2NN(char* filename) {

  TFile *_file0 = TFile::Open(filename);

  TTree* tree = (TTree*)_file0->Get("outTree");

  double hltL1Filter = tree->Draw("nEvents", "passhltL1VBFDiJetIsoTau>0 && passVBFPlusTwoTauOff>0", "goff");
  double doubleDeep20TausFilter = tree->Draw("nEvents", "passhltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_VBF2DTNoL2NN>0 && passVBFPlusTwoTauOff>0", "goff");
  double singleDeep45TauL1HLTMatchingFilter = tree->Draw("nEvents", "passhltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_VBF2DTNoL2NN>0 && passVBFPlusTwoTauOff>0", "goff");
  double jetKinemFilter = tree->Draw("nEvents", "passhltRealDijetFilter_VBF2DTNoL2NN>0 && passVBFPlusTwoTauOff>0", "goff");
  double jetIDFilter = tree->Draw("nEvents", "passhltVBFLooseIDPFDummyFilter_VBF2DTNoL2NN>0 && passVBFPlusTwoTauOff>0", "goff");
  double twoMatchedJetsFilter = tree->Draw("nEvents", "passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20_VBF2DTNoL2NN>0 && passVBFPlusTwoTauOff>0", "goff");

  double hltVBFTwoDeepTauDecision = tree->Draw("nEvents", "passVBF2DTNoL2NNHLT>0 && passVBFPlusTwoTauOff>0","goff");
  double passSelectionOnly = tree->Draw("nEvents", "passVBFPlusTwoTauOff>0", "goff");
  double passSelectionToo = tree->Draw("nEvents", "passVBF2DTNoL2NNBoth>0", "goff");

  double variableHolder[] = {hltL1Filter, doubleDeep20TausFilter, singleDeep45TauL1HLTMatchingFilter, jetKinemFilter, jetIDFilter, twoMatchedJetsFilter, hltVBFTwoDeepTauDecision, passSelectionToo}; //i've gotta learn pyRoot

  const char *names[8] = {"L1", "2Deep20Taus", "1Deep45Tau", "jetKinem.", "jetID", "jetCC", "passHLT", "passMatching"};

  TH1F* cutflowDeepTau = new TH1F("cutflowDeepTau", "", 8, 0.0, 8.0);

  std::cout << passSelectionOnly << '\t' << "pass selection only" << std::endl;
  double fraction[8];
  size_t n = sizeof(fraction) / sizeof(double);
  std::cout << std::left << std::setw(10) << "Count" \
            << std::setw(10) << "Abs. Eff." \
            << std::setw(10) << "Rel. Eff." \
            << std::setw(10) << "Filter" << std::endl;
  for (int i = 0; i < n; ++i) {
    fraction[i] = variableHolder[i]/passSelectionOnly;
    if (i == 0) std::cout << std::left << std::setw(10) << variableHolder[i] \
             << std::setw(10) << fraction[i] \
             << std::setw(10) << "-------" \
             << std::setw(10) << names[i] << std::endl;
    else std::cout << std::left << std::setw(10) << variableHolder[i] \
      << std::setw(10) << fraction[i] \
      << std::setw(10) << variableHolder[i]/variableHolder[i-1] \
      << std::setw(10) << names[i] << std::endl;
    cutflowDeepTau->Fill(names[i], variableHolder[i]/passSelectionOnly);
  }

  TCanvas *c1 = new TCanvas("c1", "", 600, 400);

  gStyle->SetOptStat(kFALSE);

  cutflowDeepTau->SetTitle("HLT PassOffline Filter Absolute Efficiency Cutflow;; Efficiency");
  cutflowDeepTau->GetXaxis()->SetLabelSize(0.039);
  cutflowDeepTau->GetYaxis()->SetRangeUser(0.6,1.1);

  cutflowDeepTau->Draw("hist");
  cutflowDeepTau->SetLineColor(1);

  auto legendAbsEff = new TLegend(0.48, 0.7, 0.9, 0.9);
  legendAbsEff->SetHeader("Key", "C");
  legendAbsEff->AddEntry(cutflowDeepTau, "Deep Tau HLT Path");
  legendAbsEff->Draw();

  c1->Print("cutflowDeepTauAbsEff.png", "png");
}
