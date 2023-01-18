# Braden Allmond, August 10th 2022, KSU

from array import array
from L1VBFEle_functions import match_L1_to_Offline, match_Offline_to_L1, fillWithTVecs, fillWithTVecsNoEnergyBranch, highestMjjPair
import ROOT
import argparse
import sys

ROOT.gROOT.SetBatch(True) # sets visual display off (i.e. no graphs/TCanvas)

# usage:
# gain/efficiency mode
# python3 L1VBFEleEff.py -i ../../../../../samples/VBFE_wMuTauFilters.root -r n -s tight -L 0
# rate mode
# python3 L1VBFEleEff.py -i ../../../../../samples/EZBs/EZB_2018/EZB1_EGOR.root -r y -s tight -L 0

if __name__ == "__main__":

  parser = argparse.ArgumentParser(description='Open a .root file')
  parser.add_argument('-i', '--inputRootFile', dest='inFilename', action='store',
                    help='the input .root file\'s name')
  parser.add_argument('-L', '--L1IndexToTest', dest='L1IndexToTest', action='store',
                    help='the L1 being tested')
  parser.add_argument('-s', '--L1LooseOrTightIso', dest='L1LooseOrTightIso', action='store',
                    help='the iso you would like to use (loose or tight)')
  parser.add_argument('-r', '--rateStudy', dest='rateStudy', action='store',
                    help='is this a rate study (yes or no)')
  args = parser.parse_args()

  inFile = ROOT.TFile.Open(args.inFilename,"READ")
  tree = inFile.Get("demo/vbf")

  ROOT.TH1.SetDefaultSumw2()

  # L1 and Offline cuts are just integers so we define them outside the event loop
              # pt  mjj  ele pt    
  L1sToTest = [[30, 300, 10], #0, for rate studies
               [38, 460, 12], #1
               [40, 460, 12], #2
               [42, 460, 12], #3
               [32, 440, 14], #4
               [34, 440, 14], #5
               [36, 440, 14], #6
               # Iso
               [30, 320, 10], #7
               [30, 380, 10], #8
               [30, 440, 10], #9
               # to be tested
               [45, 500, 12], #10
               [30, 500, 14], #11
               [35, 500, 14], #12
               [40, 500, 14], #13
               [45, 500, 14], #14
               [50, 500, 14], #15
               ]

  match_right_way = True # used for a matching study, left hardcoded assuming the study won't need to be repeated
  L1LooseOrTightIso = (args.L1LooseOrTightIso).lower()

  #rateStudy = ('y' in args.rateStudy.lower())
  rateStudyString = args.rateStudy.upper()
  isValidString = (rateStudyString == "2018B" or  rateStudyString == "2018O" or rateStudyString == "2022E")
  notRateStudy = 'NOTRATE' in rateStudyString
  rateStudy = not notRateStudy and isValidString # "not not" is the same as "is"
  if (rateStudy):
    print("\033[31m" + "This IS a rate study. L1IndexToTest has been set to zero !" + "\033[0m")
    L1IndexToTest = 0;
  else:
    print("\033[31m" + "This is NOT a rate study. Make sure you're using an MC sample!" + "\033[0m")
    L1IndexToTest = int(args.L1IndexToTest)

  L1Cuts = L1sToTest[L1IndexToTest] #defined by argparse
  print("L1 Cuts: [jets, mjj, elePt] ", L1Cuts)
  L1JetPtToPass =  L1Cuts[0]
  L1JetMjjToPass = L1Cuts[1]
  L1ElePtToPass =  L1Cuts[2]

  if (L1LooseOrTightIso == "tight"): 
    text_L1_EG = "_IsoEG" + str(L1ElePtToPass)
  else:
    text_L1_EG = "_LooseIsoEG" + str(L1ElePtToPass)

  output_name = "L1_VBF_DoubleJets" + str(L1JetPtToPass) + "_Mass_Min" + str(L1JetMjjToPass) + text_L1_EG + ".root"
  print(f"Total counts for {output_name}")

  # declare outtree name and branches
  outFile = ROOT.TFile.Open(output_name, "RECREATE")
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

  # error handling for using loose or tight iso branches
  if (L1LooseOrTightIso != "loose" and L1LooseOrTightIso != "tight"):
    print(f"argument L1LooseOrTightIso must be 'loose' or 'tight', given {L1LooseOrTightIso}")
    sys.exit()

  # hell to read but
  # defining a variable/object handle 
  #   objName = type('typename')(initialization*) *initialization changes by type
  # and then linking that object handle to an available branch in the event tree
  #   tree.SetBranchAddress("branchOfObjInTree", objHandle)

  # Rate
  runNumber = array('i', [0])
  lumiSection = array('i', [0])
  lumiSectionCounter = 0
  tree.SetBranchAddress("runNumber", runNumber)
  tree.SetBranchAddress("lumiBlock", lumiSection)

  rateDictionary = {
    "NOTRATE" :    {"runNumber" : -999, "minLS" : -999, "maxLS" : -999},
    #"2018B" : {"runNumber" : 323755, "minLS1" : 38, "maxLS1" : 81, "minLS2" :  84, "maxLS2" : 171},
    "2018O" : {"runNumber" : 323755, "minLS" : 52, "maxLS" : 152}, # L ~ 1.79
    "2022E" : {"runNumber" : 359871, "minLS" : 1,  "maxLS" : 100}, # L ~ 1.84 
  }

  goodRunNumber = rateDictionary[rateStudyString]["runNumber"]
  minLS = rateDictionary[rateStudyString]["minLS"]
  maxLS = rateDictionary[rateStudyString]["maxLS"]
  print(f"Looking at run = {goodRunNumber}, LS Range [{minLS}, {maxLS}]")

  # L1
  #if (L1IndexToTest == 6 or L1IndexToTest == 7 or L1IndexToTest == 8):
  if (L1LooseOrTightIso == "tight"):
    passL1 = array('i', [0])
    tree.SetBranchAddress("passhltL1VBFElectron", passL1)
    L1JetPt = ROOT.std.vector('float')()
    L1JetEta = ROOT.std.vector('float')()
    L1JetPhi = ROOT.std.vector('float')()
    L1JetEnergy = ROOT.std.vector('float')()
    tree.SetBranchAddress("hltL1VBFElectron_jPt", L1JetPt)
    tree.SetBranchAddress("hltL1VBFElectron_jEta", L1JetEta)
    tree.SetBranchAddress("hltL1VBFElectron_jPhi", L1JetPhi)
    tree.SetBranchAddress("hltL1VBFElectron_jEnergy", L1JetEnergy)
    L1ElePt = ROOT.std.vector('float')()
    L1EleEta = ROOT.std.vector('float')()
    L1ElePhi = ROOT.std.vector('float')()
    L1EleEnergy = ROOT.std.vector('float')()
    tree.SetBranchAddress("hltL1VBFElectron_ePt", L1ElePt)
    tree.SetBranchAddress("hltL1VBFElectron_eEta", L1EleEta)
    tree.SetBranchAddress("hltL1VBFElectron_ePhi", L1ElePhi)
    tree.SetBranchAddress("hltL1VBFElectron_eEnergy", L1EleEnergy)
 
  else:
    passL1 = array('i', [0])
    tree.SetBranchAddress("passhltL1VBFElectronLoose", passL1)
    L1JetPt = ROOT.std.vector('float')()
    L1JetEta = ROOT.std.vector('float')()
    L1JetPhi = ROOT.std.vector('float')()
    L1JetEnergy = ROOT.std.vector('float')()
    tree.SetBranchAddress("hltL1VBFElectronLoose_jPt", L1JetPt)
    tree.SetBranchAddress("hltL1VBFElectronLoose_jEta", L1JetEta)
    tree.SetBranchAddress("hltL1VBFElectronLoose_jPhi", L1JetPhi)
    tree.SetBranchAddress("hltL1VBFElectronLoose_jEnergy", L1JetEnergy)
    L1ElePt = ROOT.std.vector('float')()
    L1EleEta = ROOT.std.vector('float')()
    L1ElePhi = ROOT.std.vector('float')()
    L1EleEnergy = ROOT.std.vector('float')()
    tree.SetBranchAddress("hltL1VBFElectronLoose_ePt", L1ElePt)
    tree.SetBranchAddress("hltL1VBFElectronLoose_eEta", L1EleEta)
    tree.SetBranchAddress("hltL1VBFElectronLoose_ePhi", L1ElePhi)
    tree.SetBranchAddress("hltL1VBFElectronLoose_eEnergy", L1EleEnergy)

  is2022 = False
  if (is2022): 
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
  
    # HLT Final Decisions
    passEleTauHLT = array('i', [0])
    tree.SetBranchAddress("passEleTauHLT", passEleTauHLT)
    passSingleEleHLT = array('i', [0])
    tree.SetBranchAddress("passSingleEleHLT", passSingleEleHLT)

  # Offline kinems
  if (not rateStudy):
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

  # the offline cuts are applied to the offline objects
  # they are a flat increase of L1 kinem cuts
  OffJetPtToPass = L1JetPtToPass + 15
  OffJetMjjToPass = L1JetMjjToPass + 100
  OffTauPtToPass = 30 
  OffElePtToPass = L1ElePtToPass + 3 
  OffCuts = [OffJetPtToPass, OffJetMjjToPass, OffElePtToPass, OffTauPtToPass]
  print("Off Cuts: [jets, mjj, elePt, tauPt] ", OffCuts)

  TallyVBFEle = 0
  TallyEleTau = 0
  TallySingleEle = 0
  TallyEleTauAndSingleEle = 0
  TallyEleTauOrSingleEle = 0
  TallyTripleOr = 0

  TotalEntries = tree.GetEntries()
  for entry in range(TotalEntries):
  #for entry in range(100):
    tree.GetEntry(entry)

    # if rate study
    runNumberValue = str(runNumber[0])
    lumiSectionValue = lumiSection[0]

    goodLumi = lumiSectionValue >= minLS and lumiSectionValue <= maxLS
    if (runNumberValue == goodRunNumber and goodLumi):
    #if runNumber and lumiBlock
    # fill tree
    # continue to next event
      lumiSectionCounter += 1

    #print(runNumberValue, lumiSectionValue)
    continue

    # requiring events to pass your L1 biases your selection, fine for gain study, not fine for eff study
    #basicReqs = ((passL1[0]) and (OffnJets[0] >= 2) and (OffnEles[0] >= 1) and (OffnTaus[0] >= 1))
    basicReqs = ( not rateStudy and (OffnJets[0] >= 2) and (OffnEles[0] >= 1) and (OffnTaus[0] >= 1))

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

      # get L1 objects 
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

      ### comparing filling TVecs with/without an energy branch ###

      #  otherL1Jets = fillWithTVecsNoEnergyBranch(L1JetPt, L1JetEta, L1JetPhi)
      #  _, _, otherL1Mjj = highestMjjPair(otherL1Jets)
      #  print(f"compare mjj: {L1Mjj:.1f}  {otherL1Mjj:.1f}  {L1Mjj-otherL1Mjj:.1f}")

      ### for Electron L1s, not having an energy branch could, in principle, affect the matching
      ### but right now we just care about the rate so the energy branch will have no effect

      # switch to match the right way (from Offline to L1) or wrong way (from L1 to Offline)
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

      # writing branch info

      outMatchL1Off[0] = matchL1Off

      if (tryToMatch == True): # only possible to fill L1s if they are available and matching was attempted
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

      # EleTau HLT Matching
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

      # SingleEle HLT Matching
      SingleEleHLTEles = fillWithTVecs(SingleEleFinalFilter_pt, SingleEleFinalFilter_eta, \
                                   SingleEleFinalFilter_phi, SingleEleFinalFilter_energy)
      sizeSingleEleHLTEles = len(SingleEleHLTEles)
      matchSingleEleHLTOffEle = [i for i in range(sizeSingleEleHLTEles) 
                              if ROOT.TLorentzVector.DeltaR(OffEle, SingleEleHLTEles[i]) < 0.5]
      passSingleEleHLTOffMatching = False
      if (len(matchSingleEleHLTOffEle) > 0): passSingleEleHLTOffMatching = True
      # end matching

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
      GoodEleTau = passEleTauHLTOffMatching and passEleTauOffCuts and passEleTauHLT
      GoodSingleEle = passSingleEleHLTOffMatching and passSingleEleOffCuts and passSingleEleHLT

      # enough to calculate impact of VBF Ele, EleTau and SingleEle will be main overlap at analysis
      if (GoodVBFEle): TallyVBFEle += 1
      if (GoodEleTau): TallyEleTau += 1
      if (GoodSingleEle): TallySingleEle += 1

      if (GoodEleTau or GoodSingleEle): TallyEleTauOrSingleEle += 1
      if (GoodEleTau and GoodSingleEle): TallyEleTauAndSingleEle += 1

      if (GoodVBFEle or GoodEleTau or GoodSingleEle): TallyTripleOr += 1

  # print output
  print(f"match right way (Offline to L1): {match_right_way}")

  print(f"LS Count: {lumiSectionCounter}")
  
  # formatting a table to print instead of free-form printing
  labels = ["SingleEle", "EleTau", "OR", "AND"]
  print(f"{labels[0]:<10} {labels[1]:<9} {labels[2]:<9} {labels[3]:<9}")
  values = [TallySingleEle, TallyEleTau, TallyEleTauOrSingleEle, TallyEleTauAndSingleEle]
  print(f"{values[0]:<10} {values[1]:<9} {values[2]:<9} {values[3]:<9}")

  UniqueVBF = TallyTripleOr - TallyEleTauOrSingleEle
  if (TallyEleTauOrSingleEle != 0):
    Gain = ( (TallyTripleOr / TallyEleTauOrSingleEle) - 1)*100
  else:
    Gain = -999
  labels = ["VBF+Ele", "TripleOR", "Unique", "Gain"]
  print(f"{labels[0]:<10} {labels[1]:<9} {labels[2]:<9} {labels[3]:<9}")
  values = [TallyVBFEle, TallyTripleOr, UniqueVBF, Gain]
  print(f"{values[0]:<10} {values[1]:<9} {values[2]:<9} {values[3]:<.1f}%")

  outtree.Write()
  outFile.Close()

