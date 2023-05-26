#include "VBFIsoTauHLT/NtupleMaker/plugins/NtupleMaker.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"

using namespace std;


float 	ptL1_;
float 	etaL1_;
float 	phiL1_;
float 	energyL1_;

int	nEvents;

int passhltL1VBFElectronTightIso_RealHLT;
vector<float> hltL1VBFElectronTightIso_RealHLT_ePt;
vector<float> hltL1VBFElectronTightIso_RealHLT_eEta;
vector<float> hltL1VBFElectronTightIso_RealHLT_ePhi;
vector<float> hltL1VBFElectronTightIso_RealHLT_eEnergy;
vector<float> hltL1VBFElectronTightIso_RealHLT_jPt;
vector<float> hltL1VBFElectronTightIso_RealHLT_jEta;
vector<float> hltL1VBFElectronTightIso_RealHLT_jPhi;
vector<float> hltL1VBFElectronTightIso_RealHLT_jEnergy;

int passhltL1VBFElectronTightIso;
vector<float> hltL1VBFElectronTightIso_ePt;
vector<float> hltL1VBFElectronTightIso_eEta;
vector<float> hltL1VBFElectronTightIso_ePhi;
vector<float> hltL1VBFElectronTightIso_eEnergy;
vector<float> hltL1VBFElectronTightIso_jPt;
vector<float> hltL1VBFElectronTightIso_jEta;
vector<float> hltL1VBFElectronTightIso_jPhi;
vector<float> hltL1VBFElectronTightIso_jEnergy;

int passhltL1VBFElectronLooseIso;
vector<float> hltL1VBFElectronLooseIso_ePt;
vector<float> hltL1VBFElectronLooseIso_eEta;
vector<float> hltL1VBFElectronLooseIso_ePhi;
vector<float> hltL1VBFElectronLooseIso_eEnergy;
vector<float> hltL1VBFElectronLooseIso_jPt;
vector<float> hltL1VBFElectronLooseIso_jEta;
vector<float> hltL1VBFElectronLooseIso_jPhi;
vector<float> hltL1VBFElectronLooseIso_jEnergy;

int passhltL1VBFElectronNoIso;
vector<float> hltL1VBFElectronNoIso_ePt;
vector<float> hltL1VBFElectronNoIso_eEta;
vector<float> hltL1VBFElectronNoIso_ePhi;
vector<float> hltL1VBFElectronNoIso_eEnergy;
vector<float> hltL1VBFElectronNoIso_jPt;
vector<float> hltL1VBFElectronNoIso_jEta;
vector<float> hltL1VBFElectronNoIso_jPhi;
vector<float> hltL1VBFElectronNoIso_jEnergy;


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

int passhltL1sSingleEG26;
vector<float> hltL1sSingleEG26_pt;
vector<float> hltL1sSingleEG26_eta;
vector<float> hltL1sSingleEG26_phi;
vector<float> hltL1sSingleEG26_energy;

int passhltL1sSingleEGor;
vector<float> hltL1sSingleEGor_pt;
vector<float> hltL1sSingleEGor_eta;
vector<float> hltL1sSingleEGor_phi;
vector<float> hltL1sSingleEGor_energy;

int passhltPassthroughL1EGTightIso;
vector<float> hltPassthroughL1EGTightIso_pt;
vector<float> hltPassthroughL1EGTightIso_eta;
vector<float> hltPassthroughL1EGTightIso_phi;
vector<float> hltPassthroughL1EGTightIso_energy;

int passhltPassthroughL1EGLooseIso;
vector<float> hltPassthroughL1EGLooseIso_pt;
vector<float> hltPassthroughL1EGLooseIso_eta;
vector<float> hltPassthroughL1EGLooseIso_phi;
vector<float> hltPassthroughL1EGLooseIso_energy;

int passhltPassthroughL1EGNoIso;
vector<float> hltPassthroughL1EGNoIso_pt;
vector<float> hltPassthroughL1EGNoIso_eta;
vector<float> hltPassthroughL1EGNoIso_phi;
vector<float> hltPassthroughL1EGNoIso_energy;

void NtupleMaker::branchesL1sFromHLT(TTree* tree){

    tree->Branch("nEvents", &nEvents);

    tree->Branch("passhltL1VBFElectronTightIso_RealHLT", &passhltL1VBFElectronTightIso_RealHLT);
    tree->Branch("hltL1VBFElectronTightIso_RealHLT_ePt", &hltL1VBFElectronTightIso_RealHLT_ePt);
    tree->Branch("hltL1VBFElectronTightIso_RealHLT_eEta", &hltL1VBFElectronTightIso_RealHLT_eEta);
    tree->Branch("hltL1VBFElectronTightIso_RealHLT_ePhi", &hltL1VBFElectronTightIso_RealHLT_ePhi);
    tree->Branch("hltL1VBFElectronTightIso_RealHLT_eEnergy", &hltL1VBFElectronTightIso_RealHLT_eEnergy);
    tree->Branch("hltL1VBFElectronTightIso_RealHLT_jPt", &hltL1VBFElectronTightIso_RealHLT_jPt);
    tree->Branch("hltL1VBFElectronTightIso_RealHLT_jEta", &hltL1VBFElectronTightIso_RealHLT_jEta);
    tree->Branch("hltL1VBFElectronTightIso_RealHLT_jPhi", &hltL1VBFElectronTightIso_RealHLT_jPhi);
    tree->Branch("hltL1VBFElectronTightIso_RealHLT_jEnergy", &hltL1VBFElectronTightIso_RealHLT_jEnergy);

    tree->Branch("passhltL1VBFElectronTightIso", &passhltL1VBFElectronTightIso);
    tree->Branch("hltL1VBFElectronTightIso_ePt", &hltL1VBFElectronTightIso_ePt);
    tree->Branch("hltL1VBFElectronTightIso_eEta", &hltL1VBFElectronTightIso_eEta);
    tree->Branch("hltL1VBFElectronTightIso_ePhi", &hltL1VBFElectronTightIso_ePhi);
    tree->Branch("hltL1VBFElectronTightIso_eEnergy", &hltL1VBFElectronTightIso_eEnergy);
    tree->Branch("hltL1VBFElectronTightIso_jPt", &hltL1VBFElectronTightIso_jPt);
    tree->Branch("hltL1VBFElectronTightIso_jEta", &hltL1VBFElectronTightIso_jEta);
    tree->Branch("hltL1VBFElectronTightIso_jPhi", &hltL1VBFElectronTightIso_jPhi);
    tree->Branch("hltL1VBFElectronTightIso_jEnergy", &hltL1VBFElectronTightIso_jEnergy);

    tree->Branch("passhltL1VBFElectronLooseIso", &passhltL1VBFElectronLooseIso);
    tree->Branch("hltL1VBFElectronLooseIso_ePt", &hltL1VBFElectronLooseIso_ePt);
    tree->Branch("hltL1VBFElectronLooseIso_eEta", &hltL1VBFElectronLooseIso_eEta);
    tree->Branch("hltL1VBFElectronLooseIso_ePhi", &hltL1VBFElectronLooseIso_ePhi);
    tree->Branch("hltL1VBFElectronLooseIso_eEnergy", &hltL1VBFElectronLooseIso_eEnergy);
    tree->Branch("hltL1VBFElectronLooseIso_jPt", &hltL1VBFElectronLooseIso_jPt);
    tree->Branch("hltL1VBFElectronLooseIso_jEta", &hltL1VBFElectronLooseIso_jEta);
    tree->Branch("hltL1VBFElectronLooseIso_jPhi", &hltL1VBFElectronLooseIso_jPhi);
    tree->Branch("hltL1VBFElectronLooseIso_jEnergy", &hltL1VBFElectronLooseIso_jEnergy);

    tree->Branch("passhltL1VBFElectronNoIso", &passhltL1VBFElectronNoIso);
    tree->Branch("hltL1VBFElectronNoIso_ePt", &hltL1VBFElectronNoIso_ePt);
    tree->Branch("hltL1VBFElectronNoIso_eEta", &hltL1VBFElectronNoIso_eEta);
    tree->Branch("hltL1VBFElectronNoIso_ePhi", &hltL1VBFElectronNoIso_ePhi);
    tree->Branch("hltL1VBFElectronNoIso_eEnergy", &hltL1VBFElectronNoIso_eEnergy);
    tree->Branch("hltL1VBFElectronNoIso_jPt", &hltL1VBFElectronNoIso_jPt);
    tree->Branch("hltL1VBFElectronNoIso_jEta", &hltL1VBFElectronNoIso_jEta);
    tree->Branch("hltL1VBFElectronNoIso_jPhi", &hltL1VBFElectronNoIso_jPhi);
    tree->Branch("hltL1VBFElectronNoIso_jEnergy", &hltL1VBFElectronNoIso_jEnergy);

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

    tree->Branch("passhltL1sSingleEG26", &passhltL1sSingleEG26);
    tree->Branch("hltL1sSingleEG26_pt", &hltL1sSingleEG26_pt);
    tree->Branch("hltL1sSingleEG26_eta", &hltL1sSingleEG26_eta);
    tree->Branch("hltL1sSingleEG26_phi", &hltL1sSingleEG26_phi);
    tree->Branch("hltL1sSingleEG26_energy", &hltL1sSingleEG26_energy);

    tree->Branch("passhltL1sSingleEGor", &passhltL1sSingleEGor);
    tree->Branch("hltL1sSingleEGor_pt", &hltL1sSingleEGor_pt);
    tree->Branch("hltL1sSingleEGor_eta", &hltL1sSingleEGor_eta);
    tree->Branch("hltL1sSingleEGor_phi", &hltL1sSingleEGor_phi);
    tree->Branch("hltL1sSingleEGor_energy", &hltL1sSingleEGor_energy);

    tree->Branch("passhltPassthroughL1EGTightIso", &passhltPassthroughL1EGTightIso);
    tree->Branch("hltPassthroughL1EGTightIso_pt", &hltPassthroughL1EGTightIso_pt);
    tree->Branch("hltPassthroughL1EGTightIso_eta", &hltPassthroughL1EGTightIso_eta);
    tree->Branch("hltPassthroughL1EGTightIso_phi", &hltPassthroughL1EGTightIso_phi);
    tree->Branch("hltPassthroughL1EGTightIso_energy", &hltPassthroughL1EGTightIso_energy);

    tree->Branch("passhltPassthroughL1EGLooseIso", &passhltPassthroughL1EGLooseIso);
    tree->Branch("hltPassthroughL1EGLooseIso_pt", &hltPassthroughL1EGLooseIso_pt);
    tree->Branch("hltPassthroughL1EGLooseIso_eta", &hltPassthroughL1EGLooseIso_eta);
    tree->Branch("hltPassthroughL1EGLooseIso_phi", &hltPassthroughL1EGLooseIso_phi);
    tree->Branch("hltPassthroughL1EGLooseIso_energy", &hltPassthroughL1EGLooseIso_energy);

    tree->Branch("passhltPassthroughL1EGNoIso", &passhltPassthroughL1EGNoIso);
    tree->Branch("hltPassthroughL1EGNoIso_pt", &hltPassthroughL1EGNoIso_pt);
    tree->Branch("hltPassthroughL1EGNoIso_eta", &hltPassthroughL1EGNoIso_eta);
    tree->Branch("hltPassthroughL1EGNoIso_phi", &hltPassthroughL1EGNoIso_phi);
    tree->Branch("hltPassthroughL1EGNoIso_energy", &hltPassthroughL1EGNoIso_energy);

}

void NtupleMaker::fillL1sFromHLT(const edm::Event& iEvent){

    using namespace edm;
    // "vids" and available RefVec classes defined here
    // https://github.com/cms-sw/cmssw/blob/8b101cb0f00c4a961bc4a6d49512ef0335486f40/DataFormats/HLTReco/interface/TriggerRefsCollections.h


    // spliting objects at L1 using TriggerEventWithRefs
    edm::Handle<trigger::TriggerEventWithRefs> triggerEventWithRefsHandle_;
    iEvent.getByToken(triggerEventWithRefsToken_, triggerEventWithRefsHandle_);
    const unsigned int filterIndex(triggerEventWithRefsHandle_->filterIndex(InputTag("hltL1VBFDiJetIsoTau", "", "MYOTHERHLT")));


    //making jet object and filling vector
    l1t::JetVectorRef jetCandRefVec;
    trigger::Vids jvids;
    triggerEventWithRefsHandle_->getObjects(filterIndex, jvids, jetCandRefVec);

    hltL1VBFDiJetIsoTau_nJets.clear();
    hltL1VBFDiJetIsoTau_jetPt.clear();
    hltL1VBFDiJetIsoTau_jetEta.clear();
    hltL1VBFDiJetIsoTau_jetPhi.clear();
    hltL1VBFDiJetIsoTau_jetEnergy.clear();
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


    //making tau object and filling vector
    l1t::TauVectorRef tauCandRefVec;
    trigger::Vids tvids;
    triggerEventWithRefsHandle_->getObjects(filterIndex, tvids, tauCandRefVec);

    hltL1VBFDiJetIsoTau_nTaus.clear();
    hltL1VBFDiJetIsoTau_tauPt.clear();
    hltL1VBFDiJetIsoTau_tauEta.clear();
    hltL1VBFDiJetIsoTau_tauPhi.clear();
    hltL1VBFDiJetIsoTau_tauEnergy.clear();
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

    hltL1sMu22er2p1IsoTau28er2p1_muPt.clear();
    hltL1sMu22er2p1IsoTau28er2p1_muEta.clear();
    hltL1sMu22er2p1IsoTau28er2p1_muPhi.clear();
    hltL1sMu22er2p1IsoTau28er2p1_muEnergy.clear();
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

    hltL1sMu22er2p1IsoTau28er2p1_tauPt.clear();
    hltL1sMu22er2p1IsoTau28er2p1_tauEta.clear();
    hltL1sMu22er2p1IsoTau28er2p1_tauPhi.clear();
    hltL1sMu22er2p1IsoTau28er2p1_tauEnergy.clear();
    const unsigned int tUpperVidsSize(tUpperVids.size());
    if (tUpperVidsSize > 0) {
      for (unsigned int i = 0; i != tUpperVidsSize; ++i) {
        hltL1sMu22er2p1IsoTau28er2p1_tauPt.push_back(tauUpperControlCandRefVec[i]->pt());
        hltL1sMu22er2p1IsoTau28er2p1_tauEta.push_back(tauUpperControlCandRefVec[i]->eta());
        hltL1sMu22er2p1IsoTau28er2p1_tauPhi.push_back(tauUpperControlCandRefVec[i]->phi());
        hltL1sMu22er2p1IsoTau28er2p1_tauEnergy.push_back(tauUpperControlCandRefVec[i]->energy());
      }
    }

    //////
    const unsigned int VBFElectronRealL1Filter(triggerEventWithRefsHandle_->filterIndex(InputTag("hltL1VBFIsoEG", "", "MYOTHERHLT")));

    l1t::EGammaVectorRef electronCandRefVec;
    trigger::Vids eVids_L1VBFIsoEGRealHLT;
    triggerEventWithRefsHandle_->getObjects(VBFElectronRealL1Filter, eVids_L1VBFIsoEGRealHLT, electronCandRefVec);

    hltL1VBFElectronTightIso_RealHLT_ePt.clear();
    hltL1VBFElectronTightIso_RealHLT_eEta.clear();
    hltL1VBFElectronTightIso_RealHLT_ePhi.clear();
    hltL1VBFElectronTightIso_RealHLT_eEnergy.clear();
    const unsigned int nElectrons_RealHLT(eVids_L1VBFIsoEGRealHLT.size());
    if (nElectrons_RealHLT > 0) {
      for (unsigned int i = 0; i != nElectrons_RealHLT; ++i) {
        hltL1VBFElectronTightIso_RealHLT_ePt.push_back(electronCandRefVec[i]->pt());
        hltL1VBFElectronTightIso_RealHLT_eEta.push_back(electronCandRefVec[i]->eta());
        hltL1VBFElectronTightIso_RealHLT_ePhi.push_back(electronCandRefVec[i]->phi());
        hltL1VBFElectronTightIso_RealHLT_eEnergy.push_back(electronCandRefVec[i]->energy());
      }
    }

    l1t::JetVectorRef VBFElectronJetRefVec;
    trigger::Vids ejVids_L1VBFIsoEGRealHLT;
    triggerEventWithRefsHandle_->getObjects(VBFElectronRealL1Filter, ejVids_L1VBFIsoEGRealHLT, VBFElectronJetRefVec);

    hltL1VBFElectronTightIso_RealHLT_jPt.clear();
    hltL1VBFElectronTightIso_RealHLT_jEta.clear();
    hltL1VBFElectronTightIso_RealHLT_jPhi.clear();
    hltL1VBFElectronTightIso_RealHLT_jEnergy.clear();
    const unsigned int nVBFElectronJets_RealHLT(ejVids_L1VBFIsoEGRealHLT.size());
    if (nVBFElectronJets_RealHLT > 0) {
      for (unsigned int i = 0; i != nVBFElectronJets_RealHLT; ++ i) {
        hltL1VBFElectronTightIso_RealHLT_jPt.push_back(VBFElectronJetRefVec[i]->pt());
        hltL1VBFElectronTightIso_RealHLT_jEta.push_back(VBFElectronJetRefVec[i]->eta());
        hltL1VBFElectronTightIso_RealHLT_jPhi.push_back(VBFElectronJetRefVec[i]->phi());
        hltL1VBFElectronTightIso_RealHLT_jEnergy.push_back(VBFElectronJetRefVec[i]->energy());
      }
    }

    // Also for VBF + Electron
    //const unsigned int VBFElectronL1Filter(triggerEventWithRefsHandle_->filterIndex(InputTag("hltL1VBFElectronTightIso", "", "MYOTHERHLT")));
    const unsigned int VBFElectronL1TightIsoFilter(triggerEventWithRefsHandle_->filterIndex(InputTag("hltPassthroughL1VBFEGTightIso", "", "MYOTHERHLT")));

    l1t::EGammaVectorRef electronCandRefVec_TightIsoDummy;
    trigger::Vids eVids_TightIsoDummy;
    triggerEventWithRefsHandle_->getObjects(VBFElectronL1TightIsoFilter, eVids_TightIsoDummy, electronCandRefVec_TightIsoDummy);

    hltL1VBFElectronTightIso_ePt.clear();
    hltL1VBFElectronTightIso_eEta.clear();
    hltL1VBFElectronTightIso_ePhi.clear();
    hltL1VBFElectronTightIso_eEnergy.clear();
    const unsigned int nElectrons(eVids_TightIsoDummy.size());
    if (nElectrons > 0) {
      for (unsigned int i = 0; i != nElectrons; ++i) {
        hltL1VBFElectronTightIso_ePt.push_back(electronCandRefVec_TightIsoDummy[i]->pt());
        hltL1VBFElectronTightIso_eEta.push_back(electronCandRefVec_TightIsoDummy[i]->eta());
        hltL1VBFElectronTightIso_ePhi.push_back(electronCandRefVec_TightIsoDummy[i]->phi());
        hltL1VBFElectronTightIso_eEnergy.push_back(electronCandRefVec_TightIsoDummy[i]->energy());
      }
    }

    l1t::JetVectorRef VBFElectronJetRefVec_TightIsoDummy;
    trigger::Vids ejVids_TightIsoDummy;
    triggerEventWithRefsHandle_->getObjects(VBFElectronL1TightIsoFilter, ejVids_TightIsoDummy, VBFElectronJetRefVec_TightIsoDummy);

    hltL1VBFElectronTightIso_jPt.clear();
    hltL1VBFElectronTightIso_jEta.clear();
    hltL1VBFElectronTightIso_jPhi.clear();
    hltL1VBFElectronTightIso_jEnergy.clear();
    const unsigned int nVBFElectronJets(ejVids_TightIsoDummy.size());
    if (nVBFElectronJets > 0) {
      for (unsigned int i = 0; i != nVBFElectronJets; ++ i) {
        hltL1VBFElectronTightIso_jPt.push_back(VBFElectronJetRefVec_TightIsoDummy[i]->pt());
        hltL1VBFElectronTightIso_jEta.push_back(VBFElectronJetRefVec_TightIsoDummy[i]->eta());
        hltL1VBFElectronTightIso_jPhi.push_back(VBFElectronJetRefVec_TightIsoDummy[i]->phi());
        hltL1VBFElectronTightIso_jEnergy.push_back(VBFElectronJetRefVec_TightIsoDummy[i]->energy());
      }
    }

    // again for VBF + Loose Electron
    const unsigned int VBFElectronL1LooseFilter(triggerEventWithRefsHandle_->filterIndex(InputTag("hltPassthroughL1VBFEGLooseIso", "", "MYOTHERHLT")));

    l1t::EGammaVectorRef looseElectronCandRefVec;
    trigger::Vids leVids;
    triggerEventWithRefsHandle_->getObjects(VBFElectronL1LooseFilter, leVids, looseElectronCandRefVec);

    hltL1VBFElectronLooseIso_ePt.clear();
    hltL1VBFElectronLooseIso_eEta.clear();
    hltL1VBFElectronLooseIso_ePhi.clear();
    hltL1VBFElectronLooseIso_eEnergy.clear();
    const unsigned int nLooseElectrons(leVids.size());
    if (nLooseElectrons > 0) {
      for (unsigned int i = 0; i != nLooseElectrons; ++i) {
        hltL1VBFElectronLooseIso_ePt.push_back(looseElectronCandRefVec[i]->pt());
        hltL1VBFElectronLooseIso_eEta.push_back(looseElectronCandRefVec[i]->eta());
        hltL1VBFElectronLooseIso_ePhi.push_back(looseElectronCandRefVec[i]->phi());
        hltL1VBFElectronLooseIso_eEnergy.push_back(looseElectronCandRefVec[i]->energy());
      }
    }

    l1t::JetVectorRef VBFLooseElectronJetRefVec;
    trigger::Vids lejVids;
    triggerEventWithRefsHandle_->getObjects(VBFElectronL1LooseFilter, lejVids, VBFLooseElectronJetRefVec);

    hltL1VBFElectronLooseIso_jPt.clear();
    hltL1VBFElectronLooseIso_jEta.clear();
    hltL1VBFElectronLooseIso_jPhi.clear();
    hltL1VBFElectronLooseIso_jEnergy.clear();
    const unsigned int nVBFLooseElectronJets(lejVids.size());
    if (nVBFLooseElectronJets > 0) {
      for (unsigned int i = 0; i != nVBFLooseElectronJets; ++ i) {
        hltL1VBFElectronLooseIso_jPt.push_back(VBFLooseElectronJetRefVec[i]->pt());
        hltL1VBFElectronLooseIso_jEta.push_back(VBFLooseElectronJetRefVec[i]->eta());
        hltL1VBFElectronLooseIso_jPhi.push_back(VBFLooseElectronJetRefVec[i]->phi());
        hltL1VBFElectronLooseIso_jEnergy.push_back(VBFLooseElectronJetRefVec[i]->energy());
      }
    }

    // again for VBF + NoIso Electron
    const unsigned int VBFElectronL1NoIsoFilter(triggerEventWithRefsHandle_->filterIndex(InputTag("hltPassthroughL1VBFEGNoIso", "", "MYOTHERHLT")));

    l1t::EGammaVectorRef noisoElectronCandRefVec;
    trigger::Vids nieVids;
    triggerEventWithRefsHandle_->getObjects(VBFElectronL1NoIsoFilter, nieVids, noisoElectronCandRefVec);

    hltL1VBFElectronNoIso_ePt.clear();
    hltL1VBFElectronNoIso_eEta.clear();
    hltL1VBFElectronNoIso_ePhi.clear();
    hltL1VBFElectronNoIso_eEnergy.clear();
    const unsigned int nNoIsoElectrons(nieVids.size());
    if (nNoIsoElectrons > 0) {
      for (unsigned int i = 0; i != nNoIsoElectrons; ++i) {
        hltL1VBFElectronNoIso_ePt.push_back(noisoElectronCandRefVec[i]->pt());
        hltL1VBFElectronNoIso_eEta.push_back(noisoElectronCandRefVec[i]->eta());
        hltL1VBFElectronNoIso_ePhi.push_back(noisoElectronCandRefVec[i]->phi());
        hltL1VBFElectronNoIso_eEnergy.push_back(noisoElectronCandRefVec[i]->energy());
      }
    }

    l1t::JetVectorRef VBFNoIsoElectronJetRefVec;
    trigger::Vids niejVids;
    triggerEventWithRefsHandle_->getObjects(VBFElectronL1NoIsoFilter, niejVids, VBFNoIsoElectronJetRefVec);

    hltL1VBFElectronNoIso_jPt.clear();
    hltL1VBFElectronNoIso_jEta.clear();
    hltL1VBFElectronNoIso_jPhi.clear();
    hltL1VBFElectronNoIso_jEnergy.clear();
    const unsigned int nVBFNoIsoElectronJets(niejVids.size());
    if (nVBFNoIsoElectronJets > 0) {
      for (unsigned int i = 0; i != nVBFNoIsoElectronJets; ++ i) {
        hltL1VBFElectronNoIso_jPt.push_back(VBFNoIsoElectronJetRefVec[i]->pt());
        hltL1VBFElectronNoIso_jEta.push_back(VBFNoIsoElectronJetRefVec[i]->eta());
        hltL1VBFElectronNoIso_jPhi.push_back(VBFNoIsoElectronJetRefVec[i]->phi());
        hltL1VBFElectronNoIso_jEnergy.push_back(VBFNoIsoElectronJetRefVec[i]->energy());
      }
    }


    nEvents = 0;

    passhltL1VBFElectronTightIso_RealHLT = 0;
    passhltL1VBFElectronTightIso = 0;
    passhltL1VBFElectronLooseIso = 0;
    passhltL1VBFElectronNoIso = 0;

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

    passhltL1sSingleMu22 = 0;
    hltL1sSingleMu22_pt.clear();
    hltL1sSingleMu22_eta.clear();
    hltL1sSingleMu22_phi.clear();
    hltL1sSingleMu22_energy.clear();

    passhltL1sMu22er2p1IsoTau28er2p1 = 0;

    passhltL1sSingleEG26 = 0;
    hltL1sSingleEG26_pt.clear();
    hltL1sSingleEG26_eta.clear();
    hltL1sSingleEG26_phi.clear();
    hltL1sSingleEG26_energy.clear();
 
    passhltL1sSingleEGor = 0;
    hltL1sSingleEGor_pt.clear();
    hltL1sSingleEGor_eta.clear();
    hltL1sSingleEGor_phi.clear();
    hltL1sSingleEGor_energy.clear();

    passhltPassthroughL1EGTightIso = 0;
    hltPassthroughL1EGTightIso_pt.clear();
    hltPassthroughL1EGTightIso_eta.clear();
    hltPassthroughL1EGTightIso_phi.clear();
    hltPassthroughL1EGTightIso_energy.clear();

    passhltPassthroughL1EGLooseIso = 0;
    hltPassthroughL1EGLooseIso_pt.clear();
    hltPassthroughL1EGLooseIso_eta.clear();
    hltPassthroughL1EGLooseIso_phi.clear();
    hltPassthroughL1EGLooseIso_energy.clear();

    passhltPassthroughL1EGNoIso = 0;
    hltPassthroughL1EGNoIso_pt.clear();
    hltPassthroughL1EGNoIso_eta.clear();
    hltPassthroughL1EGNoIso_phi.clear();
    hltPassthroughL1EGNoIso_energy.clear();

    // getting trigger event per this page
    // https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideHLTAnalysis
    edm::Handle<trigger::TriggerEvent> triggerEventL1; // this code should be with the filters
    iEvent.getByToken(triggerEventToken_, triggerEventL1); // same

    // make strings to identify filter names
    const trigger::size_type nFilters(triggerEventL1->sizeFilters());
    std::string hltL1sDoubleTauBigOR_Tag = "hltL1sDoubleTauBigOR::MYOTHERHLT";
    std::string hltL1sMu22er2p1IsoTau28er2p1_Tag = "hltL1sMu22er2p1IsoTau28er2p1::MYOTHERHLT";
    //std::string hltL1VBFElectronTightIso_Tag = "hltL1VBFElectronTightIso::MYOTHERHLT";
    //std::string hltL1VBFElectronLooseIso_Tag = "hltL1VBFElectronLooseIso::MYOTHERHLT";
    //std::string hltL1VBFElectronNoIso_Tag = "hltL1VBFElectronNoIso::MYOTHERHLT";
    std::string hltL1VBFElectronTightIso_RealHLT_Tag = "hltL1VBFIsoEG::MYOTHERHLT";

    std::string hltL1VBFElectronTightIso_Tag = "hltPassthroughL1VBFEGTightIso::MYOTHERHLT";
    std::string hltL1VBFElectronLooseIso_Tag = "hltPassthroughL1VBFEGLooseIso::MYOTHERHLT";
    std::string hltL1VBFElectronNoIso_Tag = "hltPassthroughL1VBFEGNoIso::MYOTHERHLT";

    std::string hltL1VBFDiJetOR_Tag = "hltL1VBFDiJetOR::MYOTHERHLT";
    std::string hltL1VBFDiJetIsoTau_Tag = "hltL1VBFDiJetIsoTau::MYOTHERHLT";	  
    std::string hltL1sSingleMu22_Tag = "hltL1sSingleMu22::MYOTHERHLT";
    std::string hltL1sSingleEG26_Tag = "hltL1sSingleEG26::MYOTHERHLT";
    std::string hltL1sSingleEGor_Tag = "hltL1sSingleEGor::MYOTHERHLT";

    std::string hltPassthroughL1EGTightIso_Tag = "hltPassthroughL1EGTightIso::MYOTHERHLT";
    std::string hltPassthroughL1EGLooseIso_Tag = "hltPassthroughL1EGLooseIso::MYOTHERHLT";
    std::string hltPassthroughL1EGNoIso_Tag = "hltPassthroughL1EGNoIso::MYOTHERHLT";


    // accepted filters per event
    for(trigger::size_type iFilter=0; iFilter!=nFilters; ++iFilter) {
	std::string filterTag = triggerEventL1->filterTag(iFilter).encode();
	trigger::Keys objectKeys = triggerEventL1->filterKeys(iFilter);

	const trigger::TriggerObjectCollection& triggerObjects(triggerEventL1->getObjects());

	// fill "pass filter" branches
	int nObjKeys = objectKeys.size();
        // accept pass or fail condition to fill nEvents branch
	if (filterTag == hltL1VBFDiJetOR_Tag && nObjKeys >= 0) nEvents = 1;

        // L1s
        // Two Different Object Types L1s
	if (filterTag == hltL1VBFDiJetIsoTau_Tag 
            && hltL1VBFDiJetIsoTau_tauPt.size() >= 1
            && hltL1VBFDiJetIsoTau_jetPt.size() >= 2) passhltL1VBFDiJetIsoTau = 1;

        if (filterTag == hltL1sMu22er2p1IsoTau28er2p1_Tag 
            && hltL1sMu22er2p1IsoTau28er2p1_muPt.size() >= 1
            && hltL1sMu22er2p1IsoTau28er2p1_tauPt.size() >= 1) passhltL1sMu22er2p1IsoTau28er2p1 = 1;

        if (filterTag == hltL1VBFElectronTightIso_RealHLT_Tag
            && hltL1VBFElectronTightIso_RealHLT_ePt.size() >= 1
            && hltL1VBFElectronTightIso_RealHLT_jPt.size() >= 2) passhltL1VBFElectronTightIso_RealHLT = 1;

        if (filterTag == hltL1VBFElectronTightIso_Tag
            && hltL1VBFElectronTightIso_ePt.size() >= 1
            && hltL1VBFElectronTightIso_jPt.size() >= 2) passhltL1VBFElectronTightIso = 1; 

        if (filterTag == hltL1VBFElectronLooseIso_Tag
            && hltL1VBFElectronLooseIso_ePt.size() >= 1
            && hltL1VBFElectronLooseIso_jPt.size() >= 2) passhltL1VBFElectronLooseIso = 1;

        if (filterTag == hltL1VBFElectronNoIso_Tag
            && hltL1VBFElectronNoIso_ePt.size() >= 1
            && hltL1VBFElectronNoIso_jPt.size() >= 2) passhltL1VBFElectronNoIso = 1;

        // Single Object Type L1s
	if (filterTag == hltL1sDoubleTauBigOR_Tag && nObjKeys >= 2) passhltL1sDoubleTauBigOR = 1;
	if (filterTag == hltL1VBFDiJetOR_Tag && nObjKeys >= 2) passhltL1VBFDiJetOR = 1;
        if (filterTag == hltL1sSingleMu22_Tag && nObjKeys >= 1) passhltL1sSingleMu22 = 1;
        if (filterTag == hltL1sSingleEG26_Tag && nObjKeys >= 1) passhltL1sSingleEG26 = 1;
        if (filterTag == hltL1sSingleEGor_Tag && nObjKeys >= 1) passhltL1sSingleEGor = 1;

        if (filterTag == hltPassthroughL1EGTightIso_Tag && nObjKeys >= 1) passhltPassthroughL1EGTightIso = 1;
        if (filterTag == hltPassthroughL1EGLooseIso_Tag && nObjKeys >= 1) passhltPassthroughL1EGLooseIso = 1;
        if (filterTag == hltPassthroughL1EGNoIso_Tag && nObjKeys >= 1) passhltPassthroughL1EGNoIso = 1;

	//loop over trigger objects and store their kinematics to the proper filter branches
	for(trigger::size_type iKey=0; iKey < nObjKeys; ++iKey){
	    trigger::size_type objKey = objectKeys.at(iKey);
	    const trigger::TriggerObject& triggerObj(triggerObjects[objKey]);
	    ptL1_ = triggerObj.pt();
	    etaL1_ = triggerObj.eta();
	    phiL1_ = triggerObj.phi();
	    energyL1_ = triggerObj.energy();
        // clear vectors right here?
	// fill ditau and inclusive L1 branches (proposed L1 branches filled separately because it has two types of objects)
	    if (filterTag == hltL1sDoubleTauBigOR_Tag 
                  && passhltL1sDoubleTauBigOR && ptL1_>0) {
		hltL1sDoubleTauBigOR_pt.push_back(ptL1_);
		hltL1sDoubleTauBigOR_eta.push_back(etaL1_);
		hltL1sDoubleTauBigOR_phi.push_back(phiL1_);
		hltL1sDoubleTauBigOR_energy.push_back(energyL1_);
	    }
	    if (filterTag == hltL1VBFDiJetOR_Tag 
                  && passhltL1VBFDiJetOR && ptL1_>0) {
		hltL1VBFDiJetOR_pt.push_back(ptL1_);
		hltL1VBFDiJetOR_eta.push_back(etaL1_);
		hltL1VBFDiJetOR_phi.push_back(phiL1_);
		hltL1VBFDiJetOR_energy.push_back(energyL1_);
	    }
            if (filterTag == hltL1sSingleMu22_Tag
                  && passhltL1sSingleMu22 && ptL1_>0) {
                hltL1sSingleMu22_pt.push_back(ptL1_);
                hltL1sSingleMu22_eta.push_back(etaL1_);
                hltL1sSingleMu22_phi.push_back(phiL1_);
                hltL1sSingleMu22_energy.push_back(energyL1_);
            }
            if (filterTag == hltL1sSingleEG26_Tag
                  && passhltL1sSingleEG26 && ptL1_>0) {
                hltL1sSingleEG26_pt.push_back(ptL1_);
                hltL1sSingleEG26_eta.push_back(etaL1_);
                hltL1sSingleEG26_phi.push_back(phiL1_);
                hltL1sSingleEG26_energy.push_back(energyL1_);
            }
            if (filterTag == hltL1sSingleEGor_Tag
                  && passhltL1sSingleEGor && ptL1_>0) {
                hltL1sSingleEGor_pt.push_back(ptL1_);
                hltL1sSingleEGor_pt.push_back(etaL1_);
                hltL1sSingleEGor_pt.push_back(phiL1_);
                hltL1sSingleEGor_pt.push_back(energyL1_);
            }
            if (filterTag == hltPassthroughL1EGTightIso_Tag
                  && passhltPassthroughL1EGTightIso && ptL1_>0) {
                hltPassthroughL1EGTightIso_pt.push_back(ptL1_);
                hltPassthroughL1EGTightIso_eta.push_back(etaL1_);
                hltPassthroughL1EGTightIso_phi.push_back(phiL1_);
                hltPassthroughL1EGTightIso_energy.push_back(energyL1_);
            }
            if (filterTag == hltPassthroughL1EGLooseIso_Tag
                  && passhltPassthroughL1EGLooseIso && ptL1_>0) {
                hltPassthroughL1EGLooseIso_pt.push_back(ptL1_);
                hltPassthroughL1EGLooseIso_eta.push_back(etaL1_);
                hltPassthroughL1EGLooseIso_phi.push_back(phiL1_);
                hltPassthroughL1EGLooseIso_energy.push_back(energyL1_);
            }
            if (filterTag == hltPassthroughL1EGNoIso_Tag
                  && passhltPassthroughL1EGNoIso && ptL1_>0) {
                hltPassthroughL1EGNoIso_pt.push_back(ptL1_);
                hltPassthroughL1EGNoIso_eta.push_back(etaL1_);
                hltPassthroughL1EGNoIso_phi.push_back(phiL1_);
                hltPassthroughL1EGNoIso_energy.push_back(energyL1_);
            }

	} // end loop over trigger object keys
    } // end loop over nfilters
} // end function
