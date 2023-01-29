import ROOT
import re
import sys

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
    parser.add_argument('--aux_label', '-a', default="", help='prepending label for out filename')
    parser.add_argument('--L1_seed', '-s', required=False, default=0, action='store', help='select a predefined L1 seed')

    args = parser.parse_args()
    in_file = args.in_file

    ROOT.TH1.SetDefaultSumw2()

    new_file = ROOT.TFile.Open(in_file, "READ") 
    tree = new_file.Get("outtree")

    # i did not know it could be this easy.
    # i have lived my life in squalor until this moment.
    # i am dedicating myself to change, and bringing
    # forth the light in the world that was missing before
    # i chanced upon this simple and profound knowledge
    
    # branches are methods of tree object in pyroot
 
    ele_dict  = {"nBins" : 130, "xhigh" : 260}
    tau_dict  = {"nBins" : 80, "xhigh" : 320}
    jet1_dict = {"nBins" : 150, "xhigh" : 600}
    jet2_dict = {"nBins" : 50, "xhigh" : 200}
    mjj_dict  = {"nBins" : 175, "xhigh" : 7000}

    h_L1ElePt  = ROOT.TH1F("L1ElePt",  "", ele_dict["nBins"], 0, ele_dict["xhigh"])
    h_L1TauPt  = ROOT.TH1F("L1TauPt",  "", tau_dict["nBins"], 0, tau_dict["xhigh"])
    h_L1Jet1Pt = ROOT.TH1F("L1Jet1Pt", "", jet1_dict["nBins"], 0, jet1_dict["xhigh"])
    h_L1Jet2Pt = ROOT.TH1F("L1Jet2Pt", "", jet2_dict["nBins"], 0, jet2_dict["xhigh"])
    h_L1Mjj    = ROOT.TH1F("L1Mjj",    "", mjj_dict["nBins"], 0, mjj_dict["xhigh"])

    h_mL1ElePt  = ROOT.TH1F("mL1ElePt",   "", ele_dict["nBins"], 0, ele_dict["xhigh"])
    h_mL1TauPt  = ROOT.TH1F("mL1TauPt",   "", tau_dict["nBins"], 0, tau_dict["xhigh"])
    h_mL1Jet1Pt = ROOT.TH1F("mL1Jet1Pt", "", jet1_dict["nBins"], 0, jet1_dict["xhigh"])
    h_mL1Jet2Pt = ROOT.TH1F("mL1Jet2Pt", "", jet2_dict["nBins"], 0, jet2_dict["xhigh"])
    h_mL1Mjj    = ROOT.TH1F("mL1Mjj",       "", mjj_dict["nBins"], 0, mjj_dict["xhigh"])

    xbins_Off = var_configs["ElePt"][3]
    h_OffElePt  = ROOT.TH1F("ElePt",   "", ele_dict["nBins"], 0, ele_dict["xhigh"])
    #h_OffElePt  = ROOT.TH1F("ElePt",   "", len(xbins_Off)-1, xbins_Off)
    h_OffTauPt  = ROOT.TH1F("TauPt",   "", tau_dict["nBins"], 0, tau_dict["xhigh"])
    h_OffJet1Pt = ROOT.TH1F("Jet1Pt", "", jet1_dict["nBins"], 0, jet1_dict["xhigh"])
    h_OffJet2Pt = ROOT.TH1F("Jet2Pt", "", jet2_dict["nBins"], 0, jet2_dict["xhigh"])
    h_OffMjj    = ROOT.TH1F("Mjj",       "", mjj_dict["nBins"], 0, mjj_dict["xhigh"])

    h_mOffElePt  = ROOT.TH1F("mElePt",   "", ele_dict["nBins"], 0, ele_dict["xhigh"])
    #h_mOffElePt  = ROOT.TH1F("mElePt",   "", len(xbins_Off)-1, xbins_Off)
    h_mOffTauPt  = ROOT.TH1F("mTauPt",   "", tau_dict["nBins"], 0, tau_dict["xhigh"])
    h_mOffJet1Pt = ROOT.TH1F("mJet1Pt", "", jet1_dict["nBins"], 0, jet1_dict["xhigh"])
    h_mOffJet2Pt = ROOT.TH1F("mJet2Pt", "", jet2_dict["nBins"], 0, jet2_dict["xhigh"])
    h_mOffMjj    = ROOT.TH1F("mMjj",       "", mjj_dict["nBins"], 0, mjj_dict["xhigh"])

    # make cut criteria
    # read from file name!
    # credit to 
    # https://stackoverflow.com/questions/4289331/how-to-extract-numbers-from-a-string-in-python
    L1_cuts_from_in_file = re.findall(r'\d+', in_file) 
    if ("L1" in in_file):
      L1_cuts_from_in_file = L1_cuts_from_in_file[1::]
    possible_L1Cuts = [L1_cuts_from_in_file]
    # kept for backwards compatibility with old files
    #possible_L1Cuts = [ [30, 320, 10],
    #                    [38, 460, 12],
    #                    [32, 440, 14]]
    

    L1_seed_index = int(args.L1_seed)
    L1Cut_Jet1Pt = L1Cut_Jet2Pt = int(possible_L1Cuts[L1_seed_index][0])
    L1Cut_Mjj                   = int(possible_L1Cuts[L1_seed_index][1])
    L1Cut_ElePt                 = int(possible_L1Cuts[L1_seed_index][2])
    L1Cuts = [L1Cut_ElePt, L1Cut_Jet1Pt, L1Cut_Jet2Pt, L1Cut_Mjj]
    print(f"L1Cuts: {L1Cuts}")
    file_label_L1Cut = "_".join(["",str(L1Cut_Jet1Pt), str(L1Cut_Mjj), str(L1Cut_ElePt)])

    OffCut_ElePt = L1Cut_ElePt + 1 + 1 + 3
    OffCut_TauPt = 30 + 15
    OffCut_Jet1Pt = OffCut_Jet2Pt = L1Cut_Jet1Pt + 10 + 10
    OffCut_Mjj = L1Cut_Mjj + 50 + 150
    OffCuts = [OffCut_ElePt, OffCut_TauPt, OffCut_Jet1Pt, OffCut_Jet2Pt, OffCut_Mjj]
    print(f"OffCuts: {OffCuts}")


    nEntries = tree.GetEntries()
    for i in range(0, nEntries):
    #for i in range(0, 100):
      tree.GetEntry(i)

      L1ElePt   = tree.L1ElePt
      L1Jet1Pt  = tree.L1Jet1Pt
      L1Jet2Pt  = tree.L1Jet2Pt
      L1Mjj     = tree.L1Mjj
      OffElePt  = tree.OffElePt
      OffTauPt  = tree.OffTauPt
      OffJet1Pt = tree.OffJet1Pt
      OffJet2Pt = tree.OffJet2Pt
      OffMjj    = tree.OffMjj
      MatchL1Off = tree.MatchL1Off

      # simply require the flag when you fill the hist
      # e z p z :^)
      L1Cuts_PassList = [L1ElePt  > L1Cuts[0], \
                         L1Jet1Pt > L1Cuts[1], \
                         L1Jet2Pt > L1Cuts[2], \
                         L1Mjj    > L1Cuts[3] ]

      L1Cut_NoEle  = check_cuts(L1Cuts_PassList, 0)
      L1Cut_NoJet1 = check_cuts(L1Cuts_PassList, 1)
      L1Cut_NoJet2 = check_cuts(L1Cuts_PassList, 2)
      L1Cut_NoMjj  = check_cuts(L1Cuts_PassList, 3)
      L1Cut_All    = check_cuts(L1Cuts_PassList)

      OffCuts_PassList = [OffElePt  > OffCuts[0], \
                          OffTauPt  > OffCuts[1], \
                          OffJet1Pt > OffCuts[2], \
                          OffJet2Pt > OffCuts[3], \
                          OffMjj    > OffCuts[4] ]

      OffCut_NoEle  = check_cuts(OffCuts_PassList, 0)
      OffCut_NoTau  = check_cuts(OffCuts_PassList, 1)
      OffCut_NoJet1 = check_cuts(OffCuts_PassList, 2)
      OffCut_NoJet2 = check_cuts(OffCuts_PassList, 3)
      OffCut_NoMjj  = check_cuts(OffCuts_PassList, 4)
      OffCut_All    = check_cuts(OffCuts_PassList)

      debug = False
      if debug == True:
        print("#"*40)
        print("L1 info")
        print(f"{L1ElePt:6.2f}, {L1Jet1Pt:6.2f}, {L1Jet2Pt:6.2f}, {L1Mjj:6.2f}")
        print(f"{L1Cut_NoEle:6}, {L1Cut_NoJet1:6}, {L1Cut_NoJet2:6}, {L1Cut_NoMjj:6}, {L1Cut_All:6}")
        print(L1Cuts_PassList)
        print("Off. info")
        print(f"{OffElePt:6.2f}, {OffTauPt:6.2f}, {OffJet1Pt:6.2f}, {OffJet2Pt:6.2f}, {OffMjj:6.2f}")
        print(f"{OffCut_NoEle:6}, {OffCut_NoTau:6}, {OffCut_NoJet1:6}, {OffCut_NoJet2:6}, {OffCut_NoMjj:6}, {OffCut_All:6}")
        print(OffCuts_PassList)
        print(f"Match L1 Off {MatchL1Off}")


      # make 18 hists :)
      if (L1Cut_NoEle):  h_L1ElePt.Fill(L1ElePt)
      if (L1Cut_NoJet1): h_L1Jet1Pt.Fill(L1Jet1Pt)
      if (L1Cut_NoJet2): h_L1Jet2Pt.Fill(L1Jet2Pt)
      if (L1Cut_NoMjj):  h_L1Mjj.Fill(L1Mjj)

      if (OffCut_NoEle):  h_OffElePt.Fill(OffElePt)
      if (OffCut_NoTau):  h_OffTauPt.Fill(OffTauPt) 
      if (OffCut_NoJet1): h_OffJet1Pt.Fill(OffJet1Pt)
      if (OffCut_NoJet2): h_OffJet2Pt.Fill(OffJet2Pt)
      if (OffCut_NoMjj):  h_OffMjj.Fill(OffMjj)
    
      if (MatchL1Off):
        if (L1Cut_NoEle):  h_mL1ElePt.Fill(L1ElePt)
        if (L1Cut_NoJet1): h_mL1Jet1Pt.Fill(L1Jet1Pt)
        if (L1Cut_NoJet2): h_mL1Jet2Pt.Fill(L1Jet2Pt)
        if (L1Cut_NoMjj):  h_mL1Mjj.Fill(L1Mjj)

        if (L1Cut_All):
          if (OffCut_NoEle):  h_mOffElePt.Fill(OffElePt)
          if (OffCut_NoTau):  h_mOffTauPt.Fill(OffTauPt) 
          if (OffCut_NoJet1): h_mOffJet1Pt.Fill(OffJet1Pt)
          if (OffCut_NoJet2): h_mOffJet2Pt.Fill(OffJet2Pt)
          if (OffCut_NoMjj):  h_mOffMjj.Fill(OffMjj)
        

    # end for-loop, write hists to new file
    out_file_name = "hists_" + in_file.replace("eff_samples/", "")
    out_file = ROOT.TFile.Open(out_file_name, "RECREATE")
    h_L1ElePt.Write()
    h_L1Jet1Pt.Write()
    h_L1Jet2Pt.Write()
    h_L1Mjj.Write()
    h_mL1ElePt.Write()
    h_mL1Jet1Pt.Write()
    h_mL1Jet2Pt.Write()
    h_mL1Mjj.Write()
    h_OffElePt.Write()
    h_OffTauPt.Write()
    h_OffJet1Pt.Write()
    h_OffJet2Pt.Write()
    h_OffMjj.Write()
    h_mOffElePt.Write()
    h_mOffTauPt.Write()
    h_mOffJet1Pt.Write()
    h_mOffJet2Pt.Write()
    h_mOffMjj.Write()
    print(f"Histograms written to {out_file}")
