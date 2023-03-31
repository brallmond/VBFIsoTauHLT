To download this repo
`git clone https://github.com/brallmond/VBFIsoTauHLT.git`


For any questions about HLT confs in CMSSW use [this twiki](https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideGlobalHLT)

## use an edited L1 menu with conf file
In /src/ do the following

`git cms-addpkg L1Trigger/L1TGlobal`

`mkdir -p L1Trigger/L1TGlobal/data/Luminosity/startup`

`cp <L1 Menu> L1Trigger/L1TGlobal/data/Luminosity/startup`

## modify HLT module behavio locally and in crab jobs
Sometimes packages need to be added so HLT modules can be modified. These are the most common that I've needed to add.

`git cms-addpkg HLTrigger/Configuration`

`git cms-addpkg RecoTauTag/HLTProducers`


# Timing #
If you need to run timing and customize it, download this repo

`git clone --recursive https://gitlab.cern.ch/cms-tsg/steam/timing.git`
