#ifndef trigger_tree_h
#define trigger_tree_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <vector>

class trigger_tree {
public :
    TTree	*fChain;
    Int_t	fCurrent;

    // from HLT
    int runNumber;
    int lumiBlock;
    unsigned long long eventNumberID; // sometimes needs to be int for older samples...

    int nEvents;

    int passDeepDiTau35HLT;
    int passInclusiveVBFHLT;
    int passVBFPlusOneTauHLT;

    int passVBF2DTHLT;
    int passVBF2DTLooseNoL2NNHLT;
    int passVBF2DTOldL1;

    int passUpperControlMedHLT;
    int passLowerControlMedHLT;
    int passUpperControlHLT;
    int passLowerControlHLT;

    int pass2Tau1JetHLT;
    int passDiTauControl; 


    // DiTau HLT initial and final branches
    int passhltL1sDoubleTauBigOR;
    std::vector<float>* hltL1sDoubleTauBigOR_pt = nullptr;
    std::vector<float>* hltL1sDoubleTauBigOR_eta = nullptr;
    std::vector<float>* hltL1sDoubleTauBigOR_phi = nullptr;
    std::vector<float>* hltL1sDoubleTauBigOR_energy = nullptr;

    int passhltHpsDoublePFTau35TrackPt1TightChargedIsolationL1HLTMatchedReg;
    std::vector<float>* hltHpsDoublePFTau35TrackPt1TightChargedIsolationL1HLTMatchedReg_pt = nullptr;
    std::vector<float>* hltHpsDoublePFTau35TrackPt1TightChargedIsolationL1HLTMatchedReg_eta = nullptr;
    std::vector<float>* hltHpsDoublePFTau35TrackPt1TightChargedIsolationL1HLTMatchedReg_phi = nullptr;
    std::vector<float>* hltHpsDoublePFTau35TrackPt1TightChargedIsolationL1HLTMatchedReg_energy = nullptr;

    // Inclusive VBF and VBF Plus Two Tau Branches
    int passhltL1VBFDiJetOR;
    std::vector<float>* hltL1VBFDiJetOR_pt = nullptr;
    std::vector<float>* hltL1VBFDiJetOR_eta = nullptr;
    std::vector<float>* hltL1VBFDiJetOR_phi = nullptr;
    std::vector<float>* hltL1VBFDiJetOR_energy = nullptr;

    int passhltL1VBFDiJetIsoTau;
    std::vector<float>* hltL1VBFDiJetIsoTau_nJets = nullptr;
    std::vector<float>* hltL1VBFDiJetIsoTau_jetPt = nullptr;
    std::vector<float>* hltL1VBFDiJetIsoTau_jetEta = nullptr; 
    std::vector<float>* hltL1VBFDiJetIsoTau_jetPhi = nullptr; 
    std::vector<float>* hltL1VBFDiJetIsoTau_jetEnergy = nullptr; 
    std::vector<float>* hltL1VBFDiJetIsoTau_nTaus = nullptr;
    std::vector<float>* hltL1VBFDiJetIsoTau_tauPt = nullptr;
    std::vector<float>* hltL1VBFDiJetIsoTau_tauEta = nullptr; 
    std::vector<float>* hltL1VBFDiJetIsoTau_tauPhi = nullptr; 
    std::vector<float>* hltL1VBFDiJetIsoTau_tauEnergy = nullptr; 

    int passhltL1VBFDiJetIsoTauNoer;

    
    // VBF Plus Two Deep Tau Branches
    int passhltL2VBFIsoTauNNFilter;
    std::vector<float>* hltL2VBFIsoTauNNFilter_pt = nullptr;
    std::vector<float>* hltL2VBFIsoTauNNFilter_eta = nullptr;
    std::vector<float>* hltL2VBFIsoTauNNFilter_phi = nullptr;
    std::vector<float>* hltL2VBFIsoTauNNFilter_energy = nullptr;

    //
    int passhltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch;
    std::vector<float>* hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_pt = nullptr;
    std::vector<float>* hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_eta = nullptr;
    std::vector<float>* hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_phi = nullptr;
    std::vector<float>* hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_energy = nullptr;


    int passhltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatchNoL2NN;
    std::vector<float>* hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatchNoL2NN_pt = nullptr;
    std::vector<float>* hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatchNoL2NN_eta = nullptr;
    std::vector<float>* hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatchNoL2NN_phi = nullptr;
    std::vector<float>* hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatchNoL2NN_energy = nullptr;

    //
    int passhltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched;
    std::vector<float>* hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_pt = nullptr;
    std::vector<float>* hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_eta = nullptr;
    std::vector<float>* hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_phi = nullptr;
    std::vector<float>* hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_energy = nullptr;

    int passhltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatchedNoL2NN;
    std::vector<float>* hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatchedNoL2NN_pt = nullptr;
    std::vector<float>* hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatchedNoL2NN_eta = nullptr;
    std::vector<float>* hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatchedNoL2NN_phi = nullptr;
    std::vector<float>* hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatchedNoL2NN_energy = nullptr;

    //
    int passhltRealDijetFilter;
    std::vector<float>* hltRealDijetFilter_pt = nullptr;
    std::vector<float>* hltRealDijetFilter_eta = nullptr;
    std::vector<float>* hltRealDijetFilter_phi = nullptr;
    std::vector<float>* hltRealDijetFilter_energy = nullptr;

    int passhltVBFLooseIDPFDummyFilter;
    std::vector<float>* hltVBFLooseIDPFDummyFilter_pt = nullptr;
    std::vector<float>* hltVBFLooseIDPFDummyFilter_eta = nullptr;
    std::vector<float>* hltVBFLooseIDPFDummyFilter_phi = nullptr;
    std::vector<float>* hltVBFLooseIDPFDummyFilter_energy = nullptr;

    //
    int passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20;
    std::vector<float>* hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20_pt = nullptr;
    std::vector<float>* hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20_eta = nullptr;
    std::vector<float>* hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20_phi = nullptr;
    std::vector<float>* hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20_energy = nullptr;


    int passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20NoL2NN;
    std::vector<float>* hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20NoL2NN_pt = nullptr;
    std::vector<float>* hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20NoL2NN_eta = nullptr;
    std::vector<float>* hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20NoL2NN_phi = nullptr;
    std::vector<float>* hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20NoL2NN_energy = nullptr;

    int passhltHpsDoublePFTau20BeforeDeepTau;
    std::vector<float>* hltHpsDoublePFTau20BeforeDeepTau_pt = nullptr;
    std::vector<float>* hltHpsDoublePFTau20BeforeDeepTau_eta = nullptr;
    std::vector<float>* hltHpsDoublePFTau20BeforeDeepTau_phi = nullptr;
    std::vector<float>* hltHpsDoublePFTau20BeforeDeepTau_energy = nullptr;

    int passhltHpsDoublePFTau20withL2NNBeforeDeepTau;
    std::vector<float>* hltHpsDoublePFTau20withL2NNBeforeDeepTau_pt = nullptr;
    std::vector<float>* hltHpsDoublePFTau20withL2NNBeforeDeepTau_eta = nullptr;
    std::vector<float>* hltHpsDoublePFTau20withL2NNBeforeDeepTau_phi = nullptr;
    std::vector<float>* hltHpsDoublePFTau20withL2NNBeforeDeepTau_energy = nullptr;

    // end HLT branches

    // from AOD
    // trigger primitives
    std::vector<float>* tauL1PrimitivesPt = nullptr;    
    std::vector<float>* tauL1PrimitivesEta = nullptr;    
    std::vector<float>* tauL1PrimitivesPhi = nullptr;    
    std::vector<float>* tauL1PrimitivesEnergy = nullptr;    
    std::vector<int>* tauL1PrimitivesIso = nullptr;    

    std::vector<float>* jetL1PrimitivesPt = nullptr;    
    std::vector<float>* jetL1PrimitivesEta = nullptr;    
    std::vector<float>* jetL1PrimitivesPhi = nullptr;    
    std::vector<float>* jetL1PrimitivesEnergy = nullptr;    

    std::vector<float>* jetPt = nullptr;
    std::vector<float>* jetEta = nullptr;
    std::vector<float>* jetPhi = nullptr;
    std::vector<float>* jetEn = nullptr;
    std::vector<float>* tauPt = nullptr;
    std::vector<float>* tauEta = nullptr;
    std::vector<float>* tauPhi = nullptr;
    std::vector<float>* tauEnergy = nullptr;

    std::vector<float>* jetID = nullptr;
    std::vector<float>* tauByVVVLooseDeepTau2017v2p1VSe = nullptr;
    std::vector<float>* tauByTightDeepTau2017v2p1VSmu = nullptr;
    std::vector<float>* tauByVLooseDeepTau2017v2p1VSmu = nullptr;
    std::vector<float>* tauByMediumDeepTau2017v2p1VSjet = nullptr;
    std::vector<float>* tauByVVVLooseDeepTau2017v2p1VSjet = nullptr;
    // end AOD branches
    //int 	nTau;

    trigger_tree(TTree *tree=0);
    virtual ~trigger_tree();
    virtual void	Init(TTree *tree);
    virtual Int_t	GetEntry(Long64_t entry);
    virtual Long64_t	GetEntries();
    TTree* GetTree();
};

trigger_tree::trigger_tree(TTree *tree) : fChain(0)
{
    Init(tree);
}

trigger_tree::~trigger_tree()
{

}

Int_t trigger_tree::GetEntry(Long64_t entry)
{
    if (!fChain) return 0;
    return fChain->GetEntry(entry);
}

Long64_t trigger_tree::GetEntries()
{
    return fChain->GetEntries();
}

TTree* trigger_tree::GetTree()
{
    return fChain;
}

void trigger_tree::Init(TTree *tree)
{
    if (!tree) return;
    fChain = tree;
    fCurrent = -1;

    // from HLT
    fChain->SetBranchAddress("runNumber", &runNumber);
    fChain->SetBranchAddress("lumiBlock", &lumiBlock);
    fChain->SetBranchAddress("eventNumberID", &eventNumberID);
    fChain->SetBranchAddress("nEvents", &nEvents);

    fChain->SetBranchAddress("passDeepDiTau35HLT", &passDeepDiTau35HLT);
    fChain->SetBranchAddress("passInclusiveVBFHLT", &passInclusiveVBFHLT);
    fChain->SetBranchAddress("passVBFPlusOneTauHLT", &passVBFPlusOneTauHLT);

    fChain->SetBranchAddress("passVBF2DTHLT", &passVBF2DTHLT);
    fChain->SetBranchAddress("passVBF2DTLooseNoL2NNHLT", &passVBF2DTLooseNoL2NNHLT);
    fChain->SetBranchAddress("passVBF2DTOldL1", &passVBF2DTOldL1);

    fChain->SetBranchAddress("passUpperControlMedHLT", &passUpperControlMedHLT);
    fChain->SetBranchAddress("passLowerControlMedHLT", &passLowerControlMedHLT);
    fChain->SetBranchAddress("passUpperControlHLT", &passUpperControlHLT);
    fChain->SetBranchAddress("passLowerControlHLT", &passLowerControlHLT);
    
    fChain->SetBranchAddress("pass2Tau1JetHLT", &pass2Tau1JetHLT);
    fChain->SetBranchAddress("passDiTauControl", &passDiTauControl);

    // DiTau HLT initial and final branches
    fChain->SetBranchAddress("passhltL1sDoubleTauBigOR", &passhltL1sDoubleTauBigOR);
    fChain->SetBranchAddress("hltL1sDoubleTauBigOR_pt", &hltL1sDoubleTauBigOR_pt);
    fChain->SetBranchAddress("hltL1sDoubleTauBigOR_eta", &hltL1sDoubleTauBigOR_eta);
    fChain->SetBranchAddress("hltL1sDoubleTauBigOR_phi", &hltL1sDoubleTauBigOR_phi);
    fChain->SetBranchAddress("hltL1sDoubleTauBigOR_energy", &hltL1sDoubleTauBigOR_energy);


    // Inclusive VBF and VBF Plus Two Tau Branches
    fChain->SetBranchAddress("passhltL1VBFDiJetOR", &passhltL1VBFDiJetOR);
    fChain->SetBranchAddress("hltL1VBFDiJetOR_pt", &hltL1VBFDiJetOR_pt);
    fChain->SetBranchAddress("hltL1VBFDiJetOR_eta", &hltL1VBFDiJetOR_eta);
    fChain->SetBranchAddress("hltL1VBFDiJetOR_phi", &hltL1VBFDiJetOR_phi);
    fChain->SetBranchAddress("hltL1VBFDiJetOR_energy", &hltL1VBFDiJetOR_energy);

    fChain->SetBranchAddress("passhltL1VBFDiJetIsoTau", &passhltL1VBFDiJetIsoTau);
    fChain->SetBranchAddress("hltL1VBFDiJetIsoTau_nJets", &hltL1VBFDiJetIsoTau_nJets);
    fChain->SetBranchAddress("hltL1VBFDiJetIsoTau_jetPt", &hltL1VBFDiJetIsoTau_jetPt);
    fChain->SetBranchAddress("hltL1VBFDiJetIsoTau_jetEta", &hltL1VBFDiJetIsoTau_jetEta);
    fChain->SetBranchAddress("hltL1VBFDiJetIsoTau_jetPhi", &hltL1VBFDiJetIsoTau_jetPhi);
    fChain->SetBranchAddress("hltL1VBFDiJetIsoTau_jetEnergy", &hltL1VBFDiJetIsoTau_jetEnergy);
    fChain->SetBranchAddress("hltL1VBFDiJetIsoTau_nTaus", &hltL1VBFDiJetIsoTau_nTaus);
    fChain->SetBranchAddress("hltL1VBFDiJetIsoTau_tauPt", &hltL1VBFDiJetIsoTau_tauPt);
    fChain->SetBranchAddress("hltL1VBFDiJetIsoTau_tauEta", &hltL1VBFDiJetIsoTau_tauEta);
    fChain->SetBranchAddress("hltL1VBFDiJetIsoTau_tauPhi", &hltL1VBFDiJetIsoTau_tauPhi);
    fChain->SetBranchAddress("hltL1VBFDiJetIsoTau_tauEnergy", &hltL1VBFDiJetIsoTau_tauEnergy);

    fChain->SetBranchAddress("passhltL1VBFDiJetIsoTauNoer", &passhltL1VBFDiJetIsoTauNoer);

    // VBF Plus Two Deep Tau Branches
    fChain->SetBranchAddress("passhltL2VBFIsoTauNNFilter", &passhltL2VBFIsoTauNNFilter);
    fChain->SetBranchAddress("hltL2VBFIsoTauNNFilter_pt", &hltL2VBFIsoTauNNFilter_pt);
    fChain->SetBranchAddress("hltL2VBFIsoTauNNFilter_eta", &hltL2VBFIsoTauNNFilter_eta);
    fChain->SetBranchAddress("hltL2VBFIsoTauNNFilter_phi", &hltL2VBFIsoTauNNFilter_phi);
    fChain->SetBranchAddress("hltL2VBFIsoTauNNFilter_energy", &hltL2VBFIsoTauNNFilter_energy);

    //
    fChain->SetBranchAddress("passhltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch", &passhltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch);
    fChain->SetBranchAddress("hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_pt", &hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_pt);
    fChain->SetBranchAddress("hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_eta", &hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_eta);
    fChain->SetBranchAddress("hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_phi", &hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_phi);
    fChain->SetBranchAddress("hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_energy", &hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_energy);



    fChain->SetBranchAddress("passhltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatchNoL2NN", &passhltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatchNoL2NN);
    fChain->SetBranchAddress("hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatchNoL2NN_pt", &hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatchNoL2NN_pt);
    fChain->SetBranchAddress("hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatchNoL2NN_eta", &hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatchNoL2NN_eta);
    fChain->SetBranchAddress("hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatchNoL2NN_phi", &hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatchNoL2NN_phi);
    fChain->SetBranchAddress("hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatchNoL2NN_energy", &hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatchNoL2NN_energy);

    //
    fChain->SetBranchAddress("passhltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched", &passhltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched);
    fChain->SetBranchAddress("hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_pt", &hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_pt);
    fChain->SetBranchAddress("hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_eta", &hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_eta);
    fChain->SetBranchAddress("hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_phi", &hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_phi);
    fChain->SetBranchAddress("hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_energy", &hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_energy);



    fChain->SetBranchAddress("passhltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatchedNoL2NN", &passhltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatchedNoL2NN);
    fChain->SetBranchAddress("hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatchedNoL2NN_pt", &hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatchedNoL2NN_pt);
    fChain->SetBranchAddress("hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatchedNoL2NN_eta", &hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatchedNoL2NN_eta);
    fChain->SetBranchAddress("hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatchedNoL2NN_phi", &hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatchedNoL2NN_phi);
    fChain->SetBranchAddress("hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatchedNoL2NN_energy", &hltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatchedNoL2NN_energy);

    //
    fChain->SetBranchAddress("passhltRealDijetFilter", &passhltRealDijetFilter);
    fChain->SetBranchAddress("hltRealDijetFilter_pt", &hltRealDijetFilter_pt);
    fChain->SetBranchAddress("hltRealDijetFilter_eta", &hltRealDijetFilter_eta);
    fChain->SetBranchAddress("hltRealDijetFilter_phi", &hltRealDijetFilter_phi);
    fChain->SetBranchAddress("hltRealDijetFilter_energy", &hltRealDijetFilter_energy);

    fChain->SetBranchAddress("passhltVBFLooseIDPFDummyFilter", &passhltVBFLooseIDPFDummyFilter);
    fChain->SetBranchAddress("hltVBFLooseIDPFDummyFilter_pt", &hltVBFLooseIDPFDummyFilter_pt);
    fChain->SetBranchAddress("hltVBFLooseIDPFDummyFilter_eta", &hltVBFLooseIDPFDummyFilter_eta);
    fChain->SetBranchAddress("hltVBFLooseIDPFDummyFilter_phi", &hltVBFLooseIDPFDummyFilter_phi);
    fChain->SetBranchAddress("hltVBFLooseIDPFDummyFilter_energy", &hltVBFLooseIDPFDummyFilter_energy);

    //
    fChain->SetBranchAddress("passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20", &passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20);
    fChain->SetBranchAddress("hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20_pt", &hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20_pt);
    fChain->SetBranchAddress("hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20_eta", &hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20_eta);
    fChain->SetBranchAddress("hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20_phi", &hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20_phi);
    fChain->SetBranchAddress("hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20_energy", &hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20_energy);

    fChain->SetBranchAddress("passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20NoL2NN", &passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20NoL2NN);
    fChain->SetBranchAddress("hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20NoL2NN_pt", &hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20NoL2NN_pt);
    fChain->SetBranchAddress("hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20NoL2NN_eta", &hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20NoL2NN_eta);
    fChain->SetBranchAddress("hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20NoL2NN_phi", &hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20NoL2NN_phi);
    fChain->SetBranchAddress("hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20NoL2NN_energy", &hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20NoL2NN_energy);

    fChain->SetBranchAddress("passhltHpsDoublePFTau20BeforeDeepTau", &passhltHpsDoublePFTau20BeforeDeepTau);
    fChain->SetBranchAddress("hltHpsDoublePFTau20BeforeDeepTau_pt", &hltHpsDoublePFTau20BeforeDeepTau_pt);
    fChain->SetBranchAddress("hltHpsDoublePFTau20BeforeDeepTau_eta", &hltHpsDoublePFTau20BeforeDeepTau_eta);
    fChain->SetBranchAddress("hltHpsDoublePFTau20BeforeDeepTau_phi", &hltHpsDoublePFTau20BeforeDeepTau_phi);
    fChain->SetBranchAddress("hltHpsDoublePFTau20BeforeDeepTau_energy", &hltHpsDoublePFTau20BeforeDeepTau_energy);

    fChain->SetBranchAddress("passhltHpsDoublePFTau20withL2NNBeforeDeepTau", &passhltHpsDoublePFTau20withL2NNBeforeDeepTau);
    fChain->SetBranchAddress("hltHpsDoublePFTau20withL2NNBeforeDeepTau_pt", &hltHpsDoublePFTau20withL2NNBeforeDeepTau_pt);
    fChain->SetBranchAddress("hltHpsDoublePFTau20withL2NNBeforeDeepTau_eta", &hltHpsDoublePFTau20withL2NNBeforeDeepTau_eta);
    fChain->SetBranchAddress("hltHpsDoublePFTau20withL2NNBeforeDeepTau_phi", &hltHpsDoublePFTau20withL2NNBeforeDeepTau_phi);
    fChain->SetBranchAddress("hltHpsDoublePFTau20withL2NNBeforeDeepTau_energy", &hltHpsDoublePFTau20withL2NNBeforeDeepTau_energy);


    // from AOD
    // trigger primitives
    fChain->SetBranchAddress("tauL1PrimitivesPt", &tauL1PrimitivesPt);
    fChain->SetBranchAddress("tauL1PrimitivesEta", &tauL1PrimitivesEta);
    fChain->SetBranchAddress("tauL1PrimitivesPhi", &tauL1PrimitivesPhi);
    fChain->SetBranchAddress("tauL1PrimitivesEnergy", &tauL1PrimitivesEnergy);
    fChain->SetBranchAddress("tauL1PrimitivesIso", &tauL1PrimitivesIso);

    fChain->SetBranchAddress("jetL1PrimitivesPt", &jetL1PrimitivesPt);
    fChain->SetBranchAddress("jetL1PrimitivesEta", &jetL1PrimitivesEta);
    fChain->SetBranchAddress("jetL1PrimitivesPhi", &jetL1PrimitivesPhi);
    fChain->SetBranchAddress("jetL1PrimitivesEnergy", &jetL1PrimitivesEnergy);

    fChain->SetBranchAddress("jetPt", &jetPt);
    fChain->SetBranchAddress("jetEta", &jetEta);
    fChain->SetBranchAddress("jetPhi", &jetPhi);
    fChain->SetBranchAddress("jetEn", &jetEn);
    fChain->SetBranchAddress("tauPt", &tauPt);
    fChain->SetBranchAddress("tauEta", &tauEta);
    fChain->SetBranchAddress("tauPhi", &tauPhi);
    fChain->SetBranchAddress("tauEnergy", &tauEnergy);
    
    fChain->SetBranchAddress("jetID", &jetID);
    fChain->SetBranchAddress("tauByVVVLooseDeepTau2017v2p1VSe", &tauByVVVLooseDeepTau2017v2p1VSe);
    fChain->SetBranchAddress("tauByTightDeepTau2017v2p1VSmu", &tauByTightDeepTau2017v2p1VSmu);
    fChain->SetBranchAddress("tauByVLooseDeepTau2017v2p1VSmu", &tauByVLooseDeepTau2017v2p1VSmu);
    fChain->SetBranchAddress("tauByVVVLooseDeepTau2017v2p1VSjet", &tauByVVVLooseDeepTau2017v2p1VSjet);
    fChain->SetBranchAddress("tauByMediumDeepTau2017v2p1VSjet", &tauByMediumDeepTau2017v2p1VSjet);
    // end AOD
}

#endif
