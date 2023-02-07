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
    parser.add_argument('-DT', '--L1DiTauCut', dest='L1DiTauCut', default=34, action='store',
                        help='set the L1DiTauCut (default 34 for Runs after Era E)')

    args = parser.parse_args()
    in_file = args.in_file

    ROOT.TH1.SetDefaultSumw2()

    new_file = ROOT.TFile.Open(in_file, "READ") 
    tree = new_file.Get("outtree")

    TallyL1VBFDiJetOR = 0
    TallyL1VBFDiJetIsoTau = 0
    TallyL1DiTau = 0

    TallyPassLowestL1 = 0
    TallyL1VBFDiJetIncORIsoTau = 0
    TallyL1VBFDiJetIncORDiTau = 0
    TallyL1DiTauORIsoTau = 0
    TallyTripleOR = 0

    thirdJetBins = 2
    jet1Bins = 20
    jet2Bins = 8
    thirdJetScanRange = np.linspace(110., 120, thirdJetBins)
    jet1ScanRange = np.linspace(35.,130., jet1Bins)
    jet2ScanRange = np.linspace(35.,70., jet2Bins)

    gridTotal = np.zeros((thirdJetBins, jet2Bins, jet1Bins))
    gridOverlap = np.zeros((thirdJetBins, jet2Bins, jet1Bins))

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

    L1DiTauCut = float(args.L1DiTauCut)

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

    for i in range(0, nEntries):
      tree.GetEntry(i)

      BoolPassL1VBFDiJetOR = tree.passL1VBFDiJetOR
      BoolPassL1VBFDiJetIsoTau = tree.passL1VBFDiJetIsoTau
      # a higher iso tau L1 can be emulated here as well
      BoolPassL1DiTau = tree.passL1DiTau
      if (BoolPassL1DiTau):
        if (tree.L1DiTau1_pt < L1DiTauCut or tree.L1DiTau2_pt < L1DiTauCut):
          BoolPassL1DiTau = 0 

      if (BoolPassL1VBFDiJetIsoTau): TallyL1VBFDiJetIsoTau += 1
      if (BoolPassL1VBFDiJetOR): TallyL1VBFDiJetOR += 1
      if (BoolPassL1DiTau): TallyL1DiTau += 1

      if (BoolPassL1VBFDiJetOR or BoolPassL1VBFDiJetIsoTau): TallyL1VBFDiJetIncORIsoTau += 1
      if (BoolPassL1VBFDiJetOR or BoolPassL1DiTau): TallyL1VBFDiJetIncORDiTau += 1
      if (BoolPassL1VBFDiJetIsoTau or BoolPassL1DiTau): TallyL1DiTauORIsoTau += 1


      if (BoolPassL1VBFDiJetOR or BoolPassL1VBFDiJetIsoTau or BoolPassL1DiTau): TallyTripleOR += 1

      if (BoolPassL1VBFDiJetOR):
        L1DiJetORJet1Pt  = tree.L1DiJetORJet1
        L1DiJetORJet2Pt  = tree.L1DiJetORJet2
        L1DiJetORJet3Pt  = tree.L1DiJetORJet3
        L1DiJetORMjj     = tree.L1DiJetORMjj
        if ( ( (L1DiJetORJet1Pt >= 110 and L1DiJetORJet2Pt >= 35 and L1DiJetORJet3Pt == -999) or
             (L1DiJetORJet1Pt >= 35 and L1DiJetORJet2Pt >= 35 and L1DiJetORJet3Pt >= 110) )
             and L1DiJetORMjj >= 620):
          TallyPassLowestL1 += 1

        for thirdJetIndex, thirdJetEntry in enumerate(thirdJetScanRange):
          for jet2Index, jet2Entry in enumerate(jet2ScanRange):
            for jet1Index, jet1Entry in enumerate(jet1ScanRange):
              if jet2Entry > jet1Entry:
                continue

              if ( ( (L1DiJetORJet1Pt >= jet1Entry and L1DiJetORJet2Pt >= jet2Entry and L1DiJetORJet3Pt == -999) \
                  or (L1DiJetORJet1Pt >= jet1Entry and L1DiJetORJet2Pt >= jet2Entry and L1DiJetORJet3Pt >= thirdJetEntry) )
                  and L1DiJetORMjj >= 620 ):
                gridTotal[thirdJetIndex, jet2Index, jet1Index] += weight
                gridOverlap[thirdJetIndex, jet2Index, jet1Index] += weight

                if (BoolPassL1VBFDiJetIsoTau or BoolPassL1DiTau):
                  gridOverlap[thirdJetIndex, jet2Index, jet1Index] -= weight


    print(f"Sanity Check, Lowest L1 Tally : {TallyPassLowestL1}")

    # L1 Single Counts
    print("-------------L1!---------------")
    labels_single = ["VBF+IsoTau", "VBF Inc", "DiTau"] 
    values = [TallyL1VBFDiJetIsoTau, TallyL1VBFDiJetOR, TallyL1DiTau]
    print_formatted_labels_and_values(labels_single, values, three_values=True)

    # L1 ORs and Unique
    labels_OR = ["VBF Inc OR IsoTau", "VBF Inc OR DiTau", "VBF Iso Tau OR DiTau", "TripleOR", "Unique IsoTau"]
    uniqueL1VBFDiJetOR = TallyTripleOR - TallyL1DiTauORIsoTau
    values = [TallyL1VBFDiJetIncORIsoTau, TallyL1VBFDiJetIncORDiTau, TallyL1DiTauORIsoTau, \
              TallyTripleOR, uniqueL1VBFDiJetOR]
    print_formatted_labels_and_values(labels_OR, values, double_space=True, five_values=True)

    # print rate info and unpure/pure rate
    lumiScaling = 2. / rateDictionary[rateStudyString]["approxLumi"]
    rate_factor = rateDictionary[rateStudyString]["nBunches"] * 11245.6 * lumiScaling
    if (nEntries <= 0):
      print("\033\[31m" + "No viable events" + "\033\[0m")
    else: 
      rate_factor = rate_factor / nEntries
      print("#"*40)
      print("Rate Factor = nBunches * 11245.6 Hz * (Target Lumi / Avg. LS Lumi) / nEventsProcessed")
      print(f"Rate Factor = {rate_factor} Hz / Event : Rate = rate_factor * nEventsPassingCriteria")
      print(f"UNpure rate = {rate_factor * TallyL1VBFDiJetOR},  PURE rate = {rate_factor * uniqueL1VBFDiJetOR}")


    intJet1Pt = [int(i) for i in jet1ScanRange]
    intJet2Pt = [int(i) for i in jet2ScanRange]

    print(intJet1Pt)
    print(intJet2Pt)
  
    gridmax = np.max(gridTotal)
    gridmax = gridmax*1.2
  
    fig, axes = plt.subplots(2, 2)
    fig.set_size_inches(10.5, 10.5)

    # title formatting
    L1_String = "L1_DoubleJet_ZZZ_YY_DoubleJetXY_Mass_Min620"
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
 
      if (i <= 1):
        im = ax.imshow(gridTotal[i], vmin=0, vmax=gridmax, cmap='copper', interpolation='nearest', origin='lower')
        ax.set_title("jet1or3 ≥ " + str(10*(i)+110), fontsize=8)
        for (n,m),label in np.ndenumerate(gridTotal[i]):
          if (ignore_rate_factor):
            label = "{:.0f}".format(label)
          else:
            label = "{:.1f}".format(label/1000.)
          ax.text(m, n, label,ha='center',va='center', color='white', fontsize=8)

      if (i > 1):
        im = ax.imshow(gridOverlap[i-2], vmin=0, vmax=gridmax, cmap='copper', interpolation='nearest', origin='lower')
        ax.set_xlabel('jet1Pt ≥')
        for (n,m),label in np.ndenumerate(gridOverlap[i-2]):
          if (ignore_rate_factor):
            label = "{:.0f}".format(label)
          else:
            label = "{:.1f}".format(label/1000.)
          ax.text(m, n, label,ha='center',va='center', color='white', fontsize=8)

      if (i == 1):
        ax.text(1.05, 0.55, "Total Rate", transform=ax.transAxes, fontsize=12,
          rotation=-90)

      if (i == 3):
        ax.text(1.05, 0.25, "Pure Rate", transform=ax.transAxes, fontsize=12,
          rotation=-90)

      ax.set_ylabel('jet2Pt ≥')
  
      startx, endx = ax.get_xlim()
      ax.xaxis.set_ticks(np.arange(startx+0.5, endx, 1))
      ax.xaxis.set_ticklabels(intJet1Pt)

      starty, endy = ax.get_ylim()
      ax.yaxis.set_ticks(np.arange(starty+0.5, endy, 1))
      ax.yaxis.set_ticklabels(intJet2Pt)

      if (i != 0 and i != 2):
        ax.get_yaxis().set_visible(False)

    out_file = in_file.replace('.root','.pdf')
    plt.savefig(out_file)
    plt.tight_layout()
    plt.show()

 
