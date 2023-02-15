#include "VBFIsoTauHLT/NtupleMaker/plugins/NtupleMaker.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"

using namespace std;

//branches for passLowerControlHLT
//branches for passDiTauControlHLT

// Signal
// DiTau
int passhltL2DoubleTauTagNNFilter;
vector<float> hltL2DoubleTauTagNNFilter_pt;
vector<float> hltL2DoubleTauTagNNFilter_eta;
vector<float> hltL2DoubleTauTagNNFilter_phi;
vector<float> hltL2DoubleTauTagNNFilter_energy;
int passDiTauFinalFilter;
vector<float> DiTauFinalFilter_pt;
vector<float> DiTauFinalFilter_eta;
vector<float> DiTauFinalFilter_phi;
vector<float> DiTauFinalFilter_energy;

// EleTau
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
int passEleTauFinalFilterOverlap;
vector<float> EleTauFinalFilterOverlap_pt;
vector<float> EleTauFinalFilterOverlap_eta;
vector<float> EleTauFinalFilterOverlap_phi;
vector<float> EleTauFinalFilterOverlap_energy;

// SingleEle
int passSingleEleFinalFilter;
vector<float> SingleEleFinalFilter_pt;
vector<float> SingleEleFinalFilter_eta;
vector<float> SingleEleFinalFilter_phi;
vector<float> SingleEleFinalFilter_energy;

// VBF2DTHLT
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

// Inclusive VBF
// hltMatchedVBFTwoPFJets2CrossCleanedFromDoubleMediumDeepTauDitauWPPFTauHPS20
int passInclusiveVBFBothJetsFinalFilter;
vector<float> InclusiveVBFBothJetsFinalFilter_pt;
vector<float> InclusiveVBFBothJetsFinalFilter_eta;
vector<float> InclusiveVBFBothJetsFinalFilter_phi;
vector<float> InclusiveVBFBothJetsFinalFilter_energy;
// hltMatchedVBFOnePFJet2CrossCleanedFromDoubleMediumDeepTauDitauWPPFTauHPS20
int passInclusiveVBFLeadingJetFinalFilter;
vector<float> InclusiveVBFLeadingJetFinalFilter_pt;
vector<float> InclusiveVBFLeadingJetFinalFilter_eta;
vector<float> InclusiveVBFLeadingJetFinalFilter_phi;
vector<float> InclusiveVBFLeadingJetFinalFilter_energy;
// hltHpsDoublePFTau20TrackDeepTauDitauWPAgainstMuon
int passInclusiveVBFBothTausFinalFilter;
vector<float> InclusiveVBFBothTausFinalFilter_pt;
vector<float> InclusiveVBFBothTausFinalFilter_eta;
vector<float> InclusiveVBFBothTausFinalFilter_phi;
vector<float> InclusiveVBFBothTausFinalFilter_energy;

// VBF Electron
// hltMatchedVBFTwoPFJets2CrossCleanedFromEle12WPLoose1GsfTrackIsoFilter
int passVBFElectronBothJetsFinalFilter;
vector<float> VBFElectronBothJetsFinalFilter_pt;
vector<float> VBFElectronBothJetsFinalFilter_eta;
vector<float> VBFElectronBothJetsFinalFilter_phi;
vector<float> VBFElectronBothJetsFinalFilter_energy;
// hltEle12WPLoose1GsfTrackIsoFilter
int passVBFElectronEleFinalFilter;
vector<float> VBFElectronEleFinalFilter_pt;
vector<float> VBFElectronEleFinalFilter_eta;
vector<float> VBFElectronEleFinalFilter_phi;
vector<float> VBFElectronEleFinalFilter_energy;

// VBF Photon
// hltVBFTwoPFJetsForVBFPhotonTrigger
int passVBFPhotonBothJetsFinalFilter;
vector<float> VBFPhotonBothJetsFinalFilter_pt;
vector<float> VBFPhotonBothJetsFinalFilter_eta;
vector<float> VBFPhotonBothJetsFinalFilter_phi;
vector<float> VBFPhotonBothJetsFinalFilter_energy;
// hltEG12L1VBFIsoEGOR15HEFilter
int passVBFPhotonPhoFinalFilter;
vector<float> VBFPhotonPhoFinalFilter_pt;
vector<float> VBFPhotonPhoFinalFilter_eta;
vector<float> VBFPhotonPhoFinalFilter_phi;
vector<float> VBFPhotonPhoFinalFilter_energy;

// Monitoring
// SingleMu
int passSingleMuAndLowerMuTauFinalFilter;
vector<float> SingleMuAndLowerMuTauFinalFilter_pt;
vector<float> SingleMuAndLowerMuTauFinalFilter_eta;
vector<float> SingleMuAndLowerMuTauFinalFilter_phi;
vector<float> SingleMuAndLowerMuTauFinalFilter_energy;

// Upper MuTau
int passUpperMuTauL2NN;
vector<float> UpperMuTauL2NN_pt;
vector<float> UpperMuTauL2NN_eta;
vector<float> UpperMuTauL2NN_phi;
vector<float> UpperMuTauL2NN_energy;
int passUpperMuTauAndDiTau35FinalFilterMuon;
vector<float> UpperMuTauAndDiTau35FinalFilterMuon_pt;
vector<float> UpperMuTauAndDiTau35FinalFilterMuon_eta;
vector<float> UpperMuTauAndDiTau35FinalFilterMuon_phi;
vector<float> UpperMuTauAndDiTau35FinalFilterMuon_energy;
int passUpperMuTauFinalFilterTau;
vector<float> UpperMuTauFinalFilterTau_pt;
vector<float> UpperMuTauFinalFilterTau_eta;
vector<float> UpperMuTauFinalFilterTau_phi;
vector<float> UpperMuTauFinalFilterTau_energy;
int passUpperMuTauFinalFilterOverlap;
vector<float> UpperMuTauFinalFilterOverlap_pt;
vector<float> UpperMuTauFinalFilterOverlap_eta;
vector<float> UpperMuTauFinalFilterOverlap_phi;
vector<float> UpperMuTauFinalFilterOverlap_energy;

// Lower MuTau
// uses same Mu filter as SingleMu
int passLowerMuTauFinalFilterTau;
vector<float> LowerMuTauFinalFilterTau_pt;
vector<float> LowerMuTauFinalFilterTau_eta;
vector<float> LowerMuTauFinalFilterTau_phi;
vector<float> LowerMuTauFinalFilterTau_energy;
int passLowerMuTauFinalFilterOverlap;
vector<float> LowerMuTauFinalFilterOverlap_pt;
vector<float> LowerMuTauFinalFilterOverlap_eta;
vector<float> LowerMuTauFinalFilterOverlap_phi;
vector<float> LowerMuTauFinalFilterOverlap_energy;

// MuTau for DiTau 35
int passMuTauForDiTauL2NN = 0;
vector<float> MuTauForDiTauL2NN_pt;
vector<float> MuTauForDiTauL2NN_eta;
vector<float> MuTauForDiTauL2NN_phi;
vector<float> MuTauForDiTauL2NN_energy;
int passMuTauForDiTauFinalFilterTau = 0;
vector<float> MuTauForDiTauFinalFilterTau_pt;
vector<float> MuTauForDiTauFinalFilterTau_eta;
vector<float> MuTauForDiTauFinalFilterTau_phi;
vector<float> MuTauForDiTauFinalFilterTau_energy;
int passMuTauForDiTauFinalFilterOverlap = 0;
vector<float> MuTauForDiTauFinalFilterOverlap_pt;
vector<float> MuTauForDiTauFinalFilterOverlap_eta;
vector<float> MuTauForDiTauFinalFilterOverlap_phi;
vector<float> MuTauForDiTauFinalFilterOverlap_energy;

// TODO add Jaime HLT final filters
//      add Inclusive DiJet HLT final filters

void NtupleMaker::branchesTriggers(TTree* tree){

    //DiTau
    tree->Branch("passhltL2DoubleTauTagNNFilter", &passhltL2DoubleTauTagNNFilter);
    tree->Branch("hltL2DoubleTauTagNNFilter_pt", &hltL2DoubleTauTagNNFilter_pt);
    tree->Branch("hltL2DoubleTauTagNNFilter_eta", &hltL2DoubleTauTagNNFilter_eta);
    tree->Branch("hltL2DoubleTauTagNNFilter_phi", &hltL2DoubleTauTagNNFilter_phi);
    tree->Branch("hltL2DoubleTauTagNNFilter_energy", &hltL2DoubleTauTagNNFilter_energy);

    tree->Branch("passDiTauFinalFilter", &passDiTauFinalFilter);
    tree->Branch("DiTauFinalFilter_pt", &DiTauFinalFilter_pt);
    tree->Branch("DiTauFinalFilter_eta", &DiTauFinalFilter_eta);
    tree->Branch("DiTauFinalFilter_phi", &DiTauFinalFilter_phi);
    tree->Branch("DiTauFinalFilter_energy", &DiTauFinalFilter_energy);

    // EleTau
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

    tree->Branch("passEleTauFinalFilterOverlap", &passEleTauFinalFilterOverlap);
    tree->Branch("EleTauFinalFilterOverlap_pt", &EleTauFinalFilterOverlap_pt);
    tree->Branch("EleTauFinalFilterOverlap_eta", &EleTauFinalFilterOverlap_eta);
    tree->Branch("EleTauFinalFilterOverlap_phi", &EleTauFinalFilterOverlap_phi);
    tree->Branch("EleTauFinalFilterOverlap_energy", &EleTauFinalFilterOverlap_energy);

    // SingleEle
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

    // Inclusive VBF
    tree->Branch("passInclusiveVBFBothJetsFinalFilter", &passInclusiveVBFBothJetsFinalFilter);
    tree->Branch("InclusiveVBFBothJetsFinalFilter_pt", &InclusiveVBFBothJetsFinalFilter_pt);
    tree->Branch("InclusiveVBFBothJetsFinalFilter_eta", &InclusiveVBFBothJetsFinalFilter_eta);
    tree->Branch("InclusiveVBFBothJetsFinalFilter_phi", &InclusiveVBFBothJetsFinalFilter_phi);
    tree->Branch("InclusiveVBFBothJetsFinalFilter_energy", &InclusiveVBFBothJetsFinalFilter_energy);

    tree->Branch("passInclusiveVBFLeadingJetFinalFilter", &passInclusiveVBFLeadingJetFinalFilter);
    tree->Branch("InclusiveVBFLeadingJetFinalFilter_pt", &InclusiveVBFLeadingJetFinalFilter_pt);
    tree->Branch("InclusiveVBFLeadingJetFinalFilter_eta", &InclusiveVBFLeadingJetFinalFilter_eta);
    tree->Branch("InclusiveVBFLeadingJetFinalFilter_phi", &InclusiveVBFLeadingJetFinalFilter_phi);
    tree->Branch("InclusiveVBFLeadingJetFinalFilter_energy", &InclusiveVBFLeadingJetFinalFilter_energy);

    tree->Branch("passInclusiveVBFBothTausFinalFilter", &passInclusiveVBFBothTausFinalFilter);
    tree->Branch("InclusiveVBFBothTausFinalFilter_pt", &InclusiveVBFBothTausFinalFilter_pt);
    tree->Branch("InclusiveVBFBothTausFinalFilter_eta", &InclusiveVBFBothTausFinalFilter_eta);
    tree->Branch("InclusiveVBFBothTausFinalFilter_phi", &InclusiveVBFBothTausFinalFilter_phi);
    tree->Branch("InclusiveVBFBothTausFinalFilter_energy", &InclusiveVBFBothTausFinalFilter_energy);

    // VBF + Electron
    tree->Branch("passVBFElectronBothJetsFinalFilter", &passVBFElectronBothJetsFinalFilter);
    tree->Branch("VBFElectronBothJetsFinalFilter_pt", &VBFElectronBothJetsFinalFilter_pt);
    tree->Branch("VBFElectronBothJetsFinalFilter_eta", &VBFElectronBothJetsFinalFilter_eta);
    tree->Branch("VBFElectronBothJetsFinalFilter_phi", &VBFElectronBothJetsFinalFilter_phi);
    tree->Branch("VBFElectronBothJetsFinalFilter_energy", &VBFElectronBothJetsFinalFilter_energy);

    tree->Branch("passVBFElectronEleFinalFilter", &passVBFElectronEleFinalFilter);
    tree->Branch("VBFElectronEleFinalFilter_pt", &VBFElectronEleFinalFilter_pt);
    tree->Branch("VBFElectronEleFinalFilter_eta", &VBFElectronEleFinalFilter_eta);
    tree->Branch("VBFElectronEleFinalFilter_phi", &VBFElectronEleFinalFilter_phi);
    tree->Branch("VBFElectronEleFinalFilter_energy", &VBFElectronEleFinalFilter_energy);

    // VBF + Photon
    tree->Branch("passVBFPhotonBothJetsFinalFilter", &passVBFPhotonBothJetsFinalFilter);
    tree->Branch("VBFPhotonBothJetsFinalFilter_pt", &VBFPhotonBothJetsFinalFilter_pt);
    tree->Branch("VBFPhotonBothJetsFinalFilter_eta", &VBFPhotonBothJetsFinalFilter_eta);
    tree->Branch("VBFPhotonBothJetsFinalFilter_phi", &VBFPhotonBothJetsFinalFilter_phi);
    tree->Branch("VBFPhotonBothJetsFinalFilter_energy", &VBFPhotonBothJetsFinalFilter_energy);

    tree->Branch("passVBFPhotonPhoFinalFilter", &passVBFPhotonPhoFinalFilter);
    tree->Branch("VBFPhotonPhoFinalFilter_pt", &VBFPhotonPhoFinalFilter_pt);
    tree->Branch("VBFPhotonPhoFinalFilter_eta", &VBFPhotonPhoFinalFilter_eta);
    tree->Branch("VBFPhotonPhoFinalFilter_phi", &VBFPhotonPhoFinalFilter_phi);
    tree->Branch("VBFPhotonPhoFinalFilter_energy", &VBFPhotonPhoFinalFilter_energy);



    // Monitoring
    // Single Mu
    tree->Branch("passSingleMuAndLowerMuTauFinalFilter", &passSingleMuAndLowerMuTauFinalFilter);
    tree->Branch("SingleMuAndLowerMuTauFinalFilter_pt", &SingleMuAndLowerMuTauFinalFilter_pt);
    tree->Branch("SingleMuAndLowerMuTauFinalFilter_eta", &SingleMuAndLowerMuTauFinalFilter_eta);
    tree->Branch("SingleMuAndLowerMuTauFinalFilter_phi", &SingleMuAndLowerMuTauFinalFilter_phi);
    tree->Branch("SingleMuAndLowerMuTauFinalFilter_energy", &SingleMuAndLowerMuTauFinalFilter_energy);

    // Upper MuTau
    tree->Branch("passUpperMuTauL2NN", &passUpperMuTauL2NN);
    tree->Branch("UpperMuTauL2NN_pt", &UpperMuTauL2NN_pt);
    tree->Branch("UpperMuTauL2NN_eta", &UpperMuTauL2NN_eta);
    tree->Branch("UpperMuTauL2NN_phi", &UpperMuTauL2NN_phi);
    tree->Branch("UpperMuTauL2NN_energy", &UpperMuTauL2NN_energy);

    tree->Branch("passUpperMuTauAndDiTau35FinalFilterMuon", &passUpperMuTauAndDiTau35FinalFilterMuon);
    tree->Branch("UpperMuTauAndDiTau35FinalFilterMuon_pt", &UpperMuTauAndDiTau35FinalFilterMuon_pt);
    tree->Branch("UpperMuTauAndDiTau35FinalFilterMuon_eta", &UpperMuTauAndDiTau35FinalFilterMuon_eta);
    tree->Branch("UpperMuTauAndDiTau35FinalFilterMuon_phi", &UpperMuTauAndDiTau35FinalFilterMuon_phi);
    tree->Branch("UpperMuTauAndDiTau35FinalFilterMuon_energy", &UpperMuTauAndDiTau35FinalFilterMuon_energy);

    tree->Branch("passUpperMuTauFinalFilterTau", &passUpperMuTauFinalFilterTau);
    tree->Branch("UpperMuTauFinalFilterTau_pt", &UpperMuTauFinalFilterTau_pt);
    tree->Branch("UpperMuTauFinalFilterTau_eta", &UpperMuTauFinalFilterTau_eta);
    tree->Branch("UpperMuTauFinalFilterTau_phi", &UpperMuTauFinalFilterTau_phi);
    tree->Branch("UpperMuTauFinalFilterTau_energy", &UpperMuTauFinalFilterTau_energy);

    tree->Branch("passUpperMuTauFinalFilterOverlap", &passUpperMuTauFinalFilterOverlap);
    tree->Branch("UpperMuTauFinalFilterOverlap_pt", &UpperMuTauFinalFilterOverlap_pt);
    tree->Branch("UpperMuTauFinalFilterOverlap_eta", &UpperMuTauFinalFilterOverlap_eta);
    tree->Branch("UpperMuTauFinalFilterOverlap_phi", &UpperMuTauFinalFilterOverlap_phi);
    tree->Branch("UpperMuTauFinalFilterOverlap_energy", &UpperMuTauFinalFilterOverlap_energy);

    // Lower MuTau
    tree->Branch("passLowerMuTauFinalFilterTau", &passLowerMuTauFinalFilterTau);
    tree->Branch("LowerMuTauFinalFilterTau_pt", &LowerMuTauFinalFilterTau_pt);
    tree->Branch("LowerMuTauFinalFilterTau_eta", &LowerMuTauFinalFilterTau_eta);
    tree->Branch("LowerMuTauFinalFilterTau_phi", &LowerMuTauFinalFilterTau_phi);
    tree->Branch("LowerMuTauFinalFilterTau_energy", &LowerMuTauFinalFilterTau_energy);

    tree->Branch("passLowerMuTauFinalFilterOverlap", &passLowerMuTauFinalFilterOverlap);
    tree->Branch("LowerMuTauFinalFilterOverlap_pt", &LowerMuTauFinalFilterOverlap_pt);
    tree->Branch("LowerMuTauFinalFilterOverlap_eta", &LowerMuTauFinalFilterOverlap_eta);
    tree->Branch("LowerMuTauFinalFilterOverlap_phi", &LowerMuTauFinalFilterOverlap_phi);
    tree->Branch("LowerMuTauFinalFilterOverlap_energy", &LowerMuTauFinalFilterOverlap_energy);

    // MuTau for DiTau35
    tree->Branch("passMuTauForDiTauL2NN", &passMuTauForDiTauL2NN);
    tree->Branch("MuTauForDiTauL2NN_pt", &MuTauForDiTauL2NN_pt);
    tree->Branch("MuTauForDiTauL2NN_eta", &MuTauForDiTauL2NN_eta);
    tree->Branch("MuTauForDiTauL2NN_phi", &MuTauForDiTauL2NN_phi);
    tree->Branch("MuTauForDiTauL2NN_energy", &MuTauForDiTauL2NN_energy);
 
    tree->Branch("passMuTauForDiTauFinalFilterTau", &passMuTauForDiTauFinalFilterTau);
    tree->Branch("MuTauForDiTauFinalFilterTau_pt", &MuTauForDiTauFinalFilterTau_pt);
    tree->Branch("MuTauForDiTauFinalFilterTau_eta", &MuTauForDiTauFinalFilterTau_eta);
    tree->Branch("MuTauForDiTauFinalFilterTau_phi", &MuTauForDiTauFinalFilterTau_phi);
    tree->Branch("MuTauForDiTauFinalFilterTau_energy", &MuTauForDiTauFinalFilterTau_energy);

    tree->Branch("passMuTauForDiTauFinalFilterOverlap", &passMuTauForDiTauFinalFilterOverlap);
    tree->Branch("MuTauForDiTauFinalFilterOverlap_pt", &MuTauForDiTauFinalFilterOverlap_pt);
    tree->Branch("MuTauForDiTauFinalFilterOverlap_eta", &MuTauForDiTauFinalFilterOverlap_eta);
    tree->Branch("MuTauForDiTauFinalFilterOverlap_phi", &MuTauForDiTauFinalFilterOverlap_phi);
    tree->Branch("MuTauForDiTauFinalFilterOverlap_energy", &MuTauForDiTauFinalFilterOverlap_energy);

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
    // Signal
    // DiTau
    passhltL2DoubleTauTagNNFilter = 0;
    hltL2DoubleTauTagNNFilter_pt.clear();
    hltL2DoubleTauTagNNFilter_eta.clear();
    hltL2DoubleTauTagNNFilter_phi.clear();
    hltL2DoubleTauTagNNFilter_energy.clear();
    passDiTauFinalFilter = 0;
    DiTauFinalFilter_pt.clear();
    DiTauFinalFilter_eta.clear();
    DiTauFinalFilter_phi.clear();
    DiTauFinalFilter_energy.clear();

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

    passEleTauFinalFilterOverlap = 0;
    EleTauFinalFilterOverlap_pt.clear();
    EleTauFinalFilterOverlap_eta.clear();
    EleTauFinalFilterOverlap_phi.clear();
    EleTauFinalFilterOverlap_energy.clear();

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

    // Inclusive VBF
    passInclusiveVBFBothJetsFinalFilter = 0;
    InclusiveVBFBothJetsFinalFilter_pt.clear();
    InclusiveVBFBothJetsFinalFilter_eta.clear();
    InclusiveVBFBothJetsFinalFilter_phi.clear();
    InclusiveVBFBothJetsFinalFilter_energy.clear();

    passInclusiveVBFLeadingJetFinalFilter = 0;
    InclusiveVBFLeadingJetFinalFilter_pt.clear();
    InclusiveVBFLeadingJetFinalFilter_eta.clear();
    InclusiveVBFLeadingJetFinalFilter_phi.clear();
    InclusiveVBFLeadingJetFinalFilter_energy.clear();

    passInclusiveVBFBothTausFinalFilter = 0;
    InclusiveVBFBothTausFinalFilter_pt.clear();
    InclusiveVBFBothTausFinalFilter_eta.clear();
    InclusiveVBFBothTausFinalFilter_phi.clear();
    InclusiveVBFBothTausFinalFilter_energy.clear();

    // VBF Electron
    passVBFElectronBothJetsFinalFilter = 0;
    VBFElectronBothJetsFinalFilter_pt.clear();
    VBFElectronBothJetsFinalFilter_eta.clear();
    VBFElectronBothJetsFinalFilter_phi.clear();
    VBFElectronBothJetsFinalFilter_energy.clear();

    passVBFElectronEleFinalFilter = 0;
    VBFElectronEleFinalFilter_pt.clear();
    VBFElectronEleFinalFilter_eta.clear();
    VBFElectronEleFinalFilter_phi.clear();
    VBFElectronEleFinalFilter_energy.clear();
    
    // VBF Photon
    passVBFPhotonBothJetsFinalFilter = 0;
    VBFPhotonBothJetsFinalFilter_pt.clear();
    VBFPhotonBothJetsFinalFilter_eta.clear();
    VBFPhotonBothJetsFinalFilter_phi.clear();
    VBFPhotonBothJetsFinalFilter_energy.clear();

    passVBFPhotonPhoFinalFilter = 0;
    VBFPhotonPhoFinalFilter_pt.clear();
    VBFPhotonPhoFinalFilter_eta.clear();
    VBFPhotonPhoFinalFilter_phi.clear();
    VBFPhotonPhoFinalFilter_energy.clear();

    // Monitoring
    // SingleMu
    passSingleMuAndLowerMuTauFinalFilter = 0;
    SingleMuAndLowerMuTauFinalFilter_pt.clear();
    SingleMuAndLowerMuTauFinalFilter_eta.clear();
    SingleMuAndLowerMuTauFinalFilter_phi.clear();
    SingleMuAndLowerMuTauFinalFilter_energy.clear();

    // Upper MuTau
    passUpperMuTauL2NN = 0;
    UpperMuTauL2NN_pt.clear();
    UpperMuTauL2NN_eta.clear();
    UpperMuTauL2NN_phi.clear();
    UpperMuTauL2NN_energy.clear();

    passUpperMuTauAndDiTau35FinalFilterMuon = 0;
    UpperMuTauAndDiTau35FinalFilterMuon_pt.clear();
    UpperMuTauAndDiTau35FinalFilterMuon_eta.clear();
    UpperMuTauAndDiTau35FinalFilterMuon_phi.clear();
    UpperMuTauAndDiTau35FinalFilterMuon_energy.clear();

    passUpperMuTauFinalFilterTau = 0;
    UpperMuTauFinalFilterTau_pt.clear();
    UpperMuTauFinalFilterTau_eta.clear();
    UpperMuTauFinalFilterTau_phi.clear();
    UpperMuTauFinalFilterTau_energy.clear();

    passUpperMuTauFinalFilterOverlap = 0;
    UpperMuTauFinalFilterOverlap_pt.clear();
    UpperMuTauFinalFilterOverlap_eta.clear();
    UpperMuTauFinalFilterOverlap_phi.clear();
    UpperMuTauFinalFilterOverlap_energy.clear();

    // Lower MuTau
    passLowerMuTauFinalFilterTau = 0;
    LowerMuTauFinalFilterTau_pt.clear();
    LowerMuTauFinalFilterTau_eta.clear();
    LowerMuTauFinalFilterTau_phi.clear();
    LowerMuTauFinalFilterTau_energy.clear();

    passLowerMuTauFinalFilterOverlap = 0;
    LowerMuTauFinalFilterOverlap_pt.clear();
    LowerMuTauFinalFilterOverlap_eta.clear();
    LowerMuTauFinalFilterOverlap_phi.clear();
    LowerMuTauFinalFilterOverlap_energy.clear();

    // MuTau for DiTau35
    passMuTauForDiTauL2NN = 0;
    MuTauForDiTauL2NN_pt.clear();
    MuTauForDiTauL2NN_eta.clear();
    MuTauForDiTauL2NN_phi.clear();
    MuTauForDiTauL2NN_energy.clear();
    
    passMuTauForDiTauFinalFilterTau = 0;
    MuTauForDiTauFinalFilterTau_pt.clear();
    MuTauForDiTauFinalFilterTau_eta.clear();
    MuTauForDiTauFinalFilterTau_phi.clear();
    MuTauForDiTauFinalFilterTau_energy.clear();

    passMuTauForDiTauFinalFilterOverlap = 0;
    MuTauForDiTauFinalFilterOverlap_pt.clear();
    MuTauForDiTauFinalFilterOverlap_eta.clear();
    MuTauForDiTauFinalFilterOverlap_phi.clear();
    MuTauForDiTauFinalFilterOverlap_energy.clear();

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
        
        // Signal
        // DiTau
        if (filterTag == "hltL2DoubleTauTagNNFilter::MYOTHERHLT"
                      && nObjKeys >= 2) {
          passhltL2DoubleTauTagNNFilter = 1;
          fillFilterKinematics(objectKeys, triggerObjects, nObjKeys,
                               hltL2DoubleTauTagNNFilter_pt,
                               hltL2DoubleTauTagNNFilter_eta,
                               hltL2DoubleTauTagNNFilter_phi,
                               hltL2DoubleTauTagNNFilter_energy);
          continue;
        }

        if (filterTag == "hltHpsDoublePFTau35MediumDitauWPDeepTauL1HLTMatched::MYOTHERHLT"
                      && nObjKeys >= 2) {
          passDiTauFinalFilter = 1;
          fillFilterKinematics(objectKeys, triggerObjects, nObjKeys,
                               DiTauFinalFilter_pt,
                               DiTauFinalFilter_eta,
                               DiTauFinalFilter_phi,
                               DiTauFinalFilter_energy);
          continue;
        }

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

        if (filterTag == "hltHpsSelectedPFTau30LooseETauWPDeepTauL1HLTMatched::MYOTHERHLT"
                      && nObjKeys >= 1) {
          passEleTauFinalFilterTau = 1;
          fillFilterKinematics(objectKeys, triggerObjects, nObjKeys,
                               EleTauFinalFilterTau_pt,
                               EleTauFinalFilterTau_eta,
                               EleTauFinalFilterTau_phi,
                               EleTauFinalFilterTau_energy);
          continue;
        }

        if (filterTag == "hltHpsOverlapFilterIsoEle24WPTightGsfLooseETauWPDeepTauPFTau30::MYOTHERHLT"
                      && nObjKeys >= 1) {
          passEleTauFinalFilterOverlap = 1;
          fillFilterKinematics(objectKeys, triggerObjects, nObjKeys,
                               EleTauFinalFilterOverlap_pt,
                               EleTauFinalFilterOverlap_eta,
                               EleTauFinalFilterOverlap_phi,
                               EleTauFinalFilterOverlap_energy);
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

        // Inclusive VBF
        if (filterTag == "hltMatchedVBFTwoPFJets2CrossCleanedFromDoubleMediumDeepTauDitauWPPFTauHPS20::MYOTHERHLT"
                      && nObjKeys >= 2) {
          passInclusiveVBFBothJetsFinalFilter = 1;
          fillFilterKinematics(objectKeys, triggerObjects, nObjKeys,
                               InclusiveVBFBothJetsFinalFilter_pt,
                               InclusiveVBFBothJetsFinalFilter_eta,
                               InclusiveVBFBothJetsFinalFilter_phi,
                               InclusiveVBFBothJetsFinalFilter_energy);
          continue;
        }        

        if (filterTag == "hltMatchedVBFOnePFJet2CrossCleanedFromDoubleMediumDeepTauDitauWPPFTauHPS20::MYOTHERHLT"
                      && nObjKeys >= 1) {
          passInclusiveVBFLeadingJetFinalFilter = 1;
          fillFilterKinematics(objectKeys, triggerObjects, nObjKeys,
                               InclusiveVBFLeadingJetFinalFilter_pt,
                               InclusiveVBFLeadingJetFinalFilter_eta,
                               InclusiveVBFLeadingJetFinalFilter_phi,
                               InclusiveVBFLeadingJetFinalFilter_energy);
          continue;
        }        

        if (filterTag == "hltHpsDoublePFTau20TrackDeepTauDitauWPAgainstMuon::MYOTHERHLT"
                      && nObjKeys >= 2) {
          passInclusiveVBFBothTausFinalFilter = 1;
          fillFilterKinematics(objectKeys, triggerObjects, nObjKeys,
                               InclusiveVBFBothTausFinalFilter_pt,
                               InclusiveVBFBothTausFinalFilter_eta,
                               InclusiveVBFBothTausFinalFilter_phi,
                               InclusiveVBFBothTausFinalFilter_energy);
          continue;
        }        

        // VBF Electron
        if (filterTag == "hltEle12WPLoose1GsfTrackIsoFilter::MYOTHERHLT"
                      && nObjKeys >= 1) {
          passVBFElectronEleFinalFilter = 1;
          fillFilterKinematics(objectKeys, triggerObjects, nObjKeys,
                               VBFElectronEleFinalFilter_pt,
                               VBFElectronEleFinalFilter_eta,
                               VBFElectronEleFinalFilter_phi,
                               VBFElectronEleFinalFilter_energy);
          continue;
        }        

        if (filterTag == "hltMatchedVBFTwoPFJets2CrossCleanedFromEle12WPLoose1GsfTrackIsoFilter::MYOTHERHLT"
                      && nObjKeys >= 2) {
          passVBFElectronBothJetsFinalFilter = 1;
          fillFilterKinematics(objectKeys, triggerObjects, nObjKeys,
                               VBFElectronBothJetsFinalFilter_pt,
                               VBFElectronBothJetsFinalFilter_eta,
                               VBFElectronBothJetsFinalFilter_phi,
                               VBFElectronBothJetsFinalFilter_energy);
          continue;
        }

        // VBF Photon
        if (filterTag == "hltVBFTwoPFJetsForVBFPhotonTrigger::MYOTHERHLT"
                      && nObjKeys >= 2) {
          passVBFPhotonBothJetsFinalFilter = 1;
          fillFilterKinematics(objectKeys, triggerObjects, nObjKeys,
                               VBFPhotonBothJetsFinalFilter_pt,
                               VBFPhotonBothJetsFinalFilter_eta,
                               VBFPhotonBothJetsFinalFilter_phi,
                               VBFPhotonBothJetsFinalFilter_energy);
          continue;
        }

        if (filterTag == "hltEG12L1VBFIsoEGOR15HEFilter::MYOTHERHLT"
                      && nObjKeys >= 1) {
          passVBFPhotonPhoFinalFilter = 1;
          fillFilterKinematics(objectKeys, triggerObjects, nObjKeys,
                               VBFPhotonPhoFinalFilter_pt,
                               VBFPhotonPhoFinalFilter_eta,
                               VBFPhotonPhoFinalFilter_phi,
                               VBFPhotonPhoFinalFilter_energy);
          continue;
        }

        // Monitoring
        // SingleMu
        if (filterTag == "hltL3crIsoL1sSingleMu22erL1f0L2f10QL3f24QL3trkIsoFiltered0p08::MYOTHERHLT"
                      && nObjKeys >= 1) {
          passSingleMuAndLowerMuTauFinalFilter = 1;
          fillFilterKinematics(objectKeys, triggerObjects, nObjKeys,
                               SingleMuAndLowerMuTauFinalFilter_pt,
                               SingleMuAndLowerMuTauFinalFilter_eta,
                               SingleMuAndLowerMuTauFinalFilter_phi,
                               SingleMuAndLowerMuTauFinalFilter_energy);
          continue;
        }

        // Upper MuTau
        if (filterTag == "hltL2TauTagNNFilterMuXXerIsoTauYYForVBFTauTau::MYOTHERHLT"
                      && nObjKeys >= 1) {
          passUpperMuTauL2NN = 1;
          fillFilterKinematics(objectKeys, triggerObjects, nObjKeys,
                               UpperMuTauL2NN_pt,
                               UpperMuTauL2NN_eta,
                               UpperMuTauL2NN_phi,
                               UpperMuTauL2NN_energy);
          continue;
        }

        if (filterTag == "hltL3crIsoL1sBigOrMuXXerIsoTauYYerL1f0L2f10QL3f24QL3trkIsoFiltered0p08::MYOTHERHLT"
                      && nObjKeys >= 1) {
          passUpperMuTauAndDiTau35FinalFilterMuon = 1;
          fillFilterKinematics(objectKeys, triggerObjects, nObjKeys,
                               UpperMuTauAndDiTau35FinalFilterMuon_pt,
                               UpperMuTauAndDiTau35FinalFilterMuon_eta,
                               UpperMuTauAndDiTau35FinalFilterMuon_phi,
                               UpperMuTauAndDiTau35FinalFilterMuon_energy);
          continue;
        }

        if (filterTag == "hltHpsSelectedPFTau45MediumDitauWPDeepTauL1HLTBigOrMuXXerIsoTauYYerMatchedForVBFIsoTau::MYOTHERHLT"
                      && nObjKeys >= 1) {
          passUpperMuTauFinalFilterTau = 1;
          fillFilterKinematics(objectKeys, triggerObjects, nObjKeys,
                               UpperMuTauFinalFilterTau_pt,
                               UpperMuTauFinalFilterTau_eta,
                               UpperMuTauFinalFilterTau_phi,
                               UpperMuTauFinalFilterTau_energy);
          continue;
        }

        if (filterTag == "hltHpsOverlapFilterIsoMu24MediumDitauWPDeepTauPFTau45MonitoringForVBFIsoTau::MYOTHERHLT"
                      && nObjKeys >= 1) {
          passUpperMuTauFinalFilterOverlap = 1;
          fillFilterKinematics(objectKeys, triggerObjects, nObjKeys,
                               UpperMuTauFinalFilterOverlap_pt,
                               UpperMuTauFinalFilterOverlap_eta,
                               UpperMuTauFinalFilterOverlap_phi,
                               UpperMuTauFinalFilterOverlap_energy);
          continue;
        }
    
        // Lower MuTau
        if (filterTag == "hltHpsSinglePFTau20MediumDitauWPDeepTauNoMatchForVBFIsoTau::MYOTHERHLT"
                      && nObjKeys >= 1) {
          passLowerMuTauFinalFilterTau = 1;
          fillFilterKinematics(objectKeys, triggerObjects, nObjKeys,
                               LowerMuTauFinalFilterTau_pt,
                               LowerMuTauFinalFilterTau_eta,
                               LowerMuTauFinalFilterTau_phi,
                               LowerMuTauFinalFilterTau_energy);
          continue;
        }

        if (filterTag == "hltHpsOverlapFilterIsoMu24MediumDeepTauPFTau20::MYOTHERHLT"
                      && nObjKeys >= 1) {
          passLowerMuTauFinalFilterOverlap = 1;
          fillFilterKinematics(objectKeys, triggerObjects, nObjKeys,
                               LowerMuTauFinalFilterOverlap_pt,
                               LowerMuTauFinalFilterOverlap_eta,
                               LowerMuTauFinalFilterOverlap_phi,
                               LowerMuTauFinalFilterOverlap_energy);
          continue;
        }
     
        // MuTau for DiTau35
        if (filterTag == "hltL2TauTagNNFilterMuXXerIsoTauYY::MYOTHERHLT"
                      && nObjKeys >= 1) {
          passMuTauForDiTauL2NN = 1;
          fillFilterKinematics(objectKeys, triggerObjects, nObjKeys,
                               MuTauForDiTauL2NN_pt,
                               MuTauForDiTauL2NN_eta,
                               MuTauForDiTauL2NN_phi,
                               MuTauForDiTauL2NN_energy);
          continue;
        }

        if (filterTag == "hltHpsSelectedPFTau35MediumDitauWPDeepTauL1HLTBigOrMuXXerIsoTauYYerMatched::MYOTHERHLT"
                      && nObjKeys >= 1) {
          passMuTauForDiTauFinalFilterTau = 1;
          fillFilterKinematics(objectKeys, triggerObjects, nObjKeys,
                               MuTauForDiTauFinalFilterTau_pt,
                               MuTauForDiTauFinalFilterTau_eta,
                               MuTauForDiTauFinalFilterTau_phi,
                               MuTauForDiTauFinalFilterTau_energy);
          continue;
        }

        if (filterTag == "hltHpsOverlapFilterIsoMu24MediumDitauWPDeepTauPFTau35Monitoring::MYOTHERHLT"
                      && nObjKeys >= 1) {
          passMuTauForDiTauFinalFilterOverlap = 1;
          fillFilterKinematics(objectKeys, triggerObjects, nObjKeys,
                               MuTauForDiTauFinalFilterOverlap_pt,
                               MuTauForDiTauFinalFilterOverlap_eta,
                               MuTauForDiTauFinalFilterOverlap_phi,
                               MuTauForDiTauFinalFilterOverlap_energy);
          continue;
        }

    } // end loop over nfilters
} // end function
