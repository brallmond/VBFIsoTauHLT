#!/bin/bash

INPUT=VBFE_wMuTauFilters.root
LABEL=new_matching

python3 L1VBFEleEff.py -i ../../../samples/$INPUT -L 7 -o "$LABEL"_Loose_30_320_10.root
python3 L1VBFEleEff.py -i ../../../samples/$INPUT -L 6 -o "$LABEL"_Tight_30_320_10.root
