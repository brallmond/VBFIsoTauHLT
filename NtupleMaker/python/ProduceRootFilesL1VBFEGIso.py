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
  parser.add_argument('-L', '--VBFEGL1Source', dest='VBFEGL1Source', default="None", action='store',
                    help='set branches for L1 info (HLT, DummyTight, DummyLoose, DummyNo')
  args = parser.parse_args()

  inFile = ROOT.TFile.Open(args.inFilename,"READ")
  tree = inFile.Get("demo/vbf")

  ROOT.TH1.SetDefaultSumw2()

  outFile = ROOT.TFile.Open("output.root", "RECREATE")
  outtree = ROOT.TTree("outtree", "skimmed event data")

  outL1ElePt = array('f', [0.])
  outL1EleEta = array('f', [0.])
  outL1ElePhi = array('f', [0.])
  outL1OffEleMatch = array('i', [0])
  outtree.Branch("L1ElePt", outL1ElePt, 'pt/F')
  outtree.Branch("L1EleEta", outL1EleEta, 'pt/F')
  outtree.Branch("L1ElePhi", outL1ElePhi, 'pt/F')
  outtree.Branch("L1OffEleMatch", outL1OffEleMatch, 'bool/I')

  #outL1Jet1Pt = array('f', [0.])
  #outL1Jet2Pt = array('f', [0.])
  #outL1Mjj = array('f', [0.])
  #outtree.Branch("L1Jet1Pt", outL1Jet1Pt, 'pt/F')
  #outtree.Branch("L1Jet2Pt", outL1Jet2Pt, 'pt/F')
  #outtree.Branch("L1Mjj", outL1Mjj, 'mjj/F')

  outHLTElePt = array('f', [0.])
  outHLTEleEta = array('f', [0.])
  outHLTElePhi = array('f', [0.])
  outHLTOffEleMatch = array('i', [0])
  outtree.Branch("HLTElePt", outHLTElePt, 'pt/F')
  outtree.Branch("HLTEleEta", outHLTEleEta, 'pt/F')
  outtree.Branch("HLTElePhi", outHLTElePhi, 'pt/F')
  outtree.Branch("HLTOffEleMatch", outHLTOffEleMatch, 'bool/I')

  outOffElePt = array('f', [0.])
  outOffEleEta = array('f', [0.])
  outOffElePhi = array('f', [0.])
  outtree.Branch("OffElePt", outOffElePt, 'pt/F')
  outtree.Branch("OffEleEta", outOffEleEta, 'pt/F')
  outtree.Branch("OffElePhi", outOffElePhi, 'pt/F')

  outPassL1 = array('i', [0])
  outtree.Branch("PassL1", outPassL1, 'bool/I')

  outPassHLT = array('i', [0])
  outtree.Branch("PassHLT", outPassHLT, 'bool/I')

  outPassOff = array('i', [0])
  outtree.Branch("PassOff", outPassOff, 'bool/I')

  outOffTauPt = array('f', [0.])
  outOffJet1Pt = array('f', [0.])
  outOffJet2Pt = array('f', [0.])
  outOffMjj = array('f', [0.])
  outtree.Branch("OffTauPt", outOffTauPt, 'pt/F')
  outtree.Branch("OffJet1Pt", outOffJet1Pt, 'pt/F')
  outtree.Branch("OffJet2Pt", outOffJet2Pt, 'pt/F')
  outtree.Branch("OffMjj", outOffMjj, 'mjj/F')


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
  offlineObjectsViableCounter = 0

  goodRunNumber = rateDictionary[rateStudyString]["runNumber"]
  minLS = rateDictionary[rateStudyString]["minLS"]
  maxLS = rateDictionary[rateStudyString]["maxLS"]
  badLS = rateDictionary[rateStudyString]["badLS"]

  # HLT Filter Matching
  # EleTau
  PassEleTauFinalFilterTau = array('i', [0])
  tree.SetBranchAddress("passEleTauFinalFilterTau", PassEleTauFinalFilterTau)
  EleTauFinalFilterTau_pt = ROOT.std.vector('float')()
  EleTauFinalFilterTau_eta = ROOT.std.vector('float')()
  EleTauFinalFilterTau_phi = ROOT.std.vector('float')()
  EleTauFinalFilterTau_energy = ROOT.std.vector('float')()
  tree.SetBranchAddress("EleTauFinalFilterTau_pt", EleTauFinalFilterTau_pt)
  tree.SetBranchAddress("EleTauFinalFilterTau_eta", EleTauFinalFilterTau_eta)
  tree.SetBranchAddress("EleTauFinalFilterTau_phi", EleTauFinalFilterTau_phi)
  tree.SetBranchAddress("EleTauFinalFilterTau_energy", EleTauFinalFilterTau_energy)
  PassEleTauFinalFilterEle = array('i', [0])
  tree.SetBranchAddress("passEleTauFinalFilterEle", PassEleTauFinalFilterEle)
  EleTauFinalFilterEle_pt = ROOT.std.vector('float')()
  EleTauFinalFilterEle_eta = ROOT.std.vector('float')()
  EleTauFinalFilterEle_phi = ROOT.std.vector('float')()
  EleTauFinalFilterEle_energy = ROOT.std.vector('float')()
  tree.SetBranchAddress("EleTauFinalFilterEle_pt", EleTauFinalFilterEle_pt)
  tree.SetBranchAddress("EleTauFinalFilterEle_eta", EleTauFinalFilterEle_eta)
  tree.SetBranchAddress("EleTauFinalFilterEle_phi", EleTauFinalFilterEle_phi)
  tree.SetBranchAddress("EleTauFinalFilterEle_energy", EleTauFinalFilterEle_energy)
  
  # SingleTau
  PassSingleEleFinalFilter = array('i', [0])
  tree.SetBranchAddress("passSingleEleFinalFilter", PassSingleEleFinalFilter)
  SingleEleFinalFilter_pt = ROOT.std.vector('float')()
  SingleEleFinalFilter_eta = ROOT.std.vector('float')()
  SingleEleFinalFilter_phi = ROOT.std.vector('float')()
  SingleEleFinalFilter_energy = ROOT.std.vector('float')()
  tree.SetBranchAddress("SingleEleFinalFilter_pt", SingleEleFinalFilter_pt)
  tree.SetBranchAddress("SingleEleFinalFilter_eta", SingleEleFinalFilter_eta)
  tree.SetBranchAddress("SingleEleFinalFilter_phi", SingleEleFinalFilter_phi)
  tree.SetBranchAddress("SingleEleFinalFilter_energy", SingleEleFinalFilter_energy)

  PassVBFIsoEGL1 = array('i', [0])
  L1ElePt = ROOT.std.vector('float')()
  L1EleEta = ROOT.std.vector('float')()
  L1ElePhi = ROOT.std.vector('float')()
  L1EleEnergy = ROOT.std.vector('float')()
 
  L1JetPt = ROOT.std.vector('float')()
  L1JetEta = ROOT.std.vector('float')()
  L1JetPhi = ROOT.std.vector('float')()
  L1JetEnergy = ROOT.std.vector('float')()

  VBFEGL1Source = args.VBFEGL1Source
  if (VBFEGL1Source == "HLT" or VBFEGL1Source == "None"):
    tree.SetBranchAddress("passhltL1VBFIsoEG", PassVBFIsoEGL1)
    tree.SetBranchAddress("hltL1VBFElectronTightIso_RealHLT_ePt", L1ElePt)
    tree.SetBranchAddress("hltL1VBFElectronTightIso_RealHLT_eEta", L1EleEta)
    tree.SetBranchAddress("hltL1VBFElectronTightIso_RealHLT_ePhi", L1ElePhi)
    tree.SetBranchAddress("hltL1VBFElectronTightIso_RealHLT_eEnergy", L1EleEnergy)
 
    tree.SetBranchAddress("hltL1VBFElectronTightIso_RealHLT_jPt", L1JetPt)
    tree.SetBranchAddress("hltL1VBFElectronTightIso_RealHLT_jEta", L1JetEta)
    tree.SetBranchAddress("hltL1VBFElectronTightIso_RealHLT_jPhi", L1JetPhi)
    tree.SetBranchAddress("hltL1VBFElectronTightIso_RealHLT_jEnergy", L1JetEnergy)

  elif (VBFEGL1Source == "TightDummy"):
    tree.SetBranchAddress("passhltL1VBFElectronTightIso", PassVBFIsoEGL1)

    tree.SetBranchAddress("hltL1VBFElectronTightIso_ePt", L1ElePt)
    tree.SetBranchAddress("hltL1VBFElectronTightIso_eEta", L1EleEta)
    tree.SetBranchAddress("hltL1VBFElectronTightIso_ePhi", L1ElePhi)
    tree.SetBranchAddress("hltL1VBFElectronTightIso_eEnergy", L1EleEnergy)
 
    tree.SetBranchAddress("hltL1VBFElectronTightIso_jPt", L1JetPt)
    tree.SetBranchAddress("hltL1VBFElectronTightIso_jEta", L1JetEta)
    tree.SetBranchAddress("hltL1VBFElectronTightIso_jPhi", L1JetPhi)
    tree.SetBranchAddress("hltL1VBFElectronTightIso_jEnergy", L1JetEnergy)

  elif (VBFEGL1Source == "LooseDummy"):
    tree.SetBranchAddress("passhltL1VBFElectronLooseIso", PassVBFIsoEGL1)

    tree.SetBranchAddress("hltL1VBFElectronLooseIso_ePt", L1ElePt)
    tree.SetBranchAddress("hltL1VBFElectronLooseIso_eEta", L1EleEta)
    tree.SetBranchAddress("hltL1VBFElectronLooseIso_ePhi", L1ElePhi)
    tree.SetBranchAddress("hltL1VBFElectronLooseIso_eEnergy", L1EleEnergy)
 
    tree.SetBranchAddress("hltL1VBFElectronLooseIso_jPt", L1JetPt)
    tree.SetBranchAddress("hltL1VBFElectronLooseIso_jEta", L1JetEta)
    tree.SetBranchAddress("hltL1VBFElectronLooseIso_jPhi", L1JetPhi)
    tree.SetBranchAddress("hltL1VBFElectronLooseIso_jEnergy", L1JetEnergy)

  elif (VBFEGL1Source == "NoDummy"):
    tree.SetBranchAddress("passhltL1VBFElectronNoIso", PassVBFIsoEGL1)

    tree.SetBranchAddress("hltL1VBFElectronNoIso_ePt", L1ElePt)
    tree.SetBranchAddress("hltL1VBFElectronNoIso_eEta", L1EleEta)
    tree.SetBranchAddress("hltL1VBFElectronNoIso_ePhi", L1ElePhi)
    tree.SetBranchAddress("hltL1VBFElectronNoIso_eEnergy", L1EleEnergy)
 
    tree.SetBranchAddress("hltL1VBFElectronNoIso_jPt", L1JetPt)
    tree.SetBranchAddress("hltL1VBFElectronNoIso_jEta", L1JetEta)
    tree.SetBranchAddress("hltL1VBFElectronNoIso_jPhi", L1JetPhi)
    tree.SetBranchAddress("hltL1VBFElectronNoIso_jEnergy", L1JetEnergy)
  
  else:
    print(f"VBFEGL1Source not set, exiting...")
    sys.exit()


  # VBF Ele
  VBFEleFinalEleFilter_pt = ROOT.std.vector('float')()
  VBFEleFinalEleFilter_eta = ROOT.std.vector('float')()
  VBFEleFinalEleFilter_phi = ROOT.std.vector('float')()
  VBFEleFinalEleFilter_energy = ROOT.std.vector('float')()
  tree.SetBranchAddress("VBFElectronFinalFilter_EleCrossClean_pt", VBFEleFinalEleFilter_pt)
  tree.SetBranchAddress("VBFElectronFinalFilter_EleCrossClean_eta", VBFEleFinalEleFilter_eta)
  tree.SetBranchAddress("VBFElectronFinalFilter_EleCrossClean_phi", VBFEleFinalEleFilter_phi)
  tree.SetBranchAddress("VBFElectronFinalFilter_EleCrossClean_energy", VBFEleFinalEleFilter_energy)
  VBFEleFinalJetFilter_pt = ROOT.std.vector('float')()
  VBFEleFinalJetFilter_eta = ROOT.std.vector('float')()
  VBFEleFinalJetFilter_phi = ROOT.std.vector('float')()
  VBFEleFinalJetFilter_energy = ROOT.std.vector('float')()
  tree.SetBranchAddress("VBFElectronBothJetsFinalFilter_MatchAndMjjCut_pt", VBFEleFinalJetFilter_pt)
  tree.SetBranchAddress("VBFElectronBothJetsFinalFilter_MatchAndMjjCut_eta", VBFEleFinalJetFilter_eta)
  tree.SetBranchAddress("VBFElectronBothJetsFinalFilter_MatchAndMjjCut_phi", VBFEleFinalJetFilter_phi)
  tree.SetBranchAddress("VBFElectronBothJetsFinalFilter_MatchAndMjjCut_energy", VBFEleFinalJetFilter_energy)

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
  passEleTauHLT = array('i', [0])
  tree.SetBranchAddress("passEleTauHLT", passEleTauHLT)

  passSingleEleHLT = array('i', [0])
  tree.SetBranchAddress("passSingleEleHLT", passSingleEleHLT)

  passVBFEleHLT = array('i', [0])
  tree.SetBranchAddress("passVBFEleHLT", passVBFEleHLT)

  passVBFSingleTauHLT = array('i', [0])
  tree.SetBranchAddress("passVBF1DTHLT_CorrChecker", passVBFSingleTauHLT)

  # 6 dummy HLTs
  passHLT_Dummy_L1VBFEG_TightIso = array('i', [0])
  tree.SetBranchAddress("passHLT_Dummy_L1VBFEG_TightIso", passHLT_Dummy_L1VBFEG_TightIso)

  passHLT_Dummy_L1VBFEG_LooseIso = array('i', [0])
  tree.SetBranchAddress("passHLT_Dummy_L1VBFEG_LooseIso", passHLT_Dummy_L1VBFEG_LooseIso)

  passHLT_Dummy_L1VBFEG_NoIso = array('i', [0])
  tree.SetBranchAddress("passHLT_Dummy_L1VBFEG_NoIso", passHLT_Dummy_L1VBFEG_NoIso)

  passHLT_Dummy_L1EG_TightIso = array('i', [0])
  tree.SetBranchAddress("passHLT_Dummy_L1EG_TightIso", passHLT_Dummy_L1EG_TightIso)

  passHLT_Dummy_L1EG_LooseIso = array('i', [0])
  tree.SetBranchAddress("passHLT_Dummy_L1EG_LooseIso", passHLT_Dummy_L1EG_LooseIso)

  passHLT_Dummy_L1EG_NoIso = array('i', [0])
  tree.SetBranchAddress("passHLT_Dummy_L1EG_NoIso", passHLT_Dummy_L1EG_NoIso)


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
    ##Electrons
    OffnEles = array('i', [0])
    OffEleCh = ROOT.std.vector('float')()
    OffElePt = ROOT.std.vector('float')()
    OffEleEta = ROOT.std.vector('float')()
    OffElePhi = ROOT.std.vector('float')()
    OffEleEnergy = ROOT.std.vector('float')()
    tree.SetBranchAddress("nEle", OffnEles)
    tree.SetBranchAddress("eleCharge", OffEleCh)
    tree.SetBranchAddress("elePt", OffElePt)
    tree.SetBranchAddress("eleEta", OffEleEta)
    tree.SetBranchAddress("elePhi", OffElePhi)
    tree.SetBranchAddress("eleEnergy", OffEleEnergy)
  
    OffElePFChIso = ROOT.std.vector('float')()
    OffElePFPUIso = ROOT.std.vector('float')()
    OffElePFNeuIso = ROOT.std.vector('float')()
    OffElePFPhoIso = ROOT.std.vector('float')()
    tree.SetBranchAddress("elePFPUIso", OffElePFPUIso)
    tree.SetBranchAddress("elePFChIso", OffElePFChIso)
    tree.SetBranchAddress("elePFNeuIso", OffElePFNeuIso)
    tree.SetBranchAddress("elePFPhoIso", OffElePFPhoIso)
  
    # Offline Ids
    OffTauIDvsJet = ROOT.std.vector('bool')()
    OffTauIDvsEle = ROOT.std.vector('bool')()
    OffTauIDvsMuon = ROOT.std.vector('bool')()
    tree.SetBranchAddress("tauByMediumDeepTau2017v2p1VSjet", OffTauIDvsJet)
    tree.SetBranchAddress("tauByTightDeepTau2017v2p1VSe", OffTauIDvsEle)
    tree.SetBranchAddress("tauByVLooseDeepTau2017v2p1VSmu", OffTauIDvsMuon)

    OffJetPFLooseID = ROOT.std.vector('bool')()
    OffJetID = ROOT.std.vector('int')()
    OffJetPUID = ROOT.std.vector('float')()
    OffJetPUFullID = ROOT.std.vector('int')()
    tree.SetBranchAddress("jetPFLooseId", OffJetPFLooseID)
    tree.SetBranchAddress("jetID", OffJetID)
    tree.SetBranchAddress("jetPUID", OffJetPUID)
    tree.SetBranchAddress("jetPUFullID", OffJetPUFullID)

    OffEleID = ROOT.std.vector('int')()
    tree.SetBranchAddress("eleIDMVANoIsowp90", OffEleID)

  TallyVBFEleL1 = 0
  TallySingleEleL1 = 0
  TallyVBFEleORSingleEleL1 = 0

  TallyVBFEleHLT = 0
  TallySingleEleHLT = 0
  TallyVBFEleORSingleEleHLT = 0

  TallyVBFEleOff = 0
  TallySingleEleOff = 0
  TallyVBFEleORSingleEleOff = 0

  TotalEntries = tree.GetEntries()
  for entry in range(TotalEntries):
    tree.GetEntry(entry)
  
    basicReqs = ( notRateStudy and (OffnJets[0] >= 2) and (OffnEles[0] >= 1) and (OffnTaus[0] >= 1) )

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
      PassEleIso = []
      for i in range(len(OffElePFChIso)):
        firstTerm = OffElePFChIso[i]
        secondTerm = OffElePFNeuIso[i] + OffElePFPhoIso[i] - 0.5 * OffElePFPUIso[i]
        secondTerm = max([0., secondTerm]) #make term zero if above is negative
        Iso = (firstTerm + secondTerm) / OffElePt[i]
        if (Iso < 0.15): PassEleIso.append(i)
     
      EleEtaToPass = 2.1
      PassEleID =  [i for i in range(len(OffEleID)) if OffEleID[i] >= 1] # Ele ID is eleIDMVANoIsowp90
      PassEleEta = [i for i in range(len(OffEleEta)) if abs(OffEleEta[i]) <= EleEtaToPass]
      OffElesPassFilter = list(set(PassEleIso) & set(PassEleID) & set(PassEleEta))
      if (len(OffElesPassFilter) == 0): continue
      OffEles = fillWithTVecs(OffElePt, OffEleEta, OffElePhi, OffEleEnergy, OffElesPassFilter)
      sizeOffEles = len(OffEles)
      if (sizeOffEles < 1): continue

      # remove any jets from container that are overlapped with the leading electron
      OffJets = [OffJets[i] for i in range(sizeOffJets) if ROOT.TLorentzVector.DeltaR(OffEles[0], OffJets[i]) >= 0.5]
      sizeOffJets = len(OffJets)
      if (sizeOffJets < 2): continue

      # skip the event if the tau and electron are overlapped
      if (ROOT.TLorentzVector.DeltaR(OffEles[0], OffTaus[0]) < 0.5): continue

      # skip the event if the tau and electron have the same charge
      if (OffEleCh[OffElesPassFilter[0]] == OffTauCh[OffTausPassFilter[0]]): continue

      # assign Offline objects
      OffTau = OffTaus[0] # consider selecting tau based on isolation, not pt
      OffEle = OffEles[0]
      OffJet1Index, OffJet2Index, OffMjj = highestMjjPair(OffJets)
      OffJet1 = OffJets[OffJet1Index]
      OffJet2 = OffJets[OffJet2Index]
      if (ROOT.TLorentzVector.DeltaR(OffJet1, OffJet2) < 0.5): continue

      outOffElePt[0] = OffEle.Pt()
      outOffEleEta[0] = OffEle.Eta()
      outOffElePhi[0] = OffEle.Phi()

      offlineObjectsViableCounter += 1
      #if (offlineObjectsViableCounter >= 8718): break

      # get L1 objects 
      L1Eles = fillWithTVecs(L1ElePt, L1EleEta, L1ElePhi, L1EleEnergy)
      sizeL1Eles = len(L1Eles)
      L1Jets = fillWithTVecs(L1JetPt, L1JetEta, L1JetPhi, L1JetEnergy)
      sizeL1Jets = len(L1Jets)

      L1JetsThatOverlapL1Eles = []
      for i in range(sizeL1Eles):
        for j in range(sizeL1Jets):
          if (ROOT.TLorentzVector.DeltaR(L1Eles[i], L1Jets[j]) < 0.2):
            L1JetsThatOverlapL1Eles.append(j)
      #L1Jets = [L1Jets[i] for i in range(sizeL1Jets) if i not in L1JetsThatOverlapL1Eles]
      #sizeL1Jets = len(L1Jets)

      matchL1Off = False
      if (sizeL1Jets >= 2 and sizeL1Eles >= 1 and PassVBFIsoEGL1[0]):
        L1Ele = L1Eles[0]
        L1Jet1Index, L1Jet2Index, L1Mjj = highestMjjPair(L1Jets)
        L1Jet1 = L1Jets[L1Jet1Index]
        L1Jet2 = L1Jets[L1Jet2Index]
        matchL1Off, L1Indices = match_Offline_to_L1(L1Eles, L1Jets, OffEle, OffJet1, OffJet2)
        #matchL1Off = match_L1_to_Offline(L1Ele, L1Jet1, L1Jet2, OffEle, OffJet1, OffJet2)

      reassignL1 = True
      if (matchL1Off and reassignL1):
        L1Ele  = L1Eles[L1Indices[0]]
        L1Jet1 = L1Jets[L1Indices[1]]
        L1Jet2 = L1Jets[L1Indices[2]]
        L1Mjj  = (L1Jet1 + L1Jet2).M()
        # fill here
        outL1ElePt[0] = L1Ele.Pt()
        outL1EleEta[0] = L1Ele.Eta()
        outL1ElePhi[0] = L1Ele.Phi()
      else:
        outL1ElePt[0] = -999
        outL1EleEta[0] = -999
        outL1ElePhi[0] = -999

      outL1OffEleMatch[0] = matchL1Off
      outPassL1[0] = PassVBFIsoEGL1[0]

      # Matching
      # SingleEle HLT Matching
      SingleEleHLTEles = fillWithTVecs(SingleEleFinalFilter_pt, SingleEleFinalFilter_eta, 
                                   SingleEleFinalFilter_phi, SingleEleFinalFilter_energy)
      passSingleEleHLTOffMatching = matchHLTOff(SingleEleHLTEles, OffEle)

      # VBF Ele HLT Matching 
      VBFEleHLTEles = fillWithTVecs(VBFEleFinalEleFilter_pt, VBFEleFinalEleFilter_eta,
                                    VBFEleFinalEleFilter_phi, VBFEleFinalEleFilter_energy)
      matchVBFEleHLTEle = matchHLTOff(VBFEleHLTEles, OffEle)

      VBFEleHLTJets = fillWithTVecs(VBFEleFinalJetFilter_pt, VBFEleFinalJetFilter_eta,
                                    VBFEleFinalJetFilter_phi, VBFEleFinalJetFilter_energy)
      matchVBFEleHLTJet1 = matchHLTOff(VBFEleHLTJets, OffJet1)
      matchVBFEleHLTJet2 = matchHLTOff(VBFEleHLTJets, OffJet2)

      passVBFEleHLTOffMatching = matchVBFEleHLTEle and matchVBFEleHLTJet1 and matchVBFEleHLTJet2

      # end matching

      passEleTauOffCuts = False
      if (OffJet1.Pt() >= 50#30
       and OffJet2.Pt() >= 50#30
       and OffMjj >= 600#300
       and OffTau.Pt() >= 30
       and OffEle.Pt() >= 25): passEleTauOffCuts = True

      # require a high pt iso ele to emulate the lowest L1 with PS != 0 for this HLT path
      passL1IsoElePresent = True
      #if (PassVBFIsoEGL1[0]):
      #  passL1IsoElePresent = L1Ele.Pt() >= 30
      passSingleEleOffCuts = (passL1IsoElePresent and passEleTauOffCuts and OffEle.Pt() >= 33)

      passVBFEleL1Restrictions = False
      if (PassVBFIsoEGL1[0]):
        if (L1Jet1.Pt()  >= 40
          and L1Jet2.Pt() >= 40
          and L1Mjj       >= 450):
          #and L1Ele.Pt()  >= 10):
          passVBFEleL1Restrictions = True

      passVBFEleOffCuts = False
      if (OffJet1.Pt()  >= 50
       and OffJet2.Pt() >= 50
       and OffMjj       >= 600
       and OffTau.Pt()  >= 25
       and OffEle.Pt()  >= 13): passVBFEleOffCuts = True

     
      #BoolPassSingleEleL1 = passSingleEleL1[0] 
      BoolPassVBFEleL1    = PassVBFIsoEGL1[0] and passVBFEleL1Restrictions

      #if (BoolPassSingleEleL1): TallySingleEleL1 += 1
      if (BoolPassVBFEleL1): TallyVBFEleL1 += 1
      #if (BoolPassVBFEleL1 or BoolPassSingleEleL1): TallyVBFEleORSingleEleL1 += 1

      BoolPassSingleEleHLT = passSingleEleHLT[0]
      BoolPassVBFEleHLT = passVBFEleHLT[0]

      if (BoolPassSingleEleHLT): TallySingleEleHLT += 1
      if (BoolPassVBFEleHLT): TallyVBFEleHLT += 1
      if (BoolPassVBFEleHLT or BoolPassSingleEleHLT): TallyVBFEleORSingleEleHLT += 1


      GoodSingleEle = passSingleEleHLTOffMatching and passSingleEleOffCuts and passSingleEleHLT[0]
      GoodVBFEle = passVBFEleL1Restrictions and passVBFEleHLTOffMatching and passVBFEleOffCuts and passVBFEleHLT[0] # HLT instead of L1

      if (GoodVBFEle): TallyVBFEleOff += 1
      if (GoodSingleEle): TallySingleEleOff += 1
      if (GoodVBFEle or GoodSingleEle): TallyVBFEleORSingleEleOff += 1

      # fill branches
      outPassOff = passVBFEleOffCuts
      outtree.Fill()


  L1_Tallies  = [TallyVBFEleL1, 0, 0]
  HLT_Tallies = [TallyVBFEleHLT, TallySingleEleHLT, TallyVBFEleORSingleEleHLT]
  Off_Tallies = [TallyVBFEleOff, TallySingleEleOff, TallyVBFEleORSingleEleOff]

  # print output
  print("-"*40)
  print(f"nViableEvents: {viableEventCounter}")
  print(f"nEvents with ViableOfflineObjects: {offlineObjectsViableCounter}")

  outtree.Write()
  outFile.Close()

  if (notRateStudy):
    labels = ["VBF+Ele (1)", "SingleEle (2)", "OR"]
    header = ["Label", "L1", "HLT", "Offline"]
    print(f"{header[0]:17}, {header[1]:7}, {header[2]:7}, {header[3]:7}")
    for index, label in enumerate(labels):
      print(f"{label:17}, {L1_Tallies[index]:7}, {HLT_Tallies[index]:7}, {Off_Tallies[index]:7}")


