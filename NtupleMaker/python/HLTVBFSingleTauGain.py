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
# python3 L1VBFIsoTauEff.py -i ../../../../samples/VBFE_wMuTauFilters.root -r NOTRATE -L 0

# rate mode
# python3 L1VBFIsoTauEff.py -i ../../../../../samples/EZBs/EZB_2018/EZB1_EGOR.root -r 2018O -L 0

# multifile
# for line in `cat rate_files.txt`; do echo $line; python3 L1VBFIsoTauEff.py -i $line -r 2022G_PU60 -DT 34 -DJ 35 >> rate_total_output.txt; done

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

  # L1
  passL1VBFDiJetIsoTau = array('i', [0])
  tree.SetBranchAddress("passhltL1VBFDiJetIsoTau", passL1VBFDiJetIsoTau)
  L1JetPt = ROOT.std.vector('float')()
  L1JetEta = ROOT.std.vector('float')()
  L1JetPhi = ROOT.std.vector('float')()
  L1JetEnergy = ROOT.std.vector('float')()
  tree.SetBranchAddress("hltL1VBFDiJetIsoTau_jetPt", L1JetPt)
  tree.SetBranchAddress("hltL1VBFDiJetIsoTau_jetEta", L1JetEta)
  tree.SetBranchAddress("hltL1VBFDiJetIsoTau_jetPhi", L1JetPhi)
  tree.SetBranchAddress("hltL1VBFDiJetIsoTau_jetEnergy", L1JetEnergy)
  L1IsoTauPt = ROOT.std.vector('float')()
  L1IsoTauEta = ROOT.std.vector('float')()
  L1IsoTauPhi = ROOT.std.vector('float')()
  L1IsoTauEnergy = ROOT.std.vector('float')()
  tree.SetBranchAddress("hltL1VBFDiJetIsoTau_tauPt", L1IsoTauPt)
  tree.SetBranchAddress("hltL1VBFDiJetIsoTau_tauEta", L1IsoTauEta)
  tree.SetBranchAddress("hltL1VBFDiJetIsoTau_tauPhi", L1IsoTauPhi)
  tree.SetBranchAddress("hltL1VBFDiJetIsoTau_tauEnergy", L1IsoTauEnergy)


  # L1 overlaps
  passL1VBFDiJetOR = array('i', [0])
  tree.SetBranchAddress("passhltL1VBFDiJetOR", passL1VBFDiJetOR)
  L1VBFDiJetOR_pt = ROOT.std.vector('float')()
  L1VBFDiJetOR_eta = ROOT.std.vector('float')()
  L1VBFDiJetOR_phi = ROOT.std.vector('float')()
  L1VBFDiJetOR_energy = ROOT.std.vector('float')()
  tree.SetBranchAddress("hltL1VBFDiJetOR_pt", L1VBFDiJetOR_pt)
  tree.SetBranchAddress("hltL1VBFDiJetOR_eta", L1VBFDiJetOR_eta)
  tree.SetBranchAddress("hltL1VBFDiJetOR_phi", L1VBFDiJetOR_phi)
  tree.SetBranchAddress("hltL1VBFDiJetOR_energy", L1VBFDiJetOR_energy)

  passL1DiTau = array('i', [0])
  tree.SetBranchAddress("passhltL1sDoubleTauBigOR", passL1DiTau)
  L1DiTau_pt = ROOT.std.vector('float')()
  tree.SetBranchAddress("hltL1sDoubleTauBigOR_pt", L1DiTau_pt)

  # VBFDiTau HLT
  VBFDiTauFinalJetFilter_pt = ROOT.std.vector('float')()
  VBFDiTauFinalJetFilter_eta = ROOT.std.vector('float')()
  VBFDiTauFinalJetFilter_phi = ROOT.std.vector('float')()
  VBFDiTauFinalJetFilter_energy = ROOT.std.vector('float')()
  tree.SetBranchAddress("VBF2DTDoubleJetFinalFilter_pt", VBFDiTauFinalJetFilter_pt)
  tree.SetBranchAddress("VBF2DTDoubleJetFinalFilter_eta", VBFDiTauFinalJetFilter_eta)
  tree.SetBranchAddress("VBF2DTDoubleJetFinalFilter_phi", VBFDiTauFinalJetFilter_phi) 
  tree.SetBranchAddress("VBF2DTDoubleJetFinalFilter_energy", VBFDiTauFinalJetFilter_energy)
  # ERROR these branches are not filled in the sample
  VBFDiTauFinalTauFilter_pt = ROOT.std.vector('float')()
  VBFDiTauFinalTauFilter_eta = ROOT.std.vector('float')()
  VBFDiTauFinalTauFilter_phi = ROOT.std.vector('float')()
  VBFDiTauFinalTauFilter_energy = ROOT.std.vector('float')()
  tree.SetBranchAddress("VBF2DTDoubleTauFinalFilter_pt", VBFDiTauFinalTauFilter_pt)
  tree.SetBranchAddress("VBF2DTDoubleTauFinalFilter_eta", VBFDiTauFinalTauFilter_eta)
  tree.SetBranchAddress("VBF2DTDoubleTauFinalFilter_phi", VBFDiTauFinalTauFilter_phi)
  tree.SetBranchAddress("VBF2DTDoubleTauFinalFilter_energy", VBFDiTauFinalTauFilter_energy)
  #
  VBFDiTauL1MatchedTauFinalFilter_pt = ROOT.std.vector('float')()
  VBFDiTauL1MatchedTauFinalFilter_eta = ROOT.std.vector('float')()
  VBFDiTauL1MatchedTauFinalFilter_phi = ROOT.std.vector('float')()
  VBFDiTauL1MatchedTauFinalFilter_energy = ROOT.std.vector('float')()
  tree.SetBranchAddress("VBF2DTL1MatchedTauFinalFilter_pt", VBFDiTauL1MatchedTauFinalFilter_pt)
  tree.SetBranchAddress("VBF2DTL1MatchedTauFinalFilter_eta", VBFDiTauL1MatchedTauFinalFilter_eta)
  tree.SetBranchAddress("VBF2DTL1MatchedTauFinalFilter_phi", VBFDiTauL1MatchedTauFinalFilter_phi)
  tree.SetBranchAddress("VBF2DTL1MatchedTauFinalFilter_energy", VBFDiTauL1MatchedTauFinalFilter_energy)
  #
  # VBF SingleTau HLT
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

  # DiJetInc HLT
  InclusiveVBFBothTausFinalFilter_pt = ROOT.std.vector('float')()
  InclusiveVBFBothTausFinalFilter_eta = ROOT.std.vector('float')()
  InclusiveVBFBothTausFinalFilter_phi = ROOT.std.vector('float')()
  InclusiveVBFBothTausFinalFilter_energy = ROOT.std.vector('float')()
  tree.SetBranchAddress("InclusiveVBFBothTausFinalFilter_pt", InclusiveVBFBothTausFinalFilter_pt)
  tree.SetBranchAddress("InclusiveVBFBothTausFinalFilter_eta", InclusiveVBFBothTausFinalFilter_eta)
  tree.SetBranchAddress("InclusiveVBFBothTausFinalFilter_phi", InclusiveVBFBothTausFinalFilter_phi)
  tree.SetBranchAddress("InclusiveVBFBothTausFinalFilter_energy", InclusiveVBFBothTausFinalFilter_energy)

  InclusiveVBFBothJetsFinalFilter_pt = ROOT.std.vector('float')()
  InclusiveVBFBothJetsFinalFilter_eta = ROOT.std.vector('float')()
  InclusiveVBFBothJetsFinalFilter_phi = ROOT.std.vector('float')()
  InclusiveVBFBothJetsFinalFilter_energy = ROOT.std.vector('float')()
  tree.SetBranchAddress("InclusiveVBFBothJetsFinalFilter_pt", InclusiveVBFBothJetsFinalFilter_pt)
  tree.SetBranchAddress("InclusiveVBFBothJetsFinalFilter_eta", InclusiveVBFBothJetsFinalFilter_eta)
  tree.SetBranchAddress("InclusiveVBFBothJetsFinalFilter_phi", InclusiveVBFBothJetsFinalFilter_phi)
  tree.SetBranchAddress("InclusiveVBFBothJetsFinalFilter_energy", InclusiveVBFBothJetsFinalFilter_energy)

  InclusiveVBFLeadingJetFinalFilter_pt = ROOT.std.vector('float')()
  InclusiveVBFLeadingJetFinalFilter_eta = ROOT.std.vector('float')()
  InclusiveVBFLeadingJetFinalFilter_phi = ROOT.std.vector('float')()
  InclusiveVBFLeadingJetFinalFilter_energy = ROOT.std.vector('float')()
  tree.SetBranchAddress("InclusiveVBFLeadingJetFinalFilter_pt", InclusiveVBFLeadingJetFinalFilter_pt)
  tree.SetBranchAddress("InclusiveVBFLeadingJetFinalFilter_eta", InclusiveVBFLeadingJetFinalFilter_eta)
  tree.SetBranchAddress("InclusiveVBFLeadingJetFinalFilter_phi", InclusiveVBFLeadingJetFinalFilter_phi)
  tree.SetBranchAddress("InclusiveVBFLeadingJetFinalFilter_energy", InclusiveVBFLeadingJetFinalFilter_energy)


  # DiTau HLT
  DiTauFinalFilter_pt = ROOT.std.vector('float')()
  DiTauFinalFilter_eta = ROOT.std.vector('float')()
  DiTauFinalFilter_phi = ROOT.std.vector('float')()
  DiTauFinalFilter_energy = ROOT.std.vector('float')()
  tree.SetBranchAddress("DiTauFinalFilter_pt", DiTauFinalFilter_pt)
  tree.SetBranchAddress("DiTauFinalFilter_eta", DiTauFinalFilter_eta)
  tree.SetBranchAddress("DiTauFinalFilter_phi", DiTauFinalFilter_phi)
  tree.SetBranchAddress("DiTauFinalFilter_energy", DiTauFinalFilter_energy)

  # HLT final decisions
  passVBFDiTauHLT = array('i', [0])
  tree.SetBranchAddress("passVBF2DTHLT", passVBFDiTauHLT)

  passVBFSingleTauHLT = array('i', [0])
  tree.SetBranchAddress("passVBF1DTHLT_CorrChecker", passVBFSingleTauHLT)

  passInclusiveVBFHLT = array('i', [0])
  tree.SetBranchAddress("passDeepInclusiveVBFHLT", passInclusiveVBFHLT)

  passDiTauHLT = array('i', [0])
  tree.SetBranchAddress("passDeepDiTau35HLT", passDiTauHLT)


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
  
    # Offline Ids
    OffTauIDvsJet = ROOT.std.vector('bool')()
    OffTauIDvsEle = ROOT.std.vector('bool')()
    OffTauIDvsMuon = ROOT.std.vector('bool')()
    tree.SetBranchAddress("tauByMediumDeepTau2017v2p1VSjet", OffTauIDvsJet)
    tree.SetBranchAddress("tauByVVVLooseDeepTau2017v2p1VSe", OffTauIDvsEle)
    tree.SetBranchAddress("tauByVLooseDeepTau2017v2p1VSmu", OffTauIDvsMuon)

    OffJetPFLooseID = ROOT.std.vector('bool')()
    OffJetID = ROOT.std.vector('int')()
    OffJetPUID = ROOT.std.vector('float')()
    OffJetPUFullID = ROOT.std.vector('int')()
    tree.SetBranchAddress("jetPFLooseId", OffJetPFLooseID)
    tree.SetBranchAddress("jetID", OffJetID)
    tree.SetBranchAddress("jetPUID", OffJetPUID)
    tree.SetBranchAddress("jetPUFullID", OffJetPUFullID)

  TallyVBFDiTauHLT = 0
  TallyVBFSingleTauHLT = 0
  TallyInclusiveVBFHLT = 0
  TallyDiTauHLT = 0
  TallyVBFDiTauORInclusiveVBFHLT = 0
  TallyVBFDiTauORDiTauHLT = 0
  TallyInclusiveVBFORDiTauHLT = 0
  TallyTripleORHLT = 0
  TallyQuadORHLT = 0

  TallyVBFDiTauOff = 0
  TallyVBFSingleTauOff = 0
  TallyDiTauOff = 0
  TallyInclusiveVBFOff = 0
  TallyVBFDiTauORDiTauOff = 0
  TallyVBFDiTauORInclusiveVBFOff = 0
  TallyInclusiveVBFORDiTauOff = 0
  TallyTripleOROff = 0
  TallyQuadOROff = 0

  TotalEntries = tree.GetEntries()
  for entry in range(TotalEntries):
    tree.GetEntry(entry)

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
  
        BoolPassVBFDiTauHLT = passVBFDiTauHLT[0] 
        BoolPassVBFSingleTauHLT = passVBFSingleTauHLT[0]
        BoolPassInclusiveVBFHLT = passInclusiveVBFHLT[0]
        BoolPassDiTauHLT = passDiTauHLT[0]

        if (BoolPassVBFDiTauHLT): TallyVBFDiTauHLT += 1
        if (BoolPassInclusiveVBFHLT): TallyInclusiveVBFHLT += 1
        if (BoolPassDiTauHLT): TallyDiTauHLT += 1

        if (BoolPassVBFDiTauHLT or BoolPassInclusiveVBFHLT): TallyVBFDiTauORInclusiveVBFHLT += 1
        if (BoolPassVBFDiTauHLT or BoolPassDiTauHLT): TallyVBFDiTauORDiTauHLT += 1
        if (BoolPassInclusiveVBFHLT or BoolPassDiTauHLT): TallyInclusiveVBFORDiTauHLT += 1

        if (BoolPassVBFDiTauHLT or BoolPassInclusiveVBFHLT or BoolPassDiTauHLT): TallyTripleORHLT += 1
        if (BoolPassVBFDiTauHLT or BoolPassVBFSingleTauHLT or BoolPassInclusiveVBFHLT or BoolPassDiTauHLT): TallyQuadORHLT += 1

  
        continue

    # requiring events to pass your L1 biases your selection, fine for gain study, not fine for eff study
    basicReqs = ( notRateStudy and (OffnJets[0] >= 2) and (OffnTaus[0] >= 2))

    if basicReqs:
      viableEventCounter += 1

      JetEtaToPass = 4.7
      PassJetID =  [i for i in range(len(OffJetID)) if OffJetID[i] >= 2]
      PassJetEta = [i for i in range(len(OffJetEta)) if abs(OffJetEta[i]) <= JetEtaToPass]
      OffJetsPassFilter = list(set(PassJetID) & set(PassJetEta))
      if (len(OffJetsPassFilter) == 0): continue
      OffJets = fillWithTVecs(OffJetPt, OffJetEta, OffJetPhi, OffJetEnergy, OffJetsPassFilter)
      sizeOffJets = len(OffJets)
      if (sizeOffJets < 2): continue
      
      # Tau ID for Tau-Tau using 2017 DeepTau version 2p1, Med vs Jet, VVVLoose vs Ele, VLoose vs Muon
      TauEtaToPass = 2.1
      PassTauID = [i for i in range(len(OffTauIDvsJet)) \
                    if (OffTauIDvsJet[i] == True and OffTauIDvsEle[i] == True and OffTauIDvsMuon[i] == True) ]  
      PassTauEta = [i for i in range(len(OffTauEta)) if abs(OffTauEta[i]) <= TauEtaToPass]
      OffTausPassFilter = list(set(PassTauID) & set(PassTauEta))
      if (len(OffTausPassFilter) == 0): continue
      OffTaus = fillWithTVecs(OffTauPt, OffTauEta, OffTauPhi, OffTauEnergy, OffTausPassFilter)
      sizeOffTaus = len(OffTaus)
      if (sizeOffTaus < 2): continue

      # remove any jets from container that are overlapped with leading or subleading tau 
      OffJets = [OffJets[i] for i in range(sizeOffJets) if ROOT.TLorentzVector.DeltaR(OffTaus[0], OffJets[i]) >= 0.5]
      sizeOffJets = len(OffJets)
      if (sizeOffJets < 2): continue
      OffJets = [OffJets[i] for i in range(sizeOffJets) if ROOT.TLorentzVector.DeltaR(OffTaus[1], OffJets[i]) >= 0.5]
      sizeOffJets = len(OffJets)
      if (sizeOffJets < 2): continue
 
      # skip the event if both taus have the same charge
      if (OffTauCh[OffTausPassFilter[0]] == OffTauCh[OffTausPassFilter[1]]): continue

      # assign Offline objects
      OffTau1 = OffTaus[0] # consider selecting tau based on isolation, not pt
      OffTau2 = OffTaus[1]
      OffJet1Index, OffJet2Index, OffMjj = highestMjjPair(OffJets)
      OffJet1 = OffJets[OffJet1Index]
      OffJet2 = OffJets[OffJet2Index]
      if (ROOT.TLorentzVector.DeltaR(OffJet1, OffJet2) < 0.5): continue

      # Matching
      # VBFDiTau HLT Matching
      VBFDiTauHLTIsoTau = fillWithTVecs(VBFDiTauL1MatchedTauFinalFilter_pt, VBFDiTauL1MatchedTauFinalFilter_eta, \
                                        VBFDiTauL1MatchedTauFinalFilter_phi, VBFDiTauL1MatchedTauFinalFilter_energy)
      matchVBFDiTauHLTTau1 = matchHLTOff(VBFDiTauHLTIsoTau, OffTau1)
      #VBFDiTauHLTTaus = fillWithTVecs(VBFDiTauFinalTauFilter_pt, VBFDiTauFinalTauFilter_eta, \
      #                                VBFDiTauFinalTauFilter_phi, VBFDiTauFinalTauFilter_energy)
      #matchVBFDiTauHLTTau2 = matchHLTOff(VBFDiTauHLTTaus, OffTau2)

      VBFDiTauHLTJets = fillWithTVecs(VBFDiTauFinalJetFilter_pt, VBFDiTauFinalJetFilter_eta, \
                                      VBFDiTauFinalJetFilter_phi, VBFDiTauFinalJetFilter_energy)
      matchVBFDiTauHLTJet1 = matchHLTOff(VBFDiTauHLTJets, OffJet1)
      matchVBFDiTauHLTJet2 = matchHLTOff(VBFDiTauHLTJets, OffJet2)
      passVBFDiTauHLTOffMatching = (matchVBFDiTauHLTTau1 #and matchVBFDiTauHLTTau2
                                    and matchVBFDiTauHLTJet1 and matchVBFDiTauHLTJet2)


      # DiTau HLT Matching
      DiTauHLTTaus = fillWithTVecs(DiTauFinalFilter_pt, DiTauFinalFilter_eta, \
                                   DiTauFinalFilter_phi, DiTauFinalFilter_energy)
      matchDiTauHLTTau1 = matchHLTOff(DiTauHLTTaus, OffTau1)
      matchDiTauHLTTau2 = matchHLTOff(DiTauHLTTaus, OffTau2)

      passDiTauHLTOffMatching = matchDiTauHLTTau1 and matchDiTauHLTTau2

      # Inclusive VBF HLT Matching
      InclusiveVBFHLTTaus = fillWithTVecs(InclusiveVBFBothTausFinalFilter_pt, InclusiveVBFBothTausFinalFilter_eta, \
                                          InclusiveVBFBothTausFinalFilter_phi, InclusiveVBFBothTausFinalFilter_energy)
      matchInclusiveVBFHLTTau1 = matchHLTOff(InclusiveVBFHLTTaus, OffTau1)
      matchInclusiveVBFHLTTau2 = matchHLTOff(InclusiveVBFHLTTaus, OffTau2)

      InclusiveVBFHLTJets = fillWithTVecs(InclusiveVBFBothJetsFinalFilter_pt, InclusiveVBFBothJetsFinalFilter_eta, \
                                          InclusiveVBFBothJetsFinalFilter_phi, InclusiveVBFBothJetsFinalFilter_energy)
      matchInclusiveVBFHLTJet1 = matchHLTOff(InclusiveVBFHLTJets, OffJet1)
      matchInclusiveVBFHLTJet2 = matchHLTOff(InclusiveVBFHLTJets, OffJet2)

      passInclusiveVBFHLTOffMatching = (matchInclusiveVBFHLTTau1 and matchInclusiveVBFHLTTau2
                                       and matchInclusiveVBFHLTJet1 and matchInclusiveVBFHLTJet2)

      # VBF Single Tau Matching
      VBFSingleTauHLTIsoTau = fillWithTVecs(VBFSingleTauFinalTauFilter_pt, VBFSingleTauFinalTauFilter_eta, 
                                            VBFSingleTauFinalTauFilter_phi, VBFSingleTauFinalTauFilter_energy)
      matchVBFSingleTauHLTIsoTau = matchHLTOff(VBFSingleTauHLTIsoTau, OffTau1)

      VBFSingleTauHLTJets = fillWithTVecs(VBFSingleTauFinalJetFilter_pt, VBFSingleTauFinalJetFilter_eta, 
                                   VBFSingleTauFinalJetFilter_phi, VBFSingleTauFinalJetFilter_energy)
      matchVBFSingleTauHLTJet1 = matchHLTOff(VBFSingleTauHLTJets, OffJet1)
      matchVBFSingleTauHLTJet2 = matchHLTOff(VBFSingleTauHLTJets, OffJet2)

      passVBFSingleTauHLTOffMatching = (matchVBFSingleTauHLTIsoTau and matchVBFSingleTauHLTJet1 and matchVBFSingleTauHLTJet2)

      # end matching
      
      # VBF DiTau (same cuts for SingleTau)
      passVBFDiTauOffCuts = False
      if (OffJet1.Pt()  >= 45
       and OffJet2.Pt() >= 45
       and OffMjj       >= 600
       and OffTau1.Pt()  >= 50
       and OffTau2.Pt()  >= 25): passVBFDiTauOffCuts = True

      # DiTau
      L1DiTauCut = 34
      BoolPassL1DiTau = passL1DiTau[0]
      if (BoolPassL1DiTau):
        L1DiTau1_pt = L1DiTau_pt[0]
        L1DiTau2_pt = L1DiTau_pt[1]
        if (L1DiTau1_pt < L1DiTauCut or L1DiTau2_pt < L1DiTauCut): BoolPassL1DiTau = False

      passDiTauOffCuts = False
      if (OffJet1.Pt()  >= 30
       and OffJet2.Pt() >= 30
       and OffMjj       >= 600
       and OffTau1.Pt()  >= 40
       and OffTau2.Pt()  >= 40): passDiTauOffCuts = True

      # Inclusive VBF
      # TODO : add back L1 emulation here, L1 used has too low kinems, should customize in conf
      passInclusiveVBFOffCuts = False
      if (OffJet1.Pt()  >= 120
       and OffJet2.Pt() >= 40
       and OffMjj       >= 700
       and OffTau1.Pt() >= 25
       and OffTau2.Pt() >= 25): passInclusiveVBFOffCuts = True

    
      # now tally it up
      # HLT
      BoolPassVBFDiTauHLT = passVBFDiTauHLT[0]
      BoolPassVBFSingleTauHLT = passVBFSingleTauHLT[0] 
      BoolPassInclusiveVBFHLT = passInclusiveVBFHLT[0]
      BoolPassDiTauHLT = passDiTauHLT[0] and BoolPassL1DiTau

      if (BoolPassVBFDiTauHLT): TallyVBFDiTauHLT += 1
      if (BoolPassVBFSingleTauHLT):  TallyVBFSingleTauHLT += 1
      if (BoolPassInclusiveVBFHLT): TallyInclusiveVBFHLT += 1
      if (BoolPassDiTauHLT): TallyDiTauHLT += 1

      if (BoolPassVBFDiTauHLT or BoolPassInclusiveVBFHLT): TallyVBFDiTauORInclusiveVBFHLT += 1
      if (BoolPassVBFDiTauHLT or BoolPassDiTauHLT): TallyVBFDiTauORDiTauHLT += 1
      if (BoolPassInclusiveVBFHLT or BoolPassDiTauHLT): TallyInclusiveVBFORDiTauHLT += 1
      if (BoolPassVBFDiTauHLT or BoolPassInclusiveVBFHLT or BoolPassDiTauHLT): TallyTripleORHLT += 1
      if (BoolPassVBFDiTauHLT or BoolPassVBFSingleTauHLT or BoolPassInclusiveVBFHLT or BoolPassDiTauHLT): TallyQuadORHLT += 1

      HLT_Tallies = [TallyVBFDiTauHLT, TallyInclusiveVBFHLT, TallyDiTauHLT, TallyVBFSingleTauHLT,
                     TallyVBFDiTauORInclusiveVBFHLT, TallyVBFDiTauORDiTauHLT, TallyInclusiveVBFORDiTauHLT,
                     TallyTripleORHLT, TallyQuadORHLT]
 
      # Offline
      GoodVBFDiTau = BoolPassVBFDiTauHLT and passVBFDiTauOffCuts and passVBFDiTauHLTOffMatching
      GoodVBFSingleTau = BoolPassVBFSingleTauHLT and passVBFDiTauOffCuts and passVBFSingleTauHLTOffMatching
      GoodInclusiveVBF = BoolPassInclusiveVBFHLT and passInclusiveVBFOffCuts and passInclusiveVBFHLTOffMatching
      GoodDiTau = BoolPassDiTauHLT and passDiTauOffCuts and passDiTauHLTOffMatching

      if (GoodVBFDiTau): TallyVBFDiTauOff += 1
      if (GoodVBFSingleTau): TallyVBFSingleTauOff += 1
      if (GoodInclusiveVBF): TallyInclusiveVBFOff += 1
      if (GoodDiTau): TallyDiTauOff += 1

      if (GoodVBFDiTau or GoodInclusiveVBF): TallyVBFDiTauORInclusiveVBFOff += 1
      if (GoodVBFDiTau or GoodDiTau): TallyVBFDiTauORDiTauOff += 1
      if (GoodInclusiveVBF or GoodDiTau): TallyInclusiveVBFORDiTauOff += 1
      if (GoodVBFDiTau or GoodInclusiveVBF or GoodDiTau): TallyTripleOROff += 1
      if (GoodVBFDiTau or GoodVBFSingleTau or GoodInclusiveVBF or GoodDiTau): TallyQuadOROff += 1

      Off_Tallies = [TallyVBFDiTauOff, TallyInclusiveVBFOff, TallyDiTauOff, TallyVBFSingleTauOff,
                     TallyVBFDiTauORInclusiveVBFOff, TallyVBFDiTauORDiTauOff, TallyInclusiveVBFORDiTauOff,
                     TallyTripleOROff, TallyQuadOROff]


  # print output
  print("\033[42m" + f"nViableEvents: {viableEventCounter}" + "\033[0m")

  if (rateStudy):
    # HLT Single Counts
    print("-------------HLT!---------------")
    values = [TallyVBFDiTauHLT, TallyInclusiveVBFHLT, TallyDiTauHLT, -999]
    print_formatted_labels_and_values(labels_single, values) 
    # HLT ORs and Unique
    uniqueVBFDiTauHLT = TallyTripleORHLT - TallyInclusiveVBFORDiTauHLT
    values = [TallyVBFDiTauORInclusiveVBFHLT, TallyInclusiveVBFORDiTauHLT, TallyVBFDiTauORDiTauHLT, \
              TallyTripleORHLT, uniqueVBFDiTauHLT]


  if (notRateStudy):
    labels = ["VBFDiTau (1)", "VBFDijet (2)", "DiTau (3)", 
              "VBF1Tau (*)",
              "1OR2", "1OR3", "2OR3", 
              "TripleOR", "QuadOR"]
    header = ["Label", "HLT", "Offline"]
    print(f"{header[0]:17}, {header[1]:7}, {header[2]:7}")
    print("-"*40)
    for index, label in enumerate(labels):
      print(f"{label:17}, {HLT_Tallies[index]:7}, {Off_Tallies[index]:7}")


