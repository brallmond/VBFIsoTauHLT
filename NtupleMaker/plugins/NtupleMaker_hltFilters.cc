#include "VBFIsoTauHLT/NtupleMaker/plugins/NtupleMaker.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"

using namespace std;

//branches for passDeepDiTau35HLT [x]
//branches for passInclusiveVBFHLT
//branches for passDeepInclusiveVBFHLT
// Monitoring/Control HLTs
//branches for passIsoMu24eta2p1HLT
//branches for passUpperControlHLT
//branches for passLowerControlHLT
//branches for passDiTauControlHLT

// Signal
//EleTau
int passEleTauFinalFilterEle;
vector<float> EleTauFinalFilterEle_pt;
vector<float> EleTauFinalFilterEle_eta;
vector<float> EleTauFinalFilterEle_phi;
vector<float> EleTauFinalFilterEle_energy;
int passEleTauFinalFilterTau;
vector<float> EleTauFinalFilterTau_pt;
vector<float> EleTauFinalFilterTau_eta;
vector<float> EleTauFinalFilterTau_phi;
vector<float> EleTauFinalFilterTau_energy;

//SingleEle
int passSingleEleFinalFilter;
vector<float> SingleEleFinalFilter_pt;
vector<float> SingleEleFinalFilter_eta;
vector<float> SingleEleFinalFilter_phi;
vector<float> SingleEleFinalFilter_energy;

//VBF2DTHLT
int passhltL2VBFIsoTauNNFilter;
vector<float> hltL2VBFIsoTauNNFilter_pt;
vector<float> hltL2VBFIsoTauNNFilter_eta;
vector<float> hltL2VBFIsoTauNNFilter_phi;
vector<float> hltL2VBFIsoTauNNFilter_energy;
int passVBF2DTDoubleTauFinalFilter;
vector<float> VBF2DTDoubleTauFinalFilter_pt;
vector<float> VBF2DTDoubleTauFinalFilter_eta;
vector<float> VBF2DTDoubleTauFinalFilter_phi;
vector<float> VBF2DTDoubleTauFinalFilter_energy;
int passVBF2DTL1MatchedTauFinalFilter; 
vector<float> VBF2DTL1MatchedTauFinalFilter_pt;
vector<float> VBF2DTL1MatchedTauFinalFilter_eta;
vector<float> VBF2DTL1MatchedTauFinalFilter_phi;
vector<float> VBF2DTL1MatchedTauFinalFilter_energy;
int passVBF2DTDoubleJetFinalFilter;
vector<float> VBF2DTDoubleJetFinalFilter_pt;
vector<float> VBF2DTDoubleJetFinalFilter_eta;
vector<float> VBF2DTDoubleJetFinalFilter_phi;
vector<float> VBF2DTDoubleJetFinalFilter_energy;


void NtupleMaker::branchesTriggers(TTree* tree){

    //EleTau
    tree->Branch("passEleTauFinalFilterEle", &passEleTauFinalFilterEle);
    tree->Branch("EleTauFinalFilterEle_pt", &EleTauFinalFilterEle_pt);
    tree->Branch("EleTauFinalFilterEle_eta", &EleTauFinalFilterEle_eta);
    tree->Branch("EleTauFinalFilterEle_phi", &EleTauFinalFilterEle_phi);
    tree->Branch("EleTauFinalFilterEle_energy", &EleTauFinalFilterEle_energy);
    tree->Branch("passEleTauFinalFilterTau", &passEleTauFinalFilterTau);
    tree->Branch("EleTauFinalFilterTau_pt", &EleTauFinalFilterTau_pt);
    tree->Branch("EleTauFinalFilterTau_eta", &EleTauFinalFilterTau_eta);
    tree->Branch("EleTauFinalFilterTau_phi", &EleTauFinalFilterTau_phi);
    tree->Branch("EleTauFinalFilterTau_energy", &EleTauFinalFilterTau_energy);

    //SingleEle
    tree->Branch("passSingleEleFinalFilter", &passSingleEleFinalFilter);
    tree->Branch("SingleEleFinalFilter_pt", &SingleEleFinalFilter_pt);
    tree->Branch("SingleEleFinalFilter_eta", &SingleEleFinalFilter_eta);
    tree->Branch("SingleEleFinalFilter_phi", &SingleEleFinalFilter_phi);
    tree->Branch("SingleEleFinalFilter_energy", &SingleEleFinalFilter_energy);

    // VBFPlusTwoDeepTau HLT Modules
    tree->Branch("passhltL2VBFIsoTauNNFilter", &passhltL2VBFIsoTauNNFilter);
    tree->Branch("hltL2VBFIsoTauNNFilter_pt", &hltL2VBFIsoTauNNFilter_pt);
    tree->Branch("hltL2VBFIsoTauNNFilter_eta", &hltL2VBFIsoTauNNFilter_eta);
    tree->Branch("hltL2VBFIsoTauNNFilter_phi", &hltL2VBFIsoTauNNFilter_phi);
    tree->Branch("hltL2VBFIsoTauNNFilter_energy", &hltL2VBFIsoTauNNFilter_energy);

    tree->Branch("passVBF2DTDoubleTauFinalFilter", &passVBF2DTDoubleTauFinalFilter);
    tree->Branch("VBF2DTDoubleTauFinalFilter_pt", &VBF2DTDoubleTauFinalFilter_pt);
    tree->Branch("VBF2DTDoubleTauFinalFilter_eta", &VBF2DTDoubleTauFinalFilter_eta);
    tree->Branch("VBF2DTDoubleTauFinalFilter_phi", &VBF2DTDoubleTauFinalFilter_phi);
    tree->Branch("VBF2DTDoubleTauFinalFilter_energy", &VBF2DTDoubleTauFinalFilter_energy);

    tree->Branch("passVBF2DTL1MatchedTauFinalFilter", &passVBF2DTL1MatchedTauFinalFilter);
    tree->Branch("VBF2DTL1MatchedTauFinalFilter_pt", &VBF2DTL1MatchedTauFinalFilter_pt);
    tree->Branch("VBF2DTL1MatchedTauFinalFilter_eta", &VBF2DTL1MatchedTauFinalFilter_eta);
    tree->Branch("VBF2DTL1MatchedTauFinalFilter_phi", &VBF2DTL1MatchedTauFinalFilter_phi);
    tree->Branch("VBF2DTL1MatchedTauFinalFilter_energy", &VBF2DTL1MatchedTauFinalFilter_energy);

    tree->Branch("passVBF2DTDoubleJetFinalFilter", &passVBF2DTDoubleJetFinalFilter);
    tree->Branch("VBF2DTDoubleJetFinalFilter_pt", &VBF2DTDoubleJetFinalFilter_pt);
    tree->Branch("VBF2DTDoubleJetFinalFilter_eta", &VBF2DTDoubleJetFinalFilter_eta);
    tree->Branch("VBF2DTDoubleJetFinalFilter_phi", &VBF2DTDoubleJetFinalFilter_phi);
    tree->Branch("VBF2DTDoubleJetFinalFilter_energy", &VBF2DTDoubleJetFinalFilter_energy);

}

// small function to fill kinematics to object branches
// when filter is matched
void fillFilterKinematics(
  trigger::Keys objectKeys_,
  trigger::TriggerObjectCollection triggerObjects_,
  int nObjKeys_,
  vector<float> &branch_pt,
  vector<float> &branch_eta, 
  vector<float> &branch_phi,
  vector<float> &branch_energy) {

  for(trigger::size_type iKey=0; iKey < nObjKeys_; ++iKey) {
    trigger::size_type objKey = objectKeys_.at(iKey);
    const trigger::TriggerObject& triggerObj(triggerObjects_[objKey]);
    branch_pt.push_back(triggerObj.pt());
    branch_eta.push_back(triggerObj.eta());
    branch_phi.push_back(triggerObj.phi());
    branch_energy.push_back(triggerObj.energy());
  }

}

void NtupleMaker::fillTriggers(const edm::Event& iEvent){

    using namespace edm;

    // clearing vectors and initializing flags at the start of every event 
    // EleTau
    passEleTauFinalFilterEle = 0;
    EleTauFinalFilterEle_pt.clear();
    EleTauFinalFilterEle_eta.clear();
    EleTauFinalFilterEle_phi.clear();
    EleTauFinalFilterEle_energy.clear();

    passEleTauFinalFilterTau = 0;
    EleTauFinalFilterTau_pt.clear();
    EleTauFinalFilterTau_eta.clear();
    EleTauFinalFilterTau_phi.clear();
    EleTauFinalFilterTau_energy.clear();

    // SingleEle
    passSingleEleFinalFilter = 0;
    SingleEleFinalFilter_pt.clear();
    SingleEleFinalFilter_eta.clear();
    SingleEleFinalFilter_phi.clear();
    SingleEleFinalFilter_energy.clear();

    // VBF2DT
    passhltL2VBFIsoTauNNFilter = 0;
    hltL2VBFIsoTauNNFilter_pt.clear();
    hltL2VBFIsoTauNNFilter_eta.clear();
    hltL2VBFIsoTauNNFilter_phi.clear();
    hltL2VBFIsoTauNNFilter_energy.clear();

    passVBF2DTDoubleTauFinalFilter = 0;
    VBF2DTDoubleTauFinalFilter_pt.clear();
    VBF2DTDoubleTauFinalFilter_eta.clear();
    VBF2DTDoubleTauFinalFilter_phi.clear();
    VBF2DTDoubleTauFinalFilter_energy.clear();

    passVBF2DTL1MatchedTauFinalFilter = 0;
    VBF2DTL1MatchedTauFinalFilter_pt.clear();
    VBF2DTL1MatchedTauFinalFilter_eta.clear();
    VBF2DTL1MatchedTauFinalFilter_phi.clear();
    VBF2DTL1MatchedTauFinalFilter_energy.clear();

    passVBF2DTDoubleJetFinalFilter = 0;
    VBF2DTDoubleJetFinalFilter_pt.clear();
    VBF2DTDoubleJetFinalFilter_eta.clear();
    VBF2DTDoubleJetFinalFilter_phi.clear();
    VBF2DTDoubleJetFinalFilter_energy.clear();


    // getting trigger event per this page
    // https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideHLTAnalysis
    edm::Handle<trigger::TriggerEvent> triggerEvent;
    iEvent.getByToken(triggerEventToken_, triggerEvent);

    const trigger::size_type nFilters(triggerEvent->sizeFilters());

    // accepted filters per event
    // for each event, look at the filters fired
    // if the filter is one we want, mark it as filled and store its objects
    for(trigger::size_type iFilter=0; iFilter!=nFilters; ++iFilter) {
	std::string filterTag = triggerEvent->filterTag(iFilter).encode();
	trigger::Keys objectKeys = triggerEvent->filterKeys(iFilter);

	const trigger::TriggerObjectCollection& triggerObjects(triggerEvent->getObjects());
	int nObjKeys = objectKeys.size();
       
        if (nObjKeys == 0) continue; 
        //std::cout << "filter tag: " << filterTag  << " iFilter " << iFilter  << " nObjKeys " << nObjKeys << std::endl;

        // EleTau
        if (filterTag == "hltEle24erWPTightGsfTrackIsoFilterForTau::MYOTHERHLT"
                      && nObjKeys >= 1) {
          passEleTauFinalFilterEle = 1;
          fillFilterKinematics(objectKeys, triggerObjects, nObjKeys,
                               EleTauFinalFilterEle_pt,
                               EleTauFinalFilterEle_eta,
                               EleTauFinalFilterEle_phi,
                               EleTauFinalFilterEle_energy);
          continue;
        }

        if (filterTag == "hltHpsOverlapFilterIsoEle24WPTightGsfLooseETauWPDeepTauPFTau30::MYOTHERHLT"
                      && nObjKeys >= 1) {
          passEleTauFinalFilterTau = 1;
          fillFilterKinematics(objectKeys, triggerObjects, nObjKeys,
                               EleTauFinalFilterTau_pt,
                               EleTauFinalFilterTau_eta,
                               EleTauFinalFilterTau_phi,
                               EleTauFinalFilterTau_energy);
          continue;
        }

        // SingleEle
        if (filterTag == "hltEle32WPTightGsfTrackIsoFilter::MYOTHERHLT"
                      && nObjKeys >= 1) {
          passSingleEleFinalFilter = 1;
          fillFilterKinematics(objectKeys, triggerObjects, nObjKeys,
                               SingleEleFinalFilter_pt,
                               SingleEleFinalFilter_eta,
                               SingleEleFinalFilter_phi,
                               SingleEleFinalFilter_energy);
          continue;
        }


        // VBF2DT
        if (filterTag == "hltL2VBFIsoTauNNFilter::MYOTHERHLT"
                      && nObjKeys >= 1) {
          passhltL2VBFIsoTauNNFilter = 1;
          fillFilterKinematics(objectKeys, triggerObjects, nObjKeys,
                               hltL2VBFIsoTauNNFilter_pt,
                               hltL2VBFIsoTauNNFilter_eta,
                               hltL2VBFIsoTauNNFilter_phi,
                               hltL2VBFIsoTauNNFilter_energy);
          continue;
        }

        if (filterTag == "passhltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch::MYOTHERHLT"
                      && nObjKeys >= 2) {
          passVBF2DTDoubleTauFinalFilter = 1;
          fillFilterKinematics(objectKeys, triggerObjects, nObjKeys,
                               VBF2DTDoubleTauFinalFilter_pt,
                               VBF2DTDoubleTauFinalFilter_eta,
                               VBF2DTDoubleTauFinalFilter_phi,
                               VBF2DTDoubleTauFinalFilter_energy);
          continue;
        }

        if (filterTag == "hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched::MYOTHERHLT"  
                      && nObjKeys >= 1) {
          passVBF2DTL1MatchedTauFinalFilter = 1;
          fillFilterKinematics(objectKeys, triggerObjects, nObjKeys,
                               VBF2DTL1MatchedTauFinalFilter_pt,
                               VBF2DTL1MatchedTauFinalFilter_eta,
                               VBF2DTL1MatchedTauFinalFilter_phi,
                               VBF2DTL1MatchedTauFinalFilter_energy);
          continue;
        }

        if (filterTag == "hltMatchedVBFIsoTauTwoPFJets2CrossCleanedUsingDiJetCorrCheckerWithMediumDiTau::MYOTHERHLT" 
                      && nObjKeys >= 2) {
          passVBF2DTDoubleJetFinalFilter = 1;
          fillFilterKinematics(objectKeys, triggerObjects, nObjKeys,
                               VBF2DTDoubleJetFinalFilter_pt,
                               VBF2DTDoubleJetFinalFilter_eta,
                               VBF2DTDoubleJetFinalFilter_phi,
                               VBF2DTDoubleJetFinalFilter_energy);
          continue;
        }

    } // end loop over nfilters
} // end function
