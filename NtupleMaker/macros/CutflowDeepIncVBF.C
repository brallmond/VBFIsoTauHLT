void CutflowDeepIncVBF(char* filename, int isAlt) {

  TFile *_file0 = TFile::Open(filename);

  TTree* tree = (TTree*)_file0->Get("outTree");

  double hltL1Filter = tree->Draw("nEvents", "passhltL1VBFDiJetOR>0 && passInclusiveVBFOff>0", "goff");
  double doubleL2Tau20Filter = tree->Draw("nEvents", "passhltDoubleL2Tau20eta2p2>0 && passInclusiveVBFOff>0", "goff");
  double doubleL2Tau20IsoFilter = tree->Draw("nEvents", "passhltDoubleL2GlobIsoTau20eta2p2>0 && passInclusiveVBFOff>0", "goff");
  double doubleMatchedJet40Filter = tree->Draw("nEvents", "passhltMatchedVBFTwoPFJets2CrossCleanedFromDoubleMediumDeepTauDitauWPPFTauHPS20>0 && passInclusiveVBFOff>0", "goff");
  double singleMatchedJet115Filter = tree->Draw("nEvents", "passhltMatchedVBFOnePFJet2CrossCleanedFromDoubleMediumDeepTauDitauWPPFTauHPS20>0 && passInclusiveVBFOff>0", "goff");
  // alt RmOvlp version
  double doubleMatchedJet40AltFilter = tree->Draw("nEvents", "passhltMatchedVBFTwoPFJetsPassingDiJetCorrCheckerWithMediumDiTauWPPFTauHPS20>0 && passInclusiveVBFOff>0", "goff");
  double singleMatchedJet115AltFilter = tree->Draw("nEvents", "passhltMatchedVBFOnePFJetPassingDiJetCorrCheckerWithMediumDiTauWPPFTauHPS20>0 && passInclusiveVBFOff>0", "goff");

  double passSelection = tree->Draw("nEvents", "passInclusiveVBFOff>0", "goff");
  double passHLTAndSelection = tree->Draw("nEvents", "passDeepInclusiveVBFHLT>0 && passInclusiveVBFOff>0", "goff");
  double passAltHLTAndSelection = tree->Draw("nEvents", "passAltDeepInclusiveVBFHLT>0 && passInclusiveVBFOff>0", "goff");

  if (isAlt == 1) {
    doubleMatchedJet40Filter = doubleMatchedJet40AltFilter;
    singleMatchedJet115Filter = singleMatchedJet115AltFilter;
    passHLTAndSelection = passAltHLTAndSelection;
  }

  double variableHolder[] = {hltL1Filter, doubleL2Tau20Filter, doubleL2Tau20IsoFilter, \
                             doubleMatchedJet40Filter, singleMatchedJet115Filter, passHLTAndSelection}; //i've gotta learn pyRoot

  const char *names[6] = {"L1", "Two20Taus", "TauIso", "Two45Jets", "One115Jet", "passHLT"};

  TH1F* cutflowDeepTau = new TH1F("cutflowDeepIncVBF", "", 6, 0.0, 6.0);

  std::cout << passSelection << '\t' << "pass selection only" << std::endl;
  double fraction[6];
  size_t n = sizeof(fraction) / sizeof(double);
  std::cout << std::left << std::setw(10) << "Count" \
            << std::setw(10) << "Abs. Eff." \
            << std::setw(10) << "Rel. Eff." \
            << std::setw(10) << "Filter" << std::endl;
  for (int i = 0; i < n; ++i) {
    fraction[i] = variableHolder[i]/passSelection;
    if (i == 0) std::cout << std::left << std::setw(10) << variableHolder[i] \
             << std::setw(10) << fraction[i] \
             << std::setw(10) << "-------" \
             << std::setw(10) << names[i] << std::endl;
    else std::cout << std::left << std::setw(10) << variableHolder[i] \
      << std::setw(10) << fraction[i] \
      << std::setw(10) << variableHolder[i]/variableHolder[i-1] \
      << std::setw(10) << names[i] << std::endl;
    cutflowDeepTau->Fill(names[i], variableHolder[i]/passSelection);
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
  legendAbsEff->AddEntry(cutflowDeepTau, "Deep Inclusive VBF HLT Path");
  legendAbsEff->Draw();

  c1->Print("cutflowDeepTauAbsEff.png", "png");
}
