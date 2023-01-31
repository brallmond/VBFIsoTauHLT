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

    TallyL1VBFDiJetOR = 0
    TallyL1VBFDiJetIsoTau = 0
    TallyL1DiTau = 0

    TallyPassLowestL1 = 0
    TallyL1VBFDiJetIncORIsoTau = 0
    TallyL1VBFDiJetIncORDiTau = 0
    TallyL1DiTauORIsoTau = 0
    TallyTripleOR = 0

    isoTauBins = 3
    mjjBins = 4
    jetBins = 11
    isoTauScanRange = np.linspace(45.,55., isoTauBins)
    mjjScanRange = np.linspace(450.,600., mjjBins)
    jetScanRange = np.linspace(35.,55., jetBins)

    gridTotal = np.zeros((isoTauBins, mjjBins, jetBins))
    gridOverlap = np.zeros((isoTauBins, mjjBins, jetBins))

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

      BoolPassL1VBFDiJetOR = tree.passL1VBFDiJetOR
      BoolPassL1VBFDiJetIsoTau = tree.passL1VBFDiJetIsoTau
      BoolPassL1DiTau = tree.passL1DiTau

      if (BoolPassL1VBFDiJetIsoTau): TallyL1VBFDiJetIsoTau += 1
      if (BoolPassL1VBFDiJetOR): TallyL1VBFDiJetOR += 1
      if (BoolPassL1DiTau): TallyL1DiTau += 1

      if (BoolPassL1VBFDiJetOR or BoolPassL1VBFDiJetIsoTau): TallyL1VBFDiJetIncORIsoTau += 1
      if (BoolPassL1VBFDiJetOR or BoolPassL1DiTau): TallyL1VBFDiJetIncORDiTau += 1
      if (BoolPassL1VBFDiJetIsoTau or BoolPassL1DiTau): TallyL1DiTauORIsoTau += 1


      if (BoolPassL1VBFDiJetOR or BoolPassL1VBFDiJetIsoTau or BoolPassL1DiTau): TallyTripleOR += 1

      if (BoolPassL1VBFDiJetIsoTau):
        L1IsoTauPt   = tree.L1IsoTauPt
        L1Jet1Pt  = tree.L1Jet1Pt
        L1Jet2Pt  = tree.L1Jet2Pt
        L1Mjj     = tree.L1Mjj

        for tauIndex, tauEntry in enumerate(isoTauScanRange):
          for mjjIndex, mjjEntry in enumerate(mjjScanRange):
            for jetIndex, jetEntry in enumerate(jetScanRange):

              if ((L1IsoTauPt >= tauEntry) and (L1Jet1Pt >= jetEntry and L1Jet2Pt >= jetEntry) and (L1Mjj >= mjjEntry)):
                gridTotal[tauIndex, mjjIndex, jetIndex] += weight
                gridOverlap[tauIndex, mjjIndex, jetIndex] += weight

                if (L1IsoTauPt >= 45 and L1Jet1Pt >= 35 and L1Jet2Pt >= 35 and L1Mjj >= 450):
                  TallyPassLowestL1 += 1

                #if (BoolPassAnyOther):
                if (BoolPassL1VBFDiJetOR or BoolPassL1DiTau):
                  gridOverlap[tauIndex, mjjIndex, jetIndex] -= weight


    print(f"Sanity Check, Lowest L1 Tally : {TallyPassLowestL1}")

    # L1 Single Counts
    print("-------------L1!---------------")
    labels_single = ["VBF+IsoTau", "VBF Inc", "DiTau"] 
    values = [TallyL1VBFDiJetIsoTau, TallyL1VBFDiJetOR, TallyL1DiTau]
    print_formatted_labels_and_values(labels_single, values, three_values=True)

    # L1 ORs and Unique
    labels_OR = ["VBF Inc OR IsoTau", "VBF Inc OR DiTau", "VBF Iso Tau OR DiTau", "TripleOR", "Unique IsoTau"]
    uniqueL1VBFIsoTau = TallyTripleOR - TallyL1VBFDiJetIncORDiTau
    values = [TallyL1VBFDiJetIncORIsoTau, TallyL1VBFDiJetIncORDiTau, TallyL1DiTauORIsoTau, TallyTripleOR, uniqueL1VBFIsoTau]
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
      print(f"UNpure rate = {rate_factor * TallyL1VBFDiJetIsoTau},  PURE rate = {rate_factor * uniqueL1VBFIsoTau}")


    intJetPt = [int(i) for i in jetScanRange]
    intMjj = [int(i) for i in mjjScanRange]

    print(intJetPt)
    print(intMjj)
  
    gridmax = np.max(gridTotal)
    gridmax = gridmax*1.2
  
    fig, axes = plt.subplots(2, 3)
    fig.set_size_inches(10.5, 10.5)

    # title formatting
    L1_String = "L1_DoubleJetXX_ Mass_MinYYY_IsoTauZZ"
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
        ax.set_title("isoTauPt ≥ " + str(5*(i)+45), fontsize=8)
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

 
