#include "VBFIsoTauHLT/NtupleMaker/plugins/NtupleMaker.h"

#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/EventSetup.h"

// from https://github.com/cmkuo/ggAnalysis/blob/94X/ggNtuplizer/plugins/ggNtuplizer_muons.cc

using namespace std;
//typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > LorentzVector;

vector<float>  muL1PrimitivesPt_;
vector<float>  muL1PrimitivesEta_;
vector<float>  muL1PrimitivesPhi_;
vector<float>  muL1PrimitivesEnergy_;
	
vector<float>  muPt_;
vector<float>  muEnergy_;
vector<float>  muEta_;
vector<float>  muPhi_;
vector<float>  muCharge_;

vector<float>  muPFChIso_;
vector<float>  muPFPUIso_;
vector<float>  muPFNeuIso_;
vector<float>  muPFPhoIso_;

vector<int> muPDGID_;

Int_t nMuon_;

vector<int> muMVALoose_;
vector<int> muMVAMed_;
vector<int> muMVATight_;
vector<float> muRelIso0p15_;


void NtupleMaker::branchesL1Muons(TTree* tree) {

  tree->Branch("muL1PrimitivesPt",  &muL1PrimitivesPt_);
  tree->Branch("muL1PrimitivesEta", &muL1PrimitivesEta_);
  tree->Branch("muL1PrimitivesPhi", &muL1PrimitivesPhi_);
  tree->Branch("muL1PrimitivesEnergy",    &muL1PrimitivesEnergy_);

}

void NtupleMaker::branchesMuons(TTree* tree) {
  
  tree->Branch("nMuon", &nMuon_);
  tree->Branch("muPt", &muPt_);
  tree->Branch("muEta", &muEta_);
  tree->Branch("muPhi", &muPhi_);
  tree->Branch("muEnergy", &muEnergy_);
  tree->Branch("muCharge", &muCharge_);

  tree->Branch("muPFChIso", &muPFChIso_);
  tree->Branch("muPFPUIso", &muPFPUIso_);
  tree->Branch("muPFNeuIso", &muPFNeuIso_);
  tree->Branch("muPFPhoIso", &muPFPhoIso_);

  tree->Branch("muPDGID", &muPDGID_);

  tree->Branch("muMVALoose", &muMVALoose_);
  tree->Branch("muMVAMed", &muMVAMed_);
  tree->Branch("muMVATight", &muMVATight_);
  tree->Branch("muRelIso0p15", &muRelIso0p15_);

}

void NtupleMaker::fillL1Muons(const edm::Event& iEvent) {

  muL1PrimitivesPt_.clear();
  muL1PrimitivesEta_.clear();
  muL1PrimitivesPhi_.clear();
  muL1PrimitivesEnergy_.clear();

  edm::Handle<BXVector<l1t::Muon>> muL1Handle;
  iEvent.getByToken(muonTriggerPrimitives_, muL1Handle);

  for(BXVector<l1t::Muon>::const_iterator imu = muL1Handle->begin(0); imu != muL1Handle->end(0); ++imu) {
      muL1PrimitivesPt_.push_back(imu->pt());
      muL1PrimitivesEta_.push_back(imu->eta());
      muL1PrimitivesPhi_.push_back(imu->phi());
      muL1PrimitivesEnergy_.push_back(imu->energy());
  }

}

void NtupleMaker::fillMuons(const edm::Event& e) { //, const edm::EventSetup& es) {

  nMuon_ = 0;
  muPt_.clear();
  muEta_.clear();
  muPhi_.clear();
  muEnergy_.clear();
  muCharge_.clear();

  muPFChIso_.clear();
  muPFPUIso_.clear();
  muPFNeuIso_.clear();
  muPFPhoIso_.clear();

  muPDGID_.clear();

  muMVALoose_.clear();
  muMVAMed_.clear();
  muMVATight_.clear();
  muRelIso0p15_.clear();

  // fill muon pat
  edm::Handle<vector<pat::Muon> > muonHandle;
  e.getByToken(muonCollection_, muonHandle);

  if (!muonHandle.isValid()) {
    edm::LogWarning("ggNtuplizer") << "no pat::Muons (AK4) in event";
    return;
  }
  
  for (vector<pat::Muon>::const_iterator iMu = muonHandle->begin(); iMu != muonHandle->end(); ++iMu) {

    muPt_.push_back(iMu->pt());
    muEta_.push_back(iMu->eta());
    muPhi_.push_back(iMu->phi());
    muEnergy_.push_back(iMu->energy());
    muCharge_.push_back(iMu->charge());

    // different access of isolation variables between electrons and muons
    // https://github.com/cmkuo/ggAnalysis/blob/94X/ggNtuplizer/plugins/ggNtuplizer_muons.cc#L227-L237

    muPFChIso_.push_back(iMu->pfIsolationR04().sumChargedHadronPt);
    muPFPhoIso_.push_back(iMu->pfIsolationR04().sumPhotonEt);
    muPFNeuIso_.push_back(iMu->pfIsolationR04().sumNeutralHadronEt);
    muPFPUIso_.push_back(iMu->pfIsolationR04().sumPUPt);

    muPDGID_.push_back(iMu->pdgId());

    muMVALoose_.push_back(iMu->passed(reco::Muon::MvaLoose));
    muMVAMed_.push_back(iMu->passed(reco::Muon::MvaMedium)); 
    muMVATight_.push_back(iMu->passed(reco::Muon::MvaTight));
    // the Muon POG really has their shit together and simply has the rel iso available at MiniAOD
    // https://twiki.cern.ch/twiki/bin/view/CMS/SWGuideMuonSelection
    muRelIso0p15_.push_back(iMu->passed(reco::Muon::PFIsoMedium));


    ++nMuon_;
  }
  
}
