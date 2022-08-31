import ROOT
from array import array
import sys
import argparse

ROOT.gROOT.SetBatch(True) # sets visual display off (i.e. no graphs/TCanvas)

# usage: python3 checkBranchEntires.py -i ../../samples/VBFE_wMuTauFilters.root -b MuTauForDiTauFinalFilterOverlap
# intended to be a quick check that events pass a new hlt filter 
# once it is added to NtupleMaker_hltFilters.cc and tested with onlyMCConf.py

if __name__ == "__main__": 

  parser = argparse.ArgumentParser(description='Open a .root file') 
  parser.add_argument('-i', '--inputRootFile', dest='inFilename', action='store', 
                    help='the input .root file\'s name') 
  parser.add_argument('-b', '--branch', dest='branch', action='store',
                    help='the branch name you\'d like to check')
  args = parser.parse_args() 

  inFile = ROOT.TFile.Open(args.inFilename,"READ") 
  tree = inFile.Get("demo/vbf") 

  # ^^^^ Open a ROOT file
  # vvvv Count Events for 5 generic branch names

  branchBase = args.branch
  branchAdditions = ["pass", "pt", "eta", "phi", "energy"]
  branchesToCheck = []
  for word in branchAdditions:
    if word == "pass":
      branchesToCheck.append(word + branchBase)
    else:
      branchesToCheck.append(branchBase + "_" + word)

  PassBranch = tree.Draw("nEvents", branchesToCheck[0] + " >0", "goff")
  PtBranch = tree.Draw("nEvents", branchesToCheck[1] + " >0", "goff")
  EtaBranch = tree.Draw("nEvents", branchesToCheck[2] + " >0 || " + branchesToCheck[2] + " <0", "goff")
  PhiBranch = tree.Draw("nEvents", branchesToCheck[3] + " >0 || " + branchesToCheck[3] + " <0", "goff")
  EnergyBranch = tree.Draw("nEvents", branchesToCheck[4] + " >0", "goff")

  Counters = [PassBranch, PtBranch, EtaBranch, PhiBranch, EnergyBranch]
  for i in range(len(Counters)):
    print("Events in branch {}: {}".format(branchesToCheck[i], Counters[i]))

