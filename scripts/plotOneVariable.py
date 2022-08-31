import ROOT
from array import array
import sys
import argparse
import numpy as np
import matplotlib.pyplot as plt


ROOT.gROOT.SetBatch(True) # sets visual display off (i.e. no graphs/TCanvas)

# usage: python3 plotOneVariable.py -i ../../samples/VBFE_wMuTauFilters.root -b tauPt
# plots one branch variable (vectors only) in a simple matplot histogram 

# followup: make into a root version https://nyx.physics.mcgill.ca/event/264/contributions/1491/attachments/346/488/slides.pdf

if __name__ == "__main__": 

  parser = argparse.ArgumentParser(description='Open a .root file') 
  parser.add_argument('-i', '--inputRootFile', dest='inFilename', action='store', 
                    help='the input .root file\'s name') 
  parser.add_argument('-b', '--branch', dest='branch', action='store',
                    help='the branch name you\'d like to check')
  args = parser.parse_args() 

  inFile = ROOT.TFile.Open(args.inFilename,"READ") 
  tree = inFile.Get("demo/vbf") 

  PtBranch = ROOT.std.vector('float')()
  tree.SetBranchAddress(args.branch, PtBranch)

  PtBranchCounter = 0


  PtBranchScanRange = np.linspace(0.,200.,20)
  PtBranchData = []

  #for entry in range(tree.GetEntries()):
  for entry in range(2000):
    tree.GetEntry(entry) 

    PtBranchCounter += len([i for i in range(len(PtBranch)) if PtBranch[i] > 0])
    for i in range(PtBranch.size()):
      PtBranchData.append(PtBranch[i])


  # https://matplotlib.org/stable/gallery/statistics/hist.html
  plt.hist(PtBranchData, bins=20)
  plt.title(args.branch)
  plt.ylabel("Count")
  #plt.savefig('output.pdf')
  plt.show()
  print("This many events in selection: {}".format(PtBranchCounter))

