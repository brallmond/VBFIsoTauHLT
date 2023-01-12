import ROOT
from L1VBFEle_functions import fillWithTVecsNoEnergyBranch, highestMjjPair
from array import array

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
    tree = new_file.Get("l1UpgradeTree/L1UpgradeTree")

    # branches are methods of tree object in pyroot

    ROOT.TH1.SetDefaultSumw2()

    out_file = ROOT.TFile.Open(args.out_file, "RECREATE")
    out_tree = ROOT.TTree("out_tree", "skimmed event data")

    out_el_Et = array('f', [0.])
    out_el_Iso = array('i', [0])
    out_j1_Et = array('f', [0.])
    out_j2_Et = array('f', [0.])
    out_mjj = array('f', [0.])
    out_tree.Branch("L1EleEt", out_el_Et, 'pt/F')
    out_tree.Branch("L1EleIso", out_el_Iso, 'iso/I')
    out_tree.Branch("L1Jet1Et", out_j1_Et, 'pt/F')
    out_tree.Branch("L1Jet2Et", out_j2_Et, 'pt/F')
    out_tree.Branch("L1Mjj", out_mjj, 'mjj/F')

    # iso_value <= 3 allows any iso value, i think == 0 is just tight iso, also ==0 and <= 0 are equivalent as iso_values are never negative
    # iso_value == 3, any thing passing iso
    # iso_value == 0, events passing tight iso
    # iso_value cannot be negative
    # events passing tighter iso (iso_value=0) are a subset of events passing any iso (iso_value=3)
    iso_value = 0
    print(f"YOUR ISO VALUE IS {iso_value}, MAKE SURE THAT'S CORRECT")

    nViable = 0
    nEntries = tree.GetEntries()
    for i in range(nEntries):
      tree.GetEntry(i)

      if i%100 == 0: print(f"Event number: {i}")

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
      branch_eg_Iso = tree.egIso

      pass_eg_Et  = [i for i in range(nEGs) if branch_eg_Et[i] >= 2]
      pass_eg_Eta = [i for i in range(nEGs) if abs(branch_eg_Eta[i]) <= 2.1]
      pass_eg_Iso = [i for i in range(nEGs) if branch_eg_Iso[i] == iso_value]

      pass_filter_egs = list(set(pass_eg_Et) & set(pass_eg_Eta) & set(pass_eg_Iso))

      L1EGs = fillWithTVecsNoEnergyBranch(branch_eg_Et, branch_eg_Eta, branch_eg_Phi, pass_filter_egs)
      n_good_egs = len(L1EGs)

      nJets = len(tree.jetEt)
      branch_jet_Et  = tree.jetEt
      branch_jet_Eta = tree.jetEta 
      branch_jet_Phi = tree.jetPhi

      pass_jet_Et  = [i for i in range(nJets) if branch_jet_Et[i] >= 10]
      pass_jet_Eta = [i for i in range(nJets) if abs(branch_jet_Eta[i]) <= 4.7]

      pass_filter_jets = list(set(pass_jet_Et) & set(pass_jet_Eta))

      L1Jets = fillWithTVecsNoEnergyBranch(branch_jet_Et, branch_jet_Eta, branch_jet_Phi, pass_filter_jets)
      n_good_jets = len(L1Jets)

      # initialize variables to non-physical values
      el_Et = j1_Et = j2_Et = mjj = -999

      if (n_good_jets >= 1 or n_good_egs >= 1):
        nViable += 1

        if (n_good_jets >= 2):
          j1_index, j2_index, mjj = highestMjjPair(L1Jets)
          if (j1_index == 999 or j2_index == 999): 
            j1_index = 0
            j2_index = 1
            j1_Et = L1Jets[j1_index].Pt()
            j2_Et = L1Jets[j2_index].Pt()
            mjj = (L1Jets[j1_index] + L1Jets[j2_index]).M()
          else:
            j1_Et = L1Jets[j1_index].Pt()
            j2_Et = L1Jets[j2_index].Pt()
          out_mjj[0] = mjj

          # assign leading jet based on Et (which is equivalent to pT at L1)
          if (j2_Et > j1_Et): 
            temp_index = j1_index
            j1_index = j2_index
            j2_index = temp_index
            j2_Et = L1Jets[j2_index].Pt()
            out_j2_Et[0]  = j2_Et

        if (n_good_jets == 1):
          j1_index = 0
          j1_Et = L1Jets[j1_index].Pt()
          out_j1_Et[0]  = j1_Et
        
        if (n_good_egs >= 1):  
          el_Et = L1EGs[0].Pt() # assuming the leading one is the best
          el_Iso = branch_eg_Iso[pass_filter_egs[0]]
          out_el_Et[0]  = el_Et
          out_el_Iso[0] = el_Iso

      #print(f"{i} : good EGs = {n_good_egs} , good jets = {n_good_jets} : el pt {el_Et:.2f} j1 pt {j1_Et:.2f}")

      out_tree.Fill()


    # nEntries, nViable, %
    print(f"{nEntries} : {nViable} : {nViable*100/nEntries:.3f}%")
    out_tree.Write()
    out_file.Close()

