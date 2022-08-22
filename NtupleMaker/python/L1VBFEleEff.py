# Braden Allmond, August 10th 2022, KSU

from array import array
import ROOT
import argparse
import sys
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
  args = parser.parse_args()

  inFile = ROOT.TFile.Open(args.inFilename,"READ")
  tree = inFile.Get("demo/vbf")

  L1IndexToTest = int(args.L1IndexToTest)
  if ((not (0 <= L1IndexToTest <= 6)) or not isinstance(L1IndexToTest, int)):
    print("need an int from 0 to 6")
    sys.exit()

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
  PassEleTauHLTFinalTauFilter = array('i', [0])
  tree.SetBranchAddress("passhltHpsOverlapFilterIsoEle24WPTightGsfLooseETauWPDeepTauPFTau30", PassEleTauHLTFinalTauFilter)
  EleTauHLTFinalFilterTau_pt = ROOT.std.vector('float')()
  tree.SetBranchAddress("EleTauHLTFinalFilterTau_pt", EleTauHLTFinalFilterTau_pt)
  EleTauHLTFinalFilterTau_eta = ROOT.std.vector('float')()
  tree.SetBranchAddress("EleTauHLTFinalFilterTau_eta", EleTauHLTFinalFilterTau_eta)
  EleTauHLTFinalFilterTau_phi = ROOT.std.vector('float')()
  tree.SetBranchAddress("EleTauHLTFinalFilterTau_phi", EleTauHLTFinalFilterTau_phi)
  EleTauHLTFinalFilterTau_energy = ROOT.std.vector('float')()
  tree.SetBranchAddress("EleTauHLTFinalFilterTau_energy", EleTauHLTFinalFilterTau_energy)
  PassEleTauHLTFinalEleFilter = array('i', [0])
  tree.SetBranchAddress("passhltEle24erWPTightGsfTrackIsoFilterForTau", PassEleTauHLTFinalEleFilter)
  EleTauHLTFinalFilterEle_pt = ROOT.std.vector('float')()
  tree.SetBranchAddress("EleTauHLTFinalFilterEle_pt", EleTauHLTFinalFilterEle_pt)
  EleTauHLTFinalFilterEle_eta = ROOT.std.vector('float')()
  tree.SetBranchAddress("EleTauHLTFinalFilterEle_eta", EleTauHLTFinalFilterEle_eta)
  EleTauHLTFinalFilterEle_phi = ROOT.std.vector('float')()
  tree.SetBranchAddress("EleTauHLTFinalFilterEle_phi", EleTauHLTFinalFilterEle_phi)
  EleTauHLTFinalFilterEle_energy = ROOT.std.vector('float')()
  tree.SetBranchAddress("EleTauHLTFinalFilterEle_energy", EleTauHLTFinalFilterEle_energy)
  

  # HLT Final Decisions
  passEleTauHLT = array('i', [0])
  tree.SetBranchAddress("passEleTauHLT", passEleTauHLT)

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
  tree.SetBranchAddress("jetEnergy", OffJetEnergy)
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
  tree.SetBranchAddress("eleEnergy", OffEleEnergy)
  OffEleChargedHadronIso = ROOT.std.vector('float')()
  tree.SetBranchAddress("eleChargedHadronIso", OffEleChargedHadronIso)
  OffElePUChargedHadronIso = ROOT.std.vector('float')()
  tree.SetBranchAddress("elePUChargedHadronIso", OffElePUChargedHadronIso)
  OffEleNeutralHadronIso = ROOT.std.vector('float')()
  tree.SetBranchAddress("eleNeutralHadronIso", OffEleNeutralHadronIso)
  OffElePhotonIso = ROOT.std.vector('float')()
  tree.SetBranchAddress("elePhotonIso", OffElePhotonIso)

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
  OffTauPtToPass = 25
  # Ele
  OffElePtToPass = L1ElePtToPass + 1

  TallyVBFEle = 0
  TallyEleTau = 0
  TallyVBFEleAndEleTau = 0
  TallyVBFEleOrEleTau = 0

  for entry in range(tree.GetEntries()):
    tree.GetEntry(entry)

    # check if event passes L1 or HLT and has minimum object requirements
    basicReqs = ((passL1[0] or passEleTauHLT[0]) and (OffnJets[0] >= 2) and (OffnEles[0] >= 1) and (OffnTaus[0] >= 1))

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
 
      # leptopn hadronic activity variable
      # tyler's code and definition of the variable
      #iso = (ch_iso->at(i) / pt->at(i)) + std::max(0., (neu_iso->at(i) + pho_iso->at(i) - 0.5 * pu_iso->at(i)) / pt->at(i));

      # some debugging
      #print("start new")
      #for i in range(len(OffEleChargedHadronIso)):
      #  print(OffEleChargedHadronIso[i])
      #  print(OffElePt[i])
      #  print(OffEleNeutralHadronIso[i])
      #  print(OffElePhotonIso[i])
      #  print(OffEleChargedHadronIso[i])
      #  PassEleIso = OffEleChargedHadronIso[i] / OffElePt[i] + \
      #      max([0., (OffEleNeutralHadronIso[i] + OffElePhotonIso[i] - 0.5*OffEleChargedHadronIso[i]) / OffElePt[i]])

      #print(PassEleIso)
      # variable cuts events passing in half

      PassEleIso = [i for i in range(len(OffEleChargedHadronIso)) if 
                   ((OffEleChargedHadronIso[i] / OffElePt[i]) + \
                   max([0., (OffEleNeutralHadronIso[i] + OffElePhotonIso[i] - \
                     0.5*OffElePUChargedHadronIso[i]) / OffElePt[i]])) >= 0.15]
     
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
        #print("electron and tau overlapped!") 
        continue

      # assign Offline objects
      OffTau = OffTaus[0]
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
      if (sizeL1Jets < 2): continue
      L1Jet1Index, L1Jet2Index, L1Mjj = highestMjjPair(L1Jets)

      # see which offline jets the L1s are matched to
      matchL1OffJet = [i for i in range(sizeL1Jets) if 
                        (ROOT.TLorentzVector.DeltaR(OffJet1, L1Jets[i]) < 0.5 or
                         ROOT.TLorentzVector.DeltaR(OffJet2, L1Jets[i]) < 0.5 ) ]

      if (len(matchL1OffJet) < 2): continue # need at least two matched jets
      if (L1Jet1Index not in matchL1OffJet or L1Jet2Index not in matchL1OffJet): continue # need them to be the highest mjj pair
        #print("j1, j2, matched: {} {} {}".format(L1Jet1Index, L1Jet2Index, matchL1OffJet))

      # use this instead of L1Jet1/2Index directly 
      # alread checked that output was the same 
      L1Jet1 = L1Jets[matchL1OffJet[0]]
      L1Jet2 = L1Jets[matchL1OffJet[1]]

      L1Eles = fillWithTVecs(L1ElePt, L1EleEta, L1ElePhi, L1EleEnergy)
      sizeL1Eles = len(L1Eles)
      if (sizeL1Eles < 1): continue

      matchL1OffEle = [i for i in range(sizeL1Eles) if ROOT.TLorentzVector.DeltaR(OffEle, L1Eles[i]) < 0.5 ] 
      if (len(matchL1OffEle) == 0): continue

      L1Ele = L1Eles[matchL1OffEle[0]]

      # check that HLT objects can be matched to offline
      # should be MORE L1 objects that match than HLT objects from another trigger
      # the HLT objects can match different objects than the ones the L1s match
      HLTTaus = fillWithTVecs(EleTauHLTFinalFilterTau_pt, EleTauHLTFinalFilterTau_eta, \
                                EleTauHLTFinalFilterTau_phi, EleTauHLTFinalFilterTau_energy)
      sizeHLTTaus = len(HLTTaus)
      matchHLTOffTau = [i for i in range(sizeHLTTaus) if ROOT.TLorentzVector.DeltaR(OffTau, HLTTaus[i]) < 0.5]

      HLTEles = fillWithTVecs(EleTauHLTFinalFilterEle_pt, EleTauHLTFinalFilterEle_eta, \
                                EleTauHLTFinalFilterEle_phi, EleTauHLTFinalFilterEle_energy)
      sizeHLTEles = len(HLTEles)
      matchHLTOffEle = [i for i in range(sizeHLTEles) if ROOT.TLorentzVector.DeltaR(OffEle, HLTEles[i]) < 0.5]
      #matchHLTOffEle = [i for i in range(sizeHLTTaus) if ROOT.TLorentzVector.DeltaR(OffEle, HLTTaus[i]) < 0.5]

      passEleTauHLTOffMatching = False
      if ((sizeHLTTaus > 0) and (sizeHLTEles > 0)): passEleTauHLTOffMatching = True

      # we now have quality objects at L1 and Offline which are matched

      # we are testing what L1 at a given rate gives us the highest efficiency
      # how is efficiency defined?
      # unsure, let's see first highest gain.
      # to do this, we have a baseline L1 and matched offline objects
      # now, we have to artificially restrict the objects entering from
      # the baseline L1 by cutting on the L1 object kinematics. 
      # so, first thing we do is set a flag for events that pass
      
      passVBFEleL1Restrictions = False
      # L1 Kinematic Restrictions
      if (L1Jet1.Pt() >= L1JetPtToPass 
       and L1Jet2.Pt() >= L1JetPtToPass 
       and L1Mjj >= L1JetMjjToPass 
       and L1Ele.Pt() >= L1ElePtToPass): passVBFEleL1Restrictions = True

      passVBFEleOffCuts = False
      # next, set a flag for events that pass
      # Offline Cuts
      if (OffJet1.Pt() >= OffJetPtToPass
       and OffJet2.Pt() >= OffJetPtToPass
       and OffMjj >= OffJetMjjToPass
       and OffTau.Pt() >= OffTauPtToPass
       and OffEle.Pt() >= OffElePtToPass): passVBFEleOffCuts = True

      # that's all for the simulated L1
      # now we see how many events pass the EleTauHLT and offline cuts
      # we do this specifically because we assumed some heavy overlap
     
      passEleTauOffCuts = False
      if (OffJet1.Pt() >= 30
       and OffJet2.Pt() >= 30
       and OffMjj >= 300
       and OffTau.Pt() >= 30
       and OffEle.Pt() >= 24): passEleTauOffCuts = True

      # now tally it up
      if (passVBFEleL1Restrictions and passVBFEleOffCuts and passEleTauHLTOffMatching and passEleTauOffCuts): TallyVBFEleAndEleTau += 1
      if (passVBFEleL1Restrictions and passVBFEleOffCuts): TallyVBFEle += 1
      if (passEleTauHLTOffMatching and passEleTauOffCuts): TallyEleTau += 1
      if ((passVBFEleL1Restrictions and passVBFEleOffCuts) or (passEleTauHLTOffMatching and passEleTauOffCuts)): TallyVBFEleOrEleTau += 1
      #if ((passVBFEleL1Restrictions and passVBFEleOffCuts) or (passEleTauHLTOffMatching and passEleTauOffCuts)): 
      #  TallyVBFEleOrEleTau += 1
      #  if (passVBFEleL1Restrictions and passVBFEleOffCuts): TallyVBFEle += 1
      #  if (passEleTauHLTOffMatching and passEleTauOffCuts): TallyEleTau += 1 
      #  if (passVBFEleOffCuts and passEleTauOffCuts): TallyVBFEleAndEleTau += 1 


  print("""
        Total counts for L1\n
        L1_VBF_DoubleJet{0}_Mass_Min{1}_LooseIsoEG{2} \n
        VBFEle {3} \n
        EleTau {4} \n
        Ovrlap {5} \n
        Or     {6} \n
        EventsGained = {6}-{4} = {7} \n
        Percent Gain = {7}/{6} = {8:.2f}% \n
        """.format(L1JetPtToPass, L1JetMjjToPass, L1ElePtToPass,
                   TallyVBFEle, TallyEleTau, TallyVBFEleAndEleTau, TallyVBFEleOrEleTau,
                   TallyVBFEleOrEleTau-TallyEleTau, 100*(TallyVBFEleOrEleTau-TallyEleTau) / TallyVBFEleOrEleTau))

########################################################################
      # side-analysis, see how often we get the wrong objects.
      # a very detailed analysis of this would benefit algorithm construction
      # not sure i'm the person to do it though
      #if ( (len(matchL1OffJet) >= 2) and (len(matchL1OffEle) >= 1) ):
        #L1LeadingJetIndex, L1SubleadingJetIndex, L1Mjj = highestMjjPair(L1Jets)
        
        #if ((L1LeadingJetIndex != matchL1OffJet[0]) or (L1SubleadingJetIndex != matchL1OffJet[1])): 
          #print("Not L1 highest pT pair")
          #print("L1 Mjj = {}, Offline Mjj = {}, OffMjj - L1Mjj = {}".format(L1Mjj, OffMjj, OffMjj - L1Mjj))
          #print("iEntry {}".format(entry))
          #print(L1LeadingJetIndex, L1SubleadingJetIndex)
          #print(matchL1OffJet)
  

