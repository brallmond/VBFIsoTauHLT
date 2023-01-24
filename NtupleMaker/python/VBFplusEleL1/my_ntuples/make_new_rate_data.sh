# process your input dataset
for line in `cat 2022_E_rate_files.txt`; do echo $line; python3 L1VBFEleEff.py -i $line -r 2022E -s tight -L 0 >> rate_2022E_tight_total_output.txt; done

# hadd the output
hadd EZB_TightL1_2022_UpdatedRateInfo.root EZB_E_2022_EZB?_2022EL1_VBF_DoubleJets30_Mass_Min300_IsoEG10.root EZB_E_2022_EZB??_2022EL1_VBF_DoubleJets30_Mass_Min300_IsoEG10.root 

# rm the input files
rm EZB_E_2022_EZB?_2022EL1_VBF_DoubleJets30_Mass_Min300_IsoEG10.root EZB_E_2022_EZB??_2022EL1_VBF_DoubleJets30_Mass_Min300_IsoEG10.root 

