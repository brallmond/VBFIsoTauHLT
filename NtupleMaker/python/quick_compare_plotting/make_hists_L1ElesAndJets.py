import ROOT

#ROOT.gROOT.SetBatch(True) # sets visual display off (i.e. no graphs/TCanvas)


if __name__ == "__main__":
    from argparse import ArgumentParser
    parser = ArgumentParser()
    parser.add_argument('--in_file', '-i', required=True, action='store', help='input file')
    parser.add_argument('--out_file', '-o', required=True, action='store', help='output file name')

    args = parser.parse_args()
    in_file = args.in_file

    ROOT.TH1.SetDefaultSumw2()

    new_file = ROOT.TFile.Open(in_file, "READ") 
    tree = new_file.Get("out_tree")

    # i did not know it could be this easy.
    # i have lived my life in squalor until this moment.
    # i am dedicating myself to change, and bringing
    # forth the light in the world that was missing before
    # i chanced upon this simple and profound knowledge
    
    # branches are methods of tree object in pyroot
 
    ele_dict  = {"nBins" : 130, "xhigh" : 260}
    jet1_dict = {"nBins" : 150, "xhigh" : 600}
    jet2_dict = {"nBins" : 50, "xhigh" : 200}
    mjj_dict  = {"nBins" : 175, "xhigh" : 7000}

    h_L1EleEt  = ROOT.TH1F("L1EleEt",  "", ele_dict["nBins"], 0, ele_dict["xhigh"])
    h_L1Jet1Et = ROOT.TH1F("L1Jet1Et", "", jet1_dict["nBins"], 0, jet1_dict["xhigh"])
    h_L1Jet2Et = ROOT.TH1F("L1Jet2Et", "", jet2_dict["nBins"], 0, jet2_dict["xhigh"])
    h_L1Mjj    = ROOT.TH1F("L1Mjj",    "", mjj_dict["nBins"], 0, mjj_dict["xhigh"])

    nEntries = tree.GetEntries()
    #for i in range(0, nEntries):
    for i in range(0, 100):
      tree.GetEntry(i)

      L1EleEt   = tree.L1EleEt
      h_L1EleEt.Fill(L1EleEt)

      L1Jet1Et  = tree.L1Jet1Et
      h_L1Jet1Et.Fill(L1Jet1Et)

      L1Jet2Et  = tree.L1Jet2Et
      h_L1Jet2Et.Fill(L1Jet2Et)

      L1Mjj     = tree.L1Mjj
      h_L1Mjj.Fill(L1Mjj)

      debug = True
      if debug == True:
        print("#"*40)
        print("L1 info")
        print(f"{L1EleEt:6.2f}, {L1Jet1Et:6.2f}, {L1Jet2Et:6.2f}, {L1Mjj:6.2f}")

    # end for-loop, write hists to new file
    out_file = ROOT.TFile.Open(args.out_file, "RECREATE")
    h_L1EleEt.Write()
    h_L1Jet1Et.Write()
    h_L1Jet2Et.Write()
    h_L1Mjj.Write()
    print(f"Histograms written to {out_file}")
