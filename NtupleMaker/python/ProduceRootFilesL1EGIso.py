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

  passEGL1 = array('i', [0])
  L1ElePt = ROOT.std.vector('float')()
  L1EleEta = ROOT.std.vector('float')()
  L1ElePhi = ROOT.std.vector('float')()
  L1EleEnergy = ROOT.std.vector('float')()
 
  L1JetPt = ROOT.std.vector('float')()
  L1JetEta = ROOT.std.vector('float')()
  L1JetPhi = ROOT.std.vector('float')()
  L1JetEnergy = ROOT.std.vector('float')()

  EGL1Source = args.VBFEGL1Source
  if (EGL1Source == "TightDummy"):

    tree.SetBranchAddress("passhltPassthroughL1EGTightIso", passEGL1)

    tree.SetBranchAddress("hltPassthroughL1EGTightIso_pt", L1ElePt)
    tree.SetBranchAddress("hltPassthroughL1EGTightIso_eta", L1EleEta)
    tree.SetBranchAddress("hltPassthroughL1EGTightIso_phi", L1ElePhi)
    tree.SetBranchAddress("hltPassthroughL1EGTightIso_energy", L1EleEnergy)

  elif (EGL1Source == "LooseDummy"):

    tree.SetBranchAddress("passhltPassthroughL1EGLooseIso", passEGL1)

    tree.SetBranchAddress("hltPassthroughL1EGLooseIso_pt", L1ElePt)
    tree.SetBranchAddress("hltPassthroughL1EGLooseIso_eta", L1EleEta)
    tree.SetBranchAddress("hltPassthroughL1EGLooseIso_phi", L1ElePhi)
    tree.SetBranchAddress("hltPassthroughL1EGLooseIso_energy", L1EleEnergy)

  elif (EGL1Source == "NoDummy"):

    tree.SetBranchAddress("passhltPassthroughL1EGNoIso", passEGL1)

    tree.SetBranchAddress("hltPassthroughL1EGNoIso_pt", L1ElePt)
    tree.SetBranchAddress("hltPassthroughL1EGNoIso_eta", L1EleEta)
    tree.SetBranchAddress("hltPassthroughL1EGNoIso_phi", L1ElePhi)
    tree.SetBranchAddress("hltPassthroughL1EGNoIso_energy", L1EleEnergy)

  else:
    print(f"EGL1Source not set, exiting...")
    sys.exit()


  passSingleEleHLT = array('i', [0])
  tree.SetBranchAddress("passSingleEleHLT", passSingleEleHLT)

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

  TotalEntries = tree.GetEntries()
  for entry in range(TotalEntries):
    tree.GetEntry(entry)
  
    basicReqs = ( notRateStudy and (OffnEles[0] >= 1) )

    if basicReqs:
      viableEventCounter += 1

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

      OffEle = OffEles[0]

      outOffElePt[0] = OffEle.Pt()
      outOffEleEta[0] = OffEle.Eta()
      outOffElePhi[0] = OffEle.Phi()

      offlineObjectsViableCounter += 1
      #if (offlineObjectsViableCounter >= 8718): break

      # get L1 objects 
      L1Eles = fillWithTVecs(L1ElePt, L1EleEta, L1ElePhi, L1EleEnergy)
      sizeL1Eles = len(L1Eles)

      matchL1Off = False
      if (sizeL1Eles >= 1 and passEGL1[0]):
        L1Ele = L1Eles[0]
        outL1ElePt[0] = L1Ele.Pt()
        outL1EleEta[0] = L1Ele.Eta()
        outL1ElePhi[0] = L1Ele.Phi()
        matchL1Off = ROOT.TLorentzVector.DeltaR(OffEle, L1Ele) < 0.5
      else:
        outL1ElePt[0] = -999
        outL1EleEta[0] = -999
        outL1ElePhi[0] = -999
      outL1OffEleMatch[0] = matchL1Off
      outPassL1[0] = passEGL1[0]

      # Matching
      # SingleEle HLT Matching
      SingleEleHLTEles = fillWithTVecs(SingleEleFinalFilter_pt, SingleEleFinalFilter_eta, 
                                   SingleEleFinalFilter_phi, SingleEleFinalFilter_energy)
      passSingleEleHLTOffMatching = matchHLTOff(SingleEleHLTEles, OffEle)

      #passEleTauOffCuts = False
      #if (OffJet1.Pt() >= 50#30
      # and OffJet2.Pt() >= 50#30
      # and OffMjj >= 600#300
      # and OffTau.Pt() >= 30
      # and OffEle.Pt() >= 25): passEleTauOffCuts = True

      #outPassOff = passVBFEleOffCuts
      outtree.Fill()


  # print output
  #print("-"*40)
  #print(f"nViableEvents: {viableEventCounter}")
  #print(f"nEvents with ViableOfflineObjects: {offlineObjectsViableCounter}")

  outtree.Write()
  outFile.Close()

