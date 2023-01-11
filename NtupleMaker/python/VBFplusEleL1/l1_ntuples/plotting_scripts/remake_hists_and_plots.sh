#!/bin/sh

INPUT2022=2022_l1skim.root
INPUT2018=2018_l1skim.root

python3 make_hists_L1ElesAndJets.py -i $INPUT2022 -o hists_2022.root
python3 make_hists_L1ElesAndJets.py -i $INPUT2018 -o hists_2018.root

pyroot make_plots_L1ElesAndJets.py -i1 hists_2022.root -l1 2022 -i2 hists_2018.root -l2 2018
