# Braden Allmond, August 10th 2022, KSU

from array import array
from L1VBFEle_functions import match_L1_to_Offline, match_Offline_to_L1, fillWithTVecs, fillWithTVecsNoEnergyBranch, highestMjjPair, print_formatted_labels_and_values
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
  
    # HLT Final Decisions
    passMuTauHLT = array('i', [0])
    tree.SetBranchAddress("passMuTauHLT", passMuTauHLT)

    passIsoMu24eta2p1HLT = array('i', [0])
    tree.SetBranchAddress("passIsoMu24eta2p1HLT", passIsoMu24eta2p1HLT)

    passVBFMuonHLT = array('i', [0])
    tree.SetBranchAddress("passVBFMuonHLT", passVBFMuonHLT)

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
  TallyMuTauOff = 0
  TallySingleMuOff = 0
  TallyVBFMuORMuTauOff = 0
  TallyVBFMuORSingleMuOff = 0
  TallyMuTauORSingleMuOff = 0
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
    basicReqs = ( notRateStudy and (OffnJets[0] >= 2) and (OffnMus[0] >= 1) and (OffnTaus[0] >= 1))

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
      if (ROOT.TLorentzVector.DeltaR(OffMus[0], OffTaus[0]) < 0.5): 
        continue

      # skip the event if the tau and electron have the same charge
      if (OffMuCh[OffMusPassFilter[0]] == OffTauCh[OffTausPassFilter[0]]):
        continue

      # assign Offline objects
      OffTau = OffTaus[0] # consider selecting tau based on isolation, not pt
      OffMu = OffMus[0]
      OffJet1Index, OffJet2Index, OffMjj = highestMjjPair(OffJets)
      OffJet1 = OffJets[OffJet1Index]
      OffJet2 = OffJets[OffJet2Index]
      if (ROOT.TLorentzVector.DeltaR(OffJet1, OffJet2) < 0.5): continue


      # MuTau HLT Matching
      MuTauHLTMuons = fillWithTVecs(MuTauFinalMuonFilter_pt, MuTauFinalMuonFilter_eta,
                                    MuTauFinalMuonFilter_phi, MuTauFinalMuonFilter_energy)
      sizeMuTauHLTMuons = len(MuTauHLTMuons)
      matchMuTauHLTOffMuons = [i for i in range(sizeMuTauHLTMuons)
                            if ROOT.TLorentzVector.DeltaR(OffMu, MuTauHLTMuons[i]) < 0.5]

      MuTauHLTTaus = fillWithTVecs(MuTauFinalTauFilter_pt, MuTauFinalTauFilter_eta,
                                    MuTauFinalTauFilter_phi, MuTauFinalTauFilter_energy)
      sizeMuTauHLTTaus = len(MuTauHLTTaus)
      matchMuTauHLTOffTaus = [i for i in range(sizeMuTauHLTTaus)
                            if ROOT.TLorentzVector.DeltaR(OffMu, MuTauHLTTaus[i]) < 0.5]
      passMuTauHLTOffMatching = False
      if ( (len(matchMuTauHLTOffMuons) > 0) and (len(matchMuTauHLTOffTaus) > 0) ): passMuTauHLTOffMatching = True 

      # Single Mu HLT Matching
      SingleMuHLTMuons = fillWithTVecs(SingleMuAndLowerMuTauFinalFilter_pt, SingleMuAndLowerMuTauFinalFilter_eta,
                        SingleMuAndLowerMuTauFinalFilter_phi, SingleMuAndLowerMuTauFinalFilter_energy)
      sizeSingleMuHLTMuons = len(SingleMuHLTMuons)
      matchSingleMuHLTMuons = [i for i in range(sizeSingleMuHLTMuons)
                            if ROOT.TLorentzVector.DeltaR(OffMu, SingleMuHLTMuons[i]) < 0.5]
      passSingleMuHLTOffMatching = False
      if ( len(matchSingleMuHLTMuons) > 0): passSingleMuHLTOffMatching = True

      # VBF Mu HLT Matching 
      VBFMuHLTMuons = fillWithTVecs(VBFMuonFinalMuonFilter_pt, VBFMuonFinalMuonFilter_eta,
                                    VBFMuonFinalMuonFilter_phi, VBFMuonFinalMuonFilter_energy)
      sizeVBFMuHLTMuons = len(VBFMuHLTMuons)
      matchVBFMuHLTMuons = [i for i in range(sizeVBFMuHLTMuons)
                         if ROOT.TLorentzVector.DeltaR(OffMu, VBFMuHLTMuons[i]) < 0.5]

      VBFMuHLTJets = fillWithTVecs(VBFMuonFinalJetFilter_pt, VBFMuonFinalJetFilter_eta,
                                   VBFMuonFinalJetFilter_phi, VBFMuonFinalJetFilter_energy)
      sizeVBFMuHLTJets = len(VBFMuHLTJets)
      matchVBFMuHLTJet1 = [i for i in range(sizeVBFMuHLTJets)
                        if ROOT.TLorentzVector.DeltaR(OffJet1, VBFMuHLTJets[i]) < 0.5]
      matchVBFMuHLTJet2 = [i for i in range(sizeVBFMuHLTJets)
                        if ROOT.TLorentzVector.DeltaR(OffJet2, VBFMuHLTJets[i]) < 0.5]
      passVBFMuHLTOffMatching = False
      if ( (len(matchVBFMuHLTMuons) > 0) and (len(matchVBFMuHLTJet1) > 0) and (len(matchVBFMuHLTJet2) > 0)): passVBFMuHLTOffMatching = True
      # end matching

      passMuTauOffCuts = False
      if (OffJet1.Pt() >= 30
       and OffJet2.Pt() >= 30
       and OffMjj >= 300 # crazy loose, no? can't find source for this
       and OffTau.Pt() >= 30
       and OffMu.Pt() >= 21): passMuTauOffCuts = True

      passSingleMuOffCuts = (passMuTauOffCuts and OffMu.Pt() >= 25)

      # TODO: open and look at VBFMuon path (need screenshot and module level cuts)
      passVBFMuOffCuts = False
      if (OffJet1.Pt()  >= 85 
       and OffJet2.Pt() >= 35
       and OffMjj       >= 600
       and OffTau.Pt()  >= 30
       and OffMu.Pt()  >= 4): passVBFMuOffCuts = True


      # now tally it up
      GoodMuTau = passMuTauHLTOffMatching and passMuTauOffCuts and passMuTauHLT[0]
      #GoodSingleMu = passSingleMuHLTOffMatching and passSingleMuOffCuts and passIsoMu24eta2p1HLT[0]
      GoodSingleMu = passSingleMuOffCuts and passIsoMu24eta2p1HLT[0]
      #print(passSingleMuHLTOffMatching, passSingleMuOffCuts, passIsoMu24eta2p1HLT[0])
      GoodVBFMu = passVBFMuHLTOffMatching and passVBFMuOffCuts and passVBFMuonHLT[0]

      #outPassMuTauOff[0] = GoodMuTau
      #outPassSingleMuOff[0] = GoodSingleMu
      #outPassVBFMuTauOff[0] = GoodVBFMu

      outtree.Fill()

      # enough to calculate impact of VBF Mu, MuTau and SingleMu will be main overlap at analysis
      if (GoodVBFMu): TallyVBFMuOff += 1
      if (GoodMuTau): TallyMuTauOff += 1
      if (GoodSingleMu): TallySingleMuOff += 1

      if (GoodVBFMu or GoodMuTau): TallyVBFMuORMuTauOff += 1
      if (GoodVBFMu or GoodSingleMu): TallyVBFMuORSingleMuOff += 1
      if (GoodMuTau or GoodSingleMu): TallyMuTauORSingleMuOff += 1

      if (GoodVBFMu or GoodMuTau or GoodSingleMu): TallyTripleOROff += 1

      Off_Tallies = [TallyVBFMuOff, TallyMuTauOff, TallySingleMuOff, \
                     TallyVBFMuORMuTauOff, TallyVBFMuORSingleMuOff, TallyMuTauORSingleMuOff, \
                     TallyTripleOROff, TallyTripleOROff - TallyMuTauORSingleMuOff]

  # print output
  print("\033[42m" + f"nViableEvents: {viableEventCounter}" + "\033[0m")

  print("-"*40)
  if (notRateStudy):
    labels = ["VBF+Mu", "MuTau", "SingleMu", \
              "VBFMuORMuTau", "VBFMuORSingleMu", "MuTauORSingleMu", \
              "TripleOR", "UniqueVBFMu"]
    for index, label in enumerate(labels):
      print(f"{label:19}, {Off_Tallies[index]:7}")

  if (rateStudy):
    labels = ["VBF+Mu", "VBFDiJetOR", "VBFIsoTau", "DummyEGL1", \
              "VBFDiJetORVBFDiTau", "NotVBFEG", "VBFTripleOR", "QuadOR", "UniqueVBFMu"]
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

