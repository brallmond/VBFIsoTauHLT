import ROOT

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
    parser.add_argument('--aux_label', '-a', required=True, action='store', help='prepending label for out filename')
    parser.add_argument('--L1_seed', '-s', required=True, action='store', help='select one of three predefined L1 seeds')

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
    
    h_L1ElePt = ROOT.TH1F("L1ElePt", "", 20, 0, 400)
    h_L1TauPt = ROOT.TH1F("L1TauPt", "", 20, 0, 400)
    h_L1Jet1Pt = ROOT.TH1F("L1Jet1Pt", "", 20, 0, 400)
    h_L1Jet2Pt = ROOT.TH1F("L1Jet2Pt", "", 20, 0, 400)
    h_L1Mjj = ROOT.TH1F("L1Mjj", "", 20, 0, 3000)

    h_mL1TauPt = ROOT.TH1F("mL1TauPt", "", 20, 0, 400)
    h_mL1ElePt = ROOT.TH1F("mL1ElePt", "", 20, 0, 400)
    h_mL1Jet1Pt = ROOT.TH1F("mL1Jet1Pt", "", 20, 0, 400)
    h_mL1Jet2Pt = ROOT.TH1F("mL1Jet2Pt", "", 20, 0, 400)
    h_mL1Mjj = ROOT.TH1F("mL1Mjj", "", 20, 0, 3000)

    h_OffElePt = ROOT.TH1F("ElePt", "", 20, 0, 400)
    h_OffTauPt = ROOT.TH1F("TauPt", "", 20, 0, 400)
    h_OffJet1Pt = ROOT.TH1F("Jet1Pt", "", 20, 0, 400)
    h_OffJet2Pt = ROOT.TH1F("Jet2Pt", "", 20, 0, 400)
    h_OffMjj = ROOT.TH1F("Mjj", "", 20, 0, 3000)

    h_mOffTauPt = ROOT.TH1F("mTauPt", "", 20, 0, 400)
    h_mOffElePt = ROOT.TH1F("mElePt", "", 20, 0, 400)
    h_mOffJet1Pt = ROOT.TH1F("mJet1Pt", "", 20, 0, 400)
    h_mOffJet2Pt = ROOT.TH1F("mJet2Pt", "", 20, 0, 400)
    h_mOffMjj = ROOT.TH1F("mMjj", "", 20, 0, 3000)

    # make cut criteria
    possible_L1Cuts = [ [30, 320, 10],
                        [38, 460, 12],
                        [32, 440, 14]]

    L1_seed_index = int(args.L1_seed)
    L1Cut_Jet1Pt = L1Cut_Jet2Pt = possible_L1Cuts[L1_seed_index][0]
    L1Cut_Mjj                   = possible_L1Cuts[L1_seed_index][1]
    L1Cut_ElePt                 = possible_L1Cuts[L1_seed_index][2]
    L1Cuts = [L1Cut_ElePt, L1Cut_Jet1Pt, L1Cut_Jet2Pt, L1Cut_Mjj]
    print(f"L1Cuts: {L1Cuts}")

    OffCut_ElePt = L1Cut_ElePt + 1 + 1
    OffCut_TauPt = 30
    OffCut_Jet1Pt = OffCut_Jet2Pt = L1Cut_Jet1Pt + 10
    OffCut_Mjj = L1Cut_Mjj + 50  
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
      L1Cuts_PassList = [L1ElePt > L1Cut_ElePt, \
                         L1Jet1Pt > L1Cut_Jet1Pt, L1Jet2Pt > L1Cut_Jet2Pt, \
                         L1Mjj > L1Cut_Mjj]

      L1Cut_NoEle  = check_cuts(L1Cuts_PassList, 0)
      L1Cut_NoJet1 = check_cuts(L1Cuts_PassList, 1)
      L1Cut_NoJet2 = check_cuts(L1Cuts_PassList, 2)
      L1Cut_NoMjj  = check_cuts(L1Cuts_PassList, 3)
      L1Cut_All    = check_cuts(L1Cuts_PassList)

      OffCuts_PassList = [OffElePt > OffCut_ElePt, OffTauPt > OffCut_TauPt, \
                          OffJet1Pt > OffCut_Jet1Pt, OffJet2Pt > OffCut_Jet2Pt, \
                          OffMjj > OffCut_Mjj]

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
    strip_in_file = in_file.replace("../","").replace("data/","")
    out_file_name = args.aux_label + "hists_" + strip_in_file
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
    print(f"Histograms written to {out_file_name}")
