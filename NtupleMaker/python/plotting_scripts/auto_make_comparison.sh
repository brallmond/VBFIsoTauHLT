#!/bin/bash

#FILE1=UM_Tight_30_320_10.root
#FILE2=UM_Loose_30_320_10.root
#FILE3=UM_Loose_38_460_12.root
#FILE4=UM_Loose_32_440_14.root


pyroot make_hists.py -i ../../../../data/UM_Tight_30_320_10.root -s 0;
pyroot make_hists.py -i ../../../../data/UM_Loose_30_320_10.root -s 0;
pyroot make_hists.py -i ../../../../data/UM_Loose_38_460_12.root -s 1;
pyroot make_hists.py -i ../../../../data/UM_Loose_32_440_14.root -s 2;

pyroot make_plots.py -i hists_UM_Tight_30_320_10.root -L False;
pyroot make_plots.py -i hists_UM_Loose_30_320_10.root -L False;
pyroot make_plots.py -i hists_UM_Loose_38_460_12.root -L False;
pyroot make_plots.py -i hists_UM_Loose_32_440_14.root -L False;

pyroot make_comparison_plot.py \
-i1 ratios_hists_UM_Tight_30_320_10.root \
-i2 ratios_hists_UM_Loose_30_320_10.root \
-i3 ratios_hists_UM_Loose_38_460_12.root \
-i4 ratios_hists_UM_Loose_32_440_14.root; 
