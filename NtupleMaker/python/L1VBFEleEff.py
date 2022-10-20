# Braden Allmond, August 10th 2022, KSU

from array import array
import ROOT
import argparse
import sys
import numpy as np
import matplotlib.pyplot as plt

ROOT.gROOT.SetBatch(True) # sets visual display off (i.e. no graphs/TCanvas)

# usage: python3 L1VBFEleEff.py -i ../../../samples/VBFE_CorrectEleIsoAndNewFilter.root -L 6 -o Tight_30_320_10_corrected.root 

def match_L1_to_Offline(L1Ele, L1Jet1, L1Jet2, OffEle, OffJet1, OffJet2):
  """ Use dR cone to match preselected L1 objects to preselected Offline objects and return True.
      Return false if not all L1 objects can be matched."""
  match = False

  matchL1OffJetsNormal = (ROOT.TLorentzVector.DeltaR(OffJet1, L1Jet1) < 0.5 and ROOT.TLorentzVector.DeltaR(OffJet2, L1Jet2) < 0.5)
  matchL1OffJetsSwapped = (ROOT.TLorentzVector.DeltaR(OffJet1, L1Jet2) < 0.5 and ROOT.TLorentzVector.DeltaR(OffJet2, L1Jet1) < 0.5)
  matchL1OffJets = matchL1OffJetsNormal or matchL1OffJetsSwapped
  matchL1OffEle = (ROOT.TLorentzVector.DeltaR(OffEle, L1Ele) < 0.5)

  match = matchL1OffJets and matchL1OffEle

  return match


def match_Offline_to_L1(L1Eles, L1Jets, OffEle, OffJet1, OffJet2):
  """ Use dR cone to match preselected Offline objects to any available L1 object and return True.
      Return False if not all L1 objects can be matched.
      Also returns two lists of matched objects
  """
  match = False

  L1Jet1Index, L1Jet2Index, dummyL1Mjj = highestMjjPair(L1Jets)

  matchJet = [i for i in range(len(L1Jets))
           if (ROOT.TLorentzVector.DeltaR(OffJet1, L1Jets[i]) < 0.5 or
               ROOT.TLorentzVector.DeltaR(OffJet2, L1Jets[i]) < 0.5) ]

  matchJet1 = [ROOT.TLorentzVector.DeltaR(OffJet1, L1Jets[i]) for i in range(len(L1Jets))]
  print(matchJet1)

  #lengthMatchJet = len(matchJet)
  #if (lengthMatchJet == 2):
  #  L1Jet1Index

  if (len(matchJet) >= 2):
    print("*"*10)
    print(f"matchJet: {matchJet}")
    print(f"jet idxs: {L1Jet1Index, L1Jet2Index}")

  matchEle = [i for i in range(len(L1Eles))
           if ROOT.TLorentzVector.DeltaR(OffEle, L1Eles[i]) < 0.5 ]

  if (L1Jet1Index in matchJet and L1Jet2Index in matchJet and len(matchEle) >= 1): match = True

  return match
 

def highestMjjPair(inObjs):
  '''
  Takes in an array of TLorentzVector objects
  Returns the array indices of the highest mjj pair of objects and the mjj
    
    Parameters:
      inObjs - an array of TLorentzVectors

    Returns:
      leadingJetIndex - the array index of the higher pt jet in the mjj pair
      subleadingJetIndex - the array index of the lower pt jet in the mjj pair
      mjj - the dijet mass of the highest mjj pair of the inObjs
  '''
  nObjs = len(inObjs) 

  mjj = 0 
  mjjTemp = 0
  leadingJetIndex = 999#-1
  subleadingJetIndex = 999#-1

  for j in range(nObjs):
    for k in range(nObjs):
      if (k > j):
        tempJet1 = inObjs[j]
        tempJet2 = inObjs[k]
        mjjTemp = (tempJet1 + tempJet2).M()
        if (mjjTemp > mjj):
          mjj = mjjTemp
          leadingJetIndex = j
          subleadingJetIndex = k

  return leadingJetIndex, subleadingJetIndex, mjj

def fillWithTVecs(branchPt, branchEta, branchPhi, branchEnergy, arrayIDs=None):
  '''
  Takes in four kinematic branch names
  Returns an array of TLorentzVector objects filled with the kinematic info.
  Optionally skips members of the input branches if present in 'arrayIDs'.
  '''
  if arrayIDs is None:
    arrayIDs = range(len(branchPt))

  outputTVecs = []
  for i in arrayIDs:
    tempVec = ROOT.TLorentzVector()
    tempVec.SetPtEtaPhiE(branchPt[i], branchEta[i], branchPhi[i], branchEnergy[i])
    #print(branchPt[i], branchEta[i], branchPhi[i], branchEnergy[i])
    outputTVecs.append(tempVec)
  return outputTVecs


if __name__ == "__main__":

  parser = argparse.ArgumentParser(description='Open a .root file')
  parser.add_argument('-i', '--inputRootFile', dest='inFilename', action='store',
                    help='the input .root file\'s name')
  parser.add_argument('-L', '--L1IndexToTest', dest='L1IndexToTest', action='store',
                    help='the L1 being tested')
  parser.add_argument('-o', '--output_name', dest='output_name', action='store',
                    help='name of your output file')
  args = parser.parse_args()

  inFile = ROOT.TFile.Open(args.inFilename,"READ")
  tree = inFile.Get("demo/vbf")

  print(f"Output file name: {args.output_name}")
  ROOT.TH1.SetDefaultSumw2()

  outFile = ROOT.TFile.Open(args.output_name, "RECREATE")
  outtree = ROOT.TTree("outtree", "skimmed event data")

  outL1ElePt = array('f', [0.])
  outL1Jet1Pt = array('f', [0.])
  outL1Jet2Pt = array('f', [0.])
  outL1Mjj = array('f', [0.])
  outtree.Branch("L1ElePt", outL1ElePt, 'pt/F')
  outtree.Branch("L1Jet1Pt", outL1Jet1Pt, 'pt/F')
  outtree.Branch("L1Jet2Pt", outL1Jet2Pt, 'pt/F')
  outtree.Branch("L1Mjj", outL1Mjj, 'mjj/F')

  outOffElePt = array('f', [0.])
  outOffTauPt = array('f', [0.])
  outOffJet1Pt = array('f', [0.])
  outOffJet2Pt = array('f', [0.])
  outOffMjj = array('f', [0.])
  outtree.Branch("OffElePt", outOffElePt, 'pt/F')
  outtree.Branch("OffTauPt", outOffTauPt, 'pt/F')
  outtree.Branch("OffJet1Pt", outOffJet1Pt, 'pt/F')
  outtree.Branch("OffJet2Pt", outOffJet2Pt, 'pt/F')
  outtree.Branch("OffMjj", outOffMjj, 'mjj/F')

  outMatchL1Off = array('i', [0])
  outtree.Branch("MatchL1Off", outMatchL1Off, 'matched/I')

  L1IndexToTest = int(args.L1IndexToTest)
  if ((not (0 <= L1IndexToTest <= 7)) or not isinstance(L1IndexToTest, int)):
    print("need an int from 0 to 6")
    sys.exit()

  # hell to read but
  # defining a variable/object handle 
  #   objName = type('typename')(initialization*) *initialization changes by type
  # and then linking that object handle to an available branch in the event tree
  #   tree.SetBranchAddress("branchOfObjInTree", objHandle)

  # L1

  if (L1IndexToTest == 6):
    passL1 = array('i', [0])
    tree.SetBranchAddress("passhltL1VBFElectron", passL1)
    L1JetPt = ROOT.std.vector('float')()
    tree.SetBranchAddress("hltL1VBFElectron_jPt", L1JetPt)
    L1JetEta = ROOT.std.vector('float')()
    tree.SetBranchAddress("hltL1VBFElectron_jEta", L1JetEta)
    L1JetPhi = ROOT.std.vector('float')()
    tree.SetBranchAddress("hltL1VBFElectron_jPhi", L1JetPhi)
    L1JetEnergy = ROOT.std.vector('float')()
    tree.SetBranchAddress("hltL1VBFElectron_jEnergy", L1JetEnergy)
    L1ElePt = ROOT.std.vector('float')()
    tree.SetBranchAddress("hltL1VBFElectron_ePt", L1ElePt)
    L1EleEta = ROOT.std.vector('float')()
    tree.SetBranchAddress("hltL1VBFElectron_eEta", L1EleEta)
    L1ElePhi = ROOT.std.vector('float')()
    tree.SetBranchAddress("hltL1VBFElectron_ePhi", L1ElePhi)
    L1EleEnergy = ROOT.std.vector('float')()
    tree.SetBranchAddress("hltL1VBFElectron_eEnergy", L1EleEnergy)
 
  else:
    passL1 = array('i', [0])
    tree.SetBranchAddress("passhltL1VBFElectronLoose", passL1)
    L1JetPt = ROOT.std.vector('float')()
    tree.SetBranchAddress("hltL1VBFElectronLoose_jPt", L1JetPt)
    L1JetEta = ROOT.std.vector('float')()
    tree.SetBranchAddress("hltL1VBFElectronLoose_jEta", L1JetEta)
    L1JetPhi = ROOT.std.vector('float')()
    tree.SetBranchAddress("hltL1VBFElectronLoose_jPhi", L1JetPhi)
    L1JetEnergy = ROOT.std.vector('float')()
    tree.SetBranchAddress("hltL1VBFElectronLoose_jEnergy", L1JetEnergy)
    L1ElePt = ROOT.std.vector('float')()
    tree.SetBranchAddress("hltL1VBFElectronLoose_ePt", L1ElePt)
    L1EleEta = ROOT.std.vector('float')()
    tree.SetBranchAddress("hltL1VBFElectronLoose_eEta", L1EleEta)
    L1ElePhi = ROOT.std.vector('float')()
    tree.SetBranchAddress("hltL1VBFElectronLoose_ePhi", L1ElePhi)
    L1EleEnergy = ROOT.std.vector('float')()
    tree.SetBranchAddress("hltL1VBFElectronLoose_eEnergy", L1EleEnergy)
   
  # HLT Filter Matching
  # EleTau
  PassEleTauFinalFilterTau = array('i', [0])
  tree.SetBranchAddress("passEleTauFinalFilterTau", PassEleTauFinalFilterTau)
  EleTauFinalFilterTau_pt = ROOT.std.vector('float')()
  tree.SetBranchAddress("EleTauFinalFilterTau_pt", EleTauFinalFilterTau_pt)
  EleTauFinalFilterTau_eta = ROOT.std.vector('float')()
  tree.SetBranchAddress("EleTauFinalFilterTau_eta", EleTauFinalFilterTau_eta)
  EleTauFinalFilterTau_phi = ROOT.std.vector('float')()
  tree.SetBranchAddress("EleTauFinalFilterTau_phi", EleTauFinalFilterTau_phi)
  EleTauFinalFilterTau_energy = ROOT.std.vector('float')()
  tree.SetBranchAddress("EleTauFinalFilterTau_energy", EleTauFinalFilterTau_energy)
  PassEleTauFinalFilterEle = array('i', [0])
  tree.SetBranchAddress("passEleTauFinalFilterEle", PassEleTauFinalFilterEle)
  EleTauFinalFilterEle_pt = ROOT.std.vector('float')()
  tree.SetBranchAddress("EleTauFinalFilterEle_pt", EleTauFinalFilterEle_pt)
  EleTauFinalFilterEle_eta = ROOT.std.vector('float')()
  tree.SetBranchAddress("EleTauFinalFilterEle_eta", EleTauFinalFilterEle_eta)
  EleTauFinalFilterEle_phi = ROOT.std.vector('float')()
  tree.SetBranchAddress("EleTauFinalFilterEle_phi", EleTauFinalFilterEle_phi)
  EleTauFinalFilterEle_energy = ROOT.std.vector('float')()
  tree.SetBranchAddress("EleTauFinalFilterEle_energy", EleTauFinalFilterEle_energy)

  # SingleTau
  PassSingleEleFinalFilter = array('i', [0])
  tree.SetBranchAddress("passSingleEleFinalFilter", PassSingleEleFinalFilter)
  SingleEleFinalFilter_pt = ROOT.std.vector('float')()
  tree.SetBranchAddress("SingleEleFinalFilter_pt", SingleEleFinalFilter_pt)
  SingleEleFinalFilter_eta = ROOT.std.vector('float')()
  tree.SetBranchAddress("SingleEleFinalFilter_eta", SingleEleFinalFilter_eta)
  SingleEleFinalFilter_phi = ROOT.std.vector('float')()
  tree.SetBranchAddress("SingleEleFinalFilter_phi", SingleEleFinalFilter_phi)
  SingleEleFinalFilter_energy = ROOT.std.vector('float')()
  tree.SetBranchAddress("SingleEleFinalFilter_energy", SingleEleFinalFilter_energy)
  

  # HLT Final Decisions
  passEleTauHLT = array('i', [0])
  tree.SetBranchAddress("passEleTauHLT", passEleTauHLT)
  passSingleEleHLT = array('i', [0])
  tree.SetBranchAddress("passSingleEleHLT", passSingleEleHLT)

  # Offline kinems
  ##Taus
  OffnTaus = array('i', [0])
  tree.SetBranchAddress("nTau", OffnTaus)
  OffTauCh = ROOT.std.vector('float')()
  tree.SetBranchAddress("tauCharge", OffTauCh)
  OffTauPt = ROOT.std.vector('float')()
  tree.SetBranchAddress("tauPt", OffTauPt)
  OffTauEta = ROOT.std.vector('float')()
  tree.SetBranchAddress("tauEta", OffTauEta)
  OffTauPhi = ROOT.std.vector('float')()
  tree.SetBranchAddress("tauPhi", OffTauPhi)
  OffTauEnergy = ROOT.std.vector('float')()
  tree.SetBranchAddress("tauEnergy", OffTauEnergy)
  ##Jets
  OffnJets = array('i', [0])
  tree.SetBranchAddress("nJet", OffnJets)
  OffJetPt = ROOT.std.vector('float')()
  tree.SetBranchAddress("jetPt", OffJetPt)
  OffJetEta = ROOT.std.vector('float')()
  tree.SetBranchAddress("jetEta", OffJetEta)
  OffJetPhi = ROOT.std.vector('float')()
  tree.SetBranchAddress("jetPhi", OffJetPhi)
  OffJetEnergy = ROOT.std.vector('float')()
  tree.SetBranchAddress("jetEnergy", OffJetEnergy)
  ##Electrons
  OffnEles = array('i', [0])
  tree.SetBranchAddress("nEle", OffnEles)
  OffEleCh = ROOT.std.vector('float')()
  tree.SetBranchAddress("eleCharge", OffEleCh)
  OffElePt = ROOT.std.vector('float')()
  tree.SetBranchAddress("elePt", OffElePt)
  OffEleEta = ROOT.std.vector('float')()
  tree.SetBranchAddress("eleEta", OffEleEta)
  OffElePhi = ROOT.std.vector('float')()
  tree.SetBranchAddress("elePhi", OffElePhi)
  OffEleEnergy = ROOT.std.vector('float')()
  tree.SetBranchAddress("eleEnergy", OffEleEnergy)

  OffElePFChIso = ROOT.std.vector('float')()
  tree.SetBranchAddress("elePFChIso", OffElePFChIso)
  OffElePFPUIso = ROOT.std.vector('float')()
  tree.SetBranchAddress("elePFPUIso", OffElePFPUIso)
  OffElePFNeuIso = ROOT.std.vector('float')()
  tree.SetBranchAddress("elePFNeuIso", OffElePFNeuIso)
  OffElePFPhoIso = ROOT.std.vector('float')()
  tree.SetBranchAddress("elePFPhoIso", OffElePFPhoIso)

  # Offline Ids
  OffTauIDvsJet = ROOT.std.vector('bool')()
  tree.SetBranchAddress("tauByMediumDeepTau2017v2p1VSjet", OffTauIDvsJet)
  OffTauIDvsEle = ROOT.std.vector('bool')()
  tree.SetBranchAddress("tauByTightDeepTau2017v2p1VSe", OffTauIDvsEle)
  OffTauIDvsMuon = ROOT.std.vector('bool')()
  tree.SetBranchAddress("tauByVLooseDeepTau2017v2p1VSmu", OffTauIDvsMuon)

  OffJetPFLooseID = ROOT.std.vector('bool')()
  tree.SetBranchAddress("jetPFLooseId", OffJetPFLooseID)
  OffJetID = ROOT.std.vector('int')()
  tree.SetBranchAddress("jetID", OffJetID)
  OffJetPUID = ROOT.std.vector('float')()
  tree.SetBranchAddress("jetPUID", OffJetPUID)
  OffJetPUFullID = ROOT.std.vector('int')()
  tree.SetBranchAddress("jetPUFullID", OffJetPUFullID)

  OffEleID = ROOT.std.vector('int')()
  tree.SetBranchAddress("eleIDMVANoIsowp90", OffEleID)

  # L1 and Offline cuts are just integers so we define them outside the event loop
              # pt  mjj  ele pt    
  L1sToTest = [[38, 460, 12],
               [40, 460, 12],
               [42, 460, 12],
               [32, 440, 14],
               [34, 440, 14],
               [36, 440, 14],
               # Iso
               [30, 320, 10],
               # Loose Iso
               [30, 320, 10]]

  L1Cuts = L1sToTest[L1IndexToTest] #defined by argparse
  # Jet
  L1JetPtToPass = L1Cuts[0]
  L1JetMjjToPass = L1Cuts[1]
  # Ele
  L1ElePtToPass = L1Cuts[2]
  # the offline cuts are applied to the offline objects
  # they are a flat increase of L1 kinem cuts
  # Jet
  OffJetPtToPass = L1JetPtToPass + 10
  OffJetMjjToPass = L1JetMjjToPass + 50
  # Tau
  OffTauPtToPass = 30
  # Ele
  OffElePtToPass = L1ElePtToPass + 2

  if (L1IndexToTest == 6): 
    print("\nL1_VBF_DoubleJets{0}_Mass_Min{1}_IsoEG{2}".format(L1JetPtToPass, L1JetMjjToPass, L1ElePtToPass))
  else:
    print("\nL1_VBF_DoubleJets{0}_Mass_Min{1}_LooseIsoEG{2}".format(L1JetPtToPass, L1JetMjjToPass, L1ElePtToPass))

  TotalEntries = tree.GetEntries()
  for entry in range(TotalEntries):
    tree.GetEntry(entry)

    # requiring events to pass your L1 biases your selection, fine for gain study, not fine for eff study
    #basicReqs = ((passL1[0]) and (OffnJets[0] >= 2) and (OffnEles[0] >= 1) and (OffnTaus[0] >= 1))
    basicReqs = ((OffnJets[0] >= 2) and (OffnEles[0] >= 1) and (OffnTaus[0] >= 1))

    if basicReqs:
      # make and fill containers with TLorentzVectors
      # we will match the offline to the L1s, so it is redudant to cut on both
      # subsequently, we make cuts on the tighter (offline) set to begin with
      # we wait until after objects are matched to cut on pt/mjj

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
      if (ROOT.TLorentzVector.DeltaR(OffEles[0], OffTaus[0]) < 0.5): 
        continue

      # skip the event if the tau and electron have the same charge
      if (OffEleCh[OffElesPassFilter[0]] == OffTauCh[OffTausPassFilter[0]]):
        continue

      # assign Offline objects
      OffTau = OffTaus[0] # consider selecting tau based on isolation, not pt
      OffEle = OffEles[0]
      OffJet1Index, OffJet2Index, OffMjj = highestMjjPair(OffJets)
      OffJet1 = OffJets[OffJet1Index]
      OffJet2 = OffJets[OffJet2Index]
      if (ROOT.TLorentzVector.DeltaR(OffJet1, OffJet2) < 0.5): continue
 
      # fill L1 objects and get the highestMjjPair of jets
      # the L1 trigger will always pick the highestMjjPair
      # so we pick that as well and hope it matches the offline objects
      L1Jets = fillWithTVecs(L1JetPt, L1JetEta, L1JetPhi, L1JetEnergy)
      sizeL1Jets = len(L1Jets)
      L1Eles = fillWithTVecs(L1ElePt, L1EleEta, L1ElePhi, L1EleEnergy)
      sizeL1Eles = len(L1Eles)
      # fill L1 branches regardless of cuts or matching (applied later)

      # effectively requires L1 objects as was done at start of loop, set a flag not to match instead
      # check object sizes before matching

      matchL1Off = False
      tryToMatch = False
      if (sizeL1Jets >= 2 and sizeL1Eles >= 1): tryToMatch = True 

      if (tryToMatch == True):
        L1Jet1Index, L1Jet2Index, L1Mjj = highestMjjPair(L1Jets)
        L1Jet1 = L1Jets[L1Jet1Index]
        L1Jet2 = L1Jets[L1Jet2Index]
        L1Ele = L1Eles[0]

      #matchL1Off = match_L1_to_Offline(L1Ele, L1Jet1, L1Jet2, OffEle, OffJet1, OffJet2)

      matchL1Off = match_Offline_to_L1(L1Eles, L1Jets, OffEle, OffJet1, OffJet2)

      #if (matchL1Off):
      #  L1Jet1 = L1Jets[matchL1OffJet[0]]
      #  L1Jet2 = L1Jets[matchL1OffJet[1]]
      #  L1Ele = L1Eles[matchL1OffEle[0]]

      # writing branch info

      outMatchL1Off[0] = matchL1Off

      outL1ElePt[0] = L1Ele.Pt()
      outL1Jet1Pt[0] = L1Jet1.Pt()
      outL1Jet2Pt[0] = L1Jet2.Pt()
      outL1Mjj[0] = L1Mjj

      outOffElePt[0] = OffEle.Pt()
      outOffTauPt[0] = OffTau.Pt()
      outOffJet1Pt[0] = OffJet1.Pt()
      outOffJet2Pt[0] = OffJet2.Pt()
      outOffMjj[0] = OffMjj

      outtree.Fill()

  outtree.Write()
  outFile.Close()

