#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <vector>
#include <set>
#include <string>
#include <iomanip>
#include <tuple>

#include "TH1F.h"
#include "TTree.h"
#include "TChain.h"
#include "TFile.h"
#include "TLorentzVector.h"

#include "trigger_tree.h"
#include "trigger_functions.h"

// example running on wisc server: ./trigger_selection.exe /hdfs/store/user/ballmond/merged_trigger_05092020/merged.root ./output.root new

int main(int argc, char** argv)	{

    // Open input file and make new output file, also declare necessary variables
    std::string inName = *(argv + 1);
    std::string outName = *(argv + 2);

    TFile *fIn = TFile::Open(inName.c_str());
    TTree* treePtr = (TTree*) fIn->Get("demo/vbf");
    trigger_tree* inTree = new trigger_tree (treePtr);

    TTree *outTree = new TTree("outTree", "outTree");
    outTree->SetDirectory(0);

    // run variables and branches
    int nEvents, runNumber, lumiBlock, eventNumberID, lumisSize;
    outTree->Branch("nEvents", &nEvents);
    outTree->Branch("runNumber", &runNumber);
    outTree->Branch("lumiBlock", &lumiBlock);
    outTree->Branch("lumisSize", &lumisSize);
    outTree->Branch("eventNumberID", &eventNumberID);

    // AOD variables and branches
    float j1_ptAOD, j1_etaAOD, j1_phiAOD, j1_energyAOD; 
    float j2_ptAOD, j2_etaAOD, j2_phiAOD, j2_energyAOD; 
    float mjjAOD;
    float t1_ptAOD, t1_etaAOD, t1_phiAOD, t1_energyAOD;
    float t2_ptAOD, t2_etaAOD, t2_phiAOD, t2_energyAOD;
    int deepTauVSjet, deepTauVSmu, deepTauVSele, jetID;
    outTree->Branch("j1_ptAOD", &j1_ptAOD);
    outTree->Branch("j1_etaAOD", &j1_etaAOD);
    outTree->Branch("j1_phiAOD", &j1_phiAOD);
    outTree->Branch("j2_ptAOD", &j2_ptAOD);
    outTree->Branch("j2_etaAOD", &j2_etaAOD);
    outTree->Branch("j2_phiAOD", &j2_phiAOD);
    outTree->Branch("mjjAOD", &mjjAOD);
    outTree->Branch("t1_ptAOD", &t1_ptAOD);
    outTree->Branch("t1_etaAOD", &t1_etaAOD);
    outTree->Branch("t1_phiAOD", &t1_phiAOD);
    outTree->Branch("t2_ptAOD", &t2_ptAOD);
    outTree->Branch("t2_etaAOD", &t2_etaAOD);
    outTree->Branch("t2_phiAOD", &t2_phiAOD);
    outTree->Branch("deepTauVSjet", &deepTauVSjet);
    outTree->Branch("deepTauVSmu", &deepTauVSmu);
    outTree->Branch("deepTauVSele", &deepTauVSele);
    outTree->Branch("jetID", &jetID);
    // no branches for energy

    // L1s
    int passhltL1VBFDiJetOR;
    int passhltL1VBFDiJetIsoTau;
    int passhltL1VBFDiJetIsoTauNoer;
    outTree->Branch("passhltL1VBFDiJetOR", &passhltL1VBFDiJetOR);
    outTree->Branch("passhltL1VBFDiJetIsoTau", &passhltL1VBFDiJetIsoTau);
    outTree->Branch("passhltL1VBFDiJetIsoTauNoer", &passhltL1VBFDiJetIsoTauNoer);

    int passDiTau32L1, passDiTau34L1, passDiTau35L1;
    outTree->Branch("passDiTau32L1", &passDiTau32L1);
    outTree->Branch("passDiTau34L1", &passDiTau34L1);
    outTree->Branch("passDiTau35L1", &passDiTau35L1);

    // HLTs
    int passInclusiveVBFHLT, passVBF2DTHLT, passVBF2DTLooseHLT, passVBF2DTOldL1;
    int passDiTau35HLT, passDeepDiTau35HLT;
    outTree->Branch("passInclusiveVBFHLT", &passInclusiveVBFHLT);
    outTree->Branch("passVBF2DTHLT", &passVBF2DTHLT);
    outTree->Branch("passVBF2DTLooseHLT", &passVBF2DTLooseHLT);
    outTree->Branch("passVBF2DTOldL1", &passVBF2DTOldL1);
    outTree->Branch("passDiTau35HLT", &passDiTau35HLT);
    outTree->Branch("passDeepDiTau35HLT", &passDeepDiTau35HLT);

    // controls and Spain HLT
    int passUpperControlMedHLT, passLowerControlMedHLT;
    int passUpperControlHLT, passLowerControlHLT;
    int passDiTauControlHLT, pass2Tau1JetHLT;
    outTree->Branch("passUpperControlMedHLT", &passUpperControlMedHLT);
    outTree->Branch("passLowerControlMedHLT", &passLowerControlMedHLT);
    outTree->Branch("passUpperControlHLT", &passUpperControlHLT);
    outTree->Branch("passLowerControlHLT", &passLowerControlHLT);
    outTree->Branch("passDiTauControlHLT", &passDiTauControlHLT);
    outTree->Branch("pass2Tau1JetHLT", &pass2Tau1JetHLT);

    // Offlines
    int passInclusiveVBFOff, passVBF2DTOff, passDiTau35Off;  
    int pass2Tau1JetOff;
    outTree->Branch("passInclusiveVBFOff", &passInclusiveVBFOff);
    outTree->Branch("passVBF2DTOff", &passVBF2DTOff);
    outTree->Branch("passDiTau35Off", &passDiTau35Off);
    outTree->Branch("pass2Tau1JetOff", &pass2Tau1JetOff);

    // modules for VBF2DTMediumL2NN Cutflow
    int passhltL2VBFIsoTauNNFilter;
    int passhltHpsDoublePFTau20withL2NNBeforeDeepTau;
    int passhltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch;
    int passhltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched;
    int passhltRealDijetFilter;
    int passhltVBFLooseIDPFDummyFilter;
    int passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20;
    outTree->Branch("passhltL2VBFIsoTauNNFilter", &passhltL2VBFIsoTauNNFilter);
    outTree->Branch("passhltHpsDoublePFTau20withL2NNBeforeDeepTau", &passhltHpsDoublePFTau20withL2NNBeforeDeepTau);
    outTree->Branch("passhltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch", &passhltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch);
    outTree->Branch("passhltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched", &passhltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched);
    outTree->Branch("passhltRealDijetFilter", &passhltRealDijetFilter);
    outTree->Branch("passhltVBFLooseIDPFDummyFilter", &passhltVBFLooseIDPFDummyFilter);
    outTree->Branch("passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20", &passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20);


    // modules for VBF2DTLoose Cutflow (NoL2NN, module names in trigger tree can't be updated until ConfDB is)
    int passhltHpsDoublePFTau20BeforeDeepTau;
    int passhltHpsDoublePFTau20LooseDitauWPDeepTauNoMatch_VBF2DTLoose;
    int passhltHpsSinglePFTau45LooseDitauWPDeepTauL1HLTMatched_VBF2DTLoose;
    int passhltRealDijetFilter_VBF2DTLoose;
    int passhltVBFLooseIDPFDummyFilter_VBF2DTLoose;
    int passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsLooseDeepTauIsoPFTauHPS20_VBF2DTLoose;
    outTree->Branch("passhltHpsDoublePFTau20BeforeDeepTau", &passhltHpsDoublePFTau20BeforeDeepTau);
    outTree->Branch("passhltHpsDoublePFTau20LooseDitauWPDeepTauNoMatch_VBF2DTLoose", &passhltHpsDoublePFTau20LooseDitauWPDeepTauNoMatch_VBF2DTLoose);
    outTree->Branch("passhltHpsSinglePFTau45LooseDitauWPDeepTauL1HLTMatched_VBF2DTLoose", &passhltHpsSinglePFTau45LooseDitauWPDeepTauL1HLTMatched_VBF2DTLoose);
    outTree->Branch("passhltRealDijetFilter_VBF2DTLoose", &passhltRealDijetFilter_VBF2DTLoose);
    outTree->Branch("passhltVBFLooseIDPFDummyFilter_VBF2DTLoose", &passhltVBFLooseIDPFDummyFilter_VBF2DTLoose);
    outTree->Branch("passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsLooseDeepTauIsoPFTauHPS20_VBF2DTLoose", &passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsLooseDeepTauIsoPFTauHPS20_VBF2DTLoose);


    // flags for viable event and matching objects

    int viableTaus, viableJets;
    outTree->Branch("viableTaus", &viableTaus);
    outTree->Branch("viableJets", &viableJets); 

    int matchedL1Jets;
    int matchedL1Tau;
    outTree->Branch("matchedL1Jets", &matchedL1Jets);
    outTree->Branch("matchedL1Tau", &matchedL1Tau);

    int matchedHLTJets;
    int matchedHLTTaus;
    outTree->Branch("matchedHLTJets", &matchedHLTJets);
    outTree->Branch("matchedHLTTaus", &matchedHLTTaus);

    int matchedHLTJets_Loose;
    int matchedHLTTaus_Loose;
    outTree->Branch("matchedHLTJets_Loose", &matchedHLTJets_Loose);
    outTree->Branch("matchedHLTTaus_Loose", &matchedHLTTaus_Loose);

    // temp branch
    float filter_t1eta;
    float filter_t2eta;
    outTree->Branch("filter_t1eta", &filter_t1eta);
    outTree->Branch("filter_t2eta", &filter_t2eta);

    // variables without branches

    float AODJet1Pt_ = 0;
    float AODJet2Pt_ = 0;
    float AODTau1Pt_ = 0;
    float AODTau2Pt_ = 0;
    float mj1j2_ = 0;

    std::set<int> lumis;
    std::cout << "If this is a rate study, did you check your boolean variables before running?" << std::endl;
    // Event Loop
    // for-loop of fewer events is useful to test code without heavy I/O to terminal from cout statements
    for (int iEntry = 0; iEntry < 272000; ++iEntry) {
    //for (int iEntry = 0; iEntry < inTree->GetEntries(); ++iEntry) {
	inTree->GetEntry(iEntry);

        bool rateStudyHLT = false;
        bool rateStudyEZB = false;

	if ((iEntry % 100000 == 0 and (!rateStudyHLT and !rateStudyEZB)) or iEntry % 1000000 == 0) std::cout << std::to_string(iEntry) << std::endl;

	nEvents = inTree->nEvents;
	runNumber = inTree->runNumber;
	lumiBlock = inTree->lumiBlock;
	eventNumberID = inTree->eventNumberID;

        bool okayLumi = ((lumiBlock >=38 and lumiBlock <= 81) or (lumiBlock >= 84 and lumiBlock <= 171));
        //std::cout << lumiBlock << '\t' << okayLumi << std::endl;
        if (rateStudyHLT and (runNumber != 323755 or !okayLumi)) continue;
        if (rateStudyHLT or rateStudyEZB) lumis.insert(lumiBlock);
        lumisSize = lumis.size();
        

        // Inclusive VBF L1 and HLT
        passhltL1VBFDiJetOR = 0;
        passhltL1VBFDiJetOR = inTree->passhltL1VBFDiJetOR;
        passInclusiveVBFHLT = inTree->passInclusiveVBFHLT;

        // VBF2DT Old L1
        passhltL1VBFDiJetIsoTauNoer = 0;
        if (rateStudyHLT or rateStudyEZB) passhltL1VBFDiJetIsoTauNoer = inTree->passhltL1VBFDiJetIsoTauNoer;

        // VBF2DT L1
        passhltL1VBFDiJetIsoTau = 0;
        passhltL1VBFDiJetIsoTau = inTree->passhltL1VBFDiJetIsoTau;

        // fill VBF2DT HLT Modules for Cutflow
        passhltL2VBFIsoTauNNFilter = 0;
        passhltHpsDoublePFTau20withL2NNBeforeDeepTau = 0;
        passhltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch = 0;
        passhltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched = 0;
        passhltRealDijetFilter = 0;
        passhltVBFLooseIDPFDummyFilter = 0;
        passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20 = 0;

        if (passhltL1VBFDiJetIsoTau) passhltL2VBFIsoTauNNFilter = inTree->passhltL2VBFIsoTauNNFilter;
        if (passhltL2VBFIsoTauNNFilter) passhltHpsDoublePFTau20withL2NNBeforeDeepTau = inTree->passhltHpsDoublePFTau20withL2NNBeforeDeepTau;
        if (passhltHpsDoublePFTau20withL2NNBeforeDeepTau) passhltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch = inTree->passhltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch;
        if (passhltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch) passhltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched = inTree->passhltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched;
        if (passhltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched) passhltRealDijetFilter = inTree->passhltRealDijetFilter;
        if (passhltRealDijetFilter) passhltVBFLooseIDPFDummyFilter = inTree->passhltVBFLooseIDPFDummyFilter;
        if (passhltVBFLooseIDPFDummyFilter) passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20 = inTree->passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20;

        passVBF2DTHLT = inTree->passVBF2DTHLT;
        passVBF2DTOldL1 = inTree->passVBF2DTOldL1;

        // fill VBF2DT Loose HLT Modules for cutflow
        passhltHpsDoublePFTau20BeforeDeepTau = 0;
        passhltHpsDoublePFTau20LooseDitauWPDeepTauNoMatch_VBF2DTLoose = 0;
        passhltHpsSinglePFTau45LooseDitauWPDeepTauL1HLTMatched_VBF2DTLoose = 0;
        passhltRealDijetFilter_VBF2DTLoose = 0;
        passhltVBFLooseIDPFDummyFilter_VBF2DTLoose = 0;
        passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsLooseDeepTauIsoPFTauHPS20_VBF2DTLoose = 0;

        if (passhltL1VBFDiJetIsoTau) passhltHpsDoublePFTau20BeforeDeepTau = inTree->passhltHpsDoublePFTau20BeforeDeepTau;
        if (passhltHpsDoublePFTau20BeforeDeepTau) passhltHpsDoublePFTau20LooseDitauWPDeepTauNoMatch_VBF2DTLoose = inTree->passhltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatchNoL2NN;
        //if (passhltL1VBFDiJetIsoTau) passhltHpsDoublePFTau20LooseDitauWPDeepTauNoMatch_VBF2DTLoose = inTree->passhltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatchNoL2NN;
        if (passhltHpsDoublePFTau20LooseDitauWPDeepTauNoMatch_VBF2DTLoose) passhltHpsSinglePFTau45LooseDitauWPDeepTauL1HLTMatched_VBF2DTLoose = inTree->passhltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatchedNoL2NN;
        if (passhltHpsSinglePFTau45LooseDitauWPDeepTauL1HLTMatched_VBF2DTLoose) passhltRealDijetFilter_VBF2DTLoose = inTree->passhltRealDijetFilter;
        if (passhltRealDijetFilter_VBF2DTLoose) passhltVBFLooseIDPFDummyFilter_VBF2DTLoose = inTree->passhltVBFLooseIDPFDummyFilter;
        if (passhltVBFLooseIDPFDummyFilter_VBF2DTLoose) passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsLooseDeepTauIsoPFTauHPS20_VBF2DTLoose = inTree->passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20NoL2NN;

        passVBF2DTLooseHLT = inTree->passVBF2DTLooseNoL2NNHLT;

        filter_t1eta = -999;
        filter_t2eta = -999;
        //if (passhltHpsDoublePFTau20BeforeDeepTau) {
        if (passhltHpsDoublePFTau20LooseDitauWPDeepTauNoMatch_VBF2DTLoose) {
          //filter_t1eta = inTree->hltHpsDoublePFTau20BeforeDeepTau_eta->at(0);
          //filter_t2eta = inTree->hltHpsDoublePFTau20BeforeDeepTau_eta->at(1);
          filter_t1eta = inTree->hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatchNoL2NN_eta->at(0);
          filter_t2eta = inTree->hltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatchNoL2NN_eta->at(1);
        }


        // fill DiTau L1 flags and DeepDiTau35HLT
     
        passDiTau32L1 = passDiTau34L1 = passDiTau35L1 = 0;
        passDiTau32L1 = inTree->passhltL1sDoubleTauBigOR;
        int sizeL1DiTau32 = 0;
        int sizeL1DiTau34 = 0;
        int sizeL1DiTau35 = 0;
        if (passDiTau32L1) sizeL1DiTau32 = inTree->hltL1sDoubleTauBigOR_pt->size();
        if (sizeL1DiTau32 >= 2) {
          for (int iL1Tau = 0; iL1Tau < sizeL1DiTau32; ++iL1Tau) {
            if (inTree->hltL1sDoubleTauBigOR_pt->at(iL1Tau) >= 34) sizeL1DiTau34 += 1;
            if (inTree->hltL1sDoubleTauBigOR_pt->at(iL1Tau) >= 35) sizeL1DiTau35 += 1;
          }
          if (sizeL1DiTau34 >= 2) passDiTau34L1 = 1;
          if (sizeL1DiTau35 >= 2) passDiTau35L1 = 1;
        }

        passDeepDiTau35HLT = inTree->passDeepDiTau35HLT;
        //passDiTau35HLT = inTree->passDiTau35HLT;

        // fill Controls and Spain HLT
        passUpperControlMedHLT = inTree->passUpperControlMedHLT;
        passLowerControlMedHLT = inTree->passLowerControlMedHLT;
        passUpperControlHLT = inTree->passUpperControlHLT;
        passLowerControlHLT = inTree->passLowerControlHLT;
        passDiTauControlHLT = inTree->passDiTauControl;

        pass2Tau1JetHLT = inTree->pass2Tau1JetHLT;


        bool passhltL1 = passDiTau32L1 or passhltL1VBFDiJetOR or passhltL1VBFDiJetIsoTau or passhltL1VBFDiJetIsoTauNoer;
        if ((rateStudyHLT or rateStudyEZB) and passhltL1) outTree->Fill();
        if (rateStudyHLT or rateStudyEZB) continue;
        // above is all that needs to run for rate
	//---------------------apply AOD selection and fill AOD objects------------------------------//

        viableTaus = 1;
        viableJets = 1;
        matchedL1Tau = 1;
        matchedL1Jets = 1;
        matchedHLTTaus = 1;
        matchedHLTJets = 1;

	int sizeAODTau = inTree->tauPt->size(); // number of taus in event
	int sizeAODJet = inTree->jetPt->size(); // number of jets in event
	// check kinematics and ID of tau objects, store isolated taus w pt>=25 and eta<=2.1 taus
	std::vector<TLorentzVector> isoTauCands;	
	for (int iTau = 0; iTau < sizeAODTau; ++iTau) {
          bool passTauID = false;
          deepTauVSjet = inTree->tauByMediumDeepTau2017v2p1VSjet->at(iTau) > 0.5;
          deepTauVSmu = inTree->tauByVLooseDeepTau2017v2p1VSmu->at(iTau) > 0.5;
          deepTauVSele = inTree->tauByVVVLooseDeepTau2017v2p1VSe->at(iTau) > 0.5;
	
          if (deepTauVSjet && deepTauVSmu && deepTauVSele) passTauID = true;

          if (passTauID && fabs(inTree->tauEta->at(iTau) <= 2.1) ) { //&& inTree->tauPt->at(iTau) >= 25 ) {
            TLorentzVector tauCand;
            tauCand.SetPtEtaPhiE(inTree->tauPt->at(iTau),
                                 inTree->tauEta->at(iTau), 
                                 inTree->tauPhi->at(iTau), 
                                 inTree->tauEnergy->at(iTau));
            isoTauCands.push_back(tauCand);
          }
	}
        int isoTauCandsSize = isoTauCands.size();
        if (isoTauCandsSize < 2) viableTaus = 0; // need two taus minimum

	// use first two non-overlapped AOD taus
	// isoTauAODCands are already ordered by pT
	TLorentzVector AODTau1, AODTau2;
	if (viableTaus) {

	  AODTau1.SetPtEtaPhiE(isoTauCands.at(0).Pt(), 
                             isoTauCands.at(0).Eta(), 
                             isoTauCands.at(0).Phi(),
                             isoTauCands.at(0).Energy());

	  for (std::vector<TLorentzVector>::const_iterator iTau = isoTauCands.begin()+1; iTau != isoTauCands.end(); ++iTau) {
	    AODTau2.SetPtEtaPhiE(iTau->Pt(), iTau->Eta(), iTau->Phi(), iTau->Energy());
	    if (AODTau2.DeltaR(AODTau1) > 0.5) break; // if taus are not overlapped, leave the for-loop
	  }
          // check that the tau didn't make it all the way through the loop without breaking
          // I think this is unlikely but it's good to be redundant
	  if (AODTau1.DeltaR(AODTau2) < 0.5) viableTaus = 0;
        } // end viable if statement


        // difference between 20 and 45 filters is 20 doesn't have L1HLT matching, 45 does

        std::vector<TLorentzVector> HLTTauCandsFrom20Filter;
        std::vector<std::pair<int,int>> matchedHLTAODTausFrom20Filter;
        int HLTTausFrom20FilterSize = inTree->hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_pt->size();
        if (HLTTausFrom20FilterSize >= 2 && isoTauCandsSize >= 2) {
          HLTTauCandsFrom20Filter = hltFillWithCands(inTree, "hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch", HLTTausFrom20FilterSize);
          int HLTTauCandsFrom20FilterSize = HLTTauCandsFrom20Filter.size();
          if (HLTTauCandsFrom20FilterSize >= 2) {
            for (int iHLTTauFrom20Filter = 0; iHLTTauFrom20Filter < HLTTauCandsFrom20FilterSize; ++iHLTTauFrom20Filter) {
              for (int iAODTau = 0; iAODTau < isoTauCandsSize; ++iAODTau) {
                float dRtaus_ = isoTauCands.at(iAODTau).DeltaR(HLTTauCandsFrom20Filter.at(iHLTTauFrom20Filter));
                if (dRtaus_ <= 0.5) {
                  matchedHLTAODTausFrom20Filter.push_back(std::make_pair(iHLTTauFrom20Filter, iAODTau));
                }
              }
            }
          }
        }
        int matchedHLTAODTausFrom20FilterSize = matchedHLTAODTausFrom20Filter.size();
        if (matchedHLTAODTausFrom20FilterSize < 1) matchedHLTTaus = 0; 

        std::vector<TLorentzVector> HLTTauCandsFrom45Filter;
        std::vector<std::pair<int,int>> matchedHLTAODTausFrom45Filter;
        int HLTTausFrom45FilterSize = inTree->hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_pt->size();
        if (HLTTausFrom45FilterSize >= 1 && isoTauCandsSize >= 2) {
          HLTTauCandsFrom45Filter = hltFillWithCands(inTree, "hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched", HLTTausFrom45FilterSize);
          int HLTTauCandsFrom45FilterSize = HLTTauCandsFrom45Filter.size();
          if (HLTTauCandsFrom45FilterSize >= 1) {
            for (int iHLTTauFrom45Filter = 0; iHLTTauFrom45Filter < HLTTauCandsFrom45FilterSize; ++iHLTTauFrom45Filter) {
              for (int iAODTau = 0; iAODTau < isoTauCandsSize; ++iAODTau) {
                float dRtaus_ = isoTauCands.at(iAODTau).DeltaR(HLTTauCandsFrom45Filter.at(iHLTTauFrom45Filter));
                if (dRtaus_ <= 0.5) {
                  matchedHLTAODTausFrom45Filter.push_back(std::make_pair(iHLTTauFrom45Filter, iAODTau));
                }
              }
            }
          }
        }
        int matchedHLTAODTausFrom45FilterSize = matchedHLTAODTausFrom45Filter.size();
        if (matchedHLTAODTausFrom45FilterSize < 1) matchedHLTTaus = 0;

        // about 30 events total have 3 or 4 matched taus
        // what's odd is there are many more 4 tau events than 3 tau events?

        if (matchedHLTAODTausFrom45FilterSize == 1) {
          AODTau1 = isoTauCands.at(matchedHLTAODTausFrom45Filter.at(0).second);
          std::vector<TLorentzVector> matchedAODTausFrom20Filter;
          for (int iMatchedTau = 0; iMatchedTau < matchedHLTAODTausFrom20FilterSize; ++iMatchedTau) {
            matchedAODTausFrom20Filter.push_back(isoTauCands.at(matchedHLTAODTausFrom20Filter.at(iMatchedTau).second));
          }
          int matchedAODTausFrom20FilterSize = matchedAODTausFrom20Filter.size();
          int AODTau2Index = -1;
          float highestPtSum = -1;
          float comparePtSum = -1;
          for (int iAODTauFrom20Filter = 0; iAODTauFrom20Filter < matchedAODTausFrom20FilterSize; ++iAODTauFrom20Filter) {
            if (AODTau1.DeltaR(matchedAODTausFrom20Filter.at(iAODTauFrom20Filter)) > 0.5) {
              comparePtSum = (AODTau1.Pt() + matchedAODTausFrom20Filter.at(iAODTauFrom20Filter).Pt());
              if (comparePtSum > highestPtSum) { highestPtSum = comparePtSum; AODTau2Index = iAODTauFrom20Filter;}
            }
          }
          if (AODTau2Index != -1) AODTau2 = matchedAODTausFrom20Filter.at(AODTau2Index);
          if (AODTau2Index == -1) matchedHLTTaus = 0; 
        }

        if (matchedHLTAODTausFrom45FilterSize >= 2) {
          std::vector<TLorentzVector> matchedAODTausFrom45Filter;
          for (int iMatchedTau = 0; iMatchedTau < matchedHLTAODTausFrom45FilterSize; ++iMatchedTau) {
            matchedAODTausFrom45Filter.push_back(isoTauCands.at(matchedHLTAODTausFrom45Filter.at(iMatchedTau).second));
          }
          int matchedAODTausFrom45FilterSize = matchedAODTausFrom45Filter.size();
          int AODTau1Index = -1;
          int AODTau2Index = -1;
          float highestPtSum = -1;
          float comparePtSum = -1;
          for (int iAODTau = 0; iAODTau < matchedAODTausFrom45FilterSize; ++iAODTau) {
            for (int jAODTau = iAODTau+1; jAODTau < matchedAODTausFrom45FilterSize; ++jAODTau) {
              if (matchedAODTausFrom45Filter.at(iAODTau).DeltaR(matchedAODTausFrom45Filter.at(jAODTau)) > 0.5) {
                comparePtSum = (matchedAODTausFrom45Filter.at(iAODTau).Pt() + matchedAODTausFrom45Filter.at(jAODTau).Pt());
                if (comparePtSum > highestPtSum) { highestPtSum = comparePtSum; AODTau1Index = iAODTau; AODTau2Index = jAODTau;}
              }
            }
          }
          if (AODTau1Index != -1 && AODTau2Index != -1) {
            AODTau1 = matchedAODTausFrom45Filter.at(AODTau1Index);
            AODTau2 = matchedAODTausFrom45Filter.at(AODTau2Index);
          }
          if (AODTau1Index == -1 || AODTau2Index == -1) matchedHLTTaus = 0;
        }


        if (AODTau1.DeltaR(AODTau2) < 0.5 || AODTau1.Pt() == 0 || AODTau2.Pt() == 0) viableTaus = 0;

        if (viableTaus) {
          AODTau1Pt_ = AODTau1.Pt();
          AODTau2Pt_ = AODTau2.Pt();
          // make the highest pT Tau the leading Tau
          if (AODTau2Pt_ > AODTau1Pt_) {
            TLorentzVector tempTau_;
            tempTau_ = AODTau1;
            AODTau1 = AODTau2;
            AODTau2 = tempTau_;
            AODTau1Pt_ = AODTau1.Pt();
            AODTau2Pt_ = AODTau2.Pt();
          }
        }       

	// check kinematics and ID of jet objects, store jets w pt>=30 and eta<=4.7
	std::vector<TLorentzVector> jetCands;
	for (int iJet = 0; iJet < sizeAODJet; ++iJet){

          bool passJetID = false;
          if (inTree->jetID->at(iJet) >= 2) passJetID = true; // jetID is 2 if it passes loose, and 6 if it passes loose and tight

          if (passJetID && fabs(inTree->jetEta->at(iJet) <= 4.7)) { //&& inTree->jetPt->at(iJet) >= 30 
            TLorentzVector jetCand;
            jetCand.SetPtEtaPhiE(inTree->jetPt->at(iJet), 
                                 inTree->jetEta->at(iJet), 
                                 inTree->jetPhi->at(iJet), 
                                 inTree->jetEn->at(iJet));
	      // if a jetCandidate looks like it could be either tau we already selected, don't store it
	    bool jetCandIsTau = false;
            if (AODTau1.DeltaR(jetCand) < 0.5 || AODTau2.DeltaR(jetCand) < 0.5) jetCandIsTau = true;

            if (!jetCandIsTau) jetCands.push_back(jetCand);
          }
	}
	// check that we have at least two good jets
	int jetCandsSize = jetCands.size(); 
        if (jetCandsSize < 2) viableJets = 0;
	TLorentzVector AODJet1, AODJet2;
        if (viableJets) std::tie(AODJet1, AODJet2) = highestMassPair(jetCands);

        std::vector<TLorentzVector> HLTJetCands;
        std::vector<std::pair<int,int>> matchedHLTAODJets;
        int HLTJetsSize = inTree->hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20_pt->size();
        if (HLTJetsSize >= 2 && jetCandsSize >= 2) {
          HLTJetCands = hltFillWithCands(inTree, "hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20", HLTJetsSize);
          int HLTJetCandsSize = HLTJetCands.size();
          if (HLTJetCandsSize >= 2) {
            for (int iHLTJet = 0; iHLTJet < HLTJetCandsSize; ++iHLTJet) {
              for (int iAODJet = 0; iAODJet < jetCandsSize; ++iAODJet) {
                float dRjets_ = jetCands.at(iAODJet).DeltaR(HLTJetCands.at(iHLTJet));
                if (dRjets_ <= 0.5) {
                  matchedHLTAODJets.push_back(std::make_pair(iHLTJet, iAODJet));
                }
              }
            }
          }
        }
        int matchedHLTAODJetsSize = matchedHLTAODJets.size();
        if (matchedHLTAODJetsSize < 2) matchedHLTJets = 0;

        if (matchedHLTAODJetsSize == 2) {
          AODJet1 = jetCands.at(matchedHLTAODJets.at(0).second);
          AODJet2 = jetCands.at(matchedHLTAODJets.at(1).second);
        }
        
        std::vector<TLorentzVector> matchedAODJets;
        if (matchedHLTAODJetsSize >= 3) {
          for (int iMatchedJet = 0; iMatchedJet < matchedHLTAODJetsSize; ++iMatchedJet) {
            matchedAODJets.push_back(jetCands.at(matchedHLTAODJets.at(iMatchedJet).second));
          }
          // find highest mjj pair
          int AODJet1Index = -1;
          int AODJet2Index = -1;
          std::tie(AODJet1Index, AODJet2Index) = highestMassPairNew(matchedAODJets);
          if (AODJet1Index != -1 and AODJet2Index != -1) {
            AODJet1 = matchedAODJets.at(AODJet1Index);
            AODJet2 = matchedAODJets.at(AODJet2Index);
          }
          if (AODJet1Index == -1 || AODJet2Index == -1) matchedHLTJets = 0;
        }

        if (AODJet1.DeltaR(AODJet2) < 0.5 || AODJet1.Pt() == 0 || AODJet2.Pt() == 0) viableJets = 0;
        if (AODJet1.DeltaR(AODTau1) < 0.5 || AODJet1.DeltaR(AODTau2) < 0.5 || AODJet2.DeltaR(AODTau1) < 0.5 || AODJet2.DeltaR(AODTau2) < 0.5) { viableJets = 0; viableTaus = 0;}

        if (viableJets) {
          AODJet1Pt_ = AODJet1.Pt();
          AODJet2Pt_ = AODJet2.Pt();
          // make higher pT jet leading jet
          if (AODJet2Pt_ > AODJet1Pt_) {
            TLorentzVector tempJet_;
            tempJet_ = AODJet1;
            AODJet1 = AODJet2;
            AODJet2 = tempJet_;
            AODJet1Pt_ = AODJet1.Pt();
            AODJet2Pt_ = AODJet2.Pt();
          }
          mj1j2_ = (AODJet1 + AODJet2).M();
        }

	// Check AOD Objects Pass Offline Selection
        //passDiTau32Off = passDiTau34Off = 0;
        passDiTau35Off = passInclusiveVBFOff = passVBF2DTOff = pass2Tau1JetOff = 0;
        if (viableTaus && viableJets) {

          //int dEtajj = abs(AODJet1.Eta() - AODJet2.Eta());
          int offJetInc = 10; // define offline as XX increase of L1 cuts
	  int offTau1Inc = 5;
          int offTau2Inc = 5;
          int offM2Inc = 50;
 

          if (AODJet1Pt_ >= 30 && AODJet2Pt_ >= 30 && mj1j2_ >= 600) {
            //if (AODTau1Pt_ >= (32+offTau1Inc) && AODTau2Pt_ >= (32+offTau2Inc) ) passDiTau32Off = 1;
            //if (AODTau1Pt_ >= (34+offTau1Inc) && AODTau2Pt_ >= (34+offTau2Inc) ) passDiTau34Off = 1;
            if (AODTau1Pt_ >= (35+offTau1Inc) && AODTau2Pt_ >= (35+offTau2Inc) ) passDiTau35Off = 1;
          }

          // L1_DoubleJet_110_35_DoubleJet35_Mass_Min620
	  if (AODJet1Pt_ >= (110+offJetInc) && AODJet2Pt_ >= (35+offJetInc) && \
              AODTau1Pt_ >= 25 && AODTau2Pt_ >= 25 && mj1j2_ >= 700) passInclusiveVBFOff = 1;
        
          // L1_DoubleJet35_Mass_Min_450_IsoTau45er2p1_RmvOl
          if (AODJet1Pt_ >= (35+offJetInc) && AODJet2Pt_ >= (35+offJetInc) && \
              AODTau1Pt_ >= (45+offTau1Inc) && AODTau2Pt_ >= (20+offTau2Inc) && mj1j2_ >= 600) passVBF2DTOff = 1;
          //if (AODJet1Pt_ >= 60 && AODJet2Pt_ >= 60 && AODTau1Pt_ >= 60 && AODTau2Pt_ >= 35 && mj1j2_ >= 700) passVBF2DTOff = 1;    
          //if (AODJet1Pt_ >= 100 && AODJet2Pt_ >= 100 && AODTau1Pt_ >= 60 && AODTau2Pt_ >= 35 && mj1j2_ >= 600) passVBF2DTOff = 1;    
          
          // L1_DoubleIsoTau26er2p1_Jet55_OvRm_dR0p5
          if (AODJet1Pt_ >= (55+offJetInc) && AODJet2Pt_ >= (20+offJetInc) && \
              AODTau1Pt_ >= (26+18) && AODTau2Pt_ >= (26+8) && mj1j2_>=600) pass2Tau1JetOff = 1;

        } // end viable if statement


        //---------------------------match AOD and HLT------------------------------//

        // fill branches if any offline selection is passed for AOD
        // fill branches for Old or New HLT objects if they are matched to AOD

        j1_ptAOD = j1_etaAOD = j1_phiAOD = -999;
        j2_ptAOD = j2_etaAOD = j2_phiAOD = mjjAOD = -999;
        t1_ptAOD = t1_etaAOD = t1_phiAOD = -999;
        t2_ptAOD = t2_etaAOD = t2_phiAOD = -999;

        matchedHLTTaus_Loose = matchedHLTJets_Loose = 1;

        if (viableTaus && viableJets) {
          // AOD Branches
	  j1_ptAOD = AODJet1.Pt();
	  j1_etaAOD = AODJet1.Eta();
	  j1_phiAOD = AODJet1.Phi();
	  j2_ptAOD = AODJet2.Pt();
	  j2_etaAOD = AODJet2.Eta();
	  j2_phiAOD = AODJet2.Phi();

          mjjAOD = (AODJet1 + AODJet2).M();

	  t1_ptAOD = AODTau1.Pt();
	  t1_etaAOD = AODTau1.Eta();
	  t1_phiAOD = AODTau1.Phi();
	  t2_ptAOD = AODTau2.Pt();
	  t2_etaAOD = AODTau2.Eta();
	  t2_phiAOD = AODTau2.Phi();
          
	} // end if statement to fill kinematic variables

        outTree->Fill();

    } // end event loop


    std::cout << lumis.size() << std::endl;

    std::string outputFileName = outName;
    TFile *fOut = TFile::Open(outputFileName.c_str(),"RECREATE");
    fOut->cd();

    outTree->Write();

    fOut->Close();
    return 0;
}
