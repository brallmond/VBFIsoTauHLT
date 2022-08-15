# Braden Allmond, August 10th 2022, KSU

from array import array
import ROOT
#from ROOT import Math, TLorentzVector
#import sys
import argparse
import numpy as np
import matplotlib.pyplot as plt

ROOT.gROOT.SetBatch(True) # sets visual display off (i.e. no graphs/TCanvas)


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
  leadingJetIndex = -1
  subleadingJetIndex = -1

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
  Returns an array of TLorentzVector objects filled with the kinematic info

    Parameters:
      branchPt -
      branchEta -
      branchPhi -
      branchEnergy -

    Return:
      outputTVecs - 
  '''
  if arrayIDs is None:
    arrayIDs = range(len(branchPt))

  outputTVecs = []
  #for i in range(branchPt.size()):
  for i in arrayIDs:
    tempVec = ROOT.TLorentzVector(branchPt[i], branchEta[i], branchPhi[i], branchEnergy[i])
    outputTVecs.append(tempVec)
  return outputTVecs


if __name__ == "__main__":

  parser = argparse.ArgumentParser(description='Open a .root file')
  parser.add_argument('-i', '--inputRootFile', dest='inFilename', action='store',
                    help='the input .root file\'s name')
  args = parser.parse_args()

  inFile = ROOT.TFile.Open(args.inFilename,"READ")
  tree = inFile.Get("demo/vbf")

  # hell to read but
  # defining a variable/object handle 
  #   objName = type('typename')(initialization*) *initialization changes by type
  # and then linking that object handle to an available branch in the event tree
  #   tree.SetBranchAddress("branchOfObjInTree", objHandle)

  # L1
  # try with primitives at some point to compare...
  #eleL1PrimitivesPt
  #eleL1PrimitivesEta
  #eleL1PrimitivesPhi
  #eleL1PrimitivesEnergy
  #etc
  passL1 = array('i', [0])
  tree.SetBranchAddress("passhltL1VBFElectronLoose", passL1)
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
  
  # HLT

  # Offline kinems
  ##Taus
  OffnTaus = array('i', [0])
  tree.SetBranchAddress("nTau", OffnTaus)
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
  tree.SetBranchAddress("jetEn", OffJetEnergy)
  ##Electrons
  OffnEles = array('i', [0])
  tree.SetBranchAddress("nEle", OffnEles)
  OffElePt = ROOT.std.vector('float')()
  tree.SetBranchAddress("elePt", OffElePt)
  OffEleEta = ROOT.std.vector('float')()
  tree.SetBranchAddress("eleEta", OffEleEta)
  OffElePhi = ROOT.std.vector('float')()
  tree.SetBranchAddress("elePhi", OffElePhi)
  OffEleEnergy = ROOT.std.vector('float')()
  tree.SetBranchAddress("eleEn", OffEleEnergy)

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

  CountViable = 0
  for entry in range(5000):
    #print(entry)
    tree.GetEntry(entry)

    # check if event passes L1 and HLT and basic offline object count requirements
    basicReqs = passL1[0] and (OffnJets[0] >= 2) and (OffnEles[0] >= 1) and (OffnTaus[0] >= 1)
    if basicReqs:
      CountViable += 1

      # make and fill containers with TLorentzVectors
      # we will match the offline to the L1s, so it is redudant to cut on both
      # subsequently, we make cuts on the tighter (offline) set to begin with

      L1Jets = fillWithTVecs(L1JetPt, L1JetEta, L1JetPhi, L1JetEnergy)
      sizeL1Jets = len(L1Jets)
      L1Eles = fillWithTVecs(L1ElePt, L1EleEta, L1ElePhi, L1EleEnergy)
      sizeL1Eles = len(L1Eles)

      JetPtToPass = 45
      PassJetPt =  [i for i in range(len(OffJetPt)) if OffJetPt[i] >= JetPtToPass]
      PassJetID =  [i for i in range(len(OffJetID)) if OffJetID[i] >= 2]
      PassJetEta = [i for i in range(len(OffJetEta)) if OffJetEta[i] <= 4.7]
      # python list intersection https://stackoverflow.com/questions/3697432/how-to-find-list-intersection
      # listed in the order which removes the most members first (assuming & short-circuits)
      OffJetsPassFilter = list(set(PassJetPt) & set(PassJetID) & set(PassJetEta))
      OffJets = fillWithTVecs(OffJetPt, OffJetEta, OffJetPhi, OffJetEnergy, OffJetsPassFilter)
      sizeOffJets = len(OffJets)

      TauPtToPass = 25
      # Tau ID for Ele-Tau using 2017 DeepTau version 2p1, Med vs Jet, Tight vs Ele, VLoose vs Muon
      TauEtaToPass = 2.3
      PassTauPt = [i for i in range(len(OffTauPt)) if OffTauPt[i] >= TauPtToPass]
      PassTauID = [i for i in range(len(OffTauIDvsJet)) \
                    if (OffTauIDvsJet[i] == True and OffTauIDvsEle[i] == True and OffTauIDvsMuon[i] == True) ]  
      PassTauEta = [i for i in range(len(OffTauEta)) if OffTauEta[i] <= TauEtaToPass]
      OffTauPassFilter = list(set(PassTauPt) & set(PassTauID) & set(PassTauEta))
      OffTaus = fillWithTVecs(OffTauPt, OffTauEta, OffTauPhi, OffTauEnergy, OffTauPassFilter)
      sizeOffTaus = len(OffTaus)

      ElePtToPass = 12
      # Ele ID is eleIDMVANoIsowp90
      EleEtaToPass = 2.1
      PassElePt =  [i for i in range(len(OffElePt)) if OffElePt[i] >= ElePtToPass]
      PassEleID =  [i for i in range(len(OffEleID)) if OffEleID[i] >= 1]      
      PassEleEta = [i for i in range(len(OffEleEta)) if OffEleEta[i] <= EleEtaToPass]
      OffElesPassFilter = list(set(PassEleID) & set(PassElePt) & set(PassEleEta))
      OffEles = fillWithTVecs(OffElePt, OffEleEta, OffElePhi, OffEleEnergy, OffElesPassFilter)
      sizeOffEles = len(OffEles)

      # as written, it would just make more sense to assign things all at once, instead of before and then skimming

      if (sizeL1Jets > 1): #only call function if more than 2 objects
        L1LeadingJetIndex, L1SubleadingJetIndex, L1mjj = highestMjjPair(L1Jets)

      allGood = False
      if (allGood):
        L1LeadingJetPt = L1Jets[leadingJetIndex].Pt()
        L1SubleadingJetPt = L1Jets[subleadingJetIndex].Pt()

        electronPt = L1ElePt[0]

  print(CountViable)
  

