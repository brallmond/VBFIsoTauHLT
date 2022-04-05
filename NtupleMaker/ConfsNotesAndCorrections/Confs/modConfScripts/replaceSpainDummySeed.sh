#!/bin/bash
FILE=$1

sed -i -e 's/L1SeedsLogicalExpression = cms.string( \"L1_DoubleIsoTau32er2p1\" ),/L1SeedsLogicalExpression = cms.string( \"L1_DoubleIsoTau26er2p1_Jet55_RmOvlp_dR0p5\" ),/' $FILE;

