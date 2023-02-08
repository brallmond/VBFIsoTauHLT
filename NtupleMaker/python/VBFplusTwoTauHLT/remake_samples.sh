# not really a bash file, just commands thrown in one
# 2018 
for line in `cat 2018_rate_files.txt`; do echo $line; python3 L1VBFIsoTauEff.py -i $line -r 2018O -DT 34 -DJ 35 > rate_2018O_RetryDiJetBranches.txt; done

hadd Retry_AddedDiJetBranches_L1DiTau34_L1DiJetOR35_EZB_2018O_DoubleJets35_Mass_Min_450_IsoTau45.root L1DiTau34_L1DiJetOR35_EZB_2018_EZB?_EGORL1_VBF_DoubleJets35_Mass_Min450_IsoTau45.root

rm L1DiTau34_L1DiJetOR35_EZB_2018_EZB?_EGORL1_VBF_DoubleJets35_Mass_Min450_IsoTau45.root

# 2022 E
for line in `cat 2022_E_rate_files.txt`; do echo $line; python3 L1VBFIsoTauEff.py -i $line -r 2022E -DT 34 -DJ 35 > rate_2022E_RetryDiJetBranches.txt; done

hadd Retry_AddedDiJetBranches_L1DiTau34_L1DiJetOR35_EZB_2022E_DoubleJets35_Mass_Min_450_IsoTau45.root L1DiTau34_L1DiJetOR35_EZB_E_2022_EZB?_2022EL1_VBF_DoubleJets35_Mass_Min450_IsoTau45.root L1DiTau34_L1DiJetOR35_EZB_E_2022_EZB??_2022EL1_VBF_DoubleJets35_Mass_Min450_IsoTau45.root

rm L1DiTau34_L1DiJetOR35_EZB_E_2022_EZB?_2022EL1_VBF_DoubleJets35_Mass_Min450_IsoTau45.root L1DiTau34_L1DiJetOR35_EZB_E_2022_EZB??_2022EL1_VBF_DoubleJets35_Mass_Min450_IsoTau45.root

# 2022 F
for line in `cat 2022_F_rate_files.txt`; do echo $line; python3 L1VBFIsoTauEff.py -i $line -r 2022F -DT 34 -DJ 35 > rate_2022F_RetryDiJetBranches.txt; done

hadd Retry_AddedDiJetBranches_L1DiTau34_L1DiJetOR35_EZB_2022F_DoubleJets35_Mass_Min_450_IsoTau45.root L1DiTau34_L1DiJetOR35_EZB_F_2022_updated_conf_EZB?_2022FL1_VBF_DoubleJets35_Mass_Min450_IsoTau45.root

rm L1DiTau34_L1DiJetOR35_EZB_F_2022_updated_conf_EZB?_2022FL1_VBF_DoubleJets35_Mass_Min450_IsoTau45.root

# 2022 G PU 60
for line in `cat 2022_G_rate_files.txt`; do echo $line; python3 L1VBFIsoTauEff.py -i $line -r 2022G_PU60 -DT 34 -DJ 35 > rate_2022G_PU60_RetryDiJetBranches.txt; done

hadd Retry_AddedDiJetBranches_L1DiTau34_L1DiJetOR35_EZB_2022G_PU60_DoubleJets35_Mass_Min_450_IsoTau45.root L1DiTau34_L1DiJetOR35_EZB_G_2022_EZB?_2022GL1_VBF_DoubleJets35_Mass_Min450_IsoTau45.root

rm L1DiTau34_L1DiJetOR35_EZB_G_2022_EZB?_2022GL1_VBF_DoubleJets35_Mass_Min450_IsoTau45.root

# 2022 G PU 70
for line in `cat 2022_G_rate_files.txt`; do echo $line; python3 L1VBFIsoTauEff.py -i $line -r 2022G_PU70 -DT 34 -DJ 35 > rate_2022G_PU70_RetryDiJetBranches.txt; done

hadd Retry_AddedDiJetBranches_L1DiTau34_L1DiJetOR35_EZB_2022G_PU70_DoubleJets35_Mass_Min_450_IsoTau45.root L1DiTau34_L1DiJetOR35_EZB_G_2022_EZB?_2022GL1_VBF_DoubleJets35_Mass_Min450_IsoTau45.root

rm L1DiTau34_L1DiJetOR35_EZB_G_2022_EZB?_2022GL1_VBF_DoubleJets35_Mass_Min450_IsoTau45.root

# 2022 G PU 70 DiJet 45 (only for IsoTau PU studies)
for line in `cat 2022_G_rate_files.txt`; do echo $line; python3 L1VBFIsoTauEff.py -i $line -r 2022G_PU70 -DT 34 -DJ 45 > rate_2022G_PU70_RetryDiJet45Branches.txt; done

hadd Retry_AddedDiJetBranches_L1DiTau34_L1DiJetOR45_EZB_2022G_PU70_DoubleJets35_Mass_Min_450_IsoTau45.root L1DiTau34_L1DiJetOR45_EZB_G_2022_EZB?_2022GL1_VBF_DoubleJets35_Mass_Min450_IsoTau45.root

rm L1DiTau34_L1DiJetOR45_EZB_G_2022_EZB?_2022GL1_VBF_DoubleJets35_Mass_Min450_IsoTau45.root









