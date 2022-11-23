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

    looseiso_counter = 0
    tightiso_counter = 0

    nEntries = tree.GetEntries()
    print(nEntries)
    for i in range(nEntries):
      tree.GetEntry(i)

      #nEGs = tree.nEGs # not working
      # type UShort_t
      # prints as 
      # <cppyy.gbl.L1Analysis.L1AnalysisL1UpgradeDataFormat object at 0xb>
      # defined here as "unsigned short int nEGs;"
      # https://github.com/cms-sw/cmssw/blob/065028f82b4451e7bd244b4c348eb0723cd5e568/L1Trigger/L1TNtuples/interface/L1AnalysisL1UpgradeDataFormat.h

      nEGs  = len(tree.egEt)
      branch_eg_Et  = tree.egEt
      branch_eg_Eta = tree.egEta
      branch_eg_Phi = tree.egPhi
      branch_eg_Iso = tree.egIso #either 0 or 3, taking 0 to be loose and 3 to be tight

      pass_eg_Et  = [branch_eg_Et[i] for i in range(nEGs) if branch_eg_Et[i] >= 10]
      pass_eg_Eta = [branch_eg_Eta[i] for i in range(nEGs) if abs(branch_eg_Eta[i]) <= 2.1]

      pass_filter_egs = list(set(pass_eg_Et) & set(pass_eg_Eta))
      if ( len(pass_filter_egs) == 0 ): continue

      L1EGs = fillWithTVecsNoEnergyBranch(branch_eg_Et, branch_eg_Eta, branch_eg_Phi, pass_filter_egs)
      n_good_egs = len(L1EGs)

      nJets = len(tree.jetEt)
      branch_jet_Et  = tree.jetEt
      branch_jet_Eta = tree.jetEta 
      branch_jet_Phi = tree.jetPhi

      pass_jet_Et  = [branch_jet_Et[i] for i in range(nJets) if branch_jet_Et[i] >= 30]
      pass_jet_Eta = [branch_jet_Et[i] for i in range(nJets) if abs(branch_jet_Eta[i]) <= 4.7]

      pass_filter_jets = list(set(pass_jet_Et) & set(pass_jet_Eta))
      if ( len(pass_filter_jets) == 0): continue

      L1Jets = fillWithTVecsNoEnergyBranch(branch_jet_Et, branch_jet_Eta, branch_jet_Phi, pass_filter_jets)
      n_good_jets = len(L1Jets)

      if (n_good_jets >= 2 and n_good_egs >= 1):

        print("Good EGs")
        for i in range(n_good_egs):
          print(L1EGs[i].Pt())  

        print("Good Jets")
        for i in range(n_good_jets):
          print(L1Jets[i].Pt())

        L1_j1_index, L1_j1_index, L1Mjj = highestMjjPair(L1Jets)
        j1_Et = branch_jet_Et[L1_j1_index]
        j2_Et = branch_jet_Et[L1_j2_index]
        el_Et = branch_eg_Et[0]


      #h_nEGs.Fill(nEGs)

    # end for-loop, write hists to new file
    #out_file = ROOT.TFile.Open(args.out_file, "RECREATE")
    #h_L1ElePt.Write()
    #print(f"Histograms written to {out_file}")
