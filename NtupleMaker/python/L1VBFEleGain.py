# Braden Allmond, August 10th 2022, KSU

from array import array
from L1VBFEle_functions import match_L1_to_Offline, match_Offline_to_L1, fillWithTVecs, highestMjjPair
import ROOT
import argparse
import sys

ROOT.gROOT.SetBatch(True) # sets visual display off (i.e. no graphs/TCanvas)

# usage: python3 L1VBFEleGain.py -i ../../../samples/VBFE_CorrectEleIsoAndNewFilter.root -L 6

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
  OffElePtToPass = L1ElePtToPass + 1 + 1

  TallyVBFEle = 0
  TallyEleTau = 0
  TallySingleEle = 0
  TallyEleTauAndSingleEle = 0
  TallyEleTauOrSingleEle = 0
  TallyTripleOr = 0

  TotalEntries = tree.GetEntries()
  for entry in range(TotalEntries):
    tree.GetEntry(entry)

    # check if event passes L1 or HLT and has minimum object requirements
    basicReqs = ((passL1[0] or passEleTauHLT[0] or passSingleEleHLT[0]) and (OffnJets[0] >= 2) and (OffnEles[0] >= 1) and (OffnTaus[0] >= 1))
    #basicReqs = ((passL1[0] or passEleTauHLT[0] or passSingleEleHLT[0]) and (OffnJets[0] >= 2) and (OffnEles[0] >= 1) and (OffnTaus[0] >= 1))
    #basicReqs = ((OffnJets[0] >= 2) and (OffnEles[0] >= 1) and (OffnTaus[0] >= 1))

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
      #OffElesPassFilter = list(set(PassEleID) & set(PassEleEta))
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

      # skip the event if the tau and electron have the same charge
      if (OffEleCh[OffElesPassFilter[0]] == OffTauCh[OffTausPassFilter[0]]): 
        #print(OffElesPassFilter, OffEleCh[OffElesPassFilter[0]])
        #print(OffTausPassFilter, OffTauCh[OffTausPassFilter[0]])
        continue

      # assign Offline objects
      OffTau = OffTaus[0]
      OffEle = OffEles[0]
      OffJet1Index, OffJet2Index, OffMjj = highestMjjPair(OffJets)
      OffJet1 = OffJets[OffJet1Index]
      OffJet2 = OffJets[OffJet2Index]
      if (ROOT.TLorentzVector.DeltaR(OffJet1, OffJet2) < 0.5): continue
 

      L1Jets = fillWithTVecs(L1JetPt, L1JetEta, L1JetPhi, L1JetEnergy)
      sizeL1Jets = len(L1Jets)
      L1Eles = fillWithTVecs(L1ElePt, L1EleEta, L1ElePhi, L1EleEnergy)
      sizeL1Eles = len(L1Eles)

      # check object sizes before matching
      matchL1Off = False
      tryToMatch = False
      if (sizeL1Jets >= 2 and sizeL1Eles >= 1): tryToMatch = True 

      if (tryToMatch == True):
        L1Ele = L1Eles[0]
        L1Jet1Index, L1Jet2Index, L1Mjj = highestMjjPair(L1Jets)
        L1Jet1 = L1Jets[L1Jet1Index]
        L1Jet2 = L1Jets[L1Jet2Index]

      # switch to match the right way (from Offline to L1) or wrong way (from L1 to Offline)
      match_right_way = True
      if (match_right_way == False):
        matchL1Off = match_L1_to_Offline(L1Ele, L1Jet1, L1Jet2, OffEle, OffJet1, OffJet2)
      else:
        matchL1Off, L1Indices = match_Offline_to_L1(L1Eles, L1Jets, OffEle, OffJet1, OffJet2)

      reassignL1 = True
      if (matchL1Off == True and reassignL1 == True and match_right_way == True):
        L1Ele  = L1Eles[L1Indices[0]]
        L1Jet1 = L1Jets[L1Indices[1]]
        L1Jet2 = L1Jets[L1Indices[2]]
        L1Mjj = (L1Jet1 + L1Jet2).M()


      # EleTau Matching
      EleTauHLTTaus = fillWithTVecs(EleTauFinalFilterTau_pt, EleTauFinalFilterTau_eta, \
                                EleTauFinalFilterTau_phi, EleTauFinalFilterTau_energy)
      sizeEleTauHLTTaus = len(EleTauHLTTaus)
      matchEleTauHLTOffTau = [i for i in range(sizeEleTauHLTTaus) 
                     if ROOT.TLorentzVector.DeltaR(OffTau, EleTauHLTTaus[i]) < 0.5]

      EleTauHLTEles = fillWithTVecs(EleTauFinalFilterEle_pt, EleTauFinalFilterEle_eta, \
                                EleTauFinalFilterEle_phi, EleTauFinalFilterEle_energy)
      sizeEleTauHLTEles = len(EleTauHLTEles)
      matchEleTauHLTOffEle = [i for i in range(sizeEleTauHLTEles) 
                     if ROOT.TLorentzVector.DeltaR(OffEle, EleTauHLTEles[i]) < 0.5]

      passEleTauHLTOffMatching = False
      if ( (len(matchEleTauHLTOffTau) > 0) and (len(matchEleTauHLTOffEle) > 0) ): passEleTauHLTOffMatching = True

      # SingleEle Matching
      SingleEleHLTEles = fillWithTVecs(SingleEleFinalFilter_pt, SingleEleFinalFilter_eta, \
                                   SingleEleFinalFilter_phi, SingleEleFinalFilter_energy)
      sizeSingleEleHLTEles = len(SingleEleHLTEles)
      matchSingleEleHLTOffEle = [i for i in range(sizeSingleEleHLTEles) 
                              if ROOT.TLorentzVector.DeltaR(OffEle, SingleEleHLTEles[i]) < 0.5]
      passSingleEleHLTOffMatching = False
      if (len(matchSingleEleHLTOffEle) > 0): passSingleEleHLTOffMatching = True
      # end matching

      # restrict the objects entering from the baseline L1 by cutting on the L1 object kinematics. 
      passVBFEleL1Restrictions = False
      if (matchL1Off):
        if (L1Jet1.Pt()  >= L1JetPtToPass 
         and L1Jet2.Pt() >= L1JetPtToPass 
         and L1Mjj       >= L1JetMjjToPass 
         and L1Ele.Pt()  >= L1ElePtToPass): passVBFEleL1Restrictions = True

      passVBFEleOffCuts = False
      if (OffJet1.Pt()  >= OffJetPtToPass
       and OffJet2.Pt() >= OffJetPtToPass
       and OffMjj       >= OffJetMjjToPass
       and OffTau.Pt()  >= OffTauPtToPass
       and OffEle.Pt()  >= OffElePtToPass): passVBFEleOffCuts = True

      passEleTauOffCuts = False
      if (OffJet1.Pt() >= 30
       and OffJet2.Pt() >= 30
       and OffMjj >= 300
       and OffTau.Pt() >= 30
       and OffEle.Pt() >= 25): passEleTauOffCuts = True

      passSingleEleOffCuts = (passEleTauOffCuts and OffEle.Pt() >= 33)

      # now tally it up
      GoodVBFEle = matchL1Off and passVBFEleL1Restrictions and passVBFEleOffCuts
      GoodEleTau = passEleTauHLTOffMatching and passEleTauOffCuts
      GoodSingleEle = passSingleEleHLTOffMatching and passSingleEleOffCuts

      # enough to calculate impact of VBF Ele, EleTau and SingleEle will be main overlap at analysis
      if (GoodVBFEle): TallyVBFEle += 1
      if (GoodEleTau): TallyEleTau += 1
      if (GoodSingleEle): TallySingleEle += 1

      if (GoodEleTau or GoodSingleEle): TallyEleTauOrSingleEle += 1
      if (GoodEleTau and GoodSingleEle): TallyEleTauAndSingleEle += 1

      if (GoodVBFEle or GoodEleTau or GoodSingleEle): TallyTripleOr += 1

  # print output
  print(f"match right way (Offline to L1): {match_right_way}")
  text_L1_Jet = "Total counts for L1_VBF_DoubleJets" + str(L1JetPtToPass) + "_Mass_Min" + str(L1JetMjjToPass)
  if (L1IndexToTest == 6): 
    text_L1_EG = "_IsoEG" + str(L1ElePtToPass)
  else:
    text_L1_EG = "_LooseIsoEG" + str(L1ElePtToPass)
  print(text_L1_Jet + text_L1_EG)

  # formatting a table to print instead of free-form printing
  labels = ["SingleEle", "EleTau", "OR", "AND"]
  print(f"{labels[0]:<10} {labels[1]:<9} {labels[2]:<9} {labels[3]:<9}")
  values = [TallySingleEle, TallyEleTau, TallyEleTauOrSingleEle, TallyEleTauAndSingleEle]
  print(f"{values[0]:<10} {values[1]:<9} {values[2]:<9} {values[3]:<9}")

  UniqueVBF = TallyTripleOr - TallyEleTauOrSingleEle
  Gain = ( (TallyTripleOr / TallyEleTauOrSingleEle) - 1)*100
  labels = ["VBF+Ele", "TripleOR", "Unique", "Gain"]
  print(f"{labels[0]:<10} {labels[1]:<9} {labels[2]:<9} {labels[3]:<9}")
  values = [TallyVBFEle, TallyTripleOr, UniqueVBF, Gain]
  print(f"{values[0]:<10} {values[1]:<9} {values[2]:<9} {values[3]:<.1f}%")

