import ROOT
from L1VBFEle_functions import print_formatted_labels_and_values
from rateDictionary import rateDictionary
import numpy as np
import matplotlib.pyplot as plt


if __name__ == "__main__":
    from argparse import ArgumentParser
    parser = ArgumentParser()
    parser.add_argument('--in_file', '-i', required=True, action='store', help='input file')
    parser.add_argument('--metric', '-m', required=True, action='store', help='define gain metric')
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

    TallyVBFDiTauHLT = 0
    TallyInclusiveVBFHLT = 0
    TallyDiTauHLT = 0
    TallyVBFDiTauORInclusiveVBFHLT = 0
    TallyVBFDiTauORDiTauHLT = 0
    TallyInclusiveVBFORDiTauHLT = 0
    TallyTripleORHLT = 0

    TallyVBFDiTauOff = 0
    TallyInclusiveVBFOff = 0
    TallyDiTauOff = 0
    TallyVBFDiTauORInclusiveVBFOff = 0
    TallyVBFDiTauORDiTauOff = 0
    TallyInclusiveVBFORDiTauOff = 0
    TallyTripleOROff = 0

    thirdJetBins = 2
    jet1Bins = 20
    jet2Bins = 8
    thirdJetScanRange = np.linspace(110., 120, thirdJetBins)
    jet1ScanRange = np.linspace(35.,130., jet1Bins)
    jet2ScanRange = np.linspace(35.,70., jet2Bins)

    grid = np.zeros((thirdJetBins, jet2Bins, jet1Bins))

    nEntries = tree.GetEntries()

    L1DiTauCut = float(args.L1DiTauCut)

    weight = 1

    for i in range(0, nEntries):
      tree.GetEntry(i)

      BoolPassL1VBFDiJetIsoTau = tree.passL1VBFDiJetIsoTau
      BoolPassL1VBFDiJetOR = tree.passL1VBFDiJetOR
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
      L1_Tallies = [TallyL1VBFDiJetIsoTau, TallyL1VBFDiJetOR, TallyL1DiTau, \
                 TallyL1VBFDiJetIncORIsoTau, TallyL1DiTauORIsoTau, TallyL1VBFDiJetIncORDiTau, \
                 TallyTripleOR, TallyTripleOR - TallyL1VBFDiJetIncORDiTau]

      BoolPassVBFDiTauHLT = tree.passVBFDiTauHLT and BoolPassL1VBFDiJetIsoTau
      BoolPassInclusiveVBFHLT = tree.passInclusiveVBFHLT and BoolPassL1VBFDiJetOR
      BoolPassDiTauHLT = tree.passDiTauHLT and BoolPassL1DiTau

      if (BoolPassVBFDiTauHLT): TallyVBFDiTauHLT += 1
      if (BoolPassInclusiveVBFHLT): TallyInclusiveVBFHLT += 1
      if (BoolPassDiTauHLT): TallyDiTauHLT += 1
      if (BoolPassVBFDiTauHLT or BoolPassInclusiveVBFHLT): TallyVBFDiTauORInclusiveVBFHLT += 1
      if (BoolPassVBFDiTauHLT or BoolPassDiTauHLT): TallyVBFDiTauORDiTauHLT += 1
      if (BoolPassInclusiveVBFHLT or BoolPassDiTauHLT): TallyInclusiveVBFORDiTauHLT += 1
      if (BoolPassVBFDiTauHLT or BoolPassInclusiveVBFHLT or BoolPassDiTauHLT): TallyTripleORHLT += 1
      HLT_Tallies = [TallyVBFDiTauHLT, TallyInclusiveVBFHLT, TallyDiTauHLT, \
                 TallyVBFDiTauORInclusiveVBFHLT, TallyVBFDiTauORDiTauHLT, TallyInclusiveVBFORDiTauHLT, \
                 TallyTripleORHLT, TallyTripleORHLT - TallyInclusiveVBFORDiTauHLT]

      BoolMatchVBFDiTauHLTOff = tree.matchVBFDiTauOff
      BoolMatchDiTauHLTOff = tree.matchDiTauOff 

      BoolPassVBFDiTauOff = tree.passVBFDiTauOff and BoolMatchVBFDiTauHLTOff and BoolPassVBFDiTauHLT
      BoolPassInclusiveVBFOff = tree.passInclusiveVBFOff and BoolPassInclusiveVBFHLT
      BoolPassDiTauOff = tree.passDiTauOff and BoolMatchDiTauHLTOff and BoolPassDiTauHLT


      if (BoolPassVBFDiTauOff): TallyVBFDiTauOff += 1
      if (BoolPassInclusiveVBFOff): TallyInclusiveVBFOff += 1
      if (BoolPassDiTauOff): TallyDiTauOff += 1
      if (BoolPassVBFDiTauOff or BoolPassInclusiveVBFOff): TallyVBFDiTauORInclusiveVBFOff += 1
      if (BoolPassVBFDiTauOff or BoolPassDiTauOff): TallyVBFDiTauORDiTauOff += 1
      if (BoolPassInclusiveVBFOff or BoolPassDiTauOff): TallyInclusiveVBFORDiTauOff += 1
      if (BoolPassVBFDiTauOff or BoolPassInclusiveVBFOff or BoolPassDiTauOff): TallyTripleOROff += 1
      Off_Tallies = [TallyVBFDiTauOff, TallyInclusiveVBFOff, TallyDiTauOff, \
                 TallyVBFDiTauORInclusiveVBFOff, TallyVBFDiTauORDiTauOff, TallyInclusiveVBFORDiTauOff, \
                 TallyTripleOROff, TallyTripleOROff - TallyInclusiveVBFORDiTauOff]

      if ("B" in args.metric.upper()):
        ORtoPass = BoolPassInclusiveVBFOff or BoolPassDiTauOff
      else:
        ORtoPass = BoolPassVBFDiTauOff or BoolPassInclusiveVBFOff or BoolPassDiTauOff
      if (ORtoPass):
        L1Jet1Pt   = tree.L1DiJetORJet1
        L1Jet2Pt   = tree.L1DiJetORJet2
        L1Jet3Pt   = tree.L1DiJetORJet3
        L1Mjj      = tree.L1DiJetORMjj

        OffTau1Pt  = tree.OffTau1Pt
        OffTau2Pt  = tree.OffTau2Pt
        OffJet1Pt  = tree.OffJet1Pt
        OffJet2Pt  = tree.OffJet2Pt
        OffMjj     = tree.OffMjj

        for thirdJetIndex, thirdJetEntry in enumerate(thirdJetScanRange):
          for jet2Index, jet2Entry in enumerate(jet2ScanRange):
            for jet1Index, jet1Entry in enumerate(jet1ScanRange):
              if jet2Entry > jet1Entry:
                continue

              PassL1Kinems = ( ( (L1Jet1Pt >= jet1Entry and L1Jet2Pt >= jet2Entry and L1Jet3Pt == -999) \
                         or (L1Jet1Pt >= jet1Entry and L1Jet2Pt >= jet2Entry and L1Jet3Pt >= thirdJetEntry)) \
                         and L1Mjj >= 620)

              PassOffKinems = (OffJet1Pt >= 120 and OffJet2Pt >= 40 \
                         and OffTau1Pt >= 25 and OffTau2Pt >= 25 \
                         and OffMjj >= 700)


              PassOtherTriggers = BoolPassVBFDiTauOff or BoolPassDiTauOff
              if ((PassL1Kinems and PassOffKinems) or PassOtherTriggers):
                grid[thirdJetIndex, jet2Index, jet1Index] += weight


    intJet1Pt = [int(i) for i in jet1ScanRange]
    intJet2Pt = [int(i) for i in jet2ScanRange]

    gridMetricAorB = ((grid/TallyDiTauOff) - 1)*100
    gridMetricC = ((grid/TallyVBFDiTauORDiTauOff) - 1)*100

    if ("A" in args.metric.upper() or "B" in args.metric.upper()):
      grid = gridMetricAorB
    if ("C" in args.metric.upper()):
      grid = gridMetricC

    grid[grid == -100.0] = 0
    masked_grid = np.ma.masked_equal(grid, 0, copy=False)

    gridmin = np.min(masked_grid)
    gridmax = np.max(masked_grid)
    gridmax = gridmax*1.05
  
    fig, axes = plt.subplots(1, 2)
    fig.set_size_inches(10.5, 10.5)

    # title formatting
    L1_String = "L1_DoubleJet_ZZZ_YY_DoubleJetXY_Mass_Min620"
    fig.suptitle("Gain " + L1_String)

    # plot formatting 
    for i, ax in enumerate(axes.flat):
 
      if (i == 0 or i == 1 or i == 2):
        im = ax.imshow(grid[i], vmin=gridmin, vmax=gridmax, cmap='copper', interpolation='nearest', origin='lower')
        ax.set_title("jet1or3 ≥ " + str(10*i+110), fontsize=8)
        ax.set_xlabel('jet1Pt ≥') 
        for (n,m),label in np.ndenumerate(grid[i]):
          label = "{:.1f}".format(label)
          ax.text(m, n, label,ha='center',va='center', color='white', fontsize=8)

      ax.set_ylabel('jet2Pt ≥')
  
      startx, endx = ax.get_xlim()
      starty, endy = ax.get_ylim()
  
      ax.xaxis.set_ticks(np.arange(startx+0.5, endx, 1))
      ax.xaxis.set_ticklabels(intJet1Pt)
      ax.yaxis.set_ticks(np.arange(starty+0.5, endy, 1))
      ax.yaxis.set_ticklabels(intJet2Pt)

    if (i != 0):
      ax.get_yaxis().set_visible(False)

    out_file = in_file.replace('.root','.pdf')
    plt.savefig(out_file)
    plt.tight_layout()
    plt.show()

 
