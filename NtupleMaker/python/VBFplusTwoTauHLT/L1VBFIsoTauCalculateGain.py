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
    parser.add_argument('-HI', '--higher_VBFDiJetOR', dest='higher_VBFDiJetOR', default='n', action='store',
                        help='emulate the higher L1VBFDiJetOR (default no)')



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

    isoTauBins = 3
    mjjBins = 4
    jetBins = 11
    isoTauScanRange = np.linspace(45.,55., isoTauBins)
    mjjScanRange = np.linspace(450.,600., mjjBins)
    jetScanRange = np.linspace(35.,55., jetBins)

    grid = np.zeros((isoTauBins, mjjBins, jetBins))

    nEntries = tree.GetEntries()

    L1DiTauCut = float(args.L1DiTauCut)

    emulate_higher_VBFDiJetOR = "y" in args.higher_VBFDiJetOR
    if (emulate_higher_VBFDiJetOR):
      DoubleJetCut = 45
      LeadingL1JetCut = 120
    else:
      DoubleJetCut = 35
      LeadingL1JetCut = 110

    weight = 1

    for i in range(0, nEntries):
      tree.GetEntry(i)

      BoolPassL1VBFDiJetIsoTau = tree.passL1VBFDiJetIsoTau
      BoolPassL1VBFDiJetOR = tree.passL1VBFDiJetOR
      if (BoolPassL1VBFDiJetOR):
        passing_ = tree.L1DiJetORMjj >= 620 \
               and ( (tree.L1DiJetORJet1 >= DoubleJetCut and tree.L1DiJetORJet2 >= DoubleJetCut \
               and tree.L1DiJetORJet3 >= LeadingL1JetCut)\
               or (tree.L1DiJetORJet1 >= LeadingL1JetCut and tree.L1DiJetORJet2 >= DoubleJetCut \
               and tree.L1DiJetORJet3 == -999.) )
        BoolPassL1VBFDiJetOR = passing_

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
        ORtoPass = BoolPassVBFDiTauOff or BoolPassDiTauOff
      else:
        ORtoPass = BoolPassVBFDiTauOff or BoolPassInclusiveVBFOff or BoolPassDiTauOff
      if (ORtoPass):
        L1IsoTauPt = tree.L1IsoTauPt
        L1Jet1Pt   = tree.L1Jet1Pt
        L1Jet2Pt   = tree.L1Jet2Pt
        L1Mjj      = tree.L1Mjj
        OffTau1Pt  = tree.OffTau1Pt
        OffTau2Pt  = tree.OffTau2Pt
        OffJet1Pt  = tree.OffJet1Pt
        OffJet2Pt  = tree.OffJet2Pt
        OffMjj     = tree.OffMjj

        for tauIndex, tauEntry in enumerate(isoTauScanRange):
          for mjjIndex, mjjEntry in enumerate(mjjScanRange):
            for jetIndex, jetEntry in enumerate(jetScanRange):

              PassL1Kinems = ((L1IsoTauPt >= tauEntry) \
                         and (L1Jet1Pt >= jetEntry and L1Jet2Pt >= jetEntry) \
                         and (L1Mjj >= mjjEntry))
              PassOffKinems = (OffJet1Pt >= 45 and OffJet2Pt >= 45 \
                         and OffTau1Pt >= 50 and OffTau2Pt >= 25 \
                         and OffMjj >= 600)


              PassOtherTriggers = BoolPassInclusiveVBFOff or BoolPassDiTauOff
              if ((PassL1Kinems and PassOffKinems) or PassOtherTriggers):
                grid[tauIndex, mjjIndex, jetIndex] += weight


    intJetPt = [int(i) for i in jetScanRange]
    intMjj = [int(i) for i in mjjScanRange]

    gridMetricAorB = ((grid/TallyDiTauOff) - 1)*100
    gridMetricC = ((grid/TallyInclusiveVBFORDiTauOff) - 1)*100

    if ("A" in args.metric.upper() or "B" in args.metric.upper()):
      grid = gridMetricAorB
    if ("C" in args.metric.upper()):
      grid = gridMetricC

    gridmin = np.min(grid)
    gridmax = np.max(grid)
    gridmax = gridmax*1.05
  
    fig, axes = plt.subplots(1, 3)
    fig.set_size_inches(10.5, 10.5)

    # title formatting
    L1_String = "L1_DoubleJetXX_ Mass_MinYYY_IsoTauZZ"
    fig.suptitle("Gain " + L1_String)

    # plot formatting 
    for i, ax in enumerate(axes.flat):
 
      if (i == 0 or i == 1 or i == 2):
        im = ax.imshow(grid[i], vmin=gridmin, vmax=gridmax, cmap='copper', interpolation='nearest', origin='lower')
        ax.set_title("isoTauPt ≥ " + str(5*(i)+45), fontsize=8)
        ax.set_xlabel('jetPt ≥') 
        for (n,m),label in np.ndenumerate(grid[i]):
          label = "{:.1f}".format(label)
          ax.text(m, n, label,ha='center',va='center', color='white', fontsize=8)

      ax.set_ylabel('mjj ≥')
  
      startx, endx = ax.get_xlim()
      starty, endy = ax.get_ylim()
  
      ax.xaxis.set_ticks(np.arange(startx+0.5, endx, 1))
      ax.xaxis.set_ticklabels(intJetPt)
      ax.yaxis.set_ticks(np.arange(starty+0.5, endy, 1))
      ax.yaxis.set_ticklabels(intMjj)

    if (i != 0):
      ax.get_yaxis().set_visible(False)

    out_file = in_file.replace('.root','.pdf')
    plt.savefig(out_file)
    plt.tight_layout()
    plt.show()

 
