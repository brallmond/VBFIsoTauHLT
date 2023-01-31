#!/bin/bash

FILE1=samples_VBFE_wMuTauFiltersL1_VBF_DoubleJets30_Mass_Min500_IsoEG10.root
FILE2=samples_VBFE_wMuTauFiltersL1_VBF_DoubleJets35_Mass_Min500_IsoEG10.root
FILE3=samples_VBFE_wMuTauFiltersL1_VBF_DoubleJets40_Mass_Min500_IsoEG10.root
FILE4=samples_VBFE_wMuTauFiltersL1_VBF_DoubleJets45_Mass_Min500_IsoEG10.root
FILE5=samples_VBFE_wMuTauFiltersL1_VBF_DoubleJets50_Mass_Min500_IsoEG10.root

DIR=eff_samples/
INPUT1="$DIR$FILE1"
INPUT2="$DIR$FILE2"
INPUT3="$DIR$FILE3"
INPUT4="$DIR$FILE4"
INPUT5="$DIR$FILE5"

python3 make_hists.py -i $INPUT1;
python3 make_hists.py -i $INPUT2;
python3 make_hists.py -i $INPUT3;
python3 make_hists.py -i $INPUT4;
python3 make_hists.py -i $INPUT5;

HISTS=hists_
python3 make_plots.py -i $HISTS$FILE1;
python3 make_plots.py -i $HISTS$FILE2;
python3 make_plots.py -i $HISTS$FILE3;
python3 make_plots.py -i $HISTS$FILE4;
python3 make_plots.py -i $HISTS$FILE5;

RATIOS=ratios_
python3 make_comparison_plot.py \
-i1 "$RATIOS$HISTS$FILE1" \
-i2 "$RATIOS$HISTS$FILE2" \
-i3 "$RATIOS$HISTS$FILE3" \
-i4 "$RATIOS$HISTS$FILE4" \
-i5 "$RATIOS$HISTS$FILE5"; 
