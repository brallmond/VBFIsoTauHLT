#include "VBFIsoTauHLT/NtupleMaker/plugins/NtupleMaker.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"

using namespace std;

// Signal HLTs
int passDeepDiTau35HLT;
int passEleTauHLT;
int passEleJetHLT;
int passSingleEleHLT;
int passSinglePhotonHLT;
int passVBF2DTHLT;
int passVBF1DTHLT;
int passVBF1DTHLT_CorrChecker;
int passVBF1DTHLT_OverlapRemoval;
int passInclusiveVBFHLT;
int passDeepInclusiveVBFHLT;
int passVBFEleHLT;
int passVBFPhotonHLT;
int passVBFMuonHLT;
int passVBFMuonHLT_TripleJet;
int passIsoMu24eta2p1HLT;
int passMuTauHLT;

// Monitoring/Control HLTs
int passUpperControlHLT;
int passLowerControlHLT;
int passDiTauControlHLT;

// adhoc HLTs
int passHLTDummyL1;
int passHLTDummyL1Loose;
int passHLTDummyL1NoIso;
int passHLTDummyEGORL1;

int passHLT_Dummy_L1VBFEG_TightIso;
int passHLT_Dummy_L1VBFEG_LooseIso;
int passHLT_Dummy_L1VBFEG_NoIso;
int passHLT_Dummy_L1EG_TightIso;
int passHLT_Dummy_L1EG_LooseIso;
int passHLT_Dummy_L1EG_NoIso;

// Jaime's HLTs
int pass2Tau1JetHLT;
int pass2Tau1JetHigherHLT;

void NtupleMaker::branchesHLTFinalDecision(TTree* tree){

    // Signal HLTs
    tree->Branch("passDeepDiTau35HLT", &passDeepDiTau35HLT);
    tree->Branch("passEleTauHLT", &passEleTauHLT);
    tree->Branch("passEleJetHLT", &passEleJetHLT);
    tree->Branch("passSingleEleHLT", &passSingleEleHLT);
    tree->Branch("passSinglePhotonHLT", &passSinglePhotonHLT);
    tree->Branch("passVBF2DTHLT", &passVBF2DTHLT);
    tree->Branch("passVBF1DTHLT", &passVBF1DTHLT);
    tree->Branch("passVBF1DTHLT_CorrChecker", &passVBF1DTHLT_CorrChecker);
    tree->Branch("passVBF1DTHLT_OverlapRemoval", &passVBF1DTHLT_OverlapRemoval);
    tree->Branch("passInclusiveVBFHLT", &passInclusiveVBFHLT);    
    tree->Branch("passDeepInclusiveVBFHLT", &passDeepInclusiveVBFHLT);    
    tree->Branch("passVBFEleHLT", &passVBFEleHLT);
    tree->Branch("passVBFPhotonHLT", &passVBFPhotonHLT);
    tree->Branch("passVBFMuonHLT", &passVBFMuonHLT);
    tree->Branch("passVBFMuonHLT_TripleJet", &passVBFMuonHLT_TripleJet);
    tree->Branch("passIsoMu24eta2p1HLT", &passIsoMu24eta2p1HLT);
    tree->Branch("passMuTauHLT", &passMuTauHLT);

    // Monitoring/Control HLTs
    tree->Branch("passUpperControlHLT", &passUpperControlHLT);
    tree->Branch("passLowerControlHLT", &passLowerControlHLT);
    tree->Branch("passDiTauControlHLT", &passDiTauControlHLT);

    // adhoc HLTs
    // delete dead code
    //tree->Branch("passHLTDummyL1", &passHLTDummyL1);
    //tree->Branch("passHLTDummyL1Loose", &passHLTDummyL1Loose);
    //tree->Branch("passHLTDummyL1NoIso", &passHLTDummyL1NoIso);

    tree->Branch("passHLT_Dummy_L1VBFEG_TightIso", &passHLT_Dummy_L1VBFEG_TightIso);
    tree->Branch("passHLT_Dummy_L1VBFEG_LooseIso", &passHLT_Dummy_L1VBFEG_LooseIso);
    tree->Branch("passHLT_Dummy_L1VBFEG_NoIso", &passHLT_Dummy_L1VBFEG_NoIso);
    tree->Branch("passHLT_Dummy_L1EG_TightIso", &passHLT_Dummy_L1EG_TightIso);
    tree->Branch("passHLT_Dummy_L1EG_LooseIso", &passHLT_Dummy_L1EG_LooseIso);
    tree->Branch("passHLT_Dummy_L1EG_NoIso", &passHLT_Dummy_L1EG_NoIso);

    tree->Branch("passHLTDummyEGORL1", &passHLTDummyEGORL1);
 
    // Jaime's HLTs
    tree->Branch("pass2Tau1JetHLT", &pass2Tau1JetHLT);
    tree->Branch("pass2Tau1JetHigherHLT", &pass2Tau1JetHigherHLT);
}

void NtupleMaker::fillHLTFinalDecision(const edm::Event& iEvent, bool DEBUG){

    using namespace edm;

    // getting trigger results, following this page
    // https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideHLTAnalysis
    edm::Handle<edm::TriggerResults> triggerResults;
    iEvent.getByToken(triggerResultToken_, triggerResults);
    const edm::TriggerNames triggerNames_ = iEvent.triggerNames(*triggerResults);


    // Signal HLTs
    passDeepDiTau35HLT = triggerResults->accept(triggerNames_.triggerIndex(
                       "HLT_DoubleMediumDeepTauPFTauHPS35_L2NN_eta2p1_v2"));

    passEleTauHLT = triggerResults->accept(triggerNames_.triggerIndex(
                 "HLT_Ele24_eta2p1_WPTight_Gsf_LooseDeepTauPFTauHPS30_eta2p1_CrossL1_v3"));
    passEleJetHLT = triggerResults->accept(triggerNames_.triggerIndex(
                 "HLT_Ele23_CaloIdL_TrackIdL_IsoVL_PFJet30_v20"));
    passSingleEleHLT = triggerResults->accept(triggerNames_.triggerIndex(
                     "HLT_Ele32_WPTight_Gsf_v17"));

    passIsoMu24eta2p1HLT = triggerResults->accept(triggerNames_.triggerIndex(
                         "HLT_IsoMu24_eta2p1_v17"));
    passMuTauHLT = triggerResults->accept(triggerNames_.triggerIndex(
                 "HLT_IsoMu20_eta2p1_LooseDeepTauPFTauHPS27_eta2p1_CrossL1_v3"));

    passSinglePhotonHLT = triggerResults->accept(triggerNames_.triggerIndex(
                     "HLT_Photon33_v7"));
    passVBF2DTHLT = triggerResults->accept(triggerNames_.triggerIndex(
                  "HLT_DoublePFJets40_Mass500_MediumDeepTauPFTauHPS45_L2NN_MediumDeepTauPFTauHPS20_eta2p1_v2"));
    //passVBF1DTHLT = triggerResults->accept(triggerNames_.triggerIndex(
    //              "HLT_DoublePFJets40_Mass500_MediumDeepTauPFTauHPS45_L2NN_eta2p1_v2"));
    passVBF1DTHLT_CorrChecker = triggerResults->accept(triggerNames_.triggerIndex(
                    "HLT_VBFParking_DoublePFJets40_Mass500_MediumDeepTauPFTauHPS45_L2NN_eta2p1_v1"));
                  //"HLT_DoublePFJets40_Mass500_MediumDeepTauPFTauHPS45_L2NN_eta2p1_CorrChecker_v2"));
    //passVBF1DTHLT_OverlapRemoval = triggerResults->accept(triggerNames_.triggerIndex(
    //              "HLT_DoublePFJets40_Mass500_MediumDeepTauPFTauHPS45_L2NN_eta2p1_OverlapRemoval_v2"));
    //
    //passInclusiveVBFHLT = triggerResults->accept(triggerNames_.triggerIndex(
    //                    "HLT_VBF_DoubleTightChargedIsoPFTauHPS20_Trk1_eta2p1_v3"));
    passDeepInclusiveVBFHLT = triggerResults->accept(triggerNames_.triggerIndex(
                            "HLT_VBF_DoubleMediumDeepTauPFTauHPS20_eta2p1_v2"));

    if (DEBUG) std::cout << "filled signal HLTs" << std::endl;

    passVBFEleHLT = triggerResults->accept(triggerNames_.triggerIndex(
                  //"HLT_VBF_DoublePFJets35_MassMin350_Ele12_WPLoose_Gsf_L1VBFIsoEG_v1"));
                  //"HLT_VBF_DoublePFJets45_MassMin500_Ele12_eta2p1_WPTight_Gsf_v1"));
                  "HLT_VBFParking_DoublePFJets45_MassMin500_Ele12_eta2p1_WPTight_Gsf_v1"));

    passVBFPhotonHLT = triggerResults->accept(triggerNames_.triggerIndex(
                  //"HLT_VBF_DoublePFJets45_MassMin500_Photon12_v1"));
                  "HLT_VBFParking_DoublePFJets45_MassMin500_Photon12_v1"));

    if (DEBUG) std::cout << "filled VBF+EG HLTs" << std::endl;

    passVBFMuonHLT = triggerResults->accept(triggerNames_.triggerIndex(
                   "HLT_VBFparking_Mu3_TrkIsoVVL_DiPFJet80_30_Mjj500_v1"));

    passVBFMuonHLT_TripleJet = triggerResults->accept(triggerNames_.triggerIndex(
                   "HLT_VBFparking_Mu3_TrkIsoVVL_DiPFJet80_30_Mjj500_TriplePFJet_v1"));

    if (DEBUG) std::cout << "filled VBF Muon HLTs" << std::endl;


    // Monitoring/Control HLTs
    passUpperControlHLT = triggerResults->accept(triggerNames_.triggerIndex(
                        "HLT_IsoMu24_eta2p1_MediumDeepTauPFTauHPS45_L2NN_eta2p1_CrossL1_v2"));
    passLowerControlHLT = triggerResults->accept(triggerNames_.triggerIndex(
                        "HLT_IsoMu24_eta2p1_MediumDeepTauPFTauHPS20_eta2p1_SingleL1_v2"));
    passDiTauControlHLT = triggerResults->accept(triggerNames_.triggerIndex(
                        "HLT_IsoMu24_eta2p1_MediumDeepTauPFTauHPS35_L2NN_eta2p1_CrossL1_v3"));

    if (DEBUG) std::cout << "filled monitoring HLTs" << std::endl;

    // adhoc HLTs
    //passHLTDummyL1 = triggerResults->accept(triggerNames_.triggerIndex("HLT_DummyL1_v1"));
    //passHLTDummyL1Loose = triggerResults->accept(triggerNames_.triggerIndex("HLT_DummyL1Loose_v1"));
    //passHLTDummyL1NoIso = triggerResults->accept(triggerNames_.triggerIndex("HLT_DummyL1NoIso_v1"));
    //passHLTDummyEGORL1 = triggerResults->accept(triggerNames_.triggerIndex("HLT_DummyEGORL1_v1"));
    passHLT_Dummy_L1VBFEG_TightIso = triggerResults->accept(triggerNames_.triggerIndex(
                                   "HLT_Dummy_L1VBFEG_TightIso_v1"));
    passHLT_Dummy_L1VBFEG_LooseIso = triggerResults->accept(triggerNames_.triggerIndex(
                                   "HLT_Dummy_L1VBFEG_LooseIso_v1"));
    passHLT_Dummy_L1VBFEG_NoIso = triggerResults->accept(triggerNames_.triggerIndex(
                                   "HLT_Dummy_L1VBFEG_NoIso_v1"));
    passHLT_Dummy_L1EG_TightIso = triggerResults->accept(triggerNames_.triggerIndex(
                                   "HLT_Dummy_L1EG_TightIso_v1"));
    passHLT_Dummy_L1EG_LooseIso = triggerResults->accept(triggerNames_.triggerIndex(
                                   "HLT_Dummy_L1EG_LooseIso_v1"));
    passHLT_Dummy_L1EG_NoIso = triggerResults->accept(triggerNames_.triggerIndex(
                                   "HLT_Dummy_L1EG_NoIso_v1"));

    if (DEBUG) std::cout << "filled dummy HLTs" << std::endl;

    // Jaime's HLTs
    pass2Tau1JetHLT = triggerResults->accept(triggerNames_.triggerIndex(
                    "HLT_DoubleMediumDeepTauPFTauHPS30_L2NN_eta2p1_PFJet60_v2"));
    pass2Tau1JetHigherHLT = triggerResults->accept(triggerNames_.triggerIndex(
                          "HLT_DoubleMediumDeepTauPFTauHPS30_L2NN_eta2p1_PFJet75_v2"));

    if (DEBUG) std::cout << "filled Jaime's triggers" << std::endl;

}
