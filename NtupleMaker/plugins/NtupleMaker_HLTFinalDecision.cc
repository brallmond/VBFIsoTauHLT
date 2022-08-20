#include "VBFIsoTauHLT/NtupleMaker/plugins/NtupleMaker.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"

using namespace std;

int passDeepDiTau35HLT;
int passEleTauHLT; // HLT_Ele24_eta2p1_WPTight_Gsf_LooseDeepTauPFTauHPS30_eta2p1_CrossL1_v2
int passVBF2DTHLT;
int passInclusiveVBFHLT;
int passDeepInclusiveVBFHLT;

int passUpperControlHLT;
int passLowerControlHLT;
int passDiTauControlHLT; // no longer in the menu ?

int passHLTDummyL1;
int passHLTDummyL1Loose;
int passHLTDummyEGORL1;

int pass2Tau1JetHLT; // Jaime's trigger
int pass2Tau1JetHigherHLT; // Jaime's other trigger (same as above with higher jet cut)

void NtupleMaker::branchesHLTFinalDecision(TTree* tree){

    tree->Branch("passDeepDiTau35HLT", &passDeepDiTau35HLT);
    tree->Branch("passEleTauHLT", &passEleTauHLT);
    tree->Branch("passVBF2DTHLT", &passVBF2DTHLT);
    tree->Branch("passInclusiveVBFHLT", &passInclusiveVBFHLT);    
    tree->Branch("passDeepInclusiveVBFHLT", &passDeepInclusiveVBFHLT);    

    tree->Branch("passUpperControlHLT", &passUpperControlHLT);
    tree->Branch("passLowerControlHLT", &passLowerControlHLT);
    tree->Branch("passDiTauControlHLT", &passDiTauControlHLT);

    tree->Branch("passHLTDummyL1", &passHLTDummyL1);
    tree->Branch("passHLTDummyL1Loose", &passHLTDummyL1Loose);
    tree->Branch("passHLTDummyEGORL1", &passHLTDummyEGORL1);
 
    tree->Branch("pass2Tau1JetHLT", &pass2Tau1JetHLT);
    tree->Branch("pass2Tau1JetHigherHLT", &pass2Tau1JetHigherHLT);
}

void NtupleMaker::fillHLTFinalDecision(const edm::Event& iEvent){

    using namespace edm;

    // getting trigger results, following this page
    // https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideHLTAnalysis
    edm::Handle<edm::TriggerResults> triggerResults;
    iEvent.getByToken(triggerResultToken_, triggerResults);
    const edm::TriggerNames triggerNames_ = iEvent.triggerNames(*triggerResults);

    // initialize variable (could remove)

    // Signal HLTs
    passDeepDiTau35HLT = triggerResults->accept(triggerNames_.triggerIndex("HLT_DoubleMediumDeepTauPFTauHPS35_L2NN_eta2p1_v1"));


    passEleTauHLT = triggerResults->accept(triggerNames_.triggerIndex(
                 "HLT_Ele24_eta2p1_WPTight_Gsf_LooseDeepTauPFTauHPS30_eta2p1_CrossL1_v1"));

    passVBF2DTHLT = triggerResults->accept(triggerNames_.triggerIndex(
                  "HLT_DoublePFJets40_Mass500_MediumDeepTauPFTauHPS45_L2NN_MediumDeepTauPFTauHPS20_eta2p1_v1"));

    passInclusiveVBFHLT = triggerResults->accept(triggerNames_.triggerIndex(
                        "HLT_VBF_DoubleTightChargedIsoPFTauHPS20_Trk1_eta2p1_v1"));

    passDeepInclusiveVBFHLT = triggerResults->accept(triggerNames_.triggerIndex("HLT_VBF_DoubleMediumDeepTauPFTauHPS20_eta2p1_v1"));

    // Monitoring/Control HLTs
    passUpperControlHLT = triggerResults->accept(triggerNames_.triggerIndex(
                        "HLT_IsoMu24_eta2p1_MediumDeepTauPFTauHPS45_L2NN_eta2p1_CrossL1_v1"));
    passLowerControlHLT = triggerResults->accept(triggerNames_.triggerIndex(
                        "HLT_IsoMu24_eta2p1_MediumDeepTauPFTauHPS20_eta2p1_SingleL1_v1"));
    passDiTauControlHLT = triggerResults->accept(triggerNames_.triggerIndex(
                        "HLT_IsoMu24_eta2p1_MediumDeepTauPFTauHPS35_L2NN_eta2p1_CrossL1_v1"));

    // adhoc HLTs
    passHLTDummyL1 = triggerResults->accept(triggerNames_.triggerIndex("HLT_DummyL1_v1"));
    passHLTDummyL1Loose = triggerResults->accept(triggerNames_.triggerIndex("HLT_DummyL1Loose_v1"));
    passHLTDummyEGORL1 = triggerResults->accept(triggerNames_.triggerIndex("HLT_DummyEGORL1_v1"));

    // Jaime's HLTs
    pass2Tau1JetHLT = triggerResults->accept(triggerNames_.triggerIndex(
                    "HLT_DoubleMediumDeepTauPFTauHPS30_L2NN_eta2p1_PFJet60_v1"));
    pass2Tau1JetHigherHLT = triggerResults->accept(triggerNames_.triggerIndex(
                          "HLT_DoubleMediumDeepTauPFTauHPS30_L2NN_eta2p1_PFJet75_v1"));

}
