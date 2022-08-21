#include "VBFIsoTauHLT/NtupleMaker/plugins/NtupleMaker.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"

using namespace std;


float 	pt_;
float 	eta_;
float 	phi_;
float 	energy_;


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


void NtupleMaker::branchesTriggers(TTree* tree){

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

}

void NtupleMaker::fillTriggers(const edm::Event& iEvent){

    using namespace edm;

    // clearing vectors and initializing flags at the start of every event 

    // Start VBF Double Deep Tau
    passhltL2VBFIsoTauNNFilter = 0;
    hltL2VBFIsoTauNNFilter_pt.clear();

    passhltHpsSelectedPFTausMediumDitauWPDeepTauForVBFIsoTau = 0;
    hltHpsSelectedPFTausMediumDitauWPDeepTauForVBFIsoTau_pt.clear();

    passhltHpsSelectedPFTausTempLooseDitauWPDeepTauForVBFIsoTau = 0;
    hltHpsSelectedPFTausTempLooseDitauWPDeepTauForVBFIsoTau_pt.clear();

    passhltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch = 0;
    hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_pt.clear();

    passhltHpsDoublePFTau20MediumDitauWPDeepTauNoMatchNoL2NN = 0;
    hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatchNoL2NN_pt.clear();

    passhltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatch = 0;
    hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatch_pt.clear();

    passhltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatchNoL2NN = 0;
    hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatchNoL2NN_pt.clear();
    
    passhltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched = 0;
    hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_pt.clear();

    passhltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatchedNoL2NN = 0;
    hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatchedNoL2NN_pt.clear();

    passhltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatched = 0;
    hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatched_pt.clear();

    passhltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatchedNoL2NN = 0;
    hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatchedNoL2NN_pt.clear();

    passhltRealDijetFilter = 0;
    hltRealDijetFilter_pt.clear();

    passhltVBFLooseIDPFDummyFilter = 0;
    hltVBFLooseIDPFDummyFilter_pt.clear();

    passhltVBFIsoTauL1TLooseIDPFJetsMatching = 0;
    hltVBFIsoTauL1TLooseIDPFJetsMatching_pt.clear();

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


    // getting trigger event per this page
    // https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideHLTAnalysis
    edm::Handle<trigger::TriggerEvent> triggerEvent; // this code should be with the filters
    iEvent.getByToken(triggerEventToken_, triggerEvent); // same



    // make strings to identify filter names
    const trigger::size_type nFilters(triggerEvent->sizeFilters());

    // Start VBF Double Deep Tau
    std::string hltL2VBFIsoTauNNFilter_Tag = "hltL2VBFIsoTauNNFilter::MYOTHERHLT";
    
    std::string hltHpsSelectedPFTausMediumDitauWPDeepTauForVBFIsoTau_Tag = "hltHpsSelectedPFTausMediumDitauWPDeepTauForVBFIsoTau::MYOTHERHLT";
    std::string hltHpsSelectedPFTausTempLooseDitauWPDeepTauForVBFIsoTau_Tag = "hltHpsSelectedPFTausTempLooseDitauWPDeepTauForVBFIsoTau::MYOTHERHLT";
    
    std::string hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_Tag = "hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch::MYOTHERHLT";
    std::string hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatchNoL2NN_Tag = "hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatchNoL2NN::MYOTHERHLT";
    std::string hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatch_Tag = "hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatch::MYOTHERHLT";
    std::string hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatchNoL2NN_Tag = "hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatchNoL2NN::MYOTHERHLT";
    
    std::string hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_Tag = "hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched::MYOTHERHLT";
    std::string hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatchedNoL2NN_Tag = "hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatchedNoL2NN::MYOTHERHLT";
    std::string hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatched_Tag = "hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatched::MYOTHERHLT";
    std::string hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatchedNoL2NN_Tag = "hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatchedNoL2NN::MYOTHERHLT";
    
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

    // accepted filters per event
    for(trigger::size_type iFilter=0; iFilter!=nFilters; ++iFilter) {
	std::string filterTag = triggerEvent->filterTag(iFilter).encode();
	trigger::Keys objectKeys = triggerEvent->filterKeys(iFilter);

	const trigger::TriggerObjectCollection& triggerObjects(triggerEvent->getObjects());
	// fill "pass filter" branches
	int nObjKeys = objectKeys.size();

        // VBFPlusTwoDeepTau Modules
        if (filterTag == hltL2VBFIsoTauNNFilter_Tag && nObjKeys >= 1) passhltL2VBFIsoTauNNFilter = 1;
        if (filterTag == hltHpsDoublePFTau20BeforeDeepTau_Tag && nObjKeys >= 2) passhltHpsDoublePFTau20BeforeDeepTau = 1;
        if (filterTag == hltHpsDoublePFTau20withL2NNBeforeDeepTau_Tag && nObjKeys >= 2) passhltHpsDoublePFTau20withL2NNBeforeDeepTau = 1;
        
        if (filterTag == hltHpsSelectedPFTausMediumDitauWPDeepTauForVBFIsoTau_Tag && nObjKeys >= 1) passhltHpsSelectedPFTausMediumDitauWPDeepTauForVBFIsoTau = 1;
        if (filterTag == hltHpsSelectedPFTausTempLooseDitauWPDeepTauForVBFIsoTau_Tag && nObjKeys >= 1) passhltHpsSelectedPFTausTempLooseDitauWPDeepTauForVBFIsoTau = 1;
        
        if (filterTag == hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_Tag && nObjKeys >= 2) passhltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch = 1;
        if (filterTag == hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatchNoL2NN_Tag && nObjKeys >= 2) passhltHpsDoublePFTau20MediumDitauWPDeepTauNoMatchNoL2NN = 1;
        if (filterTag == hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatch_Tag && nObjKeys >= 2) passhltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatch = 1;
        if (filterTag == hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatchNoL2NN_Tag && nObjKeys >= 2) passhltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatchNoL2NN = 1;
        
        if (filterTag == hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_Tag && nObjKeys >= 1) passhltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched = 1;
        if (filterTag == hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatchedNoL2NN_Tag && nObjKeys >= 1) passhltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatchedNoL2NN = 1;
        if (filterTag == hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatched_Tag && nObjKeys >= 1) passhltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatched = 1;
        if (filterTag == hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatchedNoL2NN_Tag && nObjKeys >= 1) passhltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatchedNoL2NN = 1;
        
        if (filterTag == hltRealDijetFilter_Tag && nObjKeys >= 2) passhltRealDijetFilter = 1;
        if (filterTag == hltVBFLooseIDPFDummyFilter_Tag && nObjKeys >= 2) passhltVBFLooseIDPFDummyFilter = 1;
        if (filterTag == hltVBFIsoTauL1TLooseIDPFJetsMatching_Tag && nObjKeys >= 2) passhltVBFIsoTauL1TLooseIDPFJetsMatching = 1;
        
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


	//loop over trigger objects and store their kinematics to the proper filter branches
	for(trigger::size_type iKey=0; iKey < nObjKeys; ++iKey){
	    trigger::size_type objKey = objectKeys.at(iKey);
	    const trigger::TriggerObject& triggerObj(triggerObjects[objKey]);
	    pt_ = triggerObj.pt();
	    eta_ = triggerObj.eta();
	    phi_ = triggerObj.phi();
	    energy_ = triggerObj.energy();

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
