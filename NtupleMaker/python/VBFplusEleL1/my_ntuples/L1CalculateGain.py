import ROOT
from L1VBFEle_functions import print_formatted_labels_and_values
from rateDictionary import rateDictionary
import numpy as np
import matplotlib.pyplot as plt


if __name__ == "__main__":
    from argparse import ArgumentParser
    parser = ArgumentParser()
    parser.add_argument('--in_file', '-i', required=True, action='store', help='input file')

    args = parser.parse_args()
    in_file = args.in_file

    ROOT.TH1.SetDefaultSumw2()

    new_file = ROOT.TFile.Open(in_file, "READ") 
    tree = new_file.Get("outtree")

    electronBins = 3
    mjjBins = 11
    jetBins = 11

    OffEleInc = 3
    OffMjjInc = 100
    OffJetInc = 15

    electronScanRange = np.linspace(10., 14., electronBins)
    mjjScanRange = np.linspace(300., 500., mjjBins)
    jetScanRange = np.linspace(30., 50., jetBins)

    grid = np.zeros((electronBins, mjjBins, jetBins))

    TallyVBFEleTau = 0
    TallyEleTau = 0
    TallySingleEle = 0
    TallyVBFEleTauOREleTau = 0
    TallyVBFEleTauORSingleEle = 0
    TallyEleTauORSingleEle = 0
    TallyTripleOR = 0

    nEntries = tree.GetEntries()

    weight = 1


    # print rate info and unpure/pure rate
    for i in range(0, nEntries):
      tree.GetEntry(i)

      BoolPassVBFEleTau = tree.passVBFEleTauOff
      BoolPassEleTau = tree.passEleTauOff
      BoolPassSingleEle = tree.passSingleEleOff

      if (BoolPassVBFEleTau): TallyVBFEleTau += 1
      if (BoolPassEleTau): TallyEleTau += 1
      if (BoolPassSingleEle): TallySingleEle += 1

      if (BoolPassVBFEleTau or BoolPassEleTau): TallyVBFEleTauOREleTau += 1
      if (BoolPassVBFEleTau or BoolPassSingleEle): TallyVBFEleTauORSingleEle += 1
      if (BoolPassEleTau or BoolPassSingleEle): TallyEleTauORSingleEle += 1

      if (BoolPassVBFEleTau or BoolPassEleTau or BoolPassSingleEle): TallyTripleOR += 1

      if (BoolPassVBFEleTau or BoolPassEleTau or BoolPassSingleEle):
        OffElePt   = tree.OffElePt
        OffJet1Pt  = tree.OffJet1Pt
        OffJet2Pt  = tree.OffJet2Pt
        OffMjj     = tree.OffMjj
        OffTauPt   = tree.OffTauPt

        L1ElePt   = tree.L1ElePt
        L1Jet1Pt  = tree.L1Jet1Pt
        L1Jet2Pt  = tree.L1Jet2Pt
        L1Mjj     = tree.L1Mjj

        for eleIndex, eleEntry in enumerate(electronScanRange):
          for mjjIndex, mjjEntry in enumerate(mjjScanRange):
            for jetIndex, jetEntry in enumerate(jetScanRange):

              PassL1Kinems = ((L1ElePt >= eleEntry) \
                      and (L1Jet1Pt >= jetEntry and L1Jet2Pt >= jetEntry) \
                      and (L1Mjj >= mjjEntry))

              PassOffKinems = ((OffElePt >= (eleEntry + OffEleInc)) \
                      and (OffJet1Pt >= (jetEntry + OffJetInc) and OffJet2Pt >= (jetEntry + OffJetInc)) \
                      and (OffMjj >= (mjjEntry + OffMjjInc)) \
                      and (OffTauPt >= 30))

              PassOtherTriggers = BoolPassEleTau or BoolPassSingleEle
              if ((PassL1Kinems and PassOffKinems) or PassOtherTriggers):
                grid[eleIndex, mjjIndex, jetIndex] += weight

    Tallies = [TallyVBFEleTau, TallyEleTau, TallySingleEle,\
               TallyVBFEleTauOREleTau, TallyVBFEleTauORSingleEle, TallyEleTauORSingleEle,
               TallyTripleOR, TallyTripleOR - TallyEleTauORSingleEle]
    labels = ["VBFEleTau (1)", "EleTau (2)", "SingleEle (3)", "1OR2", "1OR3", "2OR3", "TripleOR", "UniqueEleTau"]
    for index, label in enumerate(labels):
      print(f"{label:15}, {Tallies[index]:7}")


    intJetPt = [int(i) for i in jetScanRange]
    intMjj = [int(i) for i in mjjScanRange]
  
    gridmin = np.min(grid)
    gridmax = np.max(grid)
    gridmax = gridmax*1.05
  
    fig, axes = plt.subplots(1, 3)
    fig.set_size_inches(10.5, 10.5)

    # title formattin
    loose_or_tight = "Neither"
    if ("LOOSE" in in_file.upper()):
      loose_or_tight = "Loose"
    elif ("TIGHT" in in_file.upper() or "_ISO" in in_file.upper()):
      loose_or_tight = "Tight"
    else:
      print("Change in-filename to contain tight or loose, reflecting the sample it was made from.")
    L1_String = "L1_VBF_DoubleJetXX_ Mass_MinYYY_" + loose_or_tight + "IsoEGZZ"
    fig.suptitle("Gain " + L1_String)


    # plot formatting 
    for i, ax in enumerate(axes.flat):
 
      if (i == 0 or i == 1 or i == 2):
        im = ax.imshow(grid[i], vmin=gridmin, vmax=gridmax, cmap='copper', interpolation='nearest', origin='lower')
        ax.set_title("electronPt ≥ " + str(2*(i)+10), fontsize=8)
        ax.set_xlabel('jetPt ≥')
        for (n,m),label in np.ndenumerate(grid[i]):
          label = "{:.1f}".format( (label/TallyEleTauORSingleEle - 1)*100)
          ax.text(m, n, label,ha='center',va='center', color='white', fontsize=6)

      ax.set_ylabel('mjj ≥')
  
      startx, endx = ax.get_xlim()
      starty, endy = ax.get_ylim()
  
      ax.xaxis.set_ticks(np.arange(startx+0.5, endx, 1))
      ax.xaxis.set_ticklabels(intJetPt)
      ax.yaxis.set_ticks(np.arange(starty+0.5, endy, 1))
      ax.yaxis.set_ticklabels(intMjj)

      if (i == 1 or i == 2):
        ax.get_yaxis().set_visible(False)

    out_file = in_file.replace('.root','.pdf')
    plt.savefig(out_file)
    plt.show()

 
