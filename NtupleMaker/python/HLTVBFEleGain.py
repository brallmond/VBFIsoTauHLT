# Braden Allmond, August 10th 2022, KSU

from array import array
from helper_functions import match_L1_to_Offline, match_Offline_to_L1, fillWithTVecs, fillWithTVecsNoEnergyBranch, highestMjjPair, print_formatted_labels_and_values
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


  # read input file name and prepend to output name

  output_name = "temp_outname.root"
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

  outL1DiJetORJet1 = array('f', [0.])
  outL1DiJetORJet2 = array('f', [0.])
  outL1DiJetORJet3 = array('f', [0.])
  outL1DiJetORMjj = array('f', [0.])
  outtree.Branch("L1DiJetORJet1", outL1DiJetORJet1, 'pt/F')
  outtree.Branch("L1DiJetORJet2", outL1DiJetORJet2, 'pt/F')
  outtree.Branch("L1DiJetORJet3", outL1DiJetORJet3, 'pt/F')
  outtree.Branch("L1DiJetORMjj", outL1DiJetORMjj, 'mjj/F')

  outL1VBFIsoTau_TauPt = array('f', [0.])
  outL1VBFIsoTau_Jet1Pt = array('f', [0.])
  outL1VBFIsoTau_Jet2Pt = array('f', [0.])
  outL1VBFIsoTau_Mjj = array('f', [0.])
  outtree.Branch("L1IsoTau_TauPt", outL1VBFIsoTau_TauPt, 'pt/F')
  outtree.Branch("L1IsoTau_Jet1Pt", outL1VBFIsoTau_Jet1Pt, 'pt/F')
  outtree.Branch("L1IsoTau_Jet2Pt", outL1VBFIsoTau_Jet2Pt, 'pt/F')
  outtree.Branch("L1IsoTau_Mjj", outL1VBFIsoTau_Mjj, 'mjj/F')

  outPassL1VBFDiJetEG = array('i', [0])
  outPassL1VBFDiJetOR = array('i', [0])
  outPassL1VBFDiJetIsoTau = array('i', [0])
  outPassDummyEGORL1 = array('i', [0])
  outtree.Branch("passL1VBFDiJetEG", outPassL1VBFDiJetEG, 'pass/I')
  outtree.Branch("passL1VBFDiJetOR", outPassL1VBFDiJetOR, 'pass/I')
  outtree.Branch("passL1VBFDiJetIsoTau", outPassL1VBFDiJetIsoTau, 'pass/I')
  outtree.Branch("passDummyEGORL1", outPassDummyEGORL1, 'pass/I')

  outPassVBFEleTauOff = array('i', [0])
  outPassEleTauOff = array('i', [0])
  outPassSingleEleOff = array('i', [0])
  outtree.Branch("passVBFEleTauOff", outPassVBFEleTauOff, 'pass/I')
  outtree.Branch("passEleTauOff", outPassEleTauOff, 'pass/I')
  outtree.Branch("passSingleEleOff", outPassSingleEleOff, 'pass/I')

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
  print(f"Looking at run = {goodRunNumber}, LS Range [{minLS}, {maxLS}], Bad LS = {badLS}")

  is2022 = True # can use False and 2018 EZB samples for HLT rate
  if (is2022 and notRateStudy): 
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
    tree.SetBranchAddress("passhltL1VBFIsoEG", PassVBFIsoEGL1)
    L1ElePt = ROOT.std.vector('float')()
    L1EleEta = ROOT.std.vector('float')()
    L1ElePhi = ROOT.std.vector('float')()
    L1EleEnergy = ROOT.std.vector('float')()
    tree.SetBranchAddress("hltL1VBFElectron_ePt", L1ElePt)
    tree.SetBranchAddress("hltL1VBFElectron_eEta", L1EleEta)
    tree.SetBranchAddress("hltL1VBFElectron_ePhi", L1ElePhi)
    tree.SetBranchAddress("hltL1VBFElectron_eEnergy", L1EleEnergy)

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
  
    # HLT Final Decisions
    passEleTauHLT = array('i', [0])
    tree.SetBranchAddress("passEleTauHLT", passEleTauHLT)
    passSingleEleHLT = array('i', [0])
    tree.SetBranchAddress("passSingleEleHLT", passSingleEleHLT)
    passVBFEleHLT = array('i', [0])
    tree.SetBranchAddress("passVBFEleHLT", passVBFEleHLT)

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


  TallyVBFEleOff = 0
  TallyEleTauOff = 0
  TallySingleEleOff = 0
  TallyVBFEleOREleTauOff = 0
  TallyVBFEleORSingleEleOff = 0
  TallyEleTauORSingleEleOff = 0
  TallyTripleOROff = 0

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
    #basicReqs = ((passL1[0]) and (OffnJets[0] >= 2) and (OffnEles[0] >= 1) and (OffnTaus[0] >= 1))
    basicReqs = ( notRateStudy and (OffnJets[0] >= 2) and (OffnEles[0] >= 1) and (OffnTaus[0] >= 1))

    if basicReqs:
      viableEventCounter += 1
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
      L1Eles = fillWithTVecs(L1ElePt, L1EleEta, L1ElePhi, L1EleEnergy)
      sizeL1Eles = len(L1Eles)
      if (sizeL1Eles >= 1 and PassVBFIsoEGL1[0]):
        L1Ele = L1Eles[0]


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

      # VBF Ele HLT Matching 
      VBFEleHLTEles = fillWithTVecs(VBFEleFinalEleFilter_pt, VBFEleFinalEleFilter_eta,
                                    VBFEleFinalEleFilter_phi, VBFEleFinalEleFilter_energy)
      sizeVBFEleHLTEles = len(VBFEleHLTEles)
      matchVBFEleHLTOffEle = [i for i in range(sizeVBFEleHLTEles)
                           if ROOT.TLorentzVector.DeltaR(OffEle, VBFEleHLTEles[i]) < 0.5]
      passVBFEleHLTOffEleMatching = False
      if (len(matchVBFEleHLTOffEle) > 0): passVBFEleHLTOffMatching = True
      #print(sizeVBFEleHLTEles, len(matchVBFEleHLTOffEle), passVBFEleHLTOffEleMatching)

      VBFEleHLTJets = fillWithTVecs(VBFEleFinalJetFilter_pt, VBFEleFinalJetFilter_eta,
                                    VBFEleFinalJetFilter_phi, VBFEleFinalJetFilter_energy)
      sizeVBFEleHLTJets = len(VBFEleHLTJets)
      matchVBFEleHLTOffJet1 = [i for i in range(sizeVBFEleHLTJets)
                            if ROOT.TLorentzVector.DeltaR(OffJet1, VBFEleHLTJets[i]) < 0.5]
      matchVBFEleHLTOffJet2 = [i for i in range(sizeVBFEleHLTJets)
                            if ROOT.TLorentzVector.DeltaR(OffJet2, VBFEleHLTJets[i]) < 0.5]
      passVBFEleHLTOffJetMatching = False
      if (len(matchVBFEleHLTOffJet1) > 0 and len(matchVBFEleHLTOffJet2)): passVBFEleHLTOffJetMatching = True

      passVBFEleHLTOffMatching = passVBFEleHLTOffEleMatching and passVBFEleHLTOffJetMatching

      # end matching

      passEleTauOffCuts = False
      if (OffJet1.Pt() >= 30
       and OffJet2.Pt() >= 30
       and OffMjj >= 300
       and OffTau.Pt() >= 30
       and OffEle.Pt() >= 25): passEleTauOffCuts = True

      # require a high pt iso ele to emulate the lowest L1 with PS != 0 for this HLT path
      passL1IsoElePresent = False
      if (PassVBFIsoEGL1[0]):
        passL1IsoElePresent = L1Ele.Pt() >= 30
      passSingleEleOffCuts = (passL1IsoElePresent and passEleTauOffCuts and OffEle.Pt() >= 33)

      # FIXME : double check those cut values
      passVBFEleOffCuts = False
      if (OffJet1.Pt()  >= 50 #40, 40, 500, 30, 15
       and OffJet2.Pt() >= 50
       and OffMjj       >= 600
       and OffTau.Pt()  >= 30
       and OffEle.Pt()  >= 13): passVBFEleOffCuts = True


      # now tally it up
      GoodEleTau = passEleTauHLTOffMatching and passEleTauOffCuts and passEleTauHLT[0]
      GoodSingleEle = passSingleEleHLTOffMatching and passSingleEleOffCuts and passSingleEleHLT[0]
      #GoodVBFEle = passVBFEleHLTOffMatching and passVBFEleOffCuts and passVBFEleHLT[0]
      GoodVBFEle = passVBFEleOffCuts and passVBFEleHLT[0]

      outPassEleTauOff[0] = GoodEleTau
      outPassSingleEleOff[0] = GoodSingleEle
      outPassVBFEleTauOff[0] = GoodVBFEle

      outtree.Fill()

      # enough to calculate impact of VBF Ele, EleTau and SingleEle will be main overlap at analysis
      if (GoodVBFEle): TallyVBFEleOff += 1
      if (GoodEleTau): TallyEleTauOff += 1
      if (GoodSingleEle): TallySingleEleOff += 1

      if (GoodVBFEle or GoodEleTau): TallyVBFEleOREleTauOff += 1
      if (GoodVBFEle or GoodSingleEle): TallyVBFEleORSingleEleOff += 1
      if (GoodEleTau or GoodSingleEle): TallyEleTauORSingleEleOff += 1

      if (GoodVBFEle or GoodEleTau or GoodSingleEle): TallyTripleOROff += 1

      Off_Tallies = [TallyVBFEleOff, TallyEleTauOff, TallySingleEleOff, \
                     TallyVBFEleOREleTauOff, TallyVBFEleORSingleEleOff, TallyEleTauORSingleEleOff, \
                     TallyTripleOROff, TallyTripleOROff - TallyEleTauORSingleEleOff]

  # print output
  print("\033[42m" + f"nViableEvents: {viableEventCounter}" + "\033[0m")

  print("-"*40)
  if (notRateStudy):
    labels = ["VBF+Ele", "EleTau", "SingleEle", \
              "VBFEleOREleTau", "VBFEleORSingleEle", "EleTauORSingleEle", \
              "TripleOR", "UniqueVBFEle"]
    for index, label in enumerate(labels):
      print(f"{label:19}, {Off_Tallies[index]:7}")

  if (rateStudy):
    labels = ["VBF+Ele", "VBFDiJetOR", "VBFIsoTau", "DummyEGL1", \
              "VBFDiJetORVBFDiTau", "NotVBFEG", "VBFTripleOR", "QuadOR", "UniqueVBFEle"]
    for index, label in enumerate(labels):
      print(f"{label:19}, {L1_Tallies[index]:7}")

    uniqueL1VBFEG = L1_Tallies[-1]
    # print rate info and unpure/pure rate
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

  outtree.Write()
  outFile.Close()

