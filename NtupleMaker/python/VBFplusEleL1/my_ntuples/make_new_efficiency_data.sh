#!/bin/bash

INPUT=../../../../../samples/VBFE_wMuTauFilters.root
OUTFILE=output_2ndpass_loose_Jan_27th.txt

for i in {1..5};
do
echo "#####################################################" >> $OUTFILE;
python3 L1VBFEleEff.py -i $INPUT -r "NOTRATE" -L $i -s loose >> $OUTFILE;
#echo "#####################################################" >> $OUTFILE;
#python3 L1VBFEleEff.py -i $INPUT -L $i -s loose >> $OUTFILE;
done;

