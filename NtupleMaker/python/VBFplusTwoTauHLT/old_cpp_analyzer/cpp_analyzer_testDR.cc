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

    int passhltL1sSingleMu22;
    int passhltL1sMu22er2p1IsoTau28er2p1;
    outTree->Branch("passhltL1sSingleMu22", &passhltL1sSingleMu22);
    outTree->Branch("passhltL1sMu22er2p1IsoTau28er2p1", &passhltL1sMu22er2p1IsoTau28er2p1);

    int passDiTau32L1, passDiTau34L1, passDiTau35L1;
    outTree->Branch("passDiTau32L1", &passDiTau32L1);
    outTree->Branch("passDiTau34L1", &passDiTau34L1);
    outTree->Branch("passDiTau35L1", &passDiTau35L1);

    // HLTs
    int passInclusiveVBFHLT, passDeepInclusiveVBFHLT, passAltDeepInclusiveVBFHLT;
    int passVBF2DTHLT, passVBF2DTLooseHLT, passVBF2DTOldL1;
    int passDiTau35HLT, passDeepDiTau35HLT;
    passDiTau35HLT = 0;
    outTree->Branch("passInclusiveVBFHLT", &passInclusiveVBFHLT);
    outTree->Branch("passDeepInclusiveVBFHLT", &passDeepInclusiveVBFHLT);
    outTree->Branch("passAltDeepInclusiveVBFHLT", &passAltDeepInclusiveVBFHLT);
    outTree->Branch("passVBF2DTHLT", &passVBF2DTHLT);
    outTree->Branch("passVBF2DTLooseHLT", &passVBF2DTLooseHLT);
    outTree->Branch("passVBF2DTOldL1", &passVBF2DTOldL1);
    outTree->Branch("passDiTau35HLT", &passDiTau35HLT);
    outTree->Branch("passDeepDiTau35HLT", &passDeepDiTau35HLT);

    // controls and Spain HLT
    int passUpperControlMedHLT, passLowerControlMedHLT;
    int passUpperControlHLT, passLowerControlHLT;
    int passDiTauControlHLT, pass2Tau1JetHLT, pass2Tau1JetHigherHLT;
    outTree->Branch("passUpperControlMedHLT", &passUpperControlMedHLT);
    outTree->Branch("passLowerControlMedHLT", &passLowerControlMedHLT);
    outTree->Branch("passUpperControlHLT", &passUpperControlHLT);
    outTree->Branch("passLowerControlHLT", &passLowerControlHLT);
    outTree->Branch("passDiTauControlHLT", &passDiTauControlHLT);
    outTree->Branch("pass2Tau1JetHLT", &pass2Tau1JetHLT);
    outTree->Branch("pass2Tau1JetHigherHLT", &pass2Tau1JetHigherHLT);

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
    int passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedUsingDiJetCorrCheckerWithMediumDiTau;
    outTree->Branch("passhltL2VBFIsoTauNNFilter", &passhltL2VBFIsoTauNNFilter);
    outTree->Branch("passhltHpsDoublePFTau20withL2NNBeforeDeepTau", &passhltHpsDoublePFTau20withL2NNBeforeDeepTau);
    outTree->Branch("passhltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch", &passhltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch);
    outTree->Branch("passhltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched", &passhltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched);
    outTree->Branch("passhltRealDijetFilter", &passhltRealDijetFilter);
    outTree->Branch("passhltVBFLooseIDPFDummyFilter", &passhltVBFLooseIDPFDummyFilter);
    outTree->Branch("passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20", &passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20);
    outTree->Branch("passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedUsingDiJetCorrCheckerWithMediumDiTau", &passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedUsingDiJetCorrCheckerWithMediumDiTau);


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

    // modules for DeepInclusiveVBF
    int passhltDoubleL2Tau20eta2p2;
    int passhltDoubleL2GlobIsoTau20eta2p2;
    int passhltMatchedVBFTwoPFJets2CrossCleanedFromDoubleMediumDeepTauDitauWPPFTauHPS20;
    int passhltMatchedVBFOnePFJet2CrossCleanedFromDoubleMediumDeepTauDitauWPPFTauHPS20;
    int passhltMatchedVBFTwoPFJetsPassingDiJetCorrCheckerWithMediumDiTauWPPFTauHPS20;
    int passhltMatchedVBFOnePFJetPassingDiJetCorrCheckerWithMediumDiTauWPPFTauHPS20;
    outTree->Branch("passhltDoubleL2Tau20eta2p2", &passhltDoubleL2Tau20eta2p2);
    outTree->Branch("passhltDoubleL2GlobIsoTau20eta2p2", &passhltDoubleL2GlobIsoTau20eta2p2);
    outTree->Branch("passhltMatchedVBFTwoPFJets2CrossCleanedFromDoubleMediumDeepTauDitauWPPFTauHPS20", &passhltMatchedVBFTwoPFJets2CrossCleanedFromDoubleMediumDeepTauDitauWPPFTauHPS20);
    outTree->Branch("passhltMatchedVBFOnePFJet2CrossCleanedFromDoubleMediumDeepTauDitauWPPFTauHPS20", &passhltMatchedVBFOnePFJet2CrossCleanedFromDoubleMediumDeepTauDitauWPPFTauHPS20);
    outTree->Branch("passhltMatchedVBFTwoPFJetsPassingDiJetCorrCheckerWithMediumDiTauWPPFTauHPS20", &passhltMatchedVBFTwoPFJetsPassingDiJetCorrCheckerWithMediumDiTauWPPFTauHPS20);
    outTree->Branch("passhltMatchedVBFOnePFJetPassingDiJetCorrCheckerWithMediumDiTauWPPFTauHPS20", &passhltMatchedVBFOnePFJetPassingDiJetCorrCheckerWithMediumDiTauWPPFTauHPS20);

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

    // Event Loop
    // for-loop of fewer events is useful to test code without heavy I/O to terminal from cout statements
    for (int iEntry = 4950; iEntry < 4995; ++iEntry) {
    //for (int iEntry = 0; iEntry < inTree->GetEntries(); ++iEntry) {
	inTree->GetEntry(iEntry);

	if ((iEntry % 100000 == 0 ) or iEntry % 1000000 == 0) std::cout << std::to_string(iEntry) << std::endl;

	//---------------------apply AOD selection and fill AOD objects------------------------------//

        viableTaus = 1;
        viableJets = 1;

        int passL1 = inTree->passhltL1VBFElectronLoose;
        int nJet = inTree->nJet;
        int nEle = inTree->nEle;
        int nTau = inTree->nTau;
        //int basicReqs = (inTree->passhltL1VBFElectronLoose) and (inTree->nJet >= 2) and (inTree->nEle >= 1) and (inTree->nTau >= 1) ;
        int basicReqs = ((passL1 > 0) and (nJet >= 2) and (nEle >= 1) and (nTau >= 1));
        if (basicReqs) { 
 
	  //int sizeAODJet = inTree->jetPt->size(); // number of jets in event
	  // check kinematics and ID of jet objects, store jets w pt>=30 and eta<=4.7
	  std::vector<TLorentzVector> jetCands;
	  for (int iJet = 0; iJet < nJet; ++iJet){

            bool passJetID = false;
            if (inTree->jetID->at(iJet) >= 2) passJetID = true; // jetID is 2 if it passes loose, and 6 if it passes loose and tight

            if (passJetID && fabs(inTree->jetEta->at(iJet) <= 4.7) && inTree->jetPt->at(iJet) >= 45) {
              TLorentzVector jetCand;
              jetCand.SetPtEtaPhiE(inTree->jetPt->at(iJet), 
                                 inTree->jetEta->at(iJet), 
                                 inTree->jetPhi->at(iJet), 
                                 inTree->jetEn->at(iJet));

              jetCands.push_back(jetCand);
            }
	  }
	  int jetCandsSize = jetCands.size(); 
          if (jetCandsSize < 2) {continue;}

	  //int sizeAODTau = inTree->tauPt->size(); // number of taus in event
	  // check kinematics and ID of tau objects, store isolated taus w pt>=25 and eta<=2.1 taus
	  std::vector<TLorentzVector> isoTauCands;	
	  for (int iTau = 0; iTau < nTau; ++iTau) {
            bool passTauID = false;
            deepTauVSjet = inTree->tauByMediumDeepTau2017v2p1VSjet->at(iTau) > 0.5;
            deepTauVSmu = inTree->tauByVLooseDeepTau2017v2p1VSmu->at(iTau) > 0.5;
	    deepTauVSele = inTree->tauByTightDeepTau2017v2p1VSe->at(iTau) > 0.5;
	
            if (deepTauVSjet && deepTauVSmu && deepTauVSele) passTauID = true;

            if (passTauID && fabs(inTree->tauEta->at(iTau) <= 2.3) && inTree->tauPt->at(iTau) >= 25 ) {
              TLorentzVector tauCand;
              tauCand.SetPtEtaPhiE(inTree->tauPt->at(iTau),
                                 inTree->tauEta->at(iTau), 
                                 inTree->tauPhi->at(iTau), 
                                 inTree->tauEnergy->at(iTau));
              isoTauCands.push_back(tauCand);
            }
	  }
          int isoTauCandsSize = isoTauCands.size();
          if (isoTauCandsSize < 1) {continue;}

          TLorentzVector AODTau1;
          std::cout << "iEntry: " << iEntry << std::endl;
          std::cout << "jetSize: " << jetCandsSize << std::endl;
          AODTau1 = isoTauCands.at(0);
          int fewerjets = 0;
          std::cout << "Tau kinems: " << AODTau1.Pt() << " " << AODTau1.Eta() << " " << AODTau1.Phi() << " " << AODTau1.Energy() << std::endl;
          for (int iJet = 0; iJet < jetCandsSize; ++iJet){
            double dR = AODTau1.DeltaR(jetCands.at(iJet));
            if (dR < 0.5) {std::cout << "overlap" << std::endl; fewerjets += 1;}
            std::cout << "dR: " << dR << std::endl;
          }
          std::cout << "jetSize: " << jetCandsSize - fewerjets << std::endl;
         
	// check that we have at least two good jets
        //if (viableJets) std::tie(AODJet1, AODJet2) = highestMassPair(jetCands);

        } // end basic reqs if

        outTree->Fill();

    } // end event loop


    std::string outputFileName = outName;
    TFile *fOut = TFile::Open(outputFileName.c_str(),"RECREATE");
    fOut->cd();

    outTree->Write();

    fOut->Close();
    return 0;
}
