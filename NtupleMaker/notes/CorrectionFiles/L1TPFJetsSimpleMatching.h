#ifndef L1TPFJetsSimpleMatching_H
#define L1TPFJetsSimpleMatching_H

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/ParameterSet/interface/ConfigurationDescriptions.h"
#include "FWCore/ParameterSet/interface/ParameterSetDescription.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/L1Trigger/interface/L1JetParticle.h"
#include "DataFormats/L1Trigger/interface/L1JetParticleFwd.h"
#include "DataFormats/JetReco/interface/CaloJetCollection.h"
#include "DataFormats/HLTReco/interface/TriggerFilterObjectWithRefs.h"

#include <map>
#include <vector>

class L1TPFJetsSimpleMatching : public edm::EDProducer {
public:
    explicit L1TPFJetsSimpleMatching(const edm::ParameterSet&);
    ~L1TPFJetsSimpleMatching() override;
    void produce(edm::Event&, const edm::EventSetup&) override;
    static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

private:
    const edm::EDGetTokenT<reco::PFJetCollection> jetSrc_;
    const edm::EDGetTokenT<trigger::TriggerFilterObjectWithRefs> jetTrigger_;
    const double ptMin_;
    const double matchingR2_;
};
#endif
