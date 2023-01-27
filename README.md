To download this repo
`git clone https://github.com/brallmond/VBFIsoTauHLT.git`


If you need a newer CMSSW release than 12_4_0, use [this twiki](https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideGlobalHLT)


These three repos were used in the past for various activities (see `NtupleMaker/notes/CorrectionFiles` directory)

`git cms-addpkg HLTrigger/Configuration`

`git cms-addpkg RecoTauTag/HLTProducers`

## use an edited L1 menu with conf file
In /src/ do the following

`git cms-addpkg L1Trigger/L1TGlobal`

`mkdir L1Trigger/L1TGlobal/data/Luminosity/startup`

`cp <L1 Menu> L1Trigger/L1TGlobal/data/Luminosity/startup`



Build everything by running the following command in src.
`scram b -j 8`

# Timing #

If you need to run timing and customize it, download this repo

`git clone --recursive https://gitlab.cern.ch/cms-tsg/steam/timing.git`
