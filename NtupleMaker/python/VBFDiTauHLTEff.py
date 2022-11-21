# Braden Allmond, Nov 7th 2022

from L1VBFEle_functions import fillWithTVecs, highestMjjPair
import ROOT
import argparse

ROOT.gROOT.SetBatch(True)

# usage:
# python3 VBFDiTauHLTEff.py -i ../../../samples/VBFE_CorrectedEleIsoAndNewFilter.root

if __name__ == "__main__":

  parser = argparse.ArgumentParser(description='Make skims for 2D Eff. plot')
  parser.add_argument('-i', '--input_root_file', dest='input_root_file', action='store',
                    help='the input .root file\'s name')
  parser.add_argument('-o', '--output_root_file', dest='output_root_file', action='store',
                    help='name of your output file')

  args = parser.parse_args()

  in_file = ROOT.TFile.Open(args.input_root_file, "READ")
  tree = in_file.Get("demo/vbf")

  print(f"Output file name: {args.output_root_file}")
  ROOT.TH1.SetDefaultSumw2()

  out_file = ROOT.TFile.Open(args.output_root_file, "RECREATE")
  outtree = ROOT.TTree("outtree", "skimmed event data")
  # leading/subleading
  # pt/eta/phi




