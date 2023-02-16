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
  parser.add_argument('-L', '--L1IndexToTest', dest='L1IndexToTest', action='store',
                    help='the L1 being tested')
  parser.add_argument('-s', '--L1LooseOrTightIso', dest='L1LooseOrTightIso', action='store',
                    help='the iso you would like to use (loose or tight)')
  parser.add_argument('-r', '--rateStudy', dest='rateStudy', default="NOTRATE", action='store',
                    help='specify rate study tag (see rateDictionary.py)')
  parser.add_argument('-DJ', '--L1DiJetORCut', dest='L1DiJetOR_35or45', default="35", action='store',
                    help='the cut to use for the jets in the L1DiJetOR, 35 or 45')
  args = parser.parse_args()

  inFile = ROOT.TFile.Open(args.inFilename,"READ")
  tree = inFile.Get("demo/vbf")

  ROOT.TH1.SetDefaultSumw2()

  # L1 and Offline cuts are just integers so we define them outside the event loop
              # pt  mjj  ele pt    
  L1sToTest = [[30, 300, 10], #0, for rate studies
               [30, 500, 10],
               [30, 500, 12],
               [35, 500, 12],
               [40, 500, 12],
               [45, 500, 12],
               [50, 500, 12],
               ]

  match_right_way = True # used for a matching study, left hardcoded assuming the study won't need to be repeated
  L1LooseOrTightIso = (args.L1LooseOrTightIso).lower()

  rateStudyString = args.rateStudy.upper()
  isValidString = (rateStudyString == "2018O" or rateStudyString == "2022E" or rateStudyString == "2022F"\
                or rateStudyString == "2022G_PU70" or rateStudyString == "2022G_PU60")
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

  # read input file name and prepend to output name
  split_inFilename = str(args.inFilename).split('/')
  dataset_inFilename = split_inFilename[-2]
  file_inFilename = split_inFilename[-1].replace('.root','')
  L1DiJetORCut_inFilename = "L1DiJetOR"+str(args.L1DiJetOR_35or45)+"_"

  output_name_part_1 = dataset_inFilename + "_" + file_inFilename + "L1_VBF_DoubleJets" + str(L1JetPtToPass) 
  output_name_part_2 = "_Mass_Min" + str(L1JetMjjToPass) + text_L1_EG + ".root"
  output_name = L1DiJetORCut_inFilename + output_name_part_1 + output_name_part_2
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

  # L1
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

  DiJetOR_35or45 = args.L1DiJetOR_35or45
  if ("35" in DiJetOR_35or45):
    DoubleJetCut = 35
    LeadingL1JetCut = 110
  elif ("45" in DiJetOR_35or45):
    DoubleJetCut = 45
    LeadingL1JetCut = 120 
  else:
    print("Please input 35 or 45 for the DiJetOR cut. Exiting...")
    sys.exit()

  passL1VBFDiJetIsoTau = array('i', [0])
  tree.SetBranchAddress("passhltL1VBFDiJetIsoTau", passL1VBFDiJetIsoTau)
  L1VBFIsoTau_jetPt = ROOT.std.vector('float')()
  L1VBFIsoTau_jetEta = ROOT.std.vector('float')()
  L1VBFIsoTau_jetPhi = ROOT.std.vector('float')()
  L1VBFIsoTau_jetEnergy = ROOT.std.vector('float')()
  tree.SetBranchAddress("hltL1VBFDiJetIsoTau_jetPt", L1VBFIsoTau_jetPt)
  tree.SetBranchAddress("hltL1VBFDiJetIsoTau_jetEta", L1VBFIsoTau_jetEta)
  tree.SetBranchAddress("hltL1VBFDiJetIsoTau_jetPhi", L1VBFIsoTau_jetPhi)
  tree.SetBranchAddress("hltL1VBFDiJetIsoTau_jetEnergy", L1VBFIsoTau_jetEnergy)
  L1VBFIsoTau_tauPt = ROOT.std.vector('float')()
  L1VBFIsoTau_tauEta = ROOT.std.vector('float')()
  L1VBFIsoTau_tauPhi = ROOT.std.vector('float')()
  L1VBFIsoTau_tauEnergy = ROOT.std.vector('float')()
  tree.SetBranchAddress("hltL1VBFDiJetIsoTau_tauPt", L1VBFIsoTau_tauPt)
  tree.SetBranchAddress("hltL1VBFDiJetIsoTau_tauEta", L1VBFIsoTau_tauEta)
  tree.SetBranchAddress("hltL1VBFDiJetIsoTau_tauPhi", L1VBFIsoTau_tauPhi)
  tree.SetBranchAddress("hltL1VBFDiJetIsoTau_tauEnergy", L1VBFIsoTau_tauEnergy)

  passDummyEGORL1 = array('i', [0])
  tree.SetBranchAddress("passhltL1VBFDiJetOR", passL1VBFDiJetOR)
  tree.SetBranchAddress("passHLTDummyEGORL1", passDummyEGORL1)

  TallyL1VBFDiJetEG = 0
  TallyL1VBFDiJetOR = 0
  TallyL1VBFDiJetIsoTau = 0
  TallyDummyEGORL1 = 0

  TallyTripleVBFOR = 0

  TallyL1VBFDiJetORVBFDiTau = 0
  TallyNotL1VBFEG = 0 # any L1 not VBFDiJet
  TallyQuadOR = 0 # all four

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
  
    # HLT Final Decisions
    passEleTauHLT = array('i', [0])
    tree.SetBranchAddress("passEleTauHLT", passEleTauHLT)
    passSingleEleHLT = array('i', [0])
    tree.SetBranchAddress("passSingleEleHLT", passSingleEleHLT)

  # Offline kinems
  #if (not rateStudy):
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

  # the offline cuts are applied to the offline objects
  # they are a flat increase of L1 kinem cuts
  OffJetPtToPass = L1JetPtToPass + 15
  OffJetMjjToPass = L1JetMjjToPass + 100
  OffTauPtToPass = 30 
  OffElePtToPass = L1ElePtToPass + 3 
  OffCuts = [OffJetPtToPass, OffJetMjjToPass, OffElePtToPass, OffTauPtToPass]
  print("Off Cuts: [jets, mjj, elePt, tauPt] ", OffCuts)

  TallyVBFEleOff = 0
  TallyEleTauOff = 0
  TallySingleEleOff = 0
  TallyVBFEleOREleTauOff = 0
  TallyVBFEleORSingleEleOff = 0
  TallyEleTauORSingleEleOff = 0
  TallyTripleOROff = 0
  L1_Tallies = ["","","","","","","","",""]
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
  
        # get L1 objects 
        L1Jets = fillWithTVecs(L1JetPt, L1JetEta, L1JetPhi, L1JetEnergy)
        sizeL1Jets = len(L1Jets)
        L1Eles = fillWithTVecs(L1ElePt, L1EleEta, L1ElePhi, L1EleEnergy)
        sizeL1Eles = len(L1Eles)
  
        BoolPassL1VBFDiJetEG = passL1[0]
        BoolPassL1VBFDiJetIsoTau = passL1VBFDiJetIsoTau[0]
        if (BoolPassL1VBFDiJetIsoTau):
          L1VBFIsoTauTaus = fillWithTVecs(L1VBFIsoTau_tauPt, L1VBFIsoTau_tauEta,\
                                          L1VBFIsoTau_tauPhi, L1VBFIsoTau_tauEnergy)
          L1VBFIsoTauJets = fillWithTVecs(L1VBFIsoTau_jetPt, L1VBFIsoTau_jetEta,\
                                               L1VBFIsoTau_jetPhi, L1VBFIsoTau_jetEnergy)
          L1VBFIsoTauJet1Index, L1VBFIsoTauJet2Index, L1VBFIsoTauMjj = highestMjjPair(L1VBFIsoTauJets)
          L1VBFIsoTauTauPt = L1VBFIsoTauTaus[0].Pt()
          L1VBFIsoTauJet1Pt = L1VBFIsoTauJets[L1VBFIsoTauJet1Index].Pt()
          L1VBFIsoTauJet2Pt = L1VBFIsoTauJets[L1VBFIsoTauJet2Index].Pt()
          
          outL1VBFIsoTau_TauPt[0] = L1VBFIsoTauTauPt
          outL1VBFIsoTau_Jet1Pt[0] = L1VBFIsoTauJet1Pt
          outL1VBFIsoTau_Jet2Pt[0] = L1VBFIsoTauJet2Pt
          outL1VBFIsoTau_Mjj[0] = L1VBFIsoTauMjj

          BoolPassL1VBFDiJetIsoTau = (L1VBFIsoTauTauPt >= 45 and L1VBFIsoTauMjj >= 450 \
                                 and L1VBFIsoTauJet1Pt >= 35 and L1VBFIsoTauJet2Pt >= 35)


        BoolPassDummyEGORL1 = passDummyEGORL1[0]

        # emulated L1 DiJet OR
        BoolPassL1VBFDiJetOR = passL1VBFDiJetOR[0]
        if (BoolPassL1VBFDiJetOR):
          L1VBFDiJetORJets = fillWithTVecs(L1VBFDiJetOR_pt, L1VBFDiJetOR_eta,\
                                           L1VBFDiJetOR_phi, L1VBFDiJetOR_energy)
          L1DiJetORJet1Index, L1DiJetORJet2Index, L1DiJetORMjj = highestMjjPair(L1VBFDiJetORJets)
          outL1DiJetORJet3[0] = -999.
          L1DiJetORJet3PT = -999.
          if (L1DiJetORJet1Index != 0 and L1DiJetORJet2Index != 0):
            L1DiJetORJet3 = L1VBFDiJetORJets[0]
            L1DiJetORJet3PT = L1DiJetORJet3.Pt()
            outL1DiJetORJet3[0] = L1DiJetORJet3PT
            if (L1DiJetORJet3PT < LeadingL1JetCut):
              BoolPassL1VBFDiJetOR = 0
          L1DiJetORJet1 = L1VBFDiJetORJets[L1DiJetORJet1Index]
          L1DiJetORJet2 = L1VBFDiJetORJets[L1DiJetORJet2Index]

          L1DiJetORJet1PT = L1DiJetORJet1.Pt()
          L1DiJetORJet2PT = L1DiJetORJet2.Pt()
          outL1DiJetORJet1[0] = L1DiJetORJet1PT
          outL1DiJetORJet2[0] = L1DiJetORJet2PT
          outL1DiJetORMjj[0] = L1DiJetORMjj

          passing_ = L1DiJetORMjj >= 620 \
                 and ((L1DiJetORJet1PT >= DoubleJetCut and L1DiJetORJet2PT >= DoubleJetCut and L1DiJetORJet3PT >= LeadingL1JetCut)\
                 or (L1DiJetORJet1PT >= LeadingL1JetCut and L1DiJetORJet2PT >= DoubleJetCut and L1DiJetORJet3PT == -999.) )

          BoolPassL1VBFDiJetOR = passing_

  
        outPassL1VBFDiJetEG[0] = BoolPassL1VBFDiJetEG
        outPassL1VBFDiJetOR[0] = BoolPassL1VBFDiJetOR
        outPassL1VBFDiJetIsoTau[0] = BoolPassL1VBFDiJetIsoTau
        outPassDummyEGORL1[0] = BoolPassDummyEGORL1
  
        if (BoolPassL1VBFDiJetEG): TallyL1VBFDiJetEG += 1
        if (BoolPassL1VBFDiJetOR): TallyL1VBFDiJetOR += 1
        if (BoolPassL1VBFDiJetIsoTau): TallyL1VBFDiJetIsoTau += 1
        if (BoolPassDummyEGORL1): TallyDummyEGORL1 += 1
  
        BoolExistingVBFOR = BoolPassL1VBFDiJetOR or BoolPassL1VBFDiJetIsoTau
        if (BoolExistingVBFOR): TallyL1VBFDiJetORVBFDiTau += 1
        if (BoolExistingVBFOR or BoolPassDummyEGORL1): TallyNotL1VBFEG += 1 
        if (BoolExistingVBFOR or BoolPassL1VBFDiJetEG): TallyTripleVBFOR += 1 
        if (BoolExistingVBFOR or BoolPassDummyEGORL1 or BoolPassL1VBFDiJetEG): TallyQuadOR += 1

        L1_Tallies = [TallyL1VBFDiJetEG, TallyL1VBFDiJetOR, TallyL1VBFDiJetIsoTau, TallyDummyEGORL1,\
                      TallyL1VBFDiJetORVBFDiTau, TallyNotL1VBFEG, TallyTripleVBFOR, TallyQuadOR, \
                      TallyQuadOR - TallyNotL1VBFEG]

        if (BoolPassL1VBFDiJetEG and not BoolExistingVBFOR and not BoolPassDummyEGORL1): 
          print(f"{runNumberValue}:{lumiSectionValue}:{eventID[0]}")
  
        # if objects available, set and fill branches
        if (sizeL1Jets >= 2 and sizeL1Eles >= 1 and passL1[0]):
          L1Ele = L1Eles[0]
          L1Jet1Index, L1Jet2Index, L1Mjj = highestMjjPair(L1Jets)
          L1Jet1 = L1Jets[L1Jet1Index]
          L1Jet2 = L1Jets[L1Jet2Index]
  
          outL1ElePt[0] = L1Ele.Pt()
          outL1Jet1Pt[0] = L1Jet1.Pt()
          outL1Jet2Pt[0] = L1Jet2.Pt()
          outL1Mjj[0] = L1Mjj
  
          #print(sizeL1Jets, sizeL1Eles, L1Ele.Pt(), L1Jet1.Pt(), L1Jet2.Pt(), L1Mjj)
        else:
          outL1ElePt[0] = -999
          outL1Jet1Pt[0] = -999
          outL1Jet2Pt[0] = -999
          outL1Mjj[0] = -999
        
        outtree.Fill()
  
        continue

  
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

      # require a high pt iso ele to emulate the lowest L1 with PS != 0 for this HLT path
      passL1IsoElePresent = L1Ele.Pt() >= 30
      passSingleEleOffCuts = (passL1IsoElePresent and passEleTauOffCuts and OffEle.Pt() >= 33)

      # now tally it up
      GoodVBFEle = matchL1Off and passVBFEleL1Restrictions and passVBFEleOffCuts
      GoodEleTau = passEleTauHLTOffMatching and passEleTauOffCuts and passEleTauHLT[0]
      GoodSingleEle = passSingleEleHLTOffMatching and passSingleEleOffCuts and passSingleEleHLT[0]

      outPassVBFEleTauOff[0] = GoodVBFEle
      outPassEleTauOff[0] = GoodEleTau
      outPassSingleEleOff[0] = GoodSingleEle

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

