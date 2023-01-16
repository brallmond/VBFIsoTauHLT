#!/bin/bash

INPUT=../../../../../samples/VBFE_wMuTauFilters.root
OUTFILE=output_Jan_13th.txt

for i in {10..15};
do
echo "#####################################################" >> $OUTFILE;
python3 L1VBFEleEff.py -i $INPUT -L $i -s tight >> $OUTFILE;
echo "#####################################################" >> $OUTFILE;
python3 L1VBFEleEff.py -i $INPUT -L $i -s loose >> $OUTFILE;
done;

