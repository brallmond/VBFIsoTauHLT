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

    args = parser.parse_args()
    in_file = args.in_file

    ROOT.TH1.SetDefaultSumw2()

    new_file = ROOT.TFile.Open(in_file, "READ") 
    tree = new_file.Get("outtree")

    TallyL1VBFDiJetEG = 0
    TallyL1VBFDiJetOR = 0
    TallyL1VBFDiJetIsoTau = 0
    TallyDummyEGORL1 = 0

    TallyPassLowestL1 = 0
    TallyL1VBFDiJetIncORIsoTau = 0
    TallyNotL1VBFEG = 0
    TallyQuadOR = 0

    electronScanRange = np.linspace(10.,14.,3)
    jetScanRange = np.linspace(30.,50.,11)
    mjjScanRange = np.linspace(300.,500.,11)

    gridTotal = np.zeros((3,11,11))
    gridOverlap = np.zeros((3,11,11))

    if ("2018" in in_file): 
      rateStudyString = "2018O"
    elif ("2022E" in in_file or "2022_E" in in_file):
      rateStudyString = "2022E"
    elif ("2022F" in in_file or "2022_F" in in_file):
      rateStudyString = "2022F"
    else:
      print("Change in-filename to contain 2018 or 2022E, reflecting the sample it was made from.")


    nEntries = tree.GetEntries()

    # print rate info and unpure/pure rate
    lumiScaling = 2. / rateDictionary[rateStudyString]["approxLumi"]
    rate_factor = rateDictionary[rateStudyString]["nBunches"] * 11245.6 * lumiScaling
    rate_factor = rate_factor / nEntries
    print("#"*40)
    print("Rate Factor = nBunches * 11245.6 Hz * (Target Lumi / Avg. LS Lumi) / nEventsProcessed")
    print(f"Rate Factor = {rate_factor} Hz / Event : Rate = rate_factor * nEventsPassingCriteria")

    weight = rate_factor
    ignore_rate_factor = "y" in args.ignore_rate_factor.lower()
    if (ignore_rate_factor):
      weight = 1

    for i in range(0, nEntries):
      tree.GetEntry(i)

      BoolPassL1VBFDiJetEG = tree.passL1VBFDiJetEG
      BoolPassL1VBFDiJetOR = tree.passL1VBFDiJetOR
      BoolPassL1VBFDiJetIsoTau = tree.passL1VBFDiJetIsoTau
      BoolPassDummyEGORL1  = tree.passDummyEGORL1

      if (BoolPassL1VBFDiJetEG): TallyL1VBFDiJetEG += 1
      if (BoolPassL1VBFDiJetOR): TallyL1VBFDiJetOR += 1
      if (BoolPassL1VBFDiJetIsoTau): TallyL1VBFDiJetIsoTau += 1
      if (BoolPassDummyEGORL1): TallyDummyEGORL1 += 1

      BoolExistingVBFOR = BoolPassL1VBFDiJetOR or BoolPassL1VBFDiJetIsoTau
      if (BoolExistingVBFOR): TallyL1VBFDiJetIncORIsoTau += 1
      BoolPassAnyOther = BoolExistingVBFOR or BoolPassDummyEGORL1
      if (BoolPassAnyOther): TallyNotL1VBFEG += 1 
      if (BoolPassAnyOther or BoolPassL1VBFDiJetEG): TallyQuadOR += 1

      if (BoolPassL1VBFDiJetEG):
        L1ElePt   = tree.L1ElePt
        L1Jet1Pt  = tree.L1Jet1Pt
        L1Jet2Pt  = tree.L1Jet2Pt
        L1Mjj     = tree.L1Mjj

        for eleIndex, eleEntry in enumerate(electronScanRange):
          for jetIndex, jetEntry in enumerate(jetScanRange):
            for mjjIndex, mjjEntry in enumerate(mjjScanRange):

              if ((L1ElePt >= eleEntry) and (L1Jet1Pt >= jetEntry and L1Jet2Pt >= jetEntry) and (L1Mjj >= mjjEntry)):
                gridTotal[eleIndex, jetIndex, mjjIndex] += weight
                gridOverlap[eleIndex, jetIndex, mjjIndex] += weight

                if (L1ElePt >= 10 and L1Jet1Pt >= 30 and L1Jet2Pt >= 30 and L1Mjj >= 300):
                  TallyPassLowestL1 += 1

                if (BoolPassAnyOther):
                  gridOverlap[eleIndex, jetIndex, mjjIndex] -= weight


    print(f"Sanity Check, Lowest L1 Tally : {TallyPassLowestL1}")

    # print output
    labels = ["VBF+Ele","VBF+IsoTau", "VBF Inc", "L1 EGs"] 
    values = [TallyL1VBFDiJetEG, TallyL1VBFDiJetOR, TallyL1VBFDiJetIsoTau, TallyDummyEGORL1]
    print_formatted_labels_and_values(labels, values)

    labels = ["VBF Inc OR IsoTau", "Any Except L1VBFEG", "Any L1", "Unique L1VBFEG"]
    uniqueL1VBFEG = TallyQuadOR - TallyNotL1VBFEG
    values = [TallyL1VBFDiJetIncORIsoTau, TallyNotL1VBFEG, TallyQuadOR, uniqueL1VBFEG]
    print_formatted_labels_and_values(labels, values, double_space=True)
    print(f"UNpure rate = {rate_factor * TallyL1VBFDiJetEG},  PURE rate = {rate_factor * uniqueL1VBFEG}")

    intJetPt = [int(i) for i in jetScanRange]
    intMjj = [int(i) for i in mjjScanRange]
  
    gridmax = np.max(gridTotal)
    gridmax = gridmax*1.2
  
    fig, axes = plt.subplots(2, 3)
    fig.set_size_inches(10.5, 10.5)

    # title formattin
    loose_or_tight = "Neither"
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
          label = "{:.1f}".format(label/1000.)
          ax.text(m, n, label,ha='center',va='center', color='white', fontsize=6)

      if (i == 3 or i == 4 or i == 5):
        im = ax.imshow(gridOverlap[i-3], vmin=0, vmax=gridmax, cmap='copper', interpolation='nearest', origin='lower')
        ax.set_xlabel('jetPt ≥')
        for (n,m),label in np.ndenumerate(gridOverlap[i-3]):
          label = "{:.1f}".format(label/1000.)
          ax.text(m, n, label,ha='center',va='center', color='white', fontsize=6)

      if (i == 2):
        ax.text(1.05, 0.55, "Total Rate", transform=ax.transAxes, fontsize=12,
          rotation=-90)

      if (i == 5):
        ax.text(1.05, 0.25, "Pure Rate", transform=ax.transAxes, fontsize=12,
          rotation=-90)

      ax.set_ylabel('mjj ≥')
  
      start, end = ax.get_xlim()
  
      ax.xaxis.set_ticks(np.arange(start+0.5, end, 1))
      ax.xaxis.set_ticklabels(intJetPt)
      ax.yaxis.set_ticks(np.arange(start+0.5, end, 1))
      ax.yaxis.set_ticklabels(intMjj)

      if (i == 1 or i == 2 or i == 4 or i == 5):
        ax.get_yaxis().set_visible(False)

    out_file = in_file.replace('.root','.pdf')
    plt.savefig(out_file)
    plt.show()

 
