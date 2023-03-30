# Braden Allmond, August 10th 2022, KSU

from array import array
from helper_functions import match_L1_to_Offline, match_Offline_to_L1, fillWithTVecs, fillWithTVecsNoEnergyBranch, highestMjjPair, print_formatted_labels_and_values, matchHLTOff
from rateDictionary import rateDictionary
import ROOT
import argparse
import sys

ROOT.gROOT.SetBatch(True) # sets visual display off (i.e. no graphs/TCanvas)

# usage:
# gain/efficiency mode
# python3 L1VBFEleEff.py -i ../../../../../samples/VBFE_wMuTauFilters.root -r NOTRATE -s tight -L 0
# rate mode
# python3 L1VBFEleEff.py -i ../../../../../samples/EZBs/EZB_2018/EZB1_EGOR.root -r 2018O -s tight -L 0
# multifile
# for line in `cat rate_files.txt`; do echo $line; python3 L1VBFEleEff.py -i $line -r 2022G_PU6O -s tight -L 0 -DJ 35 >> rate_total_output.txt; done

if __name__ == "__main__":

  parser = argparse.ArgumentParser(description='Open a .root file')
  parser.add_argument('-i', '--inputRootFile', dest='inFilename', action='store',
                    help='the input .root file\'s name')
  parser.add_argument('-r', '--rateStudy', dest='rateStudy', default="NOTRATE", action='store',
                    help='specify rate study tag (see rateDictionary.py)')
  args = parser.parse_args()

  inFile = ROOT.TFile.Open(args.inFilename,"READ")
  tree = inFile.Get("demo/vbf")

  ROOT.TH1.SetDefaultSumw2()


  match_right_way = True # used for a matching study, left hardcoded assuming the study won't need to be repeated

  rateStudyString = args.rateStudy.upper()
  isValidString = (rateStudyString == "2018O" or rateStudyString == "2022E" or rateStudyString == "2022F"\
                or rateStudyString == "2022G_PU70" or rateStudyString == "2022G_PU60")
  notRateStudy = 'NOTRATE' in rateStudyString
  rateStudy = not notRateStudy and isValidString # "not not" is the same as "is"


  # hell to read but
  # defining a variable/object handle 
  #   objName = type('typename')(initialization*) *initialization changes by type
  # and then linking that object handle to an available branch in the event tree
  #   tree.SetBranchAddress("branchOfObjInTree", objHandle)

  # Rate
  runNumber = array('i', [0])
  lumiSection = array('i', [0])
  eventID = array('i', [0])
  tree.SetBranchAddress("runNumber", runNumber)
  tree.SetBranchAddress("lumiBlock", lumiSection)
  tree.SetBranchAddress("eventNumberID", eventID)
  viableEventCounter = 0

  goodRunNumber = rateDictionary[rateStudyString]["runNumber"]
  minLS = rateDictionary[rateStudyString]["minLS"]
  maxLS = rateDictionary[rateStudyString]["maxLS"]
  badLS = rateDictionary[rateStudyString]["badLS"]

  # HLT Filter Matching
  # MuTau
  MuTauFinalMuonFilter_pt = ROOT.std.vector('float')()
  MuTauFinalMuonFilter_eta = ROOT.std.vector('float')()
  MuTauFinalMuonFilter_phi = ROOT.std.vector('float')()
  MuTauFinalMuonFilter_energy = ROOT.std.vector('float')()
  tree.SetBranchAddress("MuTauFinalMuonFilter_pt", MuTauFinalMuonFilter_pt)
  tree.SetBranchAddress("MuTauFinalMuonFilter_eta", MuTauFinalMuonFilter_eta)
  tree.SetBranchAddress("MuTauFinalMuonFilter_phi", MuTauFinalMuonFilter_phi)
  tree.SetBranchAddress("MuTauFinalMuonFilter_energy", MuTauFinalMuonFilter_energy)
  MuTauFinalTauFilter_pt = ROOT.std.vector('float')()
  MuTauFinalTauFilter_eta = ROOT.std.vector('float')()
  MuTauFinalTauFilter_phi = ROOT.std.vector('float')()
  MuTauFinalTauFilter_energy = ROOT.std.vector('float')()
  tree.SetBranchAddress("MuTauFinalTauFilter_pt", MuTauFinalTauFilter_pt)
  tree.SetBranchAddress("MuTauFinalTauFilter_eta", MuTauFinalTauFilter_eta)
  tree.SetBranchAddress("MuTauFinalTauFilter_phi", MuTauFinalTauFilter_phi)
  tree.SetBranchAddress("MuTauFinalTauFilter_energy", MuTauFinalTauFilter_energy)

  # Single Mu
  SingleMuAndLowerMuTauFinalFilter_pt = ROOT.std.vector('float')()
  SingleMuAndLowerMuTauFinalFilter_eta = ROOT.std.vector('float')()
  SingleMuAndLowerMuTauFinalFilter_phi = ROOT.std.vector('float')()
  SingleMuAndLowerMuTauFinalFilter_energy = ROOT.std.vector('float')()
  tree.SetBranchAddress("SingleMuAndLowerMuTauFinalFilter_pt", SingleMuAndLowerMuTauFinalFilter_pt)
  tree.SetBranchAddress("SingleMuAndLowerMuTauFinalFilter_eta", SingleMuAndLowerMuTauFinalFilter_eta)
  tree.SetBranchAddress("SingleMuAndLowerMuTauFinalFilter_phi", SingleMuAndLowerMuTauFinalFilter_phi)
  tree.SetBranchAddress("SingleMuAndLowerMuTauFinalFilter_energy", SingleMuAndLowerMuTauFinalFilter_energy)

  # VBF Mu
  VBFMuonFinalMuonFilter_pt = ROOT.std.vector('float')()
  VBFMuonFinalMuonFilter_eta = ROOT.std.vector('float')()
  VBFMuonFinalMuonFilter_phi = ROOT.std.vector('float')()
  VBFMuonFinalMuonFilter_energy = ROOT.std.vector('float')()
  tree.SetBranchAddress("VBFMuonFinalMuonFilter_pt", VBFMuonFinalMuonFilter_pt)
  tree.SetBranchAddress("VBFMuonFinalMuonFilter_eta", VBFMuonFinalMuonFilter_eta)
  tree.SetBranchAddress("VBFMuonFinalMuonFilter_phi", VBFMuonFinalMuonFilter_phi)
  tree.SetBranchAddress("VBFMuonFinalMuonFilter_energy", VBFMuonFinalMuonFilter_energy)

  VBFMuonFinalJetFilter_pt = ROOT.std.vector('float')()
  VBFMuonFinalJetFilter_eta = ROOT.std.vector('float')()
  VBFMuonFinalJetFilter_phi = ROOT.std.vector('float')()
  VBFMuonFinalJetFilter_energy = ROOT.std.vector('float')()
  tree.SetBranchAddress("VBFMuonFinalJetFilter_pt", VBFMuonFinalJetFilter_pt)
  tree.SetBranchAddress("VBFMuonFinalJetFilter_eta", VBFMuonFinalJetFilter_eta)
  tree.SetBranchAddress("VBFMuonFinalJetFilter_phi", VBFMuonFinalJetFilter_phi)
  tree.SetBranchAddress("VBFMuonFinalJetFilter_energy", VBFMuonFinalJetFilter_energy)

  # VBF Single Tau
  VBFSingleTauFinalTauFilter_pt = ROOT.std.vector('float')()
  VBFSingleTauFinalTauFilter_eta = ROOT.std.vector('float')()
  VBFSingleTauFinalTauFilter_phi = ROOT.std.vector('float')()
  VBFSingleTauFinalTauFilter_energy = ROOT.std.vector('float')()
  tree.SetBranchAddress("VBF1DTSingleTauFinalFilter_pt", VBFSingleTauFinalTauFilter_pt)
  tree.SetBranchAddress("VBF1DTSingleTauFinalFilter_eta", VBFSingleTauFinalTauFilter_eta)
  tree.SetBranchAddress("VBF1DTSingleTauFinalFilter_phi", VBFSingleTauFinalTauFilter_phi)
  tree.SetBranchAddress("VBF1DTSingleTauFinalFilter_energy", VBFSingleTauFinalTauFilter_energy)
  
  VBFSingleTauFinalJetFilter_pt = ROOT.std.vector('float')()
  VBFSingleTauFinalJetFilter_eta = ROOT.std.vector('float')()
  VBFSingleTauFinalJetFilter_phi = ROOT.std.vector('float')()
  VBFSingleTauFinalJetFilter_energy = ROOT.std.vector('float')()
  tree.SetBranchAddress("VBF1DTDoubleJetFinalFilter_CorrChecker_pt", VBFSingleTauFinalJetFilter_pt)
  tree.SetBranchAddress("VBF1DTDoubleJetFinalFilter_CorrChecker_eta", VBFSingleTauFinalJetFilter_eta)
  tree.SetBranchAddress("VBF1DTDoubleJetFinalFilter_CorrChecker_phi", VBFSingleTauFinalJetFilter_phi)
  tree.SetBranchAddress("VBF1DTDoubleJetFinalFilter_CorrChecker_energy", VBFSingleTauFinalJetFilter_energy)
  
  # HLT Final Decisions
  passMuTauHLT = array('i', [0])
  tree.SetBranchAddress("passMuTauHLT", passMuTauHLT)

  passIsoMu24eta2p1HLT = array('i', [0])
  tree.SetBranchAddress("passIsoMu24eta2p1HLT", passIsoMu24eta2p1HLT)

  passVBFMuonHLT = array('i', [0])
  tree.SetBranchAddress("passVBFMuonHLT", passVBFMuonHLT)

  passVBFSingleTauHLT = array('i', [0])
  tree.SetBranchAddress("passVBF1DTHLT_CorrChecker", passVBFSingleTauHLT)

  # Offline kinems
  if (notRateStudy):
    ##Taus
    OffnTaus = array('i', [0])
    OffTauCh = ROOT.std.vector('float')()
    OffTauPt = ROOT.std.vector('float')()
    OffTauEta = ROOT.std.vector('float')()
    OffTauPhi = ROOT.std.vector('float')()
    OffTauEnergy = ROOT.std.vector('float')()
    tree.SetBranchAddress("nTau", OffnTaus)
    tree.SetBranchAddress("tauCharge", OffTauCh)
    tree.SetBranchAddress("tauPt", OffTauPt)
    tree.SetBranchAddress("tauEta", OffTauEta)
    tree.SetBranchAddress("tauPhi", OffTauPhi)
    tree.SetBranchAddress("tauEnergy", OffTauEnergy)
    ##Jets
    OffnJets = array('i', [0])
    OffJetPt = ROOT.std.vector('float')()
    OffJetEta = ROOT.std.vector('float')()
    OffJetPhi = ROOT.std.vector('float')()
    OffJetEnergy = ROOT.std.vector('float')()
    tree.SetBranchAddress("nJet", OffnJets)
    tree.SetBranchAddress("jetPt", OffJetPt)
    tree.SetBranchAddress("jetEta", OffJetEta)
    tree.SetBranchAddress("jetPhi", OffJetPhi)
    tree.SetBranchAddress("jetEnergy", OffJetEnergy)
    ##Muons
    OffnMus = array('i', [0])
    OffMuCh = ROOT.std.vector('float')()
    OffMuPt = ROOT.std.vector('float')()
    OffMuEta = ROOT.std.vector('float')()
    OffMuPhi = ROOT.std.vector('float')()
    OffMuEnergy = ROOT.std.vector('float')()
    tree.SetBranchAddress("nMuon", OffnMus)
    tree.SetBranchAddress("muCharge", OffMuCh)
    tree.SetBranchAddress("muPt", OffMuPt)
    tree.SetBranchAddress("muEta", OffMuEta)
    tree.SetBranchAddress("muPhi", OffMuPhi)
    tree.SetBranchAddress("muEnergy", OffMuEnergy)
  
    OffMuPFChIso = ROOT.std.vector('float')()
    OffMuPFPUIso = ROOT.std.vector('float')()
    OffMuPFNeuIso = ROOT.std.vector('float')()
    OffMuPFPhoIso = ROOT.std.vector('float')()
    tree.SetBranchAddress("muPFPUIso", OffMuPFPUIso)
    tree.SetBranchAddress("muPFChIso", OffMuPFChIso)
    tree.SetBranchAddress("muPFNeuIso", OffMuPFNeuIso)
    tree.SetBranchAddress("muPFPhoIso", OffMuPFPhoIso)

    OffMuID = ROOT.std.vector('int')()
    tree.SetBranchAddress("muMVAMed", OffMuID)
  
    # Offline Ids
    OffTauIDvsJet = ROOT.std.vector('bool')()
    OffTauIDvsEle = ROOT.std.vector('bool')()
    OffTauIDvsMuon = ROOT.std.vector('bool')()
    tree.SetBranchAddress("tauByMediumDeepTau2017v2p1VSjet", OffTauIDvsJet)
    tree.SetBranchAddress("tauByVVVLooseDeepTau2017v2p1VSe", OffTauIDvsEle)
    tree.SetBranchAddress("tauByTightDeepTau2017v2p1VSmu", OffTauIDvsMuon)

    OffJetPFLooseID = ROOT.std.vector('bool')()
    OffJetID = ROOT.std.vector('int')()
    OffJetPUID = ROOT.std.vector('float')()
    OffJetPUFullID = ROOT.std.vector('int')()
    tree.SetBranchAddress("jetPFLooseId", OffJetPFLooseID)
    tree.SetBranchAddress("jetID", OffJetID)
    tree.SetBranchAddress("jetPUID", OffJetPUID)
    tree.SetBranchAddress("jetPUFullID", OffJetPUFullID)


  TallyVBFMuOff = 0
  TallyVBFSingleTauOff = 0
  TallyMuTauOff = 0
  TallySingleMuOff = 0
  TallyVBFMuORMuTauOff = 0
  TallyVBFMuORSingleMuOff = 0
  TallyMuTauORSingleMuOff = 0
  TallyTripleOROff = 0
  TallyQuadOROff = 0

  Off_Tallies = ["","","","","","","","",""]

  TotalEntries = tree.GetEntries()
  for entry in range(TotalEntries):
  #for entry in range(100):
    tree.GetEntry(entry)

    # for rate study
    if (rateStudy):
      runNumberValue = runNumber[0]
      if runNumberValue != goodRunNumber: continue

      lumiSectionValue = lumiSection[0]
      withinLumiRange = lumiSectionValue >= minLS and lumiSectionValue <= maxLS
      notBadLS = lumiSectionValue not in badLS
      goodLumi = withinLumiRange and notBadLS

      if not goodLumi: continue

      if (runNumberValue == goodRunNumber and goodLumi):
        viableEventCounter += 1
  
  
    # requiring events to pass your L1 biases your selection, fine for gain study, not fine for eff study
    basicReqs = ( notRateStudy and (OffnJets[0] >= 2) and (OffnMus[0] >= 1) and (OffnTaus[0] >= 1))

    if basicReqs:
      viableEventCounter += 1

      JetEtaToPass = 4.7
      PassJetID =  [i for i in range(len(OffJetID)) if OffJetID[i] >= 2]
      PassJetEta = [i for i in range(len(OffJetEta)) if abs(OffJetEta[i]) <= JetEtaToPass]
      # python list intersection https://stackoverflow.com/questions/3697432/how-to-find-list-intersection
      # listed in the order which removes the most members first (assuming & short-circuits)
      OffJetsPassFilter = list(set(PassJetID) & set(PassJetEta))
      if (len(OffJetsPassFilter) == 0): continue
      OffJets = fillWithTVecs(OffJetPt, OffJetEta, OffJetPhi, OffJetEnergy, OffJetsPassFilter)
      sizeOffJets = len(OffJets)
      if (sizeOffJets < 2): continue

      # Tau ID for Ele-Tau using 2017 DeepTau version 2p1, Med vs Jet, Tight vs Ele, VLoose vs Muon
      TauEtaToPass = 2.3
      PassTauID = [i for i in range(len(OffTauIDvsJet)) \
                    if (OffTauIDvsJet[i] == True and OffTauIDvsEle[i] == True and OffTauIDvsMuon[i] == True) ]  
      PassTauEta = [i for i in range(len(OffTauEta)) if abs(OffTauEta[i]) <= TauEtaToPass]
      OffTausPassFilter = list(set(PassTauID) & set(PassTauEta))
      if (len(OffTausPassFilter) == 0): continue
      OffTaus = fillWithTVecs(OffTauPt, OffTauEta, OffTauPhi, OffTauEnergy, OffTausPassFilter)
      sizeOffTaus = len(OffTaus)
      if (sizeOffTaus < 1): continue

      # remove any jets from container that is overlapped with the leading tau 
      OffJets = [OffJets[i] for i in range(sizeOffJets) if ROOT.TLorentzVector.DeltaR(OffTaus[0], OffJets[i]) >= 0.5]
      sizeOffJets = len(OffJets)
      if (sizeOffJets < 2): continue

 
      # lepton hadronic activity variable
      # "how well is this lepton isolated, given information about its PF sums for Charged&Neutral Hadrons and Photons"
      # slide 5 of this presentation: https://docs.google.com/presentation/d/1Bsz5eBHYlQSg5Lfay8OyL1wf67CuzixNds9wQIgAfgk/edit?usp=sharing
      # TODO: confirm if Tyler's code was an error or if the AN was wrong, check later papers for rel iso description
      # PU = rho*EffectiveArea in eta-phi, but we have a PU branch?
      # could do list comprehension but it's hard to read
      PassMuIso = []
      for i in range(len(OffMuPFChIso)):
        firstTerm = OffMuPFChIso[i]
        secondTerm = OffMuPFNeuIso[i] + OffMuPFPhoIso[i] - 0.5 * OffMuPFPUIso[i]
        secondTerm = max([0., secondTerm]) #make term zero if above is negative
        Iso = (firstTerm + secondTerm) / OffMuPt[i]
        if (Iso < 0.15): PassMuIso.append(i)
     
      # TODO: see impact of 2.3 (can't find 2.1 in AN)
      MuEtaToPass = 2.1
      PassMuID =  [i for i in range(len(OffMuID)) if OffMuID[i] >= 1]
      PassMuEta = [i for i in range(len(OffMuEta)) if abs(OffMuEta[i]) <= MuEtaToPass]
      OffMusPassFilter = list(set(PassMuIso) & set(PassMuID) & set(PassMuEta))
      if (len(OffMusPassFilter) == 0): continue
      OffMus = fillWithTVecs(OffMuPt, OffMuEta, OffMuPhi, OffMuEnergy, OffMusPassFilter)
      sizeOffMus = len(OffMus)
      if (sizeOffMus < 1): continue

      # remove any jets from container that are overlapped with the leading muon
      OffJets = [OffJets[i] for i in range(sizeOffJets) if ROOT.TLorentzVector.DeltaR(OffMus[0], OffJets[i]) >= 0.5]
      sizeOffJets = len(OffJets)
      if (sizeOffJets < 2): continue

      # skip the event if the tau and electron are overlapped
      if (ROOT.TLorentzVector.DeltaR(OffMus[0], OffTaus[0]) < 0.5): continue

      # skip the event if the tau and electron have the same charge
      if (OffMuCh[OffMusPassFilter[0]] == OffTauCh[OffTausPassFilter[0]]): continue

      # assign Offline objects
      OffTau = OffTaus[0] # consider selecting tau based on isolation, not pt
      OffMu = OffMus[0]
      OffJet1Index, OffJet2Index, OffMjj = highestMjjPair(OffJets)
      OffJet1 = OffJets[OffJet1Index]
      OffJet2 = OffJets[OffJet2Index]
      if (ROOT.TLorentzVector.DeltaR(OffJet1, OffJet2) < 0.5): continue

      # Matching
      # MuTau HLT Matching
      MuTauHLTMuons = fillWithTVecs(MuTauFinalMuonFilter_pt, MuTauFinalMuonFilter_eta,
                                    MuTauFinalMuonFilter_phi, MuTauFinalMuonFilter_energy)
      matchMuTauHLTMuon = matchHLTOff(MuTauHLTMuons, OffMu)

      MuTauHLTTaus = fillWithTVecs(MuTauFinalTauFilter_pt, MuTauFinalTauFilter_eta,
                                    MuTauFinalTauFilter_phi, MuTauFinalTauFilter_energy)
      matchMuTauHLTTau = matchHLTOff(MuTauHLTTaus, OffTau)

      passMuTauHLTOffMatching = matchMuTauHLTMuon and matchMuTauHLTTau

      # Single Mu HLT Matching
      SingleMuHLTMuons = fillWithTVecs(SingleMuAndLowerMuTauFinalFilter_pt, SingleMuAndLowerMuTauFinalFilter_eta,
                        SingleMuAndLowerMuTauFinalFilter_phi, SingleMuAndLowerMuTauFinalFilter_energy)
      passSingleMuHLTOffMatching = matchHLTOff(SingleMuHLTMuons, OffMu)

      # VBF Mu HLT Matching 
      VBFMuHLTMuons = fillWithTVecs(VBFMuonFinalMuonFilter_pt, VBFMuonFinalMuonFilter_eta,
                                    VBFMuonFinalMuonFilter_phi, VBFMuonFinalMuonFilter_energy)
      matchVBFMuHLTMuon = matchHLTOff(VBFMuHLTMuons, OffMu)

      VBFMuHLTJets = fillWithTVecs(VBFMuonFinalJetFilter_pt, VBFMuonFinalJetFilter_eta,
                                   VBFMuonFinalJetFilter_phi, VBFMuonFinalJetFilter_energy)
      matchVBFMuHLTJet1 = matchHLTOff(VBFMuHLTJets, OffJet1)
      matchVBFMuHLTJet2 = matchHLTOff(VBFMuHLTJets, OffJet2)

      passVBFMuHLTOffMatching = matchVBFMuHLTMuon and matchVBFMuHLTJet1 and matchVBFMuHLTJet2

      # VBF Single Tau HLT Matching
      VBFSingleTauHLTIsoTau = fillWithTVecs(VBFSingleTauFinalTauFilter_pt, VBFSingleTauFinalTauFilter_eta,
                                            VBFSingleTauFinalTauFilter_phi, VBFSingleTauFinalTauFilter_energy)
      matchVBFSingleTauHLTIsoTau = matchHLTOff(VBFSingleTauHLTIsoTau, OffTau)

      VBFSingleTauHLTJets = fillWithTVecs(VBFSingleTauFinalJetFilter_pt, VBFSingleTauFinalJetFilter_eta,
                                   VBFSingleTauFinalJetFilter_phi, VBFSingleTauFinalJetFilter_energy)
      matchVBFSingleTauHLTJet1 = matchHLTOff(VBFSingleTauHLTJets, OffJet1)
      matchVBFSingleTauHLTJet2 = matchHLTOff(VBFSingleTauHLTJets, OffJet2)

      passVBFSingleTauHLTOffMatching = (matchVBFSingleTauHLTIsoTau and matchVBFSingleTauHLTJet1 and matchVBFSingleTauHLTJet2)

      # end matching

      passMuTauOffCuts = False
      if (OffJet1.Pt() >= 30
       and OffJet2.Pt() >= 30
       and OffMjj >= 300 # crazy loose, no? can't find source for this
       and OffTau.Pt() >= 30
       and OffMu.Pt() >= 21): passMuTauOffCuts = True

      passSingleMuOffCuts = (passMuTauOffCuts and OffMu.Pt() >= 25)

      passVBFMuOffCuts = False
      if (OffJet1.Pt()  >= 85 
       and OffJet2.Pt() >= 35
       and OffMjj       >= 600
       and OffTau.Pt()  >= 30
       and OffMu.Pt()  >= 4): passVBFMuOffCuts = True

      passVBFSingleTauOffCuts = False
      if (OffJet1.Pt()  >= 45
       and OffJet2.Pt() >= 45
       and OffMjj       >= 600
       and OffTau.Pt()  >= 50
       and OffMu.Pt()   >= 5): passVBFSingleTauOffCuts = True


      # now tally it up
      GoodMuTau = passMuTauHLTOffMatching and passMuTauOffCuts and passMuTauHLT[0]
      #GoodSingleMu = passSingleMuHLTOffMatching and passSingleMuOffCuts and passIsoMu24eta2p1HLT[0]
      GoodSingleMu = passSingleMuOffCuts and passIsoMu24eta2p1HLT[0]
      GoodVBFMu = passVBFMuHLTOffMatching and passVBFMuOffCuts and passVBFMuonHLT[0]
      GoodVBFSingleTau = passVBFSingleTauHLTOffMatching and passVBFSingleTauOffCuts and passVBFSingleTauHLT[0]


      # enough to calculate impact of VBF Mu, MuTau and SingleMu will be main overlap at analysis
      if (GoodVBFMu): TallyVBFMuOff += 1
      if (GoodVBFSingleTau): TallyVBFSingleTauOff += 1
      if (GoodMuTau): TallyMuTauOff += 1
      if (GoodSingleMu): TallySingleMuOff += 1

      if (GoodVBFMu or GoodMuTau): TallyVBFMuORMuTauOff += 1
      if (GoodVBFMu or GoodSingleMu): TallyVBFMuORSingleMuOff += 1
      if (GoodMuTau or GoodSingleMu): TallyMuTauORSingleMuOff += 1

      if (GoodVBFMu or GoodMuTau or GoodSingleMu): TallyTripleOROff += 1
      if (GoodVBFMu or GoodVBFSingleTau or GoodMuTau or GoodSingleMu): TallyQuadOROff += 1

      Off_Tallies = [TallyVBFMuOff, TallyMuTauOff, TallySingleMuOff, TallyVBFSingleTauOff,
                     TallyVBFMuORMuTauOff, TallyVBFMuORSingleMuOff, TallyMuTauORSingleMuOff, 
                     TallyTripleOROff, TallyQuadOROff]

  # print output
  print("\033[42m" + f"nViableEvents: {viableEventCounter}" + "\033[0m")

  print("-"*40)
  if (notRateStudy):
    labels = ["VBF+Mu (1)", "MuTau (2)", "SingleMu(3)", "VBF1Tau(*)",
              "1OR2", "1OR3", "2OR3", 
              "TripleOR", "QuadOR"]
    for index, label in enumerate(labels):
      print(f"{label:19}, {Off_Tallies[index]:7}")

  if (rateStudy):
    labels = ["VBF+Mu", "VBFDiJetOR", "VBFIsoTau", "DummyEGL1", 
              "VBFDiJetORVBFDiTau", "NotVBFEG", "VBFTripleOR", "QuadOR", "UniqueVBFMu"]
    for index, label in enumerate(labels):
      print(f"{label:19}, {L1_Tallies[index]:7}")

    uniqueL1VBFEG = L1_Tallies[-1]
    lumiScaling = 2. / rateDictionary[rateStudyString]["approxLumi"]
    rate_factor = rateDictionary[rateStudyString]["nBunches"] * 11245.6 * lumiScaling
    if (viableEventCounter <= 0):
      print("\033\[31m" + "No viable events" + "\033\[0m")
    else: 
      rate_factor = rate_factor / viableEventCounter
      print("#"*40)
      print("Rate Factor = nBunches * 11245.6 Hz * (Target Lumi / Avg. LS Lumi) / nEventsProcessed")
      print(f"Rate Factor = {rate_factor} Hz / Event : Rate = rate_factor * nEventsPassingCriteria")
      print(f"UNpure rate = {rate_factor * TallyL1VBFDiJetEG},  PURE rate = {rate_factor * uniqueL1VBFEG}")


