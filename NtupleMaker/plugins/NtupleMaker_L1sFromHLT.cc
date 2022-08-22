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


void NtupleMaker::branchesL1sFromHLT(TTree* tree){

    tree->Branch("nEvents", &nEvents);

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

    // Also for VBF + Electron
    const unsigned int VBFElectronL1Filter(triggerEventWithRefsHandle_->filterIndex(InputTag("hltL1VBFElectron", "", "MYOTHERHLT")));

    l1t::EGammaVectorRef electronCandRefVec;
    trigger::Vids eVids;
    triggerEventWithRefsHandle_->getObjects(VBFElectronL1Filter, eVids, electronCandRefVec);

    hltL1VBFElectron_ePt.clear();
    hltL1VBFElectron_eEta.clear();
    hltL1VBFElectron_ePhi.clear();
    hltL1VBFElectron_eEnergy.clear();
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

    hltL1VBFElectron_jPt.clear();
    hltL1VBFElectron_jEta.clear();
    hltL1VBFElectron_jPhi.clear();
    hltL1VBFElectron_jEnergy.clear();
    const unsigned int nVBFElectronJets(ejVids.size());
    if (nVBFElectronJets > 0) {
      for (unsigned int i = 0; i != nVBFElectronJets; ++ i) {
        hltL1VBFElectron_jPt.push_back(VBFElectronJetRefVec[i]->pt());
        hltL1VBFElectron_jEta.push_back(VBFElectronJetRefVec[i]->eta());
        hltL1VBFElectron_jPhi.push_back(VBFElectronJetRefVec[i]->phi());
        hltL1VBFElectron_jEnergy.push_back(VBFElectronJetRefVec[i]->energy());
      }
    }
  
    // again for VBF + Loose Electron
    const unsigned int VBFElectronL1LooseFilter(triggerEventWithRefsHandle_->filterIndex(InputTag("hltL1VBFElectronLoose", "", "MYOTHERHLT")));

    l1t::EGammaVectorRef looseElectronCandRefVec;
    trigger::Vids leVids;
    triggerEventWithRefsHandle_->getObjects(VBFElectronL1LooseFilter, leVids, looseElectronCandRefVec);

    hltL1VBFElectronLoose_ePt.clear();
    hltL1VBFElectronLoose_eEta.clear();
    hltL1VBFElectronLoose_ePhi.clear();
    hltL1VBFElectronLoose_eEnergy.clear();
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

    hltL1VBFElectronLoose_jPt.clear();
    hltL1VBFElectronLoose_jEta.clear();
    hltL1VBFElectronLoose_jPhi.clear();
    hltL1VBFElectronLoose_jEnergy.clear();
    const unsigned int nVBFLooseElectronJets(lejVids.size());
    if (nVBFLooseElectronJets > 0) {
      for (unsigned int i = 0; i != nVBFLooseElectronJets; ++ i) {
        hltL1VBFElectronLoose_jPt.push_back(VBFLooseElectronJetRefVec[i]->pt());
        hltL1VBFElectronLoose_jEta.push_back(VBFLooseElectronJetRefVec[i]->eta());
        hltL1VBFElectronLoose_jPhi.push_back(VBFLooseElectronJetRefVec[i]->phi());
        hltL1VBFElectronLoose_jEnergy.push_back(VBFLooseElectronJetRefVec[i]->energy());
      }
    }

    nEvents = 0;

    passhltL1VBFElectron = 0;
    passhltL1VBFElectronLoose = 0;

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

    // getting trigger event per this page
    // https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideHLTAnalysis
    edm::Handle<trigger::TriggerEvent> triggerEventL1; // this code should be with the filters
    iEvent.getByToken(triggerEventToken_, triggerEventL1); // same

    // make strings to identify filter names
    const trigger::size_type nFilters(triggerEventL1->sizeFilters());
    std::string hltL1sDoubleTauBigOR_Tag = "hltL1sDoubleTauBigOR::MYOTHERHLT";
    std::string hltL1sMu22er2p1IsoTau28er2p1_Tag = "hltL1sMu22er2p1IsoTau28er2p1::MYOTHERHLT";
    std::string hltL1VBFElectron_Tag = "hltL1VBFElectron::MYOTHERHLT";
    std::string hltL1VBFElectronLoose_Tag = "hltL1VBFElectronLoose::MYOTHERHLT";

    std::string hltL1VBFDiJetOR_Tag = "hltL1VBFDiJetOR::MYOTHERHLT";
    std::string hltL1VBFDiJetIsoTau_Tag = "hltL1VBFDiJetIsoTau::MYOTHERHLT";	  
    std::string hltL1sSingleMu22_Tag = "hltL1sSingleMu22::MYOTHERHLT";


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
        if (filterTag == hltL1VBFElectron_Tag
            && hltL1VBFElectron_ePt.size() >= 1
            && hltL1VBFElectron_jPt.size() >= 2) passhltL1VBFElectron = 1; 
        if (filterTag == hltL1VBFElectronLoose_Tag
            && hltL1VBFElectronLoose_ePt.size() >= 1
            && hltL1VBFElectronLoose_jPt.size() >= 2) passhltL1VBFElectronLoose = 1;

        // Single Object Type L1s
	if (filterTag == hltL1sDoubleTauBigOR_Tag && nObjKeys >= 2) passhltL1sDoubleTauBigOR = 1;
	if (filterTag == hltL1VBFDiJetOR_Tag && nObjKeys >= 2) passhltL1VBFDiJetOR = 1;
        if (filterTag == hltL1sSingleMu22_Tag && nObjKeys >= 1) passhltL1sSingleMu22 = 1;

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

	} // end loop over trigger object keys
    } // end loop over nfilters
} // end function
