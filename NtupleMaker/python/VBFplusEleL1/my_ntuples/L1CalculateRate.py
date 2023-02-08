import ROOT
from L1VBFEle_functions import print_formatted_labels_and_values
from rateDictionary import rateDictionary
import numpy as np
import matplotlib.pyplot as plt


if __name__ == "__main__":
    from argparse import ArgumentParser
    parser = ArgumentParser()
    parser.add_argument('--in_file', '-i', required=True, action='store', help='input file')
    parser.add_argument('--ignore_rate_factor', '-E', required=False, action='store', default="False",\
                        help='ignore rate_factor weight? default false, if true, count events')
    parser.add_argument('--scaling', '-s', required=False, action='store', default="True",\
                        help='set your output to be unscaled, default is scaled to 2E34')
  

    args = parser.parse_args()
    in_file = args.in_file

    ROOT.TH1.SetDefaultSumw2()

    new_file = ROOT.TFile.Open(in_file, "READ") 
    tree = new_file.Get("outtree")

    TallyPassLowestL1 = 0

    TallyL1VBFDiJetEG = 0
    TallyL1VBFDiJetOR = 0
    TallyL1VBFDiJetIsoTau = 0
    TallyDummyEGORL1 = 0

    TallyL1VBFDiJetORVBFIsoTau = 0
    TallyNotL1VBFEG = 0
    TallyTripleVBFOR = 0
    TallyQuadOR = 0
    
    electronBins = 3
    mjjBins = 5
    jetBins = 5
    electronScanRange = np.linspace(10.,14., electronBins)
    mjjScanRange = np.linspace(300.,500., mjjBins)
    jetScanRange = np.linspace(30.,50., jetBins)

    gridTotal = np.zeros((electronBins, mjjBins, jetBins))
    gridOverlap = np.zeros((electronBins, mjjBins, jetBins))

    if ("2018" in in_file): 
      rateStudyString = "2018O"
    elif ("2022E" in in_file or "2022_E" in in_file):
      rateStudyString = "2022E"
    elif ("2022F" in in_file or "2022_F" in in_file):
      rateStudyString = "2022F"
    elif ("PU70" in in_file):
      rateStudyString = "2022G_PU70"
    elif ("PU60" in in_file):
      rateStudyString = "2022G_PU60"
    else:
      print("Change in-filename to contain 2018 or 2022E, reflecting the sample it was made from.")

    nEntries = tree.GetEntries()

    # print rate info and unpure/pure rate
    ignore_scaling = "n" in args.scaling.lower()
    if (ignore_scaling):
      scaling_numerator = rateDictionary[rateStudyString]["approxLumi"]
    else:
      scaling_numerator = 2.
    lumiScaling = scaling_numerator / rateDictionary[rateStudyString]["approxLumi"]
    rate_factor = rateDictionary[rateStudyString]["nBunches"] * 11245.6 * lumiScaling
    rate_factor = rate_factor / nEntries
    print("#"*40)
    print("Rate Factor = nBunches * 11245.6 Hz * (Target Lumi / Avg. LS Lumi) / nEventsProcessed")
    print(f"Rate Factor = {rate_factor} Hz / Event : Rate = rate_factor * nEventsPassingCriteria")

    weight = rate_factor
    ignore_rate_factor = "y" in args.ignore_rate_factor.lower()
    if (ignore_rate_factor):
      weight = 1

    DoubleJetCut = 35
    LeadingL1JetCut = 110

    L1IsoTauCut = 45
    L1JetPtCut = 35
    L1MjjCut = 450

    for i in range(0, nEntries):
      tree.GetEntry(i)

      BoolPassL1VBFDiJetEG = tree.passL1VBFDiJetEG
      BoolPassL1VBFDiJetOR = tree.passL1VBFDiJetOR
      if (BoolPassL1VBFDiJetOR):
        passing_ = tree.L1DiJetORMjj >= 620 \
               and ( (tree.L1DiJetORJet1 >= DoubleJetCut and tree.L1DiJetORJet2 >= DoubleJetCut \
               and tree.L1DiJetORJet3 >= LeadingL1JetCut)\
               or (tree.L1DiJetORJet1 >= LeadingL1JetCut and tree.L1DiJetORJet2 >= DoubleJetCut \
               and tree.L1DiJetORJet3 == -999.) )
        BoolPassL1VBFDiJetOR = passing_

      BoolPassL1VBFDiJetIsoTau = tree.passL1VBFDiJetIsoTau
      if (BoolPassL1VBFDiJetIsoTau):
        if (tree.L1IsoTau_TauPt < L1IsoTauCut or tree.L1IsoTau_Mjj < L1MjjCut \
           or tree.L1IsoTau_Jet1Pt < L1JetPtCut or tree.L1IsoTau_Jet2Pt < L1JetPtCut):
          BoolPassL1VBFDiJetIsoTau = 0

      BoolPassDummyEGORL1  = tree.passDummyEGORL1

      if (BoolPassL1VBFDiJetEG): TallyL1VBFDiJetEG += 1
      if (BoolPassL1VBFDiJetOR): TallyL1VBFDiJetOR += 1
      if (BoolPassL1VBFDiJetIsoTau): TallyL1VBFDiJetIsoTau += 1
      if (BoolPassDummyEGORL1): TallyDummyEGORL1 += 1

      BoolExistingVBFOR = BoolPassL1VBFDiJetOR or BoolPassL1VBFDiJetIsoTau
      if (BoolExistingVBFOR): TallyL1VBFDiJetORVBFIsoTau += 1
      if (BoolExistingVBFOR or BoolPassL1VBFDiJetEG): TallyTripleVBFOR += 1
      BoolPassAnyOther = BoolExistingVBFOR or BoolPassDummyEGORL1
      if (BoolPassAnyOther): TallyNotL1VBFEG += 1 
      if (BoolPassAnyOther or BoolPassL1VBFDiJetEG): TallyQuadOR += 1


      if (BoolPassL1VBFDiJetEG):
        L1ElePt   = tree.L1ElePt
        L1Jet1Pt  = tree.L1Jet1Pt
        L1Jet2Pt  = tree.L1Jet2Pt
        L1Mjj     = tree.L1Mjj
        if (L1ElePt >= 10 and L1Jet1Pt >= 30 and L1Jet2Pt >= 30 and L1Mjj >= 300):
          TallyPassLowestL1 += 1
             

        for eleIndex, eleEntry in enumerate(electronScanRange):
          for mjjIndex, mjjEntry in enumerate(mjjScanRange):
            for jetIndex, jetEntry in enumerate(jetScanRange):

              if ((L1ElePt >= eleEntry) and (L1Jet1Pt >= jetEntry and L1Jet2Pt >= jetEntry) and (L1Mjj >= mjjEntry)):
                gridTotal[eleIndex, mjjIndex, jetIndex] += weight
                gridOverlap[eleIndex, mjjIndex, jetIndex] += weight

                if (BoolPassAnyOther):
                  gridOverlap[eleIndex, mjjIndex, jetIndex] -= weight


    print(f"Sanity Check, Lowest L1 Tally : {TallyPassLowestL1}")
    labels = ["VBF+Ele", "VBFDiJetOR", "VBFIsoTau", "DummyEGL1", \
              "VBFDiJetORVBFDiTau", "NotVBFEG", "VBFTripleOR", "QuadOR", "UniqueVBFEle"]

    L1_Tallies = [TallyL1VBFDiJetEG, TallyL1VBFDiJetOR, TallyL1VBFDiJetIsoTau, TallyDummyEGORL1,\
                  TallyL1VBFDiJetORVBFIsoTau, TallyNotL1VBFEG, TallyTripleVBFOR, TallyQuadOR, \
                  TallyQuadOR - TallyNotL1VBFEG]

    uniqueL1VBFEG = L1_Tallies[-1]

    print(f"UNpure rate = {rate_factor * TallyL1VBFDiJetEG},  PURE rate = {rate_factor * uniqueL1VBFEG}")

    intJetPt = [int(i) for i in jetScanRange]
    intMjj = [int(i) for i in mjjScanRange]
  
    gridmax = np.max(gridTotal)
    gridmax = gridmax*1.2
  
    fig, axes = plt.subplots(2, 3)
    fig.set_size_inches(10.5, 10.5)

    # title formattin
    loose_or_tight = "Tight"
    if ("LOOSE" in in_file.upper()):
      loose_or_tight = "Loose"
    elif ("TIGHT" in in_file.upper()):
      loose_or_tight = "Tight"
    else:
      print("Change in-filename to contain tight or loose, reflecting the sample it was made from.")
    L1_String = "L1_VBF_DoubleJetXX_ Mass_MinYYY_" + loose_or_tight + "IsoEGZZ"
    year = "EZB "
    if ("2018" in rateStudyString):
      year += str(2018)
    else:
      year += rateStudyString

    RunData_String = year + ": Using run# " + str(rateDictionary[rateStudyString]["runNumber"]) + ", LS " \
                    + str(rateDictionary[rateStudyString]["minLS"]) + "-" + str(rateDictionary[rateStudyString]["maxLS"])\
                    + ", nEvents in skim = " + str(nEntries)
    rate_factor = str(rate_factor)[0:4] 
    fig.suptitle("Rate Scan in kHz of " + L1_String + '\n' 
               + RunData_String  + '\n'
               + "Rate factor: " + rate_factor + "Hz per Event")

    # plot formatting 
    for i, ax in enumerate(axes.flat):
 
      if (i == 0 or i == 1 or i == 2):
        im = ax.imshow(gridTotal[i], vmin=0, vmax=gridmax, cmap='copper', interpolation='nearest', origin='lower')
        ax.set_title("electronPt ≥ " + str(2*(i)+10), fontsize=8)
        for (n,m),label in np.ndenumerate(gridTotal[i]):
          if (ignore_rate_factor):
            label = "{:.0f}".format(label)
          else:
            label = "{:.1f}".format(label/1000.)
          ax.text(m, n, label,ha='center',va='center', color='white', fontsize=6)

      if (i == 3 or i == 4 or i == 5):
        im = ax.imshow(gridOverlap[i-3], vmin=0, vmax=gridmax, cmap='copper', interpolation='nearest', origin='lower')
        ax.set_xlabel('jetPt ≥')
        for (n,m),label in np.ndenumerate(gridOverlap[i-3]):
          if (ignore_rate_factor):
            label = "{:.0f}".format(label)
          else:
            label = "{:.1f}".format(label/1000.)
          ax.text(m, n, label,ha='center',va='center', color='white', fontsize=6)

      if (i == 2):
        ax.text(1.05, 0.55, "Total Rate", transform=ax.transAxes, fontsize=12,
          rotation=-90)

      if (i == 5):
        ax.text(1.05, 0.25, "Pure Rate", transform=ax.transAxes, fontsize=12,
          rotation=-90)

      ax.set_ylabel('mjj ≥')
  
      startx, endx = ax.get_xlim()
      starty, endy = ax.get_ylim()
  
      ax.xaxis.set_ticks(np.arange(startx+0.5, endx, 1))
      ax.xaxis.set_ticklabels(intJetPt)
      ax.yaxis.set_ticks(np.arange(starty+0.5, endy, 1))
      ax.yaxis.set_ticklabels(intMjj)

      if (i == 1 or i == 2 or i == 4 or i == 5):
        ax.get_yaxis().set_visible(False)

    out_file = in_file.replace('.root','.pdf')
    plt.savefig(out_file)
    plt.show()

 
