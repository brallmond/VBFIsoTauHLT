`git clone https://github.com/brallmond/VBFIsoTauHLT.git`


If you need a newer CMSSW release than 12_4_0, use this page

https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideGlobalHLT


These three repos were used in the past for various activities (see Corrections directory in main repo)

`git cms-addpkg HLTrigger/Configuration`

`git cms-addpkg RecoTauTag/HLTProducers`

`git cms-addpkg L1Trigger/L1TGlobal`


build everything by running the following command in src.
`scram b -j 8`

Timing

If you need to run timing and customize it, download this repo

`git clone --recursive https://gitlab.cern.ch/cms-tsg/steam/timing.git`
