import ROOT

def match_L1_to_Offline(L1Ele, L1Jet1, L1Jet2, OffEle, OffJet1, OffJet2):
  """ Use dR cone to match preselected L1 objects to preselected Offline objects and return True.
      Return false if not all L1 objects can be matched."""
  match = False

  matchL1OffJetsNormal = (ROOT.TLorentzVector.DeltaR(OffJet1, L1Jet1) < 0.5 and ROOT.TLorentzVector.DeltaR(OffJet2, L1Jet2) < 0.5)
  matchL1OffJetsSwapped = (ROOT.TLorentzVector.DeltaR(OffJet1, L1Jet2) < 0.5 and ROOT.TLorentzVector.DeltaR(OffJet2, L1Jet1) < 0.5)
  matchL1OffJets = matchL1OffJetsNormal or matchL1OffJetsSwapped
  matchL1OffEle = (ROOT.TLorentzVector.DeltaR(OffEle, L1Ele) < 0.5)

  match = matchL1OffJets and matchL1OffEle

  return match


def match_Offline_to_L1(L1Eles, L1Jets, OffEle, OffJet1, OffJet2):
  """ Use dR cone to match preselected Offline objects to any available L1 object and return True.
      Return False if not all L1 objects can be matched.
      Also returns L1Indices, which are 999 if not matched to an Offline object
  """
  match = False

  #L1Jet1Index, L1Jet2Index, dummyL1Mjj = highestMjjPair(L1Jets)

  #matchJet = [i for i in range(len(L1Jets))
  #         if (ROOT.TLorentzVector.DeltaR(OffJet1, L1Jets[i]) < 0.5 or
  #             ROOT.TLorentzVector.DeltaR(OffJet2, L1Jets[i]) < 0.5) ]

  listOffJet1dRs = []
  listOffJet2dRs = []
  for i in range(len(L1Jets)):
    OffJet1dR = ROOT.TLorentzVector.DeltaR(OffJet1, L1Jets[i])
    listOffJet1dRs.append(OffJet1dR)

    OffJet2dR = ROOT.TLorentzVector.DeltaR(OffJet2, L1Jets[i])
    listOffJet2dRs.append(OffJet2dR)

  L1Jet1Index = L1Jet2Index = 999
  if (len(listOffJet1dRs) >= 1 and len(listOffJet2dRs) >= 1):
    minListOffJet1dRs = min(listOffJet1dRs)
    minListOffJet2dRs = min(listOffJet2dRs)

    if minListOffJet1dRs < 0.5:
      L1Jet1Index = listOffJet1dRs.index(minListOffJet1dRs)
    if minListOffJet2dRs < 0.5:
      L1Jet2Index = listOffJet2dRs.index(minListOffJet2dRs)

  L1EleIndex = 999
  listOffEledRs = [ROOT.TLorentzVector.DeltaR(OffEle, L1Eles[i]) for i in range(len(L1Eles))]
  if (len(listOffEledRs) >= 1):
    minListOffEledRs = min(listOffEledRs) # variable names are a mess here
    if (minListOffEledRs < 0.5):
      L1EleIndex = listOffEledRs.index(minListOffEledRs)

  #if (L1Jet1Index in matchJet and L1Jet2Index in matchJet and len(matchEle) >= 1): match = True
  if (L1Jet1Index != 999 and L1Jet2Index != 999 and L1EleIndex != 999): match = True

  L1Indices = [L1EleIndex, L1Jet1Index, L1Jet2Index]

  return match, L1Indices
 

def highestMjjPair(inObjs):
  '''
  Takes in an array of TLorentzVector objects
  Returns the array indices of the highest mjj pair of objects and the mjj
    
    Parameters:
      inObjs - an array of TLorentzVectors

    Returns:
      leadingJetIndex - the array index of the higher pt jet in the mjj pair
      subleadingJetIndex - the array index of the lower pt jet in the mjj pair
      mjj - the dijet mass of the highest mjj pair of the inObjs
  '''
  nObjs = len(inObjs) 

  mjj = 0 
  mjjTemp = 0
  leadingJetIndex = 999#-1
  subleadingJetIndex = 999#-1

  for j in range(nObjs):
    for k in range(nObjs):
      if (k > j):
        tempJet1 = inObjs[j]
        tempJet2 = inObjs[k]
        mjjTemp = (tempJet1 + tempJet2).M()
        if (mjjTemp > mjj):
          mjj = mjjTemp
          leadingJetIndex = j
          subleadingJetIndex = k

  return leadingJetIndex, subleadingJetIndex, mjj


def fillWithTVecs(branchPt, branchEta, branchPhi, branchEnergy, arrayIDs=None):
  '''
  Takes in four kinematic branch names
  Returns an array of TLorentzVector objects filled with the kinematic info.
  Optionally skips members of the input branches if present in 'arrayIDs'.
  '''
  if arrayIDs is None:
    arrayIDs = range(len(branchPt))

  outputTVecs = []
  for i in arrayIDs:
    tempVec = ROOT.TLorentzVector()
    tempVec.SetPtEtaPhiE(branchPt[i], branchEta[i], branchPhi[i], branchEnergy[i])
    #print(branchPt[i], branchEta[i], branchPhi[i], branchEnergy[i])
    outputTVecs.append(tempVec)
  return outputTVecs

def fillWithTVecsNoEnergyBranch(branchPt, branchEta, branchPhi, arrayIDs=None):
  '''
  Takes in four kinematic branch names
  Returns an array of TLorentzVector objects filled with the kinematic info.
  Optionally skips members of the input branches if present in 'arrayIDs'.
  '''
  if arrayIDs is None:
    arrayIDs = range(len(branchPt))

  outputTVecs = []
  for i in arrayIDs:
    tempVec = ROOT.TLorentzVector()
    tempVec.SetPtEtaPhiM(branchPt[i], branchEta[i], branchPhi[i], 0)
    #print(branchPt[i], branchEta[i], branchPhi[i])
    outputTVecs.append(tempVec)
  return outputTVecs


def print_formatted_labels_and_values(labels: list, values: list, double_space: bool=False, five_values: bool=False,\
                                      three_values: bool=False):
    print("#"*40)
    if three_values:
        print(f"{labels[0]:<10} : {labels[1]:<10} : {labels[2]:<10}")
        print(f"{values[0]:<10} : {values[1]:<10} : {values[2]:<10}")
    elif five_values:
        print(f"{labels[0]:<10} : {labels[1]:<10} : {labels[2]:<10} : {labels[3]:<10} : {labels[4]: <20}")
        print(f"{values[0]:<10} : {values[1]:<10} : {values[2]:<10} : {values[3]:<10} : {values[4]: <20}")
    elif double_space:
        print(f"{labels[0]:<20} : {labels[1]:<20} : {labels[2]:<20} : {labels[3]:<20}")
        print(f"{values[0]:<20} : {values[1]:<20} : {values[2]:<20} : {values[3]:<20}")
    elif double_space and five_values:
        print(f"{labels[0]:<20} : {labels[1]:<20} : {labels[2]:<20} : {labels[3]:<20} : {labels[4]: <20}")
        print(f"{values[0]:<20} : {values[1]:<20} : {values[2]:<20} : {values[3]:<20} : {values[4]: <20}")
    else:
        print(f"{labels[0]:<10} : {labels[1]:<10} : {labels[2]:<10} : {labels[3]:<10}")
        print(f"{values[0]:<10} : {values[1]:<10} : {values[2]:<10} : {values[3]:<10}")

def matchHLTOff(HLTObjectContainer, OfflineObject):
  matchList = [i for i in range(len(HLTObjectContainer))
               if ROOT.TLorentzVector.DeltaR(OfflineObject, HLTObjectContainer[i]) < 0.5]
  if (len(matchList) > 0): return True
  else: return False


