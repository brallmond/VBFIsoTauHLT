#include "RecoTauTag/HLTProducers/interface/L1TPFJetsSimpleMatching.h"
#include "Math/GenVector/VectorUtil.h"
#include "DataFormats/L1Trigger/interface/L1JetParticle.h"
#include "DataFormats/L1Trigger/interface/L1JetParticleFwd.h"
#include "DataFormats/HLTReco/interface/TriggerTypeDefs.h"
#include "FWCore/Utilities/interface/EDMException.h"

#include "DataFormats/Math/interface/deltaR.h"

//
// class decleration
//

L1TPFJetsSimpleMatching::L1TPFJetsSimpleMatching(const edm::ParameterSet& iConfig) 
:   jetSrc_(consumes<reco::PFJetCollection>(iConfig.getParameter<edm::InputTag>("JetSrc"))),
    jetTrigger_(consumes<trigger::TriggerFilterObjectWithRefs>(iConfig.getParameter<edm::InputTag>("L1JetTrigger"))),
    ptMin_(iConfig.getParameter<double>("ptMin")),
    matchingR2_(iConfig.getParameter<double>("matchingR") * iConfig.getParameter<double>("matchingR")) {
    produces<reco::PFJetCollection>();
}

L1TPFJetsSimpleMatching::~L1TPFJetsSimpleMatching() {}

void L1TPFJetsSimpleMatching::produce(edm::Event& iEvent, const edm::EventSetup& iES) {
  unique_ptr<reco::PFJetCollection> pfMatchedJets(new reco::PFJetCollection);

  edm::Handle<reco::PFJetCollection> pfJets;
  iEvent.getByToken(jetSrc_, pfJets);

  edm::Handle<trigger::TriggerFilterObjectWithRefs> l1TriggeredJets;
  iEvent.getByToken(jetTrigger_, l1TriggeredJets);

  l1t::JetVectorRef jetCandRefVec;
  l1TriggeredJets->getObjects(trigger::TriggerL1Jet, jetCandRefVec);

  math::XYZPoint a(0., 0., 0.);

  //std::cout<<"PFsize= "<<pfJets->size()<<endl<<" L1size= "<<jetCandRefVec.size()<<std::endl;
  for (unsigned int iJet = 0; iJet < pfJets->size(); iJet++) {
    const reco::PFJet& myJet = (*pfJets)[iJet];

    if (myJet.pt() < ptMin_) continue;

    for (unsigned int iL1Jet = 0; iL1Jet < jetCandRefVec.size(); iL1Jet++) {
      // Find the relative L2pfJets, to see if it has been reconstructed
      //  if ((iJet<3) && (iL1Jet==0))  std::cout<<myJet.p4().Pt()<<" ";
      if (reco::deltaR2(myJet.p4(), jetCandRefVec[iL1Jet]->p4()) < matchingR2_) {
        pfMatchedJets->push_back(myJet);
        break;
      }
    }
  }

  iEvent.put(std::move(pfMatchedJets));
}

void L1TPFJetsSimpleMatching::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  edm::ParameterSetDescription desc;
  desc.add<edm::InputTag>("L1JetTrigger", edm::InputTag("hltL1VBFDiJetIsoTau"))->setComment("Name of trigger filter");
  desc.add<edm::InputTag>("JetSrc", edm::InputTag("hltAK4PFJetsTightIDCorrected"))
      ->setComment("Input collection of PFJets");
  desc.add<double>("ptMin", 40)->setComment("Minimal pT of PFJets to match");
  desc.add<double>("matchingR", 0.5)->setComment("dR value used for matching");
  descriptions.setComment(
      "This module produces collection of PFJetss matched to L1 Taus / Jets passing a HLT filter (Only p4 and vertex "
      "of returned PFJets are set).");
  descriptions.add("L1TPFJetsSimpleMatching", desc);
}
