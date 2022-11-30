# Braden Allmond, July 1st 2022, KSU
# (incomplete) tutorial: https://indico.cern.ch/event/704163/contributions/2936719/attachments/1693833/2726445/Tutorial-PyROOT.pdf
from array import array
import ROOT
from ROOT import Math, TLorentzVector
import sys
import numpy as np
import matplotlib.pyplot as plt

# usage: python3 2018 CountVBFElectron.py *.root

# prints all event numbers and events passing a particular HLT
# intended for use in easily finding rate of L1/HLT on EZB dataset
# should take between 5 and 10 minutes to run

ROOT.gROOT.SetBatch(True) # sets visual display off (i.e. no graphs/TCanvas)

files = sys.argv # all input arguments in an array
files.pop(0) # remove first arg which is always the name of the executed script
YEAR = files.pop(0) # first arg must be year, either 2018 or 2022
USELOOSEISO = files.pop(0) # sceond arg must be ture or false, true uses loose iso


def tallyPassL1s(nEvents, nBunches, scaling, passDummyL1, passDummyL1Loose, passDummyL1ORDiJetSeeds, passDummyL1LooseORDiJetSeeds, passDummyL1OREGORL1s, passDummyL1LooseOREGORL1s, passDiJetSeeds, passEGORL1, passTripleOR, passTripleLooseOR, passOverlapOR):
  print("Input Files")
  for f in files:
    print(f)
    inFileName = f
    inFile = ROOT.TFile.Open(inFileName,"READ")
    tree = inFile.Get("demo/vbf")
     
    nEvents += tree.Draw("nEvents", "nEvents>0", "goff")
    passDummyL1 += tree.Draw("nEvents", "passhltL1VBFElectron>0", "goff")
    passDummyL1Loose += tree.Draw("nEvents", "passhltL1VBFElectronLoose>0", "goff")
  
    passDummyL1ORDiJetSeeds += tree.Draw("nEvents", "passhltL1VBFElectron>0 || passhltL1VBFDiJetOR>0 || passhltL1VBFDiJetIsoTau>0", "goff")
    passDummyL1LooseORDiJetSeeds += tree.Draw("nEvents", "passhltL1VBFElectronLoose>0 || passhltL1VBFDiJetOR>0 || passhltL1VBFDiJetIsoTau>0", "goff")
    passDummyL1OREGORL1s += tree.Draw("nEvents", "passhltL1VBFElectron>0 || passHLTDummyEGORL1>0", "goff")
    passDummyL1LooseOREGORL1s += tree.Draw("nEvents", "passhltL1VBFElectronLoose>0 || passHLTDummyEGORL1>0", "goff")
  
    passDiJetSeeds += tree.Draw("nEvents", "passhltL1VBFDiJetOR>0 || passhltL1VBFDiJetIsoTau>0", "goff")
    passEGORL1 += tree.Draw("nEvents", "passHLTDummyEGORL1>0", "goff")

    passTripleOR += tree.Draw("nEvents", "passhltL1VBFElectron>0 || passhltL1VBFDiJetOR>0 || passhltL1VBFDiJetIsoTau>0 || passHLTDummyEGORL1>0", "goff")
    passTripleLooseOR += tree.Draw("nEvents", "passhltL1VBFElectronLoose>0 || passhltL1VBFDiJetOR>0 || passhltL1VBFDiJetIsoTau>0 || passHLTDummyEGORL1>0", "goff")

    passOverlapOR += tree.Draw("nEvents", "passhltL1VBFDiJetOR>0 || passhltL1VBFDiJetIsoTau>0 || passHLTDummyEGORL1>0", "goff")

  print("Total EZB Counts")  
  print("nEvents: {}".format(nEvents))
  print("passDummyL1: {}".format(passDummyL1))
  print("passDummyL1Loose: {}".format(passDummyL1Loose))
  print("-----------------------")
  print("pass DummyL1 OR other VBF Seeds: {}".format(passDummyL1ORDiJetSeeds))
  print("pass DummyL1Loose OR other VBF Seeds: {}".format(passDummyL1LooseORDiJetSeeds))
  print("pass other VBF Seeds: {}".format(passDiJetSeeds))
  print("-----------------------")
  print("pass DummyL1 exclusively not VBF: {}".format(passDummyL1ORDiJetSeeds - passDiJetSeeds))
  print("pass DummyL1Loose exclusively not VBF: {}".format(passDummyL1LooseORDiJetSeeds - passDiJetSeeds))
  print("-----------------------")
  print("pass DummyL1 OR EGOR L1s: {}".format(passDummyL1OREGORL1s))
  print("pass DummyL1Loose OR EGOR L1s: {}".format(passDummyL1LooseOREGORL1s))
  print("pass EGOR L1 seeds: {}".format(passEGORL1))
  print("-----------------------")
  print("pass DummyL1 exclusively not other EG: {}".format(passDummyL1OREGORL1s - passEGORL1))
  print("pass DummyL1Loose exclusively not other EG: {}".format(passDummyL1LooseOREGORL1s - passEGORL1))
  print("-----------------------")
  print("pass Triple OR: {}".format(passTripleOR))
  print("pass TripleLoose OR: {}".format(passTripleLooseOR))
  print("pass overlapOR: {}".format(passOverlapOR))
  print("pass DummyL1 exclusively: {}".format(passTripleOR - passOverlapOR))
  print("pass DummyLooseL1 exclusively: {}".format(passTripleLooseOR - passOverlapOR))
  print("-----------------------")
  print("Rate Constants")
  print("nBunches = {}".format(nBunches))
  print("revolution frequency = {} Hz".format(revfreq))
  print("nBunches*rev.freq. = {} Hz".format(constFactor))
  rateFactor = constFactor/nEvents
  print("Rate Factor = nBunches*rev.freq./nEvents = {:.3f}".format(rateFactor))
  scaledRateFactor = rateFactor*scaling
  print("Scaled Rate Factor = {:.3f}".format(scaledRateFactor))
  print("Scaled Rate = Scaled Rate Factor * #Events Passing")

  return scaledRateFactor

def plotVariable():

  for f in files:
    inFileName = f
    inFile = ROOT.TFile.Open(inFileName, "READ")
    tree = inFile.Get("demo/vbf")
    elePt = ROOT.std.vector('float')()
    tree.SetBranchAddress("hltL1VBFElectronLoose_ePt", elePt)

def calcMjjAndJetIndices(inputJets):

  for i in range(jetPt.size()):
    TJet_ = ROOT.TLorentzVector(jetPt[i], jetEta[i], jetPhi[i], jetEnergy[i])
    inputTJets.append(TJet_)

  sizeTJets = len(inputTJets)
  if (sizeTJets > 1):
    mjj = 0 
    mjjTemp = 0
    leadingJet = -1
    subleadingJet = -1
    for j in range(sizeTJets):
      for k in range(sizeTJets):
        if (k > j):
          tempJet1 = inputTJets[j]
          tempJet2 = inputTJets[k]
          mjjTemp = (tempJet1 + tempJet2).M()
          #print(inputTJets[j].M())
          if (mjjTemp > mjj):
            mjj = mjjTemp
            leadingJet = j
            subleadingJet = k

    leadingJetPt = inputTJets[leadingJet].Pt()
    subleadingJetPt = inputTJets[subleadingJet].Pt()


def varyL1(electronScanRange_, jetScanRange_, mjjScanRange_, weight_, looseTrue):

  electronScanRange = electronScanRange_
  jetScanRange = jetScanRange_ 
  mjjScanRange = mjjScanRange_ 
  weight = weight_
  gridTotal = np.zeros((3,11,11))
  gridOverlap = np.zeros((3,11,11))

  eLazyPt = []
  mjjLazy = []

  countPassLowestL1 = 0
  countPassOtherVBFOR = 0
  countPassEGORL1 = 0

  print("Input Files")
  for f in files:
    print(f)
    inFileName = f
    inFile = ROOT.TFile.Open(inFileName,"READ")
    tree = inFile.Get("demo/vbf")

    passL1 = array('i', [0])
    passIncVBF = array('i', [0])
    passVBFIsoTau = array('i', [0])
    passEGORL1Arr = array('i', [0])

    jetPt = ROOT.std.vector('float')()
    jetEta = ROOT.std.vector('float')()
    jetPhi = ROOT.std.vector('float')()
    jetEnergy = ROOT.std.vector('float')()
    elePt = ROOT.std.vector('float')()

    tree.SetBranchAddress("passhltL1VBFDiJetOR", passIncVBF)
    tree.SetBranchAddress("passhltL1VBFDiJetIsoTau", passVBFIsoTau)
    tree.SetBranchAddress("passHLTDummyEGORL1", passEGORL1Arr)

    if (looseTrue):
      tree.SetBranchAddress("passhltL1VBFElectronLoose", passL1)
      tree.SetBranchAddress("hltL1VBFElectronLoose_jPt", jetPt)
      tree.SetBranchAddress("hltL1VBFElectronLoose_jEta", jetEta)
      tree.SetBranchAddress("hltL1VBFElectronLoose_jPhi", jetPhi)
      tree.SetBranchAddress("hltL1VBFElectronLoose_jEnergy", jetEnergy)
      tree.SetBranchAddress("hltL1VBFElectronLoose_ePt", elePt)
      print("Using LooseIso Branches")
    if (not looseTrue): 
      tree.SetBranchAddress("passhltL1VBFElectron", passL1)
      tree.SetBranchAddress("hltL1VBFElectron_jPt", jetPt)
      tree.SetBranchAddress("hltL1VBFElectron_jEta", jetEta)
      tree.SetBranchAddress("hltL1VBFElectron_jPhi", jetPhi)
      tree.SetBranchAddress("hltL1VBFElectron_jEnergy", jetEnergy)
      tree.SetBranchAddress("hltL1VBFElectron_ePt", elePt)
      print("Not using LooseIso Branches")


    for entry in range(tree.GetEntriesFast()):
    #for entry in range(5000):
      #print(i)
      tree.GetEntry(entry)
      passOtherVBFOR = 0
      passEGORL1 = 0
      if (passIncVBF[0] == 1 or passVBFIsoTau[0] == 1):
        passOtherVBFOR = 1
        countPassOtherVBFOR += 1

      if (passEGORL1Arr[0] == 1): 
        passEGORL1 = 1
        countPassEGORL1 += 1

      if passL1[0] == 1:
        # print("Entry {}".format(entry))
        # find highest mjj pair
        inputTJets = []
        for i in range(jetPt.size()):

          TJet_ = ROOT.TLorentzVector(jetPt[i], jetEta[i], jetPhi[i], jetEnergy[i])
          inputTJets.append(TJet_)

        sizeTJets = len(inputTJets)
        if (sizeTJets > 1):
          mjj = 0 
          mjjTemp = 0
          leadingJet = -1
          subleadingJet = -1
          for j in range(sizeTJets):
            for k in range(sizeTJets):
              if (k > j):
                tempJet1 = inputTJets[j]
                tempJet2 = inputTJets[k]
                mjjTemp = (tempJet1 + tempJet2).M()
                #print(inputTJets[j].M())
                if (mjjTemp > mjj):
                  mjj = mjjTemp
                  leadingJet = j
                  subleadingJet = k

        leadingJetPt = inputTJets[leadingJet].Pt()
        subleadingJetPt = inputTJets[subleadingJet].Pt()

        electronPt = elePt[0]

        #eLazyPt.append(electronPt)
        #mjjLazy.append(mjj)

        #print(eLazyPt)
        #print(mjjLazy)

        #print("===========")
        #print("leadingJetPt    : {:.1f}".format(leadingJetPt))
        #print("subleadingJetPt : {:.1f}".format(subleadingJetPt))
        #print("mjj             : {:.1f}".format(mjj))
        #print("electronPt      : {:.1f}".format(electronPt))
        #print("[{:.1f},{:.1f},{:.1f},{:.1f}]".format(leadingJetPt,subleadingJetPt,mjj,electronPt))

        for eleIndex, eleEntry in enumerate(electronScanRange):
          for jetIndex, jetEntry in enumerate(jetScanRange):
            for mjjIndex, mjjEntry in enumerate(mjjScanRange):

                #if not ((electronPt >= eleEntry) and (leadingJetPt >= jetEntry and subleadingJetPt >= jetEntry) and (mjj >= mjjEntry)):
                  #print("[{:.1f},{:.1f},{:.1f},{:.1f}]".format(leadingJetPt,subleadingJetPt,mjj,electronPt))
                  #print(sizeTJets)
                #countPassLowestL1 += 1

              if ((electronPt >= eleEntry) and (leadingJetPt >= jetEntry and subleadingJetPt >= jetEntry) and (mjj >= mjjEntry)):
                gridTotal[eleIndex, jetIndex, mjjIndex] += weight
                gridOverlap[eleIndex, jetIndex, mjjIndex] += weight

                if (eleEntry == 10 and jetEntry == 30 and mjjEntry == 300):
                  countPassLowestL1 += 1

                if (passOtherVBFOR or passEGORL1):
                  gridOverlap[eleIndex, jetIndex, mjjIndex] -= weight


  print("Sanity check, nEvents passing lowest simulated L1 (known discrepancy): {}".format(countPassLowestL1))
  print("Sanity check, nEvents passing OR of other VBF L1s: {}".format(countPassOtherVBFOR))
  print("Sanity check, nEvents passing OR of other EG L1s:  {}".format(countPassEGORL1))

  #neweLazyPt = []
  #for i in range(len(eLazyPt)):
    #if (mjjLazy[i]>300):
      #neweLazyPt.append(eLazyPt[i])

  #lazy = True
  #if (lazy):
    #fig, ax = plt.subplots()
    #ax.plot(eLazyPt, mjjLazy)
    #ax.plot(electronScanRange, eLazyPt)
    #ax.hist(neweLazyPt, 20)
    #plt.show()

 

  return gridTotal, gridOverlap

if __name__ == "__main__":

  nEvents = 0
  passDummyL1 = 0
  passDummyL1Loose = 0
  passDummyL1ORDiJetSeeds = 0
  passDummyL1LooseORDiJetSeeds = 0
  passDummyL1OREGORL1s = 0
  passDummyL1LooseOREGORL1s = 0
  passDiJetSeeds = 0
  passEGORL1 = 0
  passTripleOR = 0
  passTripleLooseOR = 0
  passOverlapOR = 0

  EZBinfo = {"2018" : [2736, 2.0/1.6],
             "2022E" : [2448, 2.0/1.3],
             "2022F" : [2450, 2.0/1.8]}

  nBunches = EZBinfo[YEAR][0]
  revfreq = 11245.6 # Hz
  constFactor = nBunches*revfreq
  scaling = EZBinfo[YEAR][1]

  print(YEAR, nBunches, scaling)

  testRate = True
  rateFactor = 0
  if (testRate):
    rateFactor = tallyPassL1s(nEvents, nBunches, scaling, passDummyL1, passDummyL1Loose, passDummyL1ORDiJetSeeds, passDummyL1LooseORDiJetSeeds, passDummyL1OREGORL1s, passDummyL1LooseOREGORL1s, passDiJetSeeds, passEGORL1, passTripleOR, passTripleLooseOR, passOverlapOR)

  electronScanRange = np.linspace(10.,14.,3)
  jetScanRange = np.linspace(30.,50.,11)
  mjjScanRange = np.linspace(300.,500.,11)

  if (USELOOSEISO == "True"): USELOOSEISO = True
  elif (USELOOSEISO == "False"): USELOOSEISO = False
  else: 
    print("second argument must be True or False. Exiting...")
    sys.exit()

  useLooseIso = USELOOSEISO
  gridOutTotal, gridOutOvRm = varyL1(electronScanRange, jetScanRange, mjjScanRange, rateFactor, useLooseIso)

  plot = True
  if (plot):
    intJetPt = [int(i) for i in jetScanRange]
    intMjj = [int(i) for i in mjjScanRange]
  
    gridmax = np.max(gridOutTotal)
    gridmax = gridmax*1.2
  
    fig, axes = plt.subplots(2, 3)
    fig.set_size_inches(10.5, 10.5)
  
    for i, ax in enumerate(axes.flat):

 
      if (i == 0 or i == 1 or i == 2):
        im = ax.imshow(gridOutTotal[i], vmin=0, vmax=gridmax, cmap='copper', interpolation='nearest', origin='lower')
        ax.set_title("electronPt >= " + str(2*(i)+10), fontsize=8)
        for (n,m),label in np.ndenumerate(gridOutTotal[i]):
          label = "{:.1f}".format(label/1000.)
          ax.text(m, n, label,ha='center',va='center', color='white', fontsize=6)

      if (i == 3 or i == 4 or i == 5):
        im = ax.imshow(gridOutOvRm[i-3], vmin=0, vmax=gridmax, cmap='copper', interpolation='nearest', origin='lower')
        ax.set_xlabel('jetPt >=')
        for (n,m),label in np.ndenumerate(gridOutOvRm[i-3]):
          label = "{:.1f}".format(label/1000.)
          ax.text(m, n, label,ha='center',va='center', color='white', fontsize=6)


      if (i == 2):
        ax.text(1.05, 0.55, "Total", transform=ax.transAxes, fontsize=12,
          rotation=-90)

      if (i == 5):
        ax.text(1.05, 0.25, "Overlap Removed", transform=ax.transAxes, fontsize=12,
          rotation=-90)

      ax.set_ylabel('mjj >=')
  
      start, end = ax.get_xlim()
  
      ax.xaxis.set_ticks(np.arange(start+0.5, end, 1))
      ax.xaxis.set_ticklabels(intJetPt)
      ax.yaxis.set_ticks(np.arange(start+0.5, end, 1))
      ax.yaxis.set_ticklabels(intMjj)

      if (i == 1 or i == 2 or i == 4 or i == 5):
        ax.get_yaxis().set_visible(False)
       
  
  
    plt.savefig('output.pdf')
    plt.show()

   



























