#!/bin/bash
FILE=$1

sed -i 's/input = cms.untracked.int32( 100 )/input = cms.untracked.int32( -1 )/' $FILE;
sed -i "s/_customInfo\['maxEvents' \]=  100/_customInfo\['maxEvents' \]=  -1/" $FILE;
