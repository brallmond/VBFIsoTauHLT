#include "VBFIsoTauHLT/NtupleMaker/plugins/NtupleMaker.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"

using namespace std;

// Signal HLTs
int passDeepDiTau35HLT;
int passEleTauHLT;
int passSingleEleHLT;
int passVBF2DTHLT;
int passInclusiveVBFHLT;
int passDeepInclusiveVBFHLT;

// Monitoring/Control HLTs
int passIsoMu24eta2p1HLT;
int passUpperControlHLT;
int passLowerControlHLT;
int passDiTauControlHLT;

// adhoc HLTs
int passHLTDummyL1;
int passHLTDummyL1Loose;
int passHLTDummyEGORL1;

// Jaime's HLTs
int pass2Tau1JetHLT;
int pass2Tau1JetHigherHLT;

void NtupleMaker::branchesHLTFinalDecision(TTree* tree){

    // Signal HLTs
    tree->Branch("passDeepDiTau35HLT", &passDeepDiTau35HLT);
    tree->Branch("passEleTauHLT", &passEleTauHLT);
    tree->Branch("passSingleEleHLT", &passSingleEleHLT);
    tree->Branch("passVBF2DTHLT", &passVBF2DTHLT);
    tree->Branch("passInclusiveVBFHLT", &passInclusiveVBFHLT);    
    tree->Branch("passDeepInclusiveVBFHLT", &passDeepInclusiveVBFHLT);    

    // Monitoring/Control HLTs
    tree->Branch("passIsoMu24eta2p1HLT", &passIsoMu24eta2p1HLT);
    tree->Branch("passUpperControlHLT", &passUpperControlHLT);
    tree->Branch("passLowerControlHLT", &passLowerControlHLT);
    tree->Branch("passDiTauControlHLT", &passDiTauControlHLT);

    // adhoc HLTs
    tree->Branch("passHLTDummyL1", &passHLTDummyL1);
    tree->Branch("passHLTDummyL1Loose", &passHLTDummyL1Loose);
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
    passSingleEleHLT = triggerResults->accept(triggerNames_.triggerIndex(
                     "HLT_Ele32_WPTight_Gsf_v17"));
    passVBF2DTHLT = triggerResults->accept(triggerNames_.triggerIndex(
                  "HLT_DoublePFJets40_Mass500_MediumDeepTauPFTauHPS45_L2NN_MediumDeepTauPFTauHPS20_eta2p1_v2"));
    passInclusiveVBFHLT = triggerResults->accept(triggerNames_.triggerIndex(
                        "HLT_VBF_DoubleTightChargedIsoPFTauHPS20_Trk1_eta2p1_v3"));
    passDeepInclusiveVBFHLT = triggerResults->accept(triggerNames_.triggerIndex(
                            "HLT_VBF_DoubleMediumDeepTauPFTauHPS20_eta2p1_v2"));

    if (DEBUG) std::cout << "filled signal HLTs" << std::endl;

    // Monitoring/Control HLTs
    passIsoMu24eta2p1HLT = triggerResults->accept(triggerNames_.triggerIndex(
                         "HLT_IsoMu24_eta2p1_v17"));
    passUpperControlHLT = triggerResults->accept(triggerNames_.triggerIndex(
                        "HLT_IsoMu24_eta2p1_MediumDeepTauPFTauHPS45_L2NN_eta2p1_CrossL1_v2"));
    passLowerControlHLT = triggerResults->accept(triggerNames_.triggerIndex(
                        "HLT_IsoMu24_eta2p1_MediumDeepTauPFTauHPS20_eta2p1_SingleL1_v2"));
    passDiTauControlHLT = triggerResults->accept(triggerNames_.triggerIndex(
                        "HLT_IsoMu24_eta2p1_MediumDeepTauPFTauHPS35_L2NN_eta2p1_CrossL1_v3"));

    if (DEBUG) std::cout << "filled monitoring HLTs" << std::endl;

    // adhoc HLTs
    passHLTDummyL1 = triggerResults->accept(triggerNames_.triggerIndex("HLT_DummyL1_v1"));
    passHLTDummyL1Loose = triggerResults->accept(triggerNames_.triggerIndex("HLT_DummyL1Loose_v1"));
    passHLTDummyEGORL1 = triggerResults->accept(triggerNames_.triggerIndex("HLT_DummyEGORL1_v1"));

    if (DEBUG) std::cout << "filled dummy HLTs" << std::endl;

    // Jaime's HLTs
    pass2Tau1JetHLT = triggerResults->accept(triggerNames_.triggerIndex(
                    "HLT_DoubleMediumDeepTauPFTauHPS30_L2NN_eta2p1_PFJet60_v2"));
    pass2Tau1JetHigherHLT = triggerResults->accept(triggerNames_.triggerIndex(
                          "HLT_DoubleMediumDeepTauPFTauHPS30_L2NN_eta2p1_PFJet75_v2"));

    if (DEBUG) std::cout << "filled Jaime's triggers" << std::endl;

}
