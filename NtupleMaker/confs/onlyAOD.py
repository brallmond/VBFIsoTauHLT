# from https://github.com/Ror5ch/VBFTau/blob/master/NtupleMaker/python/ConfFile_cfg.py
# Kyungwook's repo originally

import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
        'root://cms-xrd-global.cern.ch//store/mc/Run3Summer21MiniAOD/VBFHToTauTau_M125_TuneCP5_14TeV-powheg-pythia8/MINIAODSIM/120X_mcRun3_2021_realistic_v5-v2/30000/02ef66b7-b3aa-4d61-85bd-d84c73500c13.root'
    )
)



updatedTauName = "slimmedTausNewID" #name of pat::Tau collection with new tau-Ids
import RecoTauTag.RecoTau.tools.runTauIdMVA as tauIdConfig
tauIdEmbedder = tauIdConfig.TauIDEmbedder(process, cms, #debug = False,
                    updatedTauName = updatedTauName,
                    toKeep = ["deepTau2017v2p1", #deepTau TauIDs
                               ])
tauIdEmbedder.runTauID()
# Path and EndPath definitions

process.demo = cms.EDAnalyzer('NtupleMaker'
     #, tracks = cms.untracked.InputTag('ctfWithMaterialTracks')
     , triggerResults = cms.untracked.InputTag("TriggerResults","","MYOTHERHLT") #change to HLT instead of MYOTHERHLT if not rerun 
     , triggerEvent = cms.untracked.InputTag("hltTriggerSummaryAOD","","MYOTHERHLT")
     , triggerEventWithRefs = cms.untracked.InputTag("hltTriggerSummaryRAW","","MYOTHERHLT")
     #, PFTauCollection = cms.untracked.InputTag("hltHpsPFTauProducer","","MYOTHERHLT")
     #, hltHpsTracks = cms.untracked.InputTag("hltHpsPFTauTrack","","MYOTHERHLT")

     , SkipEvent = cms.untracked.vstring('ProductNotFound')

     , fillingTriggers = cms.untracked.bool(False) # can run on data/GEN-SIM-DIGI-RAW
     , fillingEventInfo = cms.untracked.bool(True) # can run on data/GEN-SIM-DIGI-RAW/MINIAODSIM
     , fillingL1 = cms.untracked.bool(True)        # can run on MINIAODSIM
     , fillingTaus = cms.untracked.bool(True)      # can run on MINIAODSIM
     , fillingJets = cms.untracked.bool(True)      # can run on MINIAODSIM
     , fillingElectrons = cms.untracked.bool(True) # can run on MINIAODSIM
     , development = cms.untracked.bool(False)     # left in to play nice with NtupleMaker
     , doGenParticles = cms.untracked.bool(False)  # left in to play nice with NtupleMaker

     , jetTriggerPrimitives = cms.untracked.InputTag("caloStage2Digis", "Jet", "RECO")
     , tauTriggerPrimitives = cms.untracked.InputTag("caloStage2Digis", "Tau", "RECO")
     , eleTriggerPrimitives = cms.untracked.InputTag("caloStage2Digis", "EGamma", "RECO")

     , genParticleSrc = cms.untracked.InputTag("prunedGenParticles")
     , VtxLabel = cms.untracked.InputTag("offlineSlimmedPrimaryVertices")
     , rhoLabel = cms.untracked.InputTag("fixedGridRhoFastjetAll")
     , tauSrc = cms.untracked.InputTag("slimmedTausNewID")
     , electronSrc = cms.untracked.InputTag("slimmedElectrons")
     , ak4JetSrc = cms.untracked.InputTag("slimmedJets")
)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string("histo.root"),
    closeFileFast = cms.untracked.bool(True)
)

process.demoPath = cms.EndPath(
        process.rerunMvaIsolationSequence * # comment out if not running on MINIAODSIM
        getattr(process,updatedTauName) *   # comment out if not running on MINIAODSIM
        process.demo
)
