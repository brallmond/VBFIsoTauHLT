import CRABClient
# may be necessary to do this first: source /cvmfs/cms.cern.ch/common/crab-setup.sh

# using crabapi/multicrab submission
# https://twiki.cern.ch/twiki/bin/view/CMSPublic/CRABClientLibraryAPI
# bottom of this twiki describes using multicrab,
# https://twiki.cern.ch/twiki/bin/view/CMSPublic/CRAB3AdvancedTutorial

from CRABClient.UserUtilities import config
config = config()

config.General.workArea = 'test'

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'hltUpdatedVBFEGsMC.py'

config.Data.inputDBS = 'global'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 1
config.Data.outLFNDirBase = '/store/user/ballmond'

config.Data.ignoreLocality = True
config.Site.whitelist = ['T2_CH_CSCS','T1_US_FNAL', 'T2_FR_GRIF_LLR', 'T2_HU_Budapest', 'T3_US_FNALLPC', 'T2_CH_CERN', 'T2_BE_UCL', 'T2_DE_RWTH', 'T2_FR_IPHC', 'T2_IN_TIFR', 'T2_IT_Pisa', 'T2_UK_London_IC', 'T2_US_Wisconsin', 'T2_IT_Rome', 'T2_EE_Estonia', 'T2_UK_SGrid_RALPP']
config.JobType.maxJobRuntimeMin = 2000
config.JobType.maxMemoryMB = 4000
config.JobType.inputFiles = ['L1Menu_Collisions2022_v1_3_0_edited_corrected.xml']


config.Site.storageSite = 'T3_US_FNALLPC'

#i=0
#config.General.requestName = f'EraG2022_EZB{i}_Mar6th_FullyWorkingHLTs_retry'
#config.Data.inputDataset   = f'/EphemeralZeroBias{i}/Run2022G-v1/RAW'

# lines particular to user submission
# a good coder would make a separate conf or a simple if statement.
#config.Site.whitelist = ['T3_US_FNALLPC'] #use if submit user-data
#config.Data.runRange = '323755'
#config.Data.userInputFiles = ['/store/user/ballmond/EZBUpsL1sAllRunsMerged/EZB1UpsL1sAllRuns.root']
#config.Data.outputPrimaryDataset = 'EZB1_L1UpsRun324747'


    #VBF
#the AOD with the premix is the MiniAOD's parent dataset, so this should be fine
config.General.requestName = 'MC_03062023'
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
