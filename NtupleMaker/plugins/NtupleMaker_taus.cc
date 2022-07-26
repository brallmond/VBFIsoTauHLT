// Updated by Abdollah Mohammadi (KSU)  [18 May 2015]
// abdollah.mohammadi@cern.ch

#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "VBFIsoTauHLT/NtupleMaker/plugins/NtupleMaker.h"

using namespace std;

// (local) variables associated with tree branches
Int_t          nTau_;

int runNumber;
int lumiBlock;
unsigned long long eventNumberID;

// decay mode discriminators

// Tau L1 Primitives
vector<float> 	tauL1PrimitivesPt_;
vector<float> 	tauL1PrimitivesEta_;
vector<float> 	tauL1PrimitivesPhi_;
vector<float> 	tauL1PrimitivesEnergy_;
vector<int> 	tauL1PrimitivesIso_;

//Tau Id & Isolation

vector<bool>    tauByVVVLooseDeepTau2017v2p1VSjet_;
vector<bool>    tauByVVLooseDeepTau2017v2p1VSjet_;
vector<bool>    tauByVLooseDeepTau2017v2p1VSjet_;
vector<bool>    tauByLooseDeepTau2017v2p1VSjet_;
vector<bool>    tauByMediumDeepTau2017v2p1VSjet_;
vector<bool>    tauByTightDeepTau2017v2p1VSjet_;
vector<bool>    tauByVTightDeepTau2017v2p1VSjet_;
vector<bool>    tauByVVTightDeepTau2017v2p1VSjet_;

vector<bool>    tauByVVVLooseDeepTau2017v2p1VSe_;
vector<bool>    tauByVVLooseDeepTau2017v2p1VSe_;
vector<bool>    tauByVLooseDeepTau2017v2p1VSe_;
vector<bool>    tauByLooseDeepTau2017v2p1VSe_;
vector<bool>    tauByMediumDeepTau2017v2p1VSe_;
vector<bool>    tauByTightDeepTau2017v2p1VSe_;
vector<bool>    tauByVTightDeepTau2017v2p1VSe_;
vector<bool>    tauByVVTightDeepTau2017v2p1VSe_;

vector<bool>    tauByVVVLooseDeepTau2017v2p1VSmu_;
vector<bool>    tauByVLooseDeepTau2017v2p1VSmu_;
vector<bool>    tauByLooseDeepTau2017v2p1VSmu_;
vector<bool>    tauByMediumDeepTau2017v2p1VSmu_;
vector<bool>    tauByTightDeepTau2017v2p1VSmu_;


vector<int> tauPDGID_;


//Tau Kinematics
vector<float> tauPt_;
vector<float> tauEta_;
vector<float> tauPhi_;
vector<float> tauEnergy_;
vector<float> tauCharge_;


void NtupleMaker::branchesEventInfo(TTree* tree)
{
    tree->Branch("runNumber", &runNumber);
    tree->Branch("lumiBlock", &lumiBlock);
    tree->Branch("eventNumberID", &eventNumberID);
}

void NtupleMaker::branchesL1Taus(TTree* tree) 
{
    tree->Branch("tauL1PrimitivesPt", &tauL1PrimitivesPt_);
    tree->Branch("tauL1PrimitivesEta", &tauL1PrimitivesEta_);
    tree->Branch("tauL1PrimitivesPhi", &tauL1PrimitivesPhi_);
    tree->Branch("tauL1PrimitivesEnergy", &tauL1PrimitivesEnergy_);
    tree->Branch("tauL1PrimitivesIso", &tauL1PrimitivesIso_);
}

void NtupleMaker::branchesTaus(TTree* tree)
{

    tree->Branch("nTau", &nTau_);
    
    //Tau Id & Isolation


    tree->Branch("tauByVVVLooseDeepTau2017v2p1VSjet", &tauByVVVLooseDeepTau2017v2p1VSjet_);
    tree->Branch("tauByVVLooseDeepTau2017v2p1VSjet", &tauByVVLooseDeepTau2017v2p1VSjet_);
    tree->Branch("tauByVLooseDeepTau2017v2p1VSjet", &tauByVLooseDeepTau2017v2p1VSjet_);
    tree->Branch("tauByLooseDeepTau2017v2p1VSjet", &tauByLooseDeepTau2017v2p1VSjet_);
    tree->Branch("tauByMediumDeepTau2017v2p1VSjet", &tauByMediumDeepTau2017v2p1VSjet_);
    tree->Branch("tauByTightDeepTau2017v2p1VSjet", &tauByTightDeepTau2017v2p1VSjet_);
    tree->Branch("tauByVTightDeepTau2017v2p1VSjet", &tauByVTightDeepTau2017v2p1VSjet_);
    tree->Branch("tauByVVTightDeepTau2017v2p1VSjet", &tauByVVTightDeepTau2017v2p1VSjet_);

    tree->Branch("tauByVVVLooseDeepTau2017v2p1VSe", &tauByVVVLooseDeepTau2017v2p1VSe_);
    tree->Branch("tauByVVLooseDeepTau2017v2p1VSe", &tauByVVLooseDeepTau2017v2p1VSe_);
    tree->Branch("tauByVLooseDeepTau2017v2p1VSe", &tauByVLooseDeepTau2017v2p1VSe_);
    tree->Branch("tauByLooseDeepTau2017v2p1VSe", &tauByLooseDeepTau2017v2p1VSe_);
    tree->Branch("tauByMediumDeepTau2017v2p1VSe", &tauByMediumDeepTau2017v2p1VSe_);
    tree->Branch("tauByTightDeepTau2017v2p1VSe", &tauByTightDeepTau2017v2p1VSe_);
    tree->Branch("tauByVTightDeepTau2017v2p1VSe", &tauByVTightDeepTau2017v2p1VSe_);
    tree->Branch("tauByVVTightDeepTau2017v2p1VSe", &tauByVVTightDeepTau2017v2p1VSe_);

    tree->Branch("tauByVVVLooseDeepTau2017v2p1VSmu", &tauByVVVLooseDeepTau2017v2p1VSmu_);
    tree->Branch("tauByVLooseDeepTau2017v2p1VSmu", &tauByVLooseDeepTau2017v2p1VSmu_);
    tree->Branch("tauByLooseDeepTau2017v2p1VSmu", &tauByLooseDeepTau2017v2p1VSmu_);
    tree->Branch("tauByMediumDeepTau2017v2p1VSmu", &tauByMediumDeepTau2017v2p1VSmu_);
    tree->Branch("tauByTightDeepTau2017v2p1VSmu", &tauByTightDeepTau2017v2p1VSmu_);

    tree->Branch("tauPDGID", &tauPDGID_);
 
 
    //Tau Kinematics
    tree->Branch("tauPt", &tauPt_);
    tree->Branch("tauEta", &tauEta_);
    tree->Branch("tauPhi", &tauPhi_);
    tree->Branch("tauEnergy", &tauEnergy_);
    tree->Branch("tauCharge", &tauCharge_);
    
    
    
}

void NtupleMaker::fillEventInfo(const edm::Event& iEvent)
{
    runNumber = iEvent.id().run();
    lumiBlock = iEvent.id().luminosityBlock();
    eventNumberID = iEvent.id().event();
}

void NtupleMaker::fillL1Taus(const edm::Event& iEvent)
{
    tauL1PrimitivesPt_.clear();
    tauL1PrimitivesEta_.clear();
    tauL1PrimitivesPhi_.clear();
    tauL1PrimitivesEnergy_.clear();
    tauL1PrimitivesIso_.clear();

    edm::Handle<BXVector<l1t::Tau>> tauL1Handle;
    iEvent.getByToken(tauTriggerPrimitives_, tauL1Handle);

    for(BXVector<l1t::Tau>::const_iterator itau = tauL1Handle->begin(0); itau != tauL1Handle->end(0); ++itau) {
        tauL1PrimitivesPt_.push_back(itau->pt());
        tauL1PrimitivesEta_.push_back(itau->eta());
        tauL1PrimitivesPhi_.push_back(itau->phi());
        tauL1PrimitivesEnergy_.push_back(itau->energy());
        tauL1PrimitivesIso_.push_back(itau->hwIso());
    }

}

void NtupleMaker::fillTaus(const edm::Event& e)
{
    // Tau Id & Isolation

    tauByVVVLooseDeepTau2017v2p1VSjet_.clear();
    tauByVVLooseDeepTau2017v2p1VSjet_.clear();
    tauByVLooseDeepTau2017v2p1VSjet_.clear();
    tauByLooseDeepTau2017v2p1VSjet_.clear();
    tauByMediumDeepTau2017v2p1VSjet_.clear();
    tauByTightDeepTau2017v2p1VSjet_.clear();
    tauByVTightDeepTau2017v2p1VSjet_.clear();
    tauByVVTightDeepTau2017v2p1VSjet_.clear();

    tauByVVVLooseDeepTau2017v2p1VSe_.clear();
    tauByVVLooseDeepTau2017v2p1VSe_.clear();
    tauByVLooseDeepTau2017v2p1VSe_.clear();
    tauByLooseDeepTau2017v2p1VSe_.clear();
    tauByMediumDeepTau2017v2p1VSe_.clear();
    tauByTightDeepTau2017v2p1VSe_.clear();
    tauByVTightDeepTau2017v2p1VSe_.clear();
    tauByVVTightDeepTau2017v2p1VSe_.clear();

    tauByVVVLooseDeepTau2017v2p1VSmu_.clear();
    tauByVLooseDeepTau2017v2p1VSmu_.clear();
    tauByLooseDeepTau2017v2p1VSmu_.clear();
    tauByMediumDeepTau2017v2p1VSmu_.clear();
    tauByTightDeepTau2017v2p1VSmu_.clear();    

    tauPDGID_.clear();

    //Tau Kinematics
    tauPt_.clear();
    tauEta_.clear();
    tauPhi_.clear();
    tauEnergy_.clear();
    tauCharge_.clear();
    
    
    nTau_ = 0;
    
    //original Tau lines

    edm::Handle<vector<pat::Tau> > tauHandle;
    e.getByToken(tauCollection_, tauHandle);
    
    if (!tauHandle.isValid()) {
        edm::LogWarning("ggNtuplizer") << "no pat::Tau in event";
        return;
    }
    
    //startTaus 
    for(vector<pat::Tau>::const_iterator itau = tauHandle->begin(); itau != tauHandle->end(); ++itau) {
        
        // Tau Id & Isolation
        tauByVVVLooseDeepTau2017v2p1VSjet_.push_back(itau->tauID("byVVVLooseDeepTau2017v2p1VSjet"));
        tauByVVLooseDeepTau2017v2p1VSjet_.push_back(itau->tauID("byVVLooseDeepTau2017v2p1VSjet"));
        tauByVLooseDeepTau2017v2p1VSjet_.push_back(itau->tauID("byVLooseDeepTau2017v2p1VSjet"));
        tauByLooseDeepTau2017v2p1VSjet_.push_back(itau->tauID("byLooseDeepTau2017v2p1VSjet"));
        tauByMediumDeepTau2017v2p1VSjet_.push_back(itau->tauID("byMediumDeepTau2017v2p1VSjet"));
        tauByTightDeepTau2017v2p1VSjet_.push_back(itau->tauID("byTightDeepTau2017v2p1VSjet"));
        tauByVTightDeepTau2017v2p1VSjet_.push_back(itau->tauID("byVTightDeepTau2017v2p1VSjet"));
        tauByVVTightDeepTau2017v2p1VSjet_.push_back(itau->tauID("byVVTightDeepTau2017v2p1VSjet"));

        tauByVVVLooseDeepTau2017v2p1VSe_.push_back(itau->tauID("byVVVLooseDeepTau2017v2p1VSe"));
        tauByVVLooseDeepTau2017v2p1VSe_.push_back(itau->tauID("byVVLooseDeepTau2017v2p1VSe"));
        tauByVLooseDeepTau2017v2p1VSe_.push_back(itau->tauID("byVLooseDeepTau2017v2p1VSe"));
        tauByLooseDeepTau2017v2p1VSe_.push_back(itau->tauID("byLooseDeepTau2017v2p1VSe"));
        tauByMediumDeepTau2017v2p1VSe_.push_back(itau->tauID("byMediumDeepTau2017v2p1VSe"));
        tauByTightDeepTau2017v2p1VSe_.push_back(itau->tauID("byTightDeepTau2017v2p1VSe"));
        tauByVTightDeepTau2017v2p1VSe_.push_back(itau->tauID("byVTightDeepTau2017v2p1VSe"));
        tauByVVTightDeepTau2017v2p1VSe_.push_back(itau->tauID("byVVTightDeepTau2017v2p1VSe"));

        tauByVVVLooseDeepTau2017v2p1VSmu_.push_back(itau->tauID("byVVVLooseDeepTau2017v2p1VSmu"));
        tauByVLooseDeepTau2017v2p1VSmu_.push_back(itau->tauID("byVLooseDeepTau2017v2p1VSmu"));
        tauByLooseDeepTau2017v2p1VSmu_.push_back(itau->tauID("byLooseDeepTau2017v2p1VSmu"));
        tauByMediumDeepTau2017v2p1VSmu_.push_back(itau->tauID("byMediumDeepTau2017v2p1VSmu"));
        tauByTightDeepTau2017v2p1VSmu_.push_back(itau->tauID("byTightDeepTau2017v2p1VSmu"));
   
        tauPDGID_.push_back(itau->pdgId());
    
        //tauGen_.push_back(itau->genParticle());
        
        //Tau Kinematics
        tauPt_.push_back(itau->pt());
        tauEta_.push_back(itau->eta());
        tauPhi_.push_back(itau->phi());
        tauEnergy_.push_back(itau->energy());
        tauCharge_.push_back(itau->charge());

        
        
        ++nTau_;
        
    } // loop over tau candidates
    
}
