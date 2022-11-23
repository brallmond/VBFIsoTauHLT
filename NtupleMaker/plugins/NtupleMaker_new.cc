#include "VBFIsoTauHLT/NtupleMaker/plugins/NtupleMaker.h"

//using namespace std;

NtupleMaker::NtupleMaker(const edm::ParameterSet& iConfig) :
    fillingTriggers(iConfig.getUntrackedParameter<bool>("fillingTriggers")),
    fillingL1sFromHLT(iConfig.getUntrackedParameter<bool>("fillingL1sFromHLT")),
    fillingHLTFinalDecision(iConfig.getUntrackedParameter<bool>("fillingHLTFinalDecision")),

    fillingL1Primitives(iConfig.getUntrackedParameter<bool>("fillingL1Primitives")),
    fillingEventInfo(iConfig.getUntrackedParameter<bool>("fillingEventInfo")),

    fillingTaus(iConfig.getUntrackedParameter<bool>("fillingTaus")),
    fillingJets(iConfig.getUntrackedParameter<bool>("fillingJets")),
    fillingElectrons(iConfig.getUntrackedParameter<bool>("fillingElectrons")),
    fillingMuons(iConfig.getUntrackedParameter<bool>("fillingMuons")),

    development_(iConfig.getUntrackedParameter<bool>("development")),
    doGenParticles_(iConfig.getUntrackedParameter<bool>("doGenParticles")),
    genParticlesCollection_(consumes<vector<reco::GenParticle>>(iConfig.getUntrackedParameter<edm::InputTag>("genParticleSrc"))),
    tauCollection_(consumes<vector<pat::Tau>>(iConfig.getUntrackedParameter<edm::InputTag>("tauSrc"))),
    electronCollection_(consumes<vector<pat::Electron>>(iConfig.getUntrackedParameter<edm::InputTag>("electronSrc"))),
    muonCollection_(consumes<vector<pat::Muon>>(iConfig.getUntrackedParameter<edm::InputTag>("muonSrc"))),
    //PFTauCollection_(consumes<vector<reco::PFTau>>(iConfig.getUntrackedParameter<edm::InputTag>("PFTauCollection"))),
    // L1 Trigger Primitives
    jetTriggerPrimitives_(consumes<BXVector<l1t::Jet>>(iConfig.getUntrackedParameter<edm::InputTag>("jetTriggerPrimitives"))),
    tauTriggerPrimitives_(consumes<BXVector<l1t::Tau>>(iConfig.getUntrackedParameter<edm::InputTag>("tauTriggerPrimitives"))),
    eleTriggerPrimitives_(consumes<BXVector<l1t::EGamma>>(iConfig.getUntrackedParameter<edm::InputTag>("eleTriggerPrimitives"))),
    muonTriggerPrimitives_(consumes<BXVector<l1t::Muon>>(iConfig.getUntrackedParameter<edm::InputTag>("muonTriggerPrimitives"))),

    vtxLabel_(consumes<reco::VertexCollection>(iConfig.getUntrackedParameter<edm::InputTag>("VtxLabel"))),
    rhoLabel_(consumes<double>(iConfig.getUntrackedParameter<edm::InputTag>("rhoLabel"))),
    jetsAK4Label_(consumes<edm::View<pat::Jet>>(iConfig.getUntrackedParameter<edm::InputTag>("ak4JetSrc"))),

    triggerResultToken_(consumes<edm::TriggerResults>(iConfig.getUntrackedParameter<edm::InputTag>("triggerResults"))),
    triggerEventToken_(consumes<trigger::TriggerEvent>(iConfig.getUntrackedParameter<edm::InputTag>("triggerEvent"))),

    triggerEventWithRefsToken_(consumes<trigger::TriggerEventWithRefs>(iConfig.getUntrackedParameter<edm::InputTag>("triggerEventWithRefs")))

{

    edm::Service<TFileService> fs;
    tree_ = fs->make<TTree>("vbf", "vbf");

    if(fillingTriggers) branchesTriggers(tree_);
    if(fillingL1sFromHLT) branchesL1sFromHLT(tree_);
    if(fillingHLTFinalDecision) branchesHLTFinalDecision(tree_);
    if(fillingEventInfo) branchesEventInfo(tree_);
    if(fillingL1Primitives) branchesL1Taus(tree_);
    if(fillingL1Primitives) branchesL1Jets(tree_);
    if(fillingL1Primitives) branchesL1Electrons(tree_);
    if(fillingL1Primitives) branchesL1Muons(tree_);
    if(fillingTaus) branchesTaus(tree_);
    if(fillingJets) branchesJets(tree_);
    if(fillingElectrons) branchesElectrons(tree_);
    if(fillingMuons) branchesMuons(tree_);

}

NtupleMaker::~NtupleMaker(){
//destructor
}

bool DEBUG = false;
void NtupleMaker::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{

    //std::cout << "############## NEW EVENT! #################" << std::endl;
    if(fillingTriggers) {
      if (DEBUG) std::cout << "try to fill triggers" << std::endl;
      fillTriggers(iEvent);}

    if(fillingL1sFromHLT) {
      if (DEBUG) std::cout << "try to fill L1s from HLT" << std::endl;
      fillL1sFromHLT(iEvent);}

    if(fillingHLTFinalDecision) {
      if (DEBUG) std::cout << "try to fill HLT final decision" << std::endl;
      fillHLTFinalDecision(iEvent, DEBUG);}

    if(fillingEventInfo) {
      if (DEBUG) std::cout << "try to fill event info" << std::endl;
      fillEventInfo(iEvent);}

    if(fillingL1Primitives) {
      if (DEBUG) std::cout << "try to fill L1 taus" << std::endl;
      fillL1Taus(iEvent);}

    if(fillingL1Primitives) {
      if (DEBUG) std::cout << "try to fill L1 jets" << std::endl;
      fillL1Jets(iEvent);}

    if(fillingL1Primitives) {
      if (DEBUG) std::cout << "try to fill L1 electrons" << std::endl;
      fillL1Electrons(iEvent);}

    if(fillingL1Primitives) {
      if (DEBUG) std::cout << "try to fill L1 muons" << std::endl;
      fillL1Muons(iEvent);}

    if(fillingTaus) {
      if (DEBUG) std::cout << "try to fill offline taus" << std::endl;
      fillTaus(iEvent);}

    if(fillingJets) {
      if (DEBUG) std::cout << "try to fill offline jets" << std::endl;
      fillJets(iEvent, iSetup);}
 
    if(fillingElectrons) {
      if (DEBUG) std::cout << "try to fill offline electrons" << std::endl;
      fillElectrons(iEvent);}

    if(fillingMuons) {
      if (DEBUG) std::cout << "try to fill offline muons" << std::endl;
      fillMuons(iEvent);}

    tree_->Fill();
}

void NtupleMaker::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
    edm::ParameterSetDescription desc;
    desc.setUnknown();
    descriptions.addDefault(desc);
}

DEFINE_FWK_MODULE(NtupleMaker);
