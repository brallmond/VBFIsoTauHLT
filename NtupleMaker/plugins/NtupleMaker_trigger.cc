// Braden Allmond Nov 22nd 2021

#include "VBFIsoTauHLT/NtupleMaker/plugins/NtupleMaker.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"

using namespace std;

int passHLTDummyL1;
int passHLTDummyL1Loose;
int passHLTDummyEGORL1;

int passEleTauHLT; // HLT_Ele24_eta2p1_WPTight_Gsf_LooseDeepTauPFTauHPS30_eta2p1_CrossL1_v2

int passDeepDiTau35HLT;
int passDiTauControlHLT; // no longer in the menu

int passInclusiveVBFHLT;
int passDeepInclusiveVBFHLT;
int passAltDeepInclusiveVBFHLT; // they didn't want it
int passAltDeepInclusiveVBFNoMuonHLT; // they didn't want it either

int passVBF2DTHLT;
int passVBF1DTHLT; // for HL LHC
int passVBF2DTLooseHLT; // they didn't want it

int passUpperControlHLT; // went with medium WPs
int passLowerControlHLT; // went with medium WPs
int passUpperControlMedHLT;
int passLowerControlMedHLT;

int pass2Tau1JetHLT; // Jaime's trigger
int pass2Tau1JetHigherHLT; // Jaime's other trigger (same as above with higher jet cut)

// HIG Monitoring
// no longer monitoring
int passIsoMu27LooseChargedTauHLT;
int passIsoMu27LooseChargedHPSTauHLT;
int passIsoMu27MediumChargedTauHLT;
int passIsoMu27TightChargedTauHLT;
int passIsoMu27DeepTauHLT;

float 	pt_;
float 	eta_;
float 	phi_;
float 	energy_;

int	nEvents;

// filters and modules and respective objects if necessary
int passhltL1VBFElectron;
vector<float> hltL1VBFElectron_ePt;
vector<float> hltL1VBFElectron_eEta;
vector<float> hltL1VBFElectron_ePhi;
vector<float> hltL1VBFElectron_eEnergy;
vector<float> hltL1VBFElectron_jPt;
vector<float> hltL1VBFElectron_jEta;
vector<float> hltL1VBFElectron_jPhi;
vector<float> hltL1VBFElectron_jEnergy;

int passhltL1VBFElectronLoose;
vector<float> hltL1VBFElectronLoose_ePt;
vector<float> hltL1VBFElectronLoose_eEta;
vector<float> hltL1VBFElectronLoose_ePhi;
vector<float> hltL1VBFElectronLoose_eEnergy;
vector<float> hltL1VBFElectronLoose_jPt;
vector<float> hltL1VBFElectronLoose_jEta;
vector<float> hltL1VBFElectronLoose_jPhi;
vector<float> hltL1VBFElectronLoose_jEnergy;

int passhltL1EGOR;

//hltL1sDoubleTauBigOR
int 		passhltL1sDoubleTauBigOR;
vector<float>	hltL1sDoubleTauBigOR_pt;
vector<float>	hltL1sDoubleTauBigOR_eta;
vector<float>	hltL1sDoubleTauBigOR_phi;
vector<float>	hltL1sDoubleTauBigOR_energy;

//hltL1VBFDiJetOR
int	passhltL1VBFDiJetOR;
vector<float>	hltL1VBFDiJetOR_pt;
vector<float>	hltL1VBFDiJetOR_eta;
vector<float>	hltL1VBFDiJetOR_phi;
vector<float>	hltL1VBFDiJetOR_energy;

//hltL1VBFDiJetIsoTau
int	passhltL1VBFDiJetIsoTau;
vector<int>	hltL1VBFDiJetIsoTau_nJets;
vector<float>	hltL1VBFDiJetIsoTau_jetPt;
vector<float>	hltL1VBFDiJetIsoTau_jetEta;
vector<float>	hltL1VBFDiJetIsoTau_jetPhi;
vector<float>	hltL1VBFDiJetIsoTau_jetEnergy;
vector<int>	hltL1VBFDiJetIsoTau_nTaus;
vector<float>	hltL1VBFDiJetIsoTau_tauPt;
vector<float>	hltL1VBFDiJetIsoTau_tauEta;
vector<float>	hltL1VBFDiJetIsoTau_tauPhi;
vector<float>	hltL1VBFDiJetIsoTau_tauEnergy;

//lower control L1
int passhltL1sSingleMu22;
vector<float> hltL1sSingleMu22_pt;
vector<float> hltL1sSingleMu22_eta;
vector<float> hltL1sSingleMu22_phi;
vector<float> hltL1sSingleMu22_energy;

//upper control L1
int passhltL1sMu22er2p1IsoTau28er2p1;
vector<float> hltL1sMu22er2p1IsoTau28er2p1_muPt;
vector<float> hltL1sMu22er2p1IsoTau28er2p1_muEta;
vector<float> hltL1sMu22er2p1IsoTau28er2p1_muPhi;
vector<float> hltL1sMu22er2p1IsoTau28er2p1_muEnergy;
vector<float> hltL1sMu22er2p1IsoTau28er2p1_tauPt;
vector<float> hltL1sMu22er2p1IsoTau28er2p1_tauEta;
vector<float> hltL1sMu22er2p1IsoTau28er2p1_tauPhi;
vector<float> hltL1sMu22er2p1IsoTau28er2p1_tauEnergy;


//branches for VBFPlusTwoDeepTauHLT
int passhltL2VBFIsoTauNNFilter; // it would be good to have L2 Taus actually
vector<float> hltL2VBFIsoTauNNFilter_pt;
vector<float> hltL2VBFIsoTauNNFilter_eta;
vector<float> hltL2VBFIsoTauNNFilter_phi;
vector<float> hltL2VBFIsoTauNNFilter_energy;

int passhltHpsSelectedPFTausMediumDitauWPDeepTauForVBFIsoTau;
vector<float> hltHpsSelectedPFTausMediumDitauWPDeepTauForVBFIsoTau_pt;

int passhltHpsSelectedPFTausTempLooseDitauWPDeepTauForVBFIsoTau;
vector<float> hltHpsSelectedPFTausTempLooseDitauWPDeepTauForVBFIsoTau_pt;

int passhltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch;
vector<float> hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_pt;

int passhltHpsDoublePFTau20MediumDitauWPDeepTauNoMatchNoL2NN;
vector<float> hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatchNoL2NN_pt;

int passhltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatch; // no need for TempLoose any longer
vector<float> hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatch_pt;

int passhltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatchNoL2NN;
vector<float> hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatchNoL2NN_pt;

// match L1 Tau
int passhltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched;
vector<float> hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_pt;

int passhltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatchedNoL2NN;
vector<float> hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatchedNoL2NN_pt;

int passhltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatched; 
vector<float> hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatched_pt;

int passhltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatchedNoL2NN;
vector<float> hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatchedNoL2NN_pt;

// added for inefficiency study in DeepTau HLT
int passhltRealDijetFilter;
vector<float> hltRealDijetFilter_pt;

int passhltVBFLooseIDPFDummyFilter;
vector<float> hltVBFLooseIDPFDummyFilter_pt;

int passhltVBFIsoTauL1TLooseIDPFJetsMatching;
vector<float> hltVBFIsoTauL1TLooseIDPFJetsMatching_pt;

// match jets filter
int passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20; 
vector<float> hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20_pt;

int passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20NoL2NN; 
vector<float> hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20NoL2NN_pt;

int passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20;
vector<float> hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20_pt;

int passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20NoL2NN;
vector<float> hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20NoL2NN_pt;

int passhltHpsDoublePFTau20BeforeDeepTau;
vector<float> hltHpsDoublePFTau20BeforeDeepTau_pt;

int passhltHpsDoublePFTau20withL2NNBeforeDeepTau;
vector<float> hltHpsDoublePFTau20withL2NNBeforeDeepTau_pt;

// branches for DeepVBF eff study
int passhltDoubleL2Tau20eta2p2;
int passhltDoubleL2GlobIsoTau20eta2p2; // could compare L2 Taus
vector<float> hltDoubleL2GlobIsoTau20eta2p2_pt;
int passhltMatchedVBFTwoPFJets2CrossCleanedFromDoubleMediumDeepTauDitauWPPFTauHPS20;

int passhltHpsDoublePFTau20TrackDeepTauIsoDitauWPForVBFIsoTau;
int passhltHpsDoublePFTau20TrackDeepTauIsoDitauWPAgainstMuon;
vector<float> hltHpsDoublePFTau20TrackDeepTauIsoDitauWPForVBFIsoTau_pt;
vector<float> hltHpsDoublePFTau20TrackDeepTauIsoDitauWPAgainstMuon_pt;
vector<float> hltMatchedVBFTwoPFJets2CrossCleanedFromDoubleMediumDeepTauDitauWPPFTauHPS20_pt;

int passhltMatchedVBFOnePFJet2CrossCleanedFromDoubleMediumDeepTauDitauWPPFTauHPS20;
vector<float> hltMatchedVBFOnePFJet2CrossCleanedFromDoubleMediumDeepTauDitauWPPFTauHPS20_pt;

// final two branches with different jet correlation producer
int passhltMatchedVBFTwoPFJetsPassingDiJetCorrCheckerWithMediumDiTauWPPFTauHPS20;
vector<float> hltMatchedVBFTwoPFJetsPassingDiJetCorrCheckerWithMediumDiTauWPPFTauHPS20_pt;
int passhltMatchedVBFOnePFJetPassingDiJetCorrCheckerWithMediumDiTauWPPFTauHPS20;
vector<float> hltMatchedVBFOnePFJetPassingDiJetCorrCheckerWithMediumDiTauWPPFTauHPS20_pt;

int passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedUsingDiJetCorrCheckerWithMediumDiTau;
vector<float> hltMatchedVBFIsoTauTwoPFJets2CrossCleanedUsingDiJetCorrCheckerWithMediumDiTau_pt;

int passhltMatchedVBFTwoPFJetsPassingDiJetCorrCheckerWithMediumDiTauWPPFTauHPS20NoAntiMuon;
int passhltMatchedVBFOnePFJetPassingDiJetCorrCheckerWithMediumDiTauWPPFTauHPS20NoAntiMuon;

void NtupleMaker::branchesTriggers(TTree* tree){

    tree->Branch("nEvents", &nEvents);

    tree->Branch("passHLTDummyL1", &passHLTDummyL1);
    tree->Branch("passHLTDummyL1Loose", &passHLTDummyL1Loose);
    tree->Branch("passHLTDummyEGORL1", &passHLTDummyEGORL1);
   
    tree->Branch("passEleTauHLT", &passEleTauHLT);

    tree->Branch("passDeepDiTau35HLT", &passDeepDiTau35HLT);

    tree->Branch("passInclusiveVBFHLT", &passInclusiveVBFHLT);    
    tree->Branch("passDeepInclusiveVBFHLT", &passDeepInclusiveVBFHLT);    
    tree->Branch("passAltDeepInclusiveVBFHLT", &passAltDeepInclusiveVBFHLT);    
    tree->Branch("passAltDeepInclusiveVBFNoMuonHLT", &passAltDeepInclusiveVBFNoMuonHLT);    
    
    tree->Branch("passVBF2DTHLT", &passVBF2DTHLT);
    tree->Branch("passVBF1DTHLT", &passVBF1DTHLT);
    tree->Branch("passVBF2DTLooseHLT", &passVBF2DTLooseHLT);

    tree->Branch("passUpperControlHLT", &passUpperControlHLT);
    tree->Branch("passLowerControlHLT", &passLowerControlHLT);
    tree->Branch("pass2Tau1JetHLT", &pass2Tau1JetHLT);
    tree->Branch("pass2Tau1JetHigherHLT", &pass2Tau1JetHigherHLT);

    tree->Branch("passUpperControlMedHLT", &passUpperControlMedHLT);
    tree->Branch("passLowerControlMedHLT", &passLowerControlMedHLT);
    tree->Branch("passDiTauControlHLT", &passDiTauControlHLT);

    tree->Branch("passIsoMu27LooseChargedTauHLT", &passIsoMu27LooseChargedTauHLT);
    tree->Branch("passIsoMu27LooseChargedHPSTauHLT", &passIsoMu27LooseChargedHPSTauHLT);
    tree->Branch("passIsoMu27MediumChargedTauHLT", &passIsoMu27MediumChargedTauHLT);
    tree->Branch("passIsoMu27TightChargedTauHLT", &passIsoMu27TightChargedTauHLT);
    tree->Branch("passIsoMu27DeepTauHLT", &passIsoMu27DeepTauHLT);

    tree->Branch("passhltL1EGOR", &passhltL1EGOR);

    tree->Branch("passhltL1VBFElectron", &passhltL1VBFElectron);
    tree->Branch("hltL1VBFElectron_ePt", &hltL1VBFElectron_ePt);
    tree->Branch("hltL1VBFElectron_eEta", &hltL1VBFElectron_eEta);
    tree->Branch("hltL1VBFElectron_ePhi", &hltL1VBFElectron_ePhi);
    tree->Branch("hltL1VBFElectron_eEnergy", &hltL1VBFElectron_eEnergy);
    tree->Branch("hltL1VBFElectron_jPt", &hltL1VBFElectron_jPt);
    tree->Branch("hltL1VBFElectron_jEta", &hltL1VBFElectron_jEta);
    tree->Branch("hltL1VBFElectron_jPhi", &hltL1VBFElectron_jPhi);
    tree->Branch("hltL1VBFElectron_jEnergy", &hltL1VBFElectron_jEnergy);

    tree->Branch("passhltL1VBFElectronLoose", &passhltL1VBFElectronLoose);
    tree->Branch("hltL1VBFElectronLoose_ePt", &hltL1VBFElectronLoose_ePt);
    tree->Branch("hltL1VBFElectronLoose_eEta", &hltL1VBFElectronLoose_eEta);
    tree->Branch("hltL1VBFElectronLoose_ePhi", &hltL1VBFElectronLoose_ePhi);
    tree->Branch("hltL1VBFElectronLoose_eEnergy", &hltL1VBFElectronLoose_eEnergy);
    tree->Branch("hltL1VBFElectronLoose_jPt", &hltL1VBFElectronLoose_jPt);
    tree->Branch("hltL1VBFElectronLoose_jEta", &hltL1VBFElectronLoose_jEta);
    tree->Branch("hltL1VBFElectronLoose_jPhi", &hltL1VBFElectronLoose_jPhi);
    tree->Branch("hltL1VBFElectronLoose_jEnergy", &hltL1VBFElectronLoose_jEnergy);


    tree->Branch("passhltL1sDoubleTauBigOR", &passhltL1sDoubleTauBigOR);
    tree->Branch("hltL1sDoubleTauBigOR_pt", &hltL1sDoubleTauBigOR_pt);
    tree->Branch("hltL1sDoubleTauBigOR_eta", &hltL1sDoubleTauBigOR_eta);
    tree->Branch("hltL1sDoubleTauBigOR_phi", &hltL1sDoubleTauBigOR_phi);
    tree->Branch("hltL1sDoubleTauBigOR_energy", &hltL1sDoubleTauBigOR_energy);

    tree->Branch("passhltL1VBFDiJetOR", &passhltL1VBFDiJetOR);
    tree->Branch("hltL1VBFDiJetOR_pt", &hltL1VBFDiJetOR_pt);
    tree->Branch("hltL1VBFDiJetOR_eta", &hltL1VBFDiJetOR_eta);
    tree->Branch("hltL1VBFDiJetOR_phi", &hltL1VBFDiJetOR_phi);
    tree->Branch("hltL1VBFDiJetOR_energy", &hltL1VBFDiJetOR_energy);

    tree->Branch("passhltL1VBFDiJetIsoTau", &passhltL1VBFDiJetIsoTau);
    tree->Branch("hltL1VBFDiJetIsoTau_nJets", &hltL1VBFDiJetIsoTau_nJets);
    tree->Branch("hltL1VBFDiJetIsoTau_jetPt", &hltL1VBFDiJetIsoTau_jetPt);
    tree->Branch("hltL1VBFDiJetIsoTau_jetEta", &hltL1VBFDiJetIsoTau_jetEta);
    tree->Branch("hltL1VBFDiJetIsoTau_jetPhi", &hltL1VBFDiJetIsoTau_jetPhi);
    tree->Branch("hltL1VBFDiJetIsoTau_jetEnergy", &hltL1VBFDiJetIsoTau_jetEnergy);
    tree->Branch("hltL1VBFDiJetIsoTau_nTaus", &hltL1VBFDiJetIsoTau_nTaus);
    tree->Branch("hltL1VBFDiJetIsoTau_tauPt", &hltL1VBFDiJetIsoTau_tauPt);
    tree->Branch("hltL1VBFDiJetIsoTau_tauEta", &hltL1VBFDiJetIsoTau_tauEta);
    tree->Branch("hltL1VBFDiJetIsoTau_tauPhi", &hltL1VBFDiJetIsoTau_tauPhi);
    tree->Branch("hltL1VBFDiJetIsoTau_tauEnergy", &hltL1VBFDiJetIsoTau_tauEnergy);

    tree->Branch("passhltL1sSingleMu22", &passhltL1sSingleMu22);
    tree->Branch("hltL1sSingleMu22_pt", &hltL1sSingleMu22_pt);
    tree->Branch("hltL1sSingleMu22_eta", &hltL1sSingleMu22_eta);
    tree->Branch("hltL1sSingleMu22_phi", &hltL1sSingleMu22_phi);
    tree->Branch("hltL1sSingleMu22_energy", &hltL1sSingleMu22_energy);

    tree->Branch("passhltL1sMu22er2p1IsoTau28er2p1", &passhltL1sMu22er2p1IsoTau28er2p1);
    tree->Branch("hltL1sMu22er2p1IsoTau28er2p1_muPt", &hltL1sMu22er2p1IsoTau28er2p1_muPt);
    tree->Branch("hltL1sMu22er2p1IsoTau28er2p1_muEta", &hltL1sMu22er2p1IsoTau28er2p1_muEta);
    tree->Branch("hltL1sMu22er2p1IsoTau28er2p1_muPhi", &hltL1sMu22er2p1IsoTau28er2p1_muPhi);
    tree->Branch("hltL1sMu22er2p1IsoTau28er2p1_muEnergy", &hltL1sMu22er2p1IsoTau28er2p1_muEnergy);
    tree->Branch("hltL1sMu22er2p1IsoTau28er2p1_tauPt", &hltL1sMu22er2p1IsoTau28er2p1_tauPt);
    tree->Branch("hltL1sMu22er2p1IsoTau28er2p1_tauEta", &hltL1sMu22er2p1IsoTau28er2p1_tauEta);
    tree->Branch("hltL1sMu22er2p1IsoTau28er2p1_tauPhi", &hltL1sMu22er2p1IsoTau28er2p1_tauPhi);
    tree->Branch("hltL1sMu22er2p1IsoTau28er2p1_tauEnergy", &hltL1sMu22er2p1IsoTau28er2p1_tauEnergy);


    // VBFPlusTwoDeepTau HLT Modules
    tree->Branch("passhltL2VBFIsoTauNNFilter", &passhltL2VBFIsoTauNNFilter);
    tree->Branch("hltL2VBFIsoTauNNFilter_pt", &hltL2VBFIsoTauNNFilter_pt);

    // issue where these filters aren't being activated/stored in tree. Would be good info to have
    tree->Branch("passhltHpsSelectedPFTausMediumDitauWPDeepTauForVBFIsoTau", &passhltHpsSelectedPFTausMediumDitauWPDeepTauForVBFIsoTau);
    tree->Branch("hltHpsSelectedPFTausMediumDitauWPDeepTauForVBFIsoTau_pt", &hltHpsSelectedPFTausMediumDitauWPDeepTauForVBFIsoTau_pt);

    tree->Branch("passhltHpsSelectedPFTausTempLooseDitauWPDeepTauForVBFIsoTau", &passhltHpsSelectedPFTausTempLooseDitauWPDeepTauForVBFIsoTau);
    tree->Branch("hltHpsSelectedPFTausTempLooseDitauWPDeepTauForVBFIsoTau_pt", &hltHpsSelectedPFTausTempLooseDitauWPDeepTauForVBFIsoTau_pt);
    
    //
    tree->Branch("passhltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch", &passhltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch);
    tree->Branch("hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_pt", &hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_pt);

    tree->Branch("passhltHpsDoublePFTau20MediumDitauWPDeepTauNoMatchNoL2NN", &passhltHpsDoublePFTau20MediumDitauWPDeepTauNoMatchNoL2NN);
    tree->Branch("hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatchNoL2NN_pt", &hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatchNoL2NN_pt);

    tree->Branch("passhltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatch", &passhltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatch);
    tree->Branch("hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatch_pt", &hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatch_pt);

    tree->Branch("passhltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatchNoL2NN", &passhltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatchNoL2NN);
    tree->Branch("hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatchNoL2NN_pt", &hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatchNoL2NN_pt);

    //
    tree->Branch("passhltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched", &passhltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched);
    tree->Branch("hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_pt", &hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_pt);

    tree->Branch("passhltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatchedNoL2NN", &passhltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatchedNoL2NN);
    tree->Branch("hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatchedNoL2NN_pt", &hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatchedNoL2NN_pt);

    tree->Branch("passhltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatched", &passhltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatched);
    tree->Branch("hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatched_pt", &hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatched_pt);

    tree->Branch("passhltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatchedNoL2NN", &passhltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatchedNoL2NN);
    tree->Branch("hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatchedNoL2NN_pt", &hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatchedNoL2NN_pt);
    //
    tree->Branch("passhltRealDijetFilter", &passhltRealDijetFilter);
    tree->Branch("hltRealDijetFilter_pt", &hltRealDijetFilter_pt);

    tree->Branch("passhltVBFLooseIDPFDummyFilter", &passhltVBFLooseIDPFDummyFilter);
    tree->Branch("hltVBFLooseIDPFDummyFilter_pt", &hltVBFLooseIDPFDummyFilter_pt);

    tree->Branch("passhltVBFIsoTauL1TLooseIDPFJetsMatching", &passhltVBFIsoTauL1TLooseIDPFJetsMatching);
    tree->Branch("hltVBFIsoTauL1TLooseIDPFJetsMatching_pt", &hltVBFIsoTauL1TLooseIDPFJetsMatching_pt);

    tree->Branch("passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20", &passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20);
    tree->Branch("hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20_pt", &hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20_pt);

    tree->Branch("passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20NoL2NN", &passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20NoL2NN);
    tree->Branch("hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20NoL2NN_pt", &hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20NoL2NN_pt);

    tree->Branch("passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20", &passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20);
    tree->Branch("hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20_pt", &hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20_pt);

    tree->Branch("passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20NoL2NN", &passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20NoL2NN);
    tree->Branch("hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20NoL2NN_pt", &hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20NoL2NN_pt);


    tree->Branch("passhltHpsDoublePFTau20BeforeDeepTau", &passhltHpsDoublePFTau20BeforeDeepTau);
    tree->Branch("hltHpsDoublePFTau20BeforeDeepTau_pt", &hltHpsDoublePFTau20BeforeDeepTau_pt);

    tree->Branch("passhltHpsDoublePFTau20withL2NNBeforeDeepTau", &passhltHpsDoublePFTau20withL2NNBeforeDeepTau);
    tree->Branch("hltHpsDoublePFTau20withL2NNBeforeDeepTau_pt", &hltHpsDoublePFTau20withL2NNBeforeDeepTau_pt);

    tree->Branch("passhltDoubleL2Tau20eta2p2", &passhltDoubleL2Tau20eta2p2);
    tree->Branch("passhltDoubleL2GlobIsoTau20eta2p2", &passhltDoubleL2GlobIsoTau20eta2p2);
    tree->Branch("hltDoubleL2GlobIsoTau20eta2p2_pt", &hltDoubleL2GlobIsoTau20eta2p2_pt);

    tree->Branch("passhltHpsDoublePFTau20TrackDeepTauIsoDitauWPForVBFIsoTau", &passhltHpsDoublePFTau20TrackDeepTauIsoDitauWPForVBFIsoTau);
    tree->Branch("passhltHpsDoublePFTau20TrackDeepTauIsoDitauWPAgainstMuon", &passhltHpsDoublePFTau20TrackDeepTauIsoDitauWPAgainstMuon);

    tree->Branch("hltHpsDoublePFTau20TrackDeepTauIsoDitauWPForVBFIsoTau_pt", &hltHpsDoublePFTau20TrackDeepTauIsoDitauWPForVBFIsoTau_pt);
    tree->Branch("hltHpsDoublePFTau20TrackDeepTauIsoDitauWPAgainstMuon_pt", &hltHpsDoublePFTau20TrackDeepTauIsoDitauWPAgainstMuon_pt);

    tree->Branch("passhltMatchedVBFTwoPFJets2CrossCleanedFromDoubleMediumDeepTauDitauWPPFTauHPS20", &passhltMatchedVBFTwoPFJets2CrossCleanedFromDoubleMediumDeepTauDitauWPPFTauHPS20);
    tree->Branch("hltMatchedVBFTwoPFJets2CrossCleanedFromDoubleMediumDeepTauDitauWPPFTauHPS20_pt", &hltMatchedVBFTwoPFJets2CrossCleanedFromDoubleMediumDeepTauDitauWPPFTauHPS20_pt);
    tree->Branch("passhltMatchedVBFOnePFJet2CrossCleanedFromDoubleMediumDeepTauDitauWPPFTauHPS20", &passhltMatchedVBFOnePFJet2CrossCleanedFromDoubleMediumDeepTauDitauWPPFTauHPS20);
    tree->Branch("hltMatchedVBFOnePFJet2CrossCleanedFromDoubleMediumDeepTauDitauWPPFTauHPS20_pt", &hltMatchedVBFOnePFJet2CrossCleanedFromDoubleMediumDeepTauDitauWPPFTauHPS20_pt);
// final two branches with different jet correlation producer
    tree->Branch("passhltMatchedVBFTwoPFJetsPassingDiJetCorrCheckerWithMediumDiTauWPPFTauHPS20", &passhltMatchedVBFTwoPFJetsPassingDiJetCorrCheckerWithMediumDiTauWPPFTauHPS20);
    tree->Branch("hltMatchedVBFTwoPFJetsPassingDiJetCorrCheckerWithMediumDiTauWPPFTauHPS20_pt", &hltMatchedVBFTwoPFJetsPassingDiJetCorrCheckerWithMediumDiTauWPPFTauHPS20_pt);
    tree->Branch("passhltMatchedVBFOnePFJetPassingDiJetCorrCheckerWithMediumDiTauWPPFTauHPS20", &passhltMatchedVBFOnePFJetPassingDiJetCorrCheckerWithMediumDiTauWPPFTauHPS20);
    tree->Branch("hltMatchedVBFOnePFJetPassingDiJetCorrCheckerWithMediumDiTauWPPFTauHPS20_pt", &hltMatchedVBFOnePFJetPassingDiJetCorrCheckerWithMediumDiTauWPPFTauHPS20_pt);

    tree->Branch("passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedUsingDiJetCorrCheckerWithMediumDiTau", &passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedUsingDiJetCorrCheckerWithMediumDiTau);
    tree->Branch("hltMatchedVBFIsoTauTwoPFJets2CrossCleanedUsingDiJetCorrCheckerWithMediumDiTau_pt", &hltMatchedVBFIsoTauTwoPFJets2CrossCleanedUsingDiJetCorrCheckerWithMediumDiTau_pt);

    tree->Branch("passhltMatchedVBFTwoPFJetsPassingDiJetCorrCheckerWithMediumDiTauWPPFTauHPS20NoAntiMuon", &passhltMatchedVBFTwoPFJetsPassingDiJetCorrCheckerWithMediumDiTauWPPFTauHPS20NoAntiMuon);
    tree->Branch("passhltMatchedVBFOnePFJetPassingDiJetCorrCheckerWithMediumDiTauWPPFTauHPS20NoAntiMuon", &passhltMatchedVBFOnePFJetPassingDiJetCorrCheckerWithMediumDiTauWPPFTauHPS20NoAntiMuon);
}

void NtupleMaker::fillTriggers(const edm::Event& iEvent){

    using namespace edm;

    // clearing vectors and initializing flags at the start of every event 
    nEvents = 0;

    passHLTDummyL1 = 0;
    passHLTDummyL1Loose = 0;
    passHLTDummyEGORL1 = 0;

    passEleTauHLT = 0;

    passhltL1VBFElectron = 0;
    hltL1VBFElectron_ePt.clear();
    hltL1VBFElectron_eEta.clear();
    hltL1VBFElectron_ePhi.clear();
    hltL1VBFElectron_eEnergy.clear();
    hltL1VBFElectron_jPt.clear();
    hltL1VBFElectron_jEta.clear();
    hltL1VBFElectron_jPhi.clear();
    hltL1VBFElectron_jEnergy.clear();

    passhltL1VBFElectronLoose = 0;
    hltL1VBFElectronLoose_ePt.clear();
    hltL1VBFElectronLoose_eEta.clear();
    hltL1VBFElectronLoose_ePhi.clear();
    hltL1VBFElectronLoose_eEnergy.clear();
    hltL1VBFElectronLoose_jPt.clear();
    hltL1VBFElectronLoose_jEta.clear();
    hltL1VBFElectronLoose_jPhi.clear();
    hltL1VBFElectronLoose_jEnergy.clear();

    passDeepDiTau35HLT = 0;
    passDiTauControlHLT = 0;
    passInclusiveVBFHLT = 0; 
    passDeepInclusiveVBFHLT = 0; 
    passAltDeepInclusiveVBFHLT = 0; 
    passAltDeepInclusiveVBFNoMuonHLT = 0; 

    passVBF2DTHLT = 0;
    passVBF1DTHLT = 0;
    passVBF2DTLooseHLT = 0;

    passUpperControlHLT = 0;
    passLowerControlHLT = 0;

    passUpperControlMedHLT = 0;
    passLowerControlMedHLT = 0;

    pass2Tau1JetHLT = 0;
    pass2Tau1JetHigherHLT = 0;

    passIsoMu27LooseChargedTauHLT = 0;
    passIsoMu27LooseChargedHPSTauHLT = 0;
    passIsoMu27MediumChargedTauHLT = 0;
    passIsoMu27TightChargedTauHLT = 0;
    passIsoMu27DeepTauHLT = 0;

    // DiTau 32 L1 branches (there's a big OR with multiple DiTaus, but 32 is the lowest)
    passhltL1sDoubleTauBigOR = 0;
    hltL1sDoubleTauBigOR_pt.clear();
    hltL1sDoubleTauBigOR_eta.clear();
    hltL1sDoubleTauBigOR_phi.clear();
    hltL1sDoubleTauBigOR_energy.clear();


    passhltL1VBFDiJetOR = 0;
    hltL1VBFDiJetOR_pt.clear();
    hltL1VBFDiJetOR_eta.clear();
    hltL1VBFDiJetOR_phi.clear();
    hltL1VBFDiJetOR_energy.clear();

    passhltL1VBFDiJetIsoTau = 0;
    hltL1VBFDiJetIsoTau_nJets.clear();
    hltL1VBFDiJetIsoTau_jetPt.clear();
    hltL1VBFDiJetIsoTau_jetEta.clear();
    hltL1VBFDiJetIsoTau_jetPhi.clear();
    hltL1VBFDiJetIsoTau_jetEnergy.clear();
    hltL1VBFDiJetIsoTau_nTaus.clear();
    hltL1VBFDiJetIsoTau_tauPt.clear();
    hltL1VBFDiJetIsoTau_tauEta.clear();
    hltL1VBFDiJetIsoTau_tauPhi.clear();
    hltL1VBFDiJetIsoTau_tauEnergy.clear();

    passhltL1sSingleMu22 = 0;
    hltL1sSingleMu22_pt.clear();
    hltL1sSingleMu22_eta.clear();
    hltL1sSingleMu22_phi.clear();
    hltL1sSingleMu22_energy.clear();

    passhltL1sMu22er2p1IsoTau28er2p1 = 0;
    hltL1sMu22er2p1IsoTau28er2p1_muPt.clear();
    hltL1sMu22er2p1IsoTau28er2p1_muEta.clear();
    hltL1sMu22er2p1IsoTau28er2p1_muPhi.clear();
    hltL1sMu22er2p1IsoTau28er2p1_muEnergy.clear();
    hltL1sMu22er2p1IsoTau28er2p1_tauPt.clear();
    hltL1sMu22er2p1IsoTau28er2p1_tauEta.clear();
    hltL1sMu22er2p1IsoTau28er2p1_tauPhi.clear();
    hltL1sMu22er2p1IsoTau28er2p1_tauEnergy.clear();



    // Start VBF Double Deep Tau
    passhltL2VBFIsoTauNNFilter = 0;
    hltL2VBFIsoTauNNFilter_pt.clear();

    //
    passhltHpsSelectedPFTausMediumDitauWPDeepTauForVBFIsoTau = 0;
    hltHpsSelectedPFTausMediumDitauWPDeepTauForVBFIsoTau_pt.clear();

    passhltHpsSelectedPFTausTempLooseDitauWPDeepTauForVBFIsoTau = 0;
    hltHpsSelectedPFTausTempLooseDitauWPDeepTauForVBFIsoTau_pt.clear();

    //
    passhltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch = 0;
    hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_pt.clear();

    passhltHpsDoublePFTau20MediumDitauWPDeepTauNoMatchNoL2NN = 0;
    hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatchNoL2NN_pt.clear();

    passhltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatch = 0;
    hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatch_pt.clear();

    passhltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatchNoL2NN = 0;
    hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatchNoL2NN_pt.clear();
    
    //
    passhltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched = 0;
    hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_pt.clear();

    passhltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatchedNoL2NN = 0;
    hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatchedNoL2NN_pt.clear();

    passhltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatched = 0;
    hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatched_pt.clear();

    passhltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatchedNoL2NN = 0;
    hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatchedNoL2NN_pt.clear();

    //
    passhltRealDijetFilter = 0;
    hltRealDijetFilter_pt.clear();

    passhltVBFLooseIDPFDummyFilter = 0;
    hltVBFLooseIDPFDummyFilter_pt.clear();

    passhltVBFIsoTauL1TLooseIDPFJetsMatching = 0;
    hltVBFIsoTauL1TLooseIDPFJetsMatching_pt.clear();

    //
    passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20 = 0;
    hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20_pt.clear();

    passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20NoL2NN = 0;
    hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20NoL2NN_pt.clear();

    passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20 = 0;
    hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20_pt.clear();

    passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20NoL2NN = 0;
    hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20NoL2NN_pt.clear();

    passhltHpsDoublePFTau20BeforeDeepTau = 0;
    hltHpsDoublePFTau20BeforeDeepTau_pt.clear();

    passhltHpsDoublePFTau20withL2NNBeforeDeepTau = 0;
    hltHpsDoublePFTau20withL2NNBeforeDeepTau_pt.clear();

    passhltDoubleL2Tau20eta2p2 = 0;
    passhltDoubleL2GlobIsoTau20eta2p2 = 0;
    hltDoubleL2GlobIsoTau20eta2p2_pt.clear();

    passhltHpsDoublePFTau20TrackDeepTauIsoDitauWPForVBFIsoTau = 0;
    passhltHpsDoublePFTau20TrackDeepTauIsoDitauWPAgainstMuon = 0;

    hltHpsDoublePFTau20TrackDeepTauIsoDitauWPForVBFIsoTau_pt.clear();
    hltHpsDoublePFTau20TrackDeepTauIsoDitauWPAgainstMuon_pt.clear();

    passhltMatchedVBFTwoPFJets2CrossCleanedFromDoubleMediumDeepTauDitauWPPFTauHPS20 = 0;
    hltMatchedVBFTwoPFJets2CrossCleanedFromDoubleMediumDeepTauDitauWPPFTauHPS20_pt.clear();
    passhltMatchedVBFOnePFJet2CrossCleanedFromDoubleMediumDeepTauDitauWPPFTauHPS20 = 0;
    hltMatchedVBFOnePFJet2CrossCleanedFromDoubleMediumDeepTauDitauWPPFTauHPS20_pt.clear();
    // final two branches with different jet correlation producer
    passhltMatchedVBFTwoPFJetsPassingDiJetCorrCheckerWithMediumDiTauWPPFTauHPS20 = 0;
    hltMatchedVBFTwoPFJetsPassingDiJetCorrCheckerWithMediumDiTauWPPFTauHPS20_pt.clear();
    passhltMatchedVBFOnePFJetPassingDiJetCorrCheckerWithMediumDiTauWPPFTauHPS20 = 0;
    hltMatchedVBFOnePFJetPassingDiJetCorrCheckerWithMediumDiTauWPPFTauHPS20_pt.clear();

    passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedUsingDiJetCorrCheckerWithMediumDiTau = 0;
    hltMatchedVBFIsoTauTwoPFJets2CrossCleanedUsingDiJetCorrCheckerWithMediumDiTau_pt.clear();

    passhltMatchedVBFTwoPFJetsPassingDiJetCorrCheckerWithMediumDiTauWPPFTauHPS20NoAntiMuon = 0;
    passhltMatchedVBFOnePFJetPassingDiJetCorrCheckerWithMediumDiTauWPPFTauHPS20NoAntiMuon = 0;
    

    // getting trigger results, following this page
    // https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideHLTAnalysis
    edm::Handle<edm::TriggerResults> triggerResults;
    iEvent.getByToken(triggerResultToken_, triggerResults);
    edm::Handle<trigger::TriggerEvent> triggerEvent;
    iEvent.getByToken(triggerEventToken_, triggerEvent);
    const edm::TriggerNames triggerNames_ = iEvent.triggerNames(*triggerResults);

    // saving trigger results to respective branches
    //std::cout << "Can I print this?" << std::endl;
    
    // DiTau35 HLT
    std::string pathNameDiTauTrig = "HLT_DoubleTightChargedIsoPFTauHPS35_Trk1_eta2p1_v1";
    //passDiTau35HLT = triggerResults->accept(triggerNames_.triggerIndex(pathNameDiTauTrig));

    // DeepDiTau35 HLT and Control trigger
    std::string pathNameDeepDiTauTrig = "HLT_DoubleMediumDeepTauPFTauHPS35_L2NN_eta2p1_v1";
    passDeepDiTau35HLT = triggerResults->accept(triggerNames_.triggerIndex(pathNameDeepDiTauTrig));
    //std::cout << "pass " << pathNameDeepDiTauTrig << std::endl;

    std::string pathNameDiTauControl = "HLT_IsoMu24_eta2p1_MediumDeepTauPFTauHPS35_L2NN_eta2p1_CrossL1_v1";
    passDiTauControlHLT = triggerResults->accept(triggerNames_.triggerIndex(pathNameDiTauControl));
    //std::cout << "pass " << pathNameDiTauControl << std::endl;

    // Inclusive VBF HLT
    std::string pathNameInclusiveVBF = "HLT_VBF_DoubleTightChargedIsoPFTauHPS20_Trk1_eta2p1_v1";
    passInclusiveVBFHLT = triggerResults->accept(triggerNames_.triggerIndex(pathNameInclusiveVBF));
    //std::cout << "pass " << pathNameInclusiveVBF << std::endl;

    std::string pathNameDeepInclusiveVBF = "HLT_VBF_DoubleMediumDeepTauPFTauHPS20_eta2p1_v1";
    passDeepInclusiveVBFHLT = triggerResults->accept(triggerNames_.triggerIndex(pathNameDeepInclusiveVBF));
    //std::cout << "pass " << pathNameDeepInclusiveVBF << std::endl;

    std::string pathNameAltDeepInclusiveVBF = "HLT_VBF_DoubleMediumDeepTauPFTauHPS20_eta2p1_AltRmOvlp_v1";
    //passAltDeepInclusiveVBFHLT = triggerResults->accept(triggerNames_.triggerIndex(pathNameAltDeepInclusiveVBF));

    std::string pathNameAltDeepInclusiveVBFNoMuon = "HLT_VBF_DoubleMediumDeepTauPFTauHPS20_eta2p1_AltRmOvlp_NoAntiMuon_v1";
    //passAltDeepInclusiveVBFNoMuonHLT = triggerResults->accept(triggerNames_.triggerIndex(pathNameAltDeepInclusiveVBFNoMuon);

    // VBF + 2 Deep Tau HLT Medium w L2NN and Loose with No L2NN
    std::string pathNameVBF2DT = "HLT_DoublePFJets40_Mass500_MediumDeepTauPFTauHPS45_L2NN_MediumDeepTauPFTauHPS20_eta2p1_v1"; 
    passVBF2DTHLT = triggerResults->accept(triggerNames_.triggerIndex(pathNameVBF2DT));
    //std::cout << "pass " << pathNameVBF2DT << std::endl;

    std::string pathNameVBF2DTLooseNoL2NN = "HLT_DoublePFJets40_Mass500_LooseDeepTauIsoPFTauHPS45_LooseDeepTauIsoPFTauHPS20_eta2p1_v1"; 
    //passVBF2DTLooseHLT = triggerResults->accept(triggerNames_.triggerIndex(pathNameVBF2DTLooseNoL2NN));

    // My Control Paths
    std::string pathNameUpperControlMed = "HLT_IsoMu24_eta2p1_MediumDeepTauPFTauHPS45_L2NN_eta2p1_CrossL1_v1";
    passUpperControlMedHLT = triggerResults->accept(triggerNames_.triggerIndex(pathNameUpperControlMed));
    //std::cout << "pass " << pathNameUpperControlMed << std::endl;


    std::string pathNameLowerControlMed = "HLT_IsoMu24_eta2p1_MediumDeepTauPFTauHPS20_eta2p1_SingleL1_v1";
    passLowerControlMedHLT = triggerResults->accept(triggerNames_.triggerIndex(pathNameLowerControlMed));
    //std::cout << "pass " << pathNameLowerControlMed << std::endl;

    std::string pathNameUpperControl = "HLT_IsoMu24_eta2p1_LooseDeepTauIsoPFTauHPS45_eta2p1_CrossL1_v1";
    //passUpperControlHLT = triggerResults->accept(triggerNames_.triggerIndex(pathNameUpperControl));
    std::string pathNameLowerControl = "HLT_IsoMu24_eta2p1_LooseDeepTauIsoPFTauHPS20_eta2p1_SingleL1_v1";
    //passLowerControlHLT = triggerResults->accept(triggerNames_.triggerIndex(pathNameLowerControl));

    // Spain Group Triggers
    std::string pathName2Tau1Jet = "HLT_DoubleMediumDeepTauPFTauHPS30_L2NN_eta2p1_PFJet60_v1";
    pass2Tau1JetHLT = triggerResults->accept(triggerNames_.triggerIndex(pathName2Tau1Jet));
    //std::cout << "pass " << pathName2Tau1Jet << std::endl;

    std::string pathName2Tau1JetHigher = "HLT_DoubleMediumDeepTauPFTauHPS30_L2NN_eta2p1_PFJet75_v1";
    pass2Tau1JetHigherHLT = triggerResults->accept(triggerNames_.triggerIndex(pathName2Tau1JetHigher));
    //std::cout << "pass " << pathName2Tau1JetHigher << std::endl;

    // VBF + 1 Deep Tau
    std::string pathNameVBF1DT = "HLT_DoublePFJets40_Mass500_MediumDeepTauIsoPFTauHPS45_L2NN_eta2p1_v1";
    //passVBF1DTHLT = triggerResults->accept(triggerNames_.triggerIndex(pathNameVBF1DT));
    
    //Liam Monitoring
    std::string pathNameIsoMu27LooseChargedTauHLT = "HLT_IsoMu27_LooseChargedIsoPFTau20_Trk1_eta2p1_SingleL1_v5";
    std::string pathNameIsoMu27LooseChargedHPSTauHLT = "HLT_IsoMu27_LooseChargedIsoPFTauHPS20_Trk1_eta2p1_SingleL1_v1";
    std::string pathNameIsoMu27MediumChargedTauHLT = "HLT_IsoMu27_MediumChargedIsoPFTauHPS20_Trk1_eta2p1_SingleL1_v1";
    std::string pathNameIsoMu27TightChargedTauHLT = "HLT_IsoMu27_TightChargedIsoPFTauHPS20_Trk1_eta2p1_SingleL1_v1";
    std::string pathNameIsoMu27DeepTauHLT = "HLT_IsoMu27_MediumDeepTauIsoPFTauHPS20_eta2p1_SingleL1_v1";

    //passIsoMu27LooseChargedTauHLT = triggerResults->accept(triggerNames_.triggerIndex(pathNameIsoMu27LooseChargedTauHLT));
    //passIsoMu27LooseChargedHPSTauHLT = triggerResults->accept(triggerNames_.triggerIndex(pathNameIsoMu27LooseChargedHPSTauHLT));
    //passIsoMu27MediumChargedTauHLT = triggerResults->accept(triggerNames_.triggerIndex(pathNameIsoMu27MediumChargedTauHLT));
    //passIsoMu27TightChargedTauHLT = triggerResults->accept(triggerNames_.triggerIndex(pathNameIsoMu27TightChargedTauHLT));
    //passIsoMu27DeepTauHLT = triggerResults->accept(triggerNames_.triggerIndex(pathNameIsoMu27DeepTauHLT));

    std::string pathNameHLTDummyL1 = "HLT_DummyL1_v1";
    std::string pathNameHLTDummyL1Loose = "HLT_DummyL1Loose_v1";
    std::string pathNameHLTDummyEGORL1 = "HLT_DummyEGORL1_v1";

    passHLTDummyL1 = triggerResults->accept(triggerNames_.triggerIndex(pathNameHLTDummyL1));
    //std::cout << "pass " << pathNameHLTDummyL1 << std::endl;

    passHLTDummyL1Loose = triggerResults->accept(triggerNames_.triggerIndex(pathNameHLTDummyL1Loose));
    //std::cout << "pass " << pathNameHLTDummyL1Loose << std::endl;

    passHLTDummyEGORL1 = triggerResults->accept(triggerNames_.triggerIndex(pathNameHLTDummyEGORL1));
    //std::cout << "pass " << pathNameHLTDummyEGORL1 << std::endl;
    
    std::string pathNameEleTauHLT = "HLT_Ele24_eta2p1_WPTight_Gsf_LooseDeepTauPFTauHPS30_eta2p1_CrossL1_v1";
    passEleTauHLT = triggerResults->accept(triggerNames_.triggerIndex(pathNameEleTauHLT));



    // filling branches with triggerObjs information, hltL1VBFDiJetIsoTau object info filled separately since it's a weird L1
    // vids and available RefVec classes defined here
    // https://github.com/cms-sw/cmssw/blob/8b101cb0f00c4a961bc4a6d49512ef0335486f40/DataFormats/HLTReco/interface/TriggerRefsCollections.h

    // getting trigger refs for hltL1VBFDiJetIsoTau filter's tau/jet splitting
    edm::Handle<trigger::TriggerEventWithRefs> triggerEventWithRefsHandle_;
    iEvent.getByToken(triggerEventWithRefsToken_, triggerEventWithRefsHandle_);
    const unsigned int filterIndex(triggerEventWithRefsHandle_->filterIndex(InputTag("hltL1VBFDiJetIsoTau", "", "MYOTHERHLT")));
		//making jet object and filling vector
    l1t::JetVectorRef jetCandRefVec;
    trigger::Vids jvids;
    triggerEventWithRefsHandle_->getObjects(filterIndex, jvids, jetCandRefVec);
		//making tau object and filling vector
    l1t::TauVectorRef tauCandRefVec;
    trigger::Vids tvids;
    triggerEventWithRefsHandle_->getObjects(filterIndex, tvids, tauCandRefVec);

    const unsigned int nJets(jvids.size());
    if (nJets > 0) {
        hltL1VBFDiJetIsoTau_nJets.push_back(nJets);
        for (unsigned int i = 0; i != nJets; ++i) {
	    hltL1VBFDiJetIsoTau_jetPt.push_back(jetCandRefVec[i]->pt());
	    hltL1VBFDiJetIsoTau_jetEta.push_back(jetCandRefVec[i]->eta());
   	    hltL1VBFDiJetIsoTau_jetPhi.push_back(jetCandRefVec[i]->phi());
   	    hltL1VBFDiJetIsoTau_jetEnergy.push_back(jetCandRefVec[i]->energy());
        }
    }

    const unsigned int nTaus(tvids.size());
    if (nTaus > 0) {
	hltL1VBFDiJetIsoTau_nTaus.push_back(nTaus);
	for (unsigned int i = 0; i != nTaus; ++i) {
	    hltL1VBFDiJetIsoTau_tauPt.push_back(tauCandRefVec[i]->pt());
	    hltL1VBFDiJetIsoTau_tauEta.push_back(tauCandRefVec[i]->eta());
   	    hltL1VBFDiJetIsoTau_tauPhi.push_back(tauCandRefVec[i]->phi());
   	    hltL1VBFDiJetIsoTau_tauEnergy.push_back(tauCandRefVec[i]->energy());
	}
    }

    // same for UpperControl L1

    const unsigned int muTauUpperControlL1Filter(triggerEventWithRefsHandle_->filterIndex(InputTag("hltL1sBigOrMuXXerIsoTauYYer", "", "MYOTHERHLT")));

    l1t::MuonVectorRef muonCandRefVec;
    trigger::Vids mVids;
    triggerEventWithRefsHandle_->getObjects(muTauUpperControlL1Filter, mVids, muonCandRefVec);

    const unsigned int nMuons(mVids.size());
    if (nMuons > 0) {
      for (unsigned int i = 0; i != nMuons; ++i) {
        hltL1sMu22er2p1IsoTau28er2p1_muPt.push_back(muonCandRefVec[i]->pt());
        hltL1sMu22er2p1IsoTau28er2p1_muEta.push_back(muonCandRefVec[i]->eta());
        hltL1sMu22er2p1IsoTau28er2p1_muPhi.push_back(muonCandRefVec[i]->phi());
        hltL1sMu22er2p1IsoTau28er2p1_muEnergy.push_back(muonCandRefVec[i]->energy());
      }
    }

    l1t::TauVectorRef tauUpperControlCandRefVec;
    trigger::Vids tUpperVids;
    triggerEventWithRefsHandle_->getObjects(muTauUpperControlL1Filter, tUpperVids, tauUpperControlCandRefVec);

    const unsigned int tUpperVidsSize(tUpperVids.size());
    if (tUpperVidsSize > 0) {
      for (unsigned int i = 0; i != tUpperVidsSize; ++i) {
        hltL1sMu22er2p1IsoTau28er2p1_tauPt.push_back(tauUpperControlCandRefVec[i]->pt());
        hltL1sMu22er2p1IsoTau28er2p1_tauEta.push_back(tauUpperControlCandRefVec[i]->eta());
        hltL1sMu22er2p1IsoTau28er2p1_tauPhi.push_back(tauUpperControlCandRefVec[i]->phi());
        hltL1sMu22er2p1IsoTau28er2p1_tauEnergy.push_back(tauUpperControlCandRefVec[i]->energy());
      }
    }

    // Also for VBF + Electron
    const unsigned int VBFElectronL1Filter(triggerEventWithRefsHandle_->filterIndex(InputTag("hltL1VBFElectron", "", "MYOTHERHLT")));

    l1t::EGammaVectorRef electronCandRefVec;
    trigger::Vids eVids;
    triggerEventWithRefsHandle_->getObjects(VBFElectronL1Filter, eVids, electronCandRefVec);

    const unsigned int nElectrons(eVids.size());
    if (nElectrons > 0) {
      for (unsigned int i = 0; i != nElectrons; ++i) {
        hltL1VBFElectron_ePt.push_back(electronCandRefVec[i]->pt());
        hltL1VBFElectron_eEta.push_back(electronCandRefVec[i]->eta());
        hltL1VBFElectron_ePhi.push_back(electronCandRefVec[i]->phi());
        hltL1VBFElectron_eEnergy.push_back(electronCandRefVec[i]->energy());
      }
    }

    l1t::JetVectorRef VBFElectronJetRefVec;
    trigger::Vids ejVids;
    triggerEventWithRefsHandle_->getObjects(VBFElectronL1Filter, ejVids, VBFElectronJetRefVec);
   
    const unsigned int nVBFElectronJets(ejVids.size());
    if (nVBFElectronJets > 0) {
      for (unsigned int i = 0; i != nVBFElectronJets; ++ i) {
        hltL1VBFElectron_jPt.push_back(VBFElectronJetRefVec[i]->pt());
        hltL1VBFElectron_jEta.push_back(VBFElectronJetRefVec[i]->eta());
        hltL1VBFElectron_jPhi.push_back(VBFElectronJetRefVec[i]->phi());
        hltL1VBFElectron_jEnergy.push_back(VBFElectronJetRefVec[i]->energy());
      }
    }
  
    // again for VBF + Loose L1 Electron
    const unsigned int VBFElectronL1LooseFilter(triggerEventWithRefsHandle_->filterIndex(InputTag("hltL1VBFElectronLoose", "", "MYOTHERHLT")));

    l1t::EGammaVectorRef looseElectronCandRefVec;
    trigger::Vids leVids;
    triggerEventWithRefsHandle_->getObjects(VBFElectronL1LooseFilter, leVids, looseElectronCandRefVec);

    const unsigned int nLooseElectrons(leVids.size());
    if (nLooseElectrons > 0) {
      for (unsigned int i = 0; i != nLooseElectrons; ++i) {
        hltL1VBFElectronLoose_ePt.push_back(looseElectronCandRefVec[i]->pt());
        hltL1VBFElectronLoose_eEta.push_back(looseElectronCandRefVec[i]->eta());
        hltL1VBFElectronLoose_ePhi.push_back(looseElectronCandRefVec[i]->phi());
        hltL1VBFElectronLoose_eEnergy.push_back(looseElectronCandRefVec[i]->energy());
      }
    }

    l1t::JetVectorRef VBFLooseElectronJetRefVec;
    trigger::Vids lejVids;
    triggerEventWithRefsHandle_->getObjects(VBFElectronL1LooseFilter, lejVids, VBFLooseElectronJetRefVec);
   
    const unsigned int nVBFLooseElectronJets(lejVids.size());
    if (nVBFLooseElectronJets > 0) {
      for (unsigned int i = 0; i != nVBFLooseElectronJets; ++ i) {
        hltL1VBFElectronLoose_jPt.push_back(VBFLooseElectronJetRefVec[i]->pt());
        hltL1VBFElectronLoose_jEta.push_back(VBFLooseElectronJetRefVec[i]->eta());
        hltL1VBFElectronLoose_jPhi.push_back(VBFLooseElectronJetRefVec[i]->phi());
        hltL1VBFElectronLoose_jEnergy.push_back(VBFLooseElectronJetRefVec[i]->energy());
      }
    }


    // make strings to identify filter names
    const trigger::size_type nFilters(triggerEvent->sizeFilters());
    std::string hltL1sDoubleTauBigOR_Tag = "hltL1sDoubleTauBigOR::MYOTHERHLT"; // ditau L1
    std::string hltL1VBFDiJetOR_Tag = "hltL1VBFDiJetOR::MYOTHERHLT";		  // inclusive L1
    std::string hltL1VBFDiJetIsoTau_Tag = "hltL1VBFDiJetIsoTau::MYOTHERHLT";	  
    std::string hltL1sSingleMu22_Tag = "hltL1sSingleMu22::MYOTHERHLT";
    std::string hltL1sMu22er2p1IsoTau28er2p1_Tag = "hltL1sMu22er2p1IsoTau28er2p1::MYOTHERHLT";

    // Start VBF Double Deep Tau
    std::string hltL2VBFIsoTauNNFilter_Tag = "hltL2VBFIsoTauNNFilter::MYOTHERHLT";
    //
    std::string hltHpsSelectedPFTausMediumDitauWPDeepTauForVBFIsoTau_Tag = "hltHpsSelectedPFTausMediumDitauWPDeepTauForVBFIsoTau::MYOTHERHLT";
    std::string hltHpsSelectedPFTausTempLooseDitauWPDeepTauForVBFIsoTau_Tag = "hltHpsSelectedPFTausTempLooseDitauWPDeepTauForVBFIsoTau::MYOTHERHLT";
    //
    std::string hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_Tag = "hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch::MYOTHERHLT";
    std::string hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatchNoL2NN_Tag = "hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatchNoL2NN::MYOTHERHLT";
    std::string hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatch_Tag = "hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatch::MYOTHERHLT";
    std::string hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatchNoL2NN_Tag = "hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatchNoL2NN::MYOTHERHLT";
    //
    std::string hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_Tag = "hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched::MYOTHERHLT";
    std::string hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatchedNoL2NN_Tag = "hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatchedNoL2NN::MYOTHERHLT";
    std::string hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatched_Tag = "hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatched::MYOTHERHLT";
    std::string hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatchedNoL2NN_Tag = "hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatchedNoL2NN::MYOTHERHLT";
    //
    std::string hltRealDijetFilter_Tag = "hltRealDijetFilter::MYOTHERHLT";
    std::string hltVBFLooseIDPFDummyFilter_Tag = "hltVBFLooseIDPFDummyFilter::MYOTHERHLT";
    std::string hltVBFIsoTauL1TLooseIDPFJetsMatching_Tag = "hltVBFIsoTauL1TLooseIDPFJetsMatching::MYOTHERHLT";
    //
    std::string hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20_Tag = "hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20::MYOTHERHLT";
    std::string hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20NoL2NN_Tag = "hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20NoL2NN::MYOTHERHLT";
    std::string hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20_Tag = "hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20::MYOTHERHLT";
    std::string hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20NoL2NN_Tag = "hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20NoL2NN::MYOTHERHLT";

    std::string hltHpsDoublePFTau20BeforeDeepTau_Tag = "hltHpsDoublePFTau20BeforeDeepTau::MYOTHERHLT";
    std::string hltHpsDoublePFTau20withL2NNBeforeDeepTau_Tag = "hltHpsDoublePFTau20withL2NNBeforeDeepTau::MYOTHERHLT";

    // strings for DeepVBF
    std::string hltDoubleL2Tau20eta2p2_Tag = "hltDoubleL2Tau20eta2p2::MYOTHERHLT";
    std::string hltDoubleL2GlobIsoTau20eta2p2_Tag = "hltDoubleL2GlobIsoTau20eta2p2::MYOTHERHLT";

    std::string hltHpsDoublePFTau20TrackDeepTauIsoDitauWPForVBFIsoTau_Tag = "hltHpsDoublePFTau20TrackDeepTauIsoDitauWPForVBFIsoTau::MYOTHERHLT";
    std::string hltHpsDoublePFTau20TrackDeepTauIsoDitauWPAgainstMuon_Tag = "hltHpsDoublePFTau20TrackDeepTauIsoDitauWPAgainstMuon::MYOTHERHLT";

    std::string hltMatchedVBFTwoPFJets2CrossCleanedFromDoubleMediumDeepTauDitauWPPFTauHPS20_Tag = "hltMatchedVBFTwoPFJets2CrossCleanedFromDoubleMediumDeepTauDitauWPPFTauHPS20::MYOTHERHLT";
    std::string hltMatchedVBFOnePFJet2CrossCleanedFromDoubleMediumDeepTauDitauWPPFTauHPS20_Tag = "hltMatchedVBFOnePFJet2CrossCleanedFromDoubleMediumDeepTauDitauWPPFTauHPS20::MYOTHERHLT";
    std::string hltMatchedVBFTwoPFJetsPassingDiJetCorrCheckerWithMediumDiTauWPPFTauHPS20_Tag = "hltMatchedVBFTwoPFJetsPassingDiJetCorrCheckerWithMediumDiTauWPPFTauHPS20::MYOTHERHLT";
    std::string hltMatchedVBFOnePFJetPassingDiJetCorrCheckerWithMediumDiTauWPPFTauHPS20_Tag = "hltMatchedVBFOnePFJetPassingDiJetCorrCheckerWithMediumDiTauWPPFTauHPS20::MYOTHERHLT";

    std::string hltMatchedVBFIsoTauTwoPFJets2CrossCleanedUsingDiJetCorrCheckerWithMediumDiTau_Tag = "hltMatchedVBFIsoTauTwoPFJets2CrossCleanedUsingDiJetCorrCheckerWithMediumDiTau::MYOTHERHLT";

    std::string hltMatchedVBFTwoPFJetsPassingDiJetCorrCheckerWithMediumDiTauWPPFTauHPS20NoAntiMuon_Tag = "hltMatchedVBFTwoPFJetsPassingDiJetCorrCheckerWithMediumDiTauWPPFTauHPS20NoAntiMuon::MYOTHERHLT";
    std::string hltMatchedVBFOnePFJetPassingDiJetCorrCheckerWithMediumDiTauWPPFTauHPS20NoAntiMuon_Tag = "hltMatchedVBFOnePFJetPassingDiJetCorrCheckerWithMediumDiTauWPPFTauHPS20NoAntiMuon::MYOTHERHLT";

    std::string hltL1VBFElectron_Tag = "hltL1VBFElectron::MYOTHERHLT";
    std::string hltL1VBFElectronLoose_Tag = "hltL1VBFElectronLoose::MYOTHERHLT";

    // accepted filters per event
    for(trigger::size_type iFilter=0; iFilter!=nFilters; ++iFilter) {
	std::string filterTag = triggerEvent->filterTag(iFilter).encode();
	trigger::Keys objectKeys = triggerEvent->filterKeys(iFilter);

	const trigger::TriggerObjectCollection& triggerObjects(triggerEvent->getObjects());
	// fill "pass filter" branches
	int nObjKeys = objectKeys.size();
	if (filterTag == hltL1VBFDiJetOR_Tag && nObjKeys >= 0) nEvents = 1; // accept pass or fail condition to fill nEvents

        // L1s
	if (filterTag == hltL1sDoubleTauBigOR_Tag && nObjKeys >= 2) passhltL1sDoubleTauBigOR = 1;
	if (filterTag == hltL1VBFDiJetOR_Tag && nObjKeys >= 2) passhltL1VBFDiJetOR = 1;
	if (filterTag == hltL1VBFDiJetIsoTau_Tag && hltL1VBFDiJetIsoTau_tauPt.size() >= 1
						 && hltL1VBFDiJetIsoTau_jetPt.size() >= 2) passhltL1VBFDiJetIsoTau = 1;
        if (filterTag == hltL1sSingleMu22_Tag && nObjKeys >= 1) passhltL1sSingleMu22 = 1;
        if (filterTag == hltL1sMu22er2p1IsoTau28er2p1_Tag && hltL1sMu22er2p1IsoTau28er2p1_muPt.size() >= 1
                                                          && hltL1sMu22er2p1IsoTau28er2p1_tauPt.size() >= 1) passhltL1sMu22er2p1IsoTau28er2p1 = 1;
        if (filterTag == hltL1VBFElectron_Tag && hltL1VBFElectron_ePt.size() >=1 && hltL1VBFElectron_jPt.size() >= 2) passhltL1VBFElectron = 1; 
        if (filterTag == hltL1VBFElectronLoose_Tag && hltL1VBFElectronLoose_ePt.size() >= 1 && hltL1VBFElectronLoose_jPt.size() >= 2) passhltL1VBFElectronLoose = 1;


        // VBFPlusTwoDeepTau Modules
        if (filterTag == hltL2VBFIsoTauNNFilter_Tag && nObjKeys >= 1) passhltL2VBFIsoTauNNFilter = 1;
        if (filterTag == hltHpsDoublePFTau20BeforeDeepTau_Tag && nObjKeys >= 2) passhltHpsDoublePFTau20BeforeDeepTau = 1;
        if (filterTag == hltHpsDoublePFTau20withL2NNBeforeDeepTau_Tag && nObjKeys >= 2) passhltHpsDoublePFTau20withL2NNBeforeDeepTau = 1;
        //
        if (filterTag == hltHpsSelectedPFTausMediumDitauWPDeepTauForVBFIsoTau_Tag && nObjKeys >= 1) passhltHpsSelectedPFTausMediumDitauWPDeepTauForVBFIsoTau = 1;
        if (filterTag == hltHpsSelectedPFTausTempLooseDitauWPDeepTauForVBFIsoTau_Tag && nObjKeys >= 1) passhltHpsSelectedPFTausTempLooseDitauWPDeepTauForVBFIsoTau = 1;
        //
        if (filterTag == hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_Tag && nObjKeys >= 2) passhltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch = 1;
        if (filterTag == hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatchNoL2NN_Tag && nObjKeys >= 2) passhltHpsDoublePFTau20MediumDitauWPDeepTauNoMatchNoL2NN = 1;
        if (filterTag == hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatch_Tag && nObjKeys >= 2) passhltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatch = 1;
        if (filterTag == hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatchNoL2NN_Tag && nObjKeys >= 2) passhltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatchNoL2NN = 1;
        //
        if (filterTag == hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_Tag && nObjKeys >= 1) passhltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched = 1;
        if (filterTag == hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatchedNoL2NN_Tag && nObjKeys >= 1) passhltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatchedNoL2NN = 1;
        if (filterTag == hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatched_Tag && nObjKeys >= 1) passhltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatched = 1;
        if (filterTag == hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatchedNoL2NN_Tag && nObjKeys >= 1) passhltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatchedNoL2NN = 1;
        //
        if (filterTag == hltRealDijetFilter_Tag && nObjKeys >= 2) passhltRealDijetFilter = 1;
        if (filterTag == hltVBFLooseIDPFDummyFilter_Tag && nObjKeys >= 2) passhltVBFLooseIDPFDummyFilter = 1;
        if (filterTag == hltVBFIsoTauL1TLooseIDPFJetsMatching_Tag && nObjKeys >= 2) passhltVBFIsoTauL1TLooseIDPFJetsMatching = 1;
        //
        if (filterTag == hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20_Tag && nObjKeys >= 2) passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20 = 1;
        if (filterTag == hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20NoL2NN_Tag && nObjKeys >= 2) passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20NoL2NN = 1;
        if (filterTag == hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20_Tag && nObjKeys >= 2) passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20 = 1;
        if (filterTag == hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20NoL2NN_Tag && nObjKeys >= 2) passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20NoL2NN = 1;

        if (filterTag == hltDoubleL2Tau20eta2p2_Tag && nObjKeys >= 2) passhltDoubleL2Tau20eta2p2 = 1;
        if (filterTag == hltDoubleL2GlobIsoTau20eta2p2_Tag && nObjKeys >= 2) passhltDoubleL2GlobIsoTau20eta2p2 = 1;

        if (filterTag == hltHpsDoublePFTau20TrackDeepTauIsoDitauWPForVBFIsoTau_Tag && nObjKeys >= 2) passhltHpsDoublePFTau20TrackDeepTauIsoDitauWPForVBFIsoTau = 1;
        if (filterTag == hltHpsDoublePFTau20TrackDeepTauIsoDitauWPAgainstMuon_Tag && nObjKeys >= 2) passhltHpsDoublePFTau20TrackDeepTauIsoDitauWPAgainstMuon = 1;

        if (filterTag == hltMatchedVBFTwoPFJets2CrossCleanedFromDoubleMediumDeepTauDitauWPPFTauHPS20_Tag && nObjKeys >= 2) passhltMatchedVBFTwoPFJets2CrossCleanedFromDoubleMediumDeepTauDitauWPPFTauHPS20 = 1;
        if (filterTag == hltMatchedVBFOnePFJet2CrossCleanedFromDoubleMediumDeepTauDitauWPPFTauHPS20_Tag && nObjKeys >= 1) passhltMatchedVBFOnePFJet2CrossCleanedFromDoubleMediumDeepTauDitauWPPFTauHPS20 = 1;
        if (filterTag == hltMatchedVBFTwoPFJetsPassingDiJetCorrCheckerWithMediumDiTauWPPFTauHPS20_Tag && nObjKeys >= 2) passhltMatchedVBFTwoPFJetsPassingDiJetCorrCheckerWithMediumDiTauWPPFTauHPS20 = 1;
        if (filterTag == hltMatchedVBFOnePFJetPassingDiJetCorrCheckerWithMediumDiTauWPPFTauHPS20_Tag && nObjKeys >= 1) passhltMatchedVBFOnePFJetPassingDiJetCorrCheckerWithMediumDiTauWPPFTauHPS20 = 1;

        if (filterTag == hltMatchedVBFIsoTauTwoPFJets2CrossCleanedUsingDiJetCorrCheckerWithMediumDiTau_Tag && nObjKeys >= 2) passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedUsingDiJetCorrCheckerWithMediumDiTau = 1;

        if (filterTag == hltMatchedVBFTwoPFJetsPassingDiJetCorrCheckerWithMediumDiTauWPPFTauHPS20NoAntiMuon_Tag && nObjKeys >= 2) passhltMatchedVBFTwoPFJetsPassingDiJetCorrCheckerWithMediumDiTauWPPFTauHPS20NoAntiMuon = 1;
        if (filterTag == hltMatchedVBFOnePFJetPassingDiJetCorrCheckerWithMediumDiTauWPPFTauHPS20NoAntiMuon_Tag && nObjKeys >= 1) passhltMatchedVBFOnePFJetPassingDiJetCorrCheckerWithMediumDiTauWPPFTauHPS20NoAntiMuon = 1;

	//loop over trigger objects and store their kinematics to the proper filter branches
	for(trigger::size_type iKey=0; iKey < nObjKeys; ++iKey){
	    trigger::size_type objKey = objectKeys.at(iKey);
	    const trigger::TriggerObject& triggerObj(triggerObjects[objKey]);
	    pt_ = triggerObj.pt();
	    eta_ = triggerObj.eta();
	    phi_ = triggerObj.phi();
	    energy_ = triggerObj.energy();
	// fill ditau and inclusive L1 branches (proposed L1 branches filled separately because it has two types of objects)
	    if (filterTag == hltL1sDoubleTauBigOR_Tag 
                  && passhltL1sDoubleTauBigOR && pt_>0) {
		hltL1sDoubleTauBigOR_pt.push_back(pt_);
		hltL1sDoubleTauBigOR_eta.push_back(eta_);
		hltL1sDoubleTauBigOR_phi.push_back(phi_);
		hltL1sDoubleTauBigOR_energy.push_back(energy_);
	    }
	    if (filterTag == hltL1VBFDiJetOR_Tag 
                  && passhltL1VBFDiJetOR && pt_>0) {
		hltL1VBFDiJetOR_pt.push_back(pt_);
		hltL1VBFDiJetOR_eta.push_back(eta_);
		hltL1VBFDiJetOR_phi.push_back(phi_);
		hltL1VBFDiJetOR_energy.push_back(energy_);
	    }
            if (filterTag == hltL1sSingleMu22_Tag
                  && passhltL1sSingleMu22 && pt_>0) {
                hltL1sSingleMu22_pt.push_back(pt_);
                hltL1sSingleMu22_eta.push_back(eta_);
                hltL1sSingleMu22_phi.push_back(phi_);
                hltL1sSingleMu22_energy.push_back(energy_);
            }

        // Start VBF Double Deep Tau
        // fill hltL2VBFIsoTauNNFilter if match
            if (filterTag == hltL2VBFIsoTauNNFilter_Tag
                 && passhltL2VBFIsoTauNNFilter && pt_>0) {
               hltL2VBFIsoTauNNFilter_pt.push_back(pt_);
            }
            if (filterTag == hltHpsDoublePFTau20BeforeDeepTau_Tag
                 && passhltHpsDoublePFTau20BeforeDeepTau && pt_>0) {
               hltHpsDoublePFTau20BeforeDeepTau_pt.push_back(pt_);
            }
            if (filterTag == hltHpsDoublePFTau20withL2NNBeforeDeepTau_Tag
                 && passhltHpsDoublePFTau20withL2NNBeforeDeepTau && pt_>0) {
               hltHpsDoublePFTau20withL2NNBeforeDeepTau_pt.push_back(pt_);
            }

        //
        // fill hltHpsSelectedPFTausMediumDitauWPDeepTauForVBFIsoTau if match
            if (filterTag == hltHpsSelectedPFTausMediumDitauWPDeepTauForVBFIsoTau_Tag
                 && passhltHpsSelectedPFTausMediumDitauWPDeepTauForVBFIsoTau && pt_>0) {
               hltHpsSelectedPFTausMediumDitauWPDeepTauForVBFIsoTau_pt.push_back(pt_);
            }
        // fill hltHpsSelectedPFTausTempLooseDitauWPDeepTauForVBFIsoTau if match
            if (filterTag == hltHpsSelectedPFTausTempLooseDitauWPDeepTauForVBFIsoTau_Tag
                 && passhltHpsSelectedPFTausTempLooseDitauWPDeepTauForVBFIsoTau && pt_>0) {
               hltHpsSelectedPFTausTempLooseDitauWPDeepTauForVBFIsoTau_pt.push_back(pt_);
            }
        //
        // fill hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch if match
            if (filterTag == hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_Tag
                 && passhltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch && pt_>0) {
               hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_pt.push_back(pt_);
            }
        // fill hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatchNoL2NN if match
            if (filterTag == hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatchNoL2NN_Tag
                 && passhltHpsDoublePFTau20MediumDitauWPDeepTauNoMatchNoL2NN && pt_>0) {
               hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatchNoL2NN_pt.push_back(pt_);
            }
        // fill hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatch if match
            if (filterTag == hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatch_Tag
                 && passhltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatch && pt_>0) {
               hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatch_pt.push_back(pt_);
            }
        // fill hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatchNoL2NN if match
            if (filterTag == hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatchNoL2NN_Tag
                 && passhltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatchNoL2NN && pt_>0) {
               hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatchNoL2NN_pt.push_back(pt_);
            }
        //
        // fill hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched if match
            if (filterTag == hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_Tag
                 && passhltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched && pt_>0) {
               hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_pt.push_back(pt_);
            }
        // fill hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatchedNoL2NN if match
            if (filterTag == hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatchedNoL2NN_Tag
                 && passhltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatchedNoL2NN && pt_>0) {
               hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatchedNoL2NN_pt.push_back(pt_);
            }
        // fill hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatched if match
            if (filterTag == hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatched_Tag
                 && passhltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatched && pt_>0) {
               hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatched_pt.push_back(pt_);
            }
        // fill hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatchedNoL2NN if match
            if (filterTag == hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatchedNoL2NN_Tag
                 && passhltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatchedNoL2NN && pt_>0) {
               hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatchedNoL2NN_pt.push_back(pt_);
            }
        //
        // fill hltRealDijetFilter if match
            if (filterTag == hltRealDijetFilter_Tag
                 && passhltRealDijetFilter && pt_>0) {
               hltRealDijetFilter_pt.push_back(pt_);
            }
        // fill hltVBFLooseIDPFDummyFilter if match
            if (filterTag == hltVBFLooseIDPFDummyFilter_Tag
                 && passhltVBFLooseIDPFDummyFilter && pt_>0) {
               hltVBFLooseIDPFDummyFilter_pt.push_back(pt_);
            }
        // fill hltVBFIsoTauL1TLooseIDPFJetsMatching if match
            if (filterTag == hltVBFIsoTauL1TLooseIDPFJetsMatching_Tag
                 && passhltVBFIsoTauL1TLooseIDPFJetsMatching && pt_>0) {
               hltVBFIsoTauL1TLooseIDPFJetsMatching_pt.push_back(pt_);
            }
        //
        // fill hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20 if match
            if (filterTag == hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20_Tag
                 && passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20 && pt_>0) {
               hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20_pt.push_back(pt_);
            }
        // fill hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20NoL2NN if match
            if (filterTag == hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20NoL2NN_Tag
                 && passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20NoL2NN && pt_>0) {
               hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20NoL2NN_pt.push_back(pt_);
            }
        // fill hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20 if match
            if (filterTag == hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20_Tag
                 && passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20 && pt_>0) {
               hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20_pt.push_back(pt_);
            }
        // fill hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20NoL2NN if match
            if (filterTag == hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20NoL2NN_Tag
                 && passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20NoL2NN && pt_>0) {
               hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20NoL2NN_pt.push_back(pt_);
            }
        // fill hltDoubleL2GlobIsoTau20eta2p2 pt if match
            if (filterTag == hltDoubleL2GlobIsoTau20eta2p2_Tag
                 && passhltDoubleL2GlobIsoTau20eta2p2 && pt_>0) {
               hltDoubleL2GlobIsoTau20eta2p2_pt.push_back(pt_);
            }
        // fill hltHpsDoublePFTau20TrackDeepTauIsoDitauWPForVBFIsoTau pt if match
            if (filterTag == hltHpsDoublePFTau20TrackDeepTauIsoDitauWPForVBFIsoTau_Tag
                 && passhltHpsDoublePFTau20TrackDeepTauIsoDitauWPForVBFIsoTau && pt_>0) {
               hltHpsDoublePFTau20TrackDeepTauIsoDitauWPForVBFIsoTau_pt.push_back(pt_);
            }
        // fill hltHpsDoublePFTau20TrackDeepTauIsoDitauWPAgainstMuon pt if match
            if (filterTag == hltHpsDoublePFTau20TrackDeepTauIsoDitauWPAgainstMuon_Tag
                 && passhltHpsDoublePFTau20TrackDeepTauIsoDitauWPAgainstMuon && pt_>0) {
               hltHpsDoublePFTau20TrackDeepTauIsoDitauWPAgainstMuon_pt.push_back(pt_);
            }

        // fill hltMatchedVBFTwoPFJets2CrossCleanedFromDoubleMediumDeepTauDitauWPPFTauHPS20 pt if match
            if (filterTag == hltMatchedVBFTwoPFJets2CrossCleanedFromDoubleMediumDeepTauDitauWPPFTauHPS20_Tag
                 && passhltMatchedVBFTwoPFJets2CrossCleanedFromDoubleMediumDeepTauDitauWPPFTauHPS20 && pt_>0) {
               hltMatchedVBFTwoPFJets2CrossCleanedFromDoubleMediumDeepTauDitauWPPFTauHPS20_pt.push_back(pt_);
            }
        // fill hltMatchedVBFOnePFJet2CrossCleanedFromDoubleMediumDeepTauDitauWPPFTauHPS20 pt if match
            if (filterTag == hltMatchedVBFOnePFJet2CrossCleanedFromDoubleMediumDeepTauDitauWPPFTauHPS20_Tag
                 && passhltMatchedVBFOnePFJet2CrossCleanedFromDoubleMediumDeepTauDitauWPPFTauHPS20 && pt_>0) {
               hltMatchedVBFOnePFJet2CrossCleanedFromDoubleMediumDeepTauDitauWPPFTauHPS20_pt.push_back(pt_);
            }
        // fill hltMatchedVBFTwoPFJetsPassingDiJetCorrCheckerWithMediumDiTauWPPFTauHPS20 pt if match
            if (filterTag == hltMatchedVBFTwoPFJetsPassingDiJetCorrCheckerWithMediumDiTauWPPFTauHPS20_Tag
                 && passhltMatchedVBFTwoPFJetsPassingDiJetCorrCheckerWithMediumDiTauWPPFTauHPS20 && pt_>0) {
               hltMatchedVBFTwoPFJetsPassingDiJetCorrCheckerWithMediumDiTauWPPFTauHPS20_pt.push_back(pt_);
            }
        // fill hltMatchedVBFOnePFJetPassingDiJetCorrCheckerWithMediumDiTauWPPFTauHPS20 pt if match
            if (filterTag == hltMatchedVBFOnePFJetPassingDiJetCorrCheckerWithMediumDiTauWPPFTauHPS20_Tag
                 && passhltMatchedVBFOnePFJetPassingDiJetCorrCheckerWithMediumDiTauWPPFTauHPS20 && pt_>0) {
               hltMatchedVBFOnePFJetPassingDiJetCorrCheckerWithMediumDiTauWPPFTauHPS20_pt.push_back(pt_);
            }
        // fill hltMatchedVBFIsoTauTwoPFJets2CrossCleanedUsingDiJetCorrCheckerWithMediumDiTau pt if match
            if (filterTag == hltMatchedVBFIsoTauTwoPFJets2CrossCleanedUsingDiJetCorrCheckerWithMediumDiTau_Tag
                 && passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedUsingDiJetCorrCheckerWithMediumDiTau && pt_>0) {
               hltMatchedVBFIsoTauTwoPFJets2CrossCleanedUsingDiJetCorrCheckerWithMediumDiTau_pt.push_back(pt_);
            }
	} // end loop over trigger object keys
    } // end loop over nfilters
} // end function
