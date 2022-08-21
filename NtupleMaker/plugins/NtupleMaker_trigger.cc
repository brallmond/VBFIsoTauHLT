#include "VBFIsoTauHLT/NtupleMaker/plugins/NtupleMaker.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"

using namespace std;


float 	pt_;
float 	eta_;
float 	phi_;
float 	energy_;

// is there a smart way to organize these?
// Signal, Monitoring/Control, adhoc, Jaime's (not stored)
//branches for EleTau
//hltEle24erWPTightGsfTrackIsoFilterForTau // single final electron filter
int passhltEle24erWPTightGsfTrackIsoFilterForTau;
vector<float> EleTauHLTFinalFilterEle_pt;
vector<float> EleTauHLTFinalFilterEle_eta;
vector<float> EleTauHLTFinalFilterEle_phi;
vector<float> EleTauHLTFinalFilterEle_energy;
//hltHpsOverlapFilterIsoEle24WPTightGsfLooseETauWPDeepTauPFTau30 // single final tau filter
int passhltHpsOverlapFilterIsoEle24WPTightGsfLooseETauWPDeepTauPFTau30;
vector<float> EleTauHLTFinalFilterTau_pt;
vector<float> EleTauHLTFinalFilterTau_eta;
vector<float> EleTauHLTFinalFilterTau_phi;
vector<float> EleTauHLTFinalFilterTau_energy;

//branches for VBF2DTHLT
// the pass statements don't matter without a cut flow, but the final objects do for matching
int passhltL2VBFIsoTauNNFilter;
vector<float> hltL2VBFIsoTauNNFilter_pt;
vector<float> hltL2VBFIsoTauNNFilter_eta;
vector<float> hltL2VBFIsoTauNNFilter_phi;
vector<float> hltL2VBFIsoTauNNFilter_energy;

int passhltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch; // two taus final filter
vector<float> hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_pt;
vector<float> hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_eta;
vector<float> hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_phi;
vector<float> hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_energy;

int passhltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched; // matched L1 tau final filter
vector<float> hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_pt;
vector<float> hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_eta;
vector<float> hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_phi;
vector<float> hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_energy;

int passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedUsingDiJetCorrCheckerWithMediumDiTau; // dijet final filter
vector<float> hltMatchedVBFIsoTauTwoPFJets2CrossCleanedUsingDiJetCorrCheckerWithMediumDiTau_pt;
vector<float> hltMatchedVBFIsoTauTwoPFJets2CrossCleanedUsingDiJetCorrCheckerWithMediumDiTau_eta;
vector<float> hltMatchedVBFIsoTauTwoPFJets2CrossCleanedUsingDiJetCorrCheckerWithMediumDiTau_phi;
vector<float> hltMatchedVBFIsoTauTwoPFJets2CrossCleanedUsingDiJetCorrCheckerWithMediumDiTau_energy;


void NtupleMaker::branchesTriggers(TTree* tree){

    // VBFPlusTwoDeepTau HLT Modules
    // define additional branches later
    tree->Branch("passhltL2VBFIsoTauNNFilter", &passhltL2VBFIsoTauNNFilter);
    tree->Branch("hltL2VBFIsoTauNNFilter_pt", &hltL2VBFIsoTauNNFilter_pt);

    tree->Branch("passhltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch", &passhltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch);
    tree->Branch("hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_pt", &hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_pt);

    tree->Branch("passhltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched", &passhltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched);
    tree->Branch("hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_pt", &hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_pt);

    tree->Branch("passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedUsingDiJetCorrCheckerWithMediumDiTau", &passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedUsingDiJetCorrCheckerWithMediumDiTau);
    tree->Branch("hltMatchedVBFIsoTauTwoPFJets2CrossCleanedUsingDiJetCorrCheckerWithMediumDiTau_pt", &hltMatchedVBFIsoTauTwoPFJets2CrossCleanedUsingDiJetCorrCheckerWithMediumDiTau_pt);

    tree->Branch("passhltEle24erWPTightGsfTrackIsoFilterForTau", &passhltEle24erWPTightGsfTrackIsoFilterForTau);
    tree->Branch("EleTauHLTFinalFilterEle_pt", &EleTauHLTFinalFilterEle_pt);
    tree->Branch("EleTauHLTFinalFilterEle_eta", &EleTauHLTFinalFilterEle_eta);
    tree->Branch("EleTauHLTFinalFilterEle_phi", &EleTauHLTFinalFilterEle_phi);
    tree->Branch("EleTauHLTFinalFilterEle_energy", &EleTauHLTFinalFilterEle_energy);

    tree->Branch("passhltHpsOverlapFilterIsoEle24WPTightGsfLooseETauWPDeepTauPFTau30", &passhltHpsOverlapFilterIsoEle24WPTightGsfLooseETauWPDeepTauPFTau30);
    tree->Branch("EleTauHLTFinalFilterTau_pt", &EleTauHLTFinalFilterTau_pt);
    tree->Branch("EleTauHLTFinalFilterTau_eta", &EleTauHLTFinalFilterTau_eta);
    tree->Branch("EleTauHLTFinalFilterTau_phi", &EleTauHLTFinalFilterTau_phi);
    tree->Branch("EleTauHLTFinalFilterTau_energy", &EleTauHLTFinalFilterTau_energy);

}

void NtupleMaker::fillTriggers(const edm::Event& iEvent){

    using namespace edm;

    // clearing vectors and initializing flags at the start of every event 

    // VBF2DT
    passhltL2VBFIsoTauNNFilter = 0;
    hltL2VBFIsoTauNNFilter_pt.clear();

    passhltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch = 0;
    hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_pt.clear();

    passhltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched = 0;
    hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_pt.clear();

    passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedUsingDiJetCorrCheckerWithMediumDiTau = 0;
    hltMatchedVBFIsoTauTwoPFJets2CrossCleanedUsingDiJetCorrCheckerWithMediumDiTau_pt.clear();

    passhltEle24erWPTightGsfTrackIsoFilterForTau = 0;
    EleTauHLTFinalFilterEle_pt.clear();
    EleTauHLTFinalFilterEle_eta.clear();
    EleTauHLTFinalFilterEle_phi.clear();
    EleTauHLTFinalFilterEle_energy.clear();

    passhltHpsOverlapFilterIsoEle24WPTightGsfLooseETauWPDeepTauPFTau30 = 0;
    EleTauHLTFinalFilterTau_pt.clear();
    EleTauHLTFinalFilterTau_eta.clear();
    EleTauHLTFinalFilterTau_phi.clear();
    EleTauHLTFinalFilterTau_energy.clear();

    // getting trigger event per this page
    // https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideHLTAnalysis
    edm::Handle<trigger::TriggerEvent> triggerEvent; // this code should be with the filters
    iEvent.getByToken(triggerEventToken_, triggerEvent); // same

    const trigger::size_type nFilters(triggerEvent->sizeFilters());

    // make strings to identify filter names
    // no reason to have these if they're not shorter than the filter names themselves
    std::string hltL2VBFIsoTauNNFilter_Tag = "hltL2VBFIsoTauNNFilter::MYOTHERHLT";
    
    std::string hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_Tag = "hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch::MYOTHERHLT";
    
    std::string hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_Tag = "hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched::MYOTHERHLT";

    std::string hltMatchedVBFIsoTauTwoPFJets2CrossCleanedUsingDiJetCorrCheckerWithMediumDiTau_Tag = "hltMatchedVBFIsoTauTwoPFJets2CrossCleanedUsingDiJetCorrCheckerWithMediumDiTau::MYOTHERHLT";

    // accepted filters per event
    for(trigger::size_type iFilter=0; iFilter!=nFilters; ++iFilter) {
	std::string filterTag = triggerEvent->filterTag(iFilter).encode();
	trigger::Keys objectKeys = triggerEvent->filterKeys(iFilter);

	const trigger::TriggerObjectCollection& triggerObjects(triggerEvent->getObjects());
	// fill "pass filter" branches
	int nObjKeys = objectKeys.size();

        //if (filterTag == hltL2VBFIsoTauNNFilter_Tag 
        if (filterTag == "hltL2VBFIsoTauNNFilter::MYOTHERHLT"
                      && nObjKeys >= 1) passhltL2VBFIsoTauNNFilter = 1;

        if (filterTag == hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_Tag && nObjKeys >= 2) passhltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch = 1;

        if (filterTag == hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_Tag && nObjKeys >= 1) passhltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched = 1;

        if (filterTag == hltMatchedVBFIsoTauTwoPFJets2CrossCleanedUsingDiJetCorrCheckerWithMediumDiTau_Tag && nObjKeys >= 2) passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedUsingDiJetCorrCheckerWithMediumDiTau = 1;

        //
        if (filterTag == "hltEle24erWPTightGsfTrackIsoFilterForTau::MYOTHERHLT"
                      && nObjKeys >= 1) passhltEle24erWPTightGsfTrackIsoFilterForTau = 1;

        if (filterTag == "hltHpsOverlapFilterIsoEle24WPTightGsfLooseETauWPDeepTauPFTau30::MYOTHERHLT"
                      && nObjKeys >= 1) passhltHpsOverlapFilterIsoEle24WPTightGsfLooseETauWPDeepTauPFTau30 = 1;

        // it's definitely right to be clearing things where i'm clearing them, 
        // i shouldn't be defining strings, just break lines, make better variable names

	//loop over trigger objects and store their kinematics to the proper filter branches
	for(trigger::size_type iKey=0; iKey < nObjKeys; ++iKey){
	    trigger::size_type objKey = objectKeys.at(iKey);
	    const trigger::TriggerObject& triggerObj(triggerObjects[objKey]);
	    pt_ = triggerObj.pt();
	    eta_ = triggerObj.eta();
	    phi_ = triggerObj.phi();
	    energy_ = triggerObj.energy();

            if (filterTag == hltL2VBFIsoTauNNFilter_Tag
                 && passhltL2VBFIsoTauNNFilter && pt_>0) {
               hltL2VBFIsoTauNNFilter_pt.push_back(pt_);
            }

            if (filterTag == hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_Tag
                 && passhltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch && pt_>0) {
               hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_pt.push_back(pt_);
            }

            if (filterTag == hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_Tag
                 && passhltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched && pt_>0) {
               hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_pt.push_back(pt_);
            }

            if (filterTag == hltMatchedVBFIsoTauTwoPFJets2CrossCleanedUsingDiJetCorrCheckerWithMediumDiTau_Tag
                 && passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedUsingDiJetCorrCheckerWithMediumDiTau && pt_>0) {
               hltMatchedVBFIsoTauTwoPFJets2CrossCleanedUsingDiJetCorrCheckerWithMediumDiTau_pt.push_back(pt_);
            }

            if (filterTag == "hltEle24erWPTightGsfTrackIsoFilterForTau::MYOTHERHLT"
                 && passhltEle24erWPTightGsfTrackIsoFilterForTau && pt_>0) {
               EleTauHLTFinalFilterEle_pt.push_back(pt_);
               EleTauHLTFinalFilterEle_eta.push_back(eta_);
               EleTauHLTFinalFilterEle_phi.push_back(phi_);
               EleTauHLTFinalFilterEle_energy.push_back(energy_);
            }

            if (filterTag == "hltHpsOverlapFilterIsoEle24WPTightGsfLooseETauWPDeepTauPFTau30::MYOTHERHLT"
                 && passhltHpsOverlapFilterIsoEle24WPTightGsfLooseETauWPDeepTauPFTau30 && pt_>0) {
               EleTauHLTFinalFilterTau_pt.push_back(pt_);
               EleTauHLTFinalFilterTau_eta.push_back(eta_);
               EleTauHLTFinalFilterTau_phi.push_back(phi_);
               EleTauHLTFinalFilterTau_energy.push_back(energy_);
            }

	} // end loop over trigger object keys
    } // end loop over nfilters
} // end function
