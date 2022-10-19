#!/bin/bash

FILE1=UM_Tight_30_320_10.root
FILE2=UM_Loose_30_320_10.root
FILE3=UM_Loose_38_460_12.root
FILE4=UM_Loose_32_440_14.root


pyroot make_hists.py -i ../../../../data/$FILE1 -s 0;
pyroot make_hists.py -i ../../../../data/$FILE2 -s 0;
pyroot make_hists.py -i ../../../../data/$FILE3 -s 1;
pyroot make_hists.py -i ../../../../data/$FILE4 -s 2;

pyroot make_plots.py -i hists_$FILE1 -L False;
pyroot make_plots.py -i hists_$FILE2 -L False;
pyroot make_plots.py -i hists_$FILE3 -L False;
pyroot make_plots.py -i hists_$FILE4 -L False;

pyroot make_comparison_plot.py \
-i1 ratios_hists_$FILE1 \
-i2 ratios_hists_$FILE2 \
-i3 ratios_hists_$FILE3 \
-i4 ratios_hists_$FILE4; 
