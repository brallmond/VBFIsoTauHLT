#!/bin/bash
FILE=$1

# using these slides for customisations
# https://indico.cern.ch/event/1138330/contributions/4775936/attachments/2408929/4121671/TSG_Weekly_16Mar22%20%282%29.pdf

echo "process.hltParticleFlowRecHitHBHE.producers[0].qualityTests[0].name = "PFRecHitQTestHCALThresholdVsDepth"
del process.hltParticleFlowRecHitHBHE.producers[0].qualityTests[0].threshold" > $FILE
