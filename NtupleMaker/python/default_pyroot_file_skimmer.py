import ROOT

from var_configs_dictionary import var_configs
#ROOT.gROOT.SetBatch(True) # sets visual display off (i.e. no graphs/TCanvas)

def check_cuts(input_list: list, omit_index: int=-1) -> bool: # python does not have arrays
  """ given a list of values and an index, return true if all values in the list,
      *except for the indexed item*, are the same. Return false otherwise.
      If no index is given in the second argument then no values are skipped in the list"""
  set_from_input_list = set(value for index, value in enumerate(input_list) if index != omit_index) 
  set_is_one_item_and_true = (len(set_from_input_list) == 1) and (set_from_input_list.pop() == True)
  return set_is_one_item_and_true


if __name__ == "__main__":
    from argparse import ArgumentParser
    parser = ArgumentParser()
    parser.add_argument('--in_file', '-i', required=True, action='store', help='input file')
    #parser.add_argument('--out_file', '-o', required=True, action='store', help='output file name')

    args = parser.parse_args()
    in_file = args.in_file

    ROOT.TH1.SetDefaultSumw2()

    new_file = ROOT.TFile.Open(in_file, "READ") 
    tree = new_file.Get("outtree")

    # branches are methods of tree object in pyroot

    ele_dict  = {"nBins" : 130, "xhigh" : 260}

    h_L1ElePt  = ROOT.TH1F("L1ElePt",  "", ele_dict["nBins"], 0, ele_dict["xhigh"])

    nEntries = tree.GetEntries()
    for i in range(0, nEntries):
      tree.GetEntry(i)

      L1ElePt   = tree.L1ElePt

      h_L1ElePt.Fill(L1ElePt)

    # end for-loop, write hists to new file
    #out_file = ROOT.TFile.Open(args.out_file, "RECREATE")
    #h_L1ElePt.Write()
    print(f"Histograms written to {out_file}")
