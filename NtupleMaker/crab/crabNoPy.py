#stripped down crab submit file...

from CRABClient.UserUtilities import config
config = config()

config.General.workArea = 'test'

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'hltMoreHLTFilters.py'

config.Data.inputDBS = 'global'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 1
config.Data.outLFNDirBase = '/store/user/ballmond'

config.Data.ignoreLocality = True
config.Site.whitelist = ['T2_CH_CSCS','T1_US_FNAL', 'T2_FR_GRIF_LLR', 'T2_HU_Budapest', 'T3_US_FNALLPC', 'T2_CH_CERN', 'T2_BE_UCL', 'T2_DE_RWTH', 'T2_FR_IPHC', 'T2_IN_TIFR', 'T2_IT_Pisa', 'T2_UK_London_IC', 'T2_US_Wisconsin', 'T2_IT_Rome', 'T2_EE_Estonia', 'T2_UK_SGrid_RALPP']
#config.Site.whitelist = ['T3_US_FNALLPC'] #use if submit user-data
config.JobType.maxJobRuntimeMin = 2000
config.JobType.maxMemoryMB = 4000
config.JobType.inputFiles = ['L1Menu_Collisions2022_v1_2_0_edited.xml']

#config.Data.runRange = '325022'
#config.Data.runRange = '324747'
#config.Data.runRange = '324237,324970,324980,325022'
#config.Data.runRange = '321755,323725,323755,323790,323841,323940,323976,323978,324021,324077,324201,324237,324245,324293,324315,324420,324747,324785,324835,324897,324970,324980,324997,325022,325057,325097-325099'
#config.Data.runRange = '323755'

config.Site.storageSite = 'T3_US_FNALLPC'

config.General.requestName = 'MuTauFiltersIncluded'

#config.Data.inputDataset = '/EphemeralHLTPhysics8/Run2018D-v1/RAW'

#config.Data.inputDataset = '/EphemeralZeroBias8/Run2018D-v1/RAW'

#config.Data.userInputFiles = ['/store/user/ballmond/EZBUpsL1sAllRunsMerged/EZB1UpsL1sAllRuns.root']
#config.Data.outputPrimaryDataset = 'EZB1_L1UpsRun324747'

#Santeri recommended Summer samples

    #VBF
#the AOD with the premix is the MiniAOD's parent dataset, so this should be fine
config.Data.inputDataset = '/VBFHToTauTau_M125_TuneCP5_14TeV-powheg-pythia8/Run3Summer21MiniAOD-120X_mcRun3_2021_realistic_v5-v2/MINIAODSIM'
config.Data.secondaryInputDataset = '/VBFHToTauTau_M125_TuneCP5_14TeV-powheg-pythia8/Run3Summer21DRPremix-120X_mcRun3_2021_realistic_v6-v2/GEN-SIM-DIGI-RAW'   

    #ggH
#config.Data.inputDataset = '/GluGluHToTauTau_M-125_TuneCP5_14TeV-powheg-pythia8/Run3Summer21MiniAOD-120X_mcRun3_2021_realistic_v5-v2/MINIAODSIM'
#config.Data.secondaryInputDataset = '/GluGluHToTauTau_M-125_TuneCP5_14TeV-powheg-pythia8/Run3Summer21DRPremix-120X_mcRun3_2021_realistic_v6-v2/GEN-SIM-DIGI-RAW'

    # newest ggH
#config.Data.inputDataset = '/GluGluHToTauTau_M-125_TuneCP5_14TeV-powheg-pythia8/Run3Winter21DRMiniAOD-FlatPU30to80FEVT_112X_mcRun3_2021_realistic_v16-v1/MINIAODSIM'
#config.Data.secondaryInputDataset = '/GluGluHToTauTau_M-125_TuneCP5_14TeV-powheg-pythia8/Run3Winter21DRMiniAOD-FlatPU30to80FEVT_112X_mcRun3_2021_realistic_v16-v1/GEN-SIM-DIGI-RAW'
    # newest VBF
#config.Data.inputDataset = '/VBFHToTauTau_M125_TuneCP5_14TeV-powheg-pythia8/Run3Winter21DRMiniAOD-FlatPU30to80FEVT_112X_mcRun3_2021_realistic_v16-v1/MINIAODSIM'
#config.Data.secondaryInputDataset = '/VBFHToTauTau_M125_TuneCP5_14TeV-powheg-pythia8/Run3Winter21DRMiniAOD-FlatPU30to80FEVT_112X_mcRun3_2021_realistic_v16-v1/GEN-SIM-DIGI-RAW'
