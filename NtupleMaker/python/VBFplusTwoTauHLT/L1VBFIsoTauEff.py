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
# for line in `cat rate_files.txt`; do echo $line; python3 L1VBFIsoTauEff.py -i $line -r 2022G_PU60 -DT 34 -DJ 35 >> rate_total_output.txt; done

if __name__ == "__main__":

  parser = argparse.ArgumentParser(description='Open a .root file')
  parser.add_argument('-i', '--inputRootFile', dest='inFilename', action='store',
                    help='the input .root file\'s name')
  parser.add_argument('-L', '--L1IndexToTest', dest='L1IndexToTest', action='store',
                    help='the L1 being tested')
  parser.add_argument('-r', '--rateStudy', dest='rateStudy', action='store',
                    help='is this a rate study (yes or no)')
  parser.add_argument('-DT', '--L1DiTauCut', dest='L1DiTauCut', default=34, action='store',
                    help='set the L1DiTauCut (default 34 for Runs after Era E)')
  parser.add_argument('-DJ', '--L1DiJetORCut', dest='L1DiJetOR_35or45', action='store',
                    help='the cut to use for the jets in the L1DiJetOR, 35 or 45')
  args = parser.parse_args()

  inFile = ROOT.TFile.Open(args.inFilename,"READ")
  tree = inFile.Get("demo/vbf")

  ROOT.TH1.SetDefaultSumw2()

  # L1_DoubleJet35_Mass_Min450_IsoTau45er2p1_RmOvlp_dR0p5

  # L1 and Offline cuts are just integers so we define them outside the event loop
              # pt  mjj  ele pt    
  L1sToTest = [[35, 450, 45], #0, for rate studies
               [40, 450, 45],
               [45, 450, 45],
               [50, 450, 45],
               ]

  match_right_way = True # used for a matching study, left hardcoded assuming the study won't need to be repeated

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
  print("L1 Cuts: [jets, mjj, isoTauPt] ", L1Cuts)
  L1JetPtToPass =  L1Cuts[0]
  L1JetMjjToPass = L1Cuts[1]
  L1IsoTauPtToPass =  L1Cuts[2]

  text_L1_IsoTau = "_IsoTau" + str(L1IsoTauPtToPass)

  # read input file name and prepend to output name
  split_inFilename = str(args.inFilename).split('/')
  dataset_inFilename = split_inFilename[-2]
  file_inFilename = split_inFilename[-1].replace('.root','')
  L1DiTauCut_inFilename = "L1DiTau"+str(args.L1DiTauCut)+"_"
  L1DiJetORCut_inFilename = "L1DiJetOR"+str(args.L1DiJetOR_35or45)+"_"

  output_name_part_0 = L1DiTauCut_inFilename + L1DiJetORCut_inFilename
  output_name_part_1 = dataset_inFilename + "_" + file_inFilename + "L1_VBF_DoubleJets" + str(L1JetPtToPass) 
  output_name_part_2 = "_Mass_Min" + str(L1JetMjjToPass) + text_L1_IsoTau + ".root"
  output_name = output_name_part_0 + output_name_part_1 + output_name_part_2
  print(f"Total counts for {output_name}")

  # declare outtree name and branches
  outFile = ROOT.TFile.Open(output_name, "RECREATE")
  outtree = ROOT.TTree("outtree", "skimmed event data")

  outL1IsoTauPt = array('f', [0.])
  outL1Jet1Pt = array('f', [0.])
  outL1Jet2Pt = array('f', [0.])
  outL1Mjj = array('f', [0.])
  outtree.Branch("L1IsoTauPt", outL1IsoTauPt, 'pt/F')
  outtree.Branch("L1Jet1Pt", outL1Jet1Pt, 'pt/F')
  outtree.Branch("L1Jet2Pt", outL1Jet2Pt, 'pt/F')
  outtree.Branch("L1Mjj", outL1Mjj, 'mjj/F')

  outPassL1VBFDiJetEG = array('i', [0])
  outPassL1VBFDiJetOR = array('i', [0])
  outPassL1VBFDiJetIsoTau = array('i', [0])
  outPassDummyEGORL1 = array('i', [0])
  outPassL1DiTau = array('i', [0])
  outtree.Branch("passL1VBFDiJetEG", outPassL1VBFDiJetEG, 'pass/I')
  outtree.Branch("passL1VBFDiJetOR", outPassL1VBFDiJetOR, 'pass/I')
  outtree.Branch("passL1VBFDiJetIsoTau", outPassL1VBFDiJetIsoTau, 'pass/I')
  outtree.Branch("passDummyEGORL1", outPassDummyEGORL1, 'pass/I')
  outtree.Branch("passL1DiTau", outPassL1DiTau, 'pass/I')

  outPassVBFDiTauHLT = array('i', [0])
  outPassInclusiveVBFHLT = array('i', [0])
  outPassDiTauHLT = array('i', [0])
  outtree.Branch("passVBFDitauHLT", outPassVBFDiTauHLT, 'pass/I')
  outtree.Branch("passInclusiveVBFHLT", outPassInclusiveVBFHLT, 'pass/I')
  outtree.Branch("passDiTauHLT", outPassDiTauHLT, 'pass/I')

  outOffElePt = array('f', [0.])
  outOffTau1Pt = array('f', [0.])
  outOffTau2Pt = array('f', [0.])
  outOffJet1Pt = array('f', [0.])
  outOffJet2Pt = array('f', [0.])
  outOffMjj = array('f', [0.])
  outtree.Branch("OffElePt", outOffElePt, 'pt/F')
  outtree.Branch("OffTau1Pt", outOffTau1Pt, 'pt/F')
  outtree.Branch("OffTau2Pt", outOffTau2Pt, 'pt/F')
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
  tree.SetBranchAddress("runNumber", runNumber)
  tree.SetBranchAddress("lumiBlock", lumiSection)
  viableEventCounter = 0

  goodRunNumber = rateDictionary[rateStudyString]["runNumber"]
  minLS = rateDictionary[rateStudyString]["minLS"]
  maxLS = rateDictionary[rateStudyString]["maxLS"]
  print(f"Looking at run = {goodRunNumber}, LS Range [{minLS}, {maxLS}]")

  # L1
  passL1VBFDiJetIsoTau = array('i', [0])
  tree.SetBranchAddress("passhltL1VBFDiJetIsoTau", passL1VBFDiJetIsoTau)
  L1JetPt = ROOT.std.vector('float')()
  L1JetEta = ROOT.std.vector('float')()
  L1JetPhi = ROOT.std.vector('float')()
  L1JetEnergy = ROOT.std.vector('float')()
  tree.SetBranchAddress("hltL1VBFDiJetIsoTau_jetPt", L1JetPt)
  tree.SetBranchAddress("hltL1VBFDiJetIsoTau_jetEta", L1JetEta)
  tree.SetBranchAddress("hltL1VBFDiJetIsoTau_jetPhi", L1JetPhi)
  tree.SetBranchAddress("hltL1VBFDiJetIsoTau_jetEnergy", L1JetEnergy)
  L1IsoTauPt = ROOT.std.vector('float')()
  L1IsoTauEta = ROOT.std.vector('float')()
  L1IsoTauPhi = ROOT.std.vector('float')()
  L1IsoTauEnergy = ROOT.std.vector('float')()
  tree.SetBranchAddress("hltL1VBFDiJetIsoTau_tauPt", L1IsoTauPt)
  tree.SetBranchAddress("hltL1VBFDiJetIsoTau_tauEta", L1IsoTauEta)
  tree.SetBranchAddress("hltL1VBFDiJetIsoTau_tauPhi", L1IsoTauPhi)
  tree.SetBranchAddress("hltL1VBFDiJetIsoTau_tauEnergy", L1IsoTauEnergy)


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
    ThirdJetCut = 110
  elif ("45" in DiJetOR_35or45):
    DoubleJetCut = 45
    ThirdJetCut = 120
  else:
    print("Please input 35 or 45 for the DiJetOR cut. Exiting...")
    sys.exit() 

  passDummyEGORL1 = array('i', [0])
  tree.SetBranchAddress("passHLTDummyEGORL1", passDummyEGORL1)

  passL1DiTau = array('i', [0])
  tree.SetBranchAddress("passhltL1sDoubleTauBigOR", passL1DiTau)
  L1DiTau_pt = ROOT.std.vector('float')()
  tree.SetBranchAddress("hltL1sDoubleTauBigOR_pt", L1DiTau_pt)
  L1DiTauCut = float(args.L1DiTauCut)

  TallyL1VBFDiJetEG = 0
  TallyL1VBFDiJetOR = 0
  TallyL1VBFDiJetIsoTau = 0
  TallyDummyEGORL1 = 0
  TallyL1DiTau = 0

  TallyL1VBFDiJetIncORIsoTau = 0
  TallyL1VBFDiJetIncORDiTau = 0
  TallyL1DiTauORIsoTau = 0
  #TallyL1VBFEGORIsoTau = 0 # dunno, not as important here as they are in the scan
  TallyL1VBFDiJetIsoTauANDDummyEGOR = 0 # check contamination
  TallyNotL1VBFDiJetIsoTau = 0 # any L1 not VBFDiJetIsoTau, excluding EG seeds, use for VBFEG later
  TallyTripleOR = 0 # DiTau, VBF Inc, OR VBFIsotau

  is2022 = False
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

  # DiJetIsoTau HLT
  passVBFDiTauHLT = array('i', [0])
  tree.SetBranchAddress("passVBF2DTHLT", passVBFDiTauHLT)
  VBFDiTauFinalJetFilter_pt = ROOT.std.vector('float')()
  VBFDiTauFinalJetFilter_eta = ROOT.std.vector('float')()
  VBFDiTauFinalJetFilter_phi = ROOT.std.vector('float')()
  VBFDiTauFinalJetFilter_energy = ROOT.std.vector('float')()
  tree.SetBranchAddress("VBF2DTDoubleJetFinalFilter_pt", VBFDiTauFinalJetFilter_pt)
  tree.SetBranchAddress("VBF2DTDoubleJetFinalFilter_eta", VBFDiTauFinalJetFilter_eta)
  tree.SetBranchAddress("VBF2DTDoubleJetFinalFilter_phi", VBFDiTauFinalJetFilter_phi) 
  tree.SetBranchAddress("VBF2DTDoubleJetFinalFilter_energy", VBFDiTauFinalJetFilter_energy)
  VBFDiTauFinalTauFilter_pt = ROOT.std.vector('float')()
  VBFDiTauFinalTauFilter_eta = ROOT.std.vector('float')()
  VBFDiTauFinalTauFilter_phi = ROOT.std.vector('float')()
  VBFDiTauFinalTauFilter_energy = ROOT.std.vector('float')()
  tree.SetBranchAddress("VBF2DTDoubleTauFinalFilter_pt", VBFDiTauFinalTauFilter_pt)
  tree.SetBranchAddress("VBF2DTDoubleTauFinalFilter_eta", VBFDiTauFinalTauFilter_eta)
  tree.SetBranchAddress("VBF2DTDoubleTauFinalFilter_phi", VBFDiTauFinalTauFilter_phi)
  tree.SetBranchAddress("VBF2DTDoubleTauFinalFilter_energy", VBFDiTauFinalTauFilter_energy)

  # shouldn't be important, but here are the filter names for the seeded L1 tau
  #VBF2DTL1MatchedTauFinalFilter_pt
  #VBF2DTL1MatchedTauFinalFilter_eta
  #VBF2DTL1MatchedTauFinalFilter_phi
  #VBF2DTL1MatchedTauFinalFilter_energy
  
  # DiJetInc HLT
  passInclusiveVBFHLT = array('i', [0])
  tree.SetBranchAddress("passDeepInclusiveVBFHLT", passInclusiveVBFHLT)

  # DiTau HLT
  passDiTauHLT = array('i', [0])
  tree.SetBranchAddress("passDeepDiTau35HLT", passDiTauHLT)
  DiTauFinalFilter_pt = ROOT.std.vector('float')()
  DiTauFinalFilter_eta = ROOT.std.vector('float')()
  DiTauFinalFilter_phi = ROOT.std.vector('float')()
  DiTauFinalFilter_energy = ROOT.std.vector('float')()
  tree.SetBranchAddress("DiTauFinalFilter_pt", DiTauFinalFilter_pt)
  tree.SetBranchAddress("DiTauFinalFilter_eta", DiTauFinalFilter_eta)
  tree.SetBranchAddress("DiTauFinalFilter_phi", DiTauFinalFilter_phi)
  tree.SetBranchAddress("DiTauFinalFilter_energy", DiTauFinalFilter_energy)


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

  # the offline cuts are applied to the offline objects
  # they are a flat increase of L1 kinem cuts
  #OffJetPtToPass = L1JetPtToPass + 15
  #OffJetMjjToPass = L1JetMjjToPass + 100
  #OffTau1PtToPass = L1IsoTauPtToPass + 30 #path already has an HLT, should design to that, not the L1
  #OffTau2PtToPass = L1IsoTauPtToPass + 30 

  #TODO check these values
  OffJetPtToPass = 50
  OffJetMjjToPass = 600
  OffTau1PtToPass = 45 
  OffTau2PtToPass = 25
  OffCuts = [OffJetPtToPass, OffJetMjjToPass, OffTau1PtToPass, OffTau2PtToPass]
  print("Off Cuts: [jets, mjj, Tau1Pt, Tau2Pt] ", OffCuts)

  #TallyVBFEleHLT = 0
  #TallyEleTauHLT = 0
  #TallySingleEleHLT = 0
  #TallyEleTauHLTAndSingleEleHLT = 0
  #TallyEleTauHLTOrSingleEleHLT = 0

  TallyVBFDiTauHLT = 0
  TallyInclusiveVBFHLT = 0
  TallyDiTauHLT = 0
  TallyVBFDiTauORInclusiveVBFHLT = 0
  TallyVBFDiTauORDiTauHLT = 0
  TallyInclusiveVBFORDiTauHLT = 0
  TallyTripleORHLT = 0

  TotalEntries = tree.GetEntries()
  for entry in range(TotalEntries):
    tree.GetEntry(entry)

    if (rateStudy):
      # for rate study
      runNumberValue = runNumber[0]
      if runNumberValue != goodRunNumber: continue
  
      lumiSectionValue = lumiSection[0]
      goodLumi = lumiSectionValue >= minLS and lumiSectionValue <= maxLS
      if not goodLumi: continue
  
      if (runNumberValue == goodRunNumber and goodLumi):
        viableEventCounter += 1
  
        # get L1 objects 
        L1Jets = fillWithTVecs(L1JetPt, L1JetEta, L1JetPhi, L1JetEnergy)
        sizeL1Jets = len(L1Jets)
        L1IsoTaus = fillWithTVecs(L1IsoTauPt, L1IsoTauEta, L1IsoTauPhi, L1IsoTauEnergy)
        sizeL1IsoTaus = len(L1IsoTaus)
  
        BoolPassL1VBFDiJetIsoTau = passL1VBFDiJetIsoTau[0]
        BoolPassDummyEGORL1 = passDummyEGORL1[0]

        # emulated L1 DiJet OR
        BoolPassL1VBFDiJetOR = passL1VBFDiJetOR[0]
        if (BoolPassL1VBFDiJetOR):
          L1VBFDiJetORJets = fillWithTVecs(L1VBFDiJetOR_pt, L1VBFDiJetOR_eta,\
                                           L1VBFDiJetOR_phi, L1VBFDiJetOR_energy)
          L1DiJetORJet1Index, L1DiJetORJet2Index, L1DiJetORMjj = highestMjjPair(L1VBFDiJetORJets)
          if (L1DiJetORJet1Index != 0 and L1DiJetORJet2Index != 0):
            L1DiJetORJet3 = L1VBFDiJetORJets[0]
            if (L1DiJetORJet3.Pt() < ThirdJetCut):
              BoolPassL1VBFDiJetOR = 0
          L1DiJetORJet1 = L1VBFDiJetORJets[L1DiJetORJet1Index] 
          L1DiJetORJet2 = L1VBFDiJetORJets[L1DiJetORJet2Index] 
          if (L1DiJetORJet1.Pt() < DoubleJetCut or L1DiJetORJet2.Pt() < DoubleJetCut):# or L1DiJetORMjj < 620)
            BoolPassL1VBFDiJetOR = 0

        # emulated L1 DiTau
        BoolPassL1DiTau = passL1DiTau[0]
        if (BoolPassL1DiTau and runNumberValue >= 360486):
          if (L1DiTau_pt[0] < L1DiTauCut or L1DiTau_pt[1] < L1DiTauCut):
            BoolPassL1DiTau = 0
  
        outPassL1VBFDiJetIsoTau[0] = BoolPassL1VBFDiJetIsoTau
        outPassL1VBFDiJetOR[0] = BoolPassL1VBFDiJetOR
        outPassDummyEGORL1[0] = BoolPassDummyEGORL1
        outPassL1DiTau[0] = BoolPassL1DiTau
        # TODO, try 32, 34, 35, 36 cases of DiTau L1
  
        if (BoolPassL1VBFDiJetIsoTau): TallyL1VBFDiJetIsoTau += 1
        if (BoolPassL1VBFDiJetOR): TallyL1VBFDiJetOR += 1
        if (BoolPassDummyEGORL1): TallyDummyEGORL1 += 1
        if (BoolPassL1DiTau): TallyL1DiTau += 1
  
        if (BoolPassL1VBFDiJetOR or BoolPassL1VBFDiJetIsoTau): TallyL1VBFDiJetIncORIsoTau += 1
        if (BoolPassL1VBFDiJetOR or BoolPassL1DiTau): TallyL1VBFDiJetIncORDiTau += 1
        if (BoolPassL1VBFDiJetIsoTau or BoolPassL1DiTau): TallyL1DiTauORIsoTau += 1

        if (BoolPassL1VBFDiJetIsoTau and BoolPassDummyEGORL1): TallyL1VBFDiJetIsoTauANDDummyEGOR += 1
        if (BoolPassL1VBFDiJetOR or BoolPassL1VBFDiJetIsoTau or BoolPassL1DiTau): TallyTripleOR += 1
  
        # if objects available, set and fill branches
        if (sizeL1Jets >= 2 and sizeL1IsoTaus >= 1 and BoolPassL1VBFDiJetIsoTau):
          L1IsoTau = L1IsoTaus[0]
          L1Jet1Index, L1Jet2Index, L1Mjj = highestMjjPair(L1Jets)
          L1Jet1 = L1Jets[L1Jet1Index]
          L1Jet2 = L1Jets[L1Jet2Index]
  
          outL1IsoTauPt[0] = L1IsoTau.Pt()
          outL1Jet1Pt[0] = L1Jet1.Pt()
          outL1Jet2Pt[0] = L1Jet2.Pt()
          outL1Mjj[0] = L1Mjj
  
          #print(sizeL1Jets, sizeL1IsoTaus, L1IsoTau.Pt(), L1Jet1.Pt(), L1Jet2.Pt(), L1Mjj)
        else:
          outL1IsoTauPt[0] = -999
          outL1Jet1Pt[0] = -999
          outL1Jet2Pt[0] = -999
          outL1Mjj[0] = -999
        
        # after L1 do HLT
        # for each Bool, and with pass artificial L1 when enabled..
        BoolPassVBFDiTauHLT = passVBFDiTauHLT[0] and BoolPassL1VBFDiJetIsoTau
        BoolPassInclusiveVBFHLT = passInclusiveVBFHLT[0] and BoolPassL1VBFDiJetOR
        BoolPassDiTauHLT = passDiTauHLT[0] and BoolPassL1DiTau

        outPassVBFDiTauHLT[0] = BoolPassVBFDiTauHLT
        outPassInclusiveVBFHLT[0] = BoolPassInclusiveVBFHLT
        outPassDiTauHLT[0] = BoolPassDiTauHLT

        if (BoolPassVBFDiTauHLT): TallyVBFDiTauHLT += 1
        if (BoolPassInclusiveVBFHLT): TallyInclusiveVBFHLT += 1
        if (BoolPassDiTauHLT): TallyDiTauHLT += 1

        if (BoolPassVBFDiTauHLT or BoolPassInclusiveVBFHLT): TallyVBFDiTauORInclusiveVBFHLT += 1
        if (BoolPassVBFDiTauHLT or BoolPassDiTauHLT): TallyVBFDiTauORDiTauHLT += 1
        if (BoolPassInclusiveVBFHLT or BoolPassDiTauHLT): TallyInclusiveVBFORDiTauHLT += 1

        if (BoolPassVBFDiTauHLT or BoolPassInclusiveVBFHLT or BoolPassDiTauHLT): TallyTripleORHLT += 1

        outtree.Fill()
  
        continue

    # requiring events to pass your L1 biases your selection, fine for gain study, not fine for eff study
    #basicReqs = ((passL1[0]) and (OffnJets[0] >= 2) and (OffnEles[0] >= 1) and (OffnTaus[0] >= 1))
    basicReqs = ( not rateStudy and (OffnJets[0] >= 2) and (OffnTaus[0] >= 2))

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
      if (sizeOffTaus < 2): continue

      # remove any jets from container that is overlapped with leading or subleading tau 
      OffJets = [OffJets[i] for i in range(sizeOffJets) if ROOT.TLorentzVector.DeltaR(OffTaus[0], OffJets[i]) >= 0.5]
      OffJets = [OffJets[i] for i in range(sizeOffJets) if ROOT.TLorentzVector.DeltaR(OffTaus[1], OffJets[i]) >= 0.5]
      sizeOffJets = len(OffJets)
      if (sizeOffJets < 2): continue
 
      # skip the event if both taus have the same charge
      if (OffTauCh[OffTausPassFilter[0]] == OffTauCh[OffTausPassFilter[1]]):
        continue

      # assign Offline objects
      OffTau1 = OffTaus[0] # consider selecting tau based on isolation, not pt
      OffTau2 = OffTaus[1]
      OffJet1Index, OffJet2Index, OffMjj = highestMjjPair(OffJets)
      OffJet1 = OffJets[OffJet1Index]
      OffJet2 = OffJets[OffJet2Index]
      if (ROOT.TLorentzVector.DeltaR(OffJet1, OffJet2) < 0.5): continue

      # get L1 objects 
      L1Jets = fillWithTVecs(L1JetPt, L1JetEta, L1JetPhi, L1JetEnergy)
      sizeL1Jets = len(L1Jets)
      L1IsoTaus = fillWithTVecs(L1IsoTauPt, L1IsoTauEta, L1IsoTauPhi, L1IsoTauEnergy)
      sizeL1IsoTaus = len(L1IsoTaus)

      # check L1 object sizes before matching
      matchL1Off = False
      tryToMatch = False
      if (sizeL1Jets >= 2 and sizeL1IsoTaus >= 1): tryToMatch = True 
      if (tryToMatch == True):
        L1IsoTau = L1IsoTaus[0]
        L1Jet1Index, L1Jet2Index, L1Mjj = highestMjjPair(L1Jets)
        L1Jet1 = L1Jets[L1Jet1Index]
        L1Jet2 = L1Jets[L1Jet2Index]

      # switch to match the right way (from Offline to L1) or wrong way (from L1 to Offline)
      if (match_right_way == False):
        matchL1Off = match_L1_to_Offline(L1Ele, L1Jet1, L1Jet2, OffEle, OffJet1, OffJet2)
      else:
        matchL1Off, L1Indices = match_Offline_to_L1(L1Eles, L1Jets, OffEle, OffJet1, OffJet2)

      reassignL1 = True
      if (matchL1Off == True and reassignL1 == True and match_right_way == True):
        L1IsoTau  = L1IsoTaus[L1Indices[0]]
        L1Jet1 = L1Jets[L1Indices[1]]
        L1Jet2 = L1Jets[L1Indices[2]]
        L1Mjj = (L1Jet1 + L1Jet2).M()

      # writing branch info

      outMatchL1Off[0] = matchL1Off

      if (tryToMatch == True): # only possible to fill L1s if they are available and matching was attempted
        outL1IsoTauPt[0] = L1IsoTau.Pt()
        outL1Jet1Pt[0] = L1Jet1.Pt()
        outL1Jet2Pt[0] = L1Jet2.Pt()
        outL1Mjj[0] = L1Mjj

      outOffTau1Pt[0] = OffTau1.Pt()
      outOffTau2Pt[0] = OffTau2.Pt()
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

      passVBFIsoTauL1Restrictions = False
      if (matchL1Off):
        if (L1Jet1.Pt()  >= L1JetPtToPass 
         and L1Jet2.Pt() >= L1JetPtToPass 
         and L1Mjj       >= L1JetMjjToPass 
         and L1Ele.Pt()  >= L1IsoTauPtToPass): passVBFIsoTauL1Restrictions = True

      passVBFIsoTauOffCuts = False
      if (OffJet1.Pt()  >= OffJetPtToPass
       and OffJet2.Pt() >= OffJetPtToPass
       and OffMjj       >= OffJetMjjToPass
       and OffTau1.Pt()  >= OffTau1PtToPass
       and OffTau2.Pt()  >= OffTau2PtToPass): passVBFEleOffCuts = True

      # now tally it up
      GoodVBFIsoTau = matchL1Off and passVBFIsoTauL1Restrictions and passVBFIsoTauOffCuts
      GoodEleTau = passEleTauHLTOffMatching and passEleTauOffCuts and passEleTauHLT
      GoodSingleEle = passSingleEleHLTOffMatching and passSingleEleOffCuts and passSingleEleHLT

      # enough to calculate impact of VBF Ele, EleTau and SingleEle will be main overlap at analysis
      if (GoodVBFEle): TallyVBFEleHLT += 1
      if (GoodEleTau): TallyEleTauHLT += 1
      if (GoodSingleEle): TallySingleEleHLT += 1

      if (GoodEleTau or GoodSingleEle): TallyEleTauHLTOrSingleEle += 1
      if (GoodEleTau and GoodSingleEle): TallyEleTauHLTAndSingleEle += 1

      if (GoodVBFEle or GoodEleTau or GoodSingleEle): TallyTripleORHLT += 1

  # print output
  print("\033[42m" + f"nViableEvents: {viableEventCounter}" + "\033[0m")

  if (rateStudy):
    # L1 Single Counts
    print("-------------L1!---------------")
    labels_single = ["VBF+IsoTau", "VBF Inc", "DiTau", "L1 EGs"] 
    values = [TallyL1VBFDiJetIsoTau, TallyL1VBFDiJetOR, TallyL1DiTau, TallyDummyEGORL1]
    print_formatted_labels_and_values(labels_single, values)

    # L1 ORs and Unique
    labels_OR = ["VBF Inc OR IsoTau", "VBF Inc OR DiTau", "VBF Iso Tau OR DiTau", "TripleOR", "Unique IsoTau"]
    uniqueL1VBFIsoTau = TallyTripleOR - TallyL1VBFDiJetIncORDiTau
    values = [TallyL1VBFDiJetIncORIsoTau, TallyL1VBFDiJetIncORDiTau, TallyL1DiTauORIsoTau, TallyTripleOR, uniqueL1VBFIsoTau]
    print_formatted_labels_and_values(labels_OR, values, double_space=True, five_values=True)
    print("-----")
    print("L1VBFDiJetIsoTau AND L1 EGs (not including VBF Ele)", TallyL1VBFDiJetIsoTauANDDummyEGOR)

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
      print(f"UNpure rate = {rate_factor * TallyL1VBFDiJetIsoTau},  PURE rate = {rate_factor * uniqueL1VBFIsoTau}")

    # HLT Single Counts
    print("-------------HLT!---------------")
    values = [TallyVBFDiTauHLT, TallyInclusiveVBFHLT, TallyDiTauHLT, -999]
    print_formatted_labels_and_values(labels_single, values) 
    # HLT ORs and Unique
    uniqueVBFDiTauHLT = TallyTripleORHLT - TallyInclusiveVBFORDiTauHLT
    values = [TallyVBFDiTauORInclusiveVBFHLT, TallyInclusiveVBFORDiTauHLT, TallyVBFDiTauORDiTauHLT, \
              TallyTripleORHLT, uniqueVBFDiTauHLT]

  if (notRateStudy):
    print(f"match right way (Offline to L1): {match_right_way}")

    # formatting a table to print instead of free-form printing
    labels = ["SingleEle", "EleTau", "OR", "AND"]
    values = [TallySingleEleHLT, TallyEleTauHLT, TallyEleTauHLTOrSingleEle, TallyEleTauHLTAndSingleEle]
    print_formatted_labels_and_values(labels, values)

    UniqueVBF = TallyTripleORHLT - TallyEleTauHLTOrSingleEle
    if (TallyEleTauHLTOrSingleEle != 0):
      Gain = ( (TallyTripleORHLT / TallyEleTauHLTOrSingleEle) - 1)*100
    else:
      Gain = -999
    labels = ["VBF+Ele", "TripleOR", "Unique", "Gain"]
    values = [TallyVBFEleHLT, TallyTripleORHLT, UniqueVBF, Gain]
    print_formatted_labels_and_values(labels, values)

  outtree.Write()
  outFile.Close()

