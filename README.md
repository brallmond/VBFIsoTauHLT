#Updated for CMSSW_12_3_0
Fresh start.

use this page to get the latest release
https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideGlobalHLT

Might need the next three repos for various activities
`git cms-addpkg HLTrigger/Configuration`
`git cms-addpkg RecoTauTag/HLTProducers`
`git cms-addpkg L1Trigger/L1TGlobal`

This is the repo that I work from
`git clone https://github.com/brallmond/VBFIsoTauHLT.git`

Finally, build everything by running the following command in src.
`scram b -j 8`

#Timing
If you need to run timing and customize it, download this repo
`git clone --recursive https://gitlab.cern.ch/cms-tsg/steam/timing.git`
