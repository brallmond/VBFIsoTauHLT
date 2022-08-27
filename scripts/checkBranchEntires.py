import ROOT
from array import array
import sys
import argparse

ROOT.gROOT.SetBatch(True) # sets visual display off (i.e. no graphs/TCanvas)

if __name__ == "__main__": 

  parser = argparse.ArgumentParser(description='Open a .root file') 
  parser.add_argument('-i', '--inputRootFile', dest='inFilename', action='store', 
                    help='the input .root file\'s name') 
  parser.add_argument('-b', '--branch', dest='branch', action='store',
                    help='the branch name you\'d like to check')
  args = parser.parse_args() 

  inFile = ROOT.TFile.Open(args.inFilename,"READ") 
  tree = inFile.Get("demo/vbf") 

  branchBase = args.branch
  branchAdditions = ["pass", "pt", "eta", "phi", "energy"]
  branchesToCheck = []
  for word in branchAdditions:
    if word == "pass":
      branchesToCheck.append(word + branchBase)
    else:
      branchesToCheck.append(branchBase + "_" + word)

  PassBranch = array('i', [0])
  tree.SetBranchAddress(branchesToCheck[0], PassBranch)
  PtBranch = ROOT.std.vector('float')()
  tree.SetBranchAddress(branchesToCheck[1], PtBranch)
  EtaBranch = ROOT.std.vector('float')()
  tree.SetBranchAddress(branchesToCheck[2], EtaBranch)
  PhiBranch = ROOT.std.vector('float')()
  tree.SetBranchAddress(branchesToCheck[3], PhiBranch)
  EnergyBranch = ROOT.std.vector('float')()
  tree.SetBranchAddress(branchesToCheck[4], EnergyBranch)

  PassBranchCounter = 0
  PtBranchCounter = 0
  EtaBranchCounter = 0
  PhiBranchCounter = 0
  EnergyBranchCounter = 0

  for entry in range(tree.GetEntries()):
    tree.GetEntry(entry) 

    PassBranchCounter += len([i for i in range(len(PassBranch)) if PassBranch[i] > 0])
    PtBranchCounter += len([i for i in range(len(PtBranch)) if PtBranch[i] > 0])
    EtaBranchCounter += len([i for i in range(len(EtaBranch)) if abs(EtaBranch[i]) > 0])
    PhiBranchCounter += len([i for i in range(len(PhiBranch)) if abs(PhiBranch[i]) > 0])
    EnergyBranchCounter += len([i for i in range(len(EnergyBranch)) if EnergyBranch[i] > 0])

  Counters = [PassBranchCounter, PtBranchCounter, EtaBranchCounter, PhiBranchCounter, EnergyBranchCounter]
  for i in range(len(Counters)):
    print("{} {}".format(branchesToCheck[i], Counters[i]))
