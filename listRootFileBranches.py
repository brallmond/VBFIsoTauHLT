import ROOT
import sys

ROOT.gROOT.SetBatch(True) # sets visual display off (i.e. no graphs/TCanvas)

def makeStringListOfBranches(inputBranches):
  # takes in object of type tree.GetListOfBranches
  # returns a normal python array of strings
  # the strings are the branchnames one would see from
  # tree->Print() in a ROOT terminal
  return [str(inputBranches[i]).split(' ')[1] for i in range(len(inputBranches))]

if __name__ == "__main__": 

  parser = argparse.ArgumentParser(description='Open a .root file') 
  parser.add_argument('-i', '--inputRootFile', dest='inFilename', action='store', 
                    help='the input .root file\'s name') 
  args = parser.parse_args() 

  inFile = ROOT.TFile.Open(args.inFilename,"READ") 
  tree = inFile.Get("demo/vbf") 


  listBranches = tree.GetListOfBranches()

  for i in makeStringListOfBranches(listBranches):
    print(i)

