#include "VBFIsoTauHLT/NtupleMaker/plugins/NtupleMaker.h"

#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "DataFormats/GsfTrackReco/interface/GsfTrackFwd.h"
#include "DataFormats/EcalDetId/interface/ESDetId.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/EventSetup.h"

// from https://github.com/cmkuo/ggAnalysis/blob/94X/ggNtuplizer/plugins/ggNtuplizer_electrons.cc

using namespace std;
//typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > LorentzVector;

vector<float>  eleL1PrimitivesPt_;
vector<float>  eleL1PrimitivesEta_;
vector<float>  eleL1PrimitivesPhi_;
vector<float>  eleL1PrimitivesEnergy_;
	

vector<float>  elePt_;
vector<float>  eleEnergy_;
vector<float>  eleEta_;
vector<float>  elePhi_;
vector<float>  eleCharge_;

vector<float>  eleChargedHadronIso_;
vector<float>  elePUChargedHadronIso_;
vector<float>  eleNeutralHadronIso_;
vector<float>  elePhotonIso_;

vector<int> elePDGID_;

vector<float>  eleIDMVAIso_; 
vector<float>  eleIDMVANoIso_; 

vector<int> eleIDMVAIsowp90_;
vector<int> eleIDMVAIsowp80_;
vector<int> eleIDMVANoIsowp90_;
vector<int> eleIDMVANoIsowp80_;

Int_t nEle_;


void NtupleMaker::branchesL1Electrons(TTree* tree) {

  tree->Branch("eleL1PrimitivesPt",  &eleL1PrimitivesPt_);
  tree->Branch("eleL1PrimitivesEta", &eleL1PrimitivesEta_);
  tree->Branch("eleL1PrimitivesPhi", &eleL1PrimitivesPhi_);
  tree->Branch("eleL1PrimitivesEnergy",    &eleL1PrimitivesEnergy_);

}

void NtupleMaker::branchesElectrons(TTree* tree) {
  
  tree->Branch("nEle", &nEle_);
  tree->Branch("elePt", &elePt_);
  tree->Branch("eleEta", &eleEta_);
  tree->Branch("elePhi", &elePhi_);
  tree->Branch("eleEnergy", &eleEnergy_);
  tree->Branch("eleCharge", &eleCharge_);

  tree->Branch("eleChargedHadronIso", &eleChargedHadronIso_);
  tree->Branch("elePUChargedHadronIso", &elePUChargedHadronIso_);
  tree->Branch("eleNeutralHadronIso", &eleNeutralHadronIso_);
  tree->Branch("elePhotonIso", &elePhotonIso_);

  tree->Branch("elePDGID", &elePDGID_);
  tree->Branch("eleIDMVAIso", &eleIDMVAIso_);
  tree->Branch("eleIDMVANoIso", &eleIDMVANoIso_);
  tree->Branch("eleIDMVAIsowp90", &eleIDMVAIsowp90_);
  tree->Branch("eleIDMVAIsowp80", &eleIDMVAIsowp80_);
  tree->Branch("eleIDMVANoIsowp90", &eleIDMVANoIsowp90_);
  tree->Branch("eleIDMVANoIsowp80", &eleIDMVANoIsowp80_);

}

void NtupleMaker::fillL1Electrons(const edm::Event& iEvent) {

  eleL1PrimitivesPt_.clear();
  eleL1PrimitivesEta_.clear();
  eleL1PrimitivesPhi_.clear();
  eleL1PrimitivesEnergy_.clear();

  edm::Handle<BXVector<l1t::EGamma>> eleL1Handle;
  iEvent.getByToken(eleTriggerPrimitives_, eleL1Handle);

  for(BXVector<l1t::EGamma>::const_iterator iele = eleL1Handle->begin(0); iele != eleL1Handle->end(0); ++iele) {
      eleL1PrimitivesPt_.push_back(iele->pt());
      eleL1PrimitivesEta_.push_back(iele->eta());
      eleL1PrimitivesPhi_.push_back(iele->phi());
      eleL1PrimitivesEnergy_.push_back(iele->energy());
  }

}

void NtupleMaker::fillElectrons(const edm::Event& e) { //, const edm::EventSetup& es) {

  nEle_ = 0;
  elePt_.clear();
  eleEta_.clear();
  elePhi_.clear();
  eleEnergy_.clear();
  eleCharge_.clear();

  eleChargedHadronIso_.clear();
  elePUChargedHadronIso_.clear();
  eleNeutralHadronIso_.clear();
  elePhotonIso_.clear();

  elePDGID_.clear();

  eleIDMVAIso_.clear();
  eleIDMVANoIso_.clear();
  eleIDMVAIsowp90_.clear();
  eleIDMVAIsowp80_.clear();
  eleIDMVANoIsowp90_.clear();
  eleIDMVANoIsowp80_.clear();

  // fill electron pat
  //edm::Handle<edm::View<pat::Electron> > electronHandle;
  edm::Handle<vector<pat::Electron> > electronHandle;
  e.getByToken(electronCollection_, electronHandle);

  if (!electronHandle.isValid()) {
    edm::LogWarning("ggNtuplizer") << "no pat::Electrons (AK4) in event";
    return;
  }
  
  for (vector<pat::Electron>::const_iterator iEle = electronHandle->begin(); iEle != electronHandle->end(); ++iEle) {

    elePt_.push_back(iEle->pt());
    eleEta_.push_back(iEle->eta());
    elePhi_.push_back(iEle->phi());
    eleEnergy_.push_back(iEle->energy());
    eleCharge_.push_back(iEle->charge());

    // variables for lepton hadronic activity, defined here
    // https://github.com/cms-sw/cmssw/blob/master/DataFormats/PatCandidates/interface/Lepton.h#L163-L165
    // https://github.com/cms-sw/cmssw/blob/master/DataFormats/PatCandidates/interface/Electron.h#L153-L155
    eleChargedHadronIso_.push_back(iEle->puppiChargedHadronIso());
    elePUChargedHadronIso_.push_back(iEle->puChargedHadronIso());
    eleNeutralHadronIso_.push_back(iEle->puppiNeutralHadronIso());
    elePhotonIso_.push_back(iEle->puppiPhotonIso());

    //elePDGID_.push_back(iEle->genParticle());
    elePDGID_.push_back(iEle->pdgId());

    eleIDMVAIso_.push_back(iEle->userFloat("ElectronMVAEstimatorRun2Fall17IsoV2Values")); // actual MVA result
    eleIDMVANoIso_.push_back(iEle->userFloat("ElectronMVAEstimatorRun2Fall17NoIsoV2Values"));

    eleIDMVAIsowp90_.push_back(iEle->electronID("mvaEleID-Fall17-iso-V1-wp90")); // booleans, if ele pass MVA
    eleIDMVAIsowp80_.push_back(iEle->electronID("mvaEleID-Fall17-iso-V1-wp80"));

    eleIDMVANoIsowp90_.push_back(iEle->electronID("mvaEleID-Fall17-noIso-V1-wp90"));
    eleIDMVANoIsowp80_.push_back(iEle->electronID("mvaEleID-Fall17-noIso-V1-wp80"));

    ++nEle_;
  }
  
}
