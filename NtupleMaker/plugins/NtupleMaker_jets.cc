#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "VBFIsoTauHLT/NtupleMaker/plugins/NtupleMaker.h"
#include "JetMETCorrections/Objects/interface/JetCorrector.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"
#include "JetMETCorrections/Objects/interface/JetCorrectionsRecord.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/EventSetup.h"
//#include "DataFormats/Math/interface/LorentzVector.h"
#include "CondFormats/JetMETObjects/interface/FactorizedJetCorrector.h"
#include "FWCore/Utilities/interface/RandomNumberGenerator.h"
#include "CLHEP/Random/RandomEngine.h"
#include "CLHEP/Random/RandGauss.h"

using namespace std;
//typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > LorentzVector;

Int_t          nJet_;

vector<float>  jetL1PrimitivesPt_;
vector<float>  jetL1PrimitivesEta_;
vector<float>  jetL1PrimitivesPhi_;
vector<float>  jetL1PrimitivesEnergy_;

vector<float>  jetPt_;
vector<float>  jetEta_;
vector<float>  jetPhi_;
vector<float>  jetEnergy_;

vector<bool>   jetPFLooseId_;
vector<int>    jetID_; 
vector<float>  jetPUID_;
vector<int>    jetPUFullID_;


void NtupleMaker::branchesL1Jets(TTree* tree) {

  tree->Branch("jetL1PrimitivesPt",  &jetL1PrimitivesPt_);
  tree->Branch("jetL1PrimitivesEta", &jetL1PrimitivesEta_);
  tree->Branch("jetL1PrimitivesPhi", &jetL1PrimitivesPhi_);
  tree->Branch("jetL1PrimitivesEnergy",    &jetL1PrimitivesEnergy_);

}

void NtupleMaker::branchesJets(TTree* tree) {
  
  tree->Branch("nJet",                &nJet_);

  tree->Branch("jetPt",               &jetPt_);
  tree->Branch("jetEta",              &jetEta_);
  tree->Branch("jetPhi",              &jetPhi_);
  tree->Branch("jetEnergy",               &jetEnergy_);

  tree->Branch("jetPFLooseId", &jetPFLooseId_);
  tree->Branch("jetID",        &jetID_);
  tree->Branch("jetPUID",      &jetPUID_);
  tree->Branch("jetPUFullID",  &jetPUFullID_);

}

void NtupleMaker::fillL1Jets(const edm::Event& iEvent) {

  jetL1PrimitivesPt_.clear();
  jetL1PrimitivesEta_.clear();
  jetL1PrimitivesPhi_.clear();
  jetL1PrimitivesEnergy_.clear();

  edm::Handle<BXVector<l1t::Jet>> jetL1Handle;
  iEvent.getByToken(jetTriggerPrimitives_, jetL1Handle);

  for(BXVector<l1t::Jet>::const_iterator ijet = jetL1Handle->begin(0); ijet != jetL1Handle->end(0); ++ijet) {
      jetL1PrimitivesPt_.push_back(ijet->pt());
      jetL1PrimitivesEta_.push_back(ijet->eta());
      jetL1PrimitivesPhi_.push_back(ijet->phi());
      jetL1PrimitivesEnergy_.push_back(ijet->energy());
  }

}

void NtupleMaker::fillJets(const edm::Event& e, const edm::EventSetup& es) {

  jetPt_                                  .clear();
  jetEta_                                 .clear();
  jetPhi_                                 .clear();
  jetEnergy_                                  .clear();

  jetPFLooseId_                           .clear();
  jetID_                                  .clear();
  jetPUID_                                .clear();
  jetPUFullID_                            .clear();


  nJet_ = 0;

  // fill jet pat
  edm::Handle<edm::View<pat::Jet> > jetHandle;
  e.getByToken(jetsAK4Label_, jetHandle);

  if (!jetHandle.isValid()) {
    edm::LogWarning("ggNtuplizer") << "no pat::Jets (AK4) in event";
    return;
  }

  for (edm::View<pat::Jet>::const_iterator iJet = jetHandle->begin(); iJet != jetHandle->end(); ++iJet) {

    if (iJet->pt() < 20) continue;
    jetPt_.push_back(    iJet->pt());
    jetEta_.push_back(   iJet->eta());
    jetPhi_.push_back(   iJet->phi());
    jetEnergy_.push_back(    iJet->energy());

  

    //jet PF Loose ID
    double NHF      = iJet->neutralHadronEnergyFraction();
    double NEMF     = iJet->neutralEmEnergyFraction();
    double NumConst = iJet->chargedMultiplicity()+iJet->neutralMultiplicity();
    double CHF      = iJet->chargedHadronEnergyFraction();
    double CHM      = iJet->chargedMultiplicity();
    double CEMF     = iJet->chargedEmEnergyFraction();
    double NNP      = iJet->neutralMultiplicity();

    bool looseJetID = false;    
    bool tightJetID = false;
    if (fabs(iJet->eta()) <= 2.7) {
      looseJetID = (NHF<0.99 && NEMF<0.99 && NumConst>1) && ((fabs(iJet->eta())<=2.4 && CHF>0 && CHM>0 && CEMF<0.99) || fabs(iJet->eta())>2.4);
      tightJetID = (NHF<0.90 && NEMF<0.90 && NumConst>1) && ((fabs(iJet->eta())<=2.4 && CHF>0 && CHM>0 && CEMF<0.99) || fabs(iJet->eta())>2.4);
    } else if (fabs(iJet->eta()) <= 3.0) {
      looseJetID = (NEMF>0.01 && NHF<0.98 && NNP>2);
      tightJetID = (NEMF>0.01 && NHF<0.98 && NNP>2);
    } else {
      looseJetID = (NEMF<0.90 && NNP>10); 
      tightJetID = (NEMF<0.90 && NNP>10);
    }
    jetPFLooseId_.push_back(looseJetID);
    Int_t jetIDdecision = 0;
    if (looseJetID) jetIDdecision += pow(2, 1);
    if (tightJetID) jetIDdecision += pow(2, 2);
    jetID_.push_back(jetIDdecision);    

    // PUJet ID from slimmedJets
    jetPUID_.push_back(iJet->userFloat("pileupJetId:fullDiscriminant"));
    jetPUFullID_.push_back(iJet->userInt("pileupJetId:fullId"));


    nJet_++;
  }
  
}
