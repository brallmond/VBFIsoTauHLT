import ROOT
from L1VBFEle_functions import fillWithTVecsNoEnergyBranch, highestMjjPair

#ROOT.gROOT.SetBatch(True) # sets visual display off (i.e. no graphs/TCanvas)

if __name__ == "__main__":
    from argparse import ArgumentParser
    parser = ArgumentParser()
    parser.add_argument('--in_file', '-i', required=True, action='store', help='input file')
    #parser.add_argument('--out_file', '-o', required=True, action='store', help='output file name')

    args = parser.parse_args()
    in_file = args.in_file

    ROOT.TH1.SetDefaultSumw2()

    new_file = ROOT.TFile.Open(in_file, "READ") 
    tree = new_file.Get("l1UpgradeTree/L1UpgradeTree")

    # branches are methods of tree object in pyroot

    #ele_dict  = {"nBins" : 130, "xhigh" : 260}
    #h_L1ElePt  = ROOT.TH1F("L1ElePt",  "", ele_dict["nBins"], 0, ele_dict["xhigh"])

    #h_nEGs     = ROOT.TH1F("nEGs", "", 10, 0, 10)

    nEntries = tree.GetEntries()
    for i in range(0, 10):
      tree.GetEntry(i)

      #nEGs = tree.nEGs # not working
      # type UShort_t
      # prints as 
      # <cppyy.gbl.L1Analysis.L1AnalysisL1UpgradeDataFormat object at 0xb>
      # defined here as "unsigned short int nEGs;"
      # https://github.com/cms-sw/cmssw/blob/065028f82b4451e7bd244b4c348eb0723cd5e568/L1Trigger/L1TNtuples/interface/L1AnalysisL1UpgradeDataFormat.h

      nEGs  = len(tree.egEt)
      branch_egEt  = tree.egEt
      branch_egEta = tree.egEta
      branch_egPhi = tree.egPhi
      branch_egIso = tree.egIso
      L1EGs = fillWithTVecsNoEnergyBranch(branch_egEt, branch_egEta, branch_egPhi)

      nJets = len(tree.jetEt)
      branch_jetEt  = tree.jetEt
      branch_jetEta = tree.jetEta 
      branch_jetPhi = tree.jetPhi
      L1Jets = fillWithTVecsNoEnergyBranch(branch_jetEt, branch_jetEta, branch_jetPhi)
      
      print(i, len(L1EGs), len(L1Jets))


      #h_nEGs.Fill(nEGs)

    # end for-loop, write hists to new file
    #out_file = ROOT.TFile.Open(args.out_file, "RECREATE")
    #h_L1ElePt.Write()
    #print(f"Histograms written to {out_file}")
