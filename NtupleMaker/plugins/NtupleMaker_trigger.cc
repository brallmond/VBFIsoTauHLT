// Braden Allmond Nov 22nd 2021

#include "VBFIsoTauHLT/NtupleMaker/plugins/NtupleMaker.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/Common/interface/TriggerNames.h"

#include "DataFormats/Common/interface/TriggerResults.h"

using namespace std; // I think best practice is to include <vector> explicitly at the top of the file

int passDeepDiTau35HLT;
int passDiTauControl;
int passInclusiveVBFHLT;
int passVBFPlusTwoDeepTauHLT;

int passVBF2DTHLT;
int passVBF2DTTempLooseHLT;
int passVBF2DTNoL2NNHLT;
int passVBF2DTLooseNoL2NNHLT;
int passVBF2DTOldL1;

int passUpperControlHLT;
int passLowerControlHLT;
int passUpperControlMedHLT;
int passLowerControlMedHLT;

int pass2Tau1JetHLT;

float 	pt_;
float 	eta_;
float 	phi_;
float 	energy_;

int	nEvents;
//full trigger filter name is commented above each of its branches

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

//hltL1VBFDiJetIsoTau (previously called hltL1NewVBFDiJet) 
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

int passhltL1VBFDiJetIsoTauNoer;
vector<int> hltL1VBFDiJetIsoTauNoer_nJets;
vector<float> hltL1VBFDiJetIsoTauNoer_jetPt;
vector<int> hltL1VBFDiJetIsoTauNoer_nTaus;
vector<float> hltL1VBFDiJetIsoTauNoer_tauPt;


//branches for VBFPlusTwoDeepTauHLT
int passhltL2VBFIsoTauNNFilter;
vector<float> hltL2VBFIsoTauNNFilter_pt;
vector<float> hltL2VBFIsoTauNNFilter_eta;
vector<float> hltL2VBFIsoTauNNFilter_phi;
vector<float> hltL2VBFIsoTauNNFilter_energy;

int passhltHpsSelectedPFTausMediumDitauWPDeepTauForVBFIsoTau;
vector<float> hltHpsSelectedPFTausMediumDitauWPDeepTauForVBFIsoTau_pt;
vector<float> hltHpsSelectedPFTausMediumDitauWPDeepTauForVBFIsoTau_eta;
vector<float> hltHpsSelectedPFTausMediumDitauWPDeepTauForVBFIsoTau_phi;
vector<float> hltHpsSelectedPFTausMediumDitauWPDeepTauForVBFIsoTau_energy;

int passhltHpsSelectedPFTausTempLooseDitauWPDeepTauForVBFIsoTau;
vector<float> hltHpsSelectedPFTausTempLooseDitauWPDeepTauForVBFIsoTau_pt;
vector<float> hltHpsSelectedPFTausTempLooseDitauWPDeepTauForVBFIsoTau_eta;
vector<float> hltHpsSelectedPFTausTempLooseDitauWPDeepTauForVBFIsoTau_phi;
vector<float> hltHpsSelectedPFTausTempLooseDitauWPDeepTauForVBFIsoTau_energy;

int passhltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch;
vector<float> hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_pt;
vector<float> hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_eta;
vector<float> hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_phi;
vector<float> hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_energy;

int passhltHpsDoublePFTau20MediumDitauWPDeepTauNoMatchNoL2NN;
vector<float> hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatchNoL2NN_pt;
vector<float> hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatchNoL2NN_eta;
vector<float> hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatchNoL2NN_phi;
vector<float> hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatchNoL2NN_energy;

int passhltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatch;
vector<float> hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatch_pt;
vector<float> hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatch_eta;
vector<float> hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatch_phi;
vector<float> hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatch_energy;

int passhltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatchNoL2NN;
vector<float> hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatchNoL2NN_pt;
vector<float> hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatchNoL2NN_eta;
vector<float> hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatchNoL2NN_phi;
vector<float> hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatchNoL2NN_energy;

// match L1 Tau
int passhltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched;
vector<float> hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_pt;
vector<float> hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_eta;
vector<float> hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_phi;
vector<float> hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_energy;

int passhltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatchedNoL2NN;
vector<float> hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatchedNoL2NN_pt;
vector<float> hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatchedNoL2NN_eta;
vector<float> hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatchedNoL2NN_phi;
vector<float> hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatchedNoL2NN_energy;

int passhltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatched; 
vector<float> hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatched_pt;
vector<float> hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatched_eta;
vector<float> hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatched_phi;
vector<float> hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatched_energy;

int passhltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatchedNoL2NN;
vector<float> hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatchedNoL2NN_pt;
vector<float> hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatchedNoL2NN_eta;
vector<float> hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatchedNoL2NN_phi;
vector<float> hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatchedNoL2NN_energy;

// added for inefficiency study in DeepTau HLT
int passhltRealDijetFilter;
vector<float> hltRealDijetFilter_pt;
vector<float> hltRealDijetFilter_eta;
vector<float> hltRealDijetFilter_phi;
vector<float> hltRealDijetFilter_energy;

int passhltVBFLooseIDPFDummyFilter;
vector<float> hltVBFLooseIDPFDummyFilter_pt;
vector<float> hltVBFLooseIDPFDummyFilter_eta;
vector<float> hltVBFLooseIDPFDummyFilter_phi;
vector<float> hltVBFLooseIDPFDummyFilter_energy;

int passhltVBFIsoTauL1TLooseIDPFJetsMatching;
vector<float> hltVBFIsoTauL1TLooseIDPFJetsMatching_pt;
vector<float> hltVBFIsoTauL1TLooseIDPFJetsMatching_eta;
vector<float> hltVBFIsoTauL1TLooseIDPFJetsMatching_phi;
vector<float> hltVBFIsoTauL1TLooseIDPFJetsMatching_energy;

// match jets filter
int passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20; 
vector<float> hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20_pt;
vector<float> hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20_eta;
vector<float> hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20_phi;
vector<float> hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20_energy;

int passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20NoL2NN; 
vector<float> hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20NoL2NN_pt;
vector<float> hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20NoL2NN_eta;
vector<float> hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20NoL2NN_phi;
vector<float> hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20NoL2NN_energy;

int passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20;
vector<float> hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20_pt;
vector<float> hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20_eta;
vector<float> hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20_phi;
vector<float> hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20_energy;

int passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20NoL2NN;
vector<float> hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20NoL2NN_pt;
vector<float> hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20NoL2NN_eta;
vector<float> hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20NoL2NN_phi;
vector<float> hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20NoL2NN_energy;

int passhltHpsDoublePFTau20BeforeDeepTau;
vector<float> hltHpsDoublePFTau20BeforeDeepTau_pt;
vector<float> hltHpsDoublePFTau20BeforeDeepTau_eta;
vector<float> hltHpsDoublePFTau20BeforeDeepTau_phi;
vector<float> hltHpsDoublePFTau20BeforeDeepTau_energy;

int passhltHpsDoublePFTau20withL2NNBeforeDeepTau;
vector<float> hltHpsDoublePFTau20withL2NNBeforeDeepTau_pt;
vector<float> hltHpsDoublePFTau20withL2NNBeforeDeepTau_eta;
vector<float> hltHpsDoublePFTau20withL2NNBeforeDeepTau_phi;
vector<float> hltHpsDoublePFTau20withL2NNBeforeDeepTau_energy;

void NtupleMaker::branchesTriggers(TTree* tree){

    tree->Branch("nEvents", &nEvents);

    tree->Branch("passDeepDiTau35HLT", &passDeepDiTau35HLT);

    tree->Branch("passInclusiveVBFHLT", &passInclusiveVBFHLT);    
    

    tree->Branch("passVBF2DTHLT", &passVBF2DTHLT);
    tree->Branch("passVBF2DTTempLooseHLT", &passVBF2DTTempLooseHLT);
    tree->Branch("passVBF2DTNoL2NNHLT", &passVBF2DTNoL2NNHLT);
    tree->Branch("passVBF2DTLooseNoL2NNHLT", &passVBF2DTLooseNoL2NNHLT);
    tree->Branch("passVBF2DTOldL1", &passVBF2DTOldL1);

    tree->Branch("passUpperControlHLT", &passUpperControlHLT);
    tree->Branch("passLowerControlHLT", &passLowerControlHLT);
    tree->Branch("pass2Tau1JetHLT", &pass2Tau1JetHLT);

    tree->Branch("passUpperControlMedHLT", &passUpperControlMedHLT);
    tree->Branch("passLowerControlMedHLT", &passLowerControlMedHLT);
    tree->Branch("passDiTauControl", &passDiTauControl);

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

    tree->Branch("passhltL1VBFDiJetIsoTauNoer", &passhltL1VBFDiJetIsoTauNoer);
    tree->Branch("hltL1VBFDiJetIsoTauNoer_nJets", &hltL1VBFDiJetIsoTauNoer_nJets);
    tree->Branch("hltL1VBFDiJetIsoTauNoer_jetPt", &hltL1VBFDiJetIsoTauNoer_jetPt);
    tree->Branch("hltL1VBFDiJetIsoTauNoer_nTaus", &hltL1VBFDiJetIsoTauNoer_nTaus);
    tree->Branch("hltL1VBFDiJetIsoTauNoer_tauPt", &hltL1VBFDiJetIsoTauNoer_tauPt);


    // VBFPlusTwoDeepTau HLT Modules
    tree->Branch("passhltL2VBFIsoTauNNFilter", &passhltL2VBFIsoTauNNFilter);
    tree->Branch("hltL2VBFIsoTauNNFilter_pt", &hltL2VBFIsoTauNNFilter_pt);
    tree->Branch("hltL2VBFIsoTauNNFilter_eta", &hltL2VBFIsoTauNNFilter_eta);
    tree->Branch("hltL2VBFIsoTauNNFilter_phi", &hltL2VBFIsoTauNNFilter_phi);
    tree->Branch("hltL2VBFIsoTauNNFilter_energy", &hltL2VBFIsoTauNNFilter_energy);

    // issue where these filters aren't being activated/stored in tree. Would be good info to have
    tree->Branch("passhltHpsSelectedPFTausMediumDitauWPDeepTauForVBFIsoTau", &passhltHpsSelectedPFTausMediumDitauWPDeepTauForVBFIsoTau);
    tree->Branch("hltHpsSelectedPFTausMediumDitauWPDeepTauForVBFIsoTau_pt", &hltHpsSelectedPFTausMediumDitauWPDeepTauForVBFIsoTau_pt);
    tree->Branch("hltHpsSelectedPFTausMediumDitauWPDeepTauForVBFIsoTau_eta", &hltHpsSelectedPFTausMediumDitauWPDeepTauForVBFIsoTau_eta);
    tree->Branch("hltHpsSelectedPFTausMediumDitauWPDeepTauForVBFIsoTau_phi", &hltHpsSelectedPFTausMediumDitauWPDeepTauForVBFIsoTau_phi);
    tree->Branch("hltHpsSelectedPFTausMediumDitauWPDeepTauForVBFIsoTau_energy", &hltHpsSelectedPFTausMediumDitauWPDeepTauForVBFIsoTau_energy);

    tree->Branch("passhltHpsSelectedPFTausTempLooseDitauWPDeepTauForVBFIsoTau", &passhltHpsSelectedPFTausTempLooseDitauWPDeepTauForVBFIsoTau);
    tree->Branch("hltHpsSelectedPFTausTempLooseDitauWPDeepTauForVBFIsoTau_pt", &hltHpsSelectedPFTausTempLooseDitauWPDeepTauForVBFIsoTau_pt);
    tree->Branch("hltHpsSelectedPFTausTempLooseDitauWPDeepTauForVBFIsoTau_eta", &hltHpsSelectedPFTausTempLooseDitauWPDeepTauForVBFIsoTau_eta);
    tree->Branch("hltHpsSelectedPFTausTempLooseDitauWPDeepTauForVBFIsoTau_phi", &hltHpsSelectedPFTausTempLooseDitauWPDeepTauForVBFIsoTau_phi);
    tree->Branch("hltHpsSelectedPFTausTempLooseDitauWPDeepTauForVBFIsoTau_energy", &hltHpsSelectedPFTausTempLooseDitauWPDeepTauForVBFIsoTau_energy);
    
    //
    tree->Branch("passhltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch", &passhltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch);
    tree->Branch("hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_pt", &hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_pt);
    tree->Branch("hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_eta", &hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_eta);
    tree->Branch("hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_phi", &hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_phi);
    tree->Branch("hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_energy", &hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_energy);

    tree->Branch("passhltHpsDoublePFTau20MediumDitauWPDeepTauNoMatchNoL2NN", &passhltHpsDoublePFTau20MediumDitauWPDeepTauNoMatchNoL2NN);
    tree->Branch("hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatchNoL2NN_pt", &hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatchNoL2NN_pt);
    tree->Branch("hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatchNoL2NN_eta", &hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatchNoL2NN_eta);
    tree->Branch("hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatchNoL2NN_phi", &hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatchNoL2NN_phi);
    tree->Branch("hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatchNoL2NN_energy", &hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatchNoL2NN_energy);

    tree->Branch("passhltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatch", &passhltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatch);
    tree->Branch("hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatch_pt", &hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatch_pt);
    tree->Branch("hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatch_eta", &hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatch_eta);
    tree->Branch("hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatch_phi", &hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatch_phi);
    tree->Branch("hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatch_energy", &hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatch_energy);

    tree->Branch("passhltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatchNoL2NN", &passhltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatchNoL2NN);
    tree->Branch("hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatchNoL2NN_pt", &hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatchNoL2NN_pt);
    tree->Branch("hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatchNoL2NN_eta", &hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatchNoL2NN_eta);
    tree->Branch("hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatchNoL2NN_phi", &hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatchNoL2NN_phi);
    tree->Branch("hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatchNoL2NN_energy", &hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatchNoL2NN_energy);

    //
    tree->Branch("passhltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched", &passhltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched);
    tree->Branch("hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_pt", &hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_pt);
    tree->Branch("hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_eta", &hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_eta);
    tree->Branch("hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_phi", &hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_phi);
    tree->Branch("hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_energy", &hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_energy);

    tree->Branch("passhltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatchedNoL2NN", &passhltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatchedNoL2NN);
    tree->Branch("hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatchedNoL2NN_pt", &hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatchedNoL2NN_pt);
    tree->Branch("hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatchedNoL2NN_eta", &hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatchedNoL2NN_eta);
    tree->Branch("hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatchedNoL2NN_phi", &hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatchedNoL2NN_phi);
    tree->Branch("hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatchedNoL2NN_energy", &hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatchedNoL2NN_energy);

    tree->Branch("passhltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatched", &passhltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatched);
    tree->Branch("hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatched_pt", &hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatched_pt);
    tree->Branch("hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatched_eta", &hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatched_eta);
    tree->Branch("hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatched_phi", &hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatched_phi);
    tree->Branch("hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatched_energy", &hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatched_energy);

    tree->Branch("passhltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatchedNoL2NN", &passhltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatchedNoL2NN);
    tree->Branch("hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatchedNoL2NN_pt", &hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatchedNoL2NN_pt);
    tree->Branch("hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatchedNoL2NN_eta", &hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatchedNoL2NN_eta);
    tree->Branch("hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatchedNoL2NN_phi", &hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatchedNoL2NN_phi);
    tree->Branch("hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatchedNoL2NN_energy", &hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatchedNoL2NN_energy);
    //
    tree->Branch("passhltRealDijetFilter", &passhltRealDijetFilter);
    tree->Branch("hltRealDijetFilter_pt", &hltRealDijetFilter_pt);
    tree->Branch("hltRealDijetFilter_eta", &hltRealDijetFilter_eta);
    tree->Branch("hltRealDijetFilter_phi", &hltRealDijetFilter_phi);
    tree->Branch("hltRealDijetFilter_energy", &hltRealDijetFilter_energy);

    tree->Branch("passhltVBFLooseIDPFDummyFilter", &passhltVBFLooseIDPFDummyFilter);
    tree->Branch("hltVBFLooseIDPFDummyFilter_pt", &hltVBFLooseIDPFDummyFilter_pt);
    tree->Branch("hltVBFLooseIDPFDummyFilter_eta", &hltVBFLooseIDPFDummyFilter_eta);
    tree->Branch("hltVBFLooseIDPFDummyFilter_phi", &hltVBFLooseIDPFDummyFilter_phi);
    tree->Branch("hltVBFLooseIDPFDummyFilter_energy", &hltVBFLooseIDPFDummyFilter_energy);

    tree->Branch("passhltVBFIsoTauL1TLooseIDPFJetsMatching", &passhltVBFIsoTauL1TLooseIDPFJetsMatching);
    tree->Branch("hltVBFIsoTauL1TLooseIDPFJetsMatching_pt", &hltVBFIsoTauL1TLooseIDPFJetsMatching_pt);
    tree->Branch("hltVBFIsoTauL1TLooseIDPFJetsMatching_eta", &hltVBFIsoTauL1TLooseIDPFJetsMatching_eta);
    tree->Branch("hltVBFIsoTauL1TLooseIDPFJetsMatching_phi", &hltVBFIsoTauL1TLooseIDPFJetsMatching_phi);
    tree->Branch("hltVBFIsoTauL1TLooseIDPFJetsMatching_energy", &hltVBFIsoTauL1TLooseIDPFJetsMatching_energy);

    // 
    tree->Branch("passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20", &passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20);
    tree->Branch("hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20_pt", &hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20_pt);
    tree->Branch("hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20_eta", &hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20_eta);
    tree->Branch("hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20_phi", &hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20_phi);
    tree->Branch("hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20_energy", &hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20_energy);

    tree->Branch("passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20NoL2NN", &passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20NoL2NN);
    tree->Branch("hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20NoL2NN_pt", &hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20NoL2NN_pt);
    tree->Branch("hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20NoL2NN_eta", &hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20NoL2NN_eta);
    tree->Branch("hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20NoL2NN_phi", &hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20NoL2NN_phi);
    tree->Branch("hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20NoL2NN_energy", &hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20NoL2NN_energy);

    tree->Branch("passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20", &passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20);
    tree->Branch("hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20_pt", &hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20_pt);
    tree->Branch("hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20_eta", &hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20_eta);
    tree->Branch("hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20_phi", &hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20_phi);
    tree->Branch("hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20_energy", &hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20_energy);

    tree->Branch("passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20NoL2NN", &passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20NoL2NN);
    tree->Branch("hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20NoL2NN_pt", &hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20NoL2NN_pt);
    tree->Branch("hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20NoL2NN_eta", &hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20NoL2NN_eta);
    tree->Branch("hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20NoL2NN_phi", &hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20NoL2NN_phi);
    tree->Branch("hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20NoL2NN_energy", &hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20NoL2NN_energy);


    tree->Branch("passhltHpsDoublePFTau20BeforeDeepTau", &passhltHpsDoublePFTau20BeforeDeepTau);
    tree->Branch("hltHpsDoublePFTau20BeforeDeepTau_pt", &hltHpsDoublePFTau20BeforeDeepTau_pt);
    tree->Branch("hltHpsDoublePFTau20BeforeDeepTau_eta", &hltHpsDoublePFTau20BeforeDeepTau_eta);
    tree->Branch("hltHpsDoublePFTau20BeforeDeepTau_phi", &hltHpsDoublePFTau20BeforeDeepTau_phi);
    tree->Branch("hltHpsDoublePFTau20BeforeDeepTau_energy", &hltHpsDoublePFTau20BeforeDeepTau_energy);

    tree->Branch("passhltHpsDoublePFTau20withL2NNBeforeDeepTau", &passhltHpsDoublePFTau20withL2NNBeforeDeepTau);
    tree->Branch("hltHpsDoublePFTau20withL2NNBeforeDeepTau_pt", &hltHpsDoublePFTau20withL2NNBeforeDeepTau_pt);
    tree->Branch("hltHpsDoublePFTau20withL2NNBeforeDeepTau_eta", &hltHpsDoublePFTau20withL2NNBeforeDeepTau_eta);
    tree->Branch("hltHpsDoublePFTau20withL2NNBeforeDeepTau_phi", &hltHpsDoublePFTau20withL2NNBeforeDeepTau_phi);
    tree->Branch("hltHpsDoublePFTau20withL2NNBeforeDeepTau_energy", &hltHpsDoublePFTau20withL2NNBeforeDeepTau_energy);

}

void NtupleMaker::fillTriggers(const edm::Event& iEvent){

    using namespace edm;

    // clearing vectors and initializing flags at the start of every event 
    nEvents = 0;

    passDeepDiTau35HLT = 0;
    passDiTauControl = 0;
    passInclusiveVBFHLT = 0; 

    passVBF2DTHLT = 0;
    passVBF2DTTempLooseHLT = 0;
    passVBF2DTNoL2NNHLT = 0;
    passVBF2DTLooseNoL2NNHLT = 0;
    passVBF2DTOldL1 = 0;

    passUpperControlHLT = 0;
    passLowerControlHLT = 0;

    passUpperControlMedHLT = 0;
    passLowerControlMedHLT = 0;

    pass2Tau1JetHLT = 0;

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

    passhltL1VBFDiJetIsoTauNoer = 0;
    hltL1VBFDiJetIsoTauNoer_nJets.clear();
    hltL1VBFDiJetIsoTauNoer_jetPt.clear();
    hltL1VBFDiJetIsoTauNoer_nTaus.clear();
    hltL1VBFDiJetIsoTauNoer_tauPt.clear();


    // Start VBF Double Deep Tau
    passhltL2VBFIsoTauNNFilter = 0;
    hltL2VBFIsoTauNNFilter_pt.clear();
    hltL2VBFIsoTauNNFilter_eta.clear();
    hltL2VBFIsoTauNNFilter_phi.clear();
    hltL2VBFIsoTauNNFilter_energy.clear();

    //
    passhltHpsSelectedPFTausMediumDitauWPDeepTauForVBFIsoTau = 0;
    hltHpsSelectedPFTausMediumDitauWPDeepTauForVBFIsoTau_pt.clear();
    hltHpsSelectedPFTausMediumDitauWPDeepTauForVBFIsoTau_eta.clear();
    hltHpsSelectedPFTausMediumDitauWPDeepTauForVBFIsoTau_phi.clear();
    hltHpsSelectedPFTausMediumDitauWPDeepTauForVBFIsoTau_energy.clear();

    passhltHpsSelectedPFTausTempLooseDitauWPDeepTauForVBFIsoTau = 0;
    hltHpsSelectedPFTausTempLooseDitauWPDeepTauForVBFIsoTau_pt.clear();
    hltHpsSelectedPFTausTempLooseDitauWPDeepTauForVBFIsoTau_eta.clear();
    hltHpsSelectedPFTausTempLooseDitauWPDeepTauForVBFIsoTau_phi.clear();
    hltHpsSelectedPFTausTempLooseDitauWPDeepTauForVBFIsoTau_energy.clear();

    //
    passhltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch = 0;
    hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_pt.clear();
    hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_eta.clear();
    hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_phi.clear();
    hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_energy.clear();

    passhltHpsDoublePFTau20MediumDitauWPDeepTauNoMatchNoL2NN = 0;
    hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatchNoL2NN_pt.clear();
    hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatchNoL2NN_eta.clear();
    hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatchNoL2NN_phi.clear();
    hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatchNoL2NN_energy.clear();

    passhltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatch = 0;
    hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatch_pt.clear();
    hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatch_eta.clear();
    hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatch_phi.clear();
    hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatch_energy.clear();

    passhltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatchNoL2NN = 0;
    hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatchNoL2NN_pt.clear();
    hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatchNoL2NN_eta.clear();
    hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatchNoL2NN_phi.clear();
    hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatchNoL2NN_energy.clear();
    
    //
    passhltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched = 0;
    hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_pt.clear();
    hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_eta.clear();
    hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_phi.clear();
    hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_energy.clear();

    passhltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatchedNoL2NN = 0;
    hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatchedNoL2NN_pt.clear();
    hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatchedNoL2NN_eta.clear();
    hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatchedNoL2NN_phi.clear();
    hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatchedNoL2NN_energy.clear();

    passhltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatched = 0;
    hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatched_pt.clear();
    hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatched_eta.clear();
    hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatched_phi.clear();
    hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatched_energy.clear();

    passhltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatchedNoL2NN = 0;
    hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatchedNoL2NN_pt.clear();
    hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatchedNoL2NN_eta.clear();
    hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatchedNoL2NN_phi.clear();
    hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatchedNoL2NN_energy.clear();

    //
    passhltRealDijetFilter = 0;
    hltRealDijetFilter_pt.clear();
    hltRealDijetFilter_eta.clear();
    hltRealDijetFilter_phi.clear();
    hltRealDijetFilter_energy.clear();

    passhltVBFLooseIDPFDummyFilter = 0;
    hltVBFLooseIDPFDummyFilter_pt.clear();
    hltVBFLooseIDPFDummyFilter_eta.clear();
    hltVBFLooseIDPFDummyFilter_phi.clear();
    hltVBFLooseIDPFDummyFilter_energy.clear();

    passhltVBFIsoTauL1TLooseIDPFJetsMatching = 0;
    hltVBFIsoTauL1TLooseIDPFJetsMatching_pt.clear();
    hltVBFIsoTauL1TLooseIDPFJetsMatching_eta.clear();
    hltVBFIsoTauL1TLooseIDPFJetsMatching_phi.clear();
    hltVBFIsoTauL1TLooseIDPFJetsMatching_energy.clear();

    //
    passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20 = 0;
    hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20_pt.clear();
    hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20_eta.clear();
    hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20_phi.clear();
    hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20_energy.clear();

    passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20NoL2NN = 0;
    hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20NoL2NN_pt.clear();
    hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20NoL2NN_eta.clear();
    hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20NoL2NN_phi.clear();
    hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20NoL2NN_energy.clear();

    passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20 = 0;
    hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20_pt.clear();
    hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20_eta.clear();
    hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20_phi.clear();
    hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20_energy.clear();

    passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20NoL2NN = 0;
    hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20NoL2NN_pt.clear();
    hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20NoL2NN_eta.clear();
    hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20NoL2NN_phi.clear();
    hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20NoL2NN_energy.clear();

    passhltHpsDoublePFTau20BeforeDeepTau = 0;
    hltHpsDoublePFTau20BeforeDeepTau_pt.clear();
    hltHpsDoublePFTau20BeforeDeepTau_eta.clear();
    hltHpsDoublePFTau20BeforeDeepTau_phi.clear();
    hltHpsDoublePFTau20BeforeDeepTau_energy.clear();

    passhltHpsDoublePFTau20withL2NNBeforeDeepTau = 0;
    hltHpsDoublePFTau20withL2NNBeforeDeepTau_pt.clear();
    hltHpsDoublePFTau20withL2NNBeforeDeepTau_eta.clear();
    hltHpsDoublePFTau20withL2NNBeforeDeepTau_phi.clear();
    hltHpsDoublePFTau20withL2NNBeforeDeepTau_energy.clear();


    // getting trigger results, following this page
    // https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideHLTAnalysis
    edm::Handle<edm::TriggerResults> triggerResults;
    iEvent.getByToken(triggerResultToken_, triggerResults);
    edm::Handle<trigger::TriggerEvent> triggerEvent;
    iEvent.getByToken(triggerEventToken_, triggerEvent);
    const edm::TriggerNames triggerNames_ = iEvent.triggerNames(*triggerResults);

    // saving trigger results to respective branches
    // DiTau35 HLT
    std::string pathNameDiTauTrig = "HLT_DoubleTightChargedIsoPFTauHPS35_Trk1_eta2p1_v1";
    //passDiTau35HLT = triggerResults->accept(triggerNames_.triggerIndex(pathNameDiTauTrig));

    // DeepDiTau35 HLT and Control trigger
    std::string pathNameDeepDiTauTrig = "HLT_DoubleMediumDeepTauIsoPFTauHPS35_L2NN_eta2p1_v1";
    passDeepDiTau35HLT = triggerResults->accept(triggerNames_.triggerIndex(pathNameDeepDiTauTrig));
    std::string pathNameDiTauControl = "HLT_IsoMu24_eta2p1_MediumDeepTauPFTauHPS35_L2NN_eta2p1_CrossL1_v1";
    passDiTauControl = triggerResults->accept(triggerNames_.triggerIndex(pathNameDiTauControl));

    // Inclusive VBF HLT
    std::string pathNameInclusiveVBF = "HLT_VBF_DoubleTightChargedIsoPFTauHPS20_Trk1_eta2p1_v1";
    passInclusiveVBFHLT = triggerResults->accept(triggerNames_.triggerIndex(pathNameInclusiveVBF));

    // VBF + 2 Deep Tau HLT Medium w L2NN and Loose with No L2NN
    std::string pathUpdatedNameVBF2DT = "HLT_DoublePFJets40_Mass500_MediumDeepTau45_L2NN_MediumDeepTau20_eta2p1_v1";
    passVBF2DTHLT = triggerResults->accept(triggerNames_.triggerIndex(pathUpdatedNameVBF2DT));

    std::string pathNameVBF2DTLooseNoL2NN = "HLT_DoublePFJets40_Mass500_LooseDeepTau45_LooseDeepTau20_eta2p1_v1";
    passVBF2DTLooseNoL2NNHLT = triggerResults->accept(triggerNames_.triggerIndex(pathNameVBF2DTLooseNoL2NN));

    // VBF + 2 Deep Tau using L1_DoubleJet35_Mass_Min450_IsoTau45_RmOvlp
    std::string pathNameVBF2DTOldL1 = "HLT_PreviousL1Version_DoublePFJets40_Mass500_MediumDeepTau45_L2NN_MediumDeepTau20_eta2p1_v1";
    //passVBF2DTOldL1 = triggerResults->accept(triggerNames_.triggerIndex(pathNameVBF2DTOldL1));

    // My Control Paths
    std::string pathNameUpperControl = "HLT_IsoMu24_eta2p1_LooseDeepTauPFTauHPS45_eta2p1_CrossL1_v1";
    passUpperControlHLT = triggerResults->accept(triggerNames_.triggerIndex(pathNameUpperControl));
    std::string pathNameLowerControl = "HLT_IsoMu27_LooseDeepTauPFTauHPS20_eta2p1_SingleL1_v1";
    passLowerControlHLT = triggerResults->accept(triggerNames_.triggerIndex(pathNameLowerControl));

    std::string pathNameUpperControlMed = "HLT_IsoMu24_eta2p1_MediumDeepTauPFTauHPS45_L2NN_eta2p1_CrossL1_v1";
    passUpperControlMedHLT = triggerResults->accept(triggerNames_.triggerIndex(pathNameUpperControlMed));
    std::string pathNameLowerControlMed = "HLT_IsoMu27_MediumDeepTauPFTauHPS20_L2NN_eta2p1_SingleL1_v1";
    passLowerControlMedHLT = triggerResults->accept(triggerNames_.triggerIndex(pathNameLowerControlMed));

    // Spain Group Trigger
    std::string pathName2Tau1Jet = "HLT_DoubleMediumDeepTauIsoPFTauHPS30_L2NN_eta2p1_PFJet60_v1";
    pass2Tau1JetHLT = triggerResults->accept(triggerNames_.triggerIndex(pathName2Tau1Jet));


    // filling branches with triggerObjs information, hltL1VBFDiJetIsoTau object info filled separately since it's a weird L1

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

/*
    // make temp L1 reader for other L1VBFIsoTauNoer
    const unsigned int otherFilterIndex(triggerEventWithRefsHandle_->filterIndex(InputTag("hltL1VBFDiJetIsoTauNoer", "", "MYOTHERHLT")));

    l1t::JetVectorRef otherJetCandRefVec;
    trigger::Vids otherJvids;
    triggerEventWithRefsHandle_->getObjects(otherFilterIndex, otherJvids, otherJetCandRefVec);

    const unsigned int othernJets(otherJvids.size());
    if (othernJets > 0) {
      hltL1VBFDiJetIsoTauNoer_nJets.push_back(othernJets);
      for (unsigned int i = 0; i != othernJets; ++i) {
        hltL1VBFDiJetIsoTauNoer_jetPt.push_back(otherJetCandRefVec[i]->pt());
      }
    }

    l1t::TauVectorRef otherTauCandRefVec;
    trigger::Vids otherTvids;
    triggerEventWithRefsHandle_->getObjects(otherFilterIndex, otherTvids, otherTauCandRefVec);

    const unsigned int othernTaus(otherTvids.size());
    if (othernTaus > 0) {
      hltL1VBFDiJetIsoTauNoer_nTaus.push_back(othernTaus);
      for (unsigned int i = 0; i != othernTaus; ++i) {
        hltL1VBFDiJetIsoTauNoer_tauPt.push_back(otherTauCandRefVec[i]->pt());
      }
    }
*/
    // make strings to identify filter names
    const trigger::size_type nFilters(triggerEvent->sizeFilters());
    std::string hltL1sDoubleTauBigOR_Tag = "hltL1sDoubleTauBigOR::MYOTHERHLT"; // ditau L1
    std::string hltL1VBFDiJetOR_Tag = "hltL1VBFDiJetOR::MYOTHERHLT";		  // inclusive L1
    std::string hltL1VBFDiJetIsoTau_Tag = "hltL1VBFDiJetIsoTau::MYOTHERHLT";	  
    std::string hltL1VBFDiJetIsoTauNoer_Tag = "hltL1VBFDiJetIsoTauNoer::MYOTHERHLT";	  // no eta restriction

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
        if (filterTag == hltL1VBFDiJetIsoTauNoer_Tag && hltL1VBFDiJetIsoTauNoer_tauPt.size() >= 1
                                                     && hltL1VBFDiJetIsoTauNoer_jetPt.size() >= 2) passhltL1VBFDiJetIsoTauNoer = 1;

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

        // Start VBF Double Deep Tau
        // fill hltL2VBFIsoTauNNFilter if match
            if (filterTag == hltL2VBFIsoTauNNFilter_Tag
                 && passhltL2VBFIsoTauNNFilter && pt_>0) {
               hltL2VBFIsoTauNNFilter_pt.push_back(pt_);
               hltL2VBFIsoTauNNFilter_eta.push_back(eta_);
               hltL2VBFIsoTauNNFilter_phi.push_back(phi_);
               hltL2VBFIsoTauNNFilter_energy.push_back(energy_);
            }
            if (filterTag == hltHpsDoublePFTau20BeforeDeepTau_Tag
                 && passhltHpsDoublePFTau20BeforeDeepTau && pt_>0) {
               hltHpsDoublePFTau20BeforeDeepTau_pt.push_back(pt_);
               hltHpsDoublePFTau20BeforeDeepTau_eta.push_back(eta_);
               hltHpsDoublePFTau20BeforeDeepTau_phi.push_back(phi_);
               hltHpsDoublePFTau20BeforeDeepTau_energy.push_back(energy_);
            }
            if (filterTag == hltHpsDoublePFTau20withL2NNBeforeDeepTau_Tag
                 && passhltHpsDoublePFTau20withL2NNBeforeDeepTau && pt_>0) {
               hltHpsDoublePFTau20withL2NNBeforeDeepTau_pt.push_back(pt_);
               hltHpsDoublePFTau20withL2NNBeforeDeepTau_eta.push_back(eta_);
               hltHpsDoublePFTau20withL2NNBeforeDeepTau_phi.push_back(phi_);
               hltHpsDoublePFTau20withL2NNBeforeDeepTau_energy.push_back(energy_);
            }

        //
        // fill hltHpsSelectedPFTausMediumDitauWPDeepTauForVBFIsoTau if match
            if (filterTag == hltHpsSelectedPFTausMediumDitauWPDeepTauForVBFIsoTau_Tag
                 && passhltHpsSelectedPFTausMediumDitauWPDeepTauForVBFIsoTau && pt_>0) {
               hltHpsSelectedPFTausMediumDitauWPDeepTauForVBFIsoTau_pt.push_back(pt_);
               hltHpsSelectedPFTausMediumDitauWPDeepTauForVBFIsoTau_eta.push_back(eta_);
               hltHpsSelectedPFTausMediumDitauWPDeepTauForVBFIsoTau_phi.push_back(phi_);
               hltHpsSelectedPFTausMediumDitauWPDeepTauForVBFIsoTau_energy.push_back(energy_);
            }
        // fill hltHpsSelectedPFTausTempLooseDitauWPDeepTauForVBFIsoTau if match
            if (filterTag == hltHpsSelectedPFTausTempLooseDitauWPDeepTauForVBFIsoTau_Tag
                 && passhltHpsSelectedPFTausTempLooseDitauWPDeepTauForVBFIsoTau && pt_>0) {
               hltHpsSelectedPFTausTempLooseDitauWPDeepTauForVBFIsoTau_pt.push_back(pt_);
               hltHpsSelectedPFTausTempLooseDitauWPDeepTauForVBFIsoTau_eta.push_back(eta_);
               hltHpsSelectedPFTausTempLooseDitauWPDeepTauForVBFIsoTau_phi.push_back(phi_);
               hltHpsSelectedPFTausTempLooseDitauWPDeepTauForVBFIsoTau_energy.push_back(energy_);
            }
        //
        // fill hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch if match
            if (filterTag == hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_Tag
                 && passhltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch && pt_>0) {
               hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_pt.push_back(pt_);
               hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_eta.push_back(eta_);
               hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_phi.push_back(phi_);
               hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_energy.push_back(energy_);
            }
        // fill hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatchNoL2NN if match
            if (filterTag == hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatchNoL2NN_Tag
                 && passhltHpsDoublePFTau20MediumDitauWPDeepTauNoMatchNoL2NN && pt_>0) {
               hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatchNoL2NN_pt.push_back(pt_);
               hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatchNoL2NN_eta.push_back(eta_);
               hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatchNoL2NN_phi.push_back(phi_);
               hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatchNoL2NN_energy.push_back(energy_);
            }
        // fill hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatch if match
            if (filterTag == hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatch_Tag
                 && passhltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatch && pt_>0) {
               hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatch_pt.push_back(pt_);
               hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatch_eta.push_back(eta_);
               hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatch_phi.push_back(phi_);
               hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatch_energy.push_back(energy_);
            }
        // fill hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatchNoL2NN if match
            if (filterTag == hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatchNoL2NN_Tag
                 && passhltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatchNoL2NN && pt_>0) {
               hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatchNoL2NN_pt.push_back(pt_);
               hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatchNoL2NN_eta.push_back(eta_);
               hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatchNoL2NN_phi.push_back(phi_);
               hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatchNoL2NN_energy.push_back(energy_);
            }
        //
        // fill hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched if match
            if (filterTag == hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_Tag
                 && passhltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched && pt_>0) {
               hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_pt.push_back(pt_);
               hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_eta.push_back(eta_);
               hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_phi.push_back(phi_);
               hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_energy.push_back(energy_);
            }
        // fill hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatchedNoL2NN if match
            if (filterTag == hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatchedNoL2NN_Tag
                 && passhltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatchedNoL2NN && pt_>0) {
               hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatchedNoL2NN_pt.push_back(pt_);
               hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatchedNoL2NN_eta.push_back(eta_);
               hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatchedNoL2NN_phi.push_back(phi_);
               hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatchedNoL2NN_energy.push_back(energy_);
            }
        // fill hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatched if match
            if (filterTag == hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatched_Tag
                 && passhltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatched && pt_>0) {
               hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatched_pt.push_back(pt_);
               hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatched_eta.push_back(eta_);
               hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatched_phi.push_back(phi_);
               hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatched_energy.push_back(energy_);
            }
        // fill hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatchedNoL2NN if match
            if (filterTag == hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatchedNoL2NN_Tag
                 && passhltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatchedNoL2NN && pt_>0) {
               hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatchedNoL2NN_pt.push_back(pt_);
               hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatchedNoL2NN_eta.push_back(eta_);
               hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatchedNoL2NN_phi.push_back(phi_);
               hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatchedNoL2NN_energy.push_back(energy_);
            }
        //
        // fill hltRealDijetFilter if match
            if (filterTag == hltRealDijetFilter_Tag
                 && passhltRealDijetFilter && pt_>0) {
               hltRealDijetFilter_pt.push_back(pt_);
               hltRealDijetFilter_eta.push_back(eta_);
               hltRealDijetFilter_phi.push_back(phi_);
               hltRealDijetFilter_energy.push_back(energy_);
            }
        // fill hltVBFLooseIDPFDummyFilter if match
            if (filterTag == hltVBFLooseIDPFDummyFilter_Tag
                 && passhltVBFLooseIDPFDummyFilter && pt_>0) {
               hltVBFLooseIDPFDummyFilter_pt.push_back(pt_);
               hltVBFLooseIDPFDummyFilter_eta.push_back(eta_);
               hltVBFLooseIDPFDummyFilter_phi.push_back(phi_);
               hltVBFLooseIDPFDummyFilter_energy.push_back(energy_);
            }
        // fill hltVBFIsoTauL1TLooseIDPFJetsMatching if match
            if (filterTag == hltVBFIsoTauL1TLooseIDPFJetsMatching_Tag
                 && passhltVBFIsoTauL1TLooseIDPFJetsMatching && pt_>0) {
               hltVBFIsoTauL1TLooseIDPFJetsMatching_pt.push_back(pt_);
               hltVBFIsoTauL1TLooseIDPFJetsMatching_eta.push_back(eta_);
               hltVBFIsoTauL1TLooseIDPFJetsMatching_phi.push_back(phi_);
               hltVBFIsoTauL1TLooseIDPFJetsMatching_energy.push_back(energy_);
            }
        //
        // fill hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20 if match
            if (filterTag == hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20_Tag
                 && passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20 && pt_>0) {
               hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20_pt.push_back(pt_);
               hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20_eta.push_back(eta_);
               hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20_phi.push_back(phi_);
               hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20_energy.push_back(energy_);
            }
        // fill hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20NoL2NN if match
            if (filterTag == hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20NoL2NN_Tag
                 && passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20NoL2NN && pt_>0) {
               hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20NoL2NN_pt.push_back(pt_);
               hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20NoL2NN_eta.push_back(eta_);
               hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20NoL2NN_phi.push_back(phi_);
               hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20NoL2NN_energy.push_back(energy_);
            }
        // fill hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20 if match
            if (filterTag == hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20_Tag
                 && passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20 && pt_>0) {
               hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20_pt.push_back(pt_);
               hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20_eta.push_back(eta_);
               hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20_phi.push_back(phi_);
               hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20_energy.push_back(energy_);
            }
        // fill hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20NoL2NN if match
            if (filterTag == hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20NoL2NN_Tag
                 && passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20NoL2NN && pt_>0) {
               hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20NoL2NN_pt.push_back(pt_);
               hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20NoL2NN_eta.push_back(eta_);
               hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20NoL2NN_phi.push_back(phi_);
               hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20NoL2NN_energy.push_back(energy_);
            }

	} // end loop over trigger object keys
    } // end loop over nfilters
} // end function
